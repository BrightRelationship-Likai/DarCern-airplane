using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.IO;
using System.IO.Ports;


namespace CeUAV
{
    public partial class MainForm : Form
    {
        public MainForm thisForm = null;

        public delegate void action();

        public Socket socket = null;
        public EndPoint endPoint = null;
        public bool isListening = false;
        public bool isRunning = true;

        public WaveForm wf = null;
        public CtlForm cf = null;
        public DebugForm df = null;
        public DriverPowerForm dpf = null;
        public DataForm dataF = null;
        public GpsMapForm gmf = null;

        public Protrocol ptl = null;

        public SerialPort sp = null;

        public Thread tcpThread = null;
        public Thread comThread = null;

        public MainForm()
        {
            InitializeComponent();
            thisForm = this;
            menuStrip1.Renderer = new MyMenuRender();

        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            AllMsg.Load();
            ptl = new Protrocol(this);

            this.Hide();
            DataSrcFrom dsf = new DataSrcFrom(this);
            dsf.ShowDialog();
            if (AllMsg.isCom == false && AllMsg.isTCP == false)
            {
                this.Close();
                return;
            }
            this.Show();


            if (ptl.load(AllMsg.protocolPath) == false)
            {
                MessageBox.Show("协议解析错误，请重新选择协议文件，或访问http:\\www.creelinks.com下载对应的协议文件！");
                this.Close();
                return;
            }
            wf = new WaveForm(this);
            cf = new CtlForm(this);
            df = new DebugForm(this);
            dpf = new DriverPowerForm(this);
            dataF = new DataForm(this);
            gmf = new GpsMapForm();

            if (AllMsg.isTCP)
            {
                tcpThread = new Thread(ListenClientConnect);
                tcpThread.Start();
            }
            else
            {
                sp = new SerialPort(AllMsg.comPort, Convert.ToInt32(AllMsg.comBaudRate), Parity.None, 8, StopBits.One);
                try
                {
                    sp.ReadBufferSize = 10240;
                    sp.WriteBufferSize = 10240;
                    sp.Open();
                    comThread = new Thread(comThreadCallBack);
                    comThread.Start();
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("串口打开失败：" + AllMsg.comPort + "," + ex.Message);
                }
            }
            timer1.Enabled = true;
        }

        /// <summary>
        /// 串口循环检测是否有数据
        /// </summary>
        public void comThreadCallBack()
        {
            try
            {
                while (isRunning)
                {

                    if (!sp.IsOpen)
                    {
                        return;
                    }
                    if (sp.BytesToRead > 0)
                    {
                        byte[] temp = new byte[sp.BytesToRead];
                        sp.Read(temp, 0, temp.Length);
                        ptl.dealRecv(temp,temp.Length);
                    }
                    Thread.Sleep(10);
                }

            }
            catch (System.Exception ex)
            {
                if (isRunning == true)
                {
                MessageBox.Show("串口发生故障，采集线程已中止！"+ex.Message);
                }
            }
        }

        /// <summary>
        /// TCP处理接收到的数据
        /// </summary>
        /// <param name="recvBuf"></param>
        public void dealRecvVal(byte[] recvBuf, int recvCount)
        {
            try
            {
                if (dataF.isShow == true)
                {
                    StringBuilder sb = new StringBuilder();
                    for (int m = 0; m < recvCount; m++)
                    {
                        sb.Append("0x" + Convert.ToString(recvBuf[m], 16) + ",");
                    }
                    sb.Append(Environment.NewLine);
                    this.Invoke((action)delegate
                    {
                        dataF.lblRecvNum.Text = (Convert.ToInt32(dataF.lblRecvNum.Text) + 1).ToString();
                        if (dataF.txtRecv.Text.Length >= 10240)
                        {
                            dataF.txtRecv.Clear();
                        }
                        dataF.txtRecv.AppendText(sb.ToString());
                    });
                }

                int index = -1;
                int i;
                int RECV_PACK_LENGTH = 32;
                for (i = 0; i <= recvCount - RECV_PACK_LENGTH; i++)
                {
                    if (recvBuf[i] == 0x55 && (recvBuf[i + RECV_PACK_LENGTH - 1] == 0xFE))
                    {
                        index = i + 2;
                        break;
                    }
                }
                if (index == -1)
                {
                    return;
                }
                if (recvBuf[index - 1] != 0) return;

                ptl.hashTableRecv["pitchByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["rollByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["yawByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["temperature"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["altitude"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["batVoltage"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["accelerator"] = (double)(BitConverter.ToInt32(recvBuf, index)); index += 4;
                index += 4;
                ptl.hashTableRecv["pressure"] = (double)(BitConverter.ToInt32(recvBuf, index)); index += 4;
                ptl.hashTableRecv["driverPower0"] = (double)(BitConverter.ToInt32(recvBuf, index)); index += 4;
                ptl.hashTableRecv["driverPower1"] = (double)(BitConverter.ToInt32(recvBuf, index)); index += 4;
                ptl.hashTableRecv["driverPower2"] = (double)(BitConverter.ToInt32(recvBuf, index)); index += 4;
                ptl.hashTableRecv["driverPower3"] = (double)(BitConverter.ToInt32(recvBuf, index)); index += 4;
                ptl.hashTableRecv["accX"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["accXByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                index += 4;
                ptl.hashTableRecv["accY"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["accYByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["accZ"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["accZByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["gyrX"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["gyrXByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["gyrY"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                index += 4;
                ptl.hashTableRecv["gyrYByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["gyrZ"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["gyrZByFilter"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["pitchByAcc"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["pitchByGyr"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["rollByAcc"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["rollByGyr"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                index += 4;
                ptl.hashTableRecv["yawByAcc"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;
                ptl.hashTableRecv["yawByGyr"] = (double)(BitConverter.ToInt32(recvBuf, index)) / 1000; index += 4;

                this.Invoke((action)delegate
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (wf.cbb1[j].SelectedItem.ToString() != "--")
                        {
                            wf.wfgGb1.Plots[j].PlotYAppend((double)(ptl.hashTableRecv[wf.cbb1[j].SelectedItem.ToString().ToString()]));
                            wf.lbl1[j].Text = wf.cbb1[j].SelectedItem.ToString() + ":" + ((double)(ptl.hashTableRecv[wf.cbb1[j].SelectedItem.ToString().ToString()])).ToString();
                        }

                        if (wf.cbb2[j].SelectedItem.ToString() != "--")
                        {
                            wf.wfgGb2.Plots[j].PlotYAppend((double)(ptl.hashTableRecv[wf.cbb2[j].SelectedItem.ToString().ToString()]));
                            wf.lbl2[j].Text = wf.cbb2[j].SelectedItem.ToString() + ":" + ((double)(ptl.hashTableRecv[wf.cbb2[j].SelectedItem.ToString().ToString()])).ToString();
                        }
                    }


                    if (wf.sw != null)
                    {
                        ArrayList akeys = new ArrayList(ptl.hashTableRecv.Keys);
                        StringBuilder sb2 = new StringBuilder();
                        foreach (string skey in akeys)
                        {
                            sb2.Append(ptl.hashTableRecv[skey]);
                            sb2.Append("\t");
                        }
                        wf.sw.WriteLine(sb2.ToString());
                    }
                });
            }
            catch (Exception)
            {
            }
        }


        /// <summary>  
        /// TCP监听客户端连接  
        /// </summary>  
        private void ListenClientConnect()
        {
            try
            {
                //IPAddress addr = new System.Net.IPAddress(Dns.GetHostByName(Dns.GetHostName()).AddressList[0].Address);  
                IPAddress addr = IPAddress.Parse(AllMsg.tcpIP);
                socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                socket.Bind(new IPEndPoint(addr, Convert.ToInt32(AllMsg.tcpPort)));
                socket.Listen(10);
                Console.WriteLine("启动监听{0}成功", socket.LocalEndPoint.ToString());
                this.Invoke((action)delegate
                {
                    lblSelfIP.Text = "本机(服务器)IP：" + addr.ToString()+":"+AllMsg.tcpPort;
                });
                while (true)
                {
                    try
                    {
                        Socket clientSocket = socket.Accept();
                        if (isRunning == false)
                        {
                            return;
                        }
                        Thread receiveThread = new Thread(ReceiveMessage);
                        receiveThread.Start(clientSocket);
                    }
                    catch (Exception)
                    {
                    }
                }
            }
            catch (System.Exception ex)
            {
                if (isRunning  == true)
                {
                    MessageBox.Show("服务器创建失败：" + ex.Message);
                }
            }

        }
        /// <summary>  
        /// 接收消息  
        /// </summary>  
        /// <param name="clientSocket"></param>  
        private void ReceiveMessage(object clientSocket)
        {
            Socket myClientSocket = (Socket)clientSocket;
            byte[] recvBuf = new byte[10240];
            this.Invoke((action)delegate
            {
                lblStatus.Text = "客户端连接状态：已连接";
                lblStatus.ForeColor = Color.Aqua;
                lblClientIP.Text = "客户端IP：" + myClientSocket.RemoteEndPoint.ToString();
            });
            while (true)
            {
                try
                {
                    //通过clientSocket接收数据  
                    int receiveNumber = 0;
                    if (myClientSocket.Available >= 0)
                    {
                        receiveNumber = myClientSocket.Receive(recvBuf);
                        if (isRunning == false) return;
                    }
                    if (receiveNumber > 0)
                    {
                        ptl.dealRecv(recvBuf, receiveNumber);
                        myClientSocket.Send(ptl.dealSend());//接收到数据后，才发送数据
                    }
                    Thread.Sleep(10);
                }
                catch (Exception ex)
                {
                    this.Invoke((action)delegate
                    {
                        lblStatus.Text = "客户端连接状态：断开";
                        lblStatus.ForeColor = Color.Red;
                        lblClientIP.Text = "客户端IP：";
                    });
                    Console.WriteLine(ex.Message);
                    myClientSocket.Shutdown(SocketShutdown.Both);
                    myClientSocket.Close();
                    break;
                }
            }
        }

        //收集需要发送的信息
        public void getSendMsg()
        {
            ptl.hashTableSend["OutPitchKp"] = Convert.ToDouble(df.pitchOutKp);
            ptl.hashTableSend["OutPitchKi"] = Convert.ToDouble(df.pitchOutKi);
            ptl.hashTableSend["OutPitchKd"] = Convert.ToDouble(df.pitchOutKd);
            ptl.hashTableSend["InPitchKp"] = Convert.ToDouble(df.pitchInKp);
            ptl.hashTableSend["InPitchKi"] = Convert.ToDouble(df.pitchInKi);
            ptl.hashTableSend["InPitchKd"] = Convert.ToDouble(df.pitchInKd);

            ptl.hashTableSend["OutRollKp"] = Convert.ToDouble(df.rollOutKp);
            ptl.hashTableSend["OutRollKi"] = Convert.ToDouble(df.rollOutKi);
            ptl.hashTableSend["OutRollKd"] = Convert.ToDouble(df.rollOutKd);
            ptl.hashTableSend["InRollKp"] = Convert.ToDouble(df.rollInKp);
            ptl.hashTableSend["InRollKi"] = Convert.ToDouble(df.rollInKi);
            ptl.hashTableSend["InRollKd"] = Convert.ToDouble(df.rollInKd);

            ptl.hashTableSend["OutYawKp"] = Convert.ToDouble(df.yawOutKp);
            ptl.hashTableSend["OutYawKi"] = Convert.ToDouble(df.yawOutKi);
            ptl.hashTableSend["OutYawKd"] = Convert.ToDouble(df.yawOutKd);
            ptl.hashTableSend["InYawKp"] = Convert.ToDouble(df.yawInKp);
            ptl.hashTableSend["InYawKi"] = Convert.ToDouble(df.yawInKi);
            ptl.hashTableSend["InYawKd"] = Convert.ToDouble(df.yawInKd);

            ptl.hashTableSend["altKp"] = Convert.ToDouble(df.altKp);
            ptl.hashTableSend["altKi"] = Convert.ToDouble(df.altKi);
            ptl.hashTableSend["altKd"] = Convert.ToDouble(df.altKd);
            ptl.hashTableSend["altBase"] = Convert.ToDouble(df.altBase);

            ptl.hashTableSend["driverPower0Zero"] = Convert.ToDouble(dpf.d0);
            ptl.hashTableSend["driverPower1Zero"] = Convert.ToDouble(dpf.d1);
            ptl.hashTableSend["driverPower2Zero"] = Convert.ToDouble(dpf.d2);
            ptl.hashTableSend["driverPower3Zero"] = Convert.ToDouble(dpf.d3);

            ptl.hashTableSend["zeroPitch"] = Convert.ToDouble(df.zeroPitch);
            ptl.hashTableSend["zeroRoll"] = Convert.ToDouble(df.zeroRoll);
            ptl.hashTableSend["zeroYaw"] = Convert.ToDouble(df.zeroYaw);

            UInt32 status = 0x00000000;

            status |= ((df.rbYijihubo.Checked == true) ? (UInt32)0x00000001 : (UInt32)0x00000000);
            status |= ((df.rbErjiehubo.Checked == true) ? (UInt32)0x00000002 : (UInt32)0x00000000);
            status |= ((df.rbFour.Checked == true) ? (UInt32)0x00000004 : (UInt32)0x00000000);
            status |= ((df.rbKalman.Checked == true) ? (UInt32)0x00000008 : (UInt32)0x00000000);

            if (df.rbYijihubo.Checked == true)
            {
                status |= ((df.cbYijie.Checked == true) ? (UInt32)0x00000010 : (UInt32)0x00000000);
            }
            else if (df.rbErjiehubo.Checked == true)
            {
                status |= ((df.cbErjie.Checked == true) ? (UInt32)0x00000010 : (UInt32)0x00000000);
            }
            else if (df.rbFour.Checked == true)
            {
                status |= ((df.cbFour.Checked == true) ? (UInt32)0x00000010 : (UInt32)0x00000000);
            }
            else if (df.rbKalman.Checked == true)
            {
                status |= ((df.cbKalman.Checked == true) ? (UInt32)0x00000010 : (UInt32)0x00000000);
            }

            status |= ((df.cbPID.Checked == true) ? (UInt32)0x00000020 : (UInt32)0x00000000);

            status |= ((df.cbAngleZero.Checked == true) ? (UInt32)0x00008000 : (UInt32)0x00000000);

            status |= ((cf.btnLeft.Checked == true) ? (UInt32)0x00000040 : (UInt32)0x00000000);
            status |= ((cf.btnRight.Checked == true) ? (UInt32)0x00000080 : (UInt32)0x00000000);
            status |= ((cf.cbS2A.Checked == true) ? (UInt32)0x00000100 : (UInt32)0x00000000);
            status |= ((cf.cbS2B.Checked == true) ? (UInt32)0x00000200 : (UInt32)0x00000000);
            status |= ((cf.cbS2C.Checked == true) ? (UInt32)0x00000400 : (UInt32)0x00000000);
            status |= ((cf.cbS2D.Checked == true) ? (UInt32)0x00000800 : (UInt32)0x00000000);

            status |= 0x00001000;

            ptl.hashTableSend["status"] = Convert.ToDouble(status);

            ptl.hashTableSend["yijieK1"] = Convert.ToDouble(df.yijieK1);
            ptl.hashTableSend["erjieK2"] = Convert.ToDouble(df.erjieK2);

            ptl.hashTableSend["imuKp"] = Convert.ToDouble(df.imuKp);
            ptl.hashTableSend["imuKi"] = Convert.ToDouble(df.imuKi);

            ptl.hashTableSend["filterR_angle"] = Convert.ToDouble(df.kalmanRangle);
            ptl.hashTableSend["filterQ_angle"] = Convert.ToDouble(df.kalmanQangle);
            ptl.hashTableSend["filterQ_gyro"] = Convert.ToDouble(df.kalmanQgyro);
        }

        /// <summary>
        /// 定时器回调，用于更新控件信息
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                Pen pen = new Pen(Color.White);
                pen.Width = 3;
                SolidBrush sb = new SolidBrush(Color.DeepSkyBlue);
                Graphics g = Graphics.FromImage(cf.bitmapBack);
                g.Clear(Color.Black);

                double a = Convert.ToDouble(ptl.hashTableRecv["pitchByFilter"]);


                Point p0 = new Point(0, 0);
                Point p1 = new Point(300, 0);
                Point p2 = new Point(300, -(int)(Convert.ToDouble(ptl.hashTableRecv["pitchByFilter"]) * 8) - (int)(Convert.ToDouble(ptl.hashTableRecv["rollByFilter"]) * 4) + 150);
                Point p3 = new Point(0, -(int)(Convert.ToDouble(ptl.hashTableRecv["pitchByFilter"]) * 8) + (int)(Convert.ToDouble(ptl.hashTableRecv["rollByFilter"]) * 4) + 150);
                g.FillPolygon(sb, new Point[] { p0, p1, p2, p3 });

                pen = new Pen(Color.Yellow);
                sb = new SolidBrush(Color.Sienna);
                p0 = new Point(0, 300);
                p1 = new Point(300, 300);
                p2 = new Point(300, -(int)(Convert.ToDouble(ptl.hashTableRecv["pitchByFilter"]) * 8) - (int)(Convert.ToDouble(ptl.hashTableRecv["rollByFilter"]) * 4) + 150);
                p3 = new Point(0, -(int)(Convert.ToDouble(ptl.hashTableRecv["pitchByFilter"]) * 8) + (int)(Convert.ToDouble(ptl.hashTableRecv["rollByFilter"]) * 4) + 150);
                g.FillPolygon(sb, new Point[] { p0, p1, p2, p3 });

                g.DrawLine(pen, new Point(0, -(int)(Convert.ToDouble(ptl.hashTableRecv["pitchByFilter"]) * 8) + (int)(Convert.ToDouble(ptl.hashTableRecv["rollByFilter"]) * 4) + 150),
                    new Point(300, -(int)(Convert.ToDouble(ptl.hashTableRecv["pitchByFilter"]) * 8) - (int)(Convert.ToDouble(ptl.hashTableRecv["rollByFilter"]) * 4) + 150));

                g.DrawImage(cf.bitmapFore, 0, 0, 300, 300);

                pictureBox1.Image = cf.bitmapBack;

                dpf.gauge1.Value = Convert.ToDouble((ptl.hashTableRecv["driverPower0"]));
                dpf.gauge1.DialColor = Color.FromArgb((byte)(Convert.ToDouble((ptl.hashTableRecv["driverPower0"])) * 255 / 1000), 255, 0, 0);

                dpf.gauge2.Value = Convert.ToDouble((ptl.hashTableRecv["driverPower1"]));
                dpf.gauge2.DialColor = Color.FromArgb((byte)(Convert.ToDouble((ptl.hashTableRecv["driverPower1"])) * 255 / 1000), 255, 0, 0);

                dpf.gauge3.Value = Convert.ToDouble((ptl.hashTableRecv["driverPower2"]));
                dpf.gauge3.DialColor = Color.FromArgb((byte)(Convert.ToDouble((ptl.hashTableRecv["driverPower2"])) * 255 / 1000), 255, 0, 0);

                dpf.gauge4.Value = Convert.ToDouble((ptl.hashTableRecv["driverPower3"]));
                dpf.gauge4.DialColor = Color.FromArgb((byte)(Convert.ToDouble((ptl.hashTableRecv["driverPower3"])) * 255 / 1000), 255, 0, 0);

                double vall = Convert.ToDouble(ptl.hashTableRecv[cbbl.SelectedItem.ToString()]);
                if (gg1.Range.Maximum < vall)
                {
                    gg1.Range = new NationalInstruments.UI.Range(gg1.Range.Minimum, (int)(vall + 1));
                }
                if (gg1.Range.Minimum > vall)
                {
                    gg1.Range = new NationalInstruments.UI.Range((int)(vall - 1), gg1.Range.Maximum);
                }

                double valr = Convert.ToDouble(ptl.hashTableRecv[cbbr.SelectedItem.ToString()]);
                if (gg2.Range.Maximum < valr)
                {
                    gg2.Range = new NationalInstruments.UI.Range(gg1.Range.Minimum, (int)(valr + 1));
                }
                if (gg2.Range.Minimum > valr)
                {
                    gg2.Range = new NationalInstruments.UI.Range((int)(valr - 1), gg1.Range.Maximum);
                }
                gg1.Value = vall;
                gg2.Value = valr;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
                isRunning = false;
        }

        private void cbbl_SelectedIndexChanged(object sender, EventArgs e)
        {
            gg1.Range = new NationalInstruments.UI.Range(0, 1);
        }

        private void cbbr_SelectedIndexChanged(object sender, EventArgs e)
        {
            gg2.Range = new NationalInstruments.UI.Range(0, 1);
        }
 
        private void 关于ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new AboutForm().Show();
        }

        private void btnShowWave_Click(object sender, EventArgs e)
        {
            wf.Show();
        }

        private void btnShowDebug_Click(object sender, EventArgs e)
        {
            df.Show();
        }

        private void btnShowCtl_Click(object sender, EventArgs e)
        {
            cf.Show();
        }

        private void btnDataForm_Click(object sender, EventArgs e)
        {
            dataF.Show();
        }

        private void btnDpForm_Click(object sender, EventArgs e)
        {
            dpf.Show();
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            NewTMUForm ntf = new NewTMUForm();
            ntf.ShowDialog();
            if (ntf.packSize != -1)
            {
                TMUForm tf = new TMUForm(ntf.packSize, null);
                tf.ShowDialog();
            }
        }

        private void btnPtl_Click(object sender, EventArgs e)
        {
            TMUForm tf = new TMUForm(ptl.packSize,AllMsg.protocolPath);
            tf.ShowDialog();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            byte[] temp = new byte[160];
            for (int i = 0; i < 5; i++)
            {
                temp[0+i*32] = 0x55;
                temp[1 + i * 32] = (byte)i;
                temp[30 + i * 32] = (byte)(0x55+(byte)(i));
                temp[31 + i * 32] = 0xFE;
            }
            if (ptl != null)
            {
                
                ptl.dealRecv(temp, 160);
            }

        }

        private void ToolStripMenuItemProtrocol_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"http:\\www.creelinks.com\uav\protrocol.html");
        }

        private void groupBox1_Paint(object sender, PaintEventArgs e)
        {
            GroupBox gb = (GroupBox)sender;
            e.Graphics.Clear(gb.BackColor);
            e.Graphics.DrawString(gb.Text, gb.Font, Brushes.Aqua, 10, 1);
            e.Graphics.DrawLine(Pens.Aqua, 1, 7, 8, 7);
            e.Graphics.DrawLine(Pens.Aqua, e.Graphics.MeasureString(gb.Text, gb.Font).Width + 8, 7, gb.Width - 2, 7);
            e.Graphics.DrawLine(Pens.Aqua, 1, 7, 1, gb.Height - 2);
            e.Graphics.DrawLine(Pens.Aqua, 1, gb.Height - 2, gb.Width - 2, gb.Height - 2);
            e.Graphics.DrawLine(Pens.Aqua, gb.Width - 2, 7, gb.Width - 2, gb.Height - 2);
        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            System.Environment.Exit(System.Environment.ExitCode);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
        }


        private void btnGPSMap_Click(object sender, EventArgs e)
        {
            gmf.Show();
        }
    }
}


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Collections;
using System.Windows.Forms;

namespace CeUAV
{
    public class Protrocol
    {
        public int packSize = 32;
        public int packCount = 1;
        public delegate void action();
        public Package package = null;

        public WaveForm wf = null;
        public MainForm mf = null;

        public ArrayList alPar = new ArrayList();
        public ArrayList alMul = new ArrayList();

        public NoSortHashtable hashTableRecv = new NoSortHashtable();
        public NoSortHashtable hashTableSend = new NoSortHashtable();



        public Protrocol(MainForm mf)
        {
            this.mf = mf;
            this.wf = mf.wf;
            package = new Package(mf);
            initialSend();
        }

        public bool initialSend()
        {
            hashTableSend.Add("LeftX", (double)(0));
            hashTableSend.Add("LeftY", (double)(0));
            hashTableSend.Add("RightX", (double)(0));
            hashTableSend.Add("RightY", (double)(0));

            hashTableSend.Add("status", (double)(0));

            hashTableSend.Add("OutPitchKp", (double)(0));
            hashTableSend.Add("OutPitchKi", (double)(0));
            hashTableSend.Add("OutPitchKd", (double)(0));
            hashTableSend.Add("InPitchKp", (double)(0));
            hashTableSend.Add("InPitchKi", (double)(0));
            hashTableSend.Add("InPitchKd", (double)(0));

            hashTableSend.Add("OutRollKp", (double)(0));
            hashTableSend.Add("OutRollKi", (double)(0));
            hashTableSend.Add("OutRollKd", (double)(0));
            hashTableSend.Add("InRollKp", (double)(0));
            hashTableSend.Add("InRollKi", (double)(0));
            hashTableSend.Add("InRollKd", (double)(0));

            hashTableSend.Add("OutYawKp", (double)(0));
            hashTableSend.Add("OutYawKi", (double)(0));
            hashTableSend.Add("OutYawKd", (double)(0));
            hashTableSend.Add("InYawKp", (double)(0));
            hashTableSend.Add("InYawKi", (double)(0));
            hashTableSend.Add("InYawKd", (double)(0));

            hashTableSend.Add("altKp", (double)(0));
            hashTableSend.Add("altKi", (double)(0));
            hashTableSend.Add("altKd", (double)(0));
            hashTableSend.Add("altBase", (double)(0));

            hashTableSend.Add("yijieK1", (double)(0));
            hashTableSend.Add("erjieK2", (double)(0));

            hashTableSend.Add("imuKp", (double)(0));
            hashTableSend.Add("imuKi", (double)(0));

            hashTableSend.Add("filterR_angle", (double)(0));
            hashTableSend.Add("filterQ_angle", (double)(0));
            hashTableSend.Add("filterQ_gyro", (double)(0));

            hashTableSend.Add("driverPower0Zero", (double)(0));
            hashTableSend.Add("driverPower1Zero", (double)(0));
            hashTableSend.Add("driverPower2Zero", (double)(0));
            hashTableSend.Add("driverPower3Zero", (double)(0));

            hashTableSend.Add("zeroPitch", (double)(0));
            hashTableSend.Add("zeroRoll", (double)(0));
            hashTableSend.Add("zeroYaw", (double)(0));
            return true;
        }

        public bool load(string path)
        {
            FileStream fs = null;
            StreamReader sr = null;
            hashTableRecv.Clear();
            try
            {
                fs = new FileStream(path, FileMode.Open);
                sr = new StreamReader(fs, Encoding.Default);
                packSize = Convert.ToInt32(sr.ReadLine().Replace("PackSize:", ""));
                packCount = Convert.ToInt32(sr.ReadLine().Replace("PackCount:", ""));

                for (int i = 0; i < ((packSize - 4)/4) * packCount; i++)
                {
                    string temp = sr.ReadLine().Trim();
                    alPar.Add(temp);
                    if (temp != "*")
                    {
                        hashTableRecv.Add(temp, (double)(0));
                    }
                    temp = sr.ReadLine().Trim();
                    alMul.Add(temp);
                }
                sr.Close();
                fs.Close();
                return true;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("协议解析出现错误："+ex.Message+Environment.NewLine+"是否出现了相同的参数名？");
                if (sr != null)
                {
                    sr.Close();
                    sr = null;
                }
                if (fs != null)
                {
                    fs.Close();
                }
                return false;
            }
        }

        public void dealRecv(byte[] buf, int recvCount)
        {
            if (mf.dataF.isShow == true)
            {
                StringBuilder sb = new StringBuilder();
                for (int m = 0; m < recvCount; m++)
                {
                    sb.Append("0x" + Convert.ToString(buf[m], 16) + ",");
                }
                sb.Append(Environment.NewLine);
                mf.Invoke((action)delegate
                {
                    mf.dataF.lblRecvNum.Text = (Convert.ToInt32(mf.dataF.lblRecvNum.Text) + 1).ToString();
                    if (mf.dataF.txtRecv.Text.Length >= 10240)
                    {
                        mf.dataF.txtRecv.Clear();
                    }
                    mf.dataF.txtRecv.AppendText(sb.ToString());
                });
            }


            package.add(buf, recvCount);
            while (mf.isRunning)
            {
                byte[] onePack = package.get();

                if (onePack == null) 
                    return;

                int packNum = onePack[1];

                for (int i = 2; i < packSize - 2; i += 4)
                {
                    string par = (string)alPar[(i - 2) / 4 + packNum * (packSize - 4) / 4];
                    double mul = Convert.ToDouble((string)alMul[(i - 2) / 4 + packNum * (packSize - 4) / 4]);
                    if (par != "*")
                    {
                        hashTableRecv[par] =(double)( Convert.ToDouble(BitConverter.ToInt32(onePack, i)) * mul);
                    }
                }
                if (wf == null)
                {
                    wf = mf.wf;
                }
                if (wf.isPause == false)
                {
                    try
                    {

                        for (int i = 0; i < wf.cbb1.Length; i++)
                        {
                            if (wf.str1[i] != "--")
                            {
                                string s = wf.str1[i];
                                for (int j = 2; j < packSize - 2; j += 4)
                                {
                                    string par = (string)alPar[(j - 2) / 4 + packNum * (packSize - 4) / 4];
                                    if (String.Compare(par, s) == 0)
                                    {
                                        double val = (double)hashTableRecv[par];
                                        mf.Invoke((action)delegate
                                        {
                                            wf.wfgGb1.Plots[i].PlotYAppend(val);
                                            wf.lbl1[i].Text = par + ":" + val.ToString();
                                        });
                                    }
                                }
                            }
                        }

                        for (int i = 0; i < wf.cbb2.Length; i++)
                        {
                            if (wf.str2[i] != "--")
                            {
                                string s = wf.str2[i];
                                for (int j = 2; j < packSize - 2; j += 4)
                                {
                                    string par = (string)alPar[(j - 2) / 4 + packNum * (packSize - 4) / 4];
                                    if (String.Compare(par, s) == 0)
                                    {
                                        double val = (double)hashTableRecv[par];
                                        mf.Invoke((action)delegate
                                        {
                                            wf.wfgGb2.Plots[i].PlotYAppend(val);
                                            wf.lbl2[i].Text = par + ":" + val.ToString();
                                        });
                                    }
                                }
                            }
                        }
                    }
                    catch (Exception)
                    {

                    }
                }

            }
            if (wf.sw != null)
            {
                ArrayList akeys = new ArrayList(hashTableRecv.Keys);
                StringBuilder sb2 = new StringBuilder();
                foreach (string skey in akeys)
                {
                    sb2.Append(hashTableRecv[skey]);
                    sb2.Append("\t");
                }
                wf.sw.WriteLine(sb2.ToString());
            }
        }

        public byte[] dealSend()
        {
            try
            {
                mf.getSendMsg();
                ArrayList alBuf = new ArrayList();
                alBuf.Add((byte)(0x55));
                alBuf.Add((byte)(0x00));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["LeftX"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["LeftY"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["RightX"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["RightY"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["status"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutPitchKp"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutPitchKi"] * 1000)));
                byte sum = 0;
                for (int i = 0; i < 30; i++)
                {
                    sum += Convert.ToByte(alBuf[i]);
                }
                alBuf.Add((byte)(sum));
                alBuf.Add((byte)(0xFE));

                alBuf.Add((byte)(0x55));
                alBuf.Add((byte)(0x01));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutPitchKd"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InPitchKp"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InPitchKi"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InPitchKd"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutRollKp"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutRollKi"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutRollKd"] * 1000)));
                sum = 0;
                for (int i = 0; i < 30; i++)
                {
                    sum += Convert.ToByte(alBuf[i + 32]);
                }
                alBuf.Add((byte)(sum));
                alBuf.Add((byte)(0xFE));

                alBuf.Add((byte)(0x55));
                alBuf.Add((byte)(0x02));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InRollKp"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InRollKi"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InRollKd"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutYawKp"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutYawKi"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["OutYawKd"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InYawKp"] * 1000)));
                sum = 0;
                for (int i = 0; i < 30; i++)
                {
                    sum += Convert.ToByte(alBuf[i + 64]);
                }
                alBuf.Add((byte)(sum));
                alBuf.Add((byte)(0xFE));

                alBuf.Add((byte)(0x55));
                alBuf.Add((byte)(0x03));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InYawKi"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["InYawKd"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["yijieK1"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["erjieK2"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["imuKp"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["imuKi"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["filterR_angle"] * 1000)));
                sum = 0;
                for (int i = 0; i < 30; i++)
                {
                    sum += Convert.ToByte(alBuf[i + 96]);
                }
                alBuf.Add((byte)(sum));
                alBuf.Add((byte)(0xFE));

                alBuf.Add((byte)(0x55));
                alBuf.Add((byte)(0x04));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["filterQ_angle"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["filterQ_gyro"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["driverPower0Zero"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["driverPower1Zero"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["driverPower2Zero"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["driverPower3Zero"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["altKp"] * 1000)));
                sum = 0;
                for (int i = 0; i < 30; i++)
                {
                    sum += Convert.ToByte(alBuf[i + 128]);
                }
                alBuf.Add((byte)(sum));
                alBuf.Add((byte)(0xFE));

                alBuf.Add((byte)(0x55));
                alBuf.Add((byte)(0x05));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["altKi"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["altKd"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["altBase"])));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["zeroPitch"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["zeroRoll"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32((double)hashTableSend["zeroYaw"] * 1000)));
                alBuf.AddRange(BitConverter.GetBytes(Convert.ToInt32(0)));
                sum = 0;
                for (int i = 0; i < 30; i++)
                {
                    sum += Convert.ToByte(alBuf[i + 160]);
                }
                alBuf.Add((byte)(sum));
                alBuf.Add((byte)(0xFE));



                byte[] sendBuf = new byte[alBuf.Count];
                for (int i = 0; i < sendBuf.Length; i++)
                {
                    sendBuf[i] = Convert.ToByte(alBuf[i]);
                }

                if (mf.dataF.isShow == true)
                {
                    StringBuilder sb = new StringBuilder();
                    for (int i = 0; i < sendBuf.Length; i++)
                    {
                        sb.Append("0x" + Convert.ToString(sendBuf[i], 16) + ",");
                    }
                    sb.Append(Environment.NewLine);

                    mf.Invoke((action)delegate
                    {
                        mf.dataF.lblSendNum.Text = (Convert.ToInt32(mf.dataF.lblSendNum.Text) + 1).ToString();
                        if (mf.dataF.txtSend.Text.Length > 10240)
                        {
                            mf.dataF.txtSend.Clear();
                        }
                        mf.dataF.txtSend.AppendText(sb.ToString());
                    });
                }

                return sendBuf;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            return null;
        }
    }
}

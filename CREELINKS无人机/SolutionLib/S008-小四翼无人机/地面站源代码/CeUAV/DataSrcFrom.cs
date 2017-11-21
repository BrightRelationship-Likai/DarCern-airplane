using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Net;

namespace CeUAV
{
    public partial class DataSrcFrom : Form
    {
        public MainForm mf = null;
        public DataSrcFrom(MainForm mf)
        {
            InitializeComponent();
            this.mf = mf;
            txtPath.Text = AllMsg.protocolPath;
            cbbCOM.DataSource = SerialPort.GetPortNames();

            if (cbbCOM.Items.Count > 0) cbbCOM.SelectedIndex = 0;
            for (int i = 0; i < cbbCOM.Items.Count; i++)
            {
                if (cbbCOM.Items[i].ToString() == AllMsg.comPort)
                {
                    cbbCOM.SelectedIndex = i;
                    break;
                }
            }
            cbbBaudRate.SelectedIndex = 0;
            for (int i = 0; i < cbbBaudRate.Items.Count; i++)
            {
                if (AllMsg.comBaudRate == cbbBaudRate.Items[i].ToString())
                {
                    cbbBaudRate.SelectedIndex = i;
                    break;
                }
            }

            string hostName = Dns.GetHostName();//本机名   
            System.Net.IPAddress[] addressList = Dns.GetHostByName(hostName).AddressList;//会警告GetHostByName()已过期，   //我运行时且只返回了一个IPv4的地址   
            //System.Net.IPAddress[] addressList = Dns.GetHostAddresses(hostName);//会返回所有地址，包括IPv4和IPv6   
            foreach (IPAddress ip in addressList)
            {
               cbbIP.Items.Add(ip.ToString());
            }
            if (cbbIP.Items.Count > 0) cbbIP.SelectedIndex = 0;
            for (int i = 0; i < cbbIP.Items.Count; i++)
            {
                if (AllMsg.tcpIP == cbbIP.Items[i].ToString())
                {
                    cbbIP.SelectedIndex = i;
                    break;
                }
            }
            txtPort.Text = AllMsg.tcpPort;
        }

        private void btnTCP_Click(object sender, EventArgs e)
        {
            double result = 0;
            if (Double.TryParse(txtPort.Text,out result) == false)
            {
                MessageBox.Show("端口号不正确！");
                return;
            }

            if (cbbIP.Items.Count == 0)
            {
                MessageBox.Show("无可用IP！");
                return;
            }
            AllMsg.isTCP = true;
            AllMsg.tcpIP = cbbIP.SelectedItem.ToString();
            AllMsg.tcpPort = txtPort.Text;
            AllMsg.Save();
            this.Close();
        }

        private void btnCOM_Click(object sender, EventArgs e)
        {
            if (cbbCOM.Items.Count == 0)
            {
                MessageBox.Show("无可用端口！");
                return;
            }
            AllMsg.isCom = true;
            AllMsg.comPort = cbbCOM.SelectedItem.ToString();
            AllMsg.comBaudRate = cbbBaudRate.SelectedItem.ToString();
            AllMsg.Save();
            this.Close();
        }

        private void btnPath_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "*.cfg|*.cfg";
            ofd.InitialDirectory = Application.StartupPath;
            if (ofd.ShowDialog() != System.Windows.Forms.DialogResult.OK)
            {
                return;
            }
            string filePath = ofd.FileName;
            if (mf.ptl.load(filePath) == true)
            {
                AllMsg.protocolPath = filePath;
                this.txtPath.Text  = filePath;
                AllMsg.Save();
                MessageBox.Show("协议解析成功！");
            }
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
    }
}

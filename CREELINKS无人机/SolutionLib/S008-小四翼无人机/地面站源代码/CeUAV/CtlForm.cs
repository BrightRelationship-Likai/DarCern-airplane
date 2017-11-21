using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
namespace CeUAV
{
    public partial class CtlForm : Form
    {
        MainForm mf = null;
        public Bitmap bitmapBack = new Bitmap(300, 300);
        public Bitmap bitmapFore= null;

        public Bitmap bitmapLeft = new Bitmap(126, 126);
        public Bitmap bitmapRight = new Bitmap(126, 126);
        public CtlForm(MainForm mf)
        {
            InitializeComponent();
            this.mf = mf;
            if (!File.Exists(Application.StartupPath + "\\uav_fore300.png"))
            {
                MessageBox.Show("文件丢失：" + Application.StartupPath + "\\uav_fore300.png");
                bitmapFore = new Bitmap(300, 300);
            }
            else
            {
                bitmapFore = new Bitmap(Application.StartupPath + "\\uav_fore300.png");
            }
            initialCtl();
        }

        private void CtlForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        public void initialCtl()
        {
            Graphics g = Graphics.FromImage(bitmapLeft);
            SolidBrush sb = new SolidBrush(Color.DarkGray);
            g.Clear(Color.Transparent);
            g.FillEllipse(sb, 0, 0, 126, 126);
            sb = new SolidBrush(Color.Aqua);
            g.FillEllipse(sb, 63 - 8, 63 - 8, 16, 16);
            pbLeft.Image = bitmapLeft;

            g = Graphics.FromImage(bitmapRight);
            sb = new SolidBrush(Color.DarkGray);
            g.Clear(Color.Transparent);
            g.FillEllipse(sb, 0, 0, 126, 126);
            sb = new SolidBrush(Color.Aqua);
            g.FillEllipse(sb, 63 - 8, 63 - 8, 16, 16);
            pbRight.Image = bitmapLeft;

            lblRx.Text = "rx:0";
            lblRy.Text = "ry:0";
            lblLx.Text = "lx:0";
            lblLy.Text = "ly:0";

            mf.ptl.hashTableSend["LeftX"] = (double)0;
            mf.ptl.hashTableSend["LeftY"] = (double)0;
            mf.ptl.hashTableSend["RightX"] = (double)0;
            mf.ptl.hashTableSend["RightY"] = (double)0;
        }


        bool isBtnLeftPressing = false;

        private void pbLeft_MouseDown(object sender, MouseEventArgs e)
        {
            isBtnLeftPressing = true;
            Graphics g = Graphics.FromImage(bitmapLeft);
            SolidBrush sb = new SolidBrush(Color.DarkGray);
            g.Clear(Color.Transparent);

            g.FillEllipse(sb, 0, 0, 126, 126);

            sb = new SolidBrush(Color.Aqua);
            g.FillEllipse(sb, e.X - 8, e.Y - 8, 16, 16);
            pbLeft.Image = bitmapLeft;

            mf.ptl.hashTableSend["LeftX"] = (double)((e.X - 63) * 1000 / 63);
            mf.ptl.hashTableSend["LeftY"] = (double)(((126 - e.Y) - 63) * 1000 / 63);

            lblLx.Text = "lx:" + ((double)((e.X - 63) * 1000 / 63)).ToString();
            lblLy.Text = "ly:" + ((double)(((126 - e.Y) - 63) * 1000 / 63)).ToString();
        }

        private void pbLeft_MouseMove(object sender, MouseEventArgs e)
        {
            if (isBtnLeftPressing == true && e.X < 126 && e.X > 0 && e.Y < 126 && e.Y > 0)
            {
                Graphics g = Graphics.FromImage(bitmapLeft);
                SolidBrush sb = new SolidBrush(Color.DarkGray);
                g.Clear(Color.Transparent);

                g.FillEllipse(sb, 0, 0, 126, 126);

                sb = new SolidBrush(Color.Aqua);
                g.FillEllipse(sb, e.X - 8, e.Y - 8, 16, 16);
                pbLeft.Image = bitmapLeft;

                mf.ptl.hashTableSend["LeftX"] = (double)((e.X - 63) * 1000 / 63);
                mf.ptl.hashTableSend["LeftY"] = (double)(((126 - e.Y) - 63) * 1000 / 63);

                lblLx.Text = "lx:" + ((double)((e.X - 63) * 1000 / 63)).ToString();
                lblLy.Text = "ly:" + ((double)(((126 - e.Y) - 63) * 1000 / 63)).ToString();
            }

        }

        private void pbLeft_MouseUp(object sender, MouseEventArgs e)
        {
            isBtnLeftPressing = false;
        }

        bool isBtnRightPressing = false;
        private void pbRight_MouseDown(object sender, MouseEventArgs e)
        {
            isBtnRightPressing = true;
            Graphics g = Graphics.FromImage(bitmapRight);
            SolidBrush sb = new SolidBrush(Color.DarkGray);
            g.Clear(Color.Transparent);

            g.FillEllipse(sb, 0, 0, 126, 126);

            sb = new SolidBrush(Color.Aqua);
            g.FillEllipse(sb, e.X - 8, e.Y - 8, 16, 16);
            pbRight.Image = bitmapRight;

            mf.ptl.hashTableSend["RightX"] = (double)((e.X - 63) * 1000 / 63);
            mf.ptl.hashTableSend["RightY"] = (double)(((126 - e.Y) - 63) * 1000 / 63);

            lblRx.Text = "rx:" + ((double)((e.X - 63) * 1000 / 63)).ToString();
            lblRy.Text = "ry:" + ((double)(((126 - e.Y) - 63) * 1000 / 63)).ToString();
        }

        private void pbRight_MouseMove(object sender, MouseEventArgs e)
        {
            if (isBtnRightPressing == true && e.X < 126 && e.X > 0 && e.Y < 126 && e.Y > 0)
            {
                Graphics g = Graphics.FromImage(bitmapRight);
                SolidBrush sb = new SolidBrush(Color.DarkGray);
                g.Clear(Color.Transparent);

                g.FillEllipse(sb, 0, 0, 126, 126);

                sb = new SolidBrush(Color.Aqua);
                g.FillEllipse(sb, e.X - 8, e.Y - 8, 16, 16);
                pbRight.Image = bitmapRight;

                mf.ptl.hashTableSend["RightX"] = (double)((e.X - 63) * 1000 / 63);
                mf.ptl.hashTableSend["RightY"] = (double)(((126 - e.Y) - 63) * 1000 / 63);

                lblRx.Text = "rx:" + ((double)((e.X - 63) * 1000 / 63)).ToString();
                lblRy.Text = "ry:" + ((double)(((126 - e.Y) - 63) * 1000 / 63)).ToString();
            }
        }

        private void pbRight_MouseUp(object sender, MouseEventArgs e)
        {
            isBtnRightPressing = false;
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            initialCtl();
        }

        private void btnLeft_CheckedChanged(object sender, EventArgs e)
        {

            mf.ptl.hashTableSend["BtnL"] = Convert.ToDouble(((CheckBox)(sender)).Checked);

        }

        private void cbS2A_CheckedChanged(object sender, EventArgs e)
        {
            mf.ptl.hashTableSend["S2A"] = Convert.ToDouble(((CheckBox)(sender)).Checked);

        }

        private void cbS2B_CheckedChanged(object sender, EventArgs e)
        {
            mf.ptl.hashTableSend["S2B"] = Convert.ToDouble(((CheckBox)(sender)).Checked);

        }

        private void btnRight_CheckedChanged(object sender, EventArgs e)
        {
            mf.ptl.hashTableSend["BtnR"] = Convert.ToDouble(((CheckBox)(sender)).Checked);
        }

        private void cbS2C_CheckedChanged(object sender, EventArgs e)
        {
            mf.ptl.hashTableSend["S2C"] = Convert.ToDouble(((CheckBox)(sender)).Checked);
        }

        private void cbS2D_CheckedChanged(object sender, EventArgs e)
        {
            mf.ptl.hashTableSend["S2D"] = Convert.ToDouble(((CheckBox)(sender)).Checked);
        }

        private void CtlForm_Load(object sender, EventArgs e)
        {

        }

    }




}

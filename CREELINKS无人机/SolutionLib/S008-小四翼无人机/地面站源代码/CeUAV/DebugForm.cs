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
    public partial class DebugForm : Form
    {
        MainForm mf = null;

        public double pitchOutKp = 0;
        public double pitchOutKi = 0;
        public double pitchOutKd = 0;
        public double pitchInKp = 0;
        public double pitchInKi = 0;
        public double pitchInKd = 0;

        public double rollOutKp = 0;
        public double rollOutKi = 0;
        public double rollOutKd = 0;
        public double rollInKp = 0;
        public double rollInKi = 0;
        public double rollInKd = 0;        

        public double yawOutKp = 0;
        public double yawOutKi = 0;
        public double yawOutKd = 0;
        public double yawInKp = 0;
        public double yawInKi = 0;
        public double yawInKd = 0;

        public double yijieK1 = 0;
        public double erjieK2 = 0;
        public double imuKp = 0;
        public double imuKi = 0;
        public double kalmanRangle = 0;
        public double kalmanQangle = 0;
        public double kalmanQgyro = 0;

        public double altKp = 0;
        public double altKi = 0;
        public double altKd = 0;
        public double altBase = 0;

        public double zeroPitch = 0;
        public double zeroRoll = 0;
        public double zeroYaw = 0;

        public DebugForm(MainForm mf)
        {
            InitializeComponent();
            this.mf = mf;
        }

        private void rbYijihubo_CheckedChanged(object sender, EventArgs e)
        {
            gbyijie.Enabled = true;
            gberjie.Enabled = false;
            gbfour.Enabled = false;
            gbkalman.Enabled = false;
        }

        private void rbErjiehubo_CheckedChanged(object sender, EventArgs e)
        {
            gbyijie.Enabled = false;
            gberjie.Enabled = true;
            gbfour.Enabled = false;
            gbkalman.Enabled = false;
        }

        private void rbFour_CheckedChanged(object sender, EventArgs e)
        {
            gbyijie.Enabled = false;
            gberjie.Enabled = false;
            gbfour.Enabled = true;
            gbkalman.Enabled = false;
        }

        private void rbKalman_CheckedChanged(object sender, EventArgs e)
        {
            gbyijie.Enabled = false;
            gberjie.Enabled = false;
            gbfour.Enabled = false;
            gbkalman.Enabled = true;
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "*.cct|*.cct";

            ofd.InitialDirectory = Application.StartupPath + "\\ParmentDebug";
            if (Directory.Exists(Application.StartupPath + "\\ParmentDebug") == false)
            {
                Directory.CreateDirectory(Application.StartupPath + "\\ParmentDebug");
            }
            if (DialogResult.OK != ofd.ShowDialog())
                return;

            FileStream fs = new FileStream(ofd.FileName, FileMode.Open);
            BinaryReader br = new BinaryReader(fs, Encoding.Default);
            nudXOutKp.Value = new decimal(br.ReadDouble());
            nudXOutKi.Value = new decimal(br.ReadDouble());
            nudXOutKd.Value = new decimal(br.ReadDouble());
            nudXInKp.Value = new decimal(br.ReadDouble());
            nudXInKi.Value = new decimal(br.ReadDouble());
            nudXInKd.Value = new decimal(br.ReadDouble());
            nudYOutKp.Value = new decimal(br.ReadDouble());
            nudYOutKi.Value = new decimal(br.ReadDouble());
            nudYOutKd.Value = new decimal(br.ReadDouble());
            nudYInKp.Value = new decimal(br.ReadDouble());
            nudYInKi.Value = new decimal(br.ReadDouble());
            nudYInKd.Value = new decimal(br.ReadDouble());
            nudYawKp.Value = new decimal(br.ReadDouble());
            nudYawKi.Value = new decimal(br.ReadDouble());
            nudYawKd.Value = new decimal(br.ReadDouble());
            nudInYawKp.Value = new decimal(br.ReadDouble());
            nudInYawKi.Value = new decimal(br.ReadDouble());
            nudInYawKd.Value = new decimal(br.ReadDouble());
            nudYijie.Value = new decimal(br.ReadDouble());
            nudErjie.Value = new decimal(br.ReadDouble());
            nudImuKp.Value = new decimal(br.ReadDouble());
            nudImuKi.Value = new decimal(br.ReadDouble());
            nudKalmanRangle.Value = new decimal(br.ReadDouble());
            nudKalmanQangle.Value = new decimal(br.ReadDouble());
            nudKalmanQgyro.Value = new decimal(br.ReadDouble());

            nudAltKp.Value = new decimal(br.ReadDouble());
            nudAltKi.Value = new decimal(br.ReadDouble());
            nudAltKd.Value = new decimal(br.ReadDouble());
            nudAltBase.Value = new decimal(br.ReadDouble());

            br.Close();
            fs.Close();
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "*.cct|*.cct";
            sfd.InitialDirectory = Application.StartupPath+"\\ParmentDebug";
            if (Directory.Exists(Application.StartupPath + "\\ParmentDebug") == false)
            {
                Directory.CreateDirectory(Application.StartupPath + "\\ParmentDebug");
            }
            if (DialogResult.OK != sfd.ShowDialog())
            {
                return;
            }
            FileStream fs = new FileStream(sfd.FileName, FileMode.Create);
            BinaryWriter bw = new BinaryWriter(fs, Encoding.Default);
            bw.Write(Convert.ToDouble(nudXOutKp.Value));
            bw.Write(Convert.ToDouble(nudXOutKi.Value));
            bw.Write(Convert.ToDouble(nudXOutKd.Value));

            bw.Write(Convert.ToDouble(nudXInKp.Value));
            bw.Write(Convert.ToDouble(nudXInKi.Value));
            bw.Write(Convert.ToDouble(nudXInKd.Value));

            bw.Write(Convert.ToDouble(nudYOutKp.Value));
            bw.Write(Convert.ToDouble(nudYOutKi.Value));
            bw.Write(Convert.ToDouble(nudYOutKd.Value));

            bw.Write(Convert.ToDouble(nudYInKp.Value));
            bw.Write(Convert.ToDouble(nudYInKi.Value));
            bw.Write(Convert.ToDouble(nudYInKd.Value));

            bw.Write(Convert.ToDouble(nudYawKp.Value));
            bw.Write(Convert.ToDouble(nudYawKi.Value));
            bw.Write(Convert.ToDouble(nudYawKd.Value));

            bw.Write(Convert.ToDouble(nudInYawKp.Value));
            bw.Write(Convert.ToDouble(nudInYawKi.Value));
            bw.Write(Convert.ToDouble(nudInYawKd.Value));

            bw.Write(Convert.ToDouble(nudYijie.Value));
            bw.Write(Convert.ToDouble(nudErjie.Value));

            bw.Write(Convert.ToDouble(nudImuKp.Value));
            bw.Write(Convert.ToDouble(nudImuKi.Value));

            bw.Write(Convert.ToDouble(nudKalmanRangle.Value));
            bw.Write(Convert.ToDouble(nudKalmanQangle.Value));
            bw.Write(Convert.ToDouble(nudKalmanQgyro.Value));

            bw.Write(Convert.ToDouble(nudAltKp.Value));
            bw.Write(Convert.ToDouble(nudAltKi.Value));
            bw.Write(Convert.ToDouble(nudAltKd.Value));
            bw.Write(Convert.ToDouble(nudAltBase.Value));

            bw.Close();
            fs.Close();
            MessageBox.Show("Save Finish!");
        }

        private void DebugForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void nudXOutKp_ValueChanged(object sender, EventArgs e)
        {
            pitchOutKp = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudXOutKi_ValueChanged(object sender, EventArgs e)
        {
            pitchOutKi = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudXOutKd_ValueChanged(object sender, EventArgs e)
        {
            pitchOutKd = Convert.ToDouble(((NumericUpDown)sender).Value); 
        }

        private void nudXInKp_ValueChanged(object sender, EventArgs e)
        {
            pitchInKp = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudXInKi_ValueChanged(object sender, EventArgs e)
        {
            pitchInKi = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudXInKd_ValueChanged(object sender, EventArgs e)
        {
            pitchInKd = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYOutKp_ValueChanged(object sender, EventArgs e)
        {
            rollOutKp = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYOutKi_ValueChanged(object sender, EventArgs e)
        {
            rollOutKi = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYOutKd_ValueChanged(object sender, EventArgs e)
        {
            rollOutKd = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYInKp_ValueChanged(object sender, EventArgs e)
        {
            rollInKp = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYInKi_ValueChanged(object sender, EventArgs e)
        {
            rollInKi = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYInKd_ValueChanged(object sender, EventArgs e)
        {
            rollInKd = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYawKp_ValueChanged(object sender, EventArgs e)
        {
            yawOutKp = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYawKi_ValueChanged(object sender, EventArgs e)
        {
            yawOutKi = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYawKd_ValueChanged(object sender, EventArgs e)
        {
            yawOutKd = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudInYawKp_ValueChanged(object sender, EventArgs e)
        {
            yawInKp = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudInYawKi_ValueChanged(object sender, EventArgs e)
        {
            yawInKi = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudInYawKd_ValueChanged(object sender, EventArgs e)
        {
            yawInKd = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudYijie_ValueChanged(object sender, EventArgs e)
        {
            yijieK1 = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudErjie_ValueChanged(object sender, EventArgs e)
        {
            erjieK2 = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudImuKp_ValueChanged(object sender, EventArgs e)
        {
            imuKp = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudImuKi_ValueChanged(object sender, EventArgs e)
        {
            imuKi = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudKalmanRangle_ValueChanged(object sender, EventArgs e)
        {
            kalmanRangle = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudKalmanQangle_ValueChanged(object sender, EventArgs e)
        {
            kalmanQangle = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudKalmanQgyro_ValueChanged(object sender, EventArgs e)
        {
            kalmanQgyro = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudAltKp_ValueChanged(object sender, EventArgs e)
        {
            altKp = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudAltKi_ValueChanged(object sender, EventArgs e)
        {
            altKi = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudAlkKd_ValueChanged(object sender, EventArgs e)
        {
            altKd = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudAltBase_ValueChanged(object sender, EventArgs e)
        {
            altBase = Convert.ToDouble(((NumericUpDown)sender).Value);
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

        private void nudZeroPitch_ValueChanged(object sender, EventArgs e)
        {
            zeroPitch = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudZeroRoll_ValueChanged(object sender, EventArgs e)
        {
            zeroRoll = Convert.ToDouble(((NumericUpDown)sender).Value);
        }

        private void nudZeroYaw_ValueChanged(object sender, EventArgs e)
        {
            zeroYaw = Convert.ToDouble(((NumericUpDown)sender).Value);
        }
    }
}

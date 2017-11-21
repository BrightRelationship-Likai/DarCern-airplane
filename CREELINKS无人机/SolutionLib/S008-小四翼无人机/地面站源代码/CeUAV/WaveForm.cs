using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Collections;

namespace CeUAV
{
    public partial class WaveForm : Form
    {
        public ComboBox[] cbb1 = null;
        public ComboBox[] cbb2 = null;
        public Label[] lbl1 = null;
        public Label[] lbl2 = null;
        MainForm mf = null;

        public string[] str1 = new string[] { "--", "--", "--", "--", "--", "--", "--", "--" };
        public string[] str2 = new string[] { "--", "--", "--", "--", "--", "--", "--", "--" };
        public bool isPause = false;
        public WaveForm(MainForm mf)
        {
            InitializeComponent();
            this.mf = mf;
            cbb1 = new ComboBox[] { cbb11, cbb12, cbb13, cbb14, cbb15, cbb16, cbb17, cbb18 };
            cbb2 = new ComboBox[] { cbb21, cbb22, cbb23, cbb24, cbb25, cbb26, cbb27, cbb28 };

            lbl1 = new Label[] { lbl11, lbl12, lbl13, lbl14, lbl15, lbl16, lbl17, lbl18 };
            lbl2 = new Label[] { lbl21, lbl22, lbl23, lbl24, lbl25, lbl26, lbl27, lbl28 };



            ArrayList akeys = new ArrayList(mf.ptl.hashTableRecv.Keys);
            for (int i = 0; i < 8; i++)
            {
                cbb1[i].Items.Add("--");
                cbb2[i].Items.Add("--");
            }

            foreach (string skey in akeys)
            {
                mf.cbbl.Items.Add(skey);
                mf.cbbr.Items.Add(skey);

                for (int i = 0; i < 8; i++)
                {
                    cbb1[i].Items.Add(skey);
                    cbb2[i].Items.Add(skey);
                }
            }

            for (int i = 0; i < 8; i++)
            {
                cbb1[i].SelectedIndex = 0;
                cbb2[i].SelectedIndex = 0;
            }
            mf.cbbl.SelectedIndex = 0;
            mf.cbbr.SelectedIndex = 0;
        }

        private void btnReset1_Click(object sender, EventArgs e)
        {
            wfgGb1.ClearData();
        }

        private void btnReset2_Click(object sender, EventArgs e)
        {
            wfgGb2.ClearData();
        }

        private void cbb11_SelectedIndexChanged(object sender, EventArgs e)
        {
            wfgGb1.ClearData();
            ComboBox cbb = (ComboBox)sender;
            int index = Convert.ToInt32(cbb.Name.Replace("cbb1",""))-1;
            str1[index] = cbb.SelectedItem.ToString();
        }

        private void cbb21_SelectedIndexChanged(object sender, EventArgs e)
        {
            wfgGb2.ClearData();
            ComboBox cbb = (ComboBox)sender;
            int index = Convert.ToInt32(cbb.Name.Replace("cbb2", "")) - 1;
            str2[index] = cbb.SelectedItem.ToString();
        }

        public FileStream fs = null;
        public  StreamWriter sw = null;

        private void btnSaveFile_Click(object sender, EventArgs e)
        {
            if (btnSaveFile.Text == "开始保存")
            {
                btnSaveFile.Text = "停止保存";
                string path = Application.StartupPath + "\\" + DateTime.Now.ToString("yyyy-MM-dd_hh-mm-ss") + ".txt";
                fs = new FileStream(path, FileMode.Create);
                sw = new StreamWriter(fs, Encoding.Default);

                ArrayList akeys = new ArrayList(mf.ptl.hashTableRecv.Keys);
                StringBuilder sb2 = new StringBuilder();
                foreach (string skey in akeys)
                {
                    sb2.Append(skey);
                    sb2.Append("\t");
                }
                sw.WriteLine(sb2.ToString());
            }
            else
            {
                btnSaveFile.Text = "开始保存";
                sw.Close();
                sw = null;
                fs.Close();
                fs = null;
            }
        }

        private void WaveForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void WaveForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (sw != null)
            {
                sw.Close();
                sw = null;
                if (fs != null)
                {
                    fs.Close();
                    fs = null;
                }
            }
        }

        private void btnClear12_Click(object sender, EventArgs e)
        {
            wfgGb1.ClearData();
            wfgGb2.ClearData();
        }

        private void nudRange_ValueChanged(object sender, EventArgs e)
        {
            wfgGb1.XAxes[0].Range = new NationalInstruments.UI.Range(0, Convert.ToInt32(nudRange.Value));
            wfgGb2.XAxes[0].Range = new NationalInstruments.UI.Range(0, Convert.ToInt32(nudRange.Value));
        }

        private void btnPause_Click(object sender, EventArgs e)
        {
            if (btnPause.Text == "暂停")
            {
                btnPause.Text = "开始";
                isPause = true;
                xyCursor1.Visible = true;
                xyCursor2.Visible = true;
            }
            else
            {
                btnPause.Text = "暂停";
                isPause = false;
                xyCursor1.Visible = false;
                xyCursor2.Visible = false;
            }
        }

        private void label2_Click(object sender, EventArgs e)
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
    }
}

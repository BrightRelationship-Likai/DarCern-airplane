using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CeUAV
{
    public partial class DataForm : Form
    {
        MainForm mf = null;
        public bool isShow = false;
        public DataForm(MainForm mf)
        {
            InitializeComponent();
            this.mf = mf;
        }

        private void DataForm_Load(object sender, EventArgs e)
        {

        }

        private void DataForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            isShow = false;
            this.Hide();
            e.Cancel = true;
        }

        private void DataForm_Shown(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {
            isShow = true;
        }

        private void DataForm_Leave(object sender, EventArgs e)
        {
            isShow = false;
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

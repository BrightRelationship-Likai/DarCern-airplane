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
    public partial class DriverPowerForm : Form
    {
        MainForm mf = null;
        public int d0 = 0;
        public int d1 = 0;
        public int d2 = 0;
        public int d3 = 0;
        public DriverPowerForm(MainForm mf)
        {
            InitializeComponent();
            this.mf = mf;
        }

        private void DriverPowerForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void nudMD0_ValueChanged(object sender, EventArgs e)
        {
            d0 = Convert.ToInt32(nudMD0.Value);
        }

        private void nudMD1_ValueChanged(object sender, EventArgs e)
        {
            d1 = Convert.ToInt32(nudMD1.Value);
        }

        private void nudMD2_ValueChanged(object sender, EventArgs e)
        {
            d2 = Convert.ToInt32(nudMD2.Value);
        }

        private void nudMD3_ValueChanged(object sender, EventArgs e)
        {
            d3 = Convert.ToInt32(nudMD3.Value);
        }

    }
}

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
    public partial class NewTMUForm : Form
    {
        public int packSize = -1;
        public NewTMUForm()
        {
            InitializeComponent();
        }

        private void btnSure_Click(object sender, EventArgs e)
        {
            packSize = Convert.ToInt32(nudPackSize.Value);
            if (packSize % 4 != 0)
            {
                MessageBox.Show("长度应为4的倍数");
                packSize = -1;
                return;
            }
            this.Close();
        }
    }
}

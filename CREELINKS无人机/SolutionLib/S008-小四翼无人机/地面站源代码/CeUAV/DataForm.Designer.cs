namespace CeUAV
{
    partial class DataForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DataForm));
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txtSend = new System.Windows.Forms.TextBox();
            this.lblSendNum = new System.Windows.Forms.Label();
            this.lblSend = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtRecv = new System.Windows.Forms.TextBox();
            this.lblRecvNum = new System.Windows.Forms.Label();
            this.lblRecv = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.BackColor = System.Drawing.Color.Black;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.ForeColor = System.Drawing.Color.Aqua;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.groupBox1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.groupBox2);
            this.splitContainer1.Size = new System.Drawing.Size(1147, 472);
            this.splitContainer1.SplitterDistance = 231;
            this.splitContainer1.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Black;
            this.groupBox1.Controls.Add(this.panel1);
            this.groupBox1.Controls.Add(this.lblSendNum);
            this.groupBox1.Controls.Add(this.lblSend);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.ForeColor = System.Drawing.Color.Aqua;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1147, 231);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "发送";
            this.groupBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // txtSend
            // 
            this.txtSend.AcceptsReturn = true;
            this.txtSend.AcceptsTab = true;
            this.txtSend.BackColor = System.Drawing.Color.Black;
            this.txtSend.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txtSend.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtSend.ForeColor = System.Drawing.Color.Aqua;
            this.txtSend.Location = new System.Drawing.Point(1, 1);
            this.txtSend.Multiline = true;
            this.txtSend.Name = "txtSend";
            this.txtSend.ReadOnly = true;
            this.txtSend.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtSend.Size = new System.Drawing.Size(1139, 209);
            this.txtSend.TabIndex = 2;
            // 
            // lblSendNum
            // 
            this.lblSendNum.AutoSize = true;
            this.lblSendNum.BackColor = System.Drawing.Color.Black;
            this.lblSendNum.ForeColor = System.Drawing.Color.Aqua;
            this.lblSendNum.Location = new System.Drawing.Point(66, 18);
            this.lblSendNum.Name = "lblSendNum";
            this.lblSendNum.Size = new System.Drawing.Size(11, 12);
            this.lblSendNum.TabIndex = 1;
            this.lblSendNum.Text = "0";
            // 
            // lblSend
            // 
            this.lblSend.AutoSize = true;
            this.lblSend.BackColor = System.Drawing.Color.Black;
            this.lblSend.ForeColor = System.Drawing.Color.Aqua;
            this.lblSend.Location = new System.Drawing.Point(6, 17);
            this.lblSend.Name = "lblSend";
            this.lblSend.Size = new System.Drawing.Size(65, 12);
            this.lblSend.TabIndex = 0;
            this.lblSend.Text = "累计包数：";
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Black;
            this.groupBox2.Controls.Add(this.panel2);
            this.groupBox2.Controls.Add(this.lblRecvNum);
            this.groupBox2.Controls.Add(this.lblRecv);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.ForeColor = System.Drawing.Color.Aqua;
            this.groupBox2.Location = new System.Drawing.Point(0, 0);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(1147, 237);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "接收";
            this.groupBox2.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            // 
            // txtRecv
            // 
            this.txtRecv.AcceptsReturn = true;
            this.txtRecv.AcceptsTab = true;
            this.txtRecv.BackColor = System.Drawing.Color.Black;
            this.txtRecv.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txtRecv.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtRecv.ForeColor = System.Drawing.Color.Aqua;
            this.txtRecv.Location = new System.Drawing.Point(1, 1);
            this.txtRecv.Multiline = true;
            this.txtRecv.Name = "txtRecv";
            this.txtRecv.ReadOnly = true;
            this.txtRecv.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtRecv.Size = new System.Drawing.Size(1139, 215);
            this.txtRecv.TabIndex = 3;
            // 
            // lblRecvNum
            // 
            this.lblRecvNum.AutoSize = true;
            this.lblRecvNum.BackColor = System.Drawing.Color.Black;
            this.lblRecvNum.ForeColor = System.Drawing.Color.Aqua;
            this.lblRecvNum.Location = new System.Drawing.Point(66, 18);
            this.lblRecvNum.Name = "lblRecvNum";
            this.lblRecvNum.Size = new System.Drawing.Size(11, 12);
            this.lblRecvNum.TabIndex = 1;
            this.lblRecvNum.Text = "0";
            // 
            // lblRecv
            // 
            this.lblRecv.AutoSize = true;
            this.lblRecv.BackColor = System.Drawing.Color.Black;
            this.lblRecv.ForeColor = System.Drawing.Color.Aqua;
            this.lblRecv.Location = new System.Drawing.Point(6, 17);
            this.lblRecv.Name = "lblRecv";
            this.lblRecv.Size = new System.Drawing.Size(65, 12);
            this.lblRecv.TabIndex = 0;
            this.lblRecv.Text = "累计包数：";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Cyan;
            this.panel1.Controls.Add(this.txtSend);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 17);
            this.panel1.Name = "panel1";
            this.panel1.Padding = new System.Windows.Forms.Padding(1);
            this.panel1.Size = new System.Drawing.Size(1141, 211);
            this.panel1.TabIndex = 3;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.Cyan;
            this.panel2.Controls.Add(this.txtRecv);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(3, 17);
            this.panel2.Name = "panel2";
            this.panel2.Padding = new System.Windows.Forms.Padding(1);
            this.panel2.Size = new System.Drawing.Size(1141, 217);
            this.panel2.TabIndex = 4;
            // 
            // DataForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1147, 472);
            this.Controls.Add(this.splitContainer1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "DataForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "DataForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.DataForm_FormClosing);
            this.Load += new System.EventHandler(this.DataForm_Load);
            this.Shown += new System.EventHandler(this.DataForm_Shown);
            this.Leave += new System.EventHandler(this.DataForm_Leave);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.GroupBox groupBox1;
        public System.Windows.Forms.TextBox txtSend;
        public System.Windows.Forms.Label lblSendNum;
        public System.Windows.Forms.Label lblSend;
        public System.Windows.Forms.GroupBox groupBox2;
        public System.Windows.Forms.TextBox txtRecv;
        public System.Windows.Forms.Label lblRecvNum;
        public System.Windows.Forms.Label lblRecv;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
    }
}
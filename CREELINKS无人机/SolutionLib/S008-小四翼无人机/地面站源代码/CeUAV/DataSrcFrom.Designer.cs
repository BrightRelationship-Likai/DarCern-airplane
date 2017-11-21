namespace CeUAV
{
    partial class DataSrcFrom
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DataSrcFrom));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.btnTCP = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.cbbIP = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnCOM = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.cbbBaudRate = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cbbCOM = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.txtPath = new System.Windows.Forms.TextBox();
            this.btnPath = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Black;
            this.groupBox1.Controls.Add(this.panel1);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.btnTCP);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.cbbIP);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.ForeColor = System.Drawing.Color.Aqua;
            this.groupBox1.Location = new System.Drawing.Point(11, 46);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(206, 123);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "网口";
            this.groupBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.Control;
            this.panel1.Controls.Add(this.txtPort);
            this.panel1.Location = new System.Drawing.Point(79, 50);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(120, 22);
            this.panel1.TabIndex = 8;
            // 
            // txtPort
            // 
            this.txtPort.BackColor = System.Drawing.Color.Black;
            this.txtPort.ForeColor = System.Drawing.Color.Aqua;
            this.txtPort.Location = new System.Drawing.Point(-1, -1);
            this.txtPort.Margin = new System.Windows.Forms.Padding(0);
            this.txtPort.Multiline = true;
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(122, 24);
            this.txtPort.TabIndex = 3;
            this.txtPort.Text = "2121";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.Black;
            this.label6.ForeColor = System.Drawing.Color.Aqua;
            this.label6.Location = new System.Drawing.Point(6, 79);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(149, 12);
            this.label6.TabIndex = 8;
            this.label6.Text = "默认：服务器模式/TCP方式";
            // 
            // btnTCP
            // 
            this.btnTCP.BackColor = System.Drawing.Color.Black;
            this.btnTCP.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnTCP.ForeColor = System.Drawing.Color.Aqua;
            this.btnTCP.Location = new System.Drawing.Point(63, 94);
            this.btnTCP.Name = "btnTCP";
            this.btnTCP.Size = new System.Drawing.Size(75, 23);
            this.btnTCP.TabIndex = 4;
            this.btnTCP.Text = "启动";
            this.btnTCP.UseVisualStyleBackColor = false;
            this.btnTCP.Click += new System.EventHandler(this.btnTCP_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Black;
            this.label2.ForeColor = System.Drawing.Color.Aqua;
            this.label2.Location = new System.Drawing.Point(6, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(77, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "服务器端口：";
            // 
            // cbbIP
            // 
            this.cbbIP.BackColor = System.Drawing.Color.Black;
            this.cbbIP.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cbbIP.ForeColor = System.Drawing.Color.Aqua;
            this.cbbIP.FormattingEnabled = true;
            this.cbbIP.Location = new System.Drawing.Point(80, 25);
            this.cbbIP.Name = "cbbIP";
            this.cbbIP.Size = new System.Drawing.Size(119, 20);
            this.cbbIP.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Black;
            this.label1.ForeColor = System.Drawing.Color.Aqua;
            this.label1.Location = new System.Drawing.Point(18, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "服务器IP：";
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Black;
            this.groupBox2.Controls.Add(this.btnCOM);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.cbbBaudRate);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.cbbCOM);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.ForeColor = System.Drawing.Color.Aqua;
            this.groupBox2.Location = new System.Drawing.Point(223, 46);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(206, 123);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "串口";
            this.groupBox2.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            // 
            // btnCOM
            // 
            this.btnCOM.BackColor = System.Drawing.Color.Black;
            this.btnCOM.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnCOM.ForeColor = System.Drawing.Color.Aqua;
            this.btnCOM.Location = new System.Drawing.Point(67, 94);
            this.btnCOM.Name = "btnCOM";
            this.btnCOM.Size = new System.Drawing.Size(75, 23);
            this.btnCOM.TabIndex = 7;
            this.btnCOM.Text = "启动";
            this.btnCOM.UseVisualStyleBackColor = false;
            this.btnCOM.Click += new System.EventHandler(this.btnCOM_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.Black;
            this.label5.ForeColor = System.Drawing.Color.Aqua;
            this.label5.Location = new System.Drawing.Point(3, 78);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(197, 12);
            this.label5.TabIndex = 6;
            this.label5.Text = "默认：无校验/1bit停止位/长度8bit";
            // 
            // cbbBaudRate
            // 
            this.cbbBaudRate.BackColor = System.Drawing.Color.Black;
            this.cbbBaudRate.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cbbBaudRate.ForeColor = System.Drawing.Color.Aqua;
            this.cbbBaudRate.FormattingEnabled = true;
            this.cbbBaudRate.Items.AddRange(new object[] {
            "115200",
            "9600",
            "4800"});
            this.cbbBaudRate.Location = new System.Drawing.Point(80, 52);
            this.cbbBaudRate.Name = "cbbBaudRate";
            this.cbbBaudRate.Size = new System.Drawing.Size(119, 20);
            this.cbbBaudRate.TabIndex = 4;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Black;
            this.label4.ForeColor = System.Drawing.Color.Aqua;
            this.label4.Location = new System.Drawing.Point(3, 53);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 5;
            this.label4.Text = "波特率：";
            // 
            // cbbCOM
            // 
            this.cbbCOM.BackColor = System.Drawing.Color.Black;
            this.cbbCOM.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cbbCOM.ForeColor = System.Drawing.Color.Aqua;
            this.cbbCOM.FormattingEnabled = true;
            this.cbbCOM.Location = new System.Drawing.Point(80, 25);
            this.cbbCOM.Name = "cbbCOM";
            this.cbbCOM.Size = new System.Drawing.Size(119, 20);
            this.cbbCOM.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Black;
            this.label3.ForeColor = System.Drawing.Color.Aqua;
            this.label3.Location = new System.Drawing.Point(15, 28);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "串口：";
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Black;
            this.groupBox3.Controls.Add(this.panel2);
            this.groupBox3.ForeColor = System.Drawing.Color.Aqua;
            this.groupBox3.Location = new System.Drawing.Point(12, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(418, 41);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "协议";
            this.groupBox3.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.SystemColors.Control;
            this.panel2.Controls.Add(this.txtPath);
            this.panel2.Controls.Add(this.btnPath);
            this.panel2.Location = new System.Drawing.Point(5, 12);
            this.panel2.Margin = new System.Windows.Forms.Padding(0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(409, 24);
            this.panel2.TabIndex = 3;
            // 
            // txtPath
            // 
            this.txtPath.BackColor = System.Drawing.Color.Black;
            this.txtPath.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txtPath.ForeColor = System.Drawing.Color.Aqua;
            this.txtPath.Location = new System.Drawing.Point(1, 1);
            this.txtPath.Multiline = true;
            this.txtPath.Name = "txtPath";
            this.txtPath.ReadOnly = true;
            this.txtPath.Size = new System.Drawing.Size(386, 22);
            this.txtPath.TabIndex = 2;
            // 
            // btnPath
            // 
            this.btnPath.BackColor = System.Drawing.Color.Black;
            this.btnPath.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPath.ForeColor = System.Drawing.Color.Cyan;
            this.btnPath.Location = new System.Drawing.Point(388, 1);
            this.btnPath.Name = "btnPath";
            this.btnPath.Size = new System.Drawing.Size(19, 22);
            this.btnPath.TabIndex = 1;
            this.btnPath.Text = ".";
            this.btnPath.UseVisualStyleBackColor = false;
            this.btnPath.Click += new System.EventHandler(this.btnPath_Click);
            // 
            // DataSrcFrom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(436, 173);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "DataSrcFrom";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "数据来源选择";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ComboBox cbbIP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.ComboBox cbbCOM;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cbbBaudRate;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btnTCP;
        private System.Windows.Forms.Button btnCOM;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnPath;
        private System.Windows.Forms.TextBox txtPath;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
    }
}
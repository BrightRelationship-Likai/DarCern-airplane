namespace CeUAV
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.ToolStripMenuItemFile = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItemHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItemProtrocol = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItemAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.lblClientIP = new System.Windows.Forms.Label();
            this.lblStatus = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lblSelfIP = new System.Windows.Forms.Label();
            this.cbbl = new System.Windows.Forms.ComboBox();
            this.cbbr = new System.Windows.Forms.ComboBox();
            this.gg2 = new NationalInstruments.UI.WindowsForms.Gauge();
            this.gg1 = new NationalInstruments.UI.WindowsForms.Gauge();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btnShowWave = new System.Windows.Forms.Button();
            this.btnShowDebug = new System.Windows.Forms.Button();
            this.btnShowCtl = new System.Windows.Forms.Button();
            this.btnDpForm = new System.Windows.Forms.Button();
            this.btnDataForm = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnPtl = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnGPSMap = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gg2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gg1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.Black;
            this.pictureBox1.Location = new System.Drawing.Point(4, 11);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(298, 298);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItemFile,
            this.toolStripMenuItem1,
            this.ToolStripMenuItemHelp,
            this.ToolStripMenuItemAbout});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(318, 25);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // ToolStripMenuItemFile
            // 
            this.ToolStripMenuItemFile.Name = "ToolStripMenuItemFile";
            this.ToolStripMenuItemFile.Size = new System.Drawing.Size(44, 21);
            this.ToolStripMenuItemFile.Text = "文件";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(44, 21);
            this.toolStripMenuItem1.Text = "工具";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(112, 22);
            this.toolStripMenuItem2.Text = "新协议";
            this.toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem2_Click);
            // 
            // ToolStripMenuItemHelp
            // 
            this.ToolStripMenuItemHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItemProtrocol});
            this.ToolStripMenuItemHelp.Name = "ToolStripMenuItemHelp";
            this.ToolStripMenuItemHelp.Size = new System.Drawing.Size(44, 21);
            this.ToolStripMenuItemHelp.Text = "帮助";
            // 
            // ToolStripMenuItemProtrocol
            // 
            this.ToolStripMenuItemProtrocol.Name = "ToolStripMenuItemProtrocol";
            this.ToolStripMenuItemProtrocol.Size = new System.Drawing.Size(124, 22);
            this.ToolStripMenuItemProtrocol.Text = "通信协议";
            this.ToolStripMenuItemProtrocol.Click += new System.EventHandler(this.ToolStripMenuItemProtrocol_Click);
            // 
            // ToolStripMenuItemAbout
            // 
            this.ToolStripMenuItemAbout.Name = "ToolStripMenuItemAbout";
            this.ToolStripMenuItemAbout.Size = new System.Drawing.Size(44, 21);
            this.ToolStripMenuItemAbout.Text = "关于";
            this.ToolStripMenuItemAbout.Click += new System.EventHandler(this.关于ToolStripMenuItem_Click);
            // 
            // lblClientIP
            // 
            this.lblClientIP.AutoSize = true;
            this.lblClientIP.ForeColor = System.Drawing.Color.Aqua;
            this.lblClientIP.Location = new System.Drawing.Point(6, 62);
            this.lblClientIP.Name = "lblClientIP";
            this.lblClientIP.Size = new System.Drawing.Size(65, 12);
            this.lblClientIP.TabIndex = 3;
            this.lblClientIP.Text = "客户端IP：";
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.ForeColor = System.Drawing.Color.Aqua;
            this.lblStatus.Location = new System.Drawing.Point(6, 48);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(101, 12);
            this.lblStatus.TabIndex = 2;
            this.lblStatus.Text = "客户端连接状态：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Aqua;
            this.label2.Location = new System.Drawing.Point(6, 33);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(101, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "服务器端口：2121";
            // 
            // lblSelfIP
            // 
            this.lblSelfIP.AutoSize = true;
            this.lblSelfIP.ForeColor = System.Drawing.Color.Aqua;
            this.lblSelfIP.Location = new System.Drawing.Point(6, 17);
            this.lblSelfIP.Name = "lblSelfIP";
            this.lblSelfIP.Size = new System.Drawing.Size(101, 12);
            this.lblSelfIP.TabIndex = 0;
            this.lblSelfIP.Text = "本机(服务器)IP：";
            // 
            // cbbl
            // 
            this.cbbl.BackColor = System.Drawing.Color.Black;
            this.cbbl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbl.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cbbl.Font = new System.Drawing.Font("宋体", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbbl.ForeColor = System.Drawing.Color.Aqua;
            this.cbbl.FormattingEnabled = true;
            this.cbbl.Location = new System.Drawing.Point(32, 13);
            this.cbbl.Name = "cbbl";
            this.cbbl.Size = new System.Drawing.Size(99, 18);
            this.cbbl.TabIndex = 2;
            this.cbbl.SelectedIndexChanged += new System.EventHandler(this.cbbl_SelectedIndexChanged);
            // 
            // cbbr
            // 
            this.cbbr.BackColor = System.Drawing.Color.Black;
            this.cbbr.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbr.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cbbr.Font = new System.Drawing.Font("宋体", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbbr.ForeColor = System.Drawing.Color.Aqua;
            this.cbbr.FormattingEnabled = true;
            this.cbbr.Location = new System.Drawing.Point(176, 13);
            this.cbbr.Name = "cbbr";
            this.cbbr.Size = new System.Drawing.Size(99, 18);
            this.cbbr.TabIndex = 0;
            this.cbbr.SelectedIndexChanged += new System.EventHandler(this.cbbr_SelectedIndexChanged);
            // 
            // gg2
            // 
            this.gg2.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.gg2.Location = new System.Drawing.Point(152, 27);
            this.gg2.Name = "gg2";
            this.gg2.Size = new System.Drawing.Size(146, 138);
            this.gg2.TabIndex = 1;
            // 
            // gg1
            // 
            this.gg1.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.gg1.Location = new System.Drawing.Point(6, 27);
            this.gg1.Name = "gg1";
            this.gg1.Size = new System.Drawing.Size(146, 138);
            this.gg1.TabIndex = 0;
            // 
            // timer1
            // 
            this.timer1.Interval = 50;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btnShowWave
            // 
            this.btnShowWave.BackColor = System.Drawing.Color.Black;
            this.btnShowWave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnShowWave.ForeColor = System.Drawing.Color.Aqua;
            this.btnShowWave.Location = new System.Drawing.Point(6, 20);
            this.btnShowWave.Name = "btnShowWave";
            this.btnShowWave.Size = new System.Drawing.Size(66, 66);
            this.btnShowWave.TabIndex = 4;
            this.btnShowWave.Text = "显示波形";
            this.btnShowWave.UseVisualStyleBackColor = false;
            this.btnShowWave.Click += new System.EventHandler(this.btnShowWave_Click);
            // 
            // btnShowDebug
            // 
            this.btnShowDebug.BackColor = System.Drawing.Color.Black;
            this.btnShowDebug.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnShowDebug.ForeColor = System.Drawing.Color.Aqua;
            this.btnShowDebug.Location = new System.Drawing.Point(81, 20);
            this.btnShowDebug.Name = "btnShowDebug";
            this.btnShowDebug.Size = new System.Drawing.Size(66, 66);
            this.btnShowDebug.TabIndex = 4;
            this.btnShowDebug.Text = "显示参数调整";
            this.btnShowDebug.UseVisualStyleBackColor = false;
            this.btnShowDebug.Click += new System.EventHandler(this.btnShowDebug_Click);
            // 
            // btnShowCtl
            // 
            this.btnShowCtl.BackColor = System.Drawing.Color.Black;
            this.btnShowCtl.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnShowCtl.ForeColor = System.Drawing.Color.Aqua;
            this.btnShowCtl.Location = new System.Drawing.Point(156, 20);
            this.btnShowCtl.Name = "btnShowCtl";
            this.btnShowCtl.Size = new System.Drawing.Size(66, 66);
            this.btnShowCtl.TabIndex = 4;
            this.btnShowCtl.Text = "显示控制";
            this.btnShowCtl.UseVisualStyleBackColor = false;
            this.btnShowCtl.Click += new System.EventHandler(this.btnShowCtl_Click);
            // 
            // btnDpForm
            // 
            this.btnDpForm.BackColor = System.Drawing.Color.Black;
            this.btnDpForm.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDpForm.ForeColor = System.Drawing.Color.Aqua;
            this.btnDpForm.Location = new System.Drawing.Point(6, 92);
            this.btnDpForm.Name = "btnDpForm";
            this.btnDpForm.Size = new System.Drawing.Size(66, 66);
            this.btnDpForm.TabIndex = 5;
            this.btnDpForm.Text = "电调驱动";
            this.btnDpForm.UseVisualStyleBackColor = false;
            this.btnDpForm.Click += new System.EventHandler(this.btnDpForm_Click);
            // 
            // btnDataForm
            // 
            this.btnDataForm.BackColor = System.Drawing.Color.Black;
            this.btnDataForm.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDataForm.ForeColor = System.Drawing.Color.Aqua;
            this.btnDataForm.Location = new System.Drawing.Point(231, 20);
            this.btnDataForm.Name = "btnDataForm";
            this.btnDataForm.Size = new System.Drawing.Size(66, 66);
            this.btnDataForm.TabIndex = 6;
            this.btnDataForm.Text = "数据通讯";
            this.btnDataForm.UseVisualStyleBackColor = false;
            this.btnDataForm.Click += new System.EventHandler(this.btnDataForm_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Black;
            this.groupBox1.Controls.Add(this.cbbr);
            this.groupBox1.Controls.Add(this.cbbl);
            this.groupBox1.Controls.Add(this.gg2);
            this.groupBox1.Controls.Add(this.gg1);
            this.groupBox1.ForeColor = System.Drawing.Color.Aqua;
            this.groupBox1.Location = new System.Drawing.Point(6, 341);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(306, 185);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "基本";
            this.groupBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Black;
            this.groupBox2.Controls.Add(this.btnGPSMap);
            this.groupBox2.Controls.Add(this.btnPtl);
            this.groupBox2.Controls.Add(this.btnShowCtl);
            this.groupBox2.Controls.Add(this.btnShowWave);
            this.groupBox2.Controls.Add(this.btnShowDebug);
            this.groupBox2.Controls.Add(this.btnDpForm);
            this.groupBox2.Controls.Add(this.btnDataForm);
            this.groupBox2.ForeColor = System.Drawing.Color.Aqua;
            this.groupBox2.Location = new System.Drawing.Point(6, 530);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(306, 163);
            this.groupBox2.TabIndex = 8;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "窗口";
            this.groupBox2.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            // 
            // btnPtl
            // 
            this.btnPtl.BackColor = System.Drawing.Color.Black;
            this.btnPtl.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPtl.ForeColor = System.Drawing.Color.Aqua;
            this.btnPtl.Location = new System.Drawing.Point(81, 92);
            this.btnPtl.Name = "btnPtl";
            this.btnPtl.Size = new System.Drawing.Size(66, 66);
            this.btnPtl.TabIndex = 7;
            this.btnPtl.Text = "通讯协议";
            this.btnPtl.UseVisualStyleBackColor = false;
            this.btnPtl.Click += new System.EventHandler(this.btnPtl_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Black;
            this.groupBox3.Controls.Add(this.lblSelfIP);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.lblClientIP);
            this.groupBox3.Controls.Add(this.lblStatus);
            this.groupBox3.ForeColor = System.Drawing.Color.Aqua;
            this.groupBox3.Location = new System.Drawing.Point(6, 697);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(306, 80);
            this.groupBox3.TabIndex = 9;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "状态";
            this.groupBox3.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.pictureBox1);
            this.groupBox4.Location = new System.Drawing.Point(6, 24);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(306, 314);
            this.groupBox4.TabIndex = 10;
            this.groupBox4.TabStop = false;
            this.groupBox4.Paint += new System.Windows.Forms.PaintEventHandler(this.groupBox1_Paint);
            // 
            // btnGPSMap
            // 
            this.btnGPSMap.BackColor = System.Drawing.Color.Black;
            this.btnGPSMap.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnGPSMap.ForeColor = System.Drawing.Color.Aqua;
            this.btnGPSMap.Location = new System.Drawing.Point(156, 92);
            this.btnGPSMap.Name = "btnGPSMap";
            this.btnGPSMap.Size = new System.Drawing.Size(66, 66);
            this.btnGPSMap.TabIndex = 8;
            this.btnGPSMap.Text = "GPS地图";
            this.btnGPSMap.UseVisualStyleBackColor = false;
            this.btnGPSMap.Click += new System.EventHandler(this.btnGPSMap_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(318, 784);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "CREELINKS小四轴无人机";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gg2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gg1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemFile;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemHelp;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemAbout;
        private NationalInstruments.UI.WindowsForms.Gauge gg2;
        private NationalInstruments.UI.WindowsForms.Gauge gg1;
        public  System.Windows.Forms.ComboBox cbbl;
        public  System.Windows.Forms.ComboBox cbbr;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label lblSelfIP;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Label lblClientIP;
        private System.Windows.Forms.Button btnShowWave;
        private System.Windows.Forms.Button btnShowDebug;
        private System.Windows.Forms.Button btnShowCtl;
        private System.Windows.Forms.Button btnDpForm;
        private System.Windows.Forms.Button btnDataForm;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.Button btnPtl;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemProtrocol;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnGPSMap;
    }
}


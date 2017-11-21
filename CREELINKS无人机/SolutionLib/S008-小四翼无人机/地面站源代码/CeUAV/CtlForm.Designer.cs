namespace CeUAV
{
    partial class CtlForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CtlForm));
            this.lblRy = new System.Windows.Forms.Label();
            this.lblRx = new System.Windows.Forms.Label();
            this.lblLy = new System.Windows.Forms.Label();
            this.lblLx = new System.Windows.Forms.Label();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnLeft = new System.Windows.Forms.CheckBox();
            this.btnRight = new System.Windows.Forms.CheckBox();
            this.cbS2D = new System.Windows.Forms.CheckBox();
            this.cbS2C = new System.Windows.Forms.CheckBox();
            this.cbS2B = new System.Windows.Forms.CheckBox();
            this.cbS2A = new System.Windows.Forms.CheckBox();
            this.pbRight = new System.Windows.Forms.PictureBox();
            this.pbLeft = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pbRight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbLeft)).BeginInit();
            this.SuspendLayout();
            // 
            // lblRy
            // 
            this.lblRy.AutoSize = true;
            this.lblRy.BackColor = System.Drawing.Color.Black;
            this.lblRy.ForeColor = System.Drawing.Color.Aqua;
            this.lblRy.Location = new System.Drawing.Point(138, 75);
            this.lblRy.Name = "lblRy";
            this.lblRy.Size = new System.Drawing.Size(23, 12);
            this.lblRy.TabIndex = 23;
            this.lblRy.Text = "ry:";
            // 
            // lblRx
            // 
            this.lblRx.AutoSize = true;
            this.lblRx.BackColor = System.Drawing.Color.Black;
            this.lblRx.ForeColor = System.Drawing.Color.Aqua;
            this.lblRx.Location = new System.Drawing.Point(138, 63);
            this.lblRx.Name = "lblRx";
            this.lblRx.Size = new System.Drawing.Size(23, 12);
            this.lblRx.TabIndex = 22;
            this.lblRx.Text = "rx:";
            // 
            // lblLy
            // 
            this.lblLy.AutoSize = true;
            this.lblLy.BackColor = System.Drawing.Color.Black;
            this.lblLy.ForeColor = System.Drawing.Color.Aqua;
            this.lblLy.Location = new System.Drawing.Point(138, 51);
            this.lblLy.Name = "lblLy";
            this.lblLy.Size = new System.Drawing.Size(23, 12);
            this.lblLy.TabIndex = 21;
            this.lblLy.Text = "ly:";
            // 
            // lblLx
            // 
            this.lblLx.AutoSize = true;
            this.lblLx.BackColor = System.Drawing.Color.Black;
            this.lblLx.ForeColor = System.Drawing.Color.Aqua;
            this.lblLx.Location = new System.Drawing.Point(138, 39);
            this.lblLx.Name = "lblLx";
            this.lblLx.Size = new System.Drawing.Size(23, 12);
            this.lblLx.TabIndex = 20;
            this.lblLx.Text = "lx:";
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.Black;
            this.btnReset.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnReset.ForeColor = System.Drawing.Color.Aqua;
            this.btnReset.Location = new System.Drawing.Point(136, 136);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(49, 24);
            this.btnReset.TabIndex = 19;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnLeft
            // 
            this.btnLeft.AutoSize = true;
            this.btnLeft.BackColor = System.Drawing.Color.Transparent;
            this.btnLeft.Location = new System.Drawing.Point(14, 121);
            this.btnLeft.Name = "btnLeft";
            this.btnLeft.Size = new System.Drawing.Size(15, 14);
            this.btnLeft.TabIndex = 15;
            this.btnLeft.UseVisualStyleBackColor = false;
            this.btnLeft.CheckedChanged += new System.EventHandler(this.btnLeft_CheckedChanged);
            // 
            // btnRight
            // 
            this.btnRight.AutoSize = true;
            this.btnRight.BackColor = System.Drawing.Color.Transparent;
            this.btnRight.Location = new System.Drawing.Point(288, 121);
            this.btnRight.Name = "btnRight";
            this.btnRight.Size = new System.Drawing.Size(15, 14);
            this.btnRight.TabIndex = 18;
            this.btnRight.UseVisualStyleBackColor = false;
            this.btnRight.CheckedChanged += new System.EventHandler(this.btnRight_CheckedChanged);
            // 
            // cbS2D
            // 
            this.cbS2D.AutoSize = true;
            this.cbS2D.BackColor = System.Drawing.Color.Black;
            this.cbS2D.ForeColor = System.Drawing.Color.Aqua;
            this.cbS2D.Location = new System.Drawing.Point(264, 141);
            this.cbS2D.Name = "cbS2D";
            this.cbS2D.Size = new System.Drawing.Size(42, 16);
            this.cbS2D.TabIndex = 16;
            this.cbS2D.Text = "S2D";
            this.cbS2D.UseVisualStyleBackColor = false;
            this.cbS2D.CheckedChanged += new System.EventHandler(this.cbS2D_CheckedChanged);
            // 
            // cbS2C
            // 
            this.cbS2C.AutoSize = true;
            this.cbS2C.BackColor = System.Drawing.Color.Black;
            this.cbS2C.ForeColor = System.Drawing.Color.Aqua;
            this.cbS2C.Location = new System.Drawing.Point(216, 141);
            this.cbS2C.Name = "cbS2C";
            this.cbS2C.Size = new System.Drawing.Size(42, 16);
            this.cbS2C.TabIndex = 14;
            this.cbS2C.Text = "S2C";
            this.cbS2C.UseVisualStyleBackColor = false;
            this.cbS2C.CheckedChanged += new System.EventHandler(this.cbS2C_CheckedChanged);
            // 
            // cbS2B
            // 
            this.cbS2B.AutoSize = true;
            this.cbS2B.BackColor = System.Drawing.Color.Black;
            this.cbS2B.ForeColor = System.Drawing.Color.Aqua;
            this.cbS2B.Location = new System.Drawing.Point(60, 140);
            this.cbS2B.Name = "cbS2B";
            this.cbS2B.Size = new System.Drawing.Size(42, 16);
            this.cbS2B.TabIndex = 13;
            this.cbS2B.Text = "S2B";
            this.cbS2B.UseVisualStyleBackColor = false;
            this.cbS2B.CheckedChanged += new System.EventHandler(this.cbS2B_CheckedChanged);
            // 
            // cbS2A
            // 
            this.cbS2A.AutoSize = true;
            this.cbS2A.BackColor = System.Drawing.Color.Black;
            this.cbS2A.ForeColor = System.Drawing.Color.Aqua;
            this.cbS2A.Location = new System.Drawing.Point(12, 140);
            this.cbS2A.Name = "cbS2A";
            this.cbS2A.Size = new System.Drawing.Size(42, 16);
            this.cbS2A.TabIndex = 12;
            this.cbS2A.Text = "S2A";
            this.cbS2A.UseVisualStyleBackColor = false;
            this.cbS2A.CheckedChanged += new System.EventHandler(this.cbS2A_CheckedChanged);
            // 
            // pbRight
            // 
            this.pbRight.BackColor = System.Drawing.Color.Transparent;
            this.pbRight.Location = new System.Drawing.Point(180, 12);
            this.pbRight.Name = "pbRight";
            this.pbRight.Size = new System.Drawing.Size(126, 126);
            this.pbRight.TabIndex = 17;
            this.pbRight.TabStop = false;
            this.pbRight.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbRight_MouseDown);
            this.pbRight.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbRight_MouseMove);
            this.pbRight.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pbRight_MouseUp);
            // 
            // pbLeft
            // 
            this.pbLeft.BackColor = System.Drawing.Color.Transparent;
            this.pbLeft.Location = new System.Drawing.Point(12, 12);
            this.pbLeft.Name = "pbLeft";
            this.pbLeft.Size = new System.Drawing.Size(126, 126);
            this.pbLeft.TabIndex = 11;
            this.pbLeft.TabStop = false;
            this.pbLeft.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbLeft_MouseDown);
            this.pbLeft.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbLeft_MouseMove);
            this.pbLeft.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pbLeft_MouseUp);
            // 
            // CtlForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(318, 162);
            this.Controls.Add(this.lblRy);
            this.Controls.Add(this.lblRx);
            this.Controls.Add(this.lblLy);
            this.Controls.Add(this.lblLx);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnLeft);
            this.Controls.Add(this.btnRight);
            this.Controls.Add(this.cbS2D);
            this.Controls.Add(this.cbS2C);
            this.Controls.Add(this.cbS2B);
            this.Controls.Add(this.cbS2A);
            this.Controls.Add(this.pbRight);
            this.Controls.Add(this.pbLeft);
            this.Cursor = System.Windows.Forms.Cursors.Default;
            this.ForeColor = System.Drawing.Color.Aqua;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "CtlForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "遥控";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.CtlForm_FormClosing);
            this.Load += new System.EventHandler(this.CtlForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pbRight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbLeft)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.Label lblRy;
        public System.Windows.Forms.Label lblRx;
        public System.Windows.Forms.Label lblLy;
        public System.Windows.Forms.Label lblLx;
        public System.Windows.Forms.Button btnReset;
        public System.Windows.Forms.CheckBox btnLeft;
        public System.Windows.Forms.CheckBox btnRight;
        public System.Windows.Forms.CheckBox cbS2D;
        public System.Windows.Forms.CheckBox cbS2C;
        public System.Windows.Forms.CheckBox cbS2B;
        public System.Windows.Forms.CheckBox cbS2A;
        public System.Windows.Forms.PictureBox pbRight;
        public System.Windows.Forms.PictureBox pbLeft;

    }
}
namespace CeUAV
{
    partial class NewTMUForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NewTMUForm));
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.nudPackSize = new System.Windows.Forms.NumericUpDown();
            this.btnSure = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.nudPackSize)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Black;
            this.label1.ForeColor = System.Drawing.Color.Aqua;
            this.label1.Location = new System.Drawing.Point(12, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(281, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "帧头(0x55)+包序号+数据).....+校验和+帧尾(0xFE)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Black;
            this.label2.ForeColor = System.Drawing.Color.Aqua;
            this.label2.Location = new System.Drawing.Point(12, 18);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "包长度：";
            // 
            // nudPackSize
            // 
            this.nudPackSize.BackColor = System.Drawing.Color.Black;
            this.nudPackSize.ForeColor = System.Drawing.Color.Aqua;
            this.nudPackSize.Location = new System.Drawing.Point(60, 14);
            this.nudPackSize.Maximum = new decimal(new int[] {
            1024,
            0,
            0,
            0});
            this.nudPackSize.Minimum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.nudPackSize.Name = "nudPackSize";
            this.nudPackSize.Size = new System.Drawing.Size(233, 21);
            this.nudPackSize.TabIndex = 1;
            this.nudPackSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.nudPackSize.Value = new decimal(new int[] {
            32,
            0,
            0,
            0});
            // 
            // btnSure
            // 
            this.btnSure.BackColor = System.Drawing.Color.Black;
            this.btnSure.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSure.ForeColor = System.Drawing.Color.Aqua;
            this.btnSure.Location = new System.Drawing.Point(218, 62);
            this.btnSure.Name = "btnSure";
            this.btnSure.Size = new System.Drawing.Size(75, 23);
            this.btnSure.TabIndex = 2;
            this.btnSure.Text = "确定";
            this.btnSure.UseVisualStyleBackColor = false;
            this.btnSure.Click += new System.EventHandler(this.btnSure_Click);
            // 
            // NewTMUForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(297, 92);
            this.Controls.Add(this.btnSure);
            this.Controls.Add(this.nudPackSize);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "NewTMUForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "新协议格式";
            ((System.ComponentModel.ISupportInitialize)(this.nudPackSize)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown nudPackSize;
        private System.Windows.Forms.Button btnSure;

    }
}
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
    public partial class TMUForm : Form
    {
        string path = "";
        int packSize = 0;
        Bitmap bitmapBg = new Bitmap(100,100);
        public TMUForm(int packSize, string path)
        {
            InitializeComponent();

            this.packSize = packSize;
            this.path = path;

            if (path != null)
            {
                lblPath.Text = "协议路径：" + path;
                btnLoad_Click(null, null);
            }
            else
            {
            addTabCtl();
            }

            try
            {
                 bitmapBg = new Bitmap(Application.StartupPath + "\\black_bg.png");
            }
            catch (Exception)
            {
            }
        }


        public void addTabCtl()
        {
                TabPage tp = new TabPage();
                tp.Text = "第" + (tc.TabCount).ToString() + "包";
                tp.Padding = new System.Windows.Forms.Padding(3);
                tp.UseVisualStyleBackColor = true;

                DataGridView dgv = new DataGridView();
                DataGridViewTextBoxColumn Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
                DataGridViewTextBoxColumn Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
                DataGridViewTextBoxColumn Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
                DataGridViewCellStyle dataGridViewCellStyle1 = new DataGridViewCellStyle();
                DataGridViewCellStyle dataGridViewCellStyle2 = new DataGridViewCellStyle();

                dgv.AllowUserToAddRows = false;
                dgv.AllowUserToDeleteRows = false;
                dgv.AllowUserToResizeRows = false;
                dgv.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
                dgv.BackgroundColor = System.Drawing.Color.Black;
                dgv.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
                dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
                dataGridViewCellStyle1.BackColor = System.Drawing.Color.Black;
                dataGridViewCellStyle1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
                dataGridViewCellStyle1.ForeColor = System.Drawing.Color.Cyan;
                dataGridViewCellStyle1.SelectionBackColor = System.Drawing.Color.Gray;
                dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
                dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
                dgv.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
                dgv.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
                dgv.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {Column1,Column2,Column3});
                dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
                dataGridViewCellStyle2.BackColor = System.Drawing.Color.Black;
                dataGridViewCellStyle2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
                dataGridViewCellStyle2.ForeColor = System.Drawing.Color.Cyan;
                dataGridViewCellStyle2.SelectionBackColor = System.Drawing.Color.Gray;
                dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
                dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
                dgv.DefaultCellStyle = dataGridViewCellStyle2;
                dgv.EnableHeadersVisualStyles = false;
                dgv.Location = new System.Drawing.Point(3, 3);
                dgv.Dock = System.Windows.Forms.DockStyle.Fill;
                dgv.Name = "dgv"+tc.TabCount.ToString();
                dgv.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
                dgv.RowHeadersVisible = false;
                dgv.RowTemplate.Height = 23;
                dgv.Size = new System.Drawing.Size(718, 248);
                dgv.TabIndex = 2;           
                dgv.CellValueChanged += dgv1_CellValueChanged;
                dgv.Columns[0].HeaderText = "包索引";
                dgv.Columns[0].ReadOnly = true;
                dgv.Columns[1].HeaderText = "参数名称";
                dgv.Columns[2].HeaderText = "乘以系数";

                dgv.Rows.Add(new String[] { "0", "帧头0x55", "1" });
                dgv.Rows.Add(new String[] {  "1","包序号(起始于0)", "1" });
                for (int j = 2; j < packSize - 2; j += 4)
                {
                    dgv.Rows.Add(new String[] { j.ToString() + "~" + (j + 3).ToString(), "*", "1" });
                }
                dgv.Rows.Add(new String[] { (packSize - 2).ToString(), "校验合", "1" });
                dgv.Rows.Add(new String[] { (packSize - 1).ToString(), "帧尾0xFE", "1" });

                dgv.Rows[0].ReadOnly = true;
                dgv.Rows[1].ReadOnly = true;
                dgv.Rows[dgv.Rows.Count - 2].ReadOnly = true;
                dgv.Rows[dgv.Rows.Count - 1].ReadOnly = true;

                tp.Controls.Add(dgv);
                tc.TabPages.Add(tp);         
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            if (sender != null)
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Filter = "*.cfg|*.cfg";
                if (ofd.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                {
                    return;
                }
                path = ofd.FileName;
                lblPath.Text = "协议路径：" + path;
            }

            FileStream fs = null;
            StreamReader sr = null;
            try
            {
                fs = new FileStream(path, FileMode.Open);
                sr = new StreamReader(fs, Encoding.Default);
                packSize = Convert.ToInt32(sr.ReadLine().Trim().Replace("PackSize:", ""));
                int tabPages = Convert.ToInt32(sr.ReadLine().Trim().Replace("PackCount:", ""));
                tc.TabPages.Clear();

                for (int i = 0; i < tabPages; i++)
                {
                    addTabCtl();
                }

                for (int i = 0; i < tc.TabPages.Count; i++)
                {
                    TabPage tp = tc.TabPages[i];
                    DataGridView dgv = null;
                    foreach (Control c in tp.Controls)
                    {
                        if (c is DataGridView)
                        {
                            dgv = (DataGridView)c;
                        }
                    }

                    for (int j = 2; j < packSize - 2; j += 4)
                    {
                        dgv.Rows[(j - 2) / 4 + 2].Cells[1].Value = sr.ReadLine().Trim();
                        dgv.Rows[(j - 2) / 4 + 2].Cells[2].Value = sr.ReadLine().Trim();
                    }
                }

                if (tc.TabCount > 0) tc.SelectedIndex = 0;
                sr.Close();
                fs.Close();
            }
            catch (Exception)
            {
                MessageBox.Show("无法解析协议，文件是否已经损坏？");
                if (sr != null)
                {
                    sr.Close();
                    sr = null;
                }
                if (fs != null)
                {
                    fs.Close();
                }
            }
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.AddExtension = true;
            sfd.Filter = "*.cfg|*.cfg";
            if (sfd.ShowDialog() != DialogResult.OK)
            {
                return;
            }
            path = sfd.FileName;
            lblPath.Text = "协议路径：" + path;

            FileStream fs = null;
            StreamWriter sw = null;
            try
            {
                fs = new FileStream(path, FileMode.Create);
                sw = new StreamWriter(fs, Encoding.Default);
                sw.WriteLine("PackSize:" + packSize.ToString());
                sw.WriteLine("PackCount:" + tc.TabPages.Count.ToString());
                for (int i = 0; i < tc.TabPages.Count; i++)
                {
                    TabPage tp = tc.TabPages[i];
                    DataGridView dgv = null;
                    foreach (Control c in tp.Controls)
                    {
                        if (c is DataGridView)
                        {
                            dgv = (DataGridView)c;
                        }
                    }

                    for (int j = 2; j < packSize - 2; j += 4)
                    {
                        sw.WriteLine(dgv.Rows[(j - 2) / 4 + 2].Cells[1].Value.ToString());
                        sw.WriteLine(dgv.Rows[(j - 2) / 4 + 2].Cells[2].Value.ToString());
                    }
                }
                sw.Close();
                fs.Close();
                MessageBox.Show("保存完毕,需重启软件，并在传输方式对话框中选择协议文件即可！");
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
                if (sw != null)
                {
                    sw.Close();
                    sw = null;
                }
                if (fs != null)
                {
                    fs.Close();
                }
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            addTabCtl();
        }

        private void btnDel_Click(object sender, EventArgs e)
        {
            if (DialogResult.OK != MessageBox.Show("当前选择的包删除后不可恢复，确定删除", "警告", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning))
            {
                return;
            }
            tc.TabPages.RemoveAt(tc.SelectedIndex);
            for (int i = 0; i < tc.TabCount; i++)
            {
                tc.TabPages[i].Text = "第" + i.ToString() + "包";
            }
        }

        private void dgv1_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            DataGridView dgv = (DataGridView)sender;
            if (e.ColumnIndex > dgv.ColumnCount || e.ColumnIndex < 0 || e.RowIndex < 0 || e.RowIndex > dgv.RowCount)
                return;

            if (e.ColumnIndex == 1)
            {
                if (dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value == null)
                {
                    dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = "*";
                }

                if (Convert.ToString(dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value) == "*")
                {
                    return;
                }
                foreach (char c in dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString())
                {
                    if (char.IsLetterOrDigit(c) == false)
                    {
                        if (c != '_')
                        {
                            MessageBox.Show("名称中只允许 字母 或 数字 或 下划线 格式！");
                            dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = "*";
                            return;
                        }
                    }
                }
            }

            if (e.ColumnIndex == 2)
            {
                if (dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value == null)
                {
                    dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = "1";
                }
                double temp = 0;
                if (Double.TryParse(dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString(), out temp) == false)
                {
                    MessageBox.Show("只允许为 数字！");
                    dgv.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = "1";
                    return;
                }
            }
        }

        private void tc_DrawItem(object sender, DrawItemEventArgs e)
        {
            Rectangle rec = tc.ClientRectangle;
            StringFormat StrFormat = new StringFormat();
            StrFormat.LineAlignment = StringAlignment.Center;
            StrFormat.Alignment = StringAlignment.Center;         
            SolidBrush bru = new SolidBrush(Color.Black);
            SolidBrush bruFont = new SolidBrush(Color.Aqua);
            Font font = new System.Drawing.Font("微软雅黑", 9F);

            e.Graphics.DrawImage(bitmapBg, 0, 0, tc.Width, tc.Height);
            for (int i = 0; i < tc.TabPages.Count; i++)
            {
                Rectangle recChild = tc.GetTabRect(i);
                e.Graphics.FillRectangle(bru, recChild);
                e.Graphics.DrawString(tc.TabPages[i].Text, font, bruFont, recChild, StrFormat);
            }
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

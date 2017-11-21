using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using mshtml;

namespace CeUAV
{
    public partial class GpsMapForm : Form
    {
        public GpsMapForm()
        {
            InitializeComponent();
            webBrowser1.Navigate(Application.StartupPath + "\\baidumap.html");
        }


        /// <summary>
        /// 执行HTML文件中的信息
        /// </summary>
        /// <param name="cmd"></param>
        /// <param name="brower"></param>
        public void SetScriptFunction(string cmd, WebBrowser brower)
        {
            IHTMLDocument2 vDocument = brower.Document.DomDocument as IHTMLDocument2;
            IHTMLWindow2 vWindow = (IHTMLWindow2)vDocument.parentWindow;
            try
            {
                vWindow.execScript(cmd, "javascript");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                throw;
            }

        }

        /// <summary>
        /// 更新GPS显示的地图信息
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public void updataGpsMap(double x, double y)
        {
            String con = "theLocation(" + x.ToString() + "," + y.ToString() + ")";
            SetScriptFunction(con, webBrowser1);
        }
    }
}

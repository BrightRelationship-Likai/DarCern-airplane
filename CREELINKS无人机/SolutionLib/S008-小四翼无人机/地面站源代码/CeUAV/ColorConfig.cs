﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.IO;
using System.IO.Ports;


namespace CeUAV
{
    public class ColorConfig
    {
        private Color _fontcolor = Color.Aqua;
        /// <summary>
        /// 菜单字体颜色
        /// </summary>
        public Color FontColor
        {
            get { return this._fontcolor; }
            set { this._fontcolor = value; }
        }
        private Color _marginstartcolor = Color.Black;
        /// <summary>
        /// 下拉菜单坐标图标区域开始颜色
        /// </summary>
        public Color MarginStartColor
        {
            get { return this._marginstartcolor; }
            set { this._marginstartcolor = value; }
        }
        private Color _marginendcolor = Color.Black;
        /// <summary>
        /// 下拉菜单坐标图标区域结束颜色
        /// </summary>
        public Color MarginEndColor
        {
            get { return this._marginendcolor; }
            set { this._marginendcolor = value; }
        }
        private Color _dropdownitembackcolor = Color.Black;
        /// <summary>
        /// 下拉项背景颜色
        /// </summary>
        public Color DropDownItemBackColor
        {
            get { return this._dropdownitembackcolor; }
            set { this._dropdownitembackcolor = value; }
        }
        private Color _dropdownitemstartcolor = Color.Gray;
        /// <summary>
        /// 下拉项选中时开始颜色
        /// </summary>
        public Color DropDownItemStartColor
        {
            get { return this._dropdownitemstartcolor; }
            set { this._dropdownitemstartcolor = value; }
        }
        private Color _dorpdownitemendcolor = Color.Gray;
        /// <summary>
        /// 下拉项选中时结束颜色
        /// </summary>
        public Color DropDownItemEndColor
        {
            get { return this._dorpdownitemendcolor; }
            set { this._dorpdownitemendcolor = value; }
        }
        private Color _menuitemstartcolor = Color.Gray;
        /// <summary>
        /// 主菜单项选中时的开始颜色
        /// </summary>
        public Color MenuItemStartColor
        {
            get { return this._menuitemstartcolor; }
            set { this._menuitemstartcolor = value; }
        }
        private Color _menuitemendcolor = Color.Gray;
        /// <summary>
        /// 主菜单项选中时的结束颜色
        /// </summary>
        public Color MenuItemEndColor
        {
            get { return this._menuitemendcolor; }
            set { this._menuitemendcolor = value; }
        }
        private Color _separatorcolor = Color.Blue;
        /// <summary>
        /// 分割线颜色
        /// </summary>
        public Color SeparatorColor
        {
            get { return this._separatorcolor; }
            set { this._separatorcolor = value; }
        }
        private Color _mainmenubackcolor = Color.Black;
        /// <summary>
        /// 主菜单背景色
        /// </summary>
        public Color MainMenuBackColor
        {
            get { return this._mainmenubackcolor; }
            set { this._mainmenubackcolor = value; }
        }
        private Color _mainmenustartcolor = Color.Black;
        /// <summary>
        /// 主菜单背景开始颜色
        /// </summary>
        public Color MainMenuStartColor
        {
            get { return this._mainmenustartcolor; }
            set { this._mainmenustartcolor = value; }
        }
        private Color _mainmenuendcolor = Color.Black;
        /// <summary>
        /// 主菜单背景结束颜色
        /// </summary>
        public Color MainMenuEndColor
        {
            get { return this._mainmenuendcolor; }
            set { this._mainmenuendcolor = value; }
        }
        private Color _dropdownborder = Color.Aqua;
        /// <summary>
        /// 下拉区域边框颜色
        /// </summary>
        public Color DropDownBorder
        {
            get { return this._dropdownborder; }
            set { this._dropdownborder = value; }
        }

    }
}

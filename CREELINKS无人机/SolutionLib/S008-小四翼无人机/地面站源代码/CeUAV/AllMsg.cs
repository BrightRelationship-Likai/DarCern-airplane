using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace CeUAV
{
    public class AllMsg
    {
        public static string protocolPath;

        public static bool isTCP = false;
        public static string tcpIP = "*";
        public static string tcpPort = "2121";

        public static bool isCom = false;
        public static string comPort = "COM1";
        public static string comBaudRate = "115200";

        public static void Load()
        {

            protocolPath = Application.StartupPath + "\\CeProtocal.cfg";
            string allMsgPath = Application.StartupPath + "\\AllMsgCfg.cct";
            if (File.Exists(allMsgPath) == false)
            {
                return;
            }
            FileStream fs = null;
            BinaryReader br = null;
            try
            {
                fs = new FileStream(allMsgPath, FileMode.Open);
                br = new BinaryReader(fs, Encoding.Default);
                protocolPath = br.ReadString();
                tcpIP = br.ReadString();
                tcpPort = br.ReadString();
                comPort = br.ReadString();
                comBaudRate = br.ReadString();
                br.Close();
                fs.Close();
            }
            catch (System.Exception ex)
            {
                if (br != null)
                {
                    br.Close();
                    br = null;
                }
                if (fs != null)
                {
                    fs.Close();
                }
                MessageBox.Show(ex.Message);
            }

            if (File.Exists(protocolPath) == false)
            {
                protocolPath = Application.StartupPath + "\\CeProtocal.cfg";
            }

        }

        public static void Save()
        {
            string allMsgPath = Application.StartupPath + "\\AllMsgCfg.cct";
            FileStream fs = null;
            BinaryWriter bw = null;
            try
            {
                fs = new FileStream(allMsgPath, FileMode.Create);
                bw = new BinaryWriter(fs, Encoding.Default);

                bw.Write((string)protocolPath);
                bw.Write((string)tcpIP);
                bw.Write((string)tcpPort);
                bw.Write((string)comPort);
                bw.Write((string)comBaudRate);

                bw.Close();
                fs.Close();
            }
            catch (Exception)
            {
                if (bw != null)
                {
                    bw.Close();
                    bw = null;
                }
                if (fs != null)
                {
                    fs.Close();
                }
            }
        }
    }


}

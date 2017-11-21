using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Collections;
namespace CeUAV
{
    public class Package
    {
        public ArrayList al = new ArrayList();
        public MainForm mf = null;
        public Package(MainForm mf)
        {
            this.mf = mf;
        }

        public void add(byte[] data, int recvCount)
        {
            for (int i = 0; i < recvCount; i++)
            {
                al.Add(data[i]);
            }
        }

        /// <summary>
        /// 返回带帧头的数据
        /// </summary>
        /// <returns></returns>
        public byte[] get()
        {
            if (al.Count < mf.ptl.packSize)
            {
                return null;
            }
            byte[] buf = new byte[mf.ptl.packSize];
            while (mf.isRunning)
            {
                int index = -1;
                if (al.Count < mf.ptl.packSize)
                {
                    return null;
                }
                for (int i = 0; i < al.Count - 1; i++)
                {
                    if ((byte)(al[i]) == (byte)0x55)
                    {
                        if (i + mf.ptl.packSize - 1 < al.Count)
                        {
                            if ((byte)(al[i + mf.ptl.packSize - 1]) == 0xFE)
                            {
                                index = i;
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        else
                        {
                            return null;
                        }
                    }
                }
                if (index == -1 && al.Count > 0)
                {
                    al.Clear();
                    continue;
                }


                if (index != 0)
                {
                    al.RemoveRange(0, index);
                }

                byte sum = 0;
                for (int i = 0; i < mf.ptl.packSize - 2; i++)
                {
                    sum += (byte)(al[i]);
                }
                if ((byte)sum != (byte)(al[mf.ptl.packSize - 2]))//校验合不正确
                {
                    al.RemoveRange(0, mf.ptl.packSize);
                    continue;
                }
                for (int i = 0; i < mf.ptl.packSize; i++)
                {
                    buf[i] = (byte)(al[i]);
                }
                al.RemoveRange(0, mf.ptl.packSize);
                return buf;
            }
            return null;
        }
    }
}

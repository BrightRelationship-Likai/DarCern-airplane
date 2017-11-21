/**
  ******************************************************************************
  * @file    CeFontGt.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeFontGt模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeFontGt.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeFontGt模块初始化
  * @param  ceFontGt:CeFontGt属性对象
  * @param  ceXX:CeFontGt模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceFontGt_initial(CeFontGt* ceFontGt, CE_RESOURCE ceSpi)
{
    ceFontGt->ceSpiMaster.ceResource = ceSpi;
    ceFontGt->ceSpiMaster.ceSpiMasterSpeed = CE_SPI_MASTER_SPEED_100MBPS;
    ceSpiMasterOp.initial(&(ceFontGt->ceSpiMaster));
    ceSpiMasterOp.start(&(ceFontGt->ceSpiMaster));

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  从字模芯片中获取字体
  * @param  ceFontGt:CeFontGt属性对象
  * @param  msg:欲获取字体
  * @param  outBuf:存放获取到的
  * @param  ceFontGtType:欲获取的字模类型
  * @return None
  */
void ceFontGt_getFontData(CeFontGt* ceFontGt, char* msgGBK, uint8* outBuf, CE_FONT_GT_TYPE ceTft320GBKType)
{
    int     i = 0;
    uint32  address = 0;
    uint32  baseAddress = 0;
    uint8   readBuf[32] = {0};
    uint8   j, m, index, temp;

    if (((uint8)msgGBK[i] == 0xA9) && ((uint8)msgGBK[i + 1] >= 0xA1))
    {
        address = (282 + (msgGBK[i + 1] - 0xA1)) * 32 + baseAddress;
    }
    else if (((uint8)msgGBK[i] >= 0xA4) && ((uint8)msgGBK[i] <= 0xA9) && ((uint8)msgGBK[i + 1] >= 0xA1))
    {
        address = ((msgGBK[i] - 0xA1) * 94 + (msgGBK[i + 1] - 0xA1)) * 32 + baseAddress;
    }
    else if (((uint8)msgGBK[i] >= 0xA1) && ((uint8)msgGBK[i] <= 0xA9) && ((uint8)msgGBK[i + 1] >= 0xA1))
    {
        address = ((msgGBK[i] - 0xA1) * 94 + (msgGBK[i + 1] - 0xA1)) * 32 + baseAddress;
    }
    else if (((uint8)msgGBK[i] >= 0xB0) && ((uint8)msgGBK[i] <= 0xF7) && ((uint8)msgGBK[i + 1] >= 0xA1))
    {
        address = ((msgGBK[i] - 0xB0) * 94 + (msgGBK[i + 1] - 0xA1) + 846) * 32 + baseAddress;
    }
    else
    {
        address = ((msgGBK[i] - 0xA1) * 94 + (msgGBK[i + 1] - 0xA1)) * 32 + baseAddress;
    }

    ceSpiMasterOp.resetNSSBit(&(ceFontGt->ceSpiMaster));
    ceSpiMasterOp.writeReadByte(&(ceFontGt->ceSpiMaster), 0x03);//0x03指令为一般读取，还有快速读取(一次读取多个)

    ceSpiMasterOp.writeReadByte(&(ceFontGt->ceSpiMaster), (address >> 16) & 0xFF);
    ceSpiMasterOp.writeReadByte(&(ceFontGt->ceSpiMaster), (address >> 8) & 0xFF);
    ceSpiMasterOp.writeReadByte(&(ceFontGt->ceSpiMaster), (address) & 0xFF);
    for (i = 0; i < 32; i++)
    {
        readBuf[i] = ceSpiMasterOp.writeReadByte(&(ceFontGt->ceSpiMaster), 0xFF);
    }
    ceSpiMasterOp.setNSSBit(&(ceFontGt->ceSpiMaster));

    for (m = 0; m < 2; m++)
    {
        for (j = 0; j < 2; j++)
        {
            index = 0x01;
            for (i = 0; i < 8; i++)
            {
                temp = 0;
                temp |= (((readBuf[0 + j * 8 + m * 16] & index) == 0) ? 0x80 : 0x00);
                temp |= (((readBuf[1 + j * 8 + m * 16] & index) == 0) ? 0x40 : 0x00);
                temp |= (((readBuf[2 + j * 8 + m * 16] & index) == 0) ? 0x20 : 0x00);
                temp |= (((readBuf[3 + j * 8 + m * 16] & index) == 0) ? 0x10 : 0x00);
                temp |= (((readBuf[4 + j * 8 + m * 16] & index) == 0) ? 0x08 : 0x00);
                temp |= (((readBuf[5 + j * 8 + m * 16] & index) == 0) ? 0x04 : 0x00);
                temp |= (((readBuf[6 + j * 8 + m * 16] & index) == 0) ? 0x02 : 0x00);
                temp |= (((readBuf[7 + j * 8 + m * 16] & index) == 0) ? 0x01 : 0x00);
                index <<= 1;
                outBuf[i * 2 + j + m * 16] = temp;
            }
        }
    }
}

/**
  * @brief  CeFontGt模块操作对象定义
  */
const CeFontGtOp ceFontGtOp = {ceFontGt_initial, ceFontGt_getFontData};

#ifdef __cplusplus
}
#endif //__cplusplus

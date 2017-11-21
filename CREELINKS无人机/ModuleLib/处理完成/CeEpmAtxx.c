/**
  ******************************************************************************
  * @file    CeEpmAtxx.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeEpmAtxx模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeEpmAtxx.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_EPM_ATXX_DEV_WRITE   0xA0
#define CE_EPM_ATXX_DEV_READ    0xA1
/**
  * @brief  CeEpmAtxx模块初始化
  * @param  ceEpmAtxx:CeEpmAtxx属性对象
  * @param  ceI2c:CeEpmAtxx模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceEpmAtxx_initial(CeEpmAtxx* ceEpmAtxx, CE_RESOURCE ceI2c)
{
    ceEpmAtxx->ceI2cMaster.ceResource = ceI2c;
    ceEpmAtxx->ceI2cMaster.ceI2cMasterSpeed = CE_I2C_SPEED_3_4MBPS;
    ceI2cMasterOp.initial(&ceEpmAtxx->ceI2cMaster);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief 向指定地址中写数据
  * @param ceEpmAtxx:CeEpmAtxx属性对象指针
  * @param address:需要写入的地址
  * @param data:需要写入的数据
  */
void ceEpmAtxx_writeByte(CeEpmAtxx* ceEpmAtxx, uint16 address, uint8 data)
{
    ceI2cMasterOp.start(&(ceEpmAtxx->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), CE_EPM_ATXX_DEV_WRITE); //发送写命令并检查应答位
    if (ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster)) == CE_STATUS_SUCCESS)
    {
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), (uint8)(address >> 8) & 0x00FF); //发送地址
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), (uint8)(address & 0x00FF)); //发送地址
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), data); //发送数据
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
    }
    ceI2cMasterOp.stop(&(ceEpmAtxx->ceI2cMaster));
}

/**
  * @brief 从指定地址中读数据
  * @param ceEpmAtxx:CeEpmAtxx属性对象指针
  * @param address:需要读的地址
  * @param data:需要读的数据
  */
uint8 ceEpmAtxx_readByte(CeEpmAtxx* ceEpmAtxx, uint16 address)
{
    uint8 data;
    ceI2cMasterOp.start(&(ceEpmAtxx->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), CE_EPM_ATXX_DEV_WRITE); //发送写命令并检查应答位
    if (ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster)) == CE_STATUS_SUCCESS)
    {
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), (uint8)(address >> 8) & 0x00FF); //发送地址
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), (uint8)(address & 0x00FF)); //发送地址
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        ceI2cMasterOp.start(&(ceEpmAtxx->ceI2cMaster)); //重启总线
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), CE_EPM_ATXX_DEV_READ); //发送读命令
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        data = ceI2cMasterOp.readByte(&(ceEpmAtxx->ceI2cMaster), 0x00); //读数据后发送非应答信号结束通讯
    }
    ceI2cMasterOp.stop(&(ceEpmAtxx->ceI2cMaster));
    return data;
}

/**
  * @brief 向指定起始地址中，连接写入数据
  * @param ceEpmAtxx:CeEpmAtxx属性对象指针
  * @param startAddress:需写入的起始地址
  * @param dataInBuf:需写入的数据缓存
  * @param dataInBufSize:需写入的数据长度
  * @return 实际写入的数据长度
  */
uint16 ceEpmAtxx_writeData(CeEpmAtxx* ceEpmAtxx, uint16 startAddress, uint8* dataInBuf, uint16 dataInBufSize)
{
    uint16 t;
    for(t=0;t<dataInBufSize;t++)
    {
        ceEpmAtxx_writeByte(ceEpmAtxx, startAddress + t, dataInBuf[t]);
        ceSystemOp.delayMs(2);//不加延时写入会失败...
    }
    return t;
}

/**
  * @brief 向指定起始地址中，连接读取数据
  * @param ceEpmAtxx:CeEpmAtxx属性对象指针
  * @param ceI2x:CeEpmAtxx模块使用的资源号
  * @param startAddress:需读取的起始地址
  * @param dataOutBuf:需读取的数据缓存
  * @param dataOutBufSize:需读取的数据长度
  * @return 实际读取到的数据长度
  */
uint16 ceEpmAtxx_readData(CeEpmAtxx* ceEpmAtxx, uint16 startAddress, uint8* dataOutBuf, uint16 dataOutBufSize)
{
    uint16 t;
    for(t=0;t<dataOutBufSize;t++)
    {
        dataOutBuf[t] = ceEpmAtxx_readByte(ceEpmAtxx, startAddress + t);
    }
    return t;
}

CeEpmAtxxOp ceEpmAtxxOp = {ceEpmAtxx_initial, ceEpmAtxx_writeByte, ceEpmAtxx_readByte, ceEpmAtxx_writeData, ceEpmAtxx_readData};

#ifdef __cplusplus
 }
#endif //__cplusplus

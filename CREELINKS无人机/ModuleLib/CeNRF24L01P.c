/**
  ******************************************************************************
  * @file    CeNRF24L01P.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeNRF24L01P模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)24L01的最大SPI时钟为10Mhz
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeNRF24L01P.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/*!< NRF24L01相关的宏定义*/
#define CE_NRF24L01P_TX_ADR_WIDTH    5         /*!< 5 uints TX address width*/
#define CE_NRF24L01P_RX_ADR_WIDTH    5         /*!< 5 uints RX address width*/

#define CE_NRF24L01P_RX_PLOAD_WIDTH  32        /*!< 32 uints TX payload*/
#define CE_NRF24L01P_TX_PLOAD_WIDTH  32        /*!< 32 uints TX payload*/
/*!< NRF24L01寄存器指令*/
#define CE_NRF24L01P_NRF_READ_REG    0x00      /*!< 读寄存器指令*/
#define CE_NRF24L01P_NRF_WRITE_REG   0x20     /*!< 写寄存器指令*/
#define CE_NRF24L01P_RD_RX_PLOAD     0x61      /*!< 读取接收数据指令*/
#define CE_NRF24L01P_WR_TX_PLOAD     0xA0      /*!< 写待发数据指令*/
#define CE_NRF24L01P_FLUSH_TX        0xE1     /*!< 冲洗发送 FIFO指令*/
#define CE_NRF24L01P_FLUSH_RX        0xE2      /*!< 冲洗接收 FIFO指令*/
#define CE_NRF24L01P_REUSE_TX_PL     0xE3      /*!< 定义重复装载数据指令*/
#define CE_NRF24L01P_NOP             0xFF     /*!< 保留*/
/*!< SPI(nRF24L01)寄存器地址*/
#define CE_NRF24L01P_CONFIG          0x00     /*!< 配置寄存器，CRC校验模式以及收发状态响应方式*/
#define CE_NRF24L01P_EN_AA           0x01     /*!< 使能自动应答功能*/
#define CE_NRF24L01P_EN_RXADDR       0x02     /*!< 接收数据通道允许*/
#define CE_NRF24L01P_SETUP_AW        0x03     /*!< 收发地址宽度设置*/
#define CE_NRF24L01P_SETUP_RETR      0x04     /*!< 自动重发功能设置*/
#define CE_NRF24L01P_RF_CH           0x05     /*!< 射频通道*/
#define CE_NRF24L01P_RF_SETUP        0x06     /*!< 射频寄存器*/
#define CE_NRF24L01P_STATUS          0x07     /*!< 状态寄存器*/
#define CE_NRF24L01P_OBSERVE_TX      0x08     /*!< 发送检测寄存器*/
#define CE_NRF24L01P_CD              0x09     /*!< 载波检测*/
#define CE_NRF24L01P_RX_ADDR_P0      0x0A     /*!< 频道0接收数据地址*/
#define CE_NRF24L01P_RX_ADDR_P1      0x0B     /*!< 频道1接收数据地址*/
#define CE_NRF24L01P_RX_ADDR_P2      0x0C     /*!< 频道2接收数据地址*/
#define CE_NRF24L01P_RX_ADDR_P3      0x0D     /*!< 频道3接收数据地址*/
#define CE_NRF24L01P_RX_ADDR_P4      0x0E     /*!< 频道4接收数据地址*/
#define CE_NRF24L01P_RX_ADDR_P5      0x0F     /*!< 频道5接收数据地址*/
#define CE_NRF24L01P_TX_ADDR         0x10     /*!< 发送地址寄存器*/
#define CE_NRF24L01P_RX_PW_P0        0x11     /*!< 接收频道0有效数据宽度设置寄存器*/
#define CE_NRF24L01P_RX_PW_P1        0x12     /*!< 接收频道1有效数据宽度设置寄存器*/
#define CE_NRF24L01P_RX_PW_P2        0x13     /*!< 接收频道2有效数据宽度设置寄存器*/
#define CE_NRF24L01P_RX_PW_P3        0x14     /*!< 接收频道3有效数据宽度设置寄存器*/
#define CE_NRF24L01P_RX_PW_P4        0x15     /*!< 接收频道4有效数据宽度设置寄存器*/
#define CE_NRF24L01P_RX_PW_P5        0x16     /*!< 接收频道5有效数据宽度设置寄存器*/
#define CE_NRF24L01P_FIFO_STATUS     0x17     /*!< FIFO栈入栈出状态寄存器设置*/
/*!< 中断标志位*/
#define CE_NRF24L01P_RX_DR            6       /*!< 接收到数据中断。中断有效时为1，写1清除中断*/
#define CE_NRF24L01P_TX_DS            5       /*!< 数据发送完成中断*/
#define CE_NRF24L01P_MAX_RT           4       /*!< 重发次数超过设定值中断。中断有效时为1，写1清除中断*/

#define CE_NRF24L01P_MAX_TX      0x10  
#define CE_NRF24L01P_TX_OK       0x20  
#define CE_NRF24L01P_RX_OK       0x40 

#define CE_NRF24L01P_IDLE     0x00      /*!< 空闲标志*/
#define CE_NRF24L01P_RECV     0x01      /*!< 接收状态*/
#define CE_NRF24L01P_SEND     0x02      /*!< 发送状态*/


uint8 ceNRF24L01P_rxPacket(CeNRF24L01P* ceNRF24L01P);
/**
  * @brief  Task任务回调函数，用于处理接收数据
  * @param  pAddr:CeNRF24L01P属性对象指针
  * @return None
  */
void ceNRF24L01P_intCallBack(void* pAddr)
{
    int8 pipiIndex = 0x00;
    CeNRF24L01P* ceNRF24L01P = (CeNRF24L01P*)pAddr;
    pipiIndex = ceNRF24L01P_rxPacket(ceNRF24L01P);    
    if (pipiIndex >= 0x01 && pipiIndex < 0x07)//判断是否正常接收数据
    {
        pipiIndex -= 1;
        if(ceNRF24L01P->callBackRecv[pipiIndex] != CE_NULL)
        {
            ceNRF24L01P->callBackRecv[pipiIndex](ceNRF24L01P->recvBuf, CE_NRF24L01P_RX_PLOAD_WIDTH);
        }
    }
}
/**
  * @brief  通过SPI向NRF指定寄存器写入数据
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @param  reg:欲写入数据的指定寄存器地址
  * @return 返回写入寄存器前寄存器的内容
  */
uint8 ceNRF24L01P_writeReg(CeNRF24L01P* ceNRF24L01P, uint8 reg, uint8 val)
{
    uint8 status;
    ceSpiMasterOp.resetNSSBit(&(ceNRF24L01P->ceSpiMaster));
    status = ceSpiMasterOp.writeReadByte(&(ceNRF24L01P->ceSpiMaster), reg);
    ceSpiMasterOp.writeReadByte(&(ceNRF24L01P->ceSpiMaster), val);
    ceSpiMasterOp.setNSSBit(&(ceNRF24L01P->ceSpiMaster));
    return status;
}

/**
  * @brief  通过SPI从NRF读取指定寄存器的数据
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @param  reg:欲读取的指定寄存器地址
  * @return 返回读取到的寄存器的内容
  */
uint8 ceNRF24L01P_readReg(CeNRF24L01P* ceNRF24L01P, uint8 reg)
{
    uint8 reg_val;
    ceSpiMasterOp.resetNSSBit(&(ceNRF24L01P->ceSpiMaster));
    ceSpiMasterOp.writeReadByte(&(ceNRF24L01P->ceSpiMaster), reg);
    reg_val = ceSpiMasterOp.writeReadByte(&(ceNRF24L01P->ceSpiMaster), 0x00);
    ceSpiMasterOp.setNSSBit(&(ceNRF24L01P->ceSpiMaster));
    return reg_val;
}

/**
  * @brief  通过SPI向NRF写入数据
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @param  reg:欲写入数据的寄存器地址
  * @param  pBuf:存放欲写入的数据的缓冲区
  * @param  bytes:指定欲写入数据的字节数
  * @return 返回操作的状态
  */
uint8 ceNRF24L01P_writeBuf(CeNRF24L01P* ceNRF24L01P, uint8 reg, uint8 *pBuf, uint8 bytes)
{
    uint8 status, i;
    ceSpiMasterOp.resetNSSBit(&(ceNRF24L01P->ceSpiMaster));
    status = ceSpiMasterOp.writeReadByte(&(ceNRF24L01P->ceSpiMaster), reg);
    for (i = 0; i<bytes; i++)
    {
        ceSpiMasterOp.writeReadByte(&(ceNRF24L01P->ceSpiMaster), *pBuf);
        pBuf++;
    }
    ceSpiMasterOp.setNSSBit(&(ceNRF24L01P->ceSpiMaster));
    return status;
}

/**
  * @brief  通过SPI从NRF中读取数据
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @param  reg:欲读取数据的寄存器地址
  * @param  pBuf:存放欲读取数据的缓冲区
  * @param  bytes:指定欲读取数据的字节数
  * @return 返回操作的状态
  */
uint8 ceNRF24L01P_readBuf(CeNRF24L01P* ceNRF24L01P, uint8 reg, uint8 *pBuf, uint8 bytes)
{
    uint8 status, i;
    ceSpiMasterOp.resetNSSBit(&(ceNRF24L01P->ceSpiMaster));
    status = ceSpiMasterOp.writeReadByte(&(ceNRF24L01P->ceSpiMaster), reg);
    for (i = 0; i < bytes; i++)
    {
        pBuf[i] = ceSpiMasterOp.writeReadByte(&(ceNRF24L01P->ceSpiMaster), 0xFF);
    }
    ceSpiMasterOp.setNSSBit(&(ceNRF24L01P->ceSpiMaster));
    return status;
}

/**
  * @brief  发生数据包
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @param  sendBuf:欲发生的数据包缓冲区
  * @param  bufSize:欲发生数据的字节长度
  * @return 返回操作的状态
  */
CE_STATUS ceNRF24L01P_txPacket(CeNRF24L01P* ceNRF24L01P, uint8* sendBuf, uint8 bufSize)
{
    u8 sta;
    uint8 tick = 0;
    ceIntOp.stop(&(ceNRF24L01P->ceInt));

    ceGpioOp.resetBit(&(ceNRF24L01P->ceGpio));
    ceSystemOp.delayUs(5);
    ceNRF24L01P_writeBuf(ceNRF24L01P,CE_NRF24L01P_WR_TX_PLOAD,sendBuf,CE_NRF24L01P_TX_PLOAD_WIDTH);
    ceNRF24L01P_writeReg(ceNRF24L01P,CE_NRF24L01P_NRF_WRITE_REG+CE_NRF24L01P_CONFIG,0x0e);
    ceGpioOp.setBit(&(ceNRF24L01P->ceGpio));//置高CE，激发数据发送   
    ceSystemOp.delayUs(20);
    while(ceIntOp.getBit(&(ceNRF24L01P->ceInt)) == 0x01)//等待Irq拉低，数据发送完成
    {
        tick++;
        ceSystemOp.delayMs(1);
        if(tick >= 10)
            break;
    }
    sta=ceNRF24L01P_readReg(ceNRF24L01P,CE_NRF24L01P_STATUS);    
    ceNRF24L01P_writeReg(ceNRF24L01P,CE_NRF24L01P_NRF_WRITE_REG+CE_NRF24L01P_STATUS,sta);

    ceIntOp.start(&(ceNRF24L01P->ceInt));    
        
    if((sta&CE_NRF24L01P_MAX_TX) != 0)
        {
        ceNRF24L01P_writeReg(ceNRF24L01P,CE_NRF24L01P_FLUSH_TX,0xff);
            return CE_STATUS_FAILE;
        }



    if(sta&CE_NRF24L01P_TX_OK)
    {
        return CE_STATUS_SUCCESS;//发送成功
    }
    return CE_STATUS_FAILE;
}

/**
  * @brief  接收数据包
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @return 返回操作的状态
  */
uint8 ceNRF24L01P_rxPacket(CeNRF24L01P* ceNRF24L01P)
{
    uint8 status = 0x00;
    status = ceNRF24L01P_readReg(ceNRF24L01P, CE_NRF24L01P_STATUS);//读取状态寄存其来判断数据接收状况
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_STATUS, status);//清除RX_DR中断
    if(status & (0x01 << CE_NRF24L01P_RX_DR))//接收数据中断
    {
        //读数据前应该先判断RX FIFO中是否存在有效数据，FIFO满和不满要分别处理。这样就不会读取到多余的数据了
        ceNRF24L01P_readBuf(ceNRF24L01P, CE_NRF24L01P_RD_RX_PLOAD, ceNRF24L01P->recvBuf, CE_NRF24L01P_RX_PLOAD_WIDTH);//读取数据，当读RX有效数据后，FIFO寄存器中有效数据被清空
        /*status = ceNRF24L01P_readReg(ceNRF24L01P, CE_NRF24L01P_OBSERVE_TX);//不知这里的操作是否有用，可以检测数据包是否丢失。By Lizhiyang 2016-11-16
        ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_OBSERVE_TX, status & 0x0F);//数据包丢失计数器清0
        (status & 0xF0);//数据包丢失计数器*/
        status = ((status & 0x0E) >> 1) + 1;//取出通道号
    }
    return status;
}



/**
  * @brief  设置发生模式
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @param  localAddress:指定本地接收使能ACK的节点地址
  * @param  sendToAddress:指定发生至的节点地址
  * @return 系统状态码
  */
void  ceNRF24L01P_setSendMode(CeNRF24L01P* ceNRF24L01P, uint8* localAddress, uint8* sendToAddress)
{
    ceGpioOp.resetBit(&(ceNRF24L01P->ceGpio));//Ce拉低，StandBy I模式
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_CONFIG, 0x08);//设置为初始状态
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_FLUSH_TX, 0xFF);                                            //清除TX FIFO寄存器
    ceNRF24L01P_writeBuf(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_TX_ADDR, sendToAddress, CE_NRF24L01P_TX_ADR_WIDTH);        //写TX节点地址
    ceNRF24L01P_writeBuf(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_RX_ADDR_P0, localAddress, CE_NRF24L01P_RX_ADR_WIDTH);     //设置RX节点地址,主要为了使能ACK
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_EN_AA, 0x3f);     //使能所有通道自动应答
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_EN_RXADDR, 0x3f); //使能所有通道的接收地址(这两项定义的通道数不得小于当前使用的通道数)
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_SETUP_RETR, 0x1A);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_RF_CH, 40);       //设置RF通道为40,收发必须一致！

    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_RX_PW_P0, CE_NRF24L01P_RX_PLOAD_WIDTH); 

    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_RF_SETUP, 0x0F);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启,收发必须一致！
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_CONFIG, 0x0E);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
    ceGpioOp.setBit(&(ceNRF24L01P->ceGpio));
    ceSystemOp.delayUs(20);
}

/**
  * @brief  设置接收模式
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @param  pipeIndex:欲操作的接收节点索引，0-5
  * @param  recvAddress:欲操作的接收节点的地址
  * @return 系统状态码
  */
void  ceNRF24L01P_setRecvMode(CeNRF24L01P* ceNRF24L01P, uint8 pipeIndex, uint8* recvAddress)
{
    ceGpioOp.resetBit(&(ceNRF24L01P->ceGpio));//Ce拉低，StandBy I模式
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_CONFIG, 0x08);//设置为初始状态
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_FLUSH_RX, 0xFF);

    ceNRF24L01P_writeBuf(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_TX_ADDR, recvAddress, CE_NRF24L01P_TX_ADR_WIDTH);

    if(pipeIndex <= 0x01)
    {
        ceNRF24L01P_writeBuf(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_RX_ADDR_P0 + pipeIndex, recvAddress, CE_NRF24L01P_RX_ADR_WIDTH);//写接收数据的地址
    }
    else
    {
        ceNRF24L01P_writeBuf(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_RX_ADDR_P1, recvAddress, CE_NRF24L01P_RX_ADR_WIDTH); //设置RX节点地址,主要为了使能ACK
        ceNRF24L01P_writeBuf(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + (CE_NRF24L01P_RX_ADDR_P0 + pipeIndex), recvAddress, 1);  //设置RX节点地址,主要为了使能ACK(地址长度只能是1，不能多写，写一样的值也不行)
    }
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_EN_AA, 0x3F << pipeIndex);    //使能通道的自动应答
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_EN_RXADDR, 0x3F << pipeIndex);//使能通道的接收地址
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_RF_CH, 40);                   //设置RF通信频率
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + (CE_NRF24L01P_RX_PW_P0 + pipeIndex), CE_NRF24L01P_RX_PLOAD_WIDTH);      //选择通道0的有效数据宽度
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_RF_SETUP, 0x0F);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
    ceNRF24L01P_writeReg(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_CONFIG, 0x0F);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
    ceGpioOp.setBit(&(ceNRF24L01P->ceGpio));//进入接收模式(进入接收模式后130us后才开始检测空中信号，所有接收模式时应一直保持CE为高)
}

/**
  * @brief  通过SPI读写寄存器来判断NRF芯片是否正常连接
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @return 系统状态码
  */
CE_STATUS ceNRF24L01P_check(CeNRF24L01P* ceNRF24L01P)
{
    uint8 writeBuf[5] = {0xC2, 0xC3, 0xC4, 0xC5, 0xC6};
    uint8 readBuf[5] = { 0 };
    uint8 i = 0;
    ceNRF24L01P_writeBuf(ceNRF24L01P, CE_NRF24L01P_NRF_WRITE_REG + CE_NRF24L01P_TX_ADDR, writeBuf, 5);//写入5个字节的地址
    ceNRF24L01P_readBuf(ceNRF24L01P, CE_NRF24L01P_TX_ADDR, readBuf, 5);//读出写入的地址        
    for (i = 0; i < 5; i++)//比较
    {
        if (writeBuf[i] != readBuf[i] && i == 4)
        {
            return CE_STATUS_INITIAL_FALSE;
        }
    }
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeNRF24L01P模块初始化
  * @param  ceNRF24L01P:CeNRF24L01P属性对象
  * @param  ceSpi:CeNRF24L01P模块使用的Spi资源号
  * @param ceGpio:模块使用的ceGpio资源号
  * @param ceInt:模块使用的ceInt资源号
  * @return 返回CE_STATUS_SUCCESS表示初始化成功，返回CE_STATUS_INITIAL_FALSE表示未检测到NRF芯片
  */
CE_STATUS ceNRF24L01P_initial(CeNRF24L01P* ceNRF24L01P, CE_RESOURCE ceSpi,CE_RESOURCE ceGpio,CE_RESOURCE ceInt)
{
    ceNRF24L01P->status = CE_NRF24L01P_IDLE;
    ceNRF24L01P->callBackRecv[0] = CE_NULL;

    ceNRF24L01P->ceSpiMaster.ceResource = ceSpi;
    ceNRF24L01P->ceSpiMaster.ceSpiMasterSpeed = CE_SPI_MASTER_SPEED_10MBPS;
    ceNRF24L01P->ceSpiMaster.ceSpiMasterClockPhase = CE_SPI_MASTER_CLOCK_PHASE_1Edge;
    ceNRF24L01P->ceSpiMaster.ceSpiMasterClockPolarity = CE_SPI_MASTER_CLOCK_POLARITY_LOW;
    ceSpiMasterOp.initial(&(ceNRF24L01P->ceSpiMaster));
    ceSpiMasterOp.start(&(ceNRF24L01P->ceSpiMaster));

    ceNRF24L01P->ceGpio.ceResource = ceGpio;
    ceNRF24L01P->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceNRF24L01P->ceGpio));
    ceGpioOp.resetBit(&(ceNRF24L01P->ceGpio));//Ce拉低，StandBy I模式

    ceNRF24L01P->ceInt.ceResource = ceInt;
    ceNRF24L01P->ceInt.callBack=ceNRF24L01P_intCallBack;
    ceNRF24L01P->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_FALLING;
    ceNRF24L01P->ceInt.pAddPar = ceNRF24L01P;
    ceIntOp.initial(&(ceNRF24L01P->ceInt));//IRQ，低电平标志中断有效
    ceIntOp.start(&(ceNRF24L01P->ceInt));
    ceIntOp.stop(&(ceNRF24L01P->ceInt));
    ceIntOp.start(&(ceNRF24L01P->ceInt));

    return ceNRF24L01P_check(ceNRF24L01P);
}

/**
  * @brief  进入发送模式，发送操作完成后，函数才返回
  * @param  ceNRF24L01P:CeNRF24L01P属性对象指针
  * @param  sendAddress:发送地址，与接收端6个接收通道中的一个相同
  * @param  dataBuf:要发送的数据缓存区
  * @param  dataBufSize:要发送的数据长度，注意：一定要为CE_NRF24L01P_PACKET_LENGTH的整数倍
  * @return 返回CE_STATUS_SUCCESS则表明发送成功，其它则表明发送失败
  */
CE_STATUS ceNRF24L01P_send(CeNRF24L01P* ceNRF24L01P, uint8* sendAddress, uint8* dataBuf, uint16 dataBufSize)
{
    if (ceNRF24L01P->status != CE_NRF24L01P_SEND)
    {
        ceNRF24L01P->status = CE_NRF24L01P_SEND;
    }
    ceNRF24L01P_setSendMode(ceNRF24L01P, sendAddress, sendAddress);
    return ceNRF24L01P_txPacket(ceNRF24L01P, dataBuf, CE_NRF24L01P_PACKET_LENGTH);
}

/**
  * @brief  进入接收状态，开始接收数据。注意：当调用send函数后，一定要再次调用此函数才能实现数据接收，异步执行，函数直接返回。
  * @param  ceNRF24L01P:CeNRF24L01P属性对象指针
  * @param pipeIndex:模块共有6个可用接收通道，范围0-5，此值指定使用哪个接收通道接收数据，如果要使用多个接收通道接收数据，则可重复调用此函数多次
  * @param recvAddress:接收通道对应的接收地址，接收地址有详细规则，详细阅读模块手册
  * @param callBackRecv:当对应通道接收到数据后，调用的回调函数，每个通道的回调函数均独立
  * @return 返回CE_STATUS_SUCCESS则表明配置成功，返回CE_STATUS_PAR_ERROR表示参数错误，其它则表明配置失败
  */
CE_STATUS ceNRF24L01P_recv(CeNRF24L01P* ceNRF24L01P, uint8 pipeIndex, uint8* recvAddress, void(callBackRecv)(uint8* dataBuf, uint16 dataBufSize))
{
    if(pipeIndex > 5)
    {
        return CE_STATUS_PAR_ERROR;
    }
    ceNRF24L01P->status = CE_NRF24L01P_RECV;
    ceNRF24L01P->callBackRecv[pipeIndex] = callBackRecv;
    ceNRF24L01P_setRecvMode(ceNRF24L01P, pipeIndex, recvAddress);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief    CeNRF24L01P模块操作对象定义
  */
const CeNRF24L01POpBase ceNRF24L01POp = {ceNRF24L01P_initial, ceNRF24L01P_send, ceNRF24L01P_recv};

#ifdef __cplusplus
}
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeEpmAtxx.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeEpmAtxx模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_EPM_ATXX_H__
#define __CE_EPM_ATXX_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_EPM_ATXX_VERSION__ 1                                           /*!< 此驱动文件的版本号*/
#define __CE_EPM_ATXX_NEED_CREELINKS_VERSION__ 1                            /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_EPM_ATXX_NEED_CREELINKS_VERSION__)     /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeFlsWxxx.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
//#define CE_EPM_ATXX_USE_AT24C01   127     /*!< CeEpmAtxx操作的芯片型号为AT24C01，容量为126字节，地址为8位，具有8字节数据的页面写能力*/
#define CE_EPM_ATXX_USE_AT24C02     255     /*!< CeEpmAtxx操作的芯片型号为AT24C02，容量为256字节，地址为8位，具有8字节数据的页面写能力*/
//#define CE_EPM_ATXX_USE_AT24C04   511     /*!< CeEpmAtxx操作的芯片型号为AT24C04，容量为512字节，地址为16位，具有16字节数据的页面写能力*/
//#define CE_EPM_ATXX_USE_AT24C08   1023
//#define CE_EPM_ATXX_USE_AT24C16   2047
//#define CE_EPM_ATXX_USE_AT24C32   4095
//#define CE_EPM_ATXX_USE_AT24C64   8191
//#define CE_EPM_ATXX_USE_AT24C128  16383
//#define CE_EPM_ATXX_USE_AT24C256  32768
//#define CE_EPM_ATXX_USE_AT24C512  65535
/*
 *CeEpmAtxx属性对像
 */
typedef struct
{
    CeI2cMaster ceI2cMaster;
}CeEpmAtxx;
/*
 *CeEpmAtxx操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeEpmAtxx* ceEpmAtxx, CE_RESOURCE ceI2c);    /*!< @brief CeEpmAtxx模块初始化
                                                                             @param ceEpmAtxx:CeEpmAtxx属性对象指针
                                                                             @param ceI2x:CeEpmAtxx模块使用的资源号*/

    void        (*writeByte)(CeEpmAtxx* ceEpmAtxx, uint16 address, uint8 data);/*!<
                                                                             @brief 向指定地址中写数据
                                                                             @param ceEpmAtxx:CeEpmAtxx属性对象指针
                                                                             @param address:需要写入的地址
                                                                             @param data:需要写入的数据*/

    uint8       (*readByte)(CeEpmAtxx* ceEpmAtxx, uint16 address);      /*!< @brief 从指定地址中读数据
                                                                             @param ceEpmAtxx:CeEpmAtxx属性对象指针
                                                                             @param address:需要读的地址
                                                                             @param data:需要读的数据*/

    uint16      (*writeData)(CeEpmAtxx* ceEpmAtxx, uint16 startAddress, uint8* dataInBuf, uint16 dataInBufSize);/*!<
                                                                             @brief 向指定起始地址中，连接写入数据
                                                                             @param ceEpmAtxx:CeEpmAtxx属性对象指针
                                                                             @param startAddress:需写入的起始地址
                                                                             @param dataInBuf:需写入的数据缓存
                                                                             @param dataInBufSize:需写入的数据长度
                                                                             @return 实际写入的数据长度*/

    uint16      (*readData)(CeEpmAtxx* ceEpmAtxx, uint16 startAddress, uint8* dataOutBuf, uint16 dataOutBufSize);/*!<
                                                                             @brief 向指定起始地址中，连接读取数据
                                                                             @param ceEpmAtxx:CeEpmAtxx属性对象指针
                                                                             @param ceI2x:CeEpmAtxx模块使用的资源号
                                                                             @param startAddress:需读取的起始地址
                                                                             @param dataOutBuf:需读取的数据缓存
                                                                             @param dataOutBufSize:需读取的数据长度
                                                                             @return 实际读取到的数据长度*/
}CeEpmAtxxOp;
/*
 *CeEpmAtxx操作对象实例
 */
extern CeEpmAtxxOp ceEpmAtxxOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_EPM_ATXX_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_EPM_ATXX_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 向Eeprom中写数据，再读取后，校验定入与读取的值是否相同
******************************************************************************
#include "Creelinks.h"
#include "CeEpmAtxx.h"
CeEpmAtxx myEpm;                                //定义属性对象
uint8 sendBuf[10] = {1,2,3,4,5,6,7,8,9,0};
uint8 recvBuf[10];
uint8 i;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceEpmAtxxOp.initial(&myEpm,R2TI2c);         //使用R2TI2c初始化并注册事件回调函数
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceEpmAtxxOp.writeData(&myEpm, 0x16, sendBuf, 10);   //向Eeprom中写数据
        ceEpmAtxxOp.readData(&myEpm, 0x16, recvBuf, 10);    //从Eeprom中读数据
        for (i = 0; i < 10; i++)
        {
            if (sendBuf[i] == recvBuf[i])
            {
                ceDebugOp.printf("Right In: Write:%d, Read:%d\n", sendBuf[i], recvBuf[i]);
            }
            else
            {
                 ceDebugOp.printf("Error In: Write:%d, Read:%d\n", sendBuf[i], recvBuf[i]);
            }
        }
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeWlsRfid.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeWlsRfid模扇区的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)initialSection的功能暂未实现，实现起来需要看手册，比较麻烦，闲了在整。
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_WLS_RFID_H__
#define __CE_WLS_RFID_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_WLS_RFID_VERSION__ 1                                            /*!< 此驱动文件的版本号*/
#define __CE_WLS_RFID_NEED_CREELINKS_VERSION__ 18                            /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_WLS_RFID_NEED_CREELINKS_VERSION__)      /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeWlsRfid.h需要高于18以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

/**
  * @brief  枚举，CeWlsRfid对象支持的卡片类型
  */
typedef enum
{
    CE_WLS_RFID_CARD_TYPE_MIFARE_ULTRALIGHT =    0x4400, /*!< Mifare_UltraLight*/
    CE_WLS_RFID_CARD_TYPE_MIFARE_ONE_S50 =       0x0400, /*!< Mifare_One(S50)*/
    CE_WLS_RFID_CARD_TYPE_MIFARE_ONE_S70 =       0x0200, /*!< Mifare_One(S70)*/
    CE_WLS_RFID_CARD_TYPE_MIFARE_PRO_X =         0x0800, /*!< Mifare_Pro(X)*/
    CE_WLS_RFID_CARD_TYPE_MIFARE_DESFIRE =       0x4403, /*!< Mifare_DESFire*/
    CE_WLS_RFID_CARD_TYPE_OTHER,                         /*!< 其它符合14443A标准的卡*/
}CE_WLS_RFID_CARD_TYPE;

/*
 * @brief  结构体，CeWlsRfid对象用于存储卡片信息的结构体
 */
typedef struct
{
    CE_WLS_RFID_CARD_TYPE     cardType;                 /*!< 存储当前与模块连接卡片的卡片类型*/
    uint8                    serialNumber[4];           /*!< 存储当前与模块连接卡片的唯一序列号，32位*/
}CeWlsRfidCardInfo;

/*
 *CeWlsRfid属性对像
 */
typedef struct
{
    CeSpiMaster         ceSpiMaster;                    /*!< 模块使用的SpiMaster资源属性对象*/
    CeGpio              ceGpioRst;                      /*!< 模块使用的Gpio资源对象，用于控制模块的复位*/
    CeWlsRfidCardInfo    ceWlsRfidCardInfo;             /*!< 存放当前与模块连接卡片的信息结构体*/
}CeWlsRfid;
/*
 *CeWlsRfid操作对像
 */
typedef struct
{
    CE_STATUS           (*initial)(CeWlsRfid* ceWlsRfid,CE_RESOURCE ceSpi,CE_RESOURCE ceGpio);/*!<
                                                             @brief CeRfidR模块初始化
                                                             @param ceWlsRfid:ceWlsRfid属性对象指针
                                                             @param ceSpi:ceWlsRfid模块使用的Spi资源号
                                                             @param ceGpio:ceWlsRfid模块使用的Gpio资源号*/

    CE_STATUS           (*setOn)(CeWlsRfid* ceWlsRfid); /*!< @brief 使CeWlsRfid模块进行工作状态
                                                             @param ceWlsRfid:ceWlsRfid属性对象指针*/

    CeWlsRfidCardInfo*  (*connectCard)(CeWlsRfid* ceWlsRfid);/*!<
                                                             @brief 在CeWlsRfid可感应的周围摸查卡，此函数应放在循环里周期调用
                                                             @param ceWlsRfid:ceWlsRfid属性对象指针
                                                             @return 返回CE_NULL:表示未在周围找到卡，否则返回找到的卡信息*/

    CE_STATUS           (*initialSection)(CeWlsRfid* ceWlsRfid, uint8 blockIndex, char* defaultPasswordA, char* defaultPasswordB, char* newPasswordARead, char* newPasswordBWrite);/*!<
                                                             @brief 初始化一个未使用过的新扇区，或修改一个扇区的密码A和B
                                                             @param blockIndex:要写入的扇区索引，S50卡为1~15，注第0扇区不可写
                                                             @param defaultPasswordA:IC卡出厂时的密码默认A，6个字节;
                                                             @param defaultPasswordB:IC卡出厂时的密码默认B，6个字节
                                                             @param newPasswordARead:新设置的密码A，这里设置为读密码，6个字节;
                                                             @param newPasswordBWrite:新设置的密码B，这里设置为写密码，6个字节
                                                             @return CE_STATUS_SUCCESS:操作成功;CE_STATUS_PAR_ERROR:转入的参数错误;CE_STATUS_FAILE:操作失败，可能初始密码不正确*/

    CE_STATUS           (*readSection)(CeWlsRfid* ceWlsRfid, uint8 sectorIndex, uint8 blockIndex, char* passwordARead, char* dataOut);/*!<
                                                             @brief 读取指定块中的数据，块大小为16字节
                                                             @param sectorIndex:欲操作块的扇区索引，S50卡为0~15
                                                             @param blockIndex:欲操作块的索引，S50卡每个扇区可用于储存数据的块为0-2
                                                             @param passwordBRead:读密码，密码正确才允许读数据，6个字节
                                                             @param dataOut:用户提供的读数据缓存区，针对S50卡容量必须大于等于16
                                                             @return CE_STATUS_SUCCESS:操作成功;CE_STATUS_PAR_ERROR:传入的参数错误;CE_STATUS_FAILE:操作失败，可能密码不正确*/

    CE_STATUS           (*writeSection)(CeWlsRfid* ceWlsRfid, uint8 sectorIndex, uint8 blockIndex, char* passwordBWrite, char* dataIn);/*!<
                                                             @brief 往指定块中写入数据，块大小为16个字节
                                                             @param sectorIndex:欲操作块的扇区索引，S50卡为1~15，注：第0扇区不可写（存放厂商代码，已经固化，不可更改）
                                                             @param blockIndex:欲操作块的索引，S50卡每个扇区可用于储存数据的块为0-2
                                                             @param passwordBWrite:写密码，6个字节，密码正确才可写入
                                                             @param dataIn:待写入的数据,长度为16个字节，不足16的需要用户填充到16个字节。
                                                             @return CE_STATUS_SUCCESS:操作成功;CE_STATUS_PAR_ERROR:传入的参数错误;CE_STATUS_FAILE:操作失败，可能密码不正确或传入的扇区不可写*/

    CE_STATUS           (*releaseCard)(CeWlsRfid* ceWlsRfid);/*!<
                                                             @brief 释放一个已经操作完成的卡片连接,并使其处于休眠状态，
                                                             @param ceWlsRfid:ceWlsRfid属性对象指针*/

    CE_STATUS           (*setOff)(CeWlsRfid* ceWlsRfid);/*!< @brief 使CeWlsRfid模块进行低功耗状态
                                                             @param ceWlsRfid:ceWlsRfid属性对象指针*/
}CeWlsRfidOpBase;
/*
 *CeWlsRfid操作对象实例
 */
extern CeWlsRfidOpBase ceWlsRfidOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_WLS_RFID_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_WLS_RFID_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境)
* @function 创建Rfid读卡器，等待与卡片连接。连接上之后打印卡片的类型及唯一序列号，而后用默认密码进行扇区读写操作
******************************************************************************
#include "Creelinks.h"
#include "CeWlsRfid.h"
CeWlsRfid myWlsRfid;
CeWlsRfidCardInfo* ceWlsRfidCardInfo;
char defaultPasswordA[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
char writeBuffer[16] = { 0 };
char readBuffer[16]  = { 0 };
uint32 serialNumber = 0x00000000;
CE_STATUS ceStatus = CE_STATUS_SUCCESS;
int i = 0;
int main(void)
{
    ceSystemOp.initial();                        //Creelinks环境初始化
    ceSystemOp.initialDebug(R9Uart);             //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作

    ceWlsRfidOp.initial(&myWlsRfid, R12Spi, R4AG); //使用R12Spi资源和R4AG资源初始化
    ceWlsRfidOp.setOn(&myWlsRfid);                 //是模块进入工作状态

    while (1)
    {
        ceSystemOp.mainTask();                  //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceWlsRfidCardInfo = ceWlsRfidOp.connectCard(&myWlsRfid);//等待卡片连接
        if (ceWlsRfidCardInfo != CE_NULL)
        {
            serialNumber =  (ceWlsRfidCardInfo->serialNumber[0] & 0x000000FF) << 24;//将卡片唯一序列号转为uin32，方便通过十六进制打印输出
            serialNumber |= (ceWlsRfidCardInfo->serialNumber[1] & 0x000000FF) << 16;
            serialNumber |= (ceWlsRfidCardInfo->serialNumber[2] & 0x000000FF) << 8;
            serialNumber |= (ceWlsRfidCardInfo->serialNumber[3] & 0x000000FF);
            ceSystemOp.printf("CeWlsRfid findCard\nCardInfo: Type: 0x%X ID: 0x%X\n", ceWlsRfidCardInfo->cardType, serialNumber);//打印当前连接的卡片类型及唯一序列号

            for(i = 0; i < 16; i++)
            {
                writeBuffer[i] = 0xAA + i;//设置写缓冲区的数据
                readBuffer[i] = 0x00;     //清空读缓冲区
            }

            do
            {
                ceStatus = ceWlsRfidOp.writeSection(&myWlsRfid, 2, 1, defaultPasswordA, writeBuffer);//往指定扇区的指定块中写入数据
                if(ceStatus != CE_STATUS_SUCCESS)
                {
                    ceSystemOp.printf("CeWlsRfid writeSection return %s.\n", ceSystemOp.getErrorMsg(ceStatus));
                    break;
                }

                ceStatus = ceWlsRfidOp.readSection(&myWlsRfid, 2, 1, defaultPasswordA, readBuffer);//从指定扇区的指定块中读取数据
                if(ceStatus != CE_STATUS_SUCCESS)
                {
                    ceSystemOp.printf("CeWlsRfid readSection return %s.\n", ceSystemOp.getErrorMsg(ceStatus));
                    break;
                }

                for(i = 0; i < 16; i++)
                {
                    if(writeBuffer[i] != readBuffer[i])//校验数据
                    {
                        ceStatus = CE_STATUS_FAILE;//校验失败
                        break;
                    }
                }

                if(ceStatus == CE_STATUS_SUCCESS)
                {
                    ceSystemOp.printf("CeWlsRfid verify success!\n");
                }
                else
                {
                    ceSystemOp.printf("CeWlsRfid Read and write successfully but check failed!\n");
                }
            } while (0);

            ceWlsRfidOp.releaseCard(&myWlsRfid);//释放当前连接的卡片
        }
        else
        {
            //ceSystemOp.printf("CeWlsRfid no find Card!.\n");
        }

        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

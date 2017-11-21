/**
  ******************************************************************************
  * @file    CeInfRecv.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeInfRecv模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)本版本暂未实现用Gpio初始化，请注意！！！
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_INF_RECV_H__
#define __CE_INF_RECV_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_INF_RECV_VERSION__ 1                                           /*!< 此驱动文件的版本号*/
#define __CE_INF_RECV_NEED_CREELINKS_VERSION__ 1                            /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_INF_RECV_NEED_CREELINKS_VERSION__)     /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeInfRecv.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeInfRecv属性对像
 */
typedef struct
{
    CeGpio  ceGpio;
    uint8   workMode;
    CeInt ceInt;
    void (*callBackRecvSignal)(void);
}CeInfRecv;

/*
 *CeInfRecv操作对像
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeInfRecv* ceInfRecv, CE_RESOURCE ceGpio); /*!< @brief CeInfRecv模块初始化，使用一个Gpio口。本版本暂未实现用Gpio初始化，请注意！！！
                                                                                 @param ceInfRecv:CeInfRecv属性对象指针
                                                                                 @param ceGpio:CeInfRecv模块使用的资源号*/

    CE_STATUS   (*initialByInt)(CeInfRecv* ceInfRecv, CE_RESOURCE ceInt, void(*callBackRecvSignal)(void));   /*!<
                                                                                 @brief CeInfRecv模块初始化，使用一个Int口
                                                                                 @param ceInfRecv:CeInfRecv属性对象指针
                                                                                 @param ceGpio:CeInfRecv模块使用的资源号
                                                                                 @param callBackRecvSignal:收到红外信号时的中断回调*/

    uint8       (*getStatus)(CeInfRecv* ceInfRecv);                         /*!< @brief 获得红外接收管的接收状态
                                                                                 @param ceInfRecv:CeInfRecv属性对象指针
                                                                                 @return 获得红外接收管的接收状态，返回0x01:收到红外信号同； 返回0x00:未收到红外信号*/
}CeInfRecvOp;

/*
 *CeInfRecv操作对象实例
 */
extern const CeInfRecvOp ceInfRecvOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_INFSEND_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_INF_RECV_H__


/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 获取红外接收模块的接收信号状态，并通过串口打印。需要与CeLaserSend配合测试
******************************************************************************
#include "Creelinks.h"
#include "CeInfRecv.h"
CeInfRecv myInfRecv;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceInfRecvOp.initial(&myInfRecv, R1AGP);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceDebugOp.printf("CeInfRecv Status:%d\n",ceInfRecvOp.getStatus(&myInfRecv));
        ceSystemOp.delayMs(100);
    };
}
******************************************************************************
*/

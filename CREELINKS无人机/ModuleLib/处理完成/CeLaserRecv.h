/**
  ******************************************************************************
  * @file    CeLaserRecv.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeLaserRecv模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_LASER_RECV_H__
#define __CE_LASER_RECV_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_INF_RECV_VERSION__ 1                                           /*!< 此驱动文件的版本号*/
#define __CE_INF_RECV_NEED_CREELINKS_VERSION__ 1                            /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_INF_RECV_NEED_CREELINKS_VERSION__)     /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeLaserRecv.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeLaserRecv属性对像
 */
typedef struct
{
    CeGpio   ceGpio;
}CeLaserRecv;

/*
 *CeLaserRecv操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeLaserRecv* ceLaserRecv, CE_RESOURCE ceGpio);       /*!< @brief CeLaserRecv模块初始化
                                                                                     @param ceLaserRecv:CeLaserRecv属性对象指针
                                                                                     @param ceGpio:CeLaserRecv模块使用的资源号*/

    uint8       (*getStatus)(CeLaserRecv* ceLaserRecv);                         /*!< @brief CeLaserRecv模块初始化
                                                                                     @param ceLaserRecv:CeLaserRecv属性对象指针
                                                                                     @return 获得激光接收管的接收状态，返回0x01:收到激光信号；返回0x00:未收到激光信号*/
}CeLaserRecvOp;

/*
 *CeLaserRecv操作对象实例
 */
extern CeLaserRecvOp ceLaserRecvOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_INFSEND_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_LASER_RECV_H__


/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 获取激光接收模块的接收信号状态，并通过串口打印。需要与CeLaserSend配合测试
******************************************************************************
#include "Creelinks.h"
#include "CeLaserRecv.h"
CeLaserRecv myLaserRecv;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceLaserRecvOp.initial(&myLaserRecv, R1AGP);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceDebugOp.printf("CeLaserRecv Status:%d\n",ceLaserRecvOp.getStatus(&myLaserRecv));
        ceSystemOp.delayMs(100);
    };
}
******************************************************************************
*/

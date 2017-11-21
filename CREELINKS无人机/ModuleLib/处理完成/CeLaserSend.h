/**
  ******************************************************************************
  * @file    CeLaserSend.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeLaserSend模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_LASER_SEND_H__
#define __CE_LASER_SEND_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_LASER_SEND_VERSION__ 1                                           /*!< 此驱动文件的版本号*/
#define __CE_LASER_SEND_NEED_CREELINKS_VERSION__ 1                            /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_LASER_SEND_NEED_CREELINKS_VERSION__)     /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeLaserSend.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeLaserSend属性对像
 */
typedef struct
{
    CePwm cePwm;                                                            /*!< 模块使用到的Pwm资源*/
    CeTimer ceTimer;                                                        /*!< 发送时使用的精确定时器*/
    CeGpio ceGpio;
    uint8 workMode;                                                         /*!< 工作方式，0x00:Pwm方式， 0x01:Gpio+Timer方式*/
}CeLaserSend;
/*
 *CeLaserSend操作对像
 */
typedef struct
{
    CE_STATUS (*initialByPwm)(CeLaserSend* ceLaserSend, CE_RESOURCE cePwm);     /*!< @brief 使用一个Pwm资源号来CeLaserSend模块初始化
                                                                                     @param ceLaserSend:CeLaserSend属性对象指针
                                                                                     @param cePwm:CeLaserSend模块使用的资源号*/

    CE_STATUS (*initialByGpio)(CeLaserSend* ceLaserSend, CE_RESOURCE ceGpio, CE_RESOURCE ceTimer);/*!<
                                                                                     @brief 使用一个Gpio口及一个定时器进行CeLaserSend模块初始化
                                                                                     @param ceLaserSend:CeLaserSend属性对象指针
                                                                                     @param cePwm:CeLaserSend模块使用的资源号
                                                                                     @param ceTimer:CeTimer模块使用的定时器资源号*/

    void (*setOn)(CeLaserSend* ceLaserSend);                                    /*!< @brief 配置激光发射管为发射状态，即红外发射一直发出激光
                                                                                     @param ceLaserSend:CeLaserSend属性对象指针*/

    void (*setOff)(CeLaserSend* ceLaserSend);                                   /*!< @brief 配置激光发射管为关闭状态，即激光发射管不发出激光
                                                                                     @param ceLaserSend:CeLaserSend属性对象指针*/


}CeLaserSendOp;
/*
 *CeLaserSend操作对象实例
 */
extern CeLaserSendOp ceLaserSendOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_INFSEND_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_LASER_SEND_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 每隔1S打开一次激光，需要与激光收对应测试
******************************************************************************
#include "Creelinks.h"
#include "CeLaserSend.h"
CeLaserSend myLaserSend;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceLaserSendOp.initial(&myLaserSend,R5ACGPW);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceLaserSendOp.setOn(&myLaserSend);      //打开激光头
        ceSystemOp.delayMs(1000);
        ceLaserSendOp.setOff(&myLaserSend);     //关闭激光头
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

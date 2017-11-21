/**
  ******************************************************************************
  * @file    CeEvSw.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeEvSw模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)该驱动文件适用于振动开关、水银开关、干簧管
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_EV_SWZ_H__
#define __CE_EV_SWZ_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_EV_SWZ_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_EV_SWZ_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_EV_SWZ_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeEvSw.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeEvSw属性对像
 */
typedef struct
{
    CeInt ceInt;
    void (*callBackEvent)(void);                    /*!< 当模块触发事件时，调用的事件回调函数*/
}CeEvSw;
/*
 *CeEvSw操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeEvSw* ceEvSw,CE_RESOURCE ceInt, void (*callBackEvent)(void));/*!<
                                                         @brief CeEvSw模块初始化
                                                         @param ceEvSw:CeEvSw属性对象指针
                                                         @param ceInt:CeEvSw模块使用的资源号*/

    uint8       (*getBit)(CeEvSw* ceEvSw);      /*!< @brief 获取EvSw对应的GPIO口的电平状态，0x01和0x00
                                                         @param ceEvSw:CeEvSw属性对象指针
                                                         @return 返回0低电平，模块处于未触发状态；1高电平，模块处于触发状态*/
}CeEvSwOp;
/*
 *CeEvSw操作对象实例
 */
extern CeEvSwOp ceEvSwOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_BEEP_SRC_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_EV_SWZ_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 每检测到事件后，但在回调中发送信息到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeEvSw.h"
CeEvSw mySw;                                         //定义CeEvSw属性对象
void callBackEvent(void)
{
    ceDebugOp.printf("Enter callBack event!\n");    //进入回调并打印信息
}
int main(void)
{
    ceSystemOp.initial();                            //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                       //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceEvSwOp.initial(&mySw, R1AGP, callBackEvent);   //使用R1AGP初始化并注册事件回调函数
    while (1)
    {
        ceTaskOp.mainTask();                         //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
    };
}
******************************************************************************
*/

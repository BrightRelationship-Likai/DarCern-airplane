/**
  ******************************************************************************
  * @file    CeBtn16S.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtn16S模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)如果采用Int接口初始化，则回调是在中断中执行。
  *2)如果采用Gpio接口初始化，则回调是在main函数中的mainTask()中执行。
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BTN_16S_H__
#define __CE_BTN_16S_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BTN_16S_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_BTN_16S_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_BTN_16S_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeBtn16S.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeBtn16S属性对像
 */
typedef struct
{
    CeTg ceTg;                                               /*!< 模块使用到的Tg对象*/
    CeTask ceTask;                                           /*!< 模块使用到的Task对象*/
    uint16 keyStatus;                                        /*!< 记录上一次按键状态*/
    void (*callBackKeyPressEvent)(uint8 keyCode);            /*!< 键盘按下事件发生时，需要执行的函数；keyCode:被按下的按键码*/
}CeBtn16S;
/*
 *CeBtn16S操作对像
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeBtn16S* ceBtn16S, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackKeyPressEvent)(uint8 keyCode));/*!<
                                                             @brief  CeBtn16S模块使用三个Gpio来完成初始化
                                                             @param  ceBtn16S:ceBtn16S属性对象指针
                                                             @param  ceGpio0:Ce8Segx1模块使用的第一个Gpio资源号
                                                             @param  ceGpio1:Ce8Segx1模块使用的第二个Gpio资源号
                                                             @param  ceGpio2:Ce8Segx1模块使用的第三个Gpio资源号
                                                             @param  callBackKeyPressEvent:键盘按下事件发生时，需要执行的函数；keyCode:被按下的键码*/

    CE_STATUS   (*initialByTg)(CeBtn16S* ceBtn16S,CE_RESOURCE ceTg, void (*callBackKeyPressEvent)(uint8 keyCode));/*!<
                                                             @brief  CeBtn16S模块使用Tg来完成初始化
                                                             @param  ceBtn16S:ceBtn16S属性对象指针
                                                             @param  ceTg:CeBtn16S模块使用的Tg资源号
                                                             @param  callBackKeyPressEvent:键盘按下事件发生时，需要执行的函数；keyCode:被按下的键码*/
}CeBtn16SOp;
/*
 *CeBtn16S操作对象实例
 */
extern CeBtn16SOp ceBtn16SOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_SW4X4_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SW4X4_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境), 
* @function 按下任意按钮后，将键值通过串口将信息显示到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeBtn16S.h"
CeBtn16S myBtn16S;
void callBackPress(uint8 keyCode)
{
    ceDebugOp.printf("Key %d is pressing!\n",keyCode);     //打印按下的按钮号
}
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                              //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceBtn16SOp.initialByTg(&myBtn16S,R2TI2c,callBackPress); //使用R2TI2c的Tg功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
    };
}
******************************************************************************
*/

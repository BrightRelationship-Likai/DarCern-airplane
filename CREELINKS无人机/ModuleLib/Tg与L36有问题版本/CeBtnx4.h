/**
  ******************************************************************************
  * @file    CeBtnx4.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtnx4模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BTNX4_H__
#define __CE_BTNX4_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BTNX4_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_BTNX4_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_BTNX4_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeBtnx4.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeBtnx4属性对像
 */
typedef struct
{
    CeGpio ceGpio0;                                                         /*!< 模块使用到的Tg对象*/
    CeGpio ceGpio1;
    CeGpio ceGpio2;
    CeTask ceTask;                                                          /*!< 模块使用到的Task对象*/
    uint8 keyStatus;                                                        /*!< 记录上一次按键状态*/
    void (*callBackKeyPressEvent)(uint8 keyCode);                           /*!< 键盘按下事件发生时，需要执行的函数；keyCode:被按下的按键码*/
}CeBtnx4;
/*
 *CeBtnx4操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeBtnx4* ceBtnx4, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackKeyPressEvent)(uint8 keyCode));/*!<
                                                                             @brief  CeBtnx4模块使用三个Gpio来完成初始化
                                                                             @param  ceBtnx4:ceBtnx4属性对象指针
                                                                             @param ceGpio0:Ce8Segx1模块使用的第一个Gpio资源号
                                                                             @param ceGpio1:Ce8Segx1模块使用的第二个Gpio资源号
                                                                             @param ceGpio2:Ce8Segx1模块使用的第三个Gpio资源号
                                                                             @param callBackKeyPressEvent:键盘按下事件发生时，需要执行的函数:keyCode:被按下的键码，范围0-3*/
}CeBtnx4Op;
/*
 *CeBtnx4操作对象实例
 */
extern const CeBtnx4Op ceBtnx4Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_BTNX4_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_BTNX4_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境), 
* @function 按下任意按钮后，将键值通过串口将信息显示到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeBtnx4.h"
CeBtnx4 myBtnx4;
void callBackPress(uint8 keyCode)
{
    ceDebugOp.printf("Key %d is pressing!\n",keyCode);     //打印按下的按钮号
}
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                              //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceBtnx4Op.initialByTg(&myBtnx4,R2TI2c,callBackPress);   //使用R2TI2c的Tg功能功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
    };
}
******************************************************************************
*/

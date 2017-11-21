/**
  ******************************************************************************
  * @file    CeBtnTouch.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtnTouch模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BTN_TOUCH_H__
#define __CE_BTN_TOUCH_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BTN_TOUCH_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_BTN_TOUCH_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_BTN_TOUCH_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeBtnTouch.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

#define CE_BTN_TOUCH_OUT_TIME_MS   120                      /*!< 等待按键弹起或者按下的超时时间，防止死循环*/
/*
 *CeBtnTouch属性对像
*/
typedef struct
{
    CeInt       ceInt;                                      /*!< 中断资源属性对象*/
    CeGpio      ceGpio;                                     /*!< Gpio资源属性对象*/
    CeTicker    ceTicker;                                   /*!< 滴答毫秒定时器属性对象*/
    uint8       status;                                     /*!< 按钮当前状态*/
    void(*callBackPressEvent)(void);                        /*!< 按键事件回调函数*/
}CeBtnTouch;

/*
 *CeBtnTouch操作对像
*/
typedef struct
{
    CE_STATUS(*initialByGpio)(CeBtnTouch* ceBtnTouch, CE_RESOURCE ceGpio, void(*callBackPressEvent)(void));/*!<
                                                                 @brief CeBtnTouch模块使用Gpio进行初始化
                                                                 @param CeBtnTouch:CeBtnTouch属性对象指针
                                                                 @param ceGpio:CeBtnTouch模块使用的Gpio的资源号
                                                                 @param callBackPressEvent:按键按下时的回调函数*/

    CE_STATUS(*initialByInt)(CeBtnTouch* ceBtnTouch, CE_RESOURCE ceInt, void(*callBackPressEvent)(void));/*!<
                                                                 @brief CeBtnTouch模块使用Int进行初始化
                                                                 @param CeBtnTouch:CeBtnTouch属性对象指针
                                                                 @param ceInt:CeBtnTouch模块使用的资源号
                                                                 @param callBackPressEvent:按键按下时的回调函数*/

    uint8(*getGpioStatus)(CeBtnTouch* ceBtnTouch);          /*!< @brief 获取CeBtnTouch对应的GPIO口的状态，0x01和0x00
                                                                 @param ceBtnTouch:CeBtnTouch属性对象指针*/

    void(*waitForPressDown)(CeBtnTouch* ceBtnTouch);        /*!< @brief 等待按键按下，超时时间为CE_BTN_TOUCH_OUT_TIME_MS
                                                                 @param ceBtnTouch:CeBtnTouch属性对象指针*/

    void(*waitForPressUp)(CeBtnTouch* ceBtnTouch);          /*!< @brief 等待按键弹起，超时时间为CE_BTN_TOUCH_OUT_TIME_MS
                                                                 @param ceBtnTouch:CeBtnTouch属性对象指针*/

}CeBtnTouchOp;

/*
*CeBtnTouch操作对象实例
*/
extern CeBtnTouchOp ceBtnTouchOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_BTN_TOUCH_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_BTN_TOUCH_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 每检测到触模事件后，但在回调中发送信息到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeBtnTouch.h"
CeBtnTouch myBtnTouch;                                 //定义CeBtnTouch属性对象
void callBackPress(void)
{
    ceDebugOp.printf("Enter callBackPress event!\n"); //进入回调并打印信息
}
int main(void)
{
    ceSystemOp.initial();                              //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                         //通过Uart串口输出Debug信息到上位机
                                                       //TODO:请在此处插入模块初始化等操作
    ceBtnTouchOp.initialByGpio(&myBtnTouch, R1AGP, callBackPress);
    while (1)
    {
        ceTaskOp.mainTask();                           //Creelinks环境主循环任务，请保证此函数能够被周期调用
                                                       //TODO:请在此处插入用户操
    };
}
******************************************************************************
*/

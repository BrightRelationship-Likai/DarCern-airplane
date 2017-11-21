/**
  ******************************************************************************
  * @file    CeBtnx3P.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtnx3P模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BTN_X3P_H__
#define __CE_BTN_X3P_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BTN_X3P_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_BTN_X3P_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_BTN_X3P_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeBtnx3P.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeBtnx3P属性对像
 */
typedef struct
{
    CeGpio      ceGpio0;                                                /*!< 模块使用到的Gpio资源属性对象*/
    CeGpio      ceGpio1;
    CeGpio      ceGpio2;
    CeTask      ceTask;                                                 /*!< 模块使用的Task属性对象*/
    uint8       btnStatus;                                              /*!< 按钮当前状态*/
    void        (*callBackPressEvent)(uint8 btnIndex);                  /*!< 按键事件回调函数;btnIndex:按下的按键索引，范围0-2*/
}CeBtnx3P;
/*
 *CeBtnx3P操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeBtnx3P* ceBtnx3P, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackPressEvent)(uint8 btnIndex));/*!<
                                                                             @brief CeBtnx3P模块使用三个Gpio口来完成初始化
                                                                             @param ceBtnx3P:CeBtnx3P属性对象指针
                                                                             @param ceGpio0:CeBtnx3P模块使用的第一个Gpio口资源号
                                                                             @param ceGpio1:CeBtnx3P模块使用的第二个Gpio口资源号
                                                                             @param ceGpio2:CeBtnx3P模块使用的第三个Gpio口资源号
                                                                             @param callBackPressEvent:按键按下时的回调函数;btnIndex:按下的按键索引，范围0-2*/
}CeBtnx3POp;
/*
 *CeBtnx3P操作对象实例
 */
extern const CeBtnx3POp ceBtnx3POp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_BTN_X3P_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_BTN_X3P_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境)
* @function 测试对应按钮的回调是否能正常响应
******************************************************************************
#include "Creelinks.h"
#include "CeBtnx3P.h"
CeBtnx3P ceBtnx3P;                                //定义CeBenx3P属性对象
void callBackPressEvent(uint8 btnIndex)
{
    ceDebugOp.printf("callBackPressEvent is called!\tbtnIndex: %d\n", btnIndex);//如果进入回调，把触发此回调的按钮索引打印出来
}
int main(void)
{
    ceSystemOp.initial();                        //Creelinks环境初始化
    ceDebugOp.initial(Uartx);                        //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceBtnx3POp.initialByTg(&ceBtnx3P, RxT, callBackPressEvent); //使用Tg口初始化ceBtnx3P对象
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
    };
}
******************************************************************************
*/

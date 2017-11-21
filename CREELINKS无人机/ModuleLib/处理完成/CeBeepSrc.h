/**
  ******************************************************************************
  * @file    CeBeepSrc.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtnx1模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BEEP_SRC_H__
#define __CE_BEEP_SRC_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BEEP_SRC_VERSION__ 1                                           /*!< 此驱动文件的版本号*/
#define __CE_BEEP_SRC_NEED_CREELINKS_VERSION__ 1                            /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_BEEP_SRC_NEED_CREELINKS_VERSION__)     /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeBeepSrc.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeBeepSrc属性对象
 */
typedef struct
{
    CeGpio ceGpio;                                                  /*!< CeBeepSrc模块使用的Gpio资源号*/
}CeBeepSrc;

/*
 *CeBeepSrc操作对象
 */
typedef struct
{
    void    (*initial)(CeBeepSrc* ceBeepSrc,CE_RESOURCE ceGpio);    /*!< @brief CeBeepSrc模块初始化
                                                                         @param ceBeepSrc:CeBeepSrc属性对象指针*/

    void    (*setOn)(CeBeepSrc* ceBeepSrc);                         /*!< @brief 使峰鸣器开始发声
                                                                         @param ceBeepSrc:CeBeepSrc属性对象指针*/

    void    (*setOff)(CeBeepSrc* ceBeepSrc);                        /*!< @brief 使峰鸣器停止发声
                                                                         @param ceBeepSrc:CeBeepSrc属性对象指针*/
}CeBeepSrcOp;

/*
 *CeBeepSrc操作对象实例
 */
extern CeBeepSrcOp ceBeepSrcOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_BEEP_SRC_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_BEEP_SRC_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 使Beep每隔500ms发声一次
******************************************************************************
#include "Creelinks.h"
CeBeepSrc myBeepSrc;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(Uartx);                        //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceBeepSrcOp.initial(&myBeepSrc,RxG);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceBeepSrcOp.setOn(&myBeepSrc);          //使模块发声
        ceSystemOp.delayMs(500);                //延时500ms
        ceBeepSrcOp.setOff(&myBeepSrc);         //使模块不发声
        ceSystemOp.delayMs(500);                //延时500ms
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeRly1.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRly1模块的驱动头文件，控制一路继电器的开关
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY1_H__
#define __CE_RLY1_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY1_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_RLY1_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY1_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeRly1.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeRly1属性对像
 */
typedef struct
{
     CeGpio ceGpio;
}CeRly1;
/*
 *CeRly1操作对像
 */
typedef struct
{
    CE_STATUS (*initial)(CeRly1* ceRly1,CE_RESOURCE ceGpio);    /*!< @brief  CeRly1模块初始化
                                                                     @param  ceRly1:CeRly1属性对象指针*/

    void     (*setOn)(CeRly1* ceRly1);                          /*!< @brief  设置继电器闭合
                                                                     @param  ceRly1:CeRly1属性对象指针*/

    void      (*setOff)(CeRly1* ceRly1);                        /*!< @brief  设置继电器断开
                                                                     @param  ceRly1:CeRly1属性对象指针*/
}CeRly1Op;
/*
 *CeRly1操作对象实例
 */
extern const CeRly1Op ceRly1Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY1_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_RLY1_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 配置继电器以1HZ的频率吸合与断开
******************************************************************************
#include "Creelinks.h"
#include "CeRly1.h"
CeRly1 myRly;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceRly1Op.initial(&myRly, R1AGP);            //使用R1AGP的Gpio功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceRly1Op.setOn(&myRly);                 //设置继电器状态为吸合
        ceSystemOp.delayMs(500);
        ceRly1Op.setOff(&myRly);                //设置继电器状态为断开
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

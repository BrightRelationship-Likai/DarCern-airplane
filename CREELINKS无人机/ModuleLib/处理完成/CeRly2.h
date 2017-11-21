/**
  ******************************************************************************
  * @file    CeRly2.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRly2模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY2_H__
#define __CE_RLY2_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY2_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_RLY2_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY2_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeRly2.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeRly2属性对像
 */
typedef struct
{
    CeGpio ceGpio0;
    CeGpio ceGpio1;
}CeRly2;
/*
 *CeRly2操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeRly2* ceRly2,CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1 );   /*!< @brief CeRly1模块初始化
                                                                                             @param ceRly1:CeRly1属性对象指针*/

    void        (*setOn)(CeRly2* ceRly2,uint8 rlyIndex);                                /*!< @brief 设置继电器闭合
                                                                                             @param ceRly2:CeRly2属性对象指针
                                                                                             @param rlyIndex:需要闭合的继电器序号*/

    void        (*setOff)(CeRly2* ceRly2,uint8 rlyIndex);                               /*!< @brief 设置继电器断开
                                                                                             @param ceRly2:CeRly2属性对象指针
                                                                                             @param rlyIndex:需要断开的继电器序号*/
}CeRly2Op;
/*
 *CeRly2操作对象实例
 */
extern const CeRly2Op ceRly2Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY2_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_RLY2_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 配置继电器依次吸合与断开
******************************************************************************
#include "Creelinks.h"
#include "CeRly2.h"
CeRly2 myRly;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceRly2Op.initial(&myRly, R1AGP,R0GI);       //使用R1AGP和R3GI的Gpio功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceRly2Op.setOn(&myRly,0);               //设置继电器0状态为吸合
        ceSystemOp.delayMs(500);
        ceRly2Op.setOff(&myRly,0);              //设置继电器0状态为断开
        ceSystemOp.delayMs(500);
        ceRly2Op.setOn(&myRly, 1);              //设置继电器1状态为吸合
        ceSystemOp.delayMs(500);
        ceRly2Op.setOff(&myRly, 1);             //设置继电器1状态为断开
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

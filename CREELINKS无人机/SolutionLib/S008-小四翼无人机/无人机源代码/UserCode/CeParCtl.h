/**
  ******************************************************************************
  * @file    CeParCtl.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeParCtl模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_PAR_CTL_H__
#define __CE_PAR_CTL_H__
#include "Creelinks.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/*
 *CeParCtl操作对像
 */
typedef struct
{
    void    (*initial)(void);                   /*!< @brief  参数调试对象初始化*/

    void    (*beforeFilterHook)(void);          /*!< @brief  使用当前传感器数据进行无人机姿态解算前，需调用的钩子函数*/

    void    (*afterFilterHook)(void);           /*!< @brief  使用当前传感器数据进行无人机姿态解算后，需调用的钩子函数*/

    void    (*beforePIDHook)(void);             /*!< @brief  使用无人机当前状态及期望状态进行PID运算前，需调用的钩子函数*/

    void    (*afterPIDHook)(void);              /*!< @brief  使用无人机当前状态及期望状态进行PID运算后，需调用的钩子函数*/

    void    (*recvDataHook)(void);              /*!< @brief  系统每个主循环均会调用，此函数内部用于实现数据接收操作*/

    void    (*sendDataHook)(void);              /*!< @brief  系统每个主循环均会调用，此函数内部用于实现将当前无人机各项参数发送给控制端的操作*/
}CeParCtlOp;
/*
 *CeParCtl操作对象实例
 */
extern const CeParCtlOp ceParCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_PAR_CTL_H__

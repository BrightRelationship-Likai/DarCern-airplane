/**
  ******************************************************************************
  * @file    CePCMCtl.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   电机电调驱动文件，即将0~1000的驱动为转化为0~100%占空比的PWM输出
  ******************************************************************************
  * @attention
  *
  *1)输入0~1000的驱动强度，输出对应为0~100%的占空比
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_PCM_CTL_H__
#define __CE_PCM_CTL_H__
#include "Creelinks.h"
#include "CePCM.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/*
 *CePCMCtl操作对像
 */
typedef struct
{
    void      (*initial)(void);              /*!< @brief 电机驱动接口初始化*/    

    uint8     (*checkConnectStatus)(void); 

    fp32      (*getHopePitch)(void);
    fp32      (*getHopeRoll)(void);
    fp32      (*getHopeYaw)(void);
    fp32      (*getHopeAccelerator)(void);

    
}CePCMCtlOp;

/*
 *CePCMCtl操作对象实例
 */
extern const CePCMCtlOp cePCMCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_PCM_CTL_H__


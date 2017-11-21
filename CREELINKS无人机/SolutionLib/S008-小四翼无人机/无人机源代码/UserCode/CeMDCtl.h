/**
  ******************************************************************************
  * @file    CeMDCtl.h
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
#ifndef __CE_MD_CTL_H__
#define __CE_MD_CTL_H__
#include "Creelinks.h"
#include "CeMD.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
typedef struct
{
    int16 motorDrivePower0;
    int16 motorDrivePower1;
    int16 motorDrivePower2;
    int16 motorDrivePower3;
}CeMDDrivePower;

/*
 *CeMDCtl操作对像
 */
typedef struct
{
    void      (*initial)(void);              /*!< @brief 电机驱动接口初始化*/    

    void      (*setDriverPower)(CeMDDrivePower* drivePower);/*!< 
                                                  @brief 配置电机的驱动强度， 0~1000
                                                  @param drivePower:保存电机驱动强度的数组指针*/
}CeMDCtlOp;

/*
 *CeMDCtl操作对象实例
 */
extern const CeMDCtlOp ceMDCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_MD_CTL_H__


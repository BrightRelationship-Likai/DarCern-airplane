/**
  ******************************************************************************
  * @file    CeStatus.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeStatus模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_STATUS_H__
#define __CE_STATUS_H__
#include "Creelinks.h"
#include "CeSensor.h"
#include "CePCMCtl.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

typedef struct  
{
    fp32 pitch;                                         /*!< 俯仰角，向前俯为????， 向后仰为????*/
    fp32 roll;                                          /*!< 翻滚角，向左翻为????，向右翻为????*/
    fp32 yaw;                                           /*!< 偏航角，正北方向上逆时针偏为????，顺时针偏为????*/
    fp32 accelerator;                                   /*!< 无人机油门，0~1000*/

    CeAcc ceAcc;                                        /*!< 加速度传感器数据*/
    CeGyr ceGyr;                                        /*!< 角速度传感器数据*/
    CeMag ceMag;                                        /*!< 地磁传感器数据*/
    CeAlt ceAlt;                                        /*!< 气压及海拔数据*/   
    CeTem ceTem;                                        /*!< 温度传感器数据*/
    CeGps ceGps;                                        /*!< 位置信息数据*/  
}CeStatus;

/*
 *CeStatus操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(void);                       /*!< @brief  系统控制函数初始化*/

    void        (*getNowStatus)(CeStatus* ceNowStatus); /*!< @brief  获取当前无人机的飞行状态基本信息
                                                             @param  飞行参数信息保存地址*/

    void        (*getHopeStatus)(CeStatus* ceNowStatus, CeStatus* ceHopeStatus);/*!< 
                                                             @brief  获取期望的飞行状态基本信息
                                                             @param  飞行参数信息保存地址*/

}CeStatusOp;
/*
 *CeStatus操作对象实例
 */
extern const CeStatusOp ceStatusOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_STATUS_H__

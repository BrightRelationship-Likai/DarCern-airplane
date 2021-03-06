/**
  ******************************************************************************
  * @file    CePID.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   无人机PID参数调整功能模块
  ******************************************************************************
  * @attention
  *
  *1)输入当前无人机姿态（Pitch/Roll/Yaw）、高度、期望油门。
  *2)输出四个电机的驱动强度，0~1000.
  *3)默认PID参数，需在cePID_initial函数中初始化并赋值
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_PID_H__
#define __CE_PID_H__
#include "Creelinks.h"
#include "CeStatus.h"
#include "CeSensor.h"
#include "CeMDCtl.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#define  CE_PID_MIN_DRIVER_POWER    20      /*!< 定义维持电机正常运转的最小驱动力，0~1000）*/
#define  CE_PID_MAX_DRIVER_POWER    1000    /*!< 定义电机可承受的最大驱动力，0~1000*/

/**
  * @brief  结构体，PID控制器属性对象，串级PID
  */
typedef struct  
{   
    //Pitch Pid参数项
    fp32 outPitchP;                         /*!< Pitch角控制，外环Kp项*/
    fp32 outPitchI;                         /*!< Pitch角控制，外环Ki项*/
    fp32 outPitchD;
    fp32 outPitchError;                     /*!< Pitch角控制，外环角度误差累积项*/
    fp32 outPidPitch;                       /*!< Pitch角控制，外环PID控制器输出*/
    fp32 lastOutPitch;
    fp32 inPitchP;                          /*!< Pitch角控制，内环Kp项*/
    fp32 inPitchI;                          /*!< Pitch角控制，内环Ki项*/
    fp32 inPitchD;                          /*!< Pitch角控制，内环Kd项*/
    fp32 inPitchError;                      /*!< Pitch角控制，内环角度误差累积项*/
    fp32 inPidPitch;                        /*!< Pitch角控制，内环角度误差累积项*/
    fp32 lastInPitchGyrY;                   /*!< Pitch角控制，上一次内环角度项*/
    //Roll Pid参数项
    fp32 outRollP;                          /*!< Roll角控制，外环Kp项*/
    fp32 outRollI;                          /*!< Roll角控制，外环Ki项*/
    fp32 outRollD;
    fp32 outRollError;                      /*!< Roll角控制，外环角度误差累积项*/
    fp32 outPidRoll;                        /*!< Roll角控制，外环PID控制器输出*/
    fp32 lastOutRoll;
    fp32 inRollP;                           /*!< Roll角控制，内环Kp项*/
    fp32 inRollI;                           /*!< Roll角控制，内环Ki项*/
    fp32 inRollD;                           /*!< Roll角控制，内环Kd项*/
    fp32 inRollError;                       /*!< Roll角控制，内环角度误差累积项*/
    fp32 inPidRoll;                         /*!< Roll角控制，内环角度误差累积项*/
    fp32 lastInRollGyrX;                    /*!< Roll角控制，上一次内环角度项*/
    //Yaw Pid参数项，由于未使用地磁，故仅用到了内环，外环参数预留
    fp32 outYawP;                          /*!< Yaw角控制，外环Kp项*/
    fp32 outYawI;                          /*!< Yaw角控制，外环Ki项*/
    fp32 outYawD;
    fp32 outYawError;                      /*!< Yaw角控制，外环角度误差累积项*/
    fp32 outPidYaw;                        /*!< Yaw角控制，外环PID控制器输出*/
    fp32 lastOutYaw;
    fp32 inYawP;                           /*!< Yaw角控制，内环Kp项*/
    fp32 inYawI;                           /*!< Yaw角控制，内环Ki项*/
    fp32 inYawD;                           /*!< Yaw角控制，内环Kd项*/
    fp32 inYawError;                       /*!< Yaw角控制，内环角度误差累积项*/
    fp32 inPidYaw;                         /*!< Yaw角控制，内环角度误差累积项*/
    fp32 lastInYawGyrZ;                    /*!< Yaw角控制，上一次内环角度项*/
    //海拔设计 Pid参数项
    fp32 altBase;                           /*!< 海拔高度控制，油门的基值*/
    fp32 altKp;                             /*!< 海拔高度控制，Kp项*/
    fp32 altKi;                             /*!< 海拔高度控制，Ki项*/
    fp32 altKd;                             /*!< 海拔高度控制，Kd项*/
    fp32 altPid;                            /*!< 海拔高度控制，内环高度误差累积项*/
    fp32 altError;                          /*!< 海拔高度控制，内环高度误差累积项*/
    fp32 lastAltError;                      /*!<海拔高度控制，上一次内环角度项*/

    fp32 dtS;                               /*!< 两次PID计算之间的时间间隔，可用于精确控制油门的阻尼动作*/

    CeStatus* ceNowStatus;                   /*!< Yaw角控制，上一次内环角度项*/
    CeStatus* ceHopeStatus;                  /*!< Yaw角控制，上一次内环角度项*/
    CeMDDrivePower  drivePower;              /*!< 电机的驱动强度0点，用于校正电机之间的转速误差*/
}CePID;

/**
  * @brief  结构体，PID控制器操作对象
  */
typedef struct  
{
    void       (*initial)(void);            /*!< @brief  CePID控制器模块初始化
                                                 @param  cePackageSend:数据打包并发送使用的结构体
                                                 @param  cePackageRecv:数据拆包并解析使用的结构体*/

    CeMDDrivePower* (*calculate)(CeStatus* ceNowStatus, CeStatus* ceHopeStatus,fp32 dtS);  /*!< 
                                                 @brief  根据当前无人机加速度、角速度、姿态角、期望姿态角，直接计算出四个电调应有的驱动强度
                                                 @param  ceNowAcc:当前无人机三轴加速度数据，单位G
                                                 @param  ceNowGyr:当前无人机三轴角速度数据，单位度/s
                                                 @param  ceNowStatus:当前无人机姿态角数据
                                                 @param  ceHopeStatus:期望无人机处于的姿态角数据
                                                 @param  dtS:程序执行周期，单位S
                                                 @param  drivePower:计算的输出结果，四个电机的驱动强度*/
}CePIDOp;

/*
 *CePID操作对象实例
 */
extern const CePIDOp cePIDOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_PID_H__


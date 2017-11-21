/**
  ******************************************************************************
  * @file    CePID.c
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
#include "CePID.h"
#include <math.h>
#include "CeParCtl.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
CePID cePID;                //定义全局PID控制器对象
/**
  * @brief  CePID控制器模块初始化
  */
void cePID_initial(void)
{
    //当前版本需要在此处配置PID各个参数，下一版本将直接保存到FLASH当中
    cePID.outPitchP = 6.000f;        
    cePID.outPitchI = 0.010f;
    cePID.outPitchD = 0.000f;
    cePID.outPitchError = 0.000f;
    cePID.lastOutPitch = 0.000f;
    cePID.inPitchP = 0.800f;
    cePID.inPitchI = 0.000f;
    cePID.inPitchD = 20.000f;
    cePID.inPitchError = 0.000f;
    cePID.lastInPitchGyrY = 0.000f;

    cePID.outRollP = 6.000f;
    cePID.outRollI = 0.010f;
    cePID.outRollD = 0.000f;
    cePID.outRollError = 0.000f;
    cePID.lastOutRoll = 0.000f;
    cePID.inRollP = 0.800f;
    cePID.inRollI = 0.000f;
    cePID.inRollD = 20.000f;
    cePID.inRollError = 0.000f;
    cePID.lastInRollGyrX = 0.000f;

    cePID.outYawP = 0.000f;                
    cePID.outYawI = 0.000f;                       
    cePID.outYawD = 0.000f;
    cePID.outYawError = 0.000f;                    
    cePID.outPidYaw = 0.000f;            
    cePID.lastOutYaw = 0.000f;
    cePID.inYawP = 6.000f;                       
    cePID.inYawI = 0.000f;                       
    cePID.inYawD = 8.000f;                      
    cePID.inYawError = 0.000f;               
    cePID.inPidYaw = 0.000f;                  
    cePID.lastInYawGyrZ = 0.000f;                  

    cePID.altBase = 400;
    cePID.altKp = 100;
    cePID.altKi = 0.2;
    cePID.altKd = 0;
    cePID.altError = 0;
    cePID.lastAltError = 0;
}

/**
  * @brief  判断无人机是否起飞决定是否将积分项清零
  */
void cePID_resetErrByAccelerator()
{
    if(cePID.ceNowStatus->accelerator <= CE_PID_MAX_DRIVER_POWER*3/10) //当油门小于2/10的强度时，清空积分项，即不进行积分操作
    {
        cePID.outPitchError = 0;
        cePID.inPitchError = 0;
        cePID.outRollError = 0;
        cePID.inRollError = 0;
        cePID.outYawError = 0;
        cePID.inYawError = 0;
    }
}

/**
  * @brief  根据期望的经纬度位置信息，计算姿态角的增减量
  */
void cePID_calculateGPS()
{
    //当前版本暂不支持
}
/**
  * @brief  Pitch的PID计算
  */
void cePID_calculatePitch()
{
    fp32 outPitchErrorNow;
    fp32 inPitchErrorNow;
    outPitchErrorNow = cePID.ceHopeStatus->pitch - cePID.ceNowStatus->pitch;                                    //当前Pitch角度误差=期望角度-当前角度 
    cePID.outPitchError += outPitchErrorNow;                                                        //外环误差累计积分项                                                
    if(cePID.outPitchError > (fp32)(500)) cePID.outPitchError = (fp32)(500);                        //限制外环累积误差最大值
    if(cePID.outPitchError < (fp32)(-500)) cePID.outPitchError = (fp32)(-500);
    cePID.outPidPitch = cePID.outPitchP * outPitchErrorNow + cePID.outPitchI * cePID.outPitchError+ cePID.outPitchD*(cePID.ceNowStatus->pitch - cePID.lastOutPitch); //外环PID输出=外环Kp * 当前Pitch角度误差 + 外环Ki * 外环累积误差    + 外环Kd * （当前Y轴角速度 - 上一次Y轴角速度）        
    cePID.lastOutPitch = cePID.ceNowStatus->pitch;

    inPitchErrorNow = -(cePID.outPidPitch - cePID.ceNowStatus->ceGyr.y);                                           //内环当前角速度误差=外环PID输出-当前y轴角速度误差,取负值原因为传感器安装位置导致                                                             
    cePID.inPitchError += inPitchErrorNow;                                                          //内环误差累计积分项
    if(cePID.inPitchError > (fp32)(500)) cePID.inPitchError = (fp32)(500);                          //限制内环累积误差最大值
    if(cePID.inPitchError < (fp32)(-500)) cePID.inPitchError = (fp32)(-500);
    cePID.inPidPitch = cePID.inPitchP * inPitchErrorNow + cePID.inPitchI * cePID.inPitchError + cePID.inPitchD * (cePID.ceNowStatus->ceGyr.y - cePID.lastInPitchGyrY);//内环PID输出 = 内环Kp*内环当前角速度误差 + 内环Ki*内环角速度误差累积 + 内环Kd*(当前Y轴角速度 - 上一次Y轴角速度)
    cePID.lastInPitchGyrY = cePID.ceNowStatus->ceGyr.y;                                                            //保存上一次角速度
}

/**
  * @brief  Roll的PID计算
  */
void cePID_calculateRoll()
{
    fp32 outRollErrorNow;
    fp32 inRollErrorNow;
    outRollErrorNow = cePID.ceHopeStatus->roll - cePID.ceNowStatus->roll;                                       //当前Roll角度误差=期望角度-当前角度
    cePID.outRollError += outRollErrorNow;                                                          //外环误差累计积分项
    if(cePID.outRollError > (fp32)(500)) cePID.outRollError = (fp32)(500);                          //限制外环累积误差最大值
    if(cePID.outRollError < (fp32)(-500)) cePID.outRollError = (fp32)(-500);
    cePID.outPidRoll = cePID.outRollP * outRollErrorNow + cePID.outRollI * cePID.outRollError + cePID.outRollD * (cePID.ceNowStatus->roll - cePID.lastOutRoll);      //外环PID输出=外环Kp * 当前Roll角度误差 + 外环Ki * 外环累积误差    + 外环Kd * （当前X轴角速度 - 上一次X轴角速度）    
    cePID.lastOutRoll = cePID.ceNowStatus->roll; 

    inRollErrorNow = -(cePID.outPidRoll  - (-cePID.ceNowStatus->ceGyr.x));                                            //内环当前角速度误差=外环PID输出-当前y轴角速度误差,取负值原因为传感器安装位置导致。                                                         
    cePID.inRollError +=inRollErrorNow;                                                             //内环误差累计积分项
    if(cePID.inRollError > (fp32)(500)) cePID.inRollError = (fp32)(500);                            //限制内环累积误差最大值
    if(cePID.inRollError < (fp32)(-500)) cePID.inRollError = (fp32)(-500);
    cePID.inPidRoll = cePID.inRollP * inRollErrorNow + cePID.inRollI * cePID.inRollError + cePID.inRollD * (-cePID.ceNowStatus->ceGyr.x - cePID.lastInRollGyrX);//内环PID输出 = 内环Kp*内环当前角速度误差 + 内环Ki*内环角速度误差累积 + 内环Kd*(当前y轴角速度误差-上一次角速度误差)
    cePID.lastInRollGyrX = -cePID.ceNowStatus->ceGyr.x;                                                             //保存上一次角速度  
}

/**
  * @brief  Yaw的PID计算
  */
void cePID_calculateYaw()
{
    fp32 outYawErrorNow;
    outYawErrorNow = cePID.ceHopeStatus->yaw - cePID.ceNowStatus->ceGyr.z;                                               //yaw角速度误差 = 期望Z轴角速度 - 当前Z轴角速度
    cePID.inYawError += outYawErrorNow;
    if(cePID.inYawError > (fp32)(500)) cePID.inYawError = (fp32)(500);                              //限制内环累积误差最大值
    if(cePID.inYawError < (fp32)(-500)) cePID.inYawError = (fp32)(-500);        
    cePID.inPidYaw = cePID.inYawP * outYawErrorNow + cePID.inYawI * cePID.inYawError+cePID.inYawD * (cePID.ceNowStatus->ceGyr.z - cePID.lastInYawGyrZ);//yaw航向角PID输出 = Z轴Kp项 * 当前Z轴角速度误差 + 内环Ki*内环角速度误差累积 + Z轴Kd项 * （当前yaw角速度误差 - 上一次yaw角速度误差）； 
    cePID.lastInYawGyrZ = cePID.ceNowStatus->ceGyr.z;
}

/**
  * @brief  油门计算，根据控制杆输出的期望油门强度，配置当前无人机的油门参数
  */
void cePID_calculateAccelerator()
{
    if(cePID.ceHopeStatus->ceAlt.altitude == -9999)//当前处于自由飞行模式，配置油门为阻尼状态，防止油门突然增加而翻机或突然减小而摔机
    {
        if(cePID.ceNowStatus->accelerator < (cePID.ceHopeStatus->accelerator-cePID.dtS*2000) && cePID.ceNowStatus->accelerator < CE_PID_MAX_DRIVER_POWER*7/10 - cePID.dtS*2000) //配置油门上升为阻尼工作状态，防止油门突然加大而导致不稳定
            cePID.ceNowStatus->accelerator += cePID.dtS*2000;//控制油门增加速度为 2/ms
        if(cePID.ceNowStatus->accelerator > (cePID.ceHopeStatus->accelerator+cePID.dtS*1000) && cePID.ceNowStatus->accelerator >= cePID.dtS*1000 ) //配置油门下降为阴尼工作状态，防止下降速度过快导致摔机
            cePID.ceNowStatus->accelerator -= cePID.dtS*1000;//控制油门减少速度为 1/ms 			
        //if(cePID.ceNowStatus->accelerator < CE_PID_MAX_DRIVER_POWER*3/10 ) cePID.ceNowStatus->accelerator = CE_PID_MAX_DRIVER_POWER*3/10;//限制油门最小值，防止无人机油门较小时发生振荡
    }
}

/**
  * @brief  海拔高度计算，根据期望海拔高度与当前高度，配置油门强度
  */
void cePID_calculateAltitude()
{
    if(cePID.ceHopeStatus->ceAlt.altitude != -9999)    //当前无人机处于定高飞行状态，即期望高度不为-9999
    {
        fp32 altError = (cePID.ceHopeStatus->ceAlt.altitude - cePID.ceNowStatus->ceAlt.altitude);                           //海拔误差 = 期望海拔高度 - 当前海拔高度 
        if(altError > 2.0f) altError = 2.0f;                                                        //限制海拔误差最大值
        else if(altError < -2.0f) altError = -2.0f; 
        cePID.altError += altError;                                                                 //海拔误差积分累积
        if(cePID.altError > (fp32)(500)) cePID.altError = (fp32)(500);                              //限制误差累积积分项
        if(cePID.altError < (fp32)(-500)) cePID.altError = (fp32)(-500);        
        cePID.altPid = altError*cePID.altKp + cePID.altError * cePID.altKi;                         //海拔PID输出 = 海拔误差*Kp + 海拔误差积分* Ki
        cePID.ceNowStatus->accelerator = cePID.altBase + cePID.altPid;                                    //海拔最终输出 = 海拔PID输出 + 油门基值
        if(cePID.ceNowStatus->accelerator < cePID.altBase - 20 ) cePID.ceNowStatus->accelerator = cePID.altBase - 20 ;//限制油门最小值，防止因海拔高度突变引起的摔机
        if(cePID.ceNowStatus->accelerator > CE_PID_MAX_DRIVER_POWER*6/10 ) cePID.ceNowStatus->accelerator = CE_PID_MAX_DRIVER_POWER*6/10;//限制油门最大值，防止无人机突然快速上升
    }
}


/**
  * @brief  电机驱动强度的计算
  */
void cePID_calculateDriverPower()
{
    cePID.drivePower.motorDrivePower0 = cePID.ceNowStatus->accelerator + cePID.inPidPitch + cePID.inPidRoll + cePID.inPidYaw;//整合Pitch、Roll、Yaw、油门/海拔 进行PID运算出的结果
    cePID.drivePower.motorDrivePower1 = cePID.ceNowStatus->accelerator + cePID.inPidPitch - cePID.inPidRoll - cePID.inPidYaw;
    cePID.drivePower.motorDrivePower2 = cePID.ceNowStatus->accelerator - cePID.inPidPitch - cePID.inPidRoll + cePID.inPidYaw;
    cePID.drivePower.motorDrivePower3 = cePID.ceNowStatus->accelerator - cePID.inPidPitch + cePID.inPidRoll - cePID.inPidYaw;

    if(cePID.drivePower.motorDrivePower0> CE_PID_MAX_DRIVER_POWER){cePID.drivePower.motorDrivePower0 = CE_PID_MAX_DRIVER_POWER;}  //限制电机电调驱动强度在允许范围
    if(cePID.drivePower.motorDrivePower1 > CE_PID_MAX_DRIVER_POWER){cePID.drivePower.motorDrivePower1 = CE_PID_MAX_DRIVER_POWER;};
    if(cePID.drivePower.motorDrivePower2 > CE_PID_MAX_DRIVER_POWER){cePID.drivePower.motorDrivePower2 = CE_PID_MAX_DRIVER_POWER;};
    if(cePID.drivePower.motorDrivePower3 > CE_PID_MAX_DRIVER_POWER){cePID.drivePower.motorDrivePower3 = CE_PID_MAX_DRIVER_POWER;};

    if(cePID.drivePower.motorDrivePower0 < CE_PID_MIN_DRIVER_POWER){cePID.drivePower.motorDrivePower0 = CE_PID_MIN_DRIVER_POWER;};  //限制电机电调驱动强度在允许范围
    if(cePID.drivePower.motorDrivePower1 < CE_PID_MIN_DRIVER_POWER){cePID.drivePower.motorDrivePower1 = CE_PID_MIN_DRIVER_POWER;};
    if(cePID.drivePower.motorDrivePower2 < CE_PID_MIN_DRIVER_POWER){cePID.drivePower.motorDrivePower2 = CE_PID_MIN_DRIVER_POWER;};
    if(cePID.drivePower.motorDrivePower3 < CE_PID_MIN_DRIVER_POWER){cePID.drivePower.motorDrivePower3 = CE_PID_MIN_DRIVER_POWER;};
}

/**
  * @brief  根据当前无人机加速度、角速度、姿态角、期望姿态角，直接计算出四个电调应有的驱动强度
  * @param  ceNowAcc:当前无人机三轴加速度数据，单位G
  * @param  ceNowGyr:当前无人机三轴角速度数据，单位度/s
  * @param  ceNowStatus:当前无人机姿态角数据
  * @param  ceHopeStatus:期望无人机处于的姿态角数据
  * @param  dtS:程序执行周期，单位S
  * @param  drivePower：计算的输出结果，四个电机的驱动强度
  */
CeMDDrivePower* cePID_calculate(CeStatus* ceNowStatus, CeStatus* ceHopeStatus,fp32 dtS)
{
    ceParCtlOp.beforePIDHook();                 //PID计算前接口函数，用于保存PID计算前的数据

    if(ceHopeStatus->accelerator == 0)          //如果期望油门为0，则不进行PID计算
    {
        cePID.drivePower.motorDrivePower0 = CE_PID_MIN_DRIVER_POWER;
        cePID.drivePower.motorDrivePower1 = CE_PID_MIN_DRIVER_POWER;
        cePID.drivePower.motorDrivePower2 = CE_PID_MIN_DRIVER_POWER;
        cePID.drivePower.motorDrivePower3 = CE_PID_MIN_DRIVER_POWER;
			  ceParCtlOp.afterPIDHook();                  //PID计算后接口函数，用于保存PID计算后的数据
        return &(cePID.drivePower);
    }
    
    cePID.ceNowStatus = ceNowStatus;
    cePID.ceHopeStatus = ceHopeStatus;
    cePID.dtS = dtS;
    
    ceTaskOp.inCriticalSection(); 	//进入代码临界段（不清楚的可以百度），在操作系统环境下以下内容执行过程中禁止任务切换，防止其它线程修改当前角、加、姿态等数据。裸奔下则可忽略。
   
    cePID_resetErrByAccelerator();
    cePID_calculatePitch();                                                       
    cePID_calculateRoll(); 
    cePID_calculateYaw(); 
    cePID_calculateAccelerator();
    cePID_calculateAltitude();
    cePID_calculateDriverPower();

    ceTaskOp.outCriticalSection();                                      //退出代码临界段

    ceParCtlOp.afterPIDHook();                  //PID计算后接口函数，用于保存PID计算后的数据

    return &(cePID.drivePower);
}

/**
  * @brief  CePID模块操作对象定义
  */
const CePIDOp cePIDOp = {cePID_initial,cePID_calculate};

#ifdef __cplusplus
 }
#endif //__cplusplus

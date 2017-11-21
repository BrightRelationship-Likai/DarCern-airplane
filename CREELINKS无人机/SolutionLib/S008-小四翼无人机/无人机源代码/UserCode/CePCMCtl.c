/**
  ******************************************************************************
  * @file    CePCM.c
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
#include "CePCMCtl.h"
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
  * @brief  CePCM模块初始化
  * @return 系统状态码
  */
void cePCMCtl_initial(void)
{

}

uint8 cePCMCtl_checkConnectStatus(void)
{
    return 1;
}

fp32      cePCMCtl_getHopePitch(void)
{
        return 0;
}

fp32      cePCMCtl_getHopeRoll(void)
{
        return 0;
}

fp32      cePCMCtl_getHopeYaw(void)
{
        return 0;
}

fp32      cePCMCtl_getHopeAccelerator(void)
{
        return 0;
}

/**
  * @brief  初始化CePCM模块操作对象
  */
const CePCMCtlOp cePCMCtlOp = {cePCMCtl_initial,cePCMCtl_checkConnectStatus,cePCMCtl_getHopePitch,cePCMCtl_getHopeRoll,cePCMCtl_getHopeYaw,cePCMCtl_getHopeAccelerator};


#ifdef __cplusplus
}
#endif //__cplusplus

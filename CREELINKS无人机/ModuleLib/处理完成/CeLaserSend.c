/**
  ******************************************************************************
  * @file    CeLaserSend.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeLaserSend模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeLaserSend.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

void ceLaserSend_timerCallBack(void* pAddPar)
{

    if(((CeLaserSend*)(pAddPar))->workMode == 0x81)//On
    {
        ((CeLaserSend*)(pAddPar))->workMode = 0x01;
        ceGpioOp.resetBit(&(((CeLaserSend*)(pAddPar))->ceGpio));
    }else
    {
        ((CeLaserSend*)(pAddPar))->workMode = 0x81;
        ceGpioOp.setBit(&(((CeLaserSend*)(pAddPar))->ceGpio));
    }
}
/**
  * @brief  CeLaserSend模块初始化
  * @param  ceLaserSend:CeLaserSend属性对象
  * @param  cePWM:CeLaserSend模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceLaserSend_initialByPwm(CeLaserSend* ceLaserSend, CE_RESOURCE cePwm)
{
    ceLaserSend->cePwm.ceResource = cePwm;
    ceLaserSend->cePwm.cycleNs = 26315;      //38KHz
    ceLaserSend->cePwm.dutyNs = 26315 / 3;   //1/3的占空比
    cePwmOp.initial(&(ceLaserSend->cePwm));
    ceLaserSend->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief 使用一个Gpio口及一个定时器进行CeLaserSend模块初始化
  * @param ceLaserSend:CeLaserSend属性对象指针
  * @param cePwm:CeLaserSend模块使用的资源号
  * @param ceTimer:CeTimer模块使用的定时器资源号
  */
CE_STATUS ceLaserSend_initialByGpio(CeLaserSend* ceLaserSend, CE_RESOURCE ceGpio, CE_RESOURCE ceTimer)
{
    ceLaserSend->ceTimer.ceResource = ceTimer;
    ceLaserSend->ceTimer.intervalNs = 26315/2;//38KHz
    ceLaserSend->ceTimer.pAddPar = ceLaserSend;
    ceLaserSend->ceTimer.callBack = ceLaserSend_timerCallBack;
    ceTimerOp.initial(&(ceLaserSend->ceTimer));
    ceLaserSend->workMode = 0x01;
    return CE_STATUS_SUCCESS;
}


/**
  * @brief   配置红外发射管为发射状态，即红外发射一直发出红外光
  * @param   ceLaserSend:CeLaserSend属性对象指针
 */
void ceLaserSend_setOn(CeLaserSend* ceLaserSend)
{
    if(ceLaserSend->workMode == 0x00)
    {
        cePwmOp.start(&(ceLaserSend->cePwm));
    }else
    {
        ceTimerOp.start(&(ceLaserSend->ceTimer)) ;
    }
}

/**
  * @brief   配置红外发射管为关闭状态，即红外发射管不发出红外光
  * @param   ceLaserSend:CeLaserSend属性对象指针
 */
void ceLaserSend_setOff(CeLaserSend* ceLaserSend)
{
    if(ceLaserSend->workMode == 0x00)
    {
        cePwmOp.stop(&(ceLaserSend->cePwm));
    }else
    {
        ceTimerOp.stop(&(ceLaserSend->ceTimer)) ;
        ceGpioOp.resetBit(&(ceLaserSend->ceGpio));
    }
}


CeLaserSendOp ceLaserSendOp = {ceLaserSend_initialByPwm, ceLaserSend_initialByGpio,ceLaserSend_setOn,ceLaserSend_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus

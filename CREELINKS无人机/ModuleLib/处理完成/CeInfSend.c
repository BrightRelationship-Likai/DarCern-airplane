/**
  ******************************************************************************
  * @file    CeInfSend.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeInfSend模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeInfSend.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeInfSend定时器回调函数
  * @param  pAddPar:CeInfSend属性对象指针
  * @return None
  */
void ceInfSend_timerCallBack(void* pAddPar)
{

    if(((CeInfSend*)(pAddPar))->workMode == 0x81)//On
    {
        ((CeInfSend*)(pAddPar))->workMode = 0x01;
        ceGpioOp.resetBit(&(((CeInfSend*)(pAddPar))->ceGpio));
    }else
    {
        ((CeInfSend*)(pAddPar))->workMode = 0x81;
        ceGpioOp.setBit(&(((CeInfSend*)(pAddPar))->ceGpio));
    }
}
/**
  * @brief  CeInfSend模块初始化
  * @param  ceInfSend:CeInfSend属性对象
  * @param  cePWM:CeInfSend模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceInfSend_initialByPwm(CeInfSend* ceInfSend, CE_RESOURCE cePwm)
{
    ceInfSend->cePwm.ceResource = cePwm;
    ceInfSend->cePwm.cycleNs = 26315;//38KHz
    ceInfSend->cePwm.dutyNs = 26315 / 3;//1/3的占空比
    cePwmOp.initial(&(ceInfSend->cePwm));
    ceInfSend->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief 使用一个Gpio口及一个定时器进行CeInfSend模块初始化
  * @param ceInfSend:CeInfSend属性对象指针
  * @param cePwm:CeInfSend模块使用的资源号
  * @param ceTimer:CeTimer模块使用的定时器资源号
  */
CE_STATUS ceInfSend_initialByGpio(CeInfSend* ceInfSend, CE_RESOURCE ceGpio, CE_RESOURCE ceTimer)
{
    ceInfSend->ceTimer.ceResource = ceTimer;
    ceInfSend->ceTimer.intervalNs = 26315/2;//38KHz
    ceInfSend->ceTimer.pAddPar = ceInfSend;
    ceInfSend->ceTimer.callBack = ceInfSend_timerCallBack;
    ceTimerOp.initial(&(ceInfSend->ceTimer));
    ceInfSend->workMode = 0x01;
    return CE_STATUS_SUCCESS;
}


/**
  * @brief   配置红外发射管为发射状态，即红外发射一直发出红外光
  * @param   ceInfSend:CeInfSend属性对象指针
 */
void ceInfSend_setOn(CeInfSend* ceInfSend)
{
    if(ceInfSend->workMode == 0x00)
    {
        cePwmOp.start(&(ceInfSend->cePwm));
    }else
    {
        ceTimerOp.start(&(ceInfSend->ceTimer)) ;
    }
}

/**
  * @brief   配置红外发射管为关闭状态，即红外发射管不发出红外光
  * @param   ceInfSend:CeInfSend属性对象指针
 */
void ceInfSend_setOff(CeInfSend* ceInfSend)
{
    if(ceInfSend->workMode == 0x00)
    {
        cePwmOp.stop(&(ceInfSend->cePwm));
    }else
    {
        ceTimerOp.stop(&(ceInfSend->ceTimer)) ;
        ceGpioOp.resetBit(&(ceInfSend->ceGpio));
    }
}

const CeInfSendOp ceInfSendOp = {ceInfSend_initialByPwm, ceInfSend_initialByGpio, ceInfSend_setOn, ceInfSend_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus

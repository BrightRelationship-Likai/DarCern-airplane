/**
  ******************************************************************************
  * @file    CeInfRecv.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeInfRecv模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeInfRecv.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus


/**
  * @brief  CeInfRecv外部中断Int回调函数
  * @param  pAddPar:CeInfRecv属性对象指针
  * @param  cePWM:CeInfRecv模块使用的资源号
  * @return None
  */
void ceInfRecv_callBackRecvSignal(void* pAddPar)
{
    CeInfRecv* ceInfRecv = (CeInfRecv*)pAddPar;
    if(ceInfRecv->callBackRecvSignal != CE_NULL)
    {
        ceInfRecv->callBackRecvSignal();
    }
}

/**
  * @brief  CeInfRecv模块初始化
  * @param  ceInfRecv:CeInfRecv属性对象
  * @param  cePWM:CeInfRecv模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceInfRecv_initialByGpio(CeInfRecv* ceInfRecv, CE_RESOURCE ceGpio)
{
    ceInfRecv->ceGpio.ceResource = ceGpio;
    ceInfRecv->ceGpio.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceInfRecv->ceGpio));
    ceInfRecv->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief CeInfRecv模块初始化，使用一个Int口
  * @param ceInfRecv:CeInfRecv属性对象指针
  * @param ceGpio:CeInfRecv模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS   ceInfRecv_initialByInt(CeInfRecv* ceInfRecv, CE_RESOURCE ceInt,void(*callBackRecvSignal)(void))
{
    ceInfRecv->callBackRecvSignal = callBackRecvSignal;
    ceInfRecv->workMode = 0x01;

    ceInfRecv->ceInt.ceResource = ceInt;
    ceInfRecv->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_FALLING;//收到红外信号时，为低电平
    ceInfRecv->ceInt.callBack = ceInfRecv_callBackRecvSignal;
    ceInfRecv->ceInt.pAddPar = ceInfRecv;
    ceIntOp.initial(&(ceInfRecv->ceInt));
    ceIntOp.start(&(ceInfRecv->ceInt));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief CeInfRecv模块初始化
  * @param ceInfRecv:CeInfRecv属性对象指针
  * @return 获得红外接收管的接收状态，返回0x01:收到红外信号同； 返回0x00:未收到红外信号
  */
uint8 ceInfRecv_getStatus(CeInfRecv* ceInfRecv)
{
    if(ceInfRecv->workMode == 0X00)
    {
       return ceGpioOp.getBit(&(ceInfRecv->ceGpio));
    }else
    {
        return ceIntOp.getBit(&(ceInfRecv->ceInt));
    }

}

const CeInfRecvOp ceInfRecvOp = {ceInfRecv_initialByGpio, ceInfRecv_initialByInt, ceInfRecv_getStatus};

#ifdef __cplusplus
 }
#endif //__cplusplus

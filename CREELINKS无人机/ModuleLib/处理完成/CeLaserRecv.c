/**
  ******************************************************************************
  * @file    CeLaserRecv.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeLaserRecv模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeLaserRecv.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus


/**
  * @brief  CeLaserRecv模块初始化
  * @param  ceLaserRecv:CeLaserRecv属性对象
  * @param  cePWM:CeLaserRecv模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceLaserRecv_initial(CeLaserRecv* ceLaserRecv, CE_RESOURCE ceGpio)
{
    ceLaserRecv->ceGpio.ceResource = ceGpio;
    ceLaserRecv->ceGpio.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceLaserRecv->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief CeLaserRecv模块初始化
  * @param ceLaserRecv:CeLaserRecv属性对象指针
  * @return 获得激光接收管的接收状态，返回0x01:收到激光信号同； 返回0x00:未收到激光信号
 */
uint8 ceLaserRecv_getStatus(CeLaserRecv* ceLaserRecv)
{
    if(ceGpioOp.getBit(&(ceLaserRecv->ceGpio)) == 0x00)//获取IO口电平
    {
        return 0x01;
    }else
    {
        return 0x00;
    }
}

CeLaserRecvOp ceLaserRecvOp = {ceLaserRecv_initial, ceLaserRecv_getStatus};

#ifdef __cplusplus
 }
#endif //__cplusplus

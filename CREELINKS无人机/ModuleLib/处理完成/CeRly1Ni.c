/**
  ******************************************************************************
  * @file    CeRly1Ni.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRly1Ni模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeRly1Ni.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief    CeRly1Ni模块初始化
  * @param    ceRly1Ni:CeRly1Ni属性对象
  * @param    ceGpio:CeRly1Ni模块使用的Gpio接口的资源号
  * @return   系统状态码 可能的值CE_STATUS_SUCCESS
  */
CE_STATUS ceRly1Ni_initial(CeRly1Ni* ceRly1Ni, CE_RESOURCE ceGpio)
{
    ceRly1Ni->ceGpio.ceResource = ceGpio;
    ceRly1Ni->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRly1Ni->ceGpio));
    ceGpioOp.resetBit(&(ceRly1Ni->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
* @brief    设置继电器闭合
* @param    ceRly1Ni:CeRly1Ni属性对象
*/
void ceRly1Ni_setOn(CeRly1Ni* ceRly1Ni)
{
    ceGpioOp.setBit(&(ceRly1Ni->ceGpio));
}

/**
* @brief    设置继电器断开
* @param    ceRly1Ni:CeRly1Ni属性对象
*/
void ceRly1Ni_setOff(CeRly1Ni* ceRly1Ni)
{
    ceGpioOp.resetBit(&(ceRly1Ni->ceGpio));
}

/**
* @brief    CeRly1Ni可用操作合集
*/
const CeRly1NiOpBase ceRly1NiOp = {ceRly1Ni_initial, ceRly1Ni_setOn, ceRly1Ni_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus


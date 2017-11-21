/**
  ******************************************************************************
  * @file    CeRly1.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRly1模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeRly1.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief    CeRly1模块初始化
  * @param    ceRly1:CeRly1属性对象
  * @param    ceGpio:CeRly1模块使用的Gpio接口的资源号
  * @return   系统状态码 可能的值CE_STATUS_SUCCESS
  */
CE_STATUS ceRly1_initial(CeRly1* ceRly1, CE_RESOURCE ceGpio)
{
    ceRly1->ceGpio.ceResource = ceGpio;
    ceRly1->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRly1->ceGpio));
    ceGpioOp.resetBit(&(ceRly1->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
* @brief    设置继电器闭合
* @param    ceRly1:CeRly1属性对象
*/
void ceRly1_setOn(CeRly1* ceRly1)
{
    ceGpioOp.setBit(&(ceRly1->ceGpio));
}

/**
* @brief    设置继电器断开
* @param    ceRly1:CeRly1属性对象
*/
void ceRly1_setOff(CeRly1* ceRly1)
{
    ceGpioOp.resetBit(&(ceRly1->ceGpio));
}

/**
* @brief    CeRly1可用操作合集
*/
const CeRly1Op ceRly1Op = {ceRly1_initial, ceRly1_setOn, ceRly1_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus


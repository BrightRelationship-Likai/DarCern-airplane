/**
  ******************************************************************************
  * @file    CeRly2.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRly2模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeRly2.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  CeRly2模块初始化
  * @param  ceRly2:CeRly2属性对象
  * @param  ceRly2:CeRly2模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceRly2_initial(CeRly2* ceRly2, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1)
{
    ceRly2->ceGpio0.ceResource = ceGpio0;
    ceRly2->ceGpio0.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRly2->ceGpio0));
    ceGpioOp.resetBit(&(ceRly2->ceGpio0));

    ceRly2->ceGpio1.ceResource = ceGpio1;
    ceRly2->ceGpio1.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRly2->ceGpio1));
    ceGpioOp.resetBit(&(ceRly2->ceGpio1));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  设置继电器闭合
  * @param  ceRly2:CeRly2属性对象
  * @param  rlyIndex:需要闭合的继电器序号
  */
void ceRly2_setOn(CeRly2* ceRly2, uint8 rlyIndex)
{
    if (rlyIndex == 0)
    {
       ceGpioOp.setBit(&(ceRly2->ceGpio0));
    } else if (rlyIndex == 1)
    {
       ceGpioOp.setBit(&(ceRly2->ceGpio1));
    }
}

/**
  * @brief    设置继电器断开
  * @param    ceRly2:CeRly2属性对象
  * @param    rlyIndex:需要断开的继电器序号
  */
void ceRly2_setOff(CeRly2* ceRly2, uint8 rlyIndex)
{
    if (rlyIndex == 0)
    {
         ceGpioOp.resetBit(&(ceRly2->ceGpio0));
    }
    else if (rlyIndex == 1)
    {
         ceGpioOp.resetBit(&(ceRly2->ceGpio1));
    }
}

/**
  * @brief    CeRly2可用操作合集对象
  */
const CeRly2Op ceRly2Op = {ceRly2_initial,ceRly2_setOn,ceRly2_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus


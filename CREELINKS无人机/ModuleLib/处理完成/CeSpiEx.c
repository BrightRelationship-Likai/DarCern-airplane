/**
  ******************************************************************************
  * @file    CeSpiEx.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSpiEx模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeSpiEx.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeSpiEx模块初始化
  * @param  ceSpiEx:CeSpiEx属性对象指针
  * @param  ceGpio0:CeSpiEx模块使用的第一个Gpio资源号
  * @param  ceGpio1:CeSpiEx模块使用的第二个Gpio资源号
  * @param  ceGpio2:CeSpiEx模块使用的第三个Gpio资源号
  * @return 系统状态码
*/
CE_STATUS ceSpiEx_initial(CeSpiEx* ceSpiEx,CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ceSpiEx->ceGpio0.ceResource = ceGpio0;
    ceSpiEx->ceGpio0.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceSpiEx->ceGpio0));

    ceSpiEx->ceGpio1.ceResource = ceGpio1;
    ceSpiEx->ceGpio1.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceSpiEx->ceGpio1));

    ceSpiEx->ceGpio2.ceResource = ceGpio2;
    ceSpiEx->ceGpio2.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceSpiEx->ceGpio2));

    ceGpioOp.resetBit(&(ceSpiEx->ceGpio0));
    ceGpioOp.resetBit(&(ceSpiEx->ceGpio1));
    ceGpioOp.resetBit(&(ceSpiEx->ceGpio2));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  使能通道
  * @param  ceSpiEx:CeSpiEx属性对象指针
  * @param  portIndex:需要使能的通道号，0－2
*/
void ceSpiEx_enablePort(CeSpiEx* ceSpiEx, uint8 portIndex)
{
     switch (portIndex)
     {
     case 0:
         ceGpioOp.setBit(&(ceSpiEx->ceGpio0));
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio1));
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio2));
          break;
     case 1:
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio0));
         ceGpioOp.setBit(&(ceSpiEx->ceGpio1));
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio2));
          break;
     case 2:
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio0));
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio1));
         ceGpioOp.setBit(&(ceSpiEx->ceGpio2));
          break;
     default:
          break;
     }
}

/*
 *CeSpiEx操作对象
*/
const CeSpiExOp ceSpiExOp = {ceSpiEx_initial, ceSpiEx_enablePort};

#ifdef __cplusplus
 }
#endif //__cplusplus


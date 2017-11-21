/**
  ******************************************************************************
  * @file    CeGpioInEx16.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeGpioInEx16模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeGpioInEx16.h"

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeGpioInEx16模块使用Gpio进行初始化
  * @param  ceGpioInEx16:CeGpioInEx16属性对象
  * @param  ceGpio0:CeGpioInEx16模块使用的第一个Gpio的资源号
  * @param  ceGpio1:CeGpioInEx16模块使用的第二个Gpio的资源号
  * @param  ceGpio2:CeGpioInEx16模块使用的第三个Gpio的资源号
  * @return 系统状态码
  */
CE_STATUS ceGpioInEx16_initialByGpio(CeGpioInEx16* ceGpioInEx16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ceGpioInEx16->ceTg.ceResource = CE_NULL_RESOURCE;
    ceGpioInEx16->ceTg.ceResource0 = ceGpio0;
    ceGpioInEx16->ceTg.ceResource1 = ceGpio1;
    ceGpioInEx16->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ceGpioInEx16->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_IPU);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeGpioInEx16模块初始化
  * @param  ceGpioInEx16:CeGpioInEx16属性对象
  * @param  ceTg:CeGpioInEx16模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceGpioInEx16_initialByTg(CeGpioInEx16* ceGpioInEx16, CE_RESOURCE ceTg)
{
    ceGpioInEx16->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceGpioInEx16->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_IPU);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取指定索引的Gpio口电平
  * @param  ceGpioInEx16:CeGpioInEx16属性对象指针
  * @param  index:欲操作Gpio口的索引，范围0-15
  * @return 返回0x01:高电平；返回0x00:低电平
  */
uint8 ceGpioInEx16_getBit(CeGpioInEx16* ceGpioInEx16, uint8 index)
{
    uint8 i,val;
    ceGpioOp.setBit(&(ceGpioInEx16->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ceGpioInEx16->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.setBit(&(ceGpioInEx16->ceTg));
    ceSystemOp.delayUs(1);
    for( i = 0; i < 16; i++)
    {
        if (i == (15 - index))
        {

            val = ceTgOp.getGpio2Bit(&(ceGpioInEx16->ceTg));
            ceSystemOp.delayUs(1);
            ceGpioOp.resetBit(&(ceGpioInEx16->ceTg));
            ceSystemOp.delayUs(1);
            ceGpioOp.setBit(&(ceGpioInEx16->ceTg));
            ceSystemOp.delayUs(1);
            break;
        }

        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ceGpioInEx16->ceTg));
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ceGpioInEx16->ceTg));
        ceSystemOp.delayUs(1);
    }
    return val;
}


/**
  * @brief  获取全部IO口的状态，高位对应Gpio15
  * @param  ceGpioInEx16:CeGpioInEx16属性对象指针
  */
uint16      ceGpioInEx16_getData(CeGpioInEx16* ceGpioInEx16)
{
    uint8 i;
    uint16 temp = 0;
    ceGpioOp.setBit(&(ceGpioInEx16->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ceGpioInEx16->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.setBit(&(ceGpioInEx16->ceTg));
    ceSystemOp.delayUs(1);
    for( i = 0; i < 16; i++)
    {
        temp <<= 1;
        temp |= ceTgOp.getGpio2Bit(&(ceGpioInEx16->ceTg));

        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ceGpioInEx16->ceTg));
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ceGpioInEx16->ceTg));
        ceSystemOp.delayUs(1);
    }
    return temp;
}

/**
  * @brief  CeGpioInEx16模块操作对象定义
  */
const CeGpioInEx16Op ceGpioInEx16Op = {ceGpioInEx16_initialByGpio, ceGpioInEx16_initialByTg, ceGpioInEx16_getBit,ceGpioInEx16_getData};

#ifdef __cplusplus
 }
#endif //__cplusplus

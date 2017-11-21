/**
  ******************************************************************************
  * @file    CeGpioOutEx16.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeGpioOutEx16模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeGpioOutEx16.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  向74HC595写数据
  * @param  ceTg:CeGpioOutEx16属性对象中的CeTg
  * @param  data:欲写到74HC595de595的数据
  * @return None
  */
void ceGpioOutEx16_write595Byte(CeTg* ceTg, uint16 data)
{
    int i;
    for(i=0;i<16;i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
        if( (data & 0x8000) == 0x0000)
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
        }
        else
        {
            ceGpioOp.setBit(&(ce8Segx1->ceGpio1));
        }
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ce8Segx1->ceGpio0));
        ceSystemOp.delayUs(1);
        data <<= 1;
    }
    ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
}

/**
  * @brief  CeGpioOutEx16模块内部用到的初始化
  * @param  ceGpioOutEx16:CeGpioOutEx16属性对象
  * @return None
  */
void ceGpioOutEx16_initial(CeGpioOutEx16* ceGpioOutEx16)
{
    ceGpioOp.resetBit(&(ceGpioOutEx16->ceTg));//SRCL
    ceGpioOp.resetBit(&(ceGpioOutEx16->ceTg));//SER
    ceGpioOp.resetBit(&(ceGpioOutEx16->ceTg));//RCLK
    ceGpioOutEx16->ceGpioStatus = 0x0000;
    ceGpioOutEx16_write595Byte(&(ceGpioOutEx16->ceTg), ceGpioOutEx16->ceGpioStatus);
}

/**
  * @brief  CeGpioOutEx16模块使用Gpio进行初始化
  * @param  ceGpioOutEx16:CeGpioOutEx16属性对象
  * @param  ceGpio0:CeGpioOutEx16模块使用的第一个Gpio的资源号
  * @param  ceGpio1:CeGpioOutEx16模块使用的第二个Gpio的资源号
  * @param  ceGpio2:CeGpioOutEx16模块使用的第三个Gpio的资源号
  * @return 系统状态码
  */
CE_STATUS ceGpioOutEx16_initialByGpio(CeGpioOutEx16* ceGpioOutEx16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ceGpioOutEx16->ceTg.ceResource = CE_NULL_RESOURCE;
    ceGpioOutEx16->ceTg.ceResource0 = ceGpio0;
    ceGpioOutEx16->ceTg.ceResource1 = ceGpio1;
    ceGpioOutEx16->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ceGpioOutEx16->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOutEx16_initial(ceGpioOutEx16);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeGpioOutEx16模块初始化
  * @param  ceGpioOutEx16:CeGpioOutEx16属性对象
  * @param  ceTg:CeGpioOutEx16模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceGpioOutEx16_initialByTg(CeGpioOutEx16* ceGpioOutEx16, CE_RESOURCE ceTg)
{
    ceGpioOutEx16->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceGpioOutEx16->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOutEx16_initial(ceGpioOutEx16);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  设置指定索引的Gpio口
  * @param  ceGpioOutEx16:CeGpioOutEx16属性对象
  * @param  index:欲操作Gpio口的索引，范围0-15
  * @return None
  */
void ceGpioOutEx16_setBit(CeGpioOutEx16* ceGpioOutEx16, uint8 index)
{
    ceGpioOutEx16->ceGpioStatus |= (0x0001 << index);
    ceGpioOutEx16_write595Byte(&(ceGpioOutEx16->ceTg), ceGpioOutEx16->ceGpioStatus);
}

/**
  * @brief  复位指定索引的Gpio口
  * @param  ceGpioOutEx16:CeGpioOutEx16属性对象
  * @param  index:欲操作Gpio口的索引，范围0-15
  * @return None
  */
void ceGpioOutEx16_resetBit(CeGpioOutEx16* ceGpioOutEx16, uint8 index)
{
    ceGpioOutEx16->ceGpioStatus &= (~(0x0001 << index));
    ceGpioOutEx16_write595Byte(&(ceGpioOutEx16->ceTg), ceGpioOutEx16->ceGpioStatus);
}

/**
  * @brief 以一个16位数值设置全部Gpio口的状态，其中最低位对应Gpio0。
  * @param  ceGpioOutEx16:CeGpioOutEx16属性对象
  * @param data:模块所有口的电平输出值
  * @return None
  */
void ceGpioOutEx16_setData(CeGpioOutEx16* ceGpioOutEx16,uint16 data)
{
    ceGpioOutEx16->ceGpioStatus = data ;
    ceGpioOutEx16_write595Byte(&(ceGpioOutEx16->ceTg), ceGpioOutEx16->ceGpioStatus);
}

const CeGpioOutEx16Op ceGpioOutEx16Op = {ceGpioOutEx16_initialByGpio, ceGpioOutEx16_initialByTg, ceGpioOutEx16_setBit, ceGpioOutEx16_resetBit,ceGpioOutEx16_setData};

#ifdef __cplusplus
 }
#endif //__cplusplus

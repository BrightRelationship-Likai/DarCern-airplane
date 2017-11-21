/**
  ******************************************************************************
  * @file    CeRly4.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRly4模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeRly4.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  向74HC595写数据
  * @param  ceTg:Ce8Segx1属性对象中的CeTg
  * @param  data:欲写到74HC595de595的数据
  * @return None
  */
void ceRly4_write595Byte(CeTg* ceTg, uint8 data)
{
    int i;
    for(i=0;i<8;i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
        if( (data & 0x80) == 0x80)
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
        }else
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
  * @brief  CeRly4模块初始化
  * @param  ceRly4:CeRly4属性对象
  * @param   ceTg:CeRly4模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceRly4_initial(CeRly4* ceRly4, CE_RESOURCE ceTg)
{
    ceRly4->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceRly4->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceRly4->ceTg));
    ceGpioOp.resetBit(&(ceRly4->ceTg));
    ceGpioOp.resetBit(&(ceRly4->ceTg));
    ceRly4->rlyStatus = 0x00;
     ceRly4_write595Byte(&(ceRly4->ceTg),0x00);
     return CE_STATUS_SUCCESS;
}

/**
  * @brief  使用三个Gpio口来完成CeRly4模块初始化
  * @param  ceRly4:CeRly4属性对象指针
  * @param  ceGpio0:第一个Gpio口
  * @param  ceGpio1:第二个Gpio口
  * @param  ceGpio2:第三个Gpio口
  * @return 系统状态码
*/
CE_STATUS ceRly4_initialWithGpio(CeRly4* ceRly4, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ceRly4->ceTg.ceResource0 = ceGpio0;
    ceRly4->ceTg.ceResource1 = ceGpio1;
    ceRly4->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ceRly4->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceRly4->ceTg));
    ceGpioOp.resetBit(&(ceRly4->ceTg));
    ceGpioOp.resetBit(&(ceRly4->ceTg));
     ceRly4_write595Byte(&(ceRly4->ceTg), 0x00);
     return CE_STATUS_SUCCESS;
}

/**
  * @brief 设置继电器闭合
  * @param ceRly4:CeRly4属性对象指针
  * @param rlyIndex:需要闭合的继电器序号
*/
void ceRly4_setOn(CeRly4* ceRly4, uint8 rlyIndex)
{
    if (rlyIndex >= 4)
    {
         return;
    }
    ceRly4->rlyStatus |= (0x01 << rlyIndex);
    ceRly4_write595Byte(&(ceRly4->ceTg), ceRly4->rlyStatus);
}
/**
  * @brief 设置继电器断开
  * @param ceRly4:CeRly4属性对象指针
  * @param rlyIndex:需要断开的继电器序号
*/
void ceRly4_setOff(CeRly4* ceRly4, uint8 rlyIndex)
{
    if (rlyIndex >= 4)
    {
         return;
    }
    ceRly4->rlyStatus &= (~(0x01 << rlyIndex));
    ceRly4_write595Byte(&(ceRly4->ceTg), ceRly4->rlyStatus);
}
/*
*CeRly4操作对象定义
*/
const CeRly4Op ceRly4Op = {ceRly4_initial,ceRly4_initialWithGpio,ceRly4_setOn,ceRly4_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus


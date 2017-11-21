/**
******************************************************************************
* @file    CeRly8.c
* @author  Creelinks Application Team
* @version V1.0.0
* @date    2016-10-17
* @brief   适用于CeRly8模块的驱动库文件
******************************************************************************
* @attention
*
*1)
*
* <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
******************************************************************************
*/
#include"CeRly8.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  向595发送串行数据
  * @param  ceRly8:CeRly8属性对象
  * @param  data:发送的数据
*/
void ceRly8_write595Byte(CeRly8* ceRly8, uint8 data)
{
    int i;
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    for (i = 0; i<8; i++)
    {
        if (data & 0x80 == 0x00)
        {
            ceGpioOp.resetBit(&(ceRly8->ceTg));
        }
        else
        {
            ceGpioOp.setBit(&(ceRly8->ceTg));
        }
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ceRly8->ceTg));
        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ceRly8->ceTg));
        ceSystemOp.delayUs(1);
        data <<= 1;
    }
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceGpioOp.setBit(&(ceRly8->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceSystemOp.delayUs(1);
}

/**
  * @brief  CeRly8模块初始化
  * @param  ceRly8:CeRly8属性对象
  * @param  ceTg:CeRly8模块使用的资源号
  * @return 系统状态码
*/
CE_STATUS ceRly8_initial(CeRly8* ceRly8, CE_RESOURCE ceTg)
{
    ceRly8->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceRly8->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceRly8->rlyStatus = 0x00;
    ceRly8_write595Byte(ceRly8, 0x00);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  使用三个Gpio口来完成CeRly8模块初始化
  * @param  ceRly8:CeRly8属性对象指针
  * @param  ceGpio0:第一个Gpio口
  * @param  ceGpio1:第二个Gpio口
  * @param  ceGpio2:第三个Gpio口
  * @return 系统状态码
*/
CE_STATUS ceRly8_initialWithGpio(CeRly8* ceRly8, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ceRly8->ceTg.ceResource0 = ceGpio0;
    ceRly8->ceTg.ceResource1 = ceGpio1;
    ceRly8->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ceRly8->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceGpioOp.resetBit(&(ceRly8->ceTg));
    ceRly8_write595Byte(ceRly8, 0x00);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief 设置继电器闭合
  * @param ceRly8:CeRly8属性对象指针
  * @param rlyIndex:需要闭合的继电器序号
*/
void ceRly8_setOn(CeRly8* ceRly8, uint8 rlyIndex)
{
    if (rlyIndex >= 4)
    {
        return;
    }
    ceRly8->rlyStatus |= (0x01 << rlyIndex);
    ceRly8_write595Byte(ceRly8, ceRly8->rlyStatus);
}
/**
  * @brief 设置继电器断开
  * @param ceRly8:CeRly8属性对象指针
  * @param rlyIndex:需要断开的继电器序号
*/
void ceRly8_setOff(CeRly8* ceRly8, uint8 rlyIndex)
{
    if (rlyIndex >= 4)
    {
        return;
    }
    ceRly8->rlyStatus &= (~(0x01 << rlyIndex));
    ceRly8_write595Byte(ceRly8, ceRly8->rlyStatus);
}
/*
  *CeRly8操作对象定义
*/
const CeRly8Op ceRly8Op = { ceRly8_initial,ceRly8_initialWithGpio,ceRly8_setOn,ceRly8_setOff };

#ifdef __cplusplus
}
#endif //__cplusplus


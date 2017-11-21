/**
  ******************************************************************************
  * @file    CeRly4.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly4ģ����������ļ�
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
  * @brief  ��74HC595д����
  * @param  ceTg:Ce8Segx1���Զ����е�CeTg
  * @param  data:��д��74HC595de595������
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
  * @brief  CeRly4ģ���ʼ��
  * @param  ceRly4:CeRly4���Զ���
  * @param   ceTg:CeRly4ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
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
  * @brief  ʹ������Gpio�������CeRly4ģ���ʼ��
  * @param  ceRly4:CeRly4���Զ���ָ��
  * @param  ceGpio0:��һ��Gpio��
  * @param  ceGpio1:�ڶ���Gpio��
  * @param  ceGpio2:������Gpio��
  * @return ϵͳ״̬��
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
  * @brief ���ü̵����պ�
  * @param ceRly4:CeRly4���Զ���ָ��
  * @param rlyIndex:��Ҫ�պϵļ̵������
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
  * @brief ���ü̵����Ͽ�
  * @param ceRly4:CeRly4���Զ���ָ��
  * @param rlyIndex:��Ҫ�Ͽ��ļ̵������
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
*CeRly4����������
*/
const CeRly4Op ceRly4Op = {ceRly4_initial,ceRly4_initialWithGpio,ceRly4_setOn,ceRly4_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus


/**
******************************************************************************
* @file    CeRly8.c
* @author  Creelinks Application Team
* @version V1.0.0
* @date    2016-10-17
* @brief   ������CeRly8ģ����������ļ�
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
  * @brief  ��595���ʹ�������
  * @param  ceRly8:CeRly8���Զ���
  * @param  data:���͵�����
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
  * @brief  CeRly8ģ���ʼ��
  * @param  ceRly8:CeRly8���Զ���
  * @param  ceTg:CeRly8ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
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
  * @brief  ʹ������Gpio�������CeRly8ģ���ʼ��
  * @param  ceRly8:CeRly8���Զ���ָ��
  * @param  ceGpio0:��һ��Gpio��
  * @param  ceGpio1:�ڶ���Gpio��
  * @param  ceGpio2:������Gpio��
  * @return ϵͳ״̬��
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
  * @brief ���ü̵����պ�
  * @param ceRly8:CeRly8���Զ���ָ��
  * @param rlyIndex:��Ҫ�պϵļ̵������
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
  * @brief ���ü̵����Ͽ�
  * @param ceRly8:CeRly8���Զ���ָ��
  * @param rlyIndex:��Ҫ�Ͽ��ļ̵������
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
  *CeRly8����������
*/
const CeRly8Op ceRly8Op = { ceRly8_initial,ceRly8_initialWithGpio,ceRly8_setOn,ceRly8_setOff };

#ifdef __cplusplus
}
#endif //__cplusplus


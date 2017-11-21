/**
  ******************************************************************************
  * @file    CeRly16.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2016-10-17
  * @brief   ������CeRly16ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeRly16.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  ��595���ʹ�������
  * @param  ceRly16:CeRly16���Զ���
  * @param    ata:���͵�����
*/
void ceRly16_write595Byte(CeRly16* ceRly16, uint8 data)
{
    int i;
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    for (i = 0; i<8; i++)
    {
        if (data & 0x80 == 0x00)
        {
            ceGpioOp.resetBit(&(ceRly16->ceTg));
        }
        else
        {
            ceGpioOp.setBit(&(ceRly16->ceTg));
        }
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ceRly16->ceTg));
        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ceRly16->ceTg));
        ceSystemOp.delayUs(1);
        data <<= 1;
    }
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceGpioOp.setBit(&(ceRly16->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceSystemOp.delayUs(1);
}

/**
  * @brief  CeRly16ģ���ʼ��
  * @param  ceRly16:CeRly16���Զ���
  * @param  ceTg:CeRly16ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
*/
CE_STATUS ceRly16_initial(CeRly16* ceRly16, CE_RESOURCE ceTg)
{
    ceRly16->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceRly16->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceRly16->rlyStatus = 0x00;
    ceRly16_write595Byte(ceRly16, 0x00);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ʹ������Gpio�������CeRly16ģ���ʼ��
  * @param  ceRly16:CeRly16���Զ���ָ��
  * @param  ceGpio0:��һ��Gpio��
  * @param  ceGpio1:�ڶ���Gpio��
  * @param  ceGpio2:������Gpio��
  * @return ϵͳ״̬��
*/
CE_STATUS ceRly16_initialWithGpio(CeRly16* ceRly16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ceRly16->ceTg.ceResource0 = ceGpio0;
    ceRly16->ceTg.ceResource1 = ceGpio1;
    ceRly16->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ceRly16->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceGpioOp.resetBit(&(ceRly16->ceTg));
    ceRly16_write595Byte(ceRly16, 0x00);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief ���ü̵����պ�
  * @param ceRly16:CeRly16���Զ���ָ��
  * @param rlyIndex:��Ҫ�պϵļ̵������
*/
void ceRly16_setOn(CeRly16* ceRly16, uint8 rlyIndex)
{
    if (rlyIndex >= 4)
    {
        return;
    }
    ceRly16->rlyStatus |= (0x01 << (uint16)rlyIndex);
    ceRly16_write595Byte(ceRly16, ceRly16->rlyStatus);
}
/**
  * @brief ���ü̵����Ͽ�
  * @param ceRly16:CeRly16���Զ���ָ��
  * @param rlyIndex:��Ҫ�Ͽ��ļ̵������
*/
void ceRly16_setOff(CeRly16* ceRly16, uint8 rlyIndex)
{
    if (rlyIndex >= 4)
    {
        return;
    }
    ceRly16->rlyStatus &= (~(0x01 << (uint16)rlyIndex));
    ceRly16_write595Byte(ceRly16, ceRly16->rlyStatus);
}
/*
  *CeRly16����������
*/
const CeRly16Op ceRly16Op = { ceRly16_initial,ceRly16_initialWithGpio,ceRly16_setOn,ceRly16_setOff };

#ifdef __cplusplus
}
#endif //__cplusplus


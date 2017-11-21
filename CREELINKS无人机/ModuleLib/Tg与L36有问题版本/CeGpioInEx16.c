/**
  ******************************************************************************
  * @file    CeGpioInEx16.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeGpioInEx16ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeGpioInEx16.h"

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeGpioInEx16ģ��ʹ��Gpio���г�ʼ��
  * @param  ceGpioInEx16:CeGpioInEx16���Զ���
  * @param  ceGpio0:CeGpioInEx16ģ��ʹ�õĵ�һ��Gpio����Դ��
  * @param  ceGpio1:CeGpioInEx16ģ��ʹ�õĵڶ���Gpio����Դ��
  * @param  ceGpio2:CeGpioInEx16ģ��ʹ�õĵ�����Gpio����Դ��
  * @return ϵͳ״̬��
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
  * @brief  CeGpioInEx16ģ���ʼ��
  * @param  ceGpioInEx16:CeGpioInEx16���Զ���
  * @param  ceTg:CeGpioInEx16ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceGpioInEx16_initialByTg(CeGpioInEx16* ceGpioInEx16, CE_RESOURCE ceTg)
{
    ceGpioInEx16->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceGpioInEx16->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_IPU);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡָ��������Gpio�ڵ�ƽ
  * @param  ceGpioInEx16:CeGpioInEx16���Զ���ָ��
  * @param  index:������Gpio�ڵ���������Χ0-15
  * @return ����0x01:�ߵ�ƽ������0x00:�͵�ƽ
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
  * @brief  ��ȡȫ��IO�ڵ�״̬����λ��ӦGpio15
  * @param  ceGpioInEx16:CeGpioInEx16���Զ���ָ��
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
  * @brief  CeGpioInEx16ģ�����������
  */
const CeGpioInEx16Op ceGpioInEx16Op = {ceGpioInEx16_initialByGpio, ceGpioInEx16_initialByTg, ceGpioInEx16_getBit,ceGpioInEx16_getData};

#ifdef __cplusplus
 }
#endif //__cplusplus

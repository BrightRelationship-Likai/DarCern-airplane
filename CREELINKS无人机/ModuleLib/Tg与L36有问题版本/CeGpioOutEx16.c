/**
  ******************************************************************************
  * @file    CeGpioOutEx16.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeGpioOutEx16ģ����������ļ�
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
  * @brief  ��74HC595д����
  * @param  ceTg:CeGpioOutEx16���Զ����е�CeTg
  * @param  data:��д��74HC595de595������
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
  * @brief  CeGpioOutEx16ģ���ڲ��õ��ĳ�ʼ��
  * @param  ceGpioOutEx16:CeGpioOutEx16���Զ���
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
  * @brief  CeGpioOutEx16ģ��ʹ��Gpio���г�ʼ��
  * @param  ceGpioOutEx16:CeGpioOutEx16���Զ���
  * @param  ceGpio0:CeGpioOutEx16ģ��ʹ�õĵ�һ��Gpio����Դ��
  * @param  ceGpio1:CeGpioOutEx16ģ��ʹ�õĵڶ���Gpio����Դ��
  * @param  ceGpio2:CeGpioOutEx16ģ��ʹ�õĵ�����Gpio����Դ��
  * @return ϵͳ״̬��
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
  * @brief  CeGpioOutEx16ģ���ʼ��
  * @param  ceGpioOutEx16:CeGpioOutEx16���Զ���
  * @param  ceTg:CeGpioOutEx16ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceGpioOutEx16_initialByTg(CeGpioOutEx16* ceGpioOutEx16, CE_RESOURCE ceTg)
{
    ceGpioOutEx16->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceGpioOutEx16->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOutEx16_initial(ceGpioOutEx16);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ����ָ��������Gpio��
  * @param  ceGpioOutEx16:CeGpioOutEx16���Զ���
  * @param  index:������Gpio�ڵ���������Χ0-15
  * @return None
  */
void ceGpioOutEx16_setBit(CeGpioOutEx16* ceGpioOutEx16, uint8 index)
{
    ceGpioOutEx16->ceGpioStatus |= (0x0001 << index);
    ceGpioOutEx16_write595Byte(&(ceGpioOutEx16->ceTg), ceGpioOutEx16->ceGpioStatus);
}

/**
  * @brief  ��λָ��������Gpio��
  * @param  ceGpioOutEx16:CeGpioOutEx16���Զ���
  * @param  index:������Gpio�ڵ���������Χ0-15
  * @return None
  */
void ceGpioOutEx16_resetBit(CeGpioOutEx16* ceGpioOutEx16, uint8 index)
{
    ceGpioOutEx16->ceGpioStatus &= (~(0x0001 << index));
    ceGpioOutEx16_write595Byte(&(ceGpioOutEx16->ceTg), ceGpioOutEx16->ceGpioStatus);
}

/**
  * @brief ��һ��16λ��ֵ����ȫ��Gpio�ڵ�״̬���������λ��ӦGpio0��
  * @param  ceGpioOutEx16:CeGpioOutEx16���Զ���
  * @param data:ģ�����пڵĵ�ƽ���ֵ
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

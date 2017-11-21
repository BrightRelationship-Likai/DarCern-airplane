/**
  ******************************************************************************
  * @file    CeRadar.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRadarģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeRadar.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  �ⲿ�ж�Int�Ļص�����
  * @return None
  */
void ceRadar_callBackInt(void* pAddPar)
{
    CeRadar* ceRadar = (CeRadar*)pAddPar;
    if (ceRadar->status == 0x01)
    {
        ceRadar->timeCostUs = ceSystemOp.getSystemTickUs();
        ceIntOp.setMode(&(ceRadar->ceInt), CE_INT_MODE_TRIGGER_FALLING);
        ceRadar->status = 0x02;
    }
    else if (ceRadar->status == 0x02)
    {
        ceRadar->timeCost = ceSystemOp.getSystemTickUs() - ceRadar->timeCostUs;
        ceRadar->status = 0x03;
    }
}

/**
  * @brief  CeRadarģ���ʼ��
  * @param  ceRadar:CeRadar���Զ���
  * @param  ceGpio:CeRadarģ��ʹ�õ�Gpio��Դ��
  * @param  ceInt:CeRadarģ��ʹ�õ�Int��Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceRadar_initial(CeRadar* ceRadar, CE_RESOURCE ceGpio, CE_RESOURCE ceInt)
{
    ceRadar->status = 0x00;
    ceRadar->ceInt.ceResource = ceInt;//��start�н����ⲿ�ж�Int�ĳ�ʼ������Ϊ�ڲ�������Ҫ���������ն˵Ĵ�����ʽ
    ceRadar->ceInt.callBack = ceRadar_callBackInt;
    ceRadar->ceInt.pAddPar = ceRadar;
    ceRadar->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_RISING;
    ceIntOp.initial(&(ceRadar->ceInt));

    ceRadar->ceGpio.ceResource = ceGpio;
    ceRadar->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRadar->ceGpio));
    ceGpioOp.resetBit(&(ceRadar->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ʼ�״�̽�Ⲣ��ȡ̽�⵽��������ģ��ľ��룬��λmm��������Χ2cm-400cm����������3mm��
  * @param  ceRadar:CeRadar���Զ���
  * @return ����̽�⵽�ľ��룬��λmm
  */
uint32 ceRadar_getDistance(CeRadar* ceRadar)
{
    uint32 outTime = 0;
    ceRadar->timeCost = 0;
    ceRadar->status = 0x01;
    ceIntOp.setMode(&(ceRadar->ceInt), CE_INT_MODE_TRIGGER_RISING);
    ceIntOp.start(&(ceRadar->ceInt));

    ceGpioOp.setBit(&(ceRadar->ceGpio));//��������10us�ĸߵ�ƽ��ʼ����ź�
    ceSystemOp.delayUs(20);
    ceGpioOp.resetBit(&(ceRadar->ceGpio));

    while(ceRadar->status != 0x03)
    {
        ceSystemOp.delayMs(5);
        outTime += 5;
        if (outTime > 250)
        {
            break;
        }
    }
    ceRadar->status = 0x00;
    ceIntOp.stop(&(ceRadar->ceInt));
    return (uint32)((ceRadar->timeCost * 100)  / 580);//1cm/58us���������¶ȶԿ���Ӱ�쵼�µ����
}

/**
  * @brief  CeRadarģ�����������
  */
const CeRadarOp ceRadarOp = {ceRadar_initial, ceRadar_getDistance};

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeRly2.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly2ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeRly2.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  CeRly2ģ���ʼ��
  * @param  ceRly2:CeRly2���Զ���
  * @param  ceRly2:CeRly2ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceRly2_initial(CeRly2* ceRly2, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1)
{
    ceRly2->ceGpio0.ceResource = ceGpio0;
    ceRly2->ceGpio0.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRly2->ceGpio0));
    ceGpioOp.resetBit(&(ceRly2->ceGpio0));

    ceRly2->ceGpio1.ceResource = ceGpio1;
    ceRly2->ceGpio1.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRly2->ceGpio1));
    ceGpioOp.resetBit(&(ceRly2->ceGpio1));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ���ü̵����պ�
  * @param  ceRly2:CeRly2���Զ���
  * @param  rlyIndex:��Ҫ�պϵļ̵������
  */
void ceRly2_setOn(CeRly2* ceRly2, uint8 rlyIndex)
{
    if (rlyIndex == 0)
    {
       ceGpioOp.setBit(&(ceRly2->ceGpio0));
    } else if (rlyIndex == 1)
    {
       ceGpioOp.setBit(&(ceRly2->ceGpio1));
    }
}

/**
  * @brief    ���ü̵����Ͽ�
  * @param    ceRly2:CeRly2���Զ���
  * @param    rlyIndex:��Ҫ�Ͽ��ļ̵������
  */
void ceRly2_setOff(CeRly2* ceRly2, uint8 rlyIndex)
{
    if (rlyIndex == 0)
    {
         ceGpioOp.resetBit(&(ceRly2->ceGpio0));
    }
    else if (rlyIndex == 1)
    {
         ceGpioOp.resetBit(&(ceRly2->ceGpio1));
    }
}

/**
  * @brief    CeRly2���ò����ϼ�����
  */
const CeRly2Op ceRly2Op = {ceRly2_initial,ceRly2_setOn,ceRly2_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus


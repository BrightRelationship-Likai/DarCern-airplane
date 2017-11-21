/**
  ******************************************************************************
  * @file    CeRly1.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly1ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeRly1.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief    CeRly1ģ���ʼ��
  * @param    ceRly1:CeRly1���Զ���
  * @param    ceGpio:CeRly1ģ��ʹ�õ�Gpio�ӿڵ���Դ��
  * @return   ϵͳ״̬�� ���ܵ�ֵCE_STATUS_SUCCESS
  */
CE_STATUS ceRly1_initial(CeRly1* ceRly1, CE_RESOURCE ceGpio)
{
    ceRly1->ceGpio.ceResource = ceGpio;
    ceRly1->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRly1->ceGpio));
    ceGpioOp.resetBit(&(ceRly1->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
* @brief    ���ü̵����պ�
* @param    ceRly1:CeRly1���Զ���
*/
void ceRly1_setOn(CeRly1* ceRly1)
{
    ceGpioOp.setBit(&(ceRly1->ceGpio));
}

/**
* @brief    ���ü̵����Ͽ�
* @param    ceRly1:CeRly1���Զ���
*/
void ceRly1_setOff(CeRly1* ceRly1)
{
    ceGpioOp.resetBit(&(ceRly1->ceGpio));
}

/**
* @brief    CeRly1���ò����ϼ�
*/
const CeRly1Op ceRly1Op = {ceRly1_initial, ceRly1_setOn, ceRly1_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus


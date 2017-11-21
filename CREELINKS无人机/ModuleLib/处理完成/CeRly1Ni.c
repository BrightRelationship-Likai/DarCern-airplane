/**
  ******************************************************************************
  * @file    CeRly1Ni.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly1Niģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeRly1Ni.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief    CeRly1Niģ���ʼ��
  * @param    ceRly1Ni:CeRly1Ni���Զ���
  * @param    ceGpio:CeRly1Niģ��ʹ�õ�Gpio�ӿڵ���Դ��
  * @return   ϵͳ״̬�� ���ܵ�ֵCE_STATUS_SUCCESS
  */
CE_STATUS ceRly1Ni_initial(CeRly1Ni* ceRly1Ni, CE_RESOURCE ceGpio)
{
    ceRly1Ni->ceGpio.ceResource = ceGpio;
    ceRly1Ni->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRly1Ni->ceGpio));
    ceGpioOp.resetBit(&(ceRly1Ni->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
* @brief    ���ü̵����պ�
* @param    ceRly1Ni:CeRly1Ni���Զ���
*/
void ceRly1Ni_setOn(CeRly1Ni* ceRly1Ni)
{
    ceGpioOp.setBit(&(ceRly1Ni->ceGpio));
}

/**
* @brief    ���ü̵����Ͽ�
* @param    ceRly1Ni:CeRly1Ni���Զ���
*/
void ceRly1Ni_setOff(CeRly1Ni* ceRly1Ni)
{
    ceGpioOp.resetBit(&(ceRly1Ni->ceGpio));
}

/**
* @brief    CeRly1Ni���ò����ϼ�
*/
const CeRly1NiOpBase ceRly1NiOp = {ceRly1Ni_initial, ceRly1Ni_setOn, ceRly1Ni_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus


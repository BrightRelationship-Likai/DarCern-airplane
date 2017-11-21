/**
  ******************************************************************************
  * @file    CeBeepSrc.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBeepSrcģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeBeepSrc.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeBeepSrcģ���ʼ��
  * @param  ceBeepSrc:CeBeepSrc���Զ���ָ��
*/
void ceBeepSrc_initial(CeBeepSrc* ceBeepSrc, CE_RESOURCE ceGpio)
{
    ceBeepSrc->ceGpio.ceResource = ceGpio;
    ceBeepSrc->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceBeepSrc->ceGpio));
    ceGpioOp.resetBit(&(ceBeepSrc->ceGpio));
}

/**
* @brief  ʹ��������ʼ����
* @param  ceBeepSrc:CeBeepSrc���Զ���ָ��
*/
void ceBeepSrc_setOn(CeBeepSrc* ceBeepSrc)
{
    ceGpioOp.setBit(&(ceBeepSrc->ceGpio));
}

/**
* @brief  ʹ������ֹͣ����
* @param  ceBeepSrc:CeBeepSrc���Զ���ָ��
*/
void ceBeepSrc_setOff(CeBeepSrc* ceBeepSrc)
{
    ceGpioOp.resetBit(&(ceBeepSrc->ceGpio));
}

CeBeepSrcOp ceBeepSrcOp = {ceBeepSrc_initial, ceBeepSrc_setOn, ceBeepSrc_setOff};

#ifdef __cplusplus
}
#endif //__cplusplus

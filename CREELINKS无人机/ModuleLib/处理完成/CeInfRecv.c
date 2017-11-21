/**
  ******************************************************************************
  * @file    CeInfRecv.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeInfRecvģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeInfRecv.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus


/**
  * @brief  CeInfRecv�ⲿ�ж�Int�ص�����
  * @param  pAddPar:CeInfRecv���Զ���ָ��
  * @param  cePWM:CeInfRecvģ��ʹ�õ���Դ��
  * @return None
  */
void ceInfRecv_callBackRecvSignal(void* pAddPar)
{
    CeInfRecv* ceInfRecv = (CeInfRecv*)pAddPar;
    if(ceInfRecv->callBackRecvSignal != CE_NULL)
    {
        ceInfRecv->callBackRecvSignal();
    }
}

/**
  * @brief  CeInfRecvģ���ʼ��
  * @param  ceInfRecv:CeInfRecv���Զ���
  * @param  cePWM:CeInfRecvģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceInfRecv_initialByGpio(CeInfRecv* ceInfRecv, CE_RESOURCE ceGpio)
{
    ceInfRecv->ceGpio.ceResource = ceGpio;
    ceInfRecv->ceGpio.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceInfRecv->ceGpio));
    ceInfRecv->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief CeInfRecvģ���ʼ����ʹ��һ��Int��
  * @param ceInfRecv:CeInfRecv���Զ���ָ��
  * @param ceGpio:CeInfRecvģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS   ceInfRecv_initialByInt(CeInfRecv* ceInfRecv, CE_RESOURCE ceInt,void(*callBackRecvSignal)(void))
{
    ceInfRecv->callBackRecvSignal = callBackRecvSignal;
    ceInfRecv->workMode = 0x01;

    ceInfRecv->ceInt.ceResource = ceInt;
    ceInfRecv->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_FALLING;//�յ������ź�ʱ��Ϊ�͵�ƽ
    ceInfRecv->ceInt.callBack = ceInfRecv_callBackRecvSignal;
    ceInfRecv->ceInt.pAddPar = ceInfRecv;
    ceIntOp.initial(&(ceInfRecv->ceInt));
    ceIntOp.start(&(ceInfRecv->ceInt));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief CeInfRecvģ���ʼ��
  * @param ceInfRecv:CeInfRecv���Զ���ָ��
  * @return ��ú�����չܵĽ���״̬������0x01:�յ������ź�ͬ�� ����0x00:δ�յ������ź�
  */
uint8 ceInfRecv_getStatus(CeInfRecv* ceInfRecv)
{
    if(ceInfRecv->workMode == 0X00)
    {
       return ceGpioOp.getBit(&(ceInfRecv->ceGpio));
    }else
    {
        return ceIntOp.getBit(&(ceInfRecv->ceInt));
    }

}

const CeInfRecvOp ceInfRecvOp = {ceInfRecv_initialByGpio, ceInfRecv_initialByInt, ceInfRecv_getStatus};

#ifdef __cplusplus
 }
#endif //__cplusplus

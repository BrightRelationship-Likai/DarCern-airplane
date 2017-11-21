/**
  ******************************************************************************
  * @file    CeInfSend.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeInfSendģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeInfSend.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeInfSend��ʱ���ص�����
  * @param  pAddPar:CeInfSend���Զ���ָ��
  * @return None
  */
void ceInfSend_timerCallBack(void* pAddPar)
{

    if(((CeInfSend*)(pAddPar))->workMode == 0x81)//On
    {
        ((CeInfSend*)(pAddPar))->workMode = 0x01;
        ceGpioOp.resetBit(&(((CeInfSend*)(pAddPar))->ceGpio));
    }else
    {
        ((CeInfSend*)(pAddPar))->workMode = 0x81;
        ceGpioOp.setBit(&(((CeInfSend*)(pAddPar))->ceGpio));
    }
}
/**
  * @brief  CeInfSendģ���ʼ��
  * @param  ceInfSend:CeInfSend���Զ���
  * @param  cePWM:CeInfSendģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceInfSend_initialByPwm(CeInfSend* ceInfSend, CE_RESOURCE cePwm)
{
    ceInfSend->cePwm.ceResource = cePwm;
    ceInfSend->cePwm.cycleNs = 26315;//38KHz
    ceInfSend->cePwm.dutyNs = 26315 / 3;//1/3��ռ�ձ�
    cePwmOp.initial(&(ceInfSend->cePwm));
    ceInfSend->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief ʹ��һ��Gpio�ڼ�һ����ʱ������CeInfSendģ���ʼ��
  * @param ceInfSend:CeInfSend���Զ���ָ��
  * @param cePwm:CeInfSendģ��ʹ�õ���Դ��
  * @param ceTimer:CeTimerģ��ʹ�õĶ�ʱ����Դ��
  */
CE_STATUS ceInfSend_initialByGpio(CeInfSend* ceInfSend, CE_RESOURCE ceGpio, CE_RESOURCE ceTimer)
{
    ceInfSend->ceTimer.ceResource = ceTimer;
    ceInfSend->ceTimer.intervalNs = 26315/2;//38KHz
    ceInfSend->ceTimer.pAddPar = ceInfSend;
    ceInfSend->ceTimer.callBack = ceInfSend_timerCallBack;
    ceTimerOp.initial(&(ceInfSend->ceTimer));
    ceInfSend->workMode = 0x01;
    return CE_STATUS_SUCCESS;
}


/**
  * @brief   ���ú��ⷢ���Ϊ����״̬�������ⷢ��һֱ���������
  * @param   ceInfSend:CeInfSend���Զ���ָ��
 */
void ceInfSend_setOn(CeInfSend* ceInfSend)
{
    if(ceInfSend->workMode == 0x00)
    {
        cePwmOp.start(&(ceInfSend->cePwm));
    }else
    {
        ceTimerOp.start(&(ceInfSend->ceTimer)) ;
    }
}

/**
  * @brief   ���ú��ⷢ���Ϊ�ر�״̬�������ⷢ��ܲ����������
  * @param   ceInfSend:CeInfSend���Զ���ָ��
 */
void ceInfSend_setOff(CeInfSend* ceInfSend)
{
    if(ceInfSend->workMode == 0x00)
    {
        cePwmOp.stop(&(ceInfSend->cePwm));
    }else
    {
        ceTimerOp.stop(&(ceInfSend->ceTimer)) ;
        ceGpioOp.resetBit(&(ceInfSend->ceGpio));
    }
}

const CeInfSendOp ceInfSendOp = {ceInfSend_initialByPwm, ceInfSend_initialByGpio, ceInfSend_setOn, ceInfSend_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus

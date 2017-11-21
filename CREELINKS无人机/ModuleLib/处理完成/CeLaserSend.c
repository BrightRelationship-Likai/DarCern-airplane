/**
  ******************************************************************************
  * @file    CeLaserSend.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeLaserSendģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeLaserSend.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

void ceLaserSend_timerCallBack(void* pAddPar)
{

    if(((CeLaserSend*)(pAddPar))->workMode == 0x81)//On
    {
        ((CeLaserSend*)(pAddPar))->workMode = 0x01;
        ceGpioOp.resetBit(&(((CeLaserSend*)(pAddPar))->ceGpio));
    }else
    {
        ((CeLaserSend*)(pAddPar))->workMode = 0x81;
        ceGpioOp.setBit(&(((CeLaserSend*)(pAddPar))->ceGpio));
    }
}
/**
  * @brief  CeLaserSendģ���ʼ��
  * @param  ceLaserSend:CeLaserSend���Զ���
  * @param  cePWM:CeLaserSendģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceLaserSend_initialByPwm(CeLaserSend* ceLaserSend, CE_RESOURCE cePwm)
{
    ceLaserSend->cePwm.ceResource = cePwm;
    ceLaserSend->cePwm.cycleNs = 26315;      //38KHz
    ceLaserSend->cePwm.dutyNs = 26315 / 3;   //1/3��ռ�ձ�
    cePwmOp.initial(&(ceLaserSend->cePwm));
    ceLaserSend->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief ʹ��һ��Gpio�ڼ�һ����ʱ������CeLaserSendģ���ʼ��
  * @param ceLaserSend:CeLaserSend���Զ���ָ��
  * @param cePwm:CeLaserSendģ��ʹ�õ���Դ��
  * @param ceTimer:CeTimerģ��ʹ�õĶ�ʱ����Դ��
  */
CE_STATUS ceLaserSend_initialByGpio(CeLaserSend* ceLaserSend, CE_RESOURCE ceGpio, CE_RESOURCE ceTimer)
{
    ceLaserSend->ceTimer.ceResource = ceTimer;
    ceLaserSend->ceTimer.intervalNs = 26315/2;//38KHz
    ceLaserSend->ceTimer.pAddPar = ceLaserSend;
    ceLaserSend->ceTimer.callBack = ceLaserSend_timerCallBack;
    ceTimerOp.initial(&(ceLaserSend->ceTimer));
    ceLaserSend->workMode = 0x01;
    return CE_STATUS_SUCCESS;
}


/**
  * @brief   ���ú��ⷢ���Ϊ����״̬�������ⷢ��һֱ���������
  * @param   ceLaserSend:CeLaserSend���Զ���ָ��
 */
void ceLaserSend_setOn(CeLaserSend* ceLaserSend)
{
    if(ceLaserSend->workMode == 0x00)
    {
        cePwmOp.start(&(ceLaserSend->cePwm));
    }else
    {
        ceTimerOp.start(&(ceLaserSend->ceTimer)) ;
    }
}

/**
  * @brief   ���ú��ⷢ���Ϊ�ر�״̬�������ⷢ��ܲ����������
  * @param   ceLaserSend:CeLaserSend���Զ���ָ��
 */
void ceLaserSend_setOff(CeLaserSend* ceLaserSend)
{
    if(ceLaserSend->workMode == 0x00)
    {
        cePwmOp.stop(&(ceLaserSend->cePwm));
    }else
    {
        ceTimerOp.stop(&(ceLaserSend->ceTimer)) ;
        ceGpioOp.resetBit(&(ceLaserSend->ceGpio));
    }
}


CeLaserSendOp ceLaserSendOp = {ceLaserSend_initialByPwm, ceLaserSend_initialByGpio,ceLaserSend_setOn,ceLaserSend_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus

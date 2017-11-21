/**
  ******************************************************************************
  * @file    CeLaserRecv.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeLaserRecvģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeLaserRecv.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus


/**
  * @brief  CeLaserRecvģ���ʼ��
  * @param  ceLaserRecv:CeLaserRecv���Զ���
  * @param  cePWM:CeLaserRecvģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceLaserRecv_initial(CeLaserRecv* ceLaserRecv, CE_RESOURCE ceGpio)
{
    ceLaserRecv->ceGpio.ceResource = ceGpio;
    ceLaserRecv->ceGpio.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceLaserRecv->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief CeLaserRecvģ���ʼ��
  * @param ceLaserRecv:CeLaserRecv���Զ���ָ��
  * @return ��ü�����չܵĽ���״̬������0x01:�յ������ź�ͬ�� ����0x00:δ�յ������ź�
 */
uint8 ceLaserRecv_getStatus(CeLaserRecv* ceLaserRecv)
{
    if(ceGpioOp.getBit(&(ceLaserRecv->ceGpio)) == 0x00)//��ȡIO�ڵ�ƽ
    {
        return 0x01;
    }else
    {
        return 0x00;
    }
}

CeLaserRecvOp ceLaserRecvOp = {ceLaserRecv_initial, ceLaserRecv_getStatus};

#ifdef __cplusplus
 }
#endif //__cplusplus

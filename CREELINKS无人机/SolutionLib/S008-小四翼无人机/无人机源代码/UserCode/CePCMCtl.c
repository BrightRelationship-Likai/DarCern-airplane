/**
  ******************************************************************************
  * @file    CePCM.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   �����������ļ�������0~1000������Ϊת��Ϊ0~100%ռ�ձȵ�PWM���
  ******************************************************************************
  * @attention
  *
  *1)����0~1000������ǿ�ȣ������ӦΪ0~100%��ռ�ձ�
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CePCMCtl.h"
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
  * @brief  CePCMģ���ʼ��
  * @return ϵͳ״̬��
  */
void cePCMCtl_initial(void)
{

}

uint8 cePCMCtl_checkConnectStatus(void)
{
    return 1;
}

fp32      cePCMCtl_getHopePitch(void)
{
        return 0;
}

fp32      cePCMCtl_getHopeRoll(void)
{
        return 0;
}

fp32      cePCMCtl_getHopeYaw(void)
{
        return 0;
}

fp32      cePCMCtl_getHopeAccelerator(void)
{
        return 0;
}

/**
  * @brief  ��ʼ��CePCMģ���������
  */
const CePCMCtlOp cePCMCtlOp = {cePCMCtl_initial,cePCMCtl_checkConnectStatus,cePCMCtl_getHopePitch,cePCMCtl_getHopeRoll,cePCMCtl_getHopeYaw,cePCMCtl_getHopeAccelerator};


#ifdef __cplusplus
}
#endif //__cplusplus

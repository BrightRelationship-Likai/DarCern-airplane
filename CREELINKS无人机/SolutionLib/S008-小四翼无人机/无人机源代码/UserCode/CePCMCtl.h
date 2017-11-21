/**
  ******************************************************************************
  * @file    CePCMCtl.h
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
#ifndef __CE_PCM_CTL_H__
#define __CE_PCM_CTL_H__
#include "Creelinks.h"
#include "CePCM.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/*
 *CePCMCtl��������
 */
typedef struct
{
    void      (*initial)(void);              /*!< @brief ��������ӿڳ�ʼ��*/    

    uint8     (*checkConnectStatus)(void); 

    fp32      (*getHopePitch)(void);
    fp32      (*getHopeRoll)(void);
    fp32      (*getHopeYaw)(void);
    fp32      (*getHopeAccelerator)(void);

    
}CePCMCtlOp;

/*
 *CePCMCtl��������ʵ��
 */
extern const CePCMCtlOp cePCMCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_PCM_CTL_H__


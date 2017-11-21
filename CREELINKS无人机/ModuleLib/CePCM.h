/**
  ******************************************************************************
  * @file     CePCM.h
  * @author   Creelinks Application Team
  * @version  V1.0.0
  * @date    2017-01-06
  * @brief    ������CePCMģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_PCM_H__
#define __CE_PCM_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_PCM_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_PCM_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_PCM_VERSION__ > __CE_PCM_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CePCM.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

#define CE_PCM_PWM_CYCLE_MS     24
#define CE_PCM_PWM_MIX_DUTY_MS  10
#define CE_PCM_PWM_MAX_DUTY_MS  20
/*
 *CePCM���Զ���
 */
typedef struct
{
    CeInt ceInt0;
    CeInt ceInt1;
    CeInt ceInt2;
    CeInt ceInt3;
    CeGpio ceGpio0;
    CeGpio ceGpio1;
    CeGpio ceGpio2;
    CeGpio ceGpio3;
}CePCM;
/*
 *CePCM��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CePCM* cePCM, CE_RESOURCE ceInt0,CE_RESOURCE ceInt1,CE_RESOURCE ceInt2,CE_RESOURCE ceInt3,CE_RESOURCE ceGpio0,CE_RESOURCE ceGpio1,CE_RESOURCE ceGpio2,CE_RESOURCE ceGpio3);             /*!< @brief  CePCMģ���ʼ��
                                                                                 @param  cePCM:CePCM���Զ���ָ��
                                                                                 @param  ceXX:CePCMģ��ʹ�õ���Դ��*/

    fp32        (*getDuty)(CePCM* cePCM, uint8 index);  

}CePCMOpBase;

/*
 *CePCM��������ʵ��
 */
extern const CePCMOpBase cePCMOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_PCM_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_PCM_H__

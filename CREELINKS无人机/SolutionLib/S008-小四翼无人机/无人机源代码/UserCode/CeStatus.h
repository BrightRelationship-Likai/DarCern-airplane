/**
  ******************************************************************************
  * @file    CeStatus.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeStatusģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_STATUS_H__
#define __CE_STATUS_H__
#include "Creelinks.h"
#include "CeSensor.h"
#include "CePCMCtl.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

typedef struct  
{
    fp32 pitch;                                         /*!< �����ǣ���ǰ��Ϊ????�� �����Ϊ????*/
    fp32 roll;                                          /*!< �����ǣ�����Ϊ????�����ҷ�Ϊ????*/
    fp32 yaw;                                           /*!< ƫ���ǣ�������������ʱ��ƫΪ????��˳ʱ��ƫΪ????*/
    fp32 accelerator;                                   /*!< ���˻����ţ�0~1000*/

    CeAcc ceAcc;                                        /*!< ���ٶȴ���������*/
    CeGyr ceGyr;                                        /*!< ���ٶȴ���������*/
    CeMag ceMag;                                        /*!< �شŴ���������*/
    CeAlt ceAlt;                                        /*!< ��ѹ����������*/   
    CeTem ceTem;                                        /*!< �¶ȴ���������*/
    CeGps ceGps;                                        /*!< λ����Ϣ����*/  
}CeStatus;

/*
 *CeStatus��������
 */
typedef struct
{
    CE_STATUS   (*initial)(void);                       /*!< @brief  ϵͳ���ƺ�����ʼ��*/

    void        (*getNowStatus)(CeStatus* ceNowStatus); /*!< @brief  ��ȡ��ǰ���˻��ķ���״̬������Ϣ
                                                             @param  ���в�����Ϣ�����ַ*/

    void        (*getHopeStatus)(CeStatus* ceNowStatus, CeStatus* ceHopeStatus);/*!< 
                                                             @brief  ��ȡ�����ķ���״̬������Ϣ
                                                             @param  ���в�����Ϣ�����ַ*/

}CeStatusOp;
/*
 *CeStatus��������ʵ��
 */
extern const CeStatusOp ceStatusOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_STATUS_H__

/**
  ******************************************************************************
  * @file    CeTMCtl.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   ���ݴ����������WIFI��������2.4Gģ��ĳ�ʼ�������ݷ��ͽ��յȴ���
  ******************************************************************************
  * @attention
  *
  *1)��ֲ��ע�⣺����initial�����У��������ģ��ʹ�õ�����Դ��
  *2)�������ݵ���send����������Byte���鼴�ɣ�
  *3)���յ����ݺ��Զ����ó�ʼ��ʱ�ṩ�Ļص�������δ���κδ����Byte���顣
  *4)���յ����ݺ󣬵��õĻص���������ceTaskOp.mainTask()��ִ�У��뱣֤��main�����е�ceTaskOp.mainTask()�ܹ������ڵ��� 
  * 
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TMU_CTL_H__
#define __CE_TMU_CTL_H__
#include "Creelinks.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/*
 *CeTMCtl��������
 */
typedef struct
{
    CE_STATUS (*initial)(uint8 iniArg);                         /*!< @brief CeTMCtlģ���ʼ��
                                                                     @param iniArg:��ʼ��ʱ�����ݵĿ��������ò���*/

    void      (*setRecvCallBack)(void (*recvCallBack)(uint8* recvBuf, uint16 recvCount));/*!< 
                                                                     @brief CeTMCtlģ�����ý������ݵĻص�
                                                                     @param recvCallBack:�û����ṩ�Ļص�����*/

    CE_STATUS (*sendData)(uint8* dataBuf, uint16 dataCount);    /*!< @brief �������ݣ�ע�⣺�����ڲ����������һ�η������ݵ�ʱ���Ƿ����intervalMs�����С����ֱ�ӷ���
                                                                     @param dataBuf:���ͻ����ַ
                                                                     @param dataCount:���ͻ������ݳ���*/

    CE_STATUS (*checkConnectStatus)(void);                      /*!< @brief ����Ƿ�ͨѶ�ж�
                                                                     @return CE_STATUS_SUCCESS��ͨѶ������ ������ͨѶ�ж�*/

    uint32    (*getSendIntervalMs)(void);                       /*!< @brief ��������һ�η������ݵ���ʱ��ʱ����
                                                                     @return ������һ�η������ݵ����ڵ�ʱ��������λms*/
}CeTMCtlOp;
/*
 *CeTMCtl��������ʵ��
 */
extern const CeTMCtlOp ceTMCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TMU_CTL_H__



/**
  ******************************************************************************
  * @file    CeParCtl.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeParCtlģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_PAR_CTL_H__
#define __CE_PAR_CTL_H__
#include "Creelinks.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/*
 *CeParCtl��������
 */
typedef struct
{
    void    (*initial)(void);                   /*!< @brief  �������Զ����ʼ��*/

    void    (*beforeFilterHook)(void);          /*!< @brief  ʹ�õ�ǰ���������ݽ������˻���̬����ǰ������õĹ��Ӻ���*/

    void    (*afterFilterHook)(void);           /*!< @brief  ʹ�õ�ǰ���������ݽ������˻���̬���������õĹ��Ӻ���*/

    void    (*beforePIDHook)(void);             /*!< @brief  ʹ�����˻���ǰ״̬������״̬����PID����ǰ������õĹ��Ӻ���*/

    void    (*afterPIDHook)(void);              /*!< @brief  ʹ�����˻���ǰ״̬������״̬����PID���������õĹ��Ӻ���*/

    void    (*recvDataHook)(void);              /*!< @brief  ϵͳÿ����ѭ��������ã��˺����ڲ�����ʵ�����ݽ��ղ���*/

    void    (*sendDataHook)(void);              /*!< @brief  ϵͳÿ����ѭ��������ã��˺����ڲ�����ʵ�ֽ���ǰ���˻�����������͸����ƶ˵Ĳ���*/
}CeParCtlOp;
/*
 *CeParCtl��������ʵ��
 */
extern const CeParCtlOp ceParCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_PAR_CTL_H__

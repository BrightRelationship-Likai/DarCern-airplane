/**
  ******************************************************************************
  * @file    CeMDCtl.h
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
#ifndef __CE_MD_CTL_H__
#define __CE_MD_CTL_H__
#include "Creelinks.h"
#include "CeMD.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
typedef struct
{
    int16 motorDrivePower0;
    int16 motorDrivePower1;
    int16 motorDrivePower2;
    int16 motorDrivePower3;
}CeMDDrivePower;

/*
 *CeMDCtl��������
 */
typedef struct
{
    void      (*initial)(void);              /*!< @brief ��������ӿڳ�ʼ��*/    

    void      (*setDriverPower)(CeMDDrivePower* drivePower);/*!< 
                                                  @brief ���õ��������ǿ�ȣ� 0~1000
                                                  @param drivePower:����������ǿ�ȵ�����ָ��*/
}CeMDCtlOp;

/*
 *CeMDCtl��������ʵ��
 */
extern const CeMDCtlOp ceMDCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_MD_CTL_H__


/**
  ******************************************************************************
  * @file    CeL36.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2016-09-28
  * @brief
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_L36_H__
#define __CE_L36_H__

#include "CeMcu.h"
#include "CeSpi.h"
#include "CeI2c.h"
#include "CeInt.h"
#include "CeGpio.h"
#include "CePwm.h"

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#ifdef __CE_USE_L36__

/**
  * @brief  ö�٣�LCDͨѶ������
  */
typedef enum
{
    CE_L36_BUS_SPEED_H,
    CE_L36_BUS_SPEED_M,
    CE_L36_BUS_SPEED_L,
}CE_L36_BUS_SPEED;

/**
  * @brief  �ṹ�壬L36���Զ����������
  */
typedef struct
{
    CE_RESOURCE         ceResource;
    CE_L36_BUS_SPEED    ceL36BusSpeed;
    CePwm               cePwm;
    CeSpiMaster         ceSpiMaster;
    CeI2cMaster         ceI2cMaster;
    CeInt               ceInt;
    CeGpio              ceGpioEx0;
    CeGpio              ceGpioEx1;
}CeL36;

/**
  * @brief  �ṹ�壬L36�������󼯺�
  */
typedef struct
{

    CE_STATUS   (*initial)(CeL36* ceL36);               /*!< @brief ��ʼ��L36*/

    void        (*writeData)(uint16 addr, uint16 data); /*!< @brief ��L36д����
                                                             @param addr:��д���ݵĵ�ַ
                                                             @param data:��д������*/

    uint32      (*readData)(uint16 addr);               /*!< @brief ��L36������
                                                             @param addr:�������ݵĵ�ַ
                                                             @return ��ȡ��������*/

    void        (*setRST)(void);                        /*!< @brief ����L36RST��Ӧ��GpioֵΪ1�������Թ�����L36���ⲿ�豸���и�λ*/

    void        (*resetRST)(void);                      /*!< @brief ����L36RST��Ӧ��GpioֵΪ0�������Թ�����L36���ⲿ�豸���и�λ*/

}CeL36Op;
extern const CeL36Op ceL36Op;                       /*!< ������L36��صĲ���*/

#endif //__CE_USE_L36__

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_L36_H__

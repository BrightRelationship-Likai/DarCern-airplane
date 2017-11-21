/**
  ******************************************************************************
  * @file    CeSensor.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   ���˻��������ӿڶ���
  ******************************************************************************
  * @attention
  * 
  * 
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_SENSOR_H__
#define __CE_SENSOR_H__
#include "Creelinks.h"
#ifdef __cpluslus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  �ṹ�壬���ٶ�,
  *         ��λ��g
  *         ������ǰ������X+����󷽼���X-�����󷽼���Y+�����ҷ�����Y-�����Ϸ�����Z+�����·�����Z-
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeAcc;

/**
  * @brief  �ṹ�壬�����ǽ��ٶȣ�
  *         ��λ����/s
  *         �����ҷ���X+�� �󷭹�X-�� ǰ��Y+�� ����Y-�� ��ʱ��ƫ��Z+�� ˳ʱ��ƫ��Z-
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeGyr;

/**
  * @brief  �ṹ�壬�شŴ��������������̣�
  *         ��λ����
  *         ������δָ��
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeMag;

/**
  * @brief  �ṹ�壬��ѹ��
  */
typedef struct
{
    fp32 altitude;                          /*!< ���θ߶ȣ���λ��(m)*/
    fp32 pressure;                          /*!< ����ѹǿ����λ��˹��(Pa)*/
}CeAlt;

/**
  * @brief  �ṹ�壬GPS���涨λ��Ϣ�ṹ��
  */
typedef struct
{
    fp32  latitude;                         /*!< ��ǰγ������*/           
    char  latitudeHemisphere;               /*!< ��ǰγ�Ȱ���N:������ S:�ϰ���*/
    fp32  longitude;                        /*!< ��ǰ��������*/
    char  longitudeHemisphere;              /*!< ��ǰ���Ȱ���E:������W:����*/
}CeGps;



/**
  * @brief  �ṹ�壬��ǰ���˻����������¶�
  */
typedef struct
{
    fp32  temperature;                      /*!< ��ǰ�¶ȣ���λ��*/           
}CeTem;

/*
 *CeSensor��������
 */
typedef struct
{
    CE_STATUS   (*initial)(void);           /*!< @brief  ���˿ɴ������ϼ������ʼ��*/

    CE_STATUS   (*getAcc)(CeAcc* outCeAcc); /*!< @brief  ��ȡ��ǰ���˻��ļ��ٶ�
                                                 @param  outCeAcc:���ٶȽ�������ַ*/

    CE_STATUS   (*getGyr)(CeGyr* outCeGyr); /*!< @brief  ��ȡ��ǰ���˻��Ľ��ٶ�
                                                 @param  outCeGyr:���ٶȽ�������ַ*/

    CE_STATUS   (*getMag)(CeMag* outCeMag); /*!< @brief  ��ȡ��ǰ���˻��ĵش�����
                                                 @param  outCeMag:�ش����ݱ����ַ*/

    CE_STATUS   (*getAlt)(CeAlt* outCeAlt); /*!< @brief  ��ȡ��ǰ���˻����θ߶���Ϣ
                                                 @param  outCeAlt:��ǰ���˻����θ߶�����*/

    CE_STATUS   (*getGps)(CeGps* outCeGps); /*!< @brief  ��ȡ��ǰ���˻�λ����Ϣ
                                                 @param  outCeGps:��ǰ���˻�λ����Ϣ�����ַ*/

    CE_STATUS   (*getTem)(CeTem* outCeTem); /*!< @brief  ��ȡ��ǰ���˻����������¶���Ϣ
                                                 @param  outCeTem:��ǰ���˻��¶���Ϣ�����ַ*/

}CeSensorOp;

/*
 *CeSensor��������ʵ��
 */
extern const CeSensorOp ceSensorOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SENSOR_H__



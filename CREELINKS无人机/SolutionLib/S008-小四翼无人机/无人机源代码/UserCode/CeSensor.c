/**
  ******************************************************************************
  * @file    CeSensor.c
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
#include "CeSensor.h"
#include "CeMPU6050.h"
#include "CeMS5611.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define     CE_MPU6050_RESOURCE I2c1        /*!< ����MPU6050ģ��ʹ�õ���I2C��Դ��*/ 
#define     CE_MS5611_RESOURCE  I2c2        /*!< ����MS5611ģ��ʹ�õ���I2C��Դ��*/ 

CeMPU6050   ceMPU6050;                      /*!< CeMPU6050ģ�����*/ 
CeMS5611    ceMS5611;                       /*!< CeMS5611ģ�����*/ 

/**
  * @brief  ���˿ɴ������ϼ������ʼ��
  */
CE_STATUS   ceSensor_initial(void)
{
    ceMPU6050Op.initial(&ceMPU6050,CE_MPU6050_RESOURCE);
    //ceMS5611Op.initial(&ceMS5611, CE_MS5611_RESOURCE);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡ��ǰ���˻��ļ��ٶ�
  * @param  outCeAcc:���ٶȽ�������ַ
  */
CE_STATUS   ceSensor_getAcc(CeAcc* outCeAcc)
{
    CeMPU6050Acc* acc = ceMPU6050Op.getAcceleration(&ceMPU6050);
    if(acc == CE_NULL)
        return CE_STATUS_FAILE;

    outCeAcc->x = acc->x;
    outCeAcc->y = acc->y;
    outCeAcc->z = acc->z;

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡ��ǰ���˻��Ľ��ٶ�
  * @param  outCeGyr:���ٶȽ�������ַ
  */
CE_STATUS   ceSensor_getGyr(CeGyr* outCeGyr)
{
    CeMPU6050Gyr* gyr = ceMPU6050Op.getGyroscope(&ceMPU6050);
    if(gyr == CE_NULL)
        return CE_STATUS_FAILE;
    outCeGyr->x = gyr->x;
    outCeGyr->y = gyr->y;
    outCeGyr->z = gyr->z;

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡ��ǰ���˻��ĵش�����
  * @param  outCeMag:�ش����ݱ����ַ
  */
CE_STATUS   ceSensor_getMag(CeMag* outCeMag)
{

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡ��ǰ���˻����θ߶���Ϣ
  * @param  outCeAlt:��ǰ���˻����θ߶�����
  */
CE_STATUS   ceSensor_getAlt(CeAlt* outCeAlt)
{

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡ��ǰ���˻�λ����Ϣ
  * @param  outCeGps:��ǰ���˻�λ����Ϣ�����ַ
  */
CE_STATUS   ceSensor_getGps(CeGps* outCeGps)
{

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡ��ǰ���˻����������¶���Ϣ
  * @param  outCeTem:��ǰ���˻��¶���Ϣ�����ַ
  */
CE_STATUS  ceSensor_getTem(CeTem* outCeTem)
{

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeSensorģ�����������
  */
const CeSensorOp ceSensorOp = {ceSensor_initial,ceSensor_getAcc,ceSensor_getGyr,ceSensor_getMag,ceSensor_getAlt,ceSensor_getGps,ceSensor_getTem};

#ifdef __cplusplus
 }
#endif //__cplusplus

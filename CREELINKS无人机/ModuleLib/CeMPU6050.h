/**
  ******************************************************************************
  * @file    CeMPU6050.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeMPU6050ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_MPU6050_H__
#define __CE_MPU6050_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#include "Creelinks.h"
#define __CE_MPU6050_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_MPU6050_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_MPU6050_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeMPU6050.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

/**
  * @brief  �ṹ�壬���ٶ�
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeMPU6050Acc;

/**
  * @brief  �ṹ�壬�����ǽ��ٶ�
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeMPU6050Gyr;

/*
 *CeMPU6050���Զ���
 */
typedef struct
{
    CeI2cMaster         ceI2cMaster;
    CeMPU6050Acc  acceleration;
    CeMPU6050Gyr     gyroscope;
    CeMPU6050Gyr     gyroscopeZero;
}CeMPU6050;

/*
 *CeMPU6050��������
 */
typedef struct
{
    CE_STATUS              (*initial)(CeMPU6050* CeMPU6050, CE_RESOURCE ceI2c);/*!<
                                                                      @brief CeMPU6050ģ���ʼ��
                                                                      @param CeMPU6050:CeMPU6050���Զ���ָ��
                                                                      @param ceI2cMaster:CeMPU6050ģ��ʹ�õ���Դ��*/

    CeMPU6050Acc*    (*getAcceleration)(CeMPU6050* CeMPU6050);   /*!< @brief ��ȡ���ٶ�
                                                                      @param CeMPU6050:CeMPU6050���Զ���ָ��*/

    CeMPU6050Gyr*       (*getGyroscope)(CeMPU6050* CeMPU6050);      /*!< @brief ��ȡ�����ǽ��ٶ�
                                                                      @param CeMPU6050:CeMPU6050���Զ���ָ��*/
}CeMPU6050Op;
/*
 *CeMPU6050��������ʵ��
 */
extern const CeMPU6050Op ceMPU6050Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_MPU6050_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_MPU6050_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��ȡ6����Ϣ����ͨ��Uart����λ������ʾ
******************************************************************************
#include "Creelinks.h"
#include "CeMPU6050.h"
CeMPU6050 myMPU6050;                                //�������Զ���
CeMPU6050Acc* acceleration;              //����������ٶȲ���ָ��
CeMPU6050Gyr* gyroscope;                    //�����������ݲ���ָ��
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(Uartx);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceMPU6050Op.initial(&myMPU6050,I2cx);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        acceleration = ceMPU6050Op.getAcceleration(&myMPU6050);
        ceDebugOp.printf("Acceleration: x=%d, y=%d, z=%d\n", acceleration->x, acceleration->y,acceleration->z);

        gyroscope = ceMPU6050Op.getGyroscope(&myMPU6050);
        ceDebugOp.printf("Gyroscope: x=%d, y=%d, z=%d\n", gyroscope->x, gyroscope->y,gyroscope->z);

        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/




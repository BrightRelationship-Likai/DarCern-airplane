/**
  ******************************************************************************
  * @file    Ce10Dof.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeAnSwģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_10_DOF_H__
#define __CE_10_DOF_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_10_DOF_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_10_DOF_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_10_DOF_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�Ce10Dof.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
typedef struct
{
    int16 AC1;
    int16 AC2;
    int16 AC3;
    uint16 AC4;
    uint16 AC5;
    uint16 AC6;
    int16 B1;
    int16 B2;
    int16 MB;
    int16 MC;
    int16 MD;

    int16 _oss;
    int32 B5;
    int32 UT;
    int32 UP;
    int32 Pressure0;
}Ce10DofBMP180;

/**
  * @brief  �ṹ�壬���ٶ�
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}Ce10DofAcceleration;

/**
  * @brief  �ṹ�壬�����ǽ��ٶ�
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}Ce10DofGyroscope;

/**
  * @brief  �ṹ�壬�����������
  */
typedef struct
{
    int16 x;
    int16 y;
    int16 z;
}Ce10DofMagnetic;


/**
  * @brief  ��ά����
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeVector3;


typedef struct
{
    fp32     temperature;        /*!< �¶�ֵ*/
    int32    pressure;           /*!< ��ѹֵ*/
    fp32     altitude;           /*!< ���θ߶�*/
}Ce10DofEnvironment;
/*
 *Ce10Dof���Զ���
 */
typedef struct
{
    CeI2cMaster ceI2cMaster;
    Ce10DofAcceleration acceleration;
    Ce10DofGyroscope gyroscope;
    Ce10DofGyroscope gyroscopeZero;
    Ce10DofMagnetic magnetic;
    Ce10DofEnvironment environment;
    Ce10DofBMP180  exBmp180;

    CeVector3 gyroscopeVector3;
}Ce10Dof;

/*
 *Ce10Dof��������
 */
typedef struct
{
    CE_STATUS               (*initial)(Ce10Dof* ce10Dof, CE_RESOURCE ceI2c);/*!<
                                                                         @brief Ce10Dofģ���ʼ��
                                                                         @param ce10Dof:Ce10Dof���Զ���ָ��
                                                                         @param ceI2cMaster:Ce10Dofģ��ʹ�õ���Դ��*/

    Ce10DofAcceleration*    (*getAcceleration)(Ce10Dof* ce10Dof);   /*!< @brief ��ȡ���ٶ�
                                                                         @param ce10Dof:Ce10Dof���Զ���ָ��*/

    Ce10DofGyroscope*       (*getGyroscope)(Ce10Dof* ce10Dof);      /*!< @brief ��ȡ�����ǽ��ٶ�
                                                                         @param ce10Dof:Ce10Dof���Զ���ָ��*/

    Ce10DofMagnetic*        (*getMagnetic)(Ce10Dof* ce10Dof);       /*!< @brief ��ȡ�����������
                                                                         @param ce10Dof:Ce10Dof���Զ���ָ��*/

    Ce10DofEnvironment*     (*getEnvironment)(Ce10Dof* ce10Dof);    /*!< @brief ��ȡ�Ѿ���У�����¶ȡ���ѹ�����θ߶�
                                                                         @param ce10Dof:Ce10Dof���Զ���ָ��*/

}Ce10DofOp;
/*
 *Ce10Dof��������ʵ��
 */
extern const Ce10DofOp ce10DofOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_10_DOF_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_10_DOF_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��ȡ10����Ϣ����ͨ��Uart����λ������ʾ
******************************************************************************
#include "Creelinks.h"
#include "Ce10Dof.h"
Ce10Dof my10Dof;                                //�������Զ���
Ce10DofAcceleration* acceleration;              //����������ٶȲ���ָ��
Ce10DofGyroscope* gyroscope;                    //�����������ݲ���ָ��
Ce10DofMagnetic* magnetic;                      //����شŲ���ָ��
Ce10DofEnvironment* environment;                //�����¶ȡ���ѹ�����θ߶�
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ce10DofOp.initial(&my10Dof,R2TI2c);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        acceleration = ce10DofOp.getAcceleration(&my10Dof);
        ceDebugOp.printf("Acceleration: x=%d, y=%d, z=%d\n", acceleration->x, acceleration->y,acceleration->z);

        gyroscope = ce10DofOp.getGyroscope(&my10Dof);
        ceDebugOp.printf("Gyroscope: x=%d, y=%d, z=%d\n", gyroscope->x, gyroscope->y,gyroscope->z);

        magnetic = ce10DofOp.getMagnetic(&my10Dof);
        ceDebugOp.printf("Magnetic: x=%d, y=%d, z=%d\n", magnetic->x, magnetic->y,magnetic->z);

        environment = ce10DofOp.getEnvironment(&my10Dof);
        ceDebugOp.printf("Environment: temperature=%f, pressure=%d, altitude=%f\n", environment->temperature, environment->pressure,environment->altitude);

        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

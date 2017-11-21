/**
  ******************************************************************************
  * @file    CeMD.c
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
#include "CeMDCtl.h"
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
#define  CE_MD_CTL_RESOURCE_0   PC6GIP                  /*!< �����0·������ʹ�õ�PWM��Դ��*/
#define  CE_MD_CTL_RESOURCE_1   PC7GIP                  /*!< �����1·������ʹ�õ�PWM��Դ��*/
#define  CE_MD_CTL_RESOURCE_2   PC8GIP                  /*!< �����2·������ʹ�õ�PWM��Դ��*/
#define  CE_MD_CTL_RESOURCE_3   PC9GIP                  /*!< �����3·������ʹ�õ�PWM��Դ��*/
CeMD        ceMD0;                                      /*!< �����0·���������ƶ���*/
CeMD        ceMD1;                                      /*!< �����1·���������ƶ���*/
CeMD        ceMD2;                                      /*!< �����2·���������ƶ���*/
CeMD        ceMD3;                                      /*!< �����3·���������ƶ���*/
/**
  * @brief  CeMDģ���ʼ��
  * @return ϵͳ״̬��
  */
void ceMDCtl_initial(void)
{
    ceMDOp.initial(&(ceMD0), CE_MD_CTL_RESOURCE_0);     //ʹ��һ·Pwm��Դ�ų�ʼ��������0
    ceMDOp.initial(&(ceMD0), CE_MD_CTL_RESOURCE_0);     //ʹ��һ·Pwm��Դ�ų�ʼ��������0,ע���˴���ʼ������PC6��Ӧ��Pwm������ΪSTM32F103��TIM8��ʱ���ƺ���BUG����·ͨ������ʼ��������˳���Ӱ�������PWM�����򣬺�������о���
    ceMDOp.initial(&(ceMD1), CE_MD_CTL_RESOURCE_1);     //ʹ��һ·Pwm��Դ�ų�ʼ��������1
    ceMDOp.initial(&(ceMD3), CE_MD_CTL_RESOURCE_3);     //ʹ��һ·Pwm��Դ�ų�ʼ��������3
    ceMDOp.initial(&(ceMD2), CE_MD_CTL_RESOURCE_2);     //ʹ��һ·Pwm��Դ�ų�ʼ��������2
}

/**
  * @brief  ����Pwm������ǿ�ȣ�0~1000����Ӧռ�ձ�Ϊ0%~100%
  * @param  driverPower[]:Pwm������ǿ�ȣ�0~1000����Ӧռ�ձ�Ϊ0%~100%
  */
void ceMDCtl_setDriverPower(CeMDDrivePower* drivePower)
{
    ceMDOp.setDriverPower(&ceMD0,drivePower->motorDrivePower0);//���õ�0·�������ǿ�ȣ�0~1000                
    ceMDOp.setDriverPower(&ceMD1,drivePower->motorDrivePower1);//���õ�1·�������ǿ�ȣ�0~1000
    ceMDOp.setDriverPower(&ceMD2,drivePower->motorDrivePower2);//���õ�2·�������ǿ�ȣ�0~1000
    ceMDOp.setDriverPower(&ceMD3,drivePower->motorDrivePower3);//���õ�3·�������ǿ�ȣ�0~1000
}

/**
  * @brief  ��ʼ��CeMDģ���������
  */
const CeMDCtlOp ceMDCtlOp = {ceMDCtl_initial,ceMDCtl_setDriverPower};


#ifdef __cplusplus
}
#endif //__cplusplus

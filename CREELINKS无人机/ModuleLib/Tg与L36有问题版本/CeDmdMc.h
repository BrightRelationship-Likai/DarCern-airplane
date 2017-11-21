/**
  ******************************************************************************
  * @file    CeDmdMc.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeDmdMcģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)оƬ�ͺ�ΪMC33886VW������оƬû���ṩɲ��(�ƶ�)���û����Կ���ת������ʹ�����ת������ɲ��(�ƶ�)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_DMD_MC_H__
#define __CE_DMD_MC_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_DMD_MC_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_DMD_MC_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_DMD_MC_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeDmdMc.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
#define CE_DMD_MC_PWM_CYCLE_NS     10000000
/*
 *CeDmdMc���Զ���
 */
typedef struct
{
    CePwm   cePwm;                                                              /*!< ģ��ʹ�õ�Pwm����*/
    CeTg    ceTg;                                                               /*!< ģ��ʹ�õ�Tg����*/
    uint32  duty;                                                               /*!< ģ��������ǿ�ȶ�Ӧ��Pwm�ߵ�ƽ��ʱ��*/
}CeDmdMc;
/*
 *CeDmdMc��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeDmdMc* ceDmdMc, CE_RESOURCE cePwm, CE_RESOURCE ceTg);
                                                                                /*!< @brief  CeDmdMcģ���ʼ��
                                                                                     @param  ceDmdTb:CeDmdMc���Զ���
                                                                                     @param  cePwm:CeDmdMcģ��ʹ�õ�Pwm��Դ��
                                                                                     @param  ceTg:CeDmdMcģ��ʹ�õ�Tg��Դ��*/

    void        (*setOn)(CeDmdMc* ceDmdMc);                                     /*!< @brief  �����
                                                                                     @param  ceDmdMc:CeDmdMc���Զ���ָ��*/

    void        (*setDriveStrength)(CeDmdMc* ceDmdMc, uint16 driveStrength);    /*!< @brief  �����������ǿ�ȣ���������н��е���
                                                                                     @param  ceDmdMc:CeDmdMc���Զ���ָ��
                                                                                     @param  driveStrength:���������ǿ�ȣ���Χ0-10000*/

    void        (*setDirection)(CeDmdMc* ceDmdMc, uint8 direction);             /*!< @brief  ���õ����ת������
                                                                                     @param  ceDmdMc:CeDmdMc���Զ���ָ��
                                                                                     @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����*/


    void        (*setOff)(CeDmdMc* ceDmdMc);                                    /*!< @brief  ����ر�
                                                                                     @param  ceDmdMc:CeDmdMc���Զ���ָ��*/

}CeDmdMcOp;
/*
 *CeDmdMc��������ʵ��
 */
extern const CeDmdMcOp ceDmdMcOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_DMD_MC_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_DMD_MC_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���õ��ͨ������������ת��������Ϊ��ת��
******************************************************************************
#include "Creelinks.h"
#include "CeDmdMc.h"
CeDmdMc myDmdMc;
uint16 drivePower;                              //�����������0��10000

int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceDmdMcOp.initial(&myDmdMc,R1AGP,R2TI2c);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceDmdMcOp.setDirection(&myDmdMc,0x01);                  //����ͨ������Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ������������������
        {
            ceDmdMcOp.setDriveStrength(&myDmdMc,drivePower);
            ceSystemOp.delayMs(2000);
        }

        ceDmdMcOp.setDirection(&myDmdMc,0x00);                  //����ͨ������Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ������������������
        {
            ceDmdMcOp.setDriveStrength(&myDmdMc,drivePower);
            ceSystemOp.delayMs(2000);
        }
    };
}
******************************************************************************
*/

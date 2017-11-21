/**
  ******************************************************************************
  * @file    CeDmdTb.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeDmdTbģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)оƬ�ͺ�ΪTB6612FNG
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_DMD_TB_H__
#define __CE_DMD_TB_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_DMD_TB_VERSION__ 1                                                 /*!< �������ļ��İ汾��*/
#define __CE_DMD_TB_NEED_CREELINKS_VERSION__ 1                                  /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_DMD_TB_NEED_CREELINKS_VERSION__)           /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeDmdTb.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
#define CE_DMD_TB_PWM1_CYCLE_NS     10000000                                    /*!< DmdTbģ���һ��ͨ����Pwm����ת�ٵ�����*/
#define CE_DMD_TB_PWM2_CYCLE_NS     10000000                                    /*!< DmdTbģ��ڶ���ͨ����Pwm����ת�ٵ�����*/
/*
 *CeDmdTb���Զ���
 */
typedef struct
{
    CePwm   cePwm1;                                                             /*!< ģ��ĵ�һ��ͨ��ʹ�õ�Pwm����*/
    CeTg    ceTg1;                                                              /*!< ģ��ĵ�һ��ͨ��ʹ�õ�Tg����*/
    uint32  duty1;                                                              /*!< ģ��ĵ�һ��ͨ���������ǿ�ȶ�Ӧ��Pwm�ߵ�ƽ��ʱ��*/
    CePwm   cePwm2;                                                             /*!< ģ��ĵڶ���ͨ��ʹ�õ�Pwm����*/
    CeTg    ceTg2;                                                              /*!< ģ��ĵڶ���ͨ��ʹ�õ�Tg����*/
    uint32  duty2;                                                              /*!< ģ��ĵڶ���ͨ���������ǿ�ȶ�Ӧ��Pwm�ߵ�ƽ��ʱ��*/
}CeDmdTb;
/*
 *CeDmdTb��������
 */
typedef struct
{
    CE_STATUS   (*initialCh1)(CeDmdTb* ceDmdTb, CE_RESOURCE cePwm1, CE_RESOURCE ceTg1);
                                                                                /*!< @brief  CeDmdTbģ���ʼ����һ��ͨ������һ��ͨ�����Ե���ʹ�ã��ڶ���ͨ�������������һ��ͨ������ʹ�ã�
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��
                                                                                     @param  cePwm1:CeDmdTbģ���һ��ͨ��ʹ�õ�Pwm��Դ��
                                                                                     @param  ceTg1:CeDmdTbģ���һ��ͨ��ʹ�õ�Tg��Դ��*/

    CE_STATUS   (*initialCh2)(CeDmdTb* ceDmdTb, CE_RESOURCE cePwm2, CE_RESOURCE ceTg2);
                                                                                /*!< @brief  CeDmdTbģ���ʼ����һ��ͨ������һ��ͨ�����Ե���ʹ�ã��ڶ���ͨ�������������һ��ͨ������ʹ�ã�
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��
                                                                                     @param  cePwm2:CeDmdTbģ��ڶ���ͨ��ʹ�õ�Pwm��Դ��
                                                                                     @param  ceTg2:CeDmdTbģ��ڶ���ͨ��ʹ�õ�Tg��Դ��*/

    void        (*setCh1On)(CeDmdTb* ceDmdTb);                                  /*!< @brief  ��һ��ͨ������򿪡��ڴ˲�������Ҫ����ת�����������ɲ������Բ�������ת������ת�������򱣳�Ϊɲ��ǰ��ת������
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��*/

    void        (*setCh2On)(CeDmdTb* ceDmdTb);                                  /*!< @brief  �ڶ���ͨ������򿪡��ڴ˲�������Ҫ����ת�����������ɲ������Բ�������ת������ת�������򱣳�Ϊɲ��ǰ��ת������
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��*/

    void        (*setCh1DriveStrength)(CeDmdTb* ceDmdTb, uint16 driveStrength); /*!< @brief  ������һ��ͨ���������ǿ��
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��
                                                                                     @param  driveStrength:���������ǿ�ȣ���Χ0-10000*/

    void        (*setCh2DriveStrength)(CeDmdTb* ceDmdTb, uint16 driveStrength); /*!< @brief  �����ڶ���ͨ���������ǿ��
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��
                                                                                     @param  driveStrength:���������ǿ�ȣ���Χ0-10000*/

    void        (*setCh1Direction)(CeDmdTb* ceDmdTb, uint8 direction);          /*!< @brief  ���õ�һ��ͨ�������ת������
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��
                                                                                     @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����*/

    void        (*setCh2Direction)(CeDmdTb* ceDmdTb, uint8 direction);          /*!< @brief  ���õڶ���ͨ�������ת������
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��
                                                                                     @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����*/

    void        (*ch1Brake)(CeDmdTb* ceDmdTb);                                  /*!< @brief  ��һ��ͨ��ɲ���������ͣ
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��*/

    void        (*ch2Brake)(CeDmdTb* ceDmdTb);                                  /*!< @brief  �ڶ���ͨ��ɲ���������ͣ
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��*/

    void        (*setCh1Off)(CeDmdTb* ceDmdTb);                                 /*!< @brief  ��һ��ͨ������ر�
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��*/

    void        (*setCh2Off)(CeDmdTb* ceDmdTb);                                 /*!< @brief  �ڶ���ͨ������ر�
                                                                                     @param  ceDmdTb:CeDmdTb���Զ���ָ��*/

}CeDmdTbOp;
/*
 *CeDmdTb��������ʵ��
 */
extern const CeDmdTbOp ceDmdTbOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_DMD_TB_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_DMD_TB_H__


/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���õ�һ�����ͨ������������ת��������Ϊ��ת��Ȼ�����õڶ������ͨ������������ת ��������Ϊ��ת��
******************************************************************************
#include "Creelinks.h"
#include "CeDmdTb.h"
CeDmdTb myDmdTb;
uint16 drivePower;                              //�����������0��10000
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceDmdTbOp.initialCh1(&myDmdTb,R1AGP,R2TI2c);
    ceDmdTbOp.initialCh2(&myDmdTb,R5ACGPW,R10TI2c);

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceDmdTbOp.setCh1Direction(&myDmdTb,0x01);               //����ͨ��1����Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ��1����������������
        {
            ceDmdTbOp.setCh1DriveStrength(&myDmdTb,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdTbOp.ch1Brake(&myDmdTb);                           //ͨ��1�ĵ������ɲ������

        ceDmdTbOp.setCh1Direction(&myDmdTb,0x00);               //����ͨ��1����Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ��1����������������
        {
            ceDmdTbOp.setCh1DriveStrength(&myDmdTb,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdTbOp.ch1Brake(&myDmdTb);                           //ͨ��1�ĵ������ɲ������


        ceDmdTbOp.setCh2Direction(&myDmdTb,0x01);               //����ͨ��2����Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ��2����������������
        {
            ceDmdTbOp.setCh2DriveStrength(&myDmdTb,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdTbOp.ch2Brake(&myDmdTb);                           //ͨ��2�ĵ������ɲ������

        ceDmdTbOp.setCh2Direction(&myDmdTb,0x00);               //����ͨ��2����Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ��2����������������
        {
            ceDmdTbOp.setCh2DriveStrength(&myDmdTb,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdTbOp.ch2Brake(&myDmdTb);                           //ͨ��2�ĵ������ɲ������
    };
}
******************************************************************************
*/

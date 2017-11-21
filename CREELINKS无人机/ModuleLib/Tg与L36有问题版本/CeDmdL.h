/**
  ******************************************************************************
  * @file    CeDmdL.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeDmdLģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_DMD_L_H__
#define __CE_DMD_L_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_DMD_L_VERSION__ 1                                                  /*!< �������ļ��İ汾��*/
#define __CE_DMD_L_NEED_CREELINKS_VERSION__ 1                                   /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_DMD_L_NEED_CREELINKS_VERSION__)            /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeDmdL.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

//#define CE_DMD_L_USE_TO_SETP_MOTOR                                            /*!< �Ƿ�ģ�����ڲ������*/

#ifdef CE_DMD_L_USE_TO_SETP_MOTOR

/*
 *CeDmdL��Ϊ�������ʹ��ʱ�Ĺ�����ʽ
*/
typedef enum
{
    CE_DMD_L_SINGLE_4_SHOOT =0,                                                 /*!< ������*/
    CE_DMD_L_DOUBLE_4_SHOOT,                                                    /*!< ˫����*/
    CE_DMD_L_8_SHOOT,                                                           /*!< ����*/
}CE_DMD_L_STEP_MODE;
/*
 *CeDmdL���Զ���
 */
typedef struct
{
    CeTg    ceTg1;                                                              /*!< ģ��������������ĵ�һ��Tg����*/
    CeTg    ceTg2;                                                              /*!< ģ��������������ĵڶ���Tg����*/
    uint8   around;                                                             /*!< �������ת���Ĳ����Ƿ�����һȦ*/
    uint8   setpMode;                                                           /*!< ��������Ĺ�����ʽ*/
    uint8   status;                                                             /*!< ��������Ĺ���״̬*/
}CeDmdL;
/*
 *CeDmdL��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeDmdL* ceDmdL, CE_RESOURCE ceTg1, CE_RESOURCE ceTg2);/*!<
                                                                                     @brief  CeDmdLģ���������������ʼ��
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��
                                                                                     @param  ceTg1:CeDmdLģ��������������ĵ�һ��Tg��Դ��
                                                                                     @param  ceTg2:CeDmdLģ��������������ĵڶ���Tg��Դ��*/

    void        (*setStepMode)(CeDmdL* ceDmdL, CE_DMD_L_STEP_MODE ceDmdLStepMode);/*!<
                                                                                     @brief  ������������з�ʽ
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*setOn)(CeDmdL* ceDmdL);                                       /*!< @brief  ģ��������������������
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*setOff)(CeDmdL* ceDmdL);                                      /*!< @brief  ģ�������������������ر�
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*stepForward)(CeDmdL* ceDmdL);                                 /*!< @brief  ģ���������������ǰ��һ��
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*stepBackward)(CeDmdL* ceDmdL);                                /*!< @brief  ģ�������������������һ��
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

}CeDmdLOp;
/*
 *CeDmdL��������ʵ��
 */
extern const CeDmdLOp ceDmdLOp;

#else //CE_DMD_L_USE_TO_SETP_MOTOR

#define CE_DMD_L_PWM1_CYCLE_NS     10000000                                     /*!< DmdLģ���һ��ͨ����Pwm����ת�ٵ�����*/
#define CE_DMD_L_PWM2_CYCLE_NS     10000000                                     /*!< DmdLģ��ڶ���ͨ����Pwm����ת�ٵ�����*/
/*
 *CeDmdL���Զ���
 */
typedef struct
{
    CePwm   cePwm1;                                                             /*!< ģ��ĵ�һ��ͨ��ʹ�õ�Pwm����*/
    CeTg    ceTg1;                                                              /*!< ģ��ĵ�һ��ͨ��ʹ�õ�Tg����*/
    uint32  duty1;                                                              /*!< ģ��ĵ�һ��ͨ���������ǿ�ȶ�Ӧ��Pwm�ߵ�ƽ��ʱ��*/
    CePwm   cePwm2;                                                             /*!< ģ��ĵڶ���ͨ��ʹ�õ�Pwm����*/
    CeTg    ceTg2;                                                              /*!< ģ��ĵڶ���ͨ��ʹ�õ�Tg����*/
    uint32  duty2;                                                              /*!< ģ��ĵڶ���ͨ���������ǿ�ȶ�Ӧ��Pwm�ߵ�ƽ��ʱ��*/
}CeDmdL;
/*
 *CeDmdL��������
 */
typedef struct
{
    CE_STATUS   (*initialCh1)(CeDmdL* ceDmdL, CE_RESOURCE cePwm1, CE_RESOURCE ceTg1);/*!<
                                                                                     @brief  CeDmdLģ���ʼ����һ��ͨ����
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��
                                                                                     @param  cePwm1:CeDmdLģ���һ��ͨ��ʹ�õ�Pwm��Դ��
                                                                                     @param  ceTg1:CeDmdLģ���һ��ͨ��ʹ�õ�Tg��Դ��*/

    CE_STATUS   (*initialCh2)(CeDmdL* ceDmdL, CE_RESOURCE cePwm2, CE_RESOURCE ceTg2);/*!<
                                                                                     @brief  CeDmdLģ���ʼ����һ��ͨ����
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��
                                                                                     @param  cePwm2:CeDmdLģ��ڶ���ͨ��ʹ�õ�Pwm��Դ��
                                                                                     @param  ceTg2:CeDmdLģ��ڶ���ͨ��ʹ�õ�Tg��Դ��*/

    void        (*setCh1On)(CeDmdL* ceDmdL);                                    /*!< @brief  ��һ��ͨ������򿪡��ڴ˲���ǰ����Ҫ����ת������
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*setCh2On)(CeDmdL* ceDmdL);                                    /*!< @brief  �ڶ���ͨ������򿪡��ڴ˲���ǰ����Ҫ����ת������
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*setCh1DriveStrength)(CeDmdL* ceDmdL, uint16 driveStrength);   /*!< @brief  ������һ��ͨ���������ǿ��
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��
                                                                                     @param  driveStrength:���������ǿ�ȣ���Χ0-10000*/

    void        (*setCh2DriveStrength)(CeDmdL* ceDmdL, uint16 driveStrength);   /*!< @brief  �����ڶ���ͨ���������ǿ��
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��
                                                                                     @param  driveStrength:���������ǿ�ȣ���Χ0-10000*/

    void        (*setCh1Direction)(CeDmdL* ceDmdL, uint8 direction);            /*!< @brief  ���õ�һ��ͨ�������ת������
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��
                                                                                     @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����*/

    void        (*setCh2Direction)(CeDmdL* ceDmdL, uint8 direction);            /*!< @brief  ���õڶ���ͨ�������ת������
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��
                                                                                     @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����*/

    void        (*ch1Brake)(CeDmdL* ceDmdL);                                    /*!< @brief  ��һ��ͨ��ɲ���������������رղ�����
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*ch2Brake)(CeDmdL* ceDmdL);                                    /*!< @brief  �ڶ���ͨ��ɲ���������������رղ�����
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*setCh1Off)(CeDmdL* ceDmdL);                                   /*!< @brief  ��һ��ͨ������ر�
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

    void        (*setCh2Off)(CeDmdL* ceDmdL);                                   /*!< @brief  �ڶ���ͨ������ر�
                                                                                     @param  ceDmdL:CeDmdL���Զ���ָ��*/

}CeDmdLOp;
/*
 *CeDmdL��������ʵ��
 */
extern const CeDmdLOp ceDmdLOp;

#endif //CE_DMD_L_USE_TO_SETP_MOTOR

#endif //(__CE_CREELINKS_VERSION__ < __CE_DMD_L_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_DMD_L_H__


/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ģ�鹤���ڲ��������ʽ�����Գ���ʵ��ǰ��1000����Ȼ���ٺ���1000����ע�⣺��򿪺�CE_DMD_L_USE_TO_SETP_MOTOR
******************************************************************************
#include "Creelinks.h"
#include "CeDmdL.h"
CeDmdL myDmdL;
uint16 il;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceDmdLOp.initial(&myDmdL,R2TI2c,R10TI2c);   //ע�⣺ģ����Ϊ�������ʹ��ʱ������ʹ��Pwm�źţ�ͬʱӦ��ģ������������λ�ü������ߡ�
    ceDmdLOp.setStepMode(&myDmdL,CE_DMD_L_SINGLE_4_SHOOT);//���ò������������ʽ�������ġ�
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        for(i=0;i<1000;i++)
        {
            ceDmdLOp.stepForward(&myDmdL);      //�������ǰ��һ��
            ceSystemOp.delayMs(10);
        }

        for(i=0;i<1000;i++)
        {
            ceDmdLOp.stepBackward(&myDmdL);     //�����������һ��
            ceSystemOp.delayMs(10);
        }
    };
}
******************************************************************************
*/

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���õ�һ�����ͨ������������ת��������Ϊ��ת��Ȼ�����õڶ������ͨ������������ת ��������Ϊ��ת��ע�⣺��رպ�CE_DMD_L_USE_TO_SETP_MOTOR
******************************************************************************
#include "Creelinks.h"
#include "CeDmdL.h"
CeDmdL myDmdL;
uint16 drivePower;                              //�����������0��10000
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceDmdLOp.initialCh1(&myDmdL,R1AGP,R2TI2c);
    ceDmdLOp.initialCh2(&myDmdL,R5ACGPW,R10TI2c);

    while (1)
    {
        ceTaskOp.mainTask();                                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceDmdLOp.setCh1Direction(&myDmdL,0x01);                 //����ͨ��1����Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ��1����������������
        {
            ceDmdLOp.setCh1DriveStrength(&myDmdL,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdLOp.ch1Brake(&myDmdL);                             //ͨ��1�ĵ������ɲ������

        ceDmdLOp.setCh1Direction(&myDmdL,0x00);                 //����ͨ��1����Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ��1����������������
        {
            ceDmdLOp.setCh1DriveStrength(&myDmdL,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdLOp.ch1Brake(&myDmdL);                             //ͨ��1�ĵ������ɲ������


        ceDmdLOp.setCh2Direction(&myDmdL,0x01);                 //����ͨ��2����Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ��2����������������
        {
            ceDmdLOp.setCh2DriveStrength(&myDmdL,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdLOp.ch2Brake(&myDmdL);                             //ͨ��2�ĵ������ɲ������

        ceDmdLOp.setCh2Direction(&myDmdL,0x00);                 //����ͨ��2����Ϊ����
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //��0��ʼ����ͨ��2����������������
        {
            ceDmdLOp.setCh2DriveStrength(&myDmdL,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdLOp.ch2Brake(&myDmdL);                             //ͨ��2�ĵ������ɲ������
    };
}
******************************************************************************
*/

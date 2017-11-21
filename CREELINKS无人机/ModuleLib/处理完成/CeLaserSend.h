/**
  ******************************************************************************
  * @file    CeLaserSend.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeLaserSendģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_LASER_SEND_H__
#define __CE_LASER_SEND_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_LASER_SEND_VERSION__ 1                                           /*!< �������ļ��İ汾��*/
#define __CE_LASER_SEND_NEED_CREELINKS_VERSION__ 1                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_LASER_SEND_NEED_CREELINKS_VERSION__)     /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeLaserSend.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeLaserSend���Զ���
 */
typedef struct
{
    CePwm cePwm;                                                            /*!< ģ��ʹ�õ���Pwm��Դ*/
    CeTimer ceTimer;                                                        /*!< ����ʱʹ�õľ�ȷ��ʱ��*/
    CeGpio ceGpio;
    uint8 workMode;                                                         /*!< ������ʽ��0x00:Pwm��ʽ�� 0x01:Gpio+Timer��ʽ*/
}CeLaserSend;
/*
 *CeLaserSend��������
 */
typedef struct
{
    CE_STATUS (*initialByPwm)(CeLaserSend* ceLaserSend, CE_RESOURCE cePwm);     /*!< @brief ʹ��һ��Pwm��Դ����CeLaserSendģ���ʼ��
                                                                                     @param ceLaserSend:CeLaserSend���Զ���ָ��
                                                                                     @param cePwm:CeLaserSendģ��ʹ�õ���Դ��*/

    CE_STATUS (*initialByGpio)(CeLaserSend* ceLaserSend, CE_RESOURCE ceGpio, CE_RESOURCE ceTimer);/*!<
                                                                                     @brief ʹ��һ��Gpio�ڼ�һ����ʱ������CeLaserSendģ���ʼ��
                                                                                     @param ceLaserSend:CeLaserSend���Զ���ָ��
                                                                                     @param cePwm:CeLaserSendģ��ʹ�õ���Դ��
                                                                                     @param ceTimer:CeTimerģ��ʹ�õĶ�ʱ����Դ��*/

    void (*setOn)(CeLaserSend* ceLaserSend);                                    /*!< @brief ���ü��ⷢ���Ϊ����״̬�������ⷢ��һֱ��������
                                                                                     @param ceLaserSend:CeLaserSend���Զ���ָ��*/

    void (*setOff)(CeLaserSend* ceLaserSend);                                   /*!< @brief ���ü��ⷢ���Ϊ�ر�״̬�������ⷢ��ܲ���������
                                                                                     @param ceLaserSend:CeLaserSend���Զ���ָ��*/


}CeLaserSendOp;
/*
 *CeLaserSend��������ʵ��
 */
extern CeLaserSendOp ceLaserSendOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_INFSEND_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_LASER_SEND_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ÿ��1S��һ�μ��⣬��Ҫ�뼤���ն�Ӧ����
******************************************************************************
#include "Creelinks.h"
#include "CeLaserSend.h"
CeLaserSend myLaserSend;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceLaserSendOp.initial(&myLaserSend,R5ACGPW);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceLaserSendOp.setOn(&myLaserSend);      //�򿪼���ͷ
        ceSystemOp.delayMs(1000);
        ceLaserSendOp.setOff(&myLaserSend);     //�رռ���ͷ
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

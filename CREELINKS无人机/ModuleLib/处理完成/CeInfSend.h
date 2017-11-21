/**
  ******************************************************************************
  * @file    CeInfSend.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeInfSendģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_INF_SEND_H__
#define __CE_INF_SEND_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_INF_SEND_VERSION__ 1                                           /*!< �������ļ��İ汾��*/
#define __CE_INF_SEND_NEED_CREELINKS_VERSION__ 1                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_INF_SEND_NEED_CREELINKS_VERSION__)     /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeInfSend.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeInfSend���Զ���
 */
typedef struct
{
    CePwm cePwm;                                                            /*!< ģ��ʹ�õ���Pwm��Դ*/
    CeTimer ceTimer;                                                        /*!< ����ʱʹ�õľ�ȷ��ʱ��*/
    CeGpio ceGpio;
    uint8 workMode;                                                         /*!< ������ʽ��0x00:Pwm��ʽ�� 0x01:Gpio+Timer��ʽ*/
}CeInfSend;
/*
 *CeInfSend��������
 */
typedef struct
{
    CE_STATUS   (*initialByPwm)(CeInfSend* ceInfSend, CE_RESOURCE cePwm);   /*!< @brief ʹ��һ��Pwm��Դ����CeInfSendģ���ʼ��
                                                                                 @param ceInfSend:CeInfSend���Զ���ָ��
                                                                                 @param cePwm:CeInfSendģ��ʹ�õ���Դ��*/

    CE_STATUS   (*initialByGpio)(CeInfSend* ceInfSend, CE_RESOURCE ceGpio, CE_RESOURCE ceTimer);/*!<
                                                                                 @brief ʹ��һ��Gpio�ڼ�һ����ʱ������CeInfSendģ���ʼ��
                                                                                 @param ceInfSend:CeInfSend���Զ���ָ��
                                                                                 @param cePwm:CeInfSendģ��ʹ�õ���Դ��
                                                                                 @param ceTimer:CeTimerģ��ʹ�õĶ�ʱ����Դ��*/

    void        (*setOn)(CeInfSend* ceInfSend);                             /*!< @brief ���ú��ⷢ���Ϊ����״̬�������ⷢ��һֱ���������
                                                                                 @param ceInfSend:CeInfSend���Զ���ָ��*/

    void        (*setOff)(CeInfSend* ceInfSend);                            /*!< @brief ���ú��ⷢ���Ϊ�ر�״̬�������ⷢ��ܲ����������
                                                                                 @param ceInfSend:CeInfSend���Զ���ָ��*/


}CeInfSendOp;
/*
 *CeInfSend��������ʵ��
 */
extern const CeInfSendOp ceInfSendOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_INFSEND_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_INF_SEND_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ÿ��1S��һ�κ��⣬��Ҫ������ն�Ӧ����
******************************************************************************
#include "Creelinks.h"
#include "CeInfSend.h"
CeInfSend myInfSend;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceInfSendOp.initial(&myInfSend,R5ACGPW);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceInfSendOp.setOn(&myInfSend);          //�򿪺���ͷ
        ceSystemOp.delayMs(1000);
        ceInfSendOp.setOff(&myInfSend);         //�رպ���ͷ
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

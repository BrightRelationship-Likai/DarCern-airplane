/**
  ******************************************************************************
  * @file    CeBtnx3P.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBtnx3Pģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BTN_X3P_H__
#define __CE_BTN_X3P_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BTN_X3P_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_BTN_X3P_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_BTN_X3P_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeBtnx3P.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeBtnx3P���Զ���
 */
typedef struct
{
    CeGpio      ceGpio0;                                                /*!< ģ��ʹ�õ���Gpio��Դ���Զ���*/
    CeGpio      ceGpio1;
    CeGpio      ceGpio2;
    CeTask      ceTask;                                                 /*!< ģ��ʹ�õ�Task���Զ���*/
    uint8       btnStatus;                                              /*!< ��ť��ǰ״̬*/
    void        (*callBackPressEvent)(uint8 btnIndex);                  /*!< �����¼��ص�����;btnIndex:���µİ�����������Χ0-2*/
}CeBtnx3P;
/*
 *CeBtnx3P��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeBtnx3P* ceBtnx3P, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackPressEvent)(uint8 btnIndex));/*!<
                                                                             @brief CeBtnx3Pģ��ʹ������Gpio������ɳ�ʼ��
                                                                             @param ceBtnx3P:CeBtnx3P���Զ���ָ��
                                                                             @param ceGpio0:CeBtnx3Pģ��ʹ�õĵ�һ��Gpio����Դ��
                                                                             @param ceGpio1:CeBtnx3Pģ��ʹ�õĵڶ���Gpio����Դ��
                                                                             @param ceGpio2:CeBtnx3Pģ��ʹ�õĵ�����Gpio����Դ��
                                                                             @param callBackPressEvent:��������ʱ�Ļص�����;btnIndex:���µİ�����������Χ0-2*/
}CeBtnx3POp;
/*
 *CeBtnx3P��������ʵ��
 */
extern const CeBtnx3POp ceBtnx3POp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_BTN_X3P_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_BTN_X3P_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����)
* @function ���Զ�Ӧ��ť�Ļص��Ƿ���������Ӧ
******************************************************************************
#include "Creelinks.h"
#include "CeBtnx3P.h"
CeBtnx3P ceBtnx3P;                                //����CeBenx3P���Զ���
void callBackPressEvent(uint8 btnIndex)
{
    ceDebugOp.printf("callBackPressEvent is called!\tbtnIndex: %d\n", btnIndex);//�������ص����Ѵ����˻ص��İ�ť������ӡ����
}
int main(void)
{
    ceSystemOp.initial();                        //Creelinks������ʼ��
    ceDebugOp.initial(Uartx);                        //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceBtnx3POp.initialByTg(&ceBtnx3P, RxT, callBackPressEvent); //ʹ��Tg�ڳ�ʼ��ceBtnx3P����
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
    };
}
******************************************************************************
*/

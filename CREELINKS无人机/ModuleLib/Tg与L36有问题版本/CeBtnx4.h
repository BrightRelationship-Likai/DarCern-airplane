/**
  ******************************************************************************
  * @file    CeBtnx4.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBtnx4ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BTNX4_H__
#define __CE_BTNX4_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BTNX4_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_BTNX4_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_BTNX4_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeBtnx4.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeBtnx4���Զ���
 */
typedef struct
{
    CeGpio ceGpio0;                                                         /*!< ģ��ʹ�õ���Tg����*/
    CeGpio ceGpio1;
    CeGpio ceGpio2;
    CeTask ceTask;                                                          /*!< ģ��ʹ�õ���Task����*/
    uint8 keyStatus;                                                        /*!< ��¼��һ�ΰ���״̬*/
    void (*callBackKeyPressEvent)(uint8 keyCode);                           /*!< ���̰����¼�����ʱ����Ҫִ�еĺ�����keyCode:�����µİ�����*/
}CeBtnx4;
/*
 *CeBtnx4��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeBtnx4* ceBtnx4, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackKeyPressEvent)(uint8 keyCode));/*!<
                                                                             @brief  CeBtnx4ģ��ʹ������Gpio����ɳ�ʼ��
                                                                             @param  ceBtnx4:ceBtnx4���Զ���ָ��
                                                                             @param ceGpio0:Ce8Segx1ģ��ʹ�õĵ�һ��Gpio��Դ��
                                                                             @param ceGpio1:Ce8Segx1ģ��ʹ�õĵڶ���Gpio��Դ��
                                                                             @param ceGpio2:Ce8Segx1ģ��ʹ�õĵ�����Gpio��Դ��
                                                                             @param callBackKeyPressEvent:���̰����¼�����ʱ����Ҫִ�еĺ���:keyCode:�����µļ��룬��Χ0-3*/
}CeBtnx4Op;
/*
 *CeBtnx4��������ʵ��
 */
extern const CeBtnx4Op ceBtnx4Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_BTNX4_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_BTNX4_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����), 
* @function �������ⰴť�󣬽���ֵͨ�����ڽ���Ϣ��ʾ����λ��
******************************************************************************
#include "Creelinks.h"
#include "CeBtnx4.h"
CeBtnx4 myBtnx4;
void callBackPress(uint8 keyCode)
{
    ceDebugOp.printf("Key %d is pressing!\n",keyCode);     //��ӡ���µİ�ť��
}
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                              //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceBtnx4Op.initialByTg(&myBtnx4,R2TI2c,callBackPress);   //ʹ��R2TI2c��Tg���ܹ��ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeBtn16S.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBtn16Sģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)�������Int�ӿڳ�ʼ������ص������ж���ִ�С�
  *2)�������Gpio�ӿڳ�ʼ������ص�����main�����е�mainTask()��ִ�С�
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BTN_16S_H__
#define __CE_BTN_16S_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BTN_16S_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_BTN_16S_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_BTN_16S_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeBtn16S.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeBtn16S���Զ���
 */
typedef struct
{
    CeTg ceTg;                                               /*!< ģ��ʹ�õ���Tg����*/
    CeTask ceTask;                                           /*!< ģ��ʹ�õ���Task����*/
    uint16 keyStatus;                                        /*!< ��¼��һ�ΰ���״̬*/
    void (*callBackKeyPressEvent)(uint8 keyCode);            /*!< ���̰����¼�����ʱ����Ҫִ�еĺ�����keyCode:�����µİ�����*/
}CeBtn16S;
/*
 *CeBtn16S��������
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeBtn16S* ceBtn16S, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackKeyPressEvent)(uint8 keyCode));/*!<
                                                             @brief  CeBtn16Sģ��ʹ������Gpio����ɳ�ʼ��
                                                             @param  ceBtn16S:ceBtn16S���Զ���ָ��
                                                             @param  ceGpio0:Ce8Segx1ģ��ʹ�õĵ�һ��Gpio��Դ��
                                                             @param  ceGpio1:Ce8Segx1ģ��ʹ�õĵڶ���Gpio��Դ��
                                                             @param  ceGpio2:Ce8Segx1ģ��ʹ�õĵ�����Gpio��Դ��
                                                             @param  callBackKeyPressEvent:���̰����¼�����ʱ����Ҫִ�еĺ�����keyCode:�����µļ���*/

    CE_STATUS   (*initialByTg)(CeBtn16S* ceBtn16S,CE_RESOURCE ceTg, void (*callBackKeyPressEvent)(uint8 keyCode));/*!<
                                                             @brief  CeBtn16Sģ��ʹ��Tg����ɳ�ʼ��
                                                             @param  ceBtn16S:ceBtn16S���Զ���ָ��
                                                             @param  ceTg:CeBtn16Sģ��ʹ�õ�Tg��Դ��
                                                             @param  callBackKeyPressEvent:���̰����¼�����ʱ����Ҫִ�еĺ�����keyCode:�����µļ���*/
}CeBtn16SOp;
/*
 *CeBtn16S��������ʵ��
 */
extern CeBtn16SOp ceBtn16SOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_SW4X4_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SW4X4_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����), 
* @function �������ⰴť�󣬽���ֵͨ�����ڽ���Ϣ��ʾ����λ��
******************************************************************************
#include "Creelinks.h"
#include "CeBtn16S.h"
CeBtn16S myBtn16S;
void callBackPress(uint8 keyCode)
{
    ceDebugOp.printf("Key %d is pressing!\n",keyCode);     //��ӡ���µİ�ť��
}
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                              //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceBtn16SOp.initialByTg(&myBtn16S,R2TI2c,callBackPress); //ʹ��R2TI2c��Tg���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
    };
}
******************************************************************************
*/

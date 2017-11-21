/**
  ******************************************************************************
  * @file    CeRly4.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly4ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY4_H__
#define __CE_RLY4_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY4_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_RLY4_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY4_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeRly4.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeRly4���Զ���
 */
typedef struct
{
    uint8   rlyStatus;                                              /*!< �������еļ̵���״̬*/
    CeTg    ceTg;                                                   /*!< ģ��ʹ�õ���Tg�ӿ���Դ*/
}CeRly4;
/*
 *CeRly4��������
 */
typedef struct
{
    CE_STATUS (*initialWithTg)(CeRly4* ceRly4,CE_RESOURCE ceTg);    /*!< @brief  CeRly4ģ���ʼ��
                                                                         @param  ceRly4:CeRly4���Զ���ָ��
                                                                         @param  ceTg:CeRly4ģ��ʹ�õ���Դ��*/

    CE_STATUS (*initialWithGpio)(CeRly4* ceRly4,CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);
                                                                    /*!< @brief  ʹ������Gpio�������CeRly4ģ���ʼ��
                                                                         @param  ceRly4:CeRly4���Զ���ָ��
                                                                         @param  ceGpio0:��һ��Gpio��
                                                                         @param  ceGpio1:�ڶ���Gpio��
                                                                         @param  ceGpio2:������Gpio��*/

    void      (*setOn)(CeRly4* ceRly4,uint8 rlyIndex);              /*!< @brief  ���ü̵����պ�
                                                                         @param  ceRly4:CeRly4���Զ���ָ��
                                                                         @param  rlyIndex:��Ҫ�պϵļ̵������*/

    void      (*setOff)(CeRly4* ceRly4,uint8 rlyIndex);             /*!< @brief  ���ü̵����Ͽ�
                                                                         @param  ceRly4:CeRly4���Զ���ָ��
                                                                         @param  rlyIndex:��Ҫ�Ͽ��ļ̵������*/
}CeRly4Op;
/*
 *CeRly4��������ʵ��
 */
extern const CeRly4Op ceRly4Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY4_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_RLY4_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���ü̵�������������Ͽ�
******************************************************************************
#include "Creelinks.h"
#include "CeRly4.h"
CeRly4 myRly;
uint8 index = 0;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceRly4Op.initialWithTg(&myRly, R2TI2c);     //ʹ��R2TI2c��Tg���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceRly4Op.setOn(&myRly, index % 4);      //���ü̵���״̬Ϊ����
        ceSystemOp.delayMs(500);
        ceRly4Op.setOff(&myRly, index % 4);     //���ü̵���״̬Ϊ�Ͽ�
        ceSystemOp.delayMs(500);
        index++;
    };
}
******************************************************************************
*/

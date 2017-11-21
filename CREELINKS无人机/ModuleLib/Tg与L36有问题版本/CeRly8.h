/**
  ******************************************************************************
  * @file    CeRly8.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly8ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY8_H__
#define __CE_RLY8_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY8_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_RLY8_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY8_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeRly8.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
*CeRly8���Զ���
*/
typedef struct
{
    uint8   rlyStatus;                                              /*!< �������еļ̵���״̬*/
    CeTg    ceTg;                                                   /*!< ģ��ʹ�õ���Tg�ӿ���Դ*/
}CeRly8;
/*
*CeRly8��������
*/
typedef struct
{
    CE_STATUS(*initialWithTg)(CeRly8* ceRly8, CE_RESOURCE ceTg);    /*!< @brief  CeRly8ģ���ʼ��
                                                                         @param  ceRly8:CeRly8���Զ���ָ��
                                                                         @param  ceTg:CeRly8ģ��ʹ�õ���Դ��*/

    CE_STATUS(*initialWithGpio)(CeRly8* ceRly8, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);
                                                                    /*!< @brief  ʹ������Gpio�������CeRly8ģ���ʼ��
                                                                         @param  ceRly8:CeRly8���Զ���ָ��
                                                                         @param  ceGpio0:��һ��Gpio��
                                                                         @param  ceGpio1:�ڶ���Gpio��
                                                                         @param  ceGpio2:������Gpio��*/

    void(*setOn)(CeRly8* ceRly8, uint8 rlyIndex);                   /*!< @brief ���ü̵����պ�
                                                                         @param ceRly8:CeRly8���Զ���ָ��
                                                                         @param rlyIndex:��Ҫ�պϵļ̵������*/

    void(*setOff)(CeRly8* ceRly8, uint8 rlyIndex);                  /*!< @brief ���ü̵����Ͽ�
                                                                         @param ceRly8:CeRly8���Զ���ָ��
                                                                         @param rlyIndex:��Ҫ�Ͽ��ļ̵������*/
}CeRly8Op;
/*
*CeRly8��������ʵ��
*/
extern const CeRly8Op ceRly8Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY8_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_RLY8_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���ü̵�������������Ͽ�
******************************************************************************
#include "Creelinks.h"
#include "CeRly8.h"
CeRly8 myRly;
uint8 index = 0;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceRly8Op.initialWithTg(&myRly, R2TI2c);     //ʹ��R2TI2c��Tg���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceRly8Op.setOn(&myRly, index % 8);      //���ü̵���״̬Ϊ����
        ceSystemOp.delayMs(500);
        ceRly8Op.setOff(&myRly, index % 8);     //���ü̵���״̬Ϊ�Ͽ�
        ceSystemOp.delayMs(500);
        index++;
    };
}
******************************************************************************
*/

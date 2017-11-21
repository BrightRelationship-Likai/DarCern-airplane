/**
  ******************************************************************************
  * @file    CeRly16.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly16ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY16_H__
#define __CE_RLY16_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY16_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_RLY16_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY16_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeRly16.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeRly16���Զ���
*/
typedef struct
{
    uint16  rlyStatus;                                              /*!< �������еļ̵���״̬*/
    CeTg    ceTg;                                                   /*!< ģ��ʹ�õ���Tg�ӿ���Դ*/
}CeRly16;
/*
 *CeRly16��������
*/
typedef struct
{
    CE_STATUS(*initialWithTg)(CeRly16* ceRly16, CE_RESOURCE ceTg);  /*!< @brief  CeRly16ģ���ʼ��
                                                                         @param  ceRly16:CeRly16���Զ���ָ��
                                                                         @param  ceTg:CeRly16ģ��ʹ�õ���Դ��*/

    CE_STATUS(*initialWithGpio)(CeRly16* ceRly16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);
                                                                    /*!< @brief  ʹ������Gpio�������CeRly16ģ���ʼ��
                                                                         @param  ceRly16:CeRly16���Զ���ָ��
                                                                         @param  ceGpio0:��һ��Gpio��
                                                                         @param  ceGpio1:�ڶ���Gpio��
                                                                         @param  ceGpio2:������Gpio��*/

    void(*setOn)(CeRly16* ceRly16, uint8 rlyIndex);                 /*!< @brief ���ü̵����պ�
                                                                         @param ceRly16:CeRly16���Զ���ָ��
                                                                         @param rlyIndex:��Ҫ�պϵļ̵������*/

    void(*setOff)(CeRly16* ceRly16, uint8 rlyIndex);                /*!< @brief ���ü̵����Ͽ�
                                                                         @param ceRly16:CeRly16���Զ���ָ��
                                                                         @param rlyIndex:��Ҫ�Ͽ��ļ̵������*/
}CeRly16Op;
/*
*CeRly16��������ʵ��
*/
extern const CeRly16Op ceRly16Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY16_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_RLY16_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���ü̵�������������Ͽ�
******************************************************************************
#include "Creelinks.h"
#include "CeRly16.h"
CeRly16 myRly;
uint8 index = 0;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceRly16Op.initialWithTg(&myRly, R2TI2c);    //ʹ��R2TI2c��Tg���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceRly16Op.setOn(&myRly, index % 16);    //���ü̵���״̬Ϊ����
        ceSystemOp.delayMs(500);
        ceRly16Op.setOff(&myRly, index % 16);   //���ü̵���״̬Ϊ�Ͽ�
        ceSystemOp.delayMs(500);
        index++;
    };
}
******************************************************************************
*/

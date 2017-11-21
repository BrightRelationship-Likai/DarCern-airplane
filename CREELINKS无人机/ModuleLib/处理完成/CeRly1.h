/**
  ******************************************************************************
  * @file    CeRly1.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly1ģ�������ͷ�ļ�������һ·�̵����Ŀ���
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY1_H__
#define __CE_RLY1_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY1_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_RLY1_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY1_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeRly1.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeRly1���Զ���
 */
typedef struct
{
     CeGpio ceGpio;
}CeRly1;
/*
 *CeRly1��������
 */
typedef struct
{
    CE_STATUS (*initial)(CeRly1* ceRly1,CE_RESOURCE ceGpio);    /*!< @brief  CeRly1ģ���ʼ��
                                                                     @param  ceRly1:CeRly1���Զ���ָ��*/

    void     (*setOn)(CeRly1* ceRly1);                          /*!< @brief  ���ü̵����պ�
                                                                     @param  ceRly1:CeRly1���Զ���ָ��*/

    void      (*setOff)(CeRly1* ceRly1);                        /*!< @brief  ���ü̵����Ͽ�
                                                                     @param  ceRly1:CeRly1���Զ���ָ��*/
}CeRly1Op;
/*
 *CeRly1��������ʵ��
 */
extern const CeRly1Op ceRly1Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY1_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_RLY1_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���ü̵�����1HZ��Ƶ��������Ͽ�
******************************************************************************
#include "Creelinks.h"
#include "CeRly1.h"
CeRly1 myRly;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceRly1Op.initial(&myRly, R1AGP);            //ʹ��R1AGP��Gpio���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceRly1Op.setOn(&myRly);                 //���ü̵���״̬Ϊ����
        ceSystemOp.delayMs(500);
        ceRly1Op.setOff(&myRly);                //���ü̵���״̬Ϊ�Ͽ�
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

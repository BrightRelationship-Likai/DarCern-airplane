/**
  ******************************************************************************
  * @file    CeRly2.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly2ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY2_H__
#define __CE_RLY2_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY2_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_RLY2_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY2_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeRly2.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeRly2���Զ���
 */
typedef struct
{
    CeGpio ceGpio0;
    CeGpio ceGpio1;
}CeRly2;
/*
 *CeRly2��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeRly2* ceRly2,CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1 );   /*!< @brief CeRly1ģ���ʼ��
                                                                                             @param ceRly1:CeRly1���Զ���ָ��*/

    void        (*setOn)(CeRly2* ceRly2,uint8 rlyIndex);                                /*!< @brief ���ü̵����պ�
                                                                                             @param ceRly2:CeRly2���Զ���ָ��
                                                                                             @param rlyIndex:��Ҫ�պϵļ̵������*/

    void        (*setOff)(CeRly2* ceRly2,uint8 rlyIndex);                               /*!< @brief ���ü̵����Ͽ�
                                                                                             @param ceRly2:CeRly2���Զ���ָ��
                                                                                             @param rlyIndex:��Ҫ�Ͽ��ļ̵������*/
}CeRly2Op;
/*
 *CeRly2��������ʵ��
 */
extern const CeRly2Op ceRly2Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY2_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_RLY2_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���ü̵�������������Ͽ�
******************************************************************************
#include "Creelinks.h"
#include "CeRly2.h"
CeRly2 myRly;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceRly2Op.initial(&myRly, R1AGP,R0GI);       //ʹ��R1AGP��R3GI��Gpio���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceRly2Op.setOn(&myRly,0);               //���ü̵���0״̬Ϊ����
        ceSystemOp.delayMs(500);
        ceRly2Op.setOff(&myRly,0);              //���ü̵���0״̬Ϊ�Ͽ�
        ceSystemOp.delayMs(500);
        ceRly2Op.setOn(&myRly, 1);              //���ü̵���1״̬Ϊ����
        ceSystemOp.delayMs(500);
        ceRly2Op.setOff(&myRly, 1);             //���ü̵���1״̬Ϊ�Ͽ�
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeRly1Ni.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRly1Niģ�������ͷ�ļ�������һ·�̵����Ŀ���
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY1_NI_H__
#define __CE_RLY1_NI_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY1_NI_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_RLY1_NI_NEED_CREELINKS_VERSION__ 1                         /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY1_NI_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeRly1Ni.h��Ҫ����18���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeRly1Ni���Զ���
 */
typedef struct
{
	CeGpio ceGpio;
}CeRly1Ni;
/*
 *CeRly1Ni��������
 */
typedef struct
{
	CE_STATUS (*initial)(CeRly1Ni* ceRly1Ni,CE_RESOURCE ceGpio);	    /*!< @brief	CeRly1Niģ���ʼ��
														 	 	         @param	ceRly1Ni:CeRly1Ni���Զ���ָ��*/

	void	(*setOn)(CeRly1Ni* ceRly1Ni);	                            /*!< @brief ���ü̵����պ�
                                                                         @param	ceRly1Ni:CeRly1Ni���Զ���ָ��*/

	void 	(*setOff)(CeRly1Ni* ceRly1Ni);	                            /*!< @brief	���ü̵����Ͽ�
                                                                         @param	ceRly1Ni:CeRly1Ni���Զ���ָ��*/
}CeRly1NiOpBase;
/*
 *CeRly1Ni��������ʵ��
 */
extern const CeRly1NiOpBase ceRly1NiOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY1_NI_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_RLY1_NI_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����),����ELinkSTM/ELinkSTM_Pro���İ�
* @function ���ü̵�����1HZ��Ƶ��������Ͽ�
******************************************************************************
#include "Creelinks.h"
#include "CeRly1Ni.h"
CeRly1Ni myRly;
int main(void)
{
    ceSystemOp.initial();                         //Creelinks������ʼ��
    ceSystemOp.initialDebug(R9Uart);              //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceRly1NiOp.initial(&myRly, R1AGP);            //ʹ��R1AGP��Gpio���ܳ�ʼ��ģ��
    while (1)
    {
        ceSystemOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceRly1NiOp.setOn(&myRly);                 //���ü̵���״̬Ϊ����
        ceSystemOp.delayMs(500);
        ceRly1NiOp.setOff(&myRly);                //���ü̵���״̬Ϊ�Ͽ�
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

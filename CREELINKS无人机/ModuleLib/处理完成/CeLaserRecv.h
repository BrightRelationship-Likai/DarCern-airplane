/**
  ******************************************************************************
  * @file    CeLaserRecv.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeLaserRecvģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_LASER_RECV_H__
#define __CE_LASER_RECV_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_INF_RECV_VERSION__ 1                                           /*!< �������ļ��İ汾��*/
#define __CE_INF_RECV_NEED_CREELINKS_VERSION__ 1                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_INF_RECV_NEED_CREELINKS_VERSION__)     /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeLaserRecv.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeLaserRecv���Զ���
 */
typedef struct
{
    CeGpio   ceGpio;
}CeLaserRecv;

/*
 *CeLaserRecv��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeLaserRecv* ceLaserRecv, CE_RESOURCE ceGpio);       /*!< @brief CeLaserRecvģ���ʼ��
                                                                                     @param ceLaserRecv:CeLaserRecv���Զ���ָ��
                                                                                     @param ceGpio:CeLaserRecvģ��ʹ�õ���Դ��*/

    uint8       (*getStatus)(CeLaserRecv* ceLaserRecv);                         /*!< @brief CeLaserRecvģ���ʼ��
                                                                                     @param ceLaserRecv:CeLaserRecv���Զ���ָ��
                                                                                     @return ��ü�����չܵĽ���״̬������0x01:�յ������źţ�����0x00:δ�յ������ź�*/
}CeLaserRecvOp;

/*
 *CeLaserRecv��������ʵ��
 */
extern CeLaserRecvOp ceLaserRecvOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_INFSEND_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_LASER_RECV_H__


/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��ȡ�������ģ��Ľ����ź�״̬����ͨ�����ڴ�ӡ����Ҫ��CeLaserSend��ϲ���
******************************************************************************
#include "Creelinks.h"
#include "CeLaserRecv.h"
CeLaserRecv myLaserRecv;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceLaserRecvOp.initial(&myLaserRecv, R1AGP);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceDebugOp.printf("CeLaserRecv Status:%d\n",ceLaserRecvOp.getStatus(&myLaserRecv));
        ceSystemOp.delayMs(100);
    };
}
******************************************************************************
*/

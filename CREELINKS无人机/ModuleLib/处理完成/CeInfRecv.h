/**
  ******************************************************************************
  * @file    CeInfRecv.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeInfRecvģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)���汾��δʵ����Gpio��ʼ������ע�⣡����
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_INF_RECV_H__
#define __CE_INF_RECV_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_INF_RECV_VERSION__ 1                                           /*!< �������ļ��İ汾��*/
#define __CE_INF_RECV_NEED_CREELINKS_VERSION__ 1                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_INF_RECV_NEED_CREELINKS_VERSION__)     /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeInfRecv.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeInfRecv���Զ���
 */
typedef struct
{
    CeGpio  ceGpio;
    uint8   workMode;
    CeInt ceInt;
    void (*callBackRecvSignal)(void);
}CeInfRecv;

/*
 *CeInfRecv��������
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeInfRecv* ceInfRecv, CE_RESOURCE ceGpio); /*!< @brief CeInfRecvģ���ʼ����ʹ��һ��Gpio�ڡ����汾��δʵ����Gpio��ʼ������ע�⣡����
                                                                                 @param ceInfRecv:CeInfRecv���Զ���ָ��
                                                                                 @param ceGpio:CeInfRecvģ��ʹ�õ���Դ��*/

    CE_STATUS   (*initialByInt)(CeInfRecv* ceInfRecv, CE_RESOURCE ceInt, void(*callBackRecvSignal)(void));   /*!<
                                                                                 @brief CeInfRecvģ���ʼ����ʹ��һ��Int��
                                                                                 @param ceInfRecv:CeInfRecv���Զ���ָ��
                                                                                 @param ceGpio:CeInfRecvģ��ʹ�õ���Դ��
                                                                                 @param callBackRecvSignal:�յ������ź�ʱ���жϻص�*/

    uint8       (*getStatus)(CeInfRecv* ceInfRecv);                         /*!< @brief ��ú�����չܵĽ���״̬
                                                                                 @param ceInfRecv:CeInfRecv���Զ���ָ��
                                                                                 @return ��ú�����չܵĽ���״̬������0x01:�յ������ź�ͬ�� ����0x00:δ�յ������ź�*/
}CeInfRecvOp;

/*
 *CeInfRecv��������ʵ��
 */
extern const CeInfRecvOp ceInfRecvOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_INFSEND_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_INF_RECV_H__


/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��ȡ�������ģ��Ľ����ź�״̬����ͨ�����ڴ�ӡ����Ҫ��CeLaserSend��ϲ���
******************************************************************************
#include "Creelinks.h"
#include "CeInfRecv.h"
CeInfRecv myInfRecv;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceInfRecvOp.initial(&myInfRecv, R1AGP);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceDebugOp.printf("CeInfRecv Status:%d\n",ceInfRecvOp.getStatus(&myInfRecv));
        ceSystemOp.delayMs(100);
    };
}
******************************************************************************
*/

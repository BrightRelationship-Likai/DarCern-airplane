/**
  ******************************************************************************
  * @file    CeEvSw.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeEvSwģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)�������ļ��������񶯿��ء�ˮ�����ء��ɻɹ�
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_EV_SWZ_H__
#define __CE_EV_SWZ_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_EV_SWZ_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_EV_SWZ_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_EV_SWZ_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeEvSw.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeEvSw���Զ���
 */
typedef struct
{
    CeInt ceInt;
    void (*callBackEvent)(void);                    /*!< ��ģ�鴥���¼�ʱ�����õ��¼��ص�����*/
}CeEvSw;
/*
 *CeEvSw��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeEvSw* ceEvSw,CE_RESOURCE ceInt, void (*callBackEvent)(void));/*!<
                                                         @brief CeEvSwģ���ʼ��
                                                         @param ceEvSw:CeEvSw���Զ���ָ��
                                                         @param ceInt:CeEvSwģ��ʹ�õ���Դ��*/

    uint8       (*getBit)(CeEvSw* ceEvSw);      /*!< @brief ��ȡEvSw��Ӧ��GPIO�ڵĵ�ƽ״̬��0x01��0x00
                                                         @param ceEvSw:CeEvSw���Զ���ָ��
                                                         @return ����0�͵�ƽ��ģ�鴦��δ����״̬��1�ߵ�ƽ��ģ�鴦�ڴ���״̬*/
}CeEvSwOp;
/*
 *CeEvSw��������ʵ��
 */
extern CeEvSwOp ceEvSwOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_BEEP_SRC_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_EV_SWZ_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ÿ��⵽�¼��󣬵��ڻص��з�����Ϣ����λ��
******************************************************************************
#include "Creelinks.h"
#include "CeEvSw.h"
CeEvSw mySw;                                         //����CeEvSw���Զ���
void callBackEvent(void)
{
    ceDebugOp.printf("Enter callBack event!\n");    //����ص�����ӡ��Ϣ
}
int main(void)
{
    ceSystemOp.initial();                            //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                       //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceEvSwOp.initial(&mySw, R1AGP, callBackEvent);   //ʹ��R1AGP��ʼ����ע���¼��ص�����
    while (1)
    {
        ceTaskOp.mainTask();                         //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
    };
}
******************************************************************************
*/

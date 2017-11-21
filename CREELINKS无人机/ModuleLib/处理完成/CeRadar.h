/**
  ******************************************************************************
  * @file    CeRadar.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeRadarģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_REDAR_H__
#define __CE_REDAR_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_REDAR_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_REDAR_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_REDAR_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeRadar.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeRadar���Զ���
 */
typedef struct
{
    CeGpio      ceGpio;                                 /*!< CeRadar��TRING����ʹ�õ�Gpio��Դ����*/
    CeInt       ceInt;                                  /*!< CeRadar��ECHO����ʹ�õ��ⲿ�ж�Int��Դ����*/
    uint32      timeCostUs;                             /*!< CeRadar���ڼ���ʱ�仨�ѵ����Զ���*/
    uint32      timeCost;                               /*!< CeRadar���õ��ĸߵ�ƽʱ��*/
    uint8       status;                                 /*!< CeRadar��״̬*/
}CeRadar;
/*
 *CeRadar��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeRadar* ceRadar, CE_RESOURCE ceGpio, CE_RESOURCE ceInt);/*!<
                                                             @brief CeRadarģ���ʼ��
                                                             @param ceRadar:CeRadar���Զ���ָ��
                                                             @param ceGpio:CeRadarģ��ʹ�õ�Gpio��Դ��
                                                             @param ceInt:CeRadarģ��ʹ�õ�Int��Դ�ţ����ⲿ�ж�Int��֧�������غ��½��ش���*/

    uint32      (*getDistance)(CeRadar* ceRadar);       /*!< @brief ��ʼ�״�̽�Ⲣ��ȡ̽�⵽��������ģ��ľ��룬��λmm��������Χ2cm-400cm����������3mm��
                                                             @param ceRadar:CeRadar���Զ���ָ��*/

}CeRadarOp;
/*
 *CeRadar��������ʵ��
 */
extern const CeRadarOp ceRadarOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_REDAR_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_REDAR_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function �ɼ��״�ģ��������ľ��룬��ͨ�����ڽ���Ϣ��ʾ����λ��
******************************************************************************
#include "Creelinks.h"
#include "CeRadar.h"
CeRadar myRadar;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceRadarOp.initial(&myRadar,R1AGP, R6ADIG);  //ʹ��R1AGP��Gpio���� �� R6ADIG��Int���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceDebugOp.printf("The distance is:%dmm\n",ceRadarOp.getDistance(&myRadar));
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

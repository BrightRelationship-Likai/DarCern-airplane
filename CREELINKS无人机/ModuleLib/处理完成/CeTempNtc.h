/**
  ******************************************************************************
  * @file    CeTempNtc.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTempNtcģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TEMP_NTC_H__
#define __CE_TEMP_NTC_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TEMP_NTC_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_TEMP_NTC_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_TEMP_NTC_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeTempNtc.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeTempNtc���Զ���
 */
typedef struct
{
    CeAd ceAd;                                               /*!< ģ��ʹ�õ���Ad����*/
    uint16 temp0C;                                           /*!< TempNtc��0�Ȼ����µ��¶�У׼ֵ*/
    uint16 temp100C;                                         /*!< TempNtc��100�Ȼ����µ��¶�У׼ֵ*/
}CeTempNtc;
/*
 *CeTempNtc��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeTempNtc* ceTempNtc, CE_RESOURCE ceAd);/*!<
                                                                 @brief CeTempNtcģ���ʼ��
                                                                 @param ceTempNtc:CeTempNtc���Զ���ָ��
                                                                 @param ceAd:CeTempNtcģ��ʹ�õ�Ad��Դ��*/

    fp32        (*getTemperature)(CeTempNtc* ceTempNtc);    /*!< @brief ��ȡ�¶�ֵ������λС����
                                                                 @param ceTempNtc:CeTempNtc���Զ���ָ��*/

    void        (*calibration)(CeTempNtc* ceTempNtc, fp32 temp0C, fp32 temp100C);/*!<
                                                                 @brief У׼������0�Ⱥ�100�ȵĻ����зֱ�ʹ��getTemperature��ȡһ���¶�ֵ��Ȼ�������Ӧֵ���Դ��������¶ȼ������
                                                                 @param ceTempNtc:CeTempNtc���Զ���ָ��
                                                                 @param temp0C:ģ����0�Ȼ����е�ʵ�ʲ���ֵ
                                                                 @param temp100C:ģ����100�Ȼ����е�ʵ�ʲ���ֵ*/
}CeTempNtcOp;
/*
 *CeTempNtc��������ʵ��
 */
extern CeTempNtcOp ceTempNtcOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_TEMP_NTC_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TEMP_NTC_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ����ǰ�����¶�ֵͨ�����ڷ��͵���λ��
******************************************************************************
#include "Creelinks.h"
#include "CeTempNtc.h"
CeTempNtc myTemp;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceTempNtcOp.initial(&myTemp, R1AGP);        //ʹ��R1AGP��Ad���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceDebugOp.printf("The Temperature is :%f\n", ceTempNtcOp.getTemperature(&myTemp));
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

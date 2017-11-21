/**
  ******************************************************************************
  * @file    CeTimeDs.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTimeDsģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TIME_DS_H__
#define __CE_TIME_DS_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TIME_DS_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_TIME_DS_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_TIME_DS_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeTimeDs.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/**
  * @brief  �ṹ�壬TimeDs���������ʱ��
  */
typedef struct
{
    uint16 year;        /*!< TimeDsʱ�����*/
    uint8  month;       /*!< TimeDsʱ�����*/
    uint8  day;         /*!< TimeDsʱ�����*/
    uint8  hour;        /*!< TimeDsʱ���ʱ*/
    uint8  minute;      /*!< TimeDsʱ��ķ���*/
    uint8  second;      /*!< TimeDsʱ�����*/
    uint8  week;        /*!< TimeDsʱ�������*/
}CeTimeDsDate;
/*
 *CeTimeDs���Զ���
 */
typedef struct
{
    CeTg ceTg;
    CeTimeDsDate ceTimeDsDate;
}CeTimeDs;
/*
 *CeTimeDs��������
 */
typedef struct
{
    CE_STATUS       (*initialByGpio)(CeTimeDs* ceTimeDs, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                                 @brief CeTimeDsģ��ʹ��Gpio���г�ʼ��
                                                                                 @param ceTimeDs:CeTimeDs���Զ���ָ��
                                                                                 @param ceGpio0:CeTimeDsģ��ʹ�õĵ�һ��Gpio��Դ��
                                                                                 @param ceGpio1:CeTimeDsģ��ʹ�õĵڶ���Gpio��Դ��
                                                                                 @param ceGpio2:CeTimeDsģ��ʹ�õĵ�����Gpio��Դ��*/

    CE_STATUS       (*initialByTg)(CeTimeDs* ceTimeDs,CE_RESOURCE ceTg);    /*!< @brief CeTimeDsģ���ʼ��
                                                                                 @param ceTimeDs:CeTimeDs���Զ���ָ��
                                                                                 @param ceTg:CeTimeDsģ��ʹ�õ���Դ��*/

    CE_STATUS       (*setTime)(CeTimeDs* ceTimeDs, CeTimeDsDate ceTimeDsData);/*!<
                                                                                 @brief ��������ʱ��
                                                                                 @param ceTimeDs:CeTimeDs���Զ���ָ��
                                                                                 @param ceTimeDsData:Ҫ���õ�ʱ��ṹ���ָ��*/

    CeTimeDsDate*   (*getTime)(CeTimeDs* ceTimeDs);                         /*!< @brief ��ȡ����ʱ��
                                                                                 @param ceTimeDs:CeTimeDs���Զ���ָ��
                                                                                 @return ���ػ�ȡ��������ʱ��Ľṹ��ָ��*/
}CeTimeDsOp;
/*
 *CeTimeDs��������ʵ��
 */
const extern CeTimeDsOp ceTimeDsOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_TIME_DS_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TIME_DS_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��ȡ�����ռ䣬��ͨ��������ʾ����λ��
******************************************************************************
#include "Creelinks.h"
#include "CeTimeDs.h"
CeTimeDs myTime;
CeTimeDsDate* pCeTimeDsDate;
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                              //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceTimeDsOp.initialByTg(&myTime, R2TI2c);                //ʹ��R2TI2c��Tg���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        pCeTimeDsDate = ceTimeDsOp.getTime(&myTime);
        ceDebugOp.printf("Now Time: %d:%d:%d: %d:%d:%d\n", pCeTimeDsDate->year, pCeTimeDsDate->month, pCeTimeDsDate->day, pCeTimeDsDate->hour, pCeTimeDsDate->minute, pCeTimeDsDate->second);
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

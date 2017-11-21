/**
  ******************************************************************************
  * @file    CeTempDs.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTempDsģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TEMP_DS_H__
#define __CE_TEMP_DS_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TEMP_DS_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_TEMP_DS_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_TEMP_DS_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeTempDs.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeTempDs���Զ���
 */
typedef struct
{
    CeGpio ceGpio;      /*!< ģ��ʹ�õ���Gpio����*/
}CeTempDs;
/*
 *CeTempDs��������
 */
typedef struct
{
    CE_STATUS    (*initial)(CeTempDs* ceTempDs, CE_RESOURCE ceGpio);    /*!< @brief CeTempDsģ���ʼ��
                                                                             @param ceTempDs:CeTempDs���Զ���ָ��
                                                                             @param ceGpio:CeTempDsģ��ʹ�õ�Gpio��Դ��*/

    fp32         (*getTemperature)(CeTempDs* cedDS18b20);               /*!< @brief ��ȡ�¶�ֵ����Χ-55��+125��
                                                                             @param ceTempDs:CeTempDs���Զ���ָ��
                                                                             @return ���ػ�ȡ�����¶�ֵ������λС����*/
}CeTempDsOp;
/*
 *CeTempDs��������ʵ��
 */
extern const  CeTempDsOp ceTempDsOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_TEMP_DS_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TEMP_DS_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��ȡ�¶Ȳ�ͨ�����ڴ�ӡ����λ��
******************************************************************************
#include "Creelinks.h"
#include "CeTempDs.h"
CeTempDs myTemp;
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                              //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceTempDsOp.initial(&myTemp, R1AGP);                     //ʹ��R1AGP��Gpio���ܳ�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceDebugOp.printf("The temperature is: %f \n", ceTempDsOp.getTemperature(&myTemp));
    };
}
******************************************************************************
*/

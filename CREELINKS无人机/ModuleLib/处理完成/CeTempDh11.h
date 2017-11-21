/**
  ******************************************************************************
  * @file    CeTempDh11.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTempDh11��ʪ�ȴ�����ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TEMP_DH11_H__
#define __CE_TEMP_DH11_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TEMP_DH11_VERSION__ 1                                           /*!< �������ļ��İ汾��*/
#define __CE_TEMP_DH11_NEED_CREELINKS_VERSION__ 1                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_TEMP_DH11_NEED_CREELINKS_VERSION__)     /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeTempDh11.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *@brief CeTEMP_DH11ת�����
 */
typedef struct
{
    uint8 temperature;                      /*!< TempDh11ת��������¶�*/
    uint8 humidity;                         /*!< TempDh11ת�������ʪ��*/
}CeTempDh11Result;

/*
 *@brief CeTempDh11���Զ���
 */
typedef struct
{
    CeGpio ceGpio;                          /*!< CeTempDh11ģ��ʹ�õ���Gpio��Դ��*/
    CeTempDh11Result ceTempDh11Result;              /*!< CeTempDh11ת�����*/
    uint32  systemTick;                     /*!< ���ڼ��CeTempDh11�ӿ�ʼת������ȡת�������ʱ��*/
}CeTempDh11;

/*
 *@brief CeTempDh11��������
 */
typedef struct
{
    CE_STATUS       (*initial)(CeTempDh11* ceTempDh11,CE_RESOURCE ceGpio);  /*!< @brief CeTempDh11ģ��ĳ�ʼ��
                                                                         @param ceTempDh11:CeTempDh11���Զ���ָ��
                                                                         @param ceGpio:CeTempDh11ģ��ʹ�õ���Դ��*/

    void            (*startConvert)(CeTempDh11* ceTempDh11);                /*!< @brief ��ʼһ���¶�ת��
                                                                         @param ceTempDh11:CeTempDh11���Զ���ָ��*/

    CeTempDh11Result*   (*getTemperatureAndHumidity)(CeTempDh11* ceTempDh11);   /*!< @brief ��ȡ���¶�ת�������ע�⣺TEMP_DH11���һ���¶�ת����ʱ��ԼΪ20ms��
                                                                                �뾡����֤����startConvert()������˺���֮���ʱ��������20ms��
                                                                                ���С��20ms���˺�����������ֱ������20ms��������
                                                                         @param ceTempDh11:CeTempDh11���Զ���ָ��
                                                                         @return TempDh11��ת�����*/
}CeTempDh11Op;

/*
 *@brief CeTempDh11��������ʵ��
 */
extern const CeTempDh11Op ceTempDh11Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_TEMP_DH11_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TEMP_DH11_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function �ɼ������¶Ⱥ�ʪ����Ϣ����ͨ��Uart����λ������ʾ
******************************************************************************
#include "Creelinks.h"
CeTempDh11 myTempDh11;                                      //����CeTempDh11����
CeTempDh11Result* result;                                   //����ת�����ָ��
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                              //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceTempDh11Op.initial(&myTempDh11, R1AGP);               //ʹ��RxG��Դ��ʼ����ģ��
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceTempDh11Op.startConvert(&myTempDh11);             //��ʼһ��ת��
        ceSystemOp.delayMs(50);                             //��ʱ���ȴ�ת������
        result = ceTempDh11Op.getTemperatureAndHumidity(&myTempDh11);   //���ת�����
        ceDebugOp.printf("Convert Finish:Temperature=%d, Humidity=%d \n",result->temperature,result->humidity);//��ӡ�����ת�����
    };
}
******************************************************************************
*/

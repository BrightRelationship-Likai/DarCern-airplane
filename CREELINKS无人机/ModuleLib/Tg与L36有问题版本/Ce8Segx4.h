/**
  ******************************************************************************
  * @file    Ce8Segx4.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeAnSwģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_8SEG_X4_H__
#define __CE_8SEG_X4_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_8SEG_X4_VERSION__ 1                                           /*!< �������ļ��İ汾��*/
#define __CE_8SEG_X4_NEED_CREELINKS_VERSION__ 1                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_8SEG_X4_NEED_CREELINKS_VERSION__)     /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�Ce8Segx4.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *Ce8Segx4���Զ���
 */
typedef struct
{
    CeTg        ceTg;                                                   /*!< ģ��ʹ�õ���Tg��Դ���Զ���*/
    CeTicker    ceTicker;                                               /*!< ģ���ڲ�ˢ���õ��ĵδ���붨ʱ������*/
    uint8       showValBit[4];                                          /*!< ����ܵ�״̬����*/
    uint8       nowBit;                                                 /*!< ��ǰˢ�µ����*/
}Ce8Segx4;
/*
 *Ce8Segx4��������
 */
typedef struct
{
    CE_STATUS    (*initialByGpio)(Ce8Segx4* ce8Segx4,CE_RESOURCE ceGpio0,CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                             @brief Ce8Segx4ģ��ʹ������Gpio������ɳ�ʼ��
                                                                             @param ce8Segx4:Ce8Segx4���Զ���ָ��
                                                                             @param ceGpio0:Ce8Segx4ģ��ʹ�õĵ�һ��Gpio����Դ��
                                                                             @param ceGpio1:Ce8Segx4ģ��ʹ�õĵڶ���Gpio����Դ��
                                                                             @param ceGpio2:Ce8Segx4ģ��ʹ�õĵ�����Gpio����Դ��*/

    CE_STATUS    (*initialByTg)(Ce8Segx4* ce8Segx4, CE_RESOURCE ceTg);  /*!< @brief Ce8Segx4ģ��ʹ��Tg����ɳ�ʼ��
                                                                             @param ce8Segx4:Ce8Segx4���Զ���ָ��
                                                                             @param ceTg:Ce8Segx4ģ��ʹ�õ���Դ��*/

    void        (*setOn)(Ce8Segx4* ce8Segx4);                           /*!< @brief ʹģ�鴦�ڿ�����ʾ״̬
                                                                             @param ce8Segx4:Ce8Segx4���Զ���ָ��*/

    void        (*setVal)(Ce8Segx4* ce8Segx4, fp32 val);                /*!< @brief ��ʾ��ֵ
                                                                             @param ce8Segx4:Ce8Segx4���Զ���ָ��
                                                                             @param val:��Ҫ��ʾ��ֵ*/

    void        (*setChars)(Ce8Segx4* ce8Segx4, char* msg);             /*!< @brief ��ʾ�ַ���
                                                                             @param ce8Segx4:Ce8Segx4���Զ���ָ��
                                                                             @param msg:��Ҫ��ʾ���ַ���*/

    void        (*setOff)(Ce8Segx4* ce8Segx4);                          /*!< @brief ʹģ�鴦�ڹر���ʾ״̬
                                                                             @param ce8Segx4:Ce8Segx4���Զ���ָ��*/
}Ce8Segx4Op;
/*
 *Ce8Segx4��������ʵ��
 */
extern const Ce8Segx4Op ce8Segx4Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_8SEG_X4_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_8SEG_X4_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��0.01������ʾ��ֵ
******************************************************************************
#include "Creelinks.h"
#include "Ce8Segx4.h"
fp32 i = 1.234;
Ce8Segx4 mySeg;                                 //����Ce8Segx4���Զ���
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ce8Segx4Op.initialByTg(&mySeg, R2TI2c);     //ʹ����Դ��R2TI2c��ʼ��mySeg
    ce8Segx4Op.setOn(&mySeg);                   //��ʼ��ʾ
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ce8Segx4Op.setVal(&mySeg, i);           //������Ҫ��ʾ��ֵ
        i += 0.1;
        ceSystemOp.delayMs(100);
    };
}
******************************************************************************
*/

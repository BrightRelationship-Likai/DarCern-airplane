/**
  ******************************************************************************
  * @file    Ce8Segx1.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������Ce8Segx1ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_8SEG_X1_H__
#define __CE_8SEG_X1_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_8SEG_X1_VERSION__ 1                                            /*!< �������ļ��İ汾��*/
#define __CE_8SEG_X1_NEED_CREELINKS_VERSION__ 1                             /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_8SEG_X1_NEED_CREELINKS_VERSION__)      /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�Ce8Segx1.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *Ce8Segx1���Զ���
 */
typedef struct
{
    CeTg        ceTg;                                                   /*!< ģ��ʹ�õ���Tg��Դ���Զ���*/
    uint8       showTable;                                              /*!< ��һλ����ܵ�״̬*/
}Ce8Segx1;
/*
 *Ce8Segx1��������
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(Ce8Segx1* ce8Segx1, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                             @brief Ce8Segx1ģ��ʹ������Gpio������ɳ�ʼ��
                                                                             @param ce8Segx1:Ce8Segx1���Զ���ָ��
                                                                             @param ceGpio0:Ce8Segx1ģ��ʹ�õĵ�һ��Gpio����Դ��
                                                                             @param ceGpio1:Ce8Segx1ģ��ʹ�õĵڶ���Gpio����Դ��
                                                                             @param ceGpio2:Ce8Segx1ģ��ʹ�õĵ�����Gpio����Դ��*/

    CE_STATUS   (*initialByTg)(Ce8Segx1* ce8Segx1, CE_RESOURCE ceTg );  /*!< @brief Ce8Segx1ģ��ʹ��Tg����ɳ�ʼ��
                                                                             @param ce8Segx1:Ce8Segx1���Զ���ָ��
                                                                             @param ceTg:Ce8Segx1ģ��ʹ�õ���Դ��*/

    void        (*setOn)(Ce8Segx1* ce8Segx1);                           /*!< @brief ʹģ�鴦�ڿ�����ʾ״̬
                                                                             @param ce8Segx1:ce8Segx1���Զ���ָ��*/

    void        (*setOff)(Ce8Segx1* ce8Segx1);                          /*!< @brief ʹģ�鴦�ڹر���ʾ״̬
                                                                             @param ce8Segx1:ce8Segx1���Զ���ָ��*/

    void        (*setDpOn)(Ce8Segx1* ce8Segx1);                         /*!< @brief ��ʾС����
                                                                             @param ce8Segx1:ce8Segx1���Զ���ָ��*/

    void        (*setDpOff)(Ce8Segx1* ce8Segx1);                        /*!< @brief ����С����
                                                                             @param ce8Segx1:ce8Segx1���Զ���ָ��*/

    void        (*setVal)(Ce8Segx1* ce8Segx1, uint8 val);               /*!< @brief ��ʾ��ֵ
                                                                             @param ce8Segx1:ce8Segx1���Զ���ָ��
                                                                             @param val:����ʾ����ֵ����Χ0-9��ģ����ʾ����0-9*/

    void        (*setChar)(Ce8Segx1* ce8Segx1, char val);               /*!< @brief ��ʾ�ַ�
                                                                             @param ce8Segx1:ce8Segx1���Զ���ָ��
                                                                             @param val:����ʾ���ַ����ַ�0-9���СдӢ���ַ���ֻ�в����ַ�����������ʾ��*/
}Ce8Segx1Op;
/*
 *Ce8Segx1��������ʵ��
 */
extern const Ce8Segx1Op ce8Segx1Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_8SEG_X1_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_8SEG_X1_H__


/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��1������ʾ��ֵ
******************************************************************************
#include "Creelinks.h"
#include "Ce8Segx1.h"
uint8 i=0;
Ce8Segx1 mySeg;                                 //����Ce8Segx1���Զ���
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ce8Segx1Op.initialByTg(&mySeg, R2TI2c);     //ʹ����Դ��R2TI2c��ʼ��mySeg
    ce8Segx1Op.setOn(&mySeg);                   //��ʼ��ʾ
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ce8Segx1Op.setVal(&mySeg, i);           //������Ҫ��ʾ��ֵ
        i +=1;
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

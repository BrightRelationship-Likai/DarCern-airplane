/**
  ******************************************************************************
  * @file    Ce8Segx2.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������Ce8Segx2ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2017 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_8SEG_X2_H__
#define __CE_8SEG_X2_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_8SEG_X2_VERSION__ 1                                            /*!< �������ļ��İ汾��*/
#define __CE_8SEG_X2_NEED_CREELINKS_VERSION__ 1                             /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_8SEG_X2_NEED_CREELINKS_VERSION__)      /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�Ce8Segx2.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *Ce8Segx2���Զ���
 */
typedef struct
{
    CeTg        ceTg;                                                       /*!< ģ��ʹ�õ���Tg��Դ���Զ���*/
    uint8       showTable0;                                                 /*!< ��һλ����ܵ�״̬*/
    uint8       showTable1;                                                 /*!< �ڶ�λ����ܵ�״̬*/
}Ce8Segx2;
/*
 *Ce8Segx2��������
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(Ce8Segx2* ce8Segx2, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                             @brief Ce8Segx2ģ��ʹ������Gpio������ɳ�ʼ��
                                                                             @param ce8Segx2:Ce8Segx2���Զ���ָ��
                                                                             @param ceGpio0:Ce8Segx2ģ��ʹ�õĵ�һ��Gpio����Դ��
                                                                             @param ceGpio1:Ce8Segx2ģ��ʹ�õĵڶ���Gpio����Դ��
                                                                             @param ceGpio2:Ce8Segx2ģ��ʹ�õĵ�����Gpio����Դ��*/

    CE_STATUS   (*initialByTg)(Ce8Segx2* ce8Segx2, CE_RESOURCE ceTg);   /*!< @brief Ce8Segx2ģ��ʹ��Tg����ɳ�ʼ��
                                                                             @param ce8Segx2:Ce8Segx2���Զ���ָ��
                                                                             @param ceTg:Ce8Segx2ģ��ʹ�õ���Դ��*/

    void        (*setOn)(Ce8Segx2* ce8Segx2);                           /*!< @brief ʹģ�鴦�ڿ�����ʾ״̬
                                                                             @param ce8Segx2:ce8Segx2���Զ���ָ��*/

    void        (*setOff)(Ce8Segx2* ce8Segx2);                          /*!< @brief ʹģ�鴦�ڹر���ʾ״̬
                                                                             @param ce8Segx2:ce8Segx2���Զ���ָ��*/

    void        (*setDpOn)(Ce8Segx2* ce8Segx2, uint8 index);            /*!< @brief ��ʾС����
                                                                             @param ce8Segx2:ce8Segx2���Զ���ָ��
                                                                             @param index:�ڵڼ�λ������ϲ���С���㣬��Χ0��1*/

    void        (*setDpOff)(Ce8Segx2* ce8Segx2, uint8 index);           /*!< @brief ����С����
                                                                             @param ce8Segx2:ce8Segx2���Զ���ָ��
                                                                             @param index:�ڵڼ�λ������ϲ���С���㣬��Χ0��1*/

    void        (*setVal)(Ce8Segx2* ce8Segx2, uint8 val);               /*!< @brief ��ʾ��ֵ
                                                                             @param ce8Segx2:ce8Segx2���Զ���ָ��
                                                                             @param val:����ʾ����ֵ����Χ00-99��ģ����ʾ00-99����ֵ��ʮλ��ʾ�ڵڶ��Σ���ֵ�ĸ�λ��ʾ�ڵ�һ��*/

    void        (*setChars)(Ce8Segx2* ce8Segx2, char* msg);             /*!< @brief ��ʾ�ַ�
                                                                             @param ce8Segx2:ce8Segx2���Զ���ָ��
                                                                             @param msg:����ʾ���ַ����ַ�0-9���СдӢ���ַ���ֻ�в����ַ�����������ʾ��*/
}Ce8Segx2Op;
/*
 *Ce8Segx2��������ʵ��
 */
extern const Ce8Segx2Op ce8Segx2Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_8SEG_X2_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_8SEG_X2_H__

 /**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��1������ʾ��ֵ
******************************************************************************
#include "Creelinks.h"
#include "Ce8Segx2.h"
uint8 i=0;
Ce8Segx2 mySeg;                                 //����Ce8Segx2���Զ���
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ce8Segx2Op.initialByTg(&mySeg, R2TI2c);     //ʹ����Դ��R2TI2c��ʼ��mySeg
    ce8Segx2Op.setOn(&mySeg);                   //��ʼ��ʾ
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ce8Segx2Op.setVal(&mySeg, i);           //������Ҫ��ʾ��ֵ
        i +=1;
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

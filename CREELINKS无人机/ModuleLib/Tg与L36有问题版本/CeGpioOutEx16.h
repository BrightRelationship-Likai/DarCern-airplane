/**
  ******************************************************************************
  * @file    CeGpioOutEx16.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeGpioOutEx16ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_GPIO_OUT_EX16_H__
#define __CE_GPIO_OUT_EX16_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_GPIO_OUT_EX16_VERSION__ 1                                              /*!< �������ļ��İ汾��*/
#define __CE_GPIO_OUT_EX16_NEED_CREELINKS_VERSION__ 1                               /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_GPIO_OUT_EX16_NEED_CREELINKS_VERSION__)        /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeGpioOutEx16.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

/*
 *CeGpioOutEx16���Զ���
 */
typedef struct
{
    CeTg ceTg;              /*!< CeGpioOutEx16ģ��ʹ�õ���Tg��Դ��*/
    uint16 ceGpioStatus;    /*!< CeGpioOutEx16ģ��ȫ����Gpio�ڵ�״̬*/
}CeGpioOutEx16;

/*
 *CeGpioOutEx16��������
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeGpioOutEx16* ceGpioOutEx16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                                     @brief  CeGpioOutEx16ģ��ʹ��Gpio���г�ʼ��
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16���Զ���ָ��
                                                                                     @param ceGpio0:CeGpioOutEx16ģ��ʹ�õĵ�һ��Gpio����Դ��
                                                                                     @param ceGpio1:CeGpioOutEx16ģ��ʹ�õĵڶ���Gpio����Դ��
                                                                                     @param ceGpio2:CeGpioOutEx16ģ��ʹ�õĵ�����Gpio����Դ��*/

    CE_STATUS   (*initialByTg)(CeGpioOutEx16* ceGpioOutEx16, CE_RESOURCE ceTg); /*!< @brief CeGpioOutEx16ģ���ʼ��
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16���Զ���ָ��
                                                                                     @param ceTg:CeGpioOutEx16ģ��ʹ�õ���Դ��*/

    void        (*setBit)(CeGpioOutEx16* ceGpioOutEx16, uint8 index);           /*!< @brief ����ָ��������Gpio��
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16���Զ���ָ��
                                                                                     @param index:������Gpio�ڵ���������Χ0-15*/

    void        (*resetBit)(CeGpioOutEx16* ceGpioOutEx16, uint8 index);         /*!< @brief ��λָ��������Gpio��
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16���Զ���ָ��
                                                                                     @param index:��������Gpio�ڵ���������Χ0-15*/

    void        (*setData)(CeGpioOutEx16* ceGpioOutEx16,uint16 data);           /*!< @brief ��һ��16λ��ֵ����ȫ��Gpio�ڵ�״̬���������λ��ӦGpio0��
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16���Զ���ָ��
                                                                                     @param data:ģ�����пڵĵ�ƽ���ֵ*/
}CeGpioOutEx16Op;

/*
 *CeGpioOutEx16��������ʵ��
 */
extern const CeGpioOutEx16Op ceGpioOutEx16Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_GPIO_OUT_EX16_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_GPIO_OUT_EX16_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ���ο���16��Gpio������ߵ�ƽ���ﵽ��ˮ��Ч��
******************************************************************************
#include "Creelinks.h"
#include "CeGpioOutEx16.h"
CeGpioOutEx16 myEx;
uint8 index = 0;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceGpioOutEx16Op.initialByTg(&myEx, R2TI2c); //ʹ��R2TI2c��Դ�ų�ʼ��ģ��
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceGpioOutEx16Op.setBit(&myEx, index%16);//����index%16�ڸߵ�ƽ
        ceSystemOp.delayMs(1000);
        ceGpioOutEx16Op.resetBit(&myEx,index%16);//����index%16�ڵ͵�ƽ
        index++;
    };
}
******************************************************************************
*/

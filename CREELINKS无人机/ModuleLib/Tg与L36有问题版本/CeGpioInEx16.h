/**
  ******************************************************************************
  * @file    CeGpioInEx16.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeGpioInEx16ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_GPIO_IN_EX16_H__
#define __CE_GPIO_IN_EX16_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_GPIO_IN_EX16_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_GPIO_IN_EX16_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_GPIO_IN_EX16_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeGpioInEx16.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeGpioInEx16���Զ���
 */
typedef struct
{
    CeTg ceTg;                                                                  /*!< */
}CeGpioInEx16;
/*
 *CeGpioInEx16��������
 */
typedef struct
{

    CE_STATUS   (*initialByGpio)(CeGpioInEx16* ceGpioInEx16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                                     @brief  CeGpioInEx16ģ��ʹ��Gpio���г�ʼ��
                                                                                     @param ceGpioInEx16:CeGpioInEx16���Զ���ָ��
                                                                                     @param ceGpio0:CeGpioInEx16ģ��ʹ�õĵ�һ��Gpio����Դ��
                                                                                     @param ceGpio1:CeGpioInEx16ģ��ʹ�õĵڶ���Gpio����Դ��
                                                                                     @param ceGpio2:CeGpioInEx16ģ��ʹ�õĵ�����Gpio����Դ��*/

    CE_STATUS   (*initialByTg)(CeGpioInEx16* ceGpioInEx16, CE_RESOURCE ceTg);   /*!< @brief CeGpioInEx16ģ���ʼ��
                                                                                     @param ceGpioInEx16:CeGpioInEx16���Զ���ָ��
                                                                                     @param ceTg:CeGpioInEx16ģ��ʹ�õ���Դ��*/

    uint8       (*getBit)(CeGpioInEx16* ceGpioInEx16, uint8 index);             /*!< @brief ��ȡָ��������Gpio�ڵ�ƽ
                                                                                     @param ceGpioInEx16:CeGpioInEx16���Զ���ָ��
                                                                                     @param index:������Gpio�ڵ���������Χ0-15
                                                                                     @return ����0x01:�ߵ�ƽ������0x00:�͵�ƽ*/

    uint16      (*getData)(CeGpioInEx16* ceGpioInEx16);                         /*!< @brief ��ȡȫ��IO�ڵ�״̬����λ��ӦGpio15
                                                                                     @param ceGpioInEx16:CeGpioInEx16���Զ���ָ��*/
}CeGpioInEx16Op;
/*
 *CeGpioInEx16��������ʵ��
 */
extern const CeGpioInEx16Op ceGpioInEx16Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_GPIO_IN_EX16_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_GPIO_IN_EX16_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��0��6����In���ϸ�����һ����ť�������ȡ������ť��״̬������������λ��
******************************************************************************
#include "Creelinks.h"
#include "CeGpioInEx16.h"
CeGpioInEx16 myGpioInEx16;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceGpioInEx16Op.initialByTg(&myGpioInEx16,R2TI2c);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceDebugOp.printf("In 0 status:%d \n",ceGpioInEx16Op.getBit(&myGpioInEx16,0));
        ceDebugOp.printf("In 6 status:%d \n\n",ceGpioInEx16Op.getBit(&myGpioInEx16,6));
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

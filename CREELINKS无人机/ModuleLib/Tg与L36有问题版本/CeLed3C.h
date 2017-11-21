/**
  ******************************************************************************
  * @file    CeLed3C.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeXxxZzzģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_LED_3C_H__
#define __CE_LED_3C_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_LED_3C_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_LED_3C_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_LED_3C_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeLed3C.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

#define CE_LED_3C_ALL_COLOR                                                 /*!< �������ʾ6.5K��ɫ�ʣ���򿪴˺궨��*/


#define CE_LED_3C_RED       0xF800                                          /*!< ��ɫ*/
#define CE_LED_3C_GREEN     0x07E0                                          /*!< ��ɫ*/
#define CE_LED_3C_BLUE      0x001F                                          /*!< ��ɫ*/
#define CE_LED_3C_YELLOW    0xFFE0                                          /*!< ��ɫ*/
#define CE_LED_3C_CYAN      0x051D                                          /*!< ��ɫ*/
#define CE_LED_3C_PURPLE    0xA254                                           /*!< ��ɫ*/
#define CE_LED_3C_WHITE     0xFFFF                                          /*!< ��ɫ*/

/*
 *CeLed3C���Զ���
 */
typedef struct
{
    CeTg    ceTg;                                                            /*!< ģ��ʹ�õ���Tg��Դ���Զ���*/
    uint16  led3CColor;                                                      /*!< CeLed3C��ǰ��ʾ����ɫ*/
    uint8   workMode;                                                        /*!< ģ��Ĺ���ģʽ��־*/
#ifdef CE_LED_3C_ALL_COLOR
    CePwm   cePwmRed;                                                        /*!< ģ�������ɫ�£����ƺ�ɫLed��Pwm��Դ���Զ���*/
    CePwm   cePwmGreen;                                                      /*!< ģ�������ɫ�£�������ɫLed��Pwm��Դ���Զ���*/
    CePwm   cePwmBlue;                                                       /*!< ģ�������ɫ�£�������ɫLed��Pwm��Դ���Զ���*/
#endif
}CeLed3C;

/*
 *CeLed3C��������
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeLed3C* ceLed3C,CE_RESOURCE ceGpioRed, CE_RESOURCE ceGpioGreen, CE_RESOURCE ceGpioBlue);/*!<
                                                                                  @brief CeLed3Cģ��ʹ��3��Gpio������ɳ�ʼ��
                                                                                  @param ceLed3C:CeLed3C���Զ���ָ��
                                                                                  @param ceGpioRed:CeLed3Cģ��ʹ�õĺ�ɫLED����Դ��
                                                                                  @param ceGpioGreen:CeLed3Cģ��ʹ�õ���ɫLED����Դ��
                                                                                  @param ceGpioBlue:CeLed3Cģ��ʹ�õ���ɫLED����Դ��*/
    #ifdef CE_LED_3C_ALL_COLOR
    CE_STATUS   (*initialByThreePwm)(CeLed3C* ceLed3C, CE_RESOURCE cePwmRed, CE_RESOURCE cePwmGreen, CE_RESOURCE cePwmBlue);/*!<
                                                                                  @brief CeLed3Cģ��ʹ��3��Gpio������ɳ�ʼ��
                                                                                  @param ceLed3C:CeLed3C���Զ���ָ��
                                                                                  @param cePwmRed:CeLed3Cģ��ʹ�õĺ�ɫLED����Դ��
                                                                                  @param cePwmGreen:CeLed3Cģ��ʹ�õ���ɫLED����Դ��
                                                                                  @param cePwmBlue:CeLed3Cģ��ʹ�õ���ɫLED����Դ��*/
    #endif

    CE_STATUS   (*initialByTg)(CeLed3C* ceLed3C,CE_RESOURCE ceTg);          /*!< @brief CeLed3Cģ��ʹ��Tg���г�ʼ��
                                                                                 @param ceLed3C:CeLed3C���Զ���ָ��
                                                                                 @param ceTg:CeLed3Cģ��ʹ�õ���Դ��*/

    void        (*setColor)(CeLed3C* ceLed3C, uint16 color);                /*!< @brief ����Led����ɫ,������õ�����ɫ�ʣ���򿪺궨��CE_LED_3C_ALL_COLOR,����ֻ��ʹ�ú궨��ı�׼ɫ
                                                                                 @param ceLed3C:CeLed3C���Զ���ָ��
                                                                                 @param colorStatus:�����õ���ɫ*/

    void        (*setOn)(CeLed3C* ceLed3C);                                 /*!< @brief ����Led״̬Ϊ��
                                                                                 @param ceLed3C:CeLed3C���Զ���ָ��*/

    void        (*setOff)(CeLed3C* ceLed3C);                                /*!< @brief ����Led״̬Ϊ��
                                                                                 @param ceLed3C:CeLed3C���Զ���ָ��*/
}CeLed3COp;
/*
*CeLed3C��������ʵ��
*/
extern const CeLed3COp ceLed3COp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_LED_3C_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_LED_3C_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����),����ELinkSTM���İ�
* @function ʹģ���ظ���ʾ7����ɫ
******************************************************************************
#include "Creelinks.h"
#include "CeLed3C.h"
CeLed3C myLed3C;
int main(void)
{
    ceSystemOp.initial();                               //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                          //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceLed3COp.initialByTg(&myLed3C, R2TI2c);            //ʹ��Tg�ڳ�ʼ��myLed3C����
    while (1)
    {
        ceTaskOp.mainTask();                            //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceLed3COp.setColor(&myLed3C, CE_LED_3C_RED);    //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLed3COp.setColor(&myLed3C, CE_LED_3C_GREEN);  //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLed3COp.setColor(&myLed3C, CE_LED_3C_BLUE);   //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLed3COp.setColor(&myLed3C, CE_LED_3C_YELLOW); //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLed3COp.setColor(&myLed3C, CE_LED_3C_CYAN);   //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLed3COp.setColor(&myLed3C, CE_LED_3C_PURPLE); //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLed3COp.setColor(&myLed3C, CE_LED_3C_WHITE);  //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLed3COp.setOff(&myLed3C);                     //�ر���ʾ
        ceSystemOp.delayMs(1000);                       //��ʱ1000ms
    };
}
******************************************************************************
*/

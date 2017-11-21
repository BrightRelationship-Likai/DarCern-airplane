/**
  ******************************************************************************
  * @file    CeLedH3C.h
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
#error "�����ļ�CeLedH3C.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

#define CE_LED_3C_ALL_COLOR                                                 /*!< �������ʾ6.5K��ɫ�ʣ���򿪴˺궨��*/


#define CE_LED_3C_RED       0xF800                                          /*!< ��ɫ*/
#define CE_LED_3C_GREEN     0x07E0                                          /*!< ��ɫ*/
#define CE_LED_3C_BLUE      0x001F                                          /*!< ��ɫ*/
#define CE_LED_3C_YELLOW    0xFFE0                                          /*!< ��ɫ*/
#define CE_LED_3C_CYAN      0x051D                                          /*!< ��ɫ*/
#define CE_LED_3C_PURPLE    0xA254                                          /*!< ��ɫ*/
#define CE_LED_3C_WHITE     0xFFFF                                          /*!< ��ɫ*/

/*
 *CeLedH3C���Զ���
 */
typedef struct
{
    CeTg    ceTg;                                                            /*!< ģ��ʹ�õ���Tg��Դ���Զ���*/
    uint16  led3CColor;                                                      /*!< CeLedH3C��ǰ��ʾ����ɫ*/
    uint8   workMode;                                                        /*!< ģ��Ĺ���ģʽ��־*/
#ifdef CE_LED_3C_ALL_COLOR
    CePwm   cePwmRed;                                                        /*!< ģ�������ɫ�£����ƺ�ɫLed��Pwm��Դ���Զ���*/
    CePwm   cePwmGreen;                                                      /*!< ģ�������ɫ�£�������ɫLed��Pwm��Դ���Զ���*/
    CePwm   cePwmBlue;                                                       /*!< ģ�������ɫ�£�������ɫLed��Pwm��Դ���Զ���*/
#endif
}CeLedH3C;

/*
 *CeLedH3C��������
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeLedH3C* ceLedH3C,CE_RESOURCE ceGpioRed, CE_RESOURCE ceGpioGreen, CE_RESOURCE ceGpioBlue);/*!<
                                                                                  @brief CeLedH3Cģ��ʹ��3��Gpio������ɳ�ʼ��
                                                                                  @param ceLedH3C:CeLedH3C���Զ���ָ��
                                                                                  @param ceGpioRed:CeLedH3Cģ��ʹ�õĺ�ɫLED����Դ��
                                                                                  @param ceGpioGreen:CeLedH3Cģ��ʹ�õ���ɫLED����Դ��
                                                                                  @param ceGpioBlue:CeLedH3Cģ��ʹ�õ���ɫLED����Դ��*/
#ifdef CE_LED_3C_ALL_COLOR
    CE_STATUS   (*initialByThreePwm)(CeLedH3C* ceLedH3C, CE_RESOURCE cePwmRed, CE_RESOURCE cePwmGreen, CE_RESOURCE cePwmBlue);/*!<
                                                                                  @brief CeLedH3Cģ��ʹ��3��Gpio������ɳ�ʼ��
                                                                                  @param ceLedH3C:CeLedH3C���Զ���ָ��
                                                                                  @param cePwmRed:CeLedH3Cģ��ʹ�õĺ�ɫLED����Դ��
                                                                                  @param cePwmGreen:CeLedH3Cģ��ʹ�õ���ɫLED����Դ��
                                                                                  @param cePwmBlue:CeLedH3Cģ��ʹ�õ���ɫLED����Դ��*/
#endif

    CE_STATUS   (*initialByTg)(CeLedH3C* ceLedH3C,CE_RESOURCE ceTg);         /*!< @brief CeLedH3Cģ��ʹ��Tg���г�ʼ��
                                                                                  @param ceLedH3C:CeLedH3C���Զ���ָ��
                                                                                  @param ceTg:CeLedH3Cģ��ʹ�õ���Դ��*/

    void        (*setColor)(CeLedH3C* ceLedH3C, uint16 color);               /*!< @brief ����Led����ɫ,������õ�����ɫ�ʣ���򿪺궨��CE_LED_3C_ALL_COLOR,����ֻ��ʹ�ú궨��ı�׼ɫ
                                                                                  @param ceLedH3C:CeLedH3C���Զ���ָ��
                                                                                  @param colorStatus:�����õ���ɫ*/

    void        (*setOn)(CeLedH3C* ceLedH3C);                                /*!< @brief ����Led״̬Ϊ��
                                                                                  @param ceLedH3C:CeLedH3C���Զ���ָ��*/

    void        (*setOff)(CeLedH3C* ceLedH3C);                               /*!< @brief ����Led״̬Ϊ��
                                                                                  @param ceLedH3C:CeLedH3C���Զ���ָ��*/
}CeLedH3COp;
/*
*CeLedH3C��������ʵ��
*/
extern const CeLedH3COp ceLedH3COp;

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
#include "CeLedH3C.h"
CeLedH3C myLedH3C;
int main(void)
{
    ceSystemOp.initial();                               //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                          //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceLedH3COp.initialByTg(&myLedH3C, R2TI2c);          //ʹ��Tg�ڳ�ʼ��myLedH3C����
    while (1)
    {
        ceTaskOp.mainTask();                            //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_RED);    //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_GREEN);  //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_BLUE);   //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_YELLOW); //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_CYAN);   //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_PURPLE); //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_WHITE);  //��ʾ��ɫ
        ceSystemOp.delayMs(200);                        //��ʱ200ms
        ceLedH3COp.setOff(&myLedH3C);                     //�ر���ʾ
        ceSystemOp.delayMs(1000);                       //��ʱ1000ms
    };
}
******************************************************************************
*/

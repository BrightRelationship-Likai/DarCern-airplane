/**
  ******************************************************************************
  * @file    CeBtnTouch.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBtnTouchģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BTN_TOUCH_H__
#define __CE_BTN_TOUCH_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BTN_TOUCH_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_BTN_TOUCH_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_BTN_TOUCH_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeBtnTouch.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

#define CE_BTN_TOUCH_OUT_TIME_MS   120                      /*!< �ȴ�����������߰��µĳ�ʱʱ�䣬��ֹ��ѭ��*/
/*
 *CeBtnTouch���Զ���
*/
typedef struct
{
    CeInt       ceInt;                                      /*!< �ж���Դ���Զ���*/
    CeGpio      ceGpio;                                     /*!< Gpio��Դ���Զ���*/
    CeTicker    ceTicker;                                   /*!< �δ���붨ʱ�����Զ���*/
    uint8       status;                                     /*!< ��ť��ǰ״̬*/
    void(*callBackPressEvent)(void);                        /*!< �����¼��ص�����*/
}CeBtnTouch;

/*
 *CeBtnTouch��������
*/
typedef struct
{
    CE_STATUS(*initialByGpio)(CeBtnTouch* ceBtnTouch, CE_RESOURCE ceGpio, void(*callBackPressEvent)(void));/*!<
                                                                 @brief CeBtnTouchģ��ʹ��Gpio���г�ʼ��
                                                                 @param CeBtnTouch:CeBtnTouch���Զ���ָ��
                                                                 @param ceGpio:CeBtnTouchģ��ʹ�õ�Gpio����Դ��
                                                                 @param callBackPressEvent:��������ʱ�Ļص�����*/

    CE_STATUS(*initialByInt)(CeBtnTouch* ceBtnTouch, CE_RESOURCE ceInt, void(*callBackPressEvent)(void));/*!<
                                                                 @brief CeBtnTouchģ��ʹ��Int���г�ʼ��
                                                                 @param CeBtnTouch:CeBtnTouch���Զ���ָ��
                                                                 @param ceInt:CeBtnTouchģ��ʹ�õ���Դ��
                                                                 @param callBackPressEvent:��������ʱ�Ļص�����*/

    uint8(*getGpioStatus)(CeBtnTouch* ceBtnTouch);          /*!< @brief ��ȡCeBtnTouch��Ӧ��GPIO�ڵ�״̬��0x01��0x00
                                                                 @param ceBtnTouch:CeBtnTouch���Զ���ָ��*/

    void(*waitForPressDown)(CeBtnTouch* ceBtnTouch);        /*!< @brief �ȴ��������£���ʱʱ��ΪCE_BTN_TOUCH_OUT_TIME_MS
                                                                 @param ceBtnTouch:CeBtnTouch���Զ���ָ��*/

    void(*waitForPressUp)(CeBtnTouch* ceBtnTouch);          /*!< @brief �ȴ��������𣬳�ʱʱ��ΪCE_BTN_TOUCH_OUT_TIME_MS
                                                                 @param ceBtnTouch:CeBtnTouch���Զ���ָ��*/

}CeBtnTouchOp;

/*
*CeBtnTouch��������ʵ��
*/
extern CeBtnTouchOp ceBtnTouchOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_BTN_TOUCH_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_BTN_TOUCH_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ÿ��⵽��ģ�¼��󣬵��ڻص��з�����Ϣ����λ��
******************************************************************************
#include "Creelinks.h"
#include "CeBtnTouch.h"
CeBtnTouch myBtnTouch;                                 //����CeBtnTouch���Զ���
void callBackPress(void)
{
    ceDebugOp.printf("Enter callBackPress event!\n"); //����ص�����ӡ��Ϣ
}
int main(void)
{
    ceSystemOp.initial();                              //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                         //ͨ��Uart�������Debug��Ϣ����λ��
                                                       //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceBtnTouchOp.initialByGpio(&myBtnTouch, R1AGP, callBackPress);
    while (1)
    {
        ceTaskOp.mainTask();                           //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
                                                       //TODO:���ڴ˴������û���
    };
}
******************************************************************************
*/

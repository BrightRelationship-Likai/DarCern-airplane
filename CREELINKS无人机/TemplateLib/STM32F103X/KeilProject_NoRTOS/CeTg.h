/**
  ******************************************************************************
  * @file    CeTg.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2016-08-05
  * @brief   Creelinksƽ̨ CeTg(Three Gpio)��ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TG_H__
#define __CE_TG_H__

#include "CeMcu.h"

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplu

#ifdef __CE_USE_TG__

/**
  * @brief  �ṹ�壬Tg����������Լ���
  */
typedef struct
{
    CE_RESOURCE ceResource;                     /*!< Tg��Ӧ����Դ��*/
    CE_RESOURCE ceResource0;                    /*!< Tg�ĵ�һ��Gpio�ڶ�Ӧ����Դ��*/
    CE_RESOURCE ceResource1;                    /*!< Tg�ĵڶ���Gpio�ڶ�Ӧ����Դ��*/
    CE_RESOURCE ceResource2;                    /*!< Tg�ĵ�����Gpio�ڶ�Ӧ����Դ��*/

    CeExTgPar   ceExTgPar;                      /*!< �봦����ƽ̨��صĶ�������ṹ�壬������ߴ���Ч�ʣ��û������ע*/
} CeTg;
/**
  * @brief  �ṹ�壬Tg������ò�������
  */
typedef struct
{
    CE_STATUS   (*initial)(CeTg* ceTg, CE_GPIO_MODE ceGpioMode0, CE_GPIO_MODE ceGpioMode1, CE_GPIO_MODE ceGpioMode2);/*!<
                                                     @brief ��ʼ��һ��Tg��Դ
                                                     @param ceTg:Tg���Զ���ָ��
                                                     @param ceGpioMode0:Tg��һ��Gpio�ڵĹ�����ʽ
                                                     @param ceGpioMode1:Tg�ڶ���Gpio�ڵĹ�����ʽ
                                                     @param ceGpioMode2:Tg������Gpio�ڵĹ�����ʽ*/

    void        (*setGpio0)(CeTg* ceTg);        /*!< @brief ����Tg��һ��GPIO��ֵΪ1
                                                     @param ceTg:Tg���Զ���ָ��*/

    void        (*resetGpio0)(CeTg* ceTg);      /*!< @brief ����Tg��һ��GPIO��ֵΪ0
                                                     @param ceTg:Tg���Զ���ָ��*/

    uint8       (*getGpio0Bit)(CeTg* ceTg);     /*!< @brief ��ȡTg��Դ��һ��GPIO�ڵ�ֵ
                                                     @param ceTg:Tg���Զ���ָ��
                                                     @return Tg��Դ��һ��Gpio�ڵĵ�ƽ*/

    void        (*setGpio0Mode)(CeTg* ceTg,  CE_GPIO_MODE ceGpioMode);/*!<
                                                     @brief ����Tg��һ��GPIO�Ĺ���ģʽ
                                                     @param ceTg:Tg���Զ���ָ��
                                                     @param ceGpioMode:Gpio�Ĺ�����ʽ*/

    void        (*setGpio1)(CeTg* ceTg);        /*!< @brief ����Tg�ڶ���GPIO��ֵΪ1
                                                     @param ceTg:Tg���Զ���ָ��*/

    void        (*resetGpio1)(CeTg* ceTg);      /*!< @brief ����Tg�ڶ���GPIO��ֵΪ0
                                                     @param ceTg:Tg���Զ���ָ��*/

    uint8       (*getGpio1Bit)(CeTg* ceTg);     /*!< @brief ��ȡTg��Դ�ڶ���GPIO�ڵ�ֵ
                                                     @param ceTg:Tg���Զ���ָ��*/

    void        (*setGpio1Mode)(CeTg* ceTg,  CE_GPIO_MODE ceGpioMode);/*!<
                                                     @brief ����Tg�ڶ���GPIO�Ĺ���ģʽ
                                                     @param ceTg:Tg���Զ���ָ��
                                                     @param ceGpioMode:Gpio�Ĺ�����ʽ*/

    void        (*setGpio2)(CeTg* ceTg);        /*!< @brief ����Tg������GPIO��ֵΪ1
                                                     @param ceTg:Tg���Զ���ָ��*/

    void        (*resetGpio2)(CeTg* ceTg);      /*!< @brief ����Tg������GPIO��ֵΪ0
                                                     @param ceTg:Tg���Զ���ָ��*/

    uint8       (*getGpio2Bit)(CeTg* ceTg);     /*!< @brief ��ȡTg��Դ������GPIO�ڵ�ֵ
                                                     @param ceTg:Tg���Զ���ָ��*/

    void        (*setGpio2Mode)(CeTg* ceTg,  CE_GPIO_MODE ceGpioMode);/*!<
                                                     @brief ����Tg������GPIO�Ĺ���ģʽ
                                                     @param ceTg:Tg���Զ���ָ��
                                                     @param ceGpioMode:Gpio�Ĺ�����ʽ*/
} CeTgOp;
extern const CeTgOp ceTgOp;                 /*!< ������Tg��صĲ���*/

#endif //__CE_USE_TG__

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TG_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����)
* @function ����Tg������Gpio�ڣ���˳��ÿ500ms�л�һ�ε�ƽ״̬
******************************************************************************

#include "Creelinks.h"
CeTg myTg;                                      //����Tg���Զ���
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(Uartx);                        //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    myTg.ceResource = RxT;                      //ָ��Tgʹ�õ���Դ��
    //myTg.ceResource0 = RxG;                   //�ڶ���ȷ��Tgʹ�õ���Դ�ŷ�������ʹ������Gpio��Դ
    //myTg.ceResource1 = RxG;                   //�ڶ���ȷ��Tgʹ�õ���Դ�ŷ�������ʹ������Gpio��Դ
    //myTg.ceResource2 = RxG;                   //�ڶ���ȷ��Tgʹ�õ���Դ�ŷ�������ʹ������Gpio��Դ
    ceTgOp.initial(&myTg, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);//��ʼ��Tg�ڣ���ָ�������ڵĹ���ģʽ
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ��
        //TODO:���ڴ˴������û�����
        ceGpioOp.setBit(&myTg);                 //����Tg�ĵ�һ��IO��Ϊ�ߵ�ƽ
        ceSystemOp.delayMs(500);                //��ʱ500ms
        ceGpioOp.resetBit(&myTg);               //����Tg�ĵ�һ��IO��Ϊ�͵�ƽ

        ceGpioOp.setBit(&myTg);                 //����Tg�ĵڶ���IO��Ϊ�ߵ�ƽ
        ceSystemOp.delayMs(500);                //��ʱ500ms
        ceGpioOp.resetBit(&myTg);               //����Tg�ĵڶ���IO��Ϊ�͵�ƽ

        ceGpioOp.setBit(&myTg);                 //����Tg�ĵ�����IO��Ϊ�ߵ�ƽ
        ceSystemOp.delayMs(500);                //��ʱ500ms
        ceGpioOp.resetBit(&myTg);               //����Tg�ĵ�����IO��Ϊ�͵�ƽ
    };
}
******************************************************************************
*/

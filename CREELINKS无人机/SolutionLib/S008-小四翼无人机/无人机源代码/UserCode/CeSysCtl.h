/**
  ******************************************************************************
  * @file    CeSysCtl.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSysCtlģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_SYS_CTL_H__
#define __CE_SYS_CTL_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "creelinks.h"
/*
 *ö�٣������ĸ�LED����˸��ʽ
 */
typedef enum 
{
    CE_LED_CTL_MODE_OFF = 0x00,             /*!< ����LED������״̬*/
    CE_LED_CTL_MODE_IN_CFG,                 /*!< ���ڳ�ʼ������������״̬*/
    CE_LED_CTL_MODE_IN_NORMAL,              /*!< ��������״̬*/
    CE_LED_CTL_MODE_IN_ERROR,               /*!< ����״̬*/
    CE_LED_CTL_MODE_FLASH_CYCLE_P,          /*!< ƫ����*/
    CE_LED_CTL_MODE_FLASH_CYCLE_N,          /*!< ƫ����*/
    CE_LED_CTL_MODE_GOTO_FRONT,             /*!< ��*/
    CE_LED_CTL_MODE_GOTO_BACK,              /*!< ��*/
    CE_LED_CTL_MODE_GOTO_LEFT,              /*!< �󷭹�*/
    CE_LED_CTL_MODE_GOTO_RIGHT,             /*!< �ҷ���*/
}CE_LED_CTL_MODE;

/*
 *CeSysCtl��������
 */
typedef struct
{
    void        (*initial)(void);               /*!< @brief  ϵͳ���ƺ�����ʼ��*/

    fp32        (*getBatVol)(void);             /*!< @brief  ��ȡ﮵�ص�ѹ
                                                     @return ��ǰ﮵�صĵ�ѹֵ����λV*/

    void        (*setAlarm)(uint16 sayMs,uint16 sleepMs, uint8 sayTimes); /*!< 
                                                     @brief  ���÷���װ�õķ�����ʽ��������һ�����ڵķ���ʱ����ֹͣ����Ϣʱ�䣬�����ڴ�����ʹ������...��...��
                                                     @param  sayMs:����ʱ�䳤�ȣ���λMs
                                                     @param  sleepMs:ֹͣ����ʱ�䳤�ȣ���λMs
                                                     @param  sayTimes:��������*/

    uint8       (*getBtnSta)(uint8 btnIndex);   /*!< @brief  ��ȡ���ð�ť״̬
                                                     @param  btnIndex:��ť����
                                                     @return 0:��ʾδ���£�1:��ʾ�Ѱ���*/

    fp32        (*getSysRunCycleS)(void);       /*!< @brief  ���ö�ʱ����������ʽ��ͳ�����ε��ô˺�����ʱ��������λ��
                                                     @return ���ε��ô˺�����ʱ��������λ��*/

    uint8       (*checkConnectStatus)(void);    /*!< @brief ����Ƿ�ͨѶ�ж�
                                                     @return 1��ͨѶ������ 0��ͨѶ�ж�*/

    void        (*setLedMode)(CE_LED_CTL_MODE ctlMode);/*!< 
                                                     @brief �����ĸ�LED��˸�ķ�ʽ
                                                     @param ctlMode:�ĸ�LED��˸�ķ�ʽ*/

    CE_LED_CTL_MODE (*getLedMode)(void);        /*!< @brief ��ȡ��ǰ�ĸ�LED��˸�ķ�ʽ
                                                     @return ��ǰ�ĸ�LED��˸�ķ�ʽ*/

   // void        (*delayMs)(uint32 ms);

}CeSysCtlOp;
/*
 *CeSysCtl��������ʵ��
 */
extern const CeSysCtlOp ceSysCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SYS_CTL_H__

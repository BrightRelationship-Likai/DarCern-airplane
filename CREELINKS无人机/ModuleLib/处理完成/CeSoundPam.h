/**
  ******************************************************************************
  * @file    CeSoundPam.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSoundPamģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_CE_SOUND_PAM_H__
#define __CE_CE_SOUND_PAM_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_CE_SOUND_PAM_VERSION__ 1                                               /*!< �������ļ��İ汾��*/
#define __CE_CE_SOUND_PAM_NEED_CREELINKS_VERSION__ 1                                /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_CE_SOUND_PAM_NEED_CREELINKS_VERSION__)         /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeSoundPam.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

#define L1      (1000000/262)                                                       /*!< ���� ����1 ������*/
#define L1U     (1000000/277)                                                       /*!< ���� ����#1 ������*/
#define L2      (1000000/294)                                                       /*!< ���� ����2 ������*/
#define L2U     (1000000/311)                                                       /*!< ���� ����#2 ������*/
#define L3      (1000000/330)                                                       /*!< ���� ����3 ������*/
#define L4      (1000000/349)                                                       /*!< ���� ����4 ������*/
#define L4U     (1000000/370)                                                       /*!< ���� ����#4 ������*/
#define L5      (1000000/392)                                                       /*!< ���� ����5 ������*/
#define L5U     (1000000/415)                                                       /*!< ���� ����#5 ������*/
#define L6      (1000000/440)                                                       /*!< ���� ����6 ������*/
#define L6U     (1000000/466)                                                       /*!< ���� ����#6 ������*/
#define L7      (1000000/494)                                                       /*!< ���� ����7 ������*/
#define M1      (1000000/523)                                                       /*!< ���� ����1 ������*/
#define M1U     (1000000/554)                                                       /*!< ���� ����#1 ������*/
#define M2      (1000000/587)                                                       /*!< ���� ����2 ������*/
#define M2U     (1000000/622)                                                       /*!< ���� ����#2 ������*/
#define M3      (1000000/659)                                                       /*!< ���� ����3 ������*/
#define M4      (1000000/698)                                                       /*!< ���� ����4 ������*/
#define M4U     (1000000/740)                                                       /*!< ���� ����#4 ������*/
#define M5      (1000000/784)                                                       /*!< ���� ����5 ������*/
#define M5U     (1000000/831)                                                       /*!< ���� ����#5 ������*/
#define M6      (1000000/880)                                                       /*!< ���� ����6 ������*/
#define M6U     (1000000/932)                                                       /*!< ���� ����#6 ������*/
#define M7      (1000000/988)                                                       /*!< ���� ����7 ������*/
#define H1      (1000000/1046)                                                      /*!< ���� ����1 ������*/
#define H1U     (1000000/1109)                                                      /*!< ���� ����#1 ������*/
#define H2      (1000000/1175)                                                      /*!< ���� ����2 ������*/
#define H2U     (1000000/1245)                                                      /*!< ���� ����#2 ������*/
#define H3      (1000000/1318)                                                      /*!< ���� ����3 ������*/
#define H4      (1000000/1397)                                                      /*!< ���� ����4 ������*/
#define H4U     (1000000/1480)                                                      /*!< ���� ����#4 ������*/
#define H5      (1000000/1568)                                                      /*!< ���� ����5 ������*/
#define H5U     (1000000/1661)                                                      /*!< ���� ����#5 ������*/
#define H6      (1000000/1760)                                                      /*!< ���� ����6 ������*/
#define H6U     (1000000/1865)                                                      /*!< ���� ����#6 ������*/
#define H7      (1000000/1976)                                                      /*!< ���� ����7 ������*/

typedef enum
{
    CE_SOUND_PAM_CH_L,
    CE_SOUND_PAM_CH_R,
    CE_SOUND_PAM_CH_L_AND_R,
}CE_SOUND_PAM_CH;

/*
 *CeSoundPam���Զ���
 */
typedef struct
{
    CeDa ceDaL;                             /*!< ģ����ͨ��ʹ�õ���Da��Դ*/
    uint8 workModeL;                        /*!< ģ����ͨ���Ĺ�����ʽ��0:δ������1���̶�Ƶ�ʣ�2�����ַ���*/
    void(*startFinishCallBackL)(void);      /*!< ���ģ����ͨ��������ɺ�ִ�еĻص�*/

    CeDa ceDaR;                             /*!< ģ����ͨ��ʹ�õ���Da��Դ*/
    uint8 workModeR;                        /*!< ģ����ͨ���Ĺ�����ʽ��0:δ������1���̶�Ƶ�ʣ�2�����ַ���*/
    void(*startFinishCallBackR)(void);      /*!< ���ģ����ͨ��������ɺ�ִ�еĻص�*/
}CeSoundPam;
/*
 *CeSoundPam��������
 */
typedef struct
{
     CE_STATUS   (*initial)(CeSoundPam* ceSoundPam, CE_RESOURCE ceDaL, CE_RESOURCE ceDaR);                      /*!< @brief  CeSoundPamģ���ʼ��
                                                                                                                     @param  ceSoundPam:CeSoundPam���Զ���ָ��
                                                                                                                     @param  ceDa:CeSoundPamģ��ʹ�õ���Դ��*/

     void        (*start)(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR, uint16* dataBuf, uint16 dataBufSize, uint32 intervalNs, void(*startFinishCallBack)(void));/*!<
                                                                                                                     @brief  ʹģ�鰴�ո������������м�������֮���ʱ������������ͨ������Mp3�����ֲ���
                                                                                                                     @param  ceSoundPam:CeSoundPam���Զ���ָ��
                                                                                                                     @param  chLorR:����������������
                                                                                                                     @param  dataBuf:���ݻ��棬�������DA��ת����ȱ�����ͬ
                                                                                                                     @param  dataBufSize:���ݻ���Ĵ�С
                                                                                                                     @param  intervalNs:������֮���ʱ����
                                                                                                                     @param  startFinishCallBack:������ɺ�Ļص�*/

    void        (*startFixFrequencySound)(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR, uint32 fixFreHz);     /*!< @brief  �Թ̶�Ƶ�ʷ�������,�첽����������������ɺ�ֱ�ӷ���
                                                                                                                     @param  ceSoundPam:CeSoundPam���Զ���ָ��
                                                                                                                     @param  chLorR:����������������
                                                                                                                     @param  fixFreHz:������Ƶ��*/

    void        (*stopFixFrequencySound)(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR);                       /*!< @brief  ֹͣ�Թ̶�Ƶ�ʷ�������,�첽����������������ɺ�ֱ�ӷ���
                                                                                                                     @param  ceSoundPam:CeSoundPam���Զ���ָ��
                                                                                                                     @param  chLorR:����������������*/
}CeSoundPamOp;
/*
 *CeSoundPam��������ʵ��
 */
extern const CeSoundPamOp ceSoundPamOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_CE_SOUND_PAM_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_CE_SOUND_PAM_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ʹ��ģ��ģ�⾯����
******************************************************************************
#include "Creelinks.h"
#include "CeSoundPam.h"
CeSoundPam mySoundPam;
uint32 i;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceSoundPamOp.initial(&mySoundPam,R6ADIG,R8ADIG);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        for(i=650;i<=750;i+=1)                  //�Ե�Ƶ650Hz����Ƶ750Hz������ʱ��0.23s
        {
            ceSoundPamOp.startFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R,i);
            ceSystemOp.delayMs(2);
            ceSoundPamOp.stopFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R);
        }

        for(i=1450;i<=1550;i+=2)                 //�Ե�Ƶ1450Hz����Ƶ1550Hz������ʱ��0.1s
        {
            ceSoundPamOp.startFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R,i);
            ceSystemOp.delayMs(2);
            ceSoundPamOp.stopFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R);
        }

        for(i=1550;i>=1450;i-=2)                 //�Ը�Ƶ1550Hz����Ƶ1450Hz������ʱ��0.1s
        {
            ceSoundPamOp.startFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R,i);
            ceSystemOp.delayMs(2);
            ceSoundPamOp.stopFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R);
        }

        for(i=750;i>=650;i-=1)                  //�Ը�Ƶ750Hz����Ƶ650Hz������ʱ��0.23s
        {
            ceSoundPamOp.startFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R,i);
            ceSystemOp.delayMs(2);
            ceSoundPamOp.stopFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R);
        }
    };
}
******************************************************************************
*/

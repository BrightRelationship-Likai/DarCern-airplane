/**
  ******************************************************************************
  * @file    CeSoundDetS.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSoundDetSģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)Adת�������У�����ʱ�����ģ��������ɼ���֮������ʱ����û��趨��ʱ���Դ�
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_SOUND_DET_S_H__
#define __CE_SOUND_DET_S_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_SOUND_DET_S_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_SOUND_DET_S_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_SOUND_DET_S_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeSoundDetS.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeSoundDetS���Զ���
 */
typedef struct
{
    CeAd    ceAd;                                                       /*!< ģ��ʹ�õ���Ad��Դ*/
}CeSoundDetS;
/*
 *CeSoundDetS��������
 */
typedef struct
{
    CE_STATUS (*initial)(CeSoundDetS* ceSoundDetS, CE_RESOURCE ceAd);    /*!< @brief  CeSoundDetSģ���ʼ��
                                                                              @param  ceSoundDetS:CeSoundDetS���Զ���ָ��
                                                                              @param  ceAd:CeSoundDetSģ��ʹ�õ�Ad��Դ��*/

    uint16  (*startRecord)(CeSoundDetS* ceSoundDetS, uint16* dataBuf, uint16 dataBuffSize, uint32 intervalUs);/*!<
                                                                              @brief  ��ʼ¼����������ѭ�����浽¼�������˳�
                                                                              @param  dataBuf:¼�Ƶ����ݻ�����
                                                                              @param  dataBufSize:¼�Ƶ����ݻ�������С
                                                                              @param  intervalNs:����������֮���ʱ����*/

    uint32  (*getConvertResult)(CeSoundDetS* ceSoundDetS);               /*!< @brief  ����һ��ת���ɼ���ͨ�������������
                                                                              @param  ceSoundDetS:CeSoundDetS���Զ���ָ��
                                                                              @return ��ǰ����ֵ������Ϊ0�� MICͷ����ʱΪCE_AD_CONVERT_MAX_VAL*/

}CeSoundDetSOp;
/*
 *CeSoundDetS��������ʵ��
 */
extern const CeSoundDetSOp ceSoundDetSOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_SOUND_DET_S_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SOUND_DET_S_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��⻷������ֵ�����������λ��
******************************************************************************
#include "Creelinks.h"
#include "CeSoundDetS.h"
CeSoundDetS mySoundDetS;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceSoundDetSOp.initial(&mySoundDetS,R1AGP);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceDebugOp.printf("Sound Val:%d\n",ceSoundDetSOp.getConvertResult(&mySoundDetS));
        ceSystemOp.delayMs(10);
    };
}
******************************************************************************
*/

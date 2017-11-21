/**
  ******************************************************************************
  * @file    CeSoundDet.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSoundDetģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)Adת�������У�����ʱ�����ģ��������ɼ���֮������ʱ����û��趨��ʱ���Դ�
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_SOUND_DET_H__
#define __CE_SOUND_DET_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_SOUND_DET_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_SOUND_DET_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_SOUND_DET_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeSoundDet.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
*CeSoundDet���Զ���
*/
typedef struct
{
    CeAd    ceAd;                                                   /*!< ģ��ʹ�õ���Ad��Դ*/
    CeInt   ceInt;                                                  /*!< ģ��ʹ�õ���Int��Դ*/
    void    (*callBack)(void);                                      /*!< ��ŵ����ⲿ��������ʱ���ⲿ�ж�Intִ�еĻص�����*/
}CeSoundDet;

/*
 *CeSoundDet��������
*/
typedef struct
{
    CE_STATUS   (*initial)(CeSoundDet* ceSoundDet, CE_RESOURCE ceAd, CE_RESOURCE ceInt, void (*callback)(void));/*!<
                                                                         @brief  CeSoundDetģ���ʼ��
                                                                         @param  ceSoundDet:CeSoundDet���Զ���ָ��
                                                                         @param  ceAd:CeSoundDetģ��ʹ�õ�Ad��Դ��
                                                                         @param  ceInt:CeSoundDetģ��ʹ�õ�Int��Դ��
                                                                         @param  callBack:���ⲿ��������ʱ���ⲿ�ж�Intִ�еĻص�����*/

    uint16      (*startRecord)(CeSoundDet* ceSoundDet, uint16* dataBuf, uint16 dataBuffSize, uint32 intervalUs);/*!<
                                                                         @brief  ��ʼ¼����������ѭ�����浽¼�������˳�
                                                                         @param  dataBuf:¼�Ƶ����ݻ�����
                                                                         @param  dataBufSize:¼�Ƶ����ݻ�������С
                                                                         @param  intervalNs:����������֮���ʱ����*/

    uint32      (*getConvertResult)(CeSoundDet* ceSoundDet);        /*!< @brief  ����һ��ת���ɼ���ͨ�������������
                                                                         @param  ceSoundDets:CeSoundDets���Զ���ָ��
                                                                         @return ��ǰ����ֵ������Ϊ0��MICͷ����ʱΪCE_AD_CONVERT_MAX_VAL*/
}CeSoundDetOp;

/*
 *CeSoundDet��������ʵ��
*/
extern const CeSoundDetOp ceSoundDetOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_SOUND_DET_S_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_SOUND_DET_S_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function �����ⲿ��������ʱ�������жϲ�������Ϣ����λ����
******************************************************************************
#include "Creelinks.h"
#include "CeSoundDet.h"
CeSoundDet mySoundDet;

void callBackNoise()        //���յ��ⲿ�����󴥷����жϻص�
{
    ceDebugOp.printf("Cacth Int.\n");
}

int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceSoundDetOp.initial(&mySoundDet,R1AGP,R6ADIG,callBackNoise);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
    };
}
******************************************************************************
*/

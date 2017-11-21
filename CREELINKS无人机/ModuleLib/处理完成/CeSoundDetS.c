/**
  ******************************************************************************
  * @file    CeSoundDetS.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSoundDetSģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)44100hz 16bit 22675Ns
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeSoundDetS.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeSoundDetSģ���ʼ��
  * @param  ceSoundDetS:CeSoundDetS���Զ���
  * @param  ceAd:CeSoundDetSģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceSoundDetS_initial(CeSoundDetS* ceSoundDetS, CE_RESOURCE ceAd)
{
    ceSoundDetS->ceAd.ceResource = ceAd;
    ceAdOp.initial(&(ceSoundDetS->ceAd));
     return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ʼ¼������
  * @param  dataBuf:¼�Ƶ����ݻ�����
  * @param  dataBufSize:¼�Ƶ����ݻ�������С
  * @param  intervalNs:����������֮���ʱ����
  */
uint16  ceSoundDetS_startRecord(CeSoundDetS* ceSoundDetS, uint16* dataBuf, uint16 dataBuffSize, uint32 intervalUs)
{
    uint16 i = 0x0000;
    if(intervalUs >= 3)
    {
        intervalUs -= 2;
    }
    for(i = 0; i < dataBuffSize; i++)
    {
        dataBuf[i] = (uint16)ceAdOp.getConvertValue(&(ceSoundDetS->ceAd));
        ceSystemOp.delayUs(intervalUs);
    }
    return i;
}

/**
  * @brief  ����һ��ת���ɼ���ͨ�������������
  * @param  ceSoundDetS:CeSoundDetS���Զ���ָ��
  * @return ��ǰ����ֵ������Ϊ0�� MICͷ����ʱΪCE_AD_CONVERT_MAX_VAL
  */
uint32  ceSoundDetS_getConvertResult(CeSoundDetS* ceSoundDetS)
{
    return ceAdOp.getConvertValue(&(ceSoundDetS->ceAd));
}

const CeSoundDetSOp ceSoundDetSOp = {ceSoundDetS_initial, ceSoundDetS_startRecord, ceSoundDetS_getConvertResult};

#ifdef __cplusplus
 }
#endif //__cplusplus

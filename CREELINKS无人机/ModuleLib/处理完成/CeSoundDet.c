/**
  ******************************************************************************
  * @file    CeSoundDet.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSoundDetģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)44100hz 16bit 22675Ns
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeSoundDet.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeSoundDet�ⲿ�ж�Int�Ļص�����
  * @param  pAddPar:CeSoundDet���Զ���ָ��
  * @return ϵͳ״̬��
  */
void callBackInt(void* pAddPar)
{
    if(((CeSoundDet*)(pAddPar))->callBack != CE_NULL)
    {
        ((CeSoundDet*)(pAddPar))->callBack();
    }
}

/**
  * @brief  CeSoundDetģ���ʼ��
  * @param  ceSoundDet:CeSoundDet���Զ���
  * @param  ceAd:CeSoundDetģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceSoundDet_initial(CeSoundDet* ceSoundDet, CE_RESOURCE ceAd, CE_RESOURCE ceInt,void (*callback)(void))
{
    ceSoundDet->callBack = callback;

    ceSoundDet->ceAd.ceResource = ceAd;
    ceAdOp.initial(&(ceSoundDet->ceAd));

    ceSoundDet->ceInt.ceResource = ceInt;
    ceSoundDet->ceInt.callBack = callBackInt;
    ceSoundDet->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_FALLING;
    ceSoundDet->ceInt.pAddPar = ceSoundDet;
    ceIntOp.initial(&(ceSoundDet->ceInt));
    ceIntOp.start(&(ceSoundDet->ceInt));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ʼ¼������
  * @param  ceSoundDet:CeSoundDet���Զ���
  * @param  dataBuf:¼�Ƶ����ݻ�����
  * @param  dataBufSize:¼�Ƶ����ݻ�������С
  * @param  intervalNs:����������֮���ʱ����
  */
uint16  ceSoundDet_startRecord(CeSoundDet* ceSoundDet, uint16* dataBuf, uint16 dataBuffSize, uint32 intervalUs)
{
    uint16 i = 0x0000;
    if (intervalUs >= 3)
    {
        intervalUs -= 2;
    }
    for (i = 0; i < dataBuffSize; i++)
    {
        dataBuf[i] = (uint16)ceAdOp.getConvertValue(&(ceSoundDet->ceAd));
        ceSystemOp.delayUs(intervalUs);
    }
    return i;
}

/**
  * @brief  ����һ��ת���ɼ���ͨ�������������
  * @param  ceSoundDet:CeSoundDet���Զ���
  * @return ��ǰ����ֵ������Ϊ0�� MICͷ����ʱΪCE_AD_CONVERT_MAX_VAL
  */
uint32  ceSoundDet_getConvertResult(CeSoundDet* ceSoundDet)
{
    return ceAdOp.getConvertValue(&(ceSoundDet->ceAd));
}

const CeSoundDetOp ceSoundDetOp = {ceSoundDet_initial, ceSoundDet_startRecord, ceSoundDet_getConvertResult};

#ifdef __cplusplus
}
#endif //__cplusplus

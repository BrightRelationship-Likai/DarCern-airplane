/**
  ******************************************************************************
  * @file    CeSoundPam.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSoundPamģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeSoundPam.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_SOUND_PAM_DA_VAL_BUF_SIZE    128
uint16 ceSoundPam_sound[CE_SOUND_PAM_DA_VAL_BUF_SIZE];

/**
  * @brief  CeSoundPamģ����ͨ��Daת����ɵĻص�����
  * @param  pAddr:CeSoundPam���Զ���ָ��
  * @return None
  */
void ceSoundPam_daLConvertFinishCallBack(void* pAddr)
{
    CeSoundPam *ceSoundPam = (CeSoundPam*)pAddr;
    if(ceSoundPam->workModeL == 0x01)
    {
        ceDaOp.start(&(ceSoundPam->ceDaL),ceSoundPam_sound,CE_SOUND_PAM_DA_VAL_BUF_SIZE);
    }
    else
    {
        ceSoundPam->startFinishCallBackL();
    }
}

/**
  * @brief  CeSoundPamģ����ͨ��Daת����ɵĻص�����
  * @param  pAddr:CeSoundPam���Զ���ָ��
  * @return None
  */
void ceSoundPam_daRConvertFinishCallBack(void* pAddr)
{
    CeSoundPam *ceSoundPam = (CeSoundPam*)pAddr;
    if(ceSoundPam->workModeR == 0x01)
    {
        ceDaOp.start(&(ceSoundPam->ceDaR),ceSoundPam_sound,CE_SOUND_PAM_DA_VAL_BUF_SIZE);
    }
    else
    {
        ceSoundPam->startFinishCallBackL();
    }
}

/**
  * @brief  CeSoundPamģ���ʼ��
  * @param  ceSoundPam:CeSoundPam���Զ���
  * @param  ceXX:CeSoundPamģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceSoundPam_initial(CeSoundPam* ceSoundPam, CE_RESOURCE ceDaL, CE_RESOURCE ceDaR)
{
    int i;
    for (i = 0; i < CE_SOUND_PAM_DA_VAL_BUF_SIZE; i++)
    {
        ceSoundPam_sound[i] = ((i % 2 == 0) ? CE_DA_CONVERT_MAX_VAL : 0);
    }
    ceSoundPam->ceDaL.ceResource = ceDaL;
    ceSoundPam->ceDaL.convertIntervalNs = 1000000;
    ceSoundPam->ceDaL.callBackConvertFinish = ceSoundPam_daLConvertFinishCallBack;
    ceSoundPam->ceDaL.pAddPar = ceSoundPam;
    ceDaOp.initial(&(ceSoundPam->ceDaL));
    ceSoundPam->workModeL = 0x00;

    ceSoundPam->ceDaR.ceResource = ceDaR;
    ceSoundPam->ceDaL.convertIntervalNs = 1000000;
    ceSoundPam->ceDaR.callBackConvertFinish = ceSoundPam_daRConvertFinishCallBack;
    ceSoundPam->ceDaR.pAddPar = ceSoundPam;
    ceDaOp.initial(&(ceSoundPam->ceDaR));
    ceSoundPam->workModeR = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ʹģ�鰴�ո������������м�������֮���ʱ������������ͨ������Mp3�����ֲ���
  * @param  ceSoundPam:CeSoundPam���Զ���ָ��
  * @param  chLorR:����������������
  * @param  dataBuf:���ݻ��棬�������DA��ת����ȱ�����ͬ
  * @param  dataBufSize:���ݻ���Ĵ�С
  * @param  intervalNs:������֮���ʱ����
  * @param  startFinishCallBack:������ɺ�Ļص�
  */
void ceSoundPam_start(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR, uint16* dataBuf, uint16 dataBufSize, uint32 intervalNs, void(*startFinishCallBack)(void))
{
    if(chLorR == CE_SOUND_PAM_CH_L)
    {
        ceSoundPam->workModeL = 0x00;
        ceSoundPam->startFinishCallBackL = startFinishCallBack;
        ceSoundPam->ceDaL.convertIntervalNs = intervalNs;
        ceDaOp.updata(&(ceSoundPam->ceDaL));
        ceDaOp.start(&(ceSoundPam->ceDaL), dataBuf, dataBufSize);
    }
    else if(chLorR == CE_SOUND_PAM_CH_R)
    {
        ceSoundPam->workModeR = 0x00;
        ceSoundPam->startFinishCallBackR = startFinishCallBack;
        ceSoundPam->ceDaR.convertIntervalNs = intervalNs;
        ceDaOp.updata(&(ceSoundPam->ceDaR));
        ceDaOp.start(&(ceSoundPam->ceDaR), dataBuf, dataBufSize);
    }
    else
    {
        ceSoundPam->workModeL = 0x00;
        ceSoundPam->startFinishCallBackL = startFinishCallBack;
        ceSoundPam->ceDaL.convertIntervalNs = intervalNs;
        ceDaOp.updata(&(ceSoundPam->ceDaL));
        ceSoundPam->workModeR = 0x00;
        ceSoundPam->startFinishCallBackR = startFinishCallBack;
        ceSoundPam->ceDaR.convertIntervalNs = intervalNs;
        ceDaOp.updata(&(ceSoundPam->ceDaR));
        ceDaOp.start(&(ceSoundPam->ceDaL), dataBuf, dataBufSize);
        ceDaOp.start(&(ceSoundPam->ceDaR), dataBuf, dataBufSize);
    }
}

/**
  * @brief  �Թ̶�Ƶ�ʷ�������,�첽����������������ɺ�ֱ�ӷ���
  * @param  ceSoundPam:CeSoundPam���Զ���ָ��
  * @param  chLorR:����������������
  * @param  fixFreHz:������Ƶ��
  */
void ceSoundPam_startFixFrequencySound(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR, uint32 fixFreHz)
{
    if (chLorR == CE_SOUND_PAM_CH_L)//L
    {
        ceDaOp.stop(&(ceSoundPam->ceDaL));
        ceSoundPam->ceDaL.convertIntervalNs = (uint32)((uint64)(1 * 1000 * 1000 * 1000 / 2) / ((uint64)fixFreHz));
        ceDaOp.updata(&(ceSoundPam->ceDaL));
        ceDaOp.start(&(ceSoundPam->ceDaL), ceSoundPam_sound, CE_SOUND_PAM_DA_VAL_BUF_SIZE);
        ceSoundPam->workModeL = 0x01;
    }
    else if(chLorR == CE_SOUND_PAM_CH_R)//R
    {
        ceDaOp.stop(&(ceSoundPam->ceDaR));
        ceSoundPam->ceDaR.convertIntervalNs = (uint32)((uint64)(1 * 1000 * 1000 * 1000 / 2) / ((uint64)fixFreHz));
        ceDaOp.updata(&(ceSoundPam->ceDaR));
        ceDaOp.start(&(ceSoundPam->ceDaL), ceSoundPam_sound, CE_SOUND_PAM_DA_VAL_BUF_SIZE);
        ceSoundPam->workModeR = 0x01;
    }
    else
    {
        ceDaOp.stop(&(ceSoundPam->ceDaL));
        ceSoundPam->ceDaL.convertIntervalNs = 1000000;//(uint32)((uint64)(1 * 1000 * 1000 * 1000 / 2) / ((uint64)fixFreHz));
        ceDaOp.updata(&(ceSoundPam->ceDaL));
        ceDaOp.start(&(ceSoundPam->ceDaL),ceSoundPam_sound, CE_SOUND_PAM_DA_VAL_BUF_SIZE);
        ceSoundPam->workModeL = 0x01;

        ceDaOp.stop(&(ceSoundPam->ceDaR));
        ceSoundPam->ceDaR.convertIntervalNs = 1000000;//(uint32)((uint64)(1 * 1000 * 1000 * 1000 / 2) / ((uint64)fixFreHz));
        ceDaOp.updata(&(ceSoundPam->ceDaR));
        ceDaOp.start(&(ceSoundPam->ceDaR), ceSoundPam_sound, CE_SOUND_PAM_DA_VAL_BUF_SIZE);
        ceSoundPam->workModeR = 0x01;
    }
}

/**
  * @brief  ֹͣ�Թ̶�Ƶ�ʷ�������,�첽����������������ɺ�ֱ�ӷ���
  * @param  ceSoundPam:CeSoundPam���Զ���ָ��
  * @param  chLorR:����������������
  */
void ceSoundPam_stopFixFrequencySound(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR)
{
    if (chLorR == CE_SOUND_PAM_CH_L)//L
    {
        ceDaOp.stop(&(ceSoundPam->ceDaL));
    }
    else if(chLorR == CE_SOUND_PAM_CH_R)//R
    {
        ceDaOp.stop(&(ceSoundPam->ceDaR));
    }
    else
    {
        ceDaOp.stop(&(ceSoundPam->ceDaL));
        ceDaOp.stop(&(ceSoundPam->ceDaR));
    }
}

const CeSoundPamOp ceSoundPamOp = {ceSoundPam_initial, ceSoundPam_start,ceSoundPam_startFixFrequencySound, ceSoundPam_stopFixFrequencySound};

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeSoundPam.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSoundPam模块的驱动库文件
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
  * @brief  CeSoundPam模块左通道Da转换完成的回调处理
  * @param  pAddr:CeSoundPam属性对象指针
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
  * @brief  CeSoundPam模块右通道Da转换完成的回调处理
  * @param  pAddr:CeSoundPam属性对象指针
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
  * @brief  CeSoundPam模块初始化
  * @param  ceSoundPam:CeSoundPam属性对象
  * @param  ceXX:CeSoundPam模块使用的资源号
  * @return 系统状态码
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
  * @brief  使模块按照给定的数字序列及两个点之间的时间间隔来发声，通常用于Mp3等音乐播放
  * @param  ceSoundPam:CeSoundPam属性对象指针
  * @param  chLorR:左声道还是右声道
  * @param  dataBuf:数据缓存，宽度因与DA的转换宽度保持相同
  * @param  dataBufSize:数据缓存的大小
  * @param  intervalNs:两个点之间的时间间隔
  * @param  startFinishCallBack:播放完成后的回调
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
  * @brief  以固定频率发出声音,异步发声，函数配置完成后，直接返回
  * @param  ceSoundPam:CeSoundPam属性对象指针
  * @param  chLorR:左声道还是右声道
  * @param  fixFreHz:发声的频率
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
  * @brief  停止以固定频率发出声音,异步发声，函数配置完成后，直接返回
  * @param  ceSoundPam:CeSoundPam属性对象指针
  * @param  chLorR:左声道还是右声道
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

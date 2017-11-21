/**
  ******************************************************************************
  * @file    CeSoundDetS.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSoundDetS模块的驱动库文件
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
  * @brief  CeSoundDetS模块初始化
  * @param  ceSoundDetS:CeSoundDetS属性对象
  * @param  ceAd:CeSoundDetS模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceSoundDetS_initial(CeSoundDetS* ceSoundDetS, CE_RESOURCE ceAd)
{
    ceSoundDetS->ceAd.ceResource = ceAd;
    ceAdOp.initial(&(ceSoundDetS->ceAd));
     return CE_STATUS_SUCCESS;
}

/**
  * @brief  开始录制声音
  * @param  dataBuf:录制的数据缓冲区
  * @param  dataBufSize:录制的数据缓冲区大小
  * @param  intervalNs:两个采样点之间的时间间隔
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
  * @brief  进行一次转换采集，通常用于噪声检测
  * @param  ceSoundDetS:CeSoundDetS属性对象指针
  * @return 当前噪声值，无声为0， MIC头饱和时为CE_AD_CONVERT_MAX_VAL
  */
uint32  ceSoundDetS_getConvertResult(CeSoundDetS* ceSoundDetS)
{
    return ceAdOp.getConvertValue(&(ceSoundDetS->ceAd));
}

const CeSoundDetSOp ceSoundDetSOp = {ceSoundDetS_initial, ceSoundDetS_startRecord, ceSoundDetS_getConvertResult};

#ifdef __cplusplus
 }
#endif //__cplusplus

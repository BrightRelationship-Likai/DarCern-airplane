/**
  ******************************************************************************
  * @file    CeSoundDet.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSoundDet模块的驱动库文件
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
  * @brief  CeSoundDet外部中断Int的回调处理
  * @param  pAddPar:CeSoundDet属性对象指针
  * @return 系统状态码
  */
void callBackInt(void* pAddPar)
{
    if(((CeSoundDet*)(pAddPar))->callBack != CE_NULL)
    {
        ((CeSoundDet*)(pAddPar))->callBack();
    }
}

/**
  * @brief  CeSoundDet模块初始化
  * @param  ceSoundDet:CeSoundDet属性对象
  * @param  ceAd:CeSoundDet模块使用的资源号
  * @return 系统状态码
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
  * @brief  开始录制声音
  * @param  ceSoundDet:CeSoundDet属性对象
  * @param  dataBuf:录制的数据缓冲区
  * @param  dataBufSize:录制的数据缓冲区大小
  * @param  intervalNs:两个采样点之间的时间间隔
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
  * @brief  进行一次转换采集，通常用于噪声检测
  * @param  ceSoundDet:CeSoundDet属性对象
  * @return 当前噪声值，无声为0， MIC头饱和时为CE_AD_CONVERT_MAX_VAL
  */
uint32  ceSoundDet_getConvertResult(CeSoundDet* ceSoundDet)
{
    return ceAdOp.getConvertValue(&(ceSoundDet->ceAd));
}

const CeSoundDetOp ceSoundDetOp = {ceSoundDet_initial, ceSoundDet_startRecord, ceSoundDet_getConvertResult};

#ifdef __cplusplus
}
#endif //__cplusplus

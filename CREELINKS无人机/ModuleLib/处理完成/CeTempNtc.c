/**
  ******************************************************************************
  * @file    CeTempNtc.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTempNtc模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeTempNtc.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#define CE_TEMP_NTC_12WIDTH_TEMP0C      0x0FCD  /*!< 宏定义12位宽度Ad，模块在0度环境中的默认采样值*/
#define CE_TEMP_NTC_12WIDTH_TEMP100C    0x0AAF  /*!< 宏定义12位宽度Ad，模块在100度环境中的默认采样值*/

/**
 * @brief  CeTempNtc模块初始化
 * @param  ceTempNtc:CeTempNtc属性对象
 * @param  ceAd:CeTempNtc模块使用的资源号
 * @return 系统状态码
 */
CE_STATUS ceTempNtc_initial(CeTempNtc* ceTempNtc, CE_RESOURCE ceAd)
{
    ceTempNtc->ceAd.ceResource = ceAd;
    ceAdOp.initial(&(ceTempNtc->ceAd));
    ceTempNtc->temp0C = (CE_AD_CONVERT_WIDTH * CE_TEMP_NTC_12WIDTH_TEMP0C) / 12;
    ceTempNtc->temp100C = (CE_AD_CONVERT_WIDTH * CE_TEMP_NTC_12WIDTH_TEMP100C) / 12;
    return CE_STATUS_SUCCESS;
}

/**
 * @brief  获取温度值，有两位小数点
 * @param  ceTempNtc:CeTempNtc属性对象
 * @return None
 */
fp32 ceTempNtc_getTemperature(CeTempNtc* ceTempNtc)
{
    uint16 val = 0x0000;
    val = (uint16) ceAdOp.getConvertValue(&(ceTempNtc->ceAd));
    return (fp32) (ceTempNtc->temp0C - val) / ((fp32) (((ceTempNtc->temp0C - ceTempNtc->temp100C < 100) ? 100 : (ceTempNtc->temp0C - ceTempNtc->temp100C))) / 100);
}

/**
 * @brief  校准温度，请在0度100度的真实环境中分别使用getTemperature获取一次温度值，然后填入对应值，以此来修正温度计算的误差。
 * @param  ceTempNtc:CeTempNtc属性对象
 * @param  temp0C:模块在0度环境中的实际采样值
 * @param  temp100C:模块在100度环境中的实际采样值
 * @return None
 */
void ceTempNtc_calibration(CeTempNtc* ceTempNtc, fp32 temp0C, fp32 temp100C)
{
    ceTempNtc->temp0C = (uint16) (((ceTempNtc->temp0C - ceTempNtc->temp100C) / 100) * temp0C + ceTempNtc->temp0C);
    ceTempNtc->temp100C = (uint16) (((ceTempNtc->temp0C - ceTempNtc->temp100C) / 100) * temp0C + ceTempNtc->temp100C);
}

CeTempNtcOp ceTempNtcOp = {ceTempNtc_initial, ceTempNtc_getTemperature, ceTempNtc_calibration};

#ifdef __cplusplus
 }
#endif //__cplusplus

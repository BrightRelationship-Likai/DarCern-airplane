/**
  ******************************************************************************
  * @file    CeLight.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeLight模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeLight.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#define CE_LIGHT_12WIDTH_LIGHT_DARK         0x0FFF  /*!< 宏定义12位宽度Ad，模块在无光环境中的默认采样值*/
#define CE_LIGHT_12WIDTH_LIGHT_SATURATED    0x0000  /*!< 宏定义12位宽度Ad，模块在强光环境中(传感器饱和)的默认采样值*/
/**
  * @brief  CeLight模块初始化
  * @param  ceLight:CeLight属性对象
  * @param  ceAd:CeLight模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceLight_initial(CeLight* ceLight, CE_RESOURCE ceAd)
{
    ceLight->ceAd.ceResource = ceAd;
    ceAdOp.initial(&(ceLight->ceAd));
    ceLight->lightDark = 0;
    return CE_STATUS_SUCCESS;
}

/**
 * @brief  获取光线亮度，范围0-100，表示光线弱强
 * @param  ceLight:CeLight属性对象
 * @return None
 */
int16 ceLight_getLight(CeLight* ceLight)
{
    uint16 val = 0x0000;
    uint16 temp0, temp1;
    val = (uint16)ceAdOp.getConvertValue(&(ceLight->ceAd));
    temp0 = (CE_AD_CONVERT_WIDTH * CE_LIGHT_12WIDTH_LIGHT_DARK) / 12;
    temp1 =  (CE_AD_CONVERT_WIDTH * CE_LIGHT_12WIDTH_LIGHT_SATURATED) / 12;
    val = ((temp0 - val) / (((temp0 - temp1 < 100) ? 100 : (temp0 - temp1)) / 100));
    val = val * (uint32)(ceLight->lightHard- ceLight->lightDark)/100 - ceLight->lightDark;
    return val;
}

/**
 * @brief  校准光线，请在无光的真实环境中使用getLight获取一次光线的亮度，然后填入此值，以此来修正光线亮度计算的误差
 * @param  ceLight:CeLight属性对象
 * @param   lightDark:模块在无光环境中的实际采样值
 * @return None
 */
void ceLight_calibration(CeLight* ceLight, int16 lightDark,int16 lightHard)
{
    ceLight->lightDark = lightDark;
    ceLight->lightHard = lightHard;
}

const CeLightOp ceLightOp = {ceLight_initial, ceLight_getLight, ceLight_calibration};

#ifdef __cplusplus
 }
#endif //__cplusplus

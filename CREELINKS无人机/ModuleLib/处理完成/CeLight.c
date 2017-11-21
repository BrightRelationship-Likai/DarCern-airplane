/**
  ******************************************************************************
  * @file    CeLight.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeLightģ����������ļ�
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
#define CE_LIGHT_12WIDTH_LIGHT_DARK         0x0FFF  /*!< �궨��12λ���Ad��ģ�����޹⻷���е�Ĭ�ϲ���ֵ*/
#define CE_LIGHT_12WIDTH_LIGHT_SATURATED    0x0000  /*!< �궨��12λ���Ad��ģ����ǿ�⻷����(����������)��Ĭ�ϲ���ֵ*/
/**
  * @brief  CeLightģ���ʼ��
  * @param  ceLight:CeLight���Զ���
  * @param  ceAd:CeLightģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceLight_initial(CeLight* ceLight, CE_RESOURCE ceAd)
{
    ceLight->ceAd.ceResource = ceAd;
    ceAdOp.initial(&(ceLight->ceAd));
    ceLight->lightDark = 0;
    return CE_STATUS_SUCCESS;
}

/**
 * @brief  ��ȡ�������ȣ���Χ0-100����ʾ������ǿ
 * @param  ceLight:CeLight���Զ���
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
 * @brief  У׼���ߣ������޹����ʵ������ʹ��getLight��ȡһ�ι��ߵ����ȣ�Ȼ�������ֵ���Դ��������������ȼ�������
 * @param  ceLight:CeLight���Զ���
 * @param   lightDark:ģ�����޹⻷���е�ʵ�ʲ���ֵ
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

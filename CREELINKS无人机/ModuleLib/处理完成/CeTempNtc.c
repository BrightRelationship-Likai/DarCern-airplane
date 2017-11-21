/**
  ******************************************************************************
  * @file    CeTempNtc.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTempNtcģ����������ļ�
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
#define CE_TEMP_NTC_12WIDTH_TEMP0C      0x0FCD  /*!< �궨��12λ���Ad��ģ����0�Ȼ����е�Ĭ�ϲ���ֵ*/
#define CE_TEMP_NTC_12WIDTH_TEMP100C    0x0AAF  /*!< �궨��12λ���Ad��ģ����100�Ȼ����е�Ĭ�ϲ���ֵ*/

/**
 * @brief  CeTempNtcģ���ʼ��
 * @param  ceTempNtc:CeTempNtc���Զ���
 * @param  ceAd:CeTempNtcģ��ʹ�õ���Դ��
 * @return ϵͳ״̬��
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
 * @brief  ��ȡ�¶�ֵ������λС����
 * @param  ceTempNtc:CeTempNtc���Զ���
 * @return None
 */
fp32 ceTempNtc_getTemperature(CeTempNtc* ceTempNtc)
{
    uint16 val = 0x0000;
    val = (uint16) ceAdOp.getConvertValue(&(ceTempNtc->ceAd));
    return (fp32) (ceTempNtc->temp0C - val) / ((fp32) (((ceTempNtc->temp0C - ceTempNtc->temp100C < 100) ? 100 : (ceTempNtc->temp0C - ceTempNtc->temp100C))) / 100);
}

/**
 * @brief  У׼�¶ȣ�����0��100�ȵ���ʵ�����зֱ�ʹ��getTemperature��ȡһ���¶�ֵ��Ȼ�������Ӧֵ���Դ��������¶ȼ������
 * @param  ceTempNtc:CeTempNtc���Զ���
 * @param  temp0C:ģ����0�Ȼ����е�ʵ�ʲ���ֵ
 * @param  temp100C:ģ����100�Ȼ����е�ʵ�ʲ���ֵ
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

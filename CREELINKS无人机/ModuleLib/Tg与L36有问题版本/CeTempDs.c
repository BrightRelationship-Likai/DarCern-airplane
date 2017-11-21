/**
  ******************************************************************************
  * @file    CeTempDs.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTempDsģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeTempDs.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  CeTempDs��������λ
  * @param  ceTempDs:CeTempDs���Զ���ָ��
  * @return �����Ķ�����λ
  */
uint8 ceTempDs_readBit(CeTempDs* ceTempDs)
{
     uint8 bitData = 0;
     ceGpioOp.setMode(&ceTempDs->ceGpio, CE_GPIO_MODE_OUT_PP);
     ceGpioOp.setBit(&ceTempDs->ceGpio);
     ceSystemOp.delayUs(2);
     ceGpioOp.resetBit(&ceTempDs->ceGpio);
     ceSystemOp.delayUs(2);
     ceGpioOp.setBit(&ceTempDs->ceGpio);

     ceGpioOp.setMode(&ceTempDs->ceGpio, CE_GPIO_MODE_IPU);
     ceSystemOp.delayUs(12);
     if (ceGpioOp.getBit(&ceTempDs->ceGpio))
          bitData = 1;
     else
          bitData = 0;
     ceSystemOp.delayUs(60);
     return bitData;
}

/**
  * @brief  CeTempDs���ֽ�
  * @param  ceTempDs:CeTempDs���Զ���ָ��
  * @return �������ֽ�
  */
uint8 ceTempDs_readByte(CeTempDs* ceTempDs)
{
     uint8 i, byteTemp, byteData;
     byteTemp = 0;
     byteData = 0;
     for (i = 0; i < 8; i++)
     {
          byteTemp = ceTempDs_readBit(ceTempDs);
          byteData = (byteTemp << i) | byteData;
     }
     return byteData;
}

/**
  * @brief  CeTempDsд�ֽ�
  * @param  ceTempDs:CeTempDs���Զ���ָ��
  * @param  ceData:Ҫд���ֽ�
  */
void ceTempDs_writeByte(CeTempDs* ceTempDs, uint8 ceData)
{
     uint8 i;
     ceGpioOp.setMode(&ceTempDs->ceGpio, CE_GPIO_MODE_OUT_PP);
     for (i = 0; i < 8; i++)
     {
          ceGpioOp.resetBit(&ceTempDs->ceGpio);
          if ((ceData & 0x01) == 0x01)
          {
               ceSystemOp.delayUs(2);
               ceGpioOp.setBit(&ceTempDs->ceGpio);
               ceSystemOp.delayUs(60);
          }
          else
          {
               ceSystemOp.delayUs(60);
               ceGpioOp.resetBit(&ceTempDs->ceGpio);
               ceSystemOp.delayUs(2);
          }
          ceGpioOp.setBit(&ceTempDs->ceGpio);
          ceData >>= 1;
     }
}

/**
  * @brief  CeTempDs��λ
  * @param  ceTempDs:CeTempDs���Զ���ָ��
  */
void ceTempDs_reset(CeTempDs* ceTempDs)
{
     ceGpioOp.setMode(&ceTempDs->ceGpio, CE_GPIO_MODE_OUT_PP); // Set OutPut
     ceGpioOp.setBit(&ceTempDs->ceGpio); // ����ߵ�ƽ
     ceSystemOp.delayUs(2); // 2us
     ceGpioOp.resetBit(&ceTempDs->ceGpio); // ����͵�ƽ������750us
     ceSystemOp.delayUs(750);
     ceGpioOp.setBit(&ceTempDs->ceGpio);
     ceSystemOp.delayUs(15);      // 15us
}

/**
  * @brief  CeTempDsģ�����豸�Ƿ����
  * @param  ceTempDs:CeTempDs���Զ���ָ��
  * @return ϵͳ״̬�룬���ܵ�ֵ:CE_STATUS_SUCCESS��CE_STATUS_FAILE
  */
CE_STATUS ceTempDs_check(CeTempDs* ceTempDs)
{
     uint8 retry = 0;
     ceTempDs_reset(ceTempDs);

     ceGpioOp.setMode(&ceTempDs->ceGpio, CE_GPIO_MODE_IPU);
     while (ceGpioOp.getBit(&ceTempDs->ceGpio) && retry < 200)
     {
          retry++;
          ceSystemOp.delayUs(1);
     };
     if (retry >= 200)
          return CE_STATUS_FAILE;
     else
          retry = 0x00;

     while (!ceGpioOp.getBit(&ceTempDs->ceGpio) && retry < 240)
     {
          retry++;
          ceSystemOp.delayUs(1);
     };
     if (retry >= 240)
          return CE_STATUS_FAILE;
     return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeTempDsģ���ʼ��
  * @param  ceTempDs:CeTempDs���Զ���ָ��
  * @param  ceGpio:CeTempDsģ��ʹ�õ���Դ��
  * @return ϵͳ״̬�룬���ܵ�ֵ:CE_STATUS_SUCCESS��CE_STATUS_FAILE
  */
CE_STATUS ceTempDs_initial(CeTempDs* ceTempDs, CE_RESOURCE ceGpio)
{
     ceTempDs->ceGpio.ceResource = ceGpio;
     ceTempDs->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
     ceGpioOp.initial(&ceTempDs->ceGpio);
     return ceTempDs_check(ceTempDs); // ���DS18b20, ȷ���豸�Ƿ���������
}

/**
  * @brief  ��ȡ�¶�ֵ����Χ-55��+125��
  * @param  ceTempDs:CeTempDs���Զ���ָ��
  * @return ���ػ�ȡ�����¶�ֵ������λС���㡣����豸�����ڣ�����0
  */
fp32 ceTempDs_getTemperature(CeTempDs* ceTempDs)
{
     uint8 TempL = 0, TempH = 0;
     int16 Temp = 0;
     if (ceTempDs_check(ceTempDs) != CE_STATUS_SUCCESS)
    {
        return (fp32)0;
    }
     ceTempDs_writeByte(ceTempDs, 0xCC); // ��ʼ�¶�ת�� �¶�ת�� (ָ����0x44H)
     ceTempDs_writeByte(ceTempDs, 0x44);     // convert RAMָ��

    if (ceTempDs_check(ceTempDs) != CE_STATUS_SUCCESS)
    {
        return (fp32)0;
    }
     ceTempDs_writeByte(ceTempDs, 0xCC); // ���ݴ���(ָ����0xBEH)
     ceTempDs_writeByte(ceTempDs, 0xBE);     // convert RAM ָ��

     TempL = ceTempDs_readByte(ceTempDs);
     TempH = ceTempDs_readByte(ceTempDs);
     Temp = TempH;
     Temp = (Temp << 8) + TempL;

     if ((Temp & 0xF800) == 0xF800)
     {
          Temp = ~Temp;
          Temp = Temp + 1;
          return (fp32) (Temp * (-0.0625));
     }
     else
     {
          return (fp32) (Temp * 0.0625);
     }
}

const CeTempDsOp ceTempDsOp = {ceTempDs_initial, ceTempDs_getTemperature};

#ifdef __cplusplus
 }
#endif //__cplusplus


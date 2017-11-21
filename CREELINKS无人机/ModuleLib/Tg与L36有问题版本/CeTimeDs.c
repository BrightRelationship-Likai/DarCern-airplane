/**
  ******************************************************************************
  * @file    CeTimeDs.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTimeDsģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeTimeDs.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

     /*!< */

//оƬ�Ĵ�����ַ���� �����д��ַ������Ҫ+1
#define CE_TIME_DS1302_SEC_REG          0x80        /*!< �����ݵ�ַ������Ҫ + 1��д���䡣
                                                            ���λ��ʾʱ����ͣ��־(CH)������λ��Ϊ1ʱ��ʱ������ֹͣ��DS1302���ڵ͹���״̬��
                                                                                        ����λ��Ϊ0ʱ��ʱ�ӿ�ʼ���С�*/
#define CE_TIME_DS1302_MIN_REG          0x82        /*!< �����ݵ�ַ������Ҫ + 1��д����*/
#define CE_TIME_DS1302_HR_REG           0x84        /*!< ʱ���ݵ�ַ������Ҫ + 1��д����*/
#define CE_TIME_DS1302_DATE_REG         0x86        /*!< �����ݵ�ַ������Ҫ + 1��д����*/
#define CE_TIME_DS1302_MONTH_REG        0x88        /*!< �����ݵ�ַ������Ҫ + 1��д����*/
#define CE_TIME_DS1302_DAY_REG          0x8a        /*!< ���ڼ����ݵ�ַ������Ҫ + 1��д����*/
#define CE_TIME_DS1302_YEAR_REG         0x8c        /*!< �����ݵ�ַ������Ҫ + 1��д����*/
#define CE_TIME_DS1302_CONTROL_REG      0x8e        /*!< д�����Ĵ�����ַ�����λΪд����λ(WP)������7λ����0*/
#define CE_TIME_DS1302_CHARGER_REG      0x90        /*!< ������Ĵ���*/
#define CE_TIME_DS1302_CLKBURST_REG     0xbe        /*!< ���崮�Ĵ���*/
#define CE_TIME_DS1302_RAM_BASE         0X30        /*!< RAM������ַ*/

/**
  * @brief  AsciiתBcd
  * @param  asciiData:��ת����Ascii����
  * @return ����ת�����Bcd
  */
uint8 AsciiToBcd(uint8 asciiData)
{
    uint8 bcdData = 0;
    bcdData = (((asciiData / 10) << 4) | ((asciiData % 10)));
    return bcdData;
}

/**
  * @brief  BcdתAscii
  * @param  bcdData:��ת����Bcd����
  * @return ����ת�����Ascii
  */
uint8 BcdToAscii(uint8 bcdData)
{
    uint8 asciiData = 0;
    asciiData = (((bcdData & 0xf0) >> 4) * 10 + (bcdData & 0x0f));
    return asciiData;
}

/**
  * @brief  DS1302д�ֽ�
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @param  val:��д���ֽ�����
  * @return None
  */
void ceTimeDs_writeByte(CeTg* ceTg, uint8 val)
{
    uint8 i = 0;
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
    ceSystemOp.delayUs(2);
    for(i = 0; i < 8; i ++)
    {
        if((val & 0x01) == 0x01)
        {
            ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
        }
        else
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
        }
        ceGpioOp.setBit(&(ce8Segx1->ceGpio1));
        val >>= 1;
        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
    }
}

/**
  * @brief  DS1302���ֽ�
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @return ���ض�ȡ��������
  */
uint8 ceTimeDs_readByte(CeTg* ceTg)
{
    uint8 i = 0x00;
    uint8 readVal = 0x00;
    for(i = 0; i < 8; i ++)
    {
        readVal >>= 1;
        if(ceTgOp.getGpio2Bit(ceTg) == 0x01)
        {
            readVal = readVal | 0x80;
        }
        ceGpioOp.setBit(&(ce8Segx1->ceGpio1));
        ceSystemOp.delayUs(2);
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
        ceSystemOp.delayUs(2);
    }
    return readVal;
}

/**
  * @brief  CeTimeDs��ָ����ַ��ȡ����
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @param  readAdd:����ȡ���ݵĵ�ַ
  * @return ���ض�ȡ��������
  */
uint8 ceTimeDs_read(CeTg* ceTg, uint8 readAdd)
{
    uint8 dat = 0;
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
    ceGpioOp.setBit(&(ce8Segx1->ceGpio0));
    ceTimeDs_writeByte(ceTg, readAdd | 0x01);
    dat = ceTimeDs_readByte(ceTg);
    ceGpioOp.setBit(&(ce8Segx1->ceGpio0));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
    return dat;
}

/**
  * @brief  CeTimeDsд���ݵ�ָ����ַ
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @param  readAdd:��д���ĵ�ַ
  * @pram   readVal:��д������
  * @return None
  */
void ceTimeDs_write(CeTg* ceTg, uint8 readAdd, uint8 readVal)
{
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
    ceGpioOp.setBit(&(ce8Segx1->ceGpio0));
    ceTimeDs_writeByte(ceTg, readAdd);
    ceTimeDs_writeByte(ceTg, readVal);
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
    ceSystemOp.delayUs(1);
}

/**
  * @brief  CeTimeDsģ���ڲ��ĳ�ʼ��
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @return None
  */
void ceTimeDs_initial(CeTimeDs* ceTimeDs)
{
    uint8 i = 0;
    uint8 j = 0;
    uint8 write[] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
    uint8 time[] = {0, 0, 12, 11, 11, 1, 13};

    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_CONTROL_REG, 0x00);

    for(i = 0; i < 7; i++)
    {
        j = time[i] % 10;
        time[i] = (time[i] / 10) * 16 + j;
    }
    for(i = 0; i < 7; i++)
    {
        ceTimeDs_write(&(ceTimeDs->ceTg), write[i], time[i]);
    }
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_CONTROL_REG, 0x80);
}

/**
  * @brief  CeTimeDsģ��ʹ��Gpio���г�ʼ��
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @param  ceGpio0CeTimeDsģ��ʹ�õĵ�һ��Gpio��Դ��
  * @param  ceGpio1:CeTimeDsģ��ʹ�õĵڶ���Gpio��Դ��
  * @param  ceGpio2:CeTimeDsģ��ʹ�õĵ�����Gpio��Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceTimeDs_initialByGpio(CeTimeDs* ceTimeDs, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ceTimeDs->ceTg.ceResource = CE_NULL_RESOURCE;
    ceTimeDs->ceTg.ceResource0 = ceGpio0;//RST
    ceTimeDs->ceTg.ceResource1 = ceGpio1;//SCLK
    ceTimeDs->ceTg.ceResource2 = ceGpio2;//SDA
    ceTgOp.initial(&(ceTimeDs->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_OD);
    ceGpioOp.resetBit(&(ceTimeDs->ceTg));
    ceGpioOp.resetBit(&(ceTimeDs->ceTg));
    ceGpioOp.resetBit(&(ceTimeDs->ceTg));
    ceTimeDs_initial(ceTimeDs);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeTimeDsģ���ʼ��
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @param  ceTg:CeTimeDsģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceTimeDs_initialByTg(CeTimeDs* ceTimeDs, CE_RESOURCE ceTg)
{
    ceTimeDs->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceTimeDs->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_OD);//RST,SCLK,SDA
    ceGpioOp.resetBit(&(ceTimeDs->ceTg));
    ceGpioOp.resetBit(&(ceTimeDs->ceTg));
    ceGpioOp.resetBit(&(ceTimeDs->ceTg));
    ceTimeDs_initial(ceTimeDs);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��������ʱ��
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @param ceTimeDsData:Ҫ���õ�ʱ��ṹ���ָ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceTimeDs_setTime(CeTimeDs* ceTimeDs, CeTimeDsDate ceTimeDsData)
{
    ceTimeDsData.year -= 2000;//�Ĵ�����ֻ����00-99����ݣ���������ʱ���ʱ���ȥ2000
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_CONTROL_REG, 0x00);
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_SEC_REG,  (AsciiToBcd(ceTimeDsData.second)) | 0x00);//���忴CE_TIME_DS1302_SEC_REG��ע��
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_MIN_REG,   AsciiToBcd(ceTimeDsData.minute));
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_HR_REG,    AsciiToBcd(ceTimeDsData.hour));
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_DATE_REG,  AsciiToBcd(ceTimeDsData.day));
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_MONTH_REG, AsciiToBcd(ceTimeDsData.month));
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_DAY_REG,   AsciiToBcd(ceTimeDsData.week));
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_YEAR_REG,  AsciiToBcd(ceTimeDsData.year));
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_CONTROL_REG, 0x80);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡ����ʱ��
  * @param  ceTimeDs:CeTimeDs���Զ���
  * @return ���ػ�ȡ��������ʱ��Ľṹ��ָ��
  */
CeTimeDsDate* ceTimeDs_getTime(CeTimeDs* ceTimeDs)
{
    ceTimeDs->ceTimeDsDate.year   = BcdToAscii(ceTimeDs_read(&(ceTimeDs->ceTg), CE_TIME_DS1302_YEAR_REG));
    ceTimeDs->ceTimeDsDate.week   = BcdToAscii(ceTimeDs_read(&(ceTimeDs->ceTg), CE_TIME_DS1302_DAY_REG));
    ceTimeDs->ceTimeDsDate.month  = BcdToAscii(ceTimeDs_read(&(ceTimeDs->ceTg), CE_TIME_DS1302_MONTH_REG));
    ceTimeDs->ceTimeDsDate.day    = BcdToAscii(ceTimeDs_read(&(ceTimeDs->ceTg), CE_TIME_DS1302_DATE_REG));
    ceTimeDs->ceTimeDsDate.hour   = BcdToAscii(ceTimeDs_read(&(ceTimeDs->ceTg), CE_TIME_DS1302_HR_REG));
    ceTimeDs->ceTimeDsDate.minute = BcdToAscii(ceTimeDs_read(&(ceTimeDs->ceTg), CE_TIME_DS1302_MIN_REG));
    ceTimeDs->ceTimeDsDate.second = BcdToAscii(ceTimeDs_read(&(ceTimeDs->ceTg), CE_TIME_DS1302_SEC_REG));
    ceTimeDs->ceTimeDsDate.year += 2000;//�Ĵ�����ֻ����00-99����ݣ����Ի�ȡʱ���ʱ�����2000
    return &(ceTimeDs->ceTimeDsDate);
}

const CeTimeDsOp ceTimeDsOp = {ceTimeDs_initialByGpio, ceTimeDs_initialByTg, ceTimeDs_setTime, ceTimeDs_getTime};

#ifdef __cplusplus
}
#endif //__cplusplus

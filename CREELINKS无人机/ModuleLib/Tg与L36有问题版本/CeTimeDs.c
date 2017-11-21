/**
  ******************************************************************************
  * @file    CeTimeDs.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTimeDs模块的驱动库文件
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

//芯片寄存器地址定义 定义的写地址，读需要+1
#define CE_TIME_DS1302_SEC_REG          0x80        /*!< 秒数据地址，读需要 + 1，写不变。
                                                            最高位表示时钟暂停标志(CH)，当该位置为1时，时钟振荡器停止，DS1302处于低功耗状态；
                                                                                        当该位置为0时，时钟开始运行。*/
#define CE_TIME_DS1302_MIN_REG          0x82        /*!< 分数据地址，读需要 + 1，写不变*/
#define CE_TIME_DS1302_HR_REG           0x84        /*!< 时数据地址，读需要 + 1，写不变*/
#define CE_TIME_DS1302_DATE_REG         0x86        /*!< 日数据地址，读需要 + 1，写不变*/
#define CE_TIME_DS1302_MONTH_REG        0x88        /*!< 月数据地址，读需要 + 1，写不变*/
#define CE_TIME_DS1302_DAY_REG          0x8a        /*!< 星期几数据地址，读需要 + 1，写不变*/
#define CE_TIME_DS1302_YEAR_REG         0x8c        /*!< 年数据地址，读需要 + 1，写不变*/
#define CE_TIME_DS1302_CONTROL_REG      0x8e        /*!< 写保护寄存器地址，最高位为写保护位(WP)，其它7位均置0*/
#define CE_TIME_DS1302_CHARGER_REG      0x90        /*!< 涓流充电寄存器*/
#define CE_TIME_DS1302_CLKBURST_REG     0xbe        /*!< 脉冲串寄存器*/
#define CE_TIME_DS1302_RAM_BASE         0X30        /*!< RAM基础地址*/

/**
  * @brief  Ascii转Bcd
  * @param  asciiData:欲转换的Ascii数据
  * @return 返回转换后的Bcd
  */
uint8 AsciiToBcd(uint8 asciiData)
{
    uint8 bcdData = 0;
    bcdData = (((asciiData / 10) << 4) | ((asciiData % 10)));
    return bcdData;
}

/**
  * @brief  Bcd转Ascii
  * @param  bcdData:欲转换的Bcd数据
  * @return 返回转换后的Ascii
  */
uint8 BcdToAscii(uint8 bcdData)
{
    uint8 asciiData = 0;
    asciiData = (((bcdData & 0xf0) >> 4) * 10 + (bcdData & 0x0f));
    return asciiData;
}

/**
  * @brief  DS1302写字节
  * @param  ceTimeDs:CeTimeDs属性对象
  * @param  val:欲写的字节数据
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
  * @brief  DS1302读字节
  * @param  ceTimeDs:CeTimeDs属性对象
  * @return 返回读取到的数据
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
  * @brief  CeTimeDs从指定地址读取数据
  * @param  ceTimeDs:CeTimeDs属性对象
  * @param  readAdd:欲读取数据的地址
  * @return 返回读取到的数据
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
  * @brief  CeTimeDs写数据到指定地址
  * @param  ceTimeDs:CeTimeDs属性对象
  * @param  readAdd:欲写到的地址
  * @pram   readVal:欲写的数据
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
  * @brief  CeTimeDs模块内部的初始化
  * @param  ceTimeDs:CeTimeDs属性对象
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
  * @brief  CeTimeDs模块使用Gpio进行初始化
  * @param  ceTimeDs:CeTimeDs属性对象
  * @param  ceGpio0CeTimeDs模块使用的第一个Gpio资源号
  * @param  ceGpio1:CeTimeDs模块使用的第二个Gpio资源号
  * @param  ceGpio2:CeTimeDs模块使用的第三个Gpio资源号
  * @return 系统状态码
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
  * @brief  CeTimeDs模块初始化
  * @param  ceTimeDs:CeTimeDs属性对象
  * @param  ceTg:CeTimeDs模块使用的资源号
  * @return 系统状态码
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
  * @brief  设置日期时间
  * @param  ceTimeDs:CeTimeDs属性对象
  * @param ceTimeDsData:要设置的时间结构体的指针
  * @return 系统状态码
  */
CE_STATUS ceTimeDs_setTime(CeTimeDs* ceTimeDs, CeTimeDsDate ceTimeDsData)
{
    ceTimeDsData.year -= 2000;//寄存器中只保存00-99的年份，所以设置时间的时候减去2000
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_CONTROL_REG, 0x00);
    ceTimeDs_write(&(ceTimeDs->ceTg), CE_TIME_DS1302_SEC_REG,  (AsciiToBcd(ceTimeDsData.second)) | 0x00);//具体看CE_TIME_DS1302_SEC_REG的注释
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
  * @brief  获取日期时间
  * @param  ceTimeDs:CeTimeDs属性对象
  * @return 返回获取到的日期时间的结构体指针
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
    ceTimeDs->ceTimeDsDate.year += 2000;//寄存器中只保存00-99的年份，所以获取时间的时候加上2000
    return &(ceTimeDs->ceTimeDsDate);
}

const CeTimeDsOp ceTimeDsOp = {ceTimeDs_initialByGpio, ceTimeDs_initialByTg, ceTimeDs_setTime, ceTimeDs_getTime};

#ifdef __cplusplus
}
#endif //__cplusplus

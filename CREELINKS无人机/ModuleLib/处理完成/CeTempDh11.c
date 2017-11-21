/**
  ******************************************************************************
  * @file    CeTempDh11.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTempDh11温湿度传感器模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeTempDh11.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief    从DH11传感器中读一个字节
  * @param    ceTempDh11:CeTempDh11对像指针
  * @return 读取到的字节
  */
char ceTempDh11_readByte(CeTempDh11* ceTempDh11)
{
    uint32 sysTick = 0;
    char i, U8temp, U8comdata=0;
    for (i = 0; i < 8; i++)
    {
        sysTick = ceSystemOp.getSystemTickMs();
        while (ceGpioOp.getBit(&ceTempDh11->ceGpio) == 0x00)    //表示 读取的高电位延时大于20多us 则读取的是1 否则读取的是0
        {
            if (ceSystemOp.getSystemTickMs() < sysTick)
            {
                sysTick = ceSystemOp.getSystemTickMs();
            }else if (ceSystemOp.getSystemTickMs() - sysTick >= 10)
            {
                sysTick = ceSystemOp.getSystemTickMs();
                break;
            }
        }
        ceSystemOp.delayUs(35);                                       //通过U8FLAG 可判断    bit11 显示数据的脉长
        U8temp = 0;
        if (ceGpioOp.getBit(&ceTempDh11->ceGpio) == 0x01)
            U8temp = 1;
        sysTick = ceSystemOp.getSystemTickMs();
        while (ceGpioOp.getBit(&ceTempDh11->ceGpio) == 0x01)
        {
            if (ceSystemOp.getSystemTickMs() < sysTick)
            {
                sysTick = ceSystemOp.getSystemTickMs();
            }else if (ceSystemOp.getSystemTickMs() - sysTick >= 10)
            {
                sysTick = ceSystemOp.getSystemTickMs();
                break;
            }
        }
        U8comdata <<= 1;
        U8comdata |= U8temp;
    }
    return U8comdata;
}

/**
  * @brief    CeTempDh11模块初始化
  * @param    ceTempDh11:CeTempDh11对像指针
  * @return 系统状态码
  */
CE_STATUS ceTempDh11_initial(CeTempDh11* ceTempDh11, CE_RESOURCE ceGpio)
{
    ceTempDh11->ceGpio.ceResource = ceGpio;
    ceTempDh11->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceTempDh11->ceGpio));
    ceGpioOp.setBit(&(ceTempDh11->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief    开始一次温度转换
  * @param  ceTempDh11:CeTempDh11对像指针
*/
void startConvert(CeTempDh11* ceTempDh11)
{
    ceGpioOp.setMode(&(ceTempDh11->ceGpio), CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceTempDh11->ceGpio));
    ceTempDh11->systemTick = ceSystemOp.getSystemTickMs();
}

/**
  * @brief    进行一次转换，并获得转换结果
  * @param    ceTempDh11:CeTempDh11对像指针
  * @return 转换结果
  */
CeTempDh11Result* ceTempDh11_getTemperatureAndHumidity(CeTempDh11* ceTempDh11)
{
    uint32 sysTick = 0;
    uint8 U8checkdata = 0;
    uint8 ceTempDh11Temp[4];
    while ((ceSystemOp.getSystemTickMs() - ceTempDh11->systemTick < 20) && (ceSystemOp.getSystemTickMs() - ceTempDh11->systemTick > 0))
    {
        ceSystemOp.delayMs(0);
    }
    ceTaskOp.inCriticalSection();
    ceGpioOp.setBit(&(ceTempDh11->ceGpio));
    ceSystemOp.delayUs(60);
    ceGpioOp.setMode(&(ceTempDh11->ceGpio), CE_GPIO_MODE_IN_FLOATING);
    sysTick = ceSystemOp.getSystemTickMs();
    if (ceGpioOp.getBit(&(ceTempDh11->ceGpio)) == 0x00)
    {
        while (ceGpioOp.getBit(&(ceTempDh11->ceGpio)) == 0x00)
        {
            if (ceSystemOp.getSystemTickMs() < sysTick)
            {
                sysTick = ceSystemOp.getSystemTickMs();
            }
            if (ceSystemOp.getSystemTickMs() - sysTick >= 10)
            {
                sysTick = ceSystemOp.getSystemTickMs();
                break;
            }
        }
        while (ceGpioOp.getBit(&(ceTempDh11->ceGpio)) == 0x01)
        {
            if (ceSystemOp.getSystemTickMs() < sysTick)
            {
                sysTick = ceSystemOp.getSystemTickMs();
            }
            if (ceSystemOp.getSystemTickMs() - sysTick >= 10)
            {
                sysTick = ceSystemOp.getSystemTickMs();
                break;
            }
        }
        ceTempDh11Temp[0] = ceTempDh11_readByte(ceTempDh11);
        ceTempDh11Temp[1] = ceTempDh11_readByte(ceTempDh11);            //后8位一直为0，这里暂时不计算
        ceTempDh11Temp[2] = ceTempDh11_readByte(ceTempDh11);
        ceTempDh11Temp[3] = ceTempDh11_readByte(ceTempDh11);            //后9位始终为0，这里暂时不计算
        U8checkdata = ceTempDh11_readByte(ceTempDh11);
    }
    ceTaskOp.outCriticalSection();
    if (U8checkdata == (uint8) (ceTempDh11Temp[0] + ceTempDh11Temp[2]))
    {
        ceTempDh11->ceTempDh11Result.temperature = ceTempDh11Temp[2];            //温度
        ceTempDh11->ceTempDh11Result.humidity = ceTempDh11Temp[0];                //湿度
    }

    return &(ceTempDh11->ceTempDh11Result);
}

const CeTempDh11Op ceTempDh11Op = {ceTempDh11_initial,startConvert, ceTempDh11_getTemperatureAndHumidity};

#ifdef __cplusplus
 }
#endif //__cplusplus

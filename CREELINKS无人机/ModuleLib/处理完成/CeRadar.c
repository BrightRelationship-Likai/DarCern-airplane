/**
  ******************************************************************************
  * @file    CeRadar.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRadar模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeRadar.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  外部中断Int的回调处理
  * @return None
  */
void ceRadar_callBackInt(void* pAddPar)
{
    CeRadar* ceRadar = (CeRadar*)pAddPar;
    if (ceRadar->status == 0x01)
    {
        ceRadar->timeCostUs = ceSystemOp.getSystemTickUs();
        ceIntOp.setMode(&(ceRadar->ceInt), CE_INT_MODE_TRIGGER_FALLING);
        ceRadar->status = 0x02;
    }
    else if (ceRadar->status == 0x02)
    {
        ceRadar->timeCost = ceSystemOp.getSystemTickUs() - ceRadar->timeCostUs;
        ceRadar->status = 0x03;
    }
}

/**
  * @brief  CeRadar模块初始化
  * @param  ceRadar:CeRadar属性对象
  * @param  ceGpio:CeRadar模块使用的Gpio资源号
  * @param  ceInt:CeRadar模块使用的Int资源号
  * @return 系统状态码
  */
CE_STATUS ceRadar_initial(CeRadar* ceRadar, CE_RESOURCE ceGpio, CE_RESOURCE ceInt)
{
    ceRadar->status = 0x00;
    ceRadar->ceInt.ceResource = ceInt;//在start中进行外部中断Int的初始化，因为在测试中需要重新配置终端的触发方式
    ceRadar->ceInt.callBack = ceRadar_callBackInt;
    ceRadar->ceInt.pAddPar = ceRadar;
    ceRadar->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_RISING;
    ceIntOp.initial(&(ceRadar->ceInt));

    ceRadar->ceGpio.ceResource = ceGpio;
    ceRadar->ceGpio.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceRadar->ceGpio));
    ceGpioOp.resetBit(&(ceRadar->ceGpio));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  开始雷达探测并获取探测到的物理离模块的距离，单位mm。测量范围2cm-400cm，测量精度3mm。
  * @param  ceRadar:CeRadar属性对象
  * @return 返回探测到的距离，单位mm
  */
uint32 ceRadar_getDistance(CeRadar* ceRadar)
{
    uint32 outTime = 0;
    ceRadar->timeCost = 0;
    ceRadar->status = 0x01;
    ceIntOp.setMode(&(ceRadar->ceInt), CE_INT_MODE_TRIGGER_RISING);
    ceIntOp.start(&(ceRadar->ceInt));

    ceGpioOp.setBit(&(ceRadar->ceGpio));//产生至少10us的高电平开始测距信号
    ceSystemOp.delayUs(20);
    ceGpioOp.resetBit(&(ceRadar->ceGpio));

    while(ceRadar->status != 0x03)
    {
        ceSystemOp.delayMs(5);
        outTime += 5;
        if (outTime > 250)
        {
            break;
        }
    }
    ceRadar->status = 0x00;
    ceIntOp.stop(&(ceRadar->ceInt));
    return (uint32)((ceRadar->timeCost * 100)  / 580);//1cm/58us，不考虑温度对空气影响导致的误差
}

/**
  * @brief  CeRadar模块操作对象定义
  */
const CeRadarOp ceRadarOp = {ceRadar_initial, ceRadar_getDistance};

#ifdef __cplusplus
 }
#endif //__cplusplus

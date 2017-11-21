/**
  ******************************************************************************
  * @file    CeDmdMc.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeDmdMc模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeDmdMc.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  CeDmdMc模块初始化
  * @param  ceDmdTb:CeDmdMc属性对象
  * @param  cePwm:CeDmdMc模块使用的Pwm资源号
  * @param  ceTg:CeDmdMc模块使用的Tg资源号
  * @return 系统状态码，可能的值:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdMc_initial(CeDmdMc* ceDmdMc, CE_RESOURCE cePwm, CE_RESOURCE ceTg)
{
    ceDmdMc->duty = CE_PWM_MIN_CYCLE_NS;
    ceDmdMc->cePwm.ceResource = cePwm;
    ceDmdMc->cePwm.cycleNs = CE_DMD_MC_PWM_CYCLE_NS;
    ceDmdMc->cePwm.dutyNs = CE_PWM_MIN_CYCLE_NS;  //注意要和上面的ceDmdMc->duty保持一致，直接用宏，效率较高
    cePwmOp.initial(&(ceDmdMc->cePwm));
    cePwmOp.resetGpioBit(&(ceDmdMc->cePwm));      //设置Pwm为低电平，防止不确定的电平导致意外

    ceDmdMc->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceDmdMc->ceTg), CE_GPIO_MODE_IPU, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    //ceGpioOp.resetBit(&(ceDmdMc->ceTg));        //FS，H桥的故障状态，开漏低电平有效，只设置模式不去操作此Gpio口
    ceGpioOp.resetBit(&(ceDmdMc->ceTg));          //IN1，当IN1为1时，OUT1为高，以此来控制转动方向
    ceGpioOp.resetBit(&(ceDmdMc->ceTg));          //IN2，当IN2为1时，OUT2为高，以此来控制转动方向
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  输出打开
  * @param  ceDmdMc:CeDmdMc属性对象
  * @return None
  */
void ceDmdMc_setOn(CeDmdMc* ceDmdMc)
{
    cePwmOp.start(&(ceDmdMc->cePwm));
}

/**
  * @brief  调整电机驱动强度，可在输出中进行调整
  * @param  ceDmdMc:CeDmdMc属性对象
  * @param  driveStrength:电机驱动的强度，范围0-10000
  * @return None
  */
void ceDmdMc_setDriveStrength(CeDmdMc* ceDmdMc, uint16 driveStrength)
{
    uint32 duty = ((uint64)driveStrength * CE_DMD_MC_PWM_CYCLE_NS) / 10000;

    if (duty > CE_DMD_MC_PWM_CYCLE_NS)
    {
        duty = CE_DMD_MC_PWM_CYCLE_NS;
    }
    else
    {
        if (duty < CE_PWM_MIN_CYCLE_NS)
        {
            duty = CE_PWM_MIN_CYCLE_NS;
        }
    }
    ceDmdMc->duty = duty;
    ceDmdMc->cePwm.dutyNs = duty;
    cePwmOp.updata(&(ceDmdMc->cePwm));
}

/**
  * @brief  设置电机的转动方向
  * @param  ceDmdMc:CeDmdMc属性对象
  * @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向
  * @return None
  */
void ceDmdMc_setDirection(CeDmdMc* ceDmdMc, uint8 direction)
{
    if (direction == 0x00)
    {
        ceGpioOp.resetBit(&(ceDmdMc->ceTg));
        ceGpioOp.setBit(&(ceDmdMc->ceTg));
    }
    else
    {
        ceGpioOp.setBit(&(ceDmdMc->ceTg));
        ceGpioOp.resetBit(&(ceDmdMc->ceTg));
    }
}

/**
  * @brief  输出关闭
  * @param  ceDmdMc:CeDmdMc属性对象
  * @return None
  */
void ceDmdMc_setOff(CeDmdMc* ceDmdMc)
{
    cePwmOp.stop(&(ceDmdMc->cePwm));
    cePwmOp.resetGpioBit(&(ceDmdMc->cePwm));
    ceGpioOp.resetBit(&(ceDmdMc->ceTg));
    ceGpioOp.resetBit(&(ceDmdMc->ceTg));
}

const CeDmdMcOp ceDmdMcOp = {ceDmdMc_initial, ceDmdMc_setOn, ceDmdMc_setDriveStrength, ceDmdMc_setDirection, ceDmdMc_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeDmdTb.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeDmdTb模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeDmdTb.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  CeDmdTb模块初始化第一个通道。第一个通道可以单独使用，第二个通道不可以脱离第一个通道单独使用！
  * @param  ceDmdTb:CeDmdTb属性对象
  * @param  cePwm1:CeDmdTb模块第一个通道使用的Pwm资源号
  * @param  ceTg1:CeDmdTb模块第一个通道使用的Tg资源号
  * @return 系统状态码，可能的值:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdTb_initialCh1(CeDmdTb* ceDmdTb, CE_RESOURCE cePwm1, CE_RESOURCE ceTg1)
{
    ceDmdTb->duty1 = CE_PWM_MIN_CYCLE_NS;
    ceDmdTb->cePwm1.ceResource = cePwm1;
    ceDmdTb->cePwm1.cycleNs = CE_DMD_TB_PWM1_CYCLE_NS;
    ceDmdTb->cePwm1.dutyNs = CE_PWM_MIN_CYCLE_NS;//注意要和上面的ceDmdMc->duty保持一致，直接用宏，效率较高
    cePwmOp.initial(&(ceDmdTb->cePwm1));
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm1));//设置Pwm为低电平，防止不确定的电平导致意外

    ceDmdTb->ceTg1.ceResource = ceTg1;
    ceTgOp.initial(&(ceDmdTb->ceTg1), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.setBit(&(ceDmdTb->ceTg1));//TB6612FNG的STBY(StandBy)为低时芯片处于待机状态，为高处于工作状态。所以此引脚为高芯片才能正常工作！
    ceGpioOp.resetBit(&(ceDmdTb->ceTg1));//AIN1
    ceGpioOp.resetBit(&(ceDmdTb->ceTg1));//AIN2
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeDmdTb模块初始化第二个通道。第一个通道可以单独使用，第二个通道不可以脱离第一个通道单独使用！
  * @param  ceDmdTb:CeDmdTb属性对象
  * @param  cePwm2:CeDmdTb模块第二个通道使用的Pwm资源号
  * @param  ceTg2:CeDmdTb模块第二个通道使用的Tg资源号
  * @return 系统状态码，可能的值:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdTb_initialCh2(CeDmdTb* ceDmdTb, CE_RESOURCE cePwm2, CE_RESOURCE ceTg2)
{
    ceDmdTb->duty2 = CE_PWM_MIN_CYCLE_NS;
    ceDmdTb->cePwm2.ceResource = cePwm2;
    ceDmdTb->cePwm2.cycleNs = CE_DMD_TB_PWM2_CYCLE_NS;
    ceDmdTb->cePwm2.dutyNs = CE_PWM_MIN_CYCLE_NS;//注意要和上面的ceDmdMc->duty保持一致，直接用宏，效率较高
    cePwmOp.initial(&(ceDmdTb->cePwm2));
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm2));//设置Pwm为低电平，防止不确定的电平导致意外

    ceDmdTb->ceTg2.ceResource = ceTg2;
    ceTgOp.initial(&(ceDmdTb->ceTg2), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdTb->ceTg2));//未使用
    ceGpioOp.resetBit(&(ceDmdTb->ceTg2));//BIN1
    ceGpioOp.resetBit(&(ceDmdTb->ceTg2));//BIN2
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  第一个通道输出打开。在此操作前必须要设置转动方向，如果是刹车后可以不用设置转动方向，转动方向则保持为刹车前的转动方向。
  * @param  ceDmdTb:CeDmdTb属性对象
  * @return None
  */
void ceDmdTb_setCh1On(CeDmdTb* ceDmdTb)
{
    cePwmOp.start(&(ceDmdTb->cePwm1));
}

/**
  * @brief  第二个通道输出打开。在此操作前必须要设置转动方向，如果是刹车后可以不用设置转动方向，转动方向则保持为刹车前的转动方向。
  * @param  ceDmdTb:CeDmdTb属性对象
  * @return None
  */
void ceDmdTb_setCh2On(CeDmdTb* ceDmdTb)
{
    cePwmOp.start(&(ceDmdTb->cePwm2));
}

/**
  * @brief  调整第一个通道电机驱动强度
  * @param  ceDmdTb:CeDmdTb属性对象
  * @param  driveStrength:电机驱动的强度，范围0-10000
  * @return None
  */
void ceDmdTb_setCh1DriveStrength(CeDmdTb* ceDmdTb, uint16 driveStrength)
{
    uint32 duty = ((uint64)driveStrength * CE_DMD_TB_PWM1_CYCLE_NS) / 10000;
    if (duty > CE_DMD_TB_PWM1_CYCLE_NS)
    {
        duty = CE_DMD_TB_PWM1_CYCLE_NS;
    }
    else
    {
        if (duty < CE_PWM_MIN_CYCLE_NS)
        {
            duty = CE_PWM_MIN_CYCLE_NS;
        }
    }
    ceDmdTb->duty1 = duty;
    ceDmdTb->cePwm1.dutyNs = duty;
    cePwmOp.updata(&(ceDmdTb->cePwm1));
}

/**
  * @brief  调整第二个通道电机驱动强度
  * @param  ceDmdTb:CeDmdTb属性对象
  * @param  driveStrength:电机驱动的强度，范围0-10000
  * @return None
  */
void ceDmdTb_setCh2DriveStrength(CeDmdTb* ceDmdTb, uint16 driveStrength)
{
    uint32 duty = ((uint64)driveStrength * CE_DMD_TB_PWM2_CYCLE_NS) / 10000;
    if (duty > CE_DMD_TB_PWM2_CYCLE_NS)
    {
        duty = CE_DMD_TB_PWM2_CYCLE_NS;
    }
    else
    {
        if (duty < CE_PWM_MIN_CYCLE_NS)
        {
            duty = CE_PWM_MIN_CYCLE_NS;
        }
    }
    ceDmdTb->duty2 = duty;
    ceDmdTb->cePwm2.dutyNs = duty;
    cePwmOp.updata(&(ceDmdTb->cePwm2));
}

/**
  * @brief  设置第一个通道电机的转动方向
  * @param  ceDmdTb:CeDmdTb属性对象
  * @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向
  * @return None
  */
void ceDmdTb_setCh1Direction(CeDmdTb* ceDmdTb, uint8 direction)
{
    if(direction == 0x00)
    {
        ceGpioOp.resetBit(&(ceDmdTb->ceTg1));
        ceGpioOp.setBit(&(ceDmdTb->ceTg1));
    }
    else
    {
        ceGpioOp.setBit(&(ceDmdTb->ceTg1));
        ceGpioOp.resetBit(&(ceDmdTb->ceTg1));
    }
}

/**
  * @brief  设置第二个通道电机的转动方向
  * @param  ceDmdTb:CeDmdTb属性对象
  * @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向
  * @return None
  */
void ceDmdTb_setCh2Direction(CeDmdTb* ceDmdTb, uint8 direction)
{
    if(direction == 0x00)
    {
        ceGpioOp.resetBit(&(ceDmdTb->ceTg2));
        ceGpioOp.setBit(&(ceDmdTb->ceTg2));
    }
    else
    {
        ceGpioOp.setBit(&(ceDmdTb->ceTg2));
        ceGpioOp.resetBit(&(ceDmdTb->ceTg2));
    }
}

/**
  * @brief  第一个通道刹车，输出暂停
  * @param  ceDmdTb:CeDmdTb属性对象
  * @return None
  */
void ceDmdTb_ch1Brake(CeDmdTb* ceDmdTb)
{
    cePwmOp.stop(&(ceDmdTb->cePwm1));//只要Pwm为低，模式状态就为制动
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm1));//Pwm停止后，强制设置Pwm为低电平！
}

/**
  * @brief  第二个通道刹车，输出暂停
  * @param  ceDmdTb:CeDmdTb属性对象
  * @return None
  */
void ceDmdTb_ch2Brake(CeDmdTb* ceDmdTb)
{
    cePwmOp.stop(&(ceDmdTb->cePwm2));//只要Pwm为低，模式状态就为制动
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm2));//Pwm停止后，强制设置Pwm为低电平！
}

/**
  * @brief  第一个通道输出关闭
  * @param  ceDmdTb:CeDmdTb属性对象
  * @return None
  */
void ceDmdTb_setCh1Off(CeDmdTb* ceDmdTb)
{
    cePwmOp.stop(&(ceDmdTb->cePwm1));
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm1));
    ceGpioOp.resetBit(&(ceDmdTb->ceTg1));
    ceGpioOp.resetBit(&(ceDmdTb->ceTg1));
}

/**
  * @brief  第一个通道输出关闭
  * @param  ceDmdTb:CeDmdTb属性对象
  * @return None
  */
void ceDmdTb_setCh2Off(CeDmdTb* ceDmdTb)
{
    cePwmOp.stop(&(ceDmdTb->cePwm2));
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm1));
    ceGpioOp.resetBit(&(ceDmdTb->ceTg2));
    ceGpioOp.resetBit(&(ceDmdTb->ceTg2));
}

const CeDmdTbOp ceDmdTbOp = { ceDmdTb_initialCh1, ceDmdTb_initialCh2, ceDmdTb_setCh1On, ceDmdTb_setCh2On, ceDmdTb_setCh1DriveStrength, ceDmdTb_setCh2DriveStrength,
                                    ceDmdTb_setCh1Direction, ceDmdTb_setCh2Direction, ceDmdTb_ch1Brake, ceDmdTb_ch2Brake, ceDmdTb_setCh1Off, ceDmdTb_setCh2Off};

#ifdef __cplusplus
 }
#endif //__cplusplus

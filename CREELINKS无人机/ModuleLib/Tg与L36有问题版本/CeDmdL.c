/**
  ******************************************************************************
  * @file    CeDmdL.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeDmdL模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)芯片型号L289N，可以作为2路直流电机驱动或者一路步进电机驱动。
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeDmdL.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#ifdef CE_DMD_L_USE_TO_SETP_MOTOR       /*!< 是否将模块用于步进电机*/

/**
  * @brief  CeDmdL模块用作步进电机初始化
  * @param  ceDmdL:CeDmdL属性对象指针
  * @param  ceTg1:CeDmdL模块用作步进电机的第一个Tg资源号
  * @param  ceTg2:CeDmdL模块用作步进电机的第二个Tg资源号
  * @return 系统状态码，可能的值:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdL_initial(CeDmdL* ceDmdL, CE_RESOURCE ceTg1, CE_RESOURCE ceTg2)
{
    ceDmdL->around = 0x00;
    ceDmdL->status = 0x00;
    ceDmdL->ceTg1.ceResource = ceTg1;
    ceTgOp.initial(&(ceDmdL->ceTg1), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN1
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN2
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//未使用，给低电平

    ceDmdL->ceTg2.ceResource = ceTg2;
    ceTgOp.initial(&(ceDmdL->ceTg2), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN3
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN4
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//未使用，给低电平
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  模块用作步进电机，输出打开
  * @param  ceDmdL:CeDmdL属性对象指针
  * @return None
  */
void ceDmdL_setOn(CeDmdL* ceDmdL)
{
    if ((ceDmdL->status & 0x01) == 0x01)
    {
        ceGpioOp.setBit(&(ceDmdL->ceTg1));//IN1
    }
    else
    {
        ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN1
    }

    if ((ceDmdL->status & 0x02) == 0x02)
    {
        ceGpioOp.setBit(&(ceDmdL->ceTg1));//IN1
    }
    else
    {
        ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN1
    }

    if ((ceDmdL->status & 0x04) == 0x04)
    {
        ceGpioOp.setBit(&(ceDmdL->ceTg2));//IN1
    }
    else
    {
        ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN1
    }

    if ((ceDmdL->status & 0x05) == 0x05)
    {
        ceGpioOp.setBit(&(ceDmdL->ceTg2));//IN1
    }
    else
    {
        ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN1
    }
}

/**
  * @brief  模块用作步进电机，输出关闭
  * @param  ceDmdL:CeDmdL属性对象指针
  * @return None
  */
void ceDmdL_setOff(CeDmdL* ceDmdL)
{
    ceDmdL->status = ceTgOp.getGpio0Bit(&(ceDmdL->ceTg1)) | (ceTgOp.getGpio1Bit(&(ceDmdL->ceTg1)) << 1) | (ceTgOp.getGpio0Bit(&(ceDmdL->ceTg2)) << 2) | (ceTgOp.getGpio1Bit(&(ceDmdL->ceTg2)) << 3);
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
}

/**
  * @brief  模块用作步进电机，前进一步
  * @param  ceDmdL:CeDmdL属性对象指针
  * @return None
  */
void ceDmdL_stepForward(CeDmdL* ceDmdL)
{
    if (ceDmdL->setpMode == CE_DMD_L_SINGLE_4_SHOOT)
    {
        switch (ceDmdL->around)
        {
        case 3:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 2:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 1:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 0:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        }
        ceDmdL->around++;
        if (ceDmdL->around >= 0x04)
        {
            ceDmdL->around = 0x00;
        }
    }
    else if (ceDmdL->setpMode == CE_DMD_L_DOUBLE_4_SHOOT)
    {
        switch (ceDmdL->around)
        {
        case 3:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        case 2:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 1:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 0:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        }
        ceDmdL->around++;
        if (ceDmdL->around >= 0x04)
        {
            ceDmdL->around = 0x00;
        }
    }
    else
    {
        switch (ceDmdL->around)
        {
        case 7:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        case 6:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 5:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 4:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 3:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 2:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 1:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        case 0:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        }
        ceDmdL->around++;
        if (ceDmdL->around >= 0x08)
        {
            ceDmdL->around = 0x00;
        }
    }
}

/**
  * @brief  步进电机的运行方式
  * @param  ceDmdL:CeDmdL属性对象指针
  * @return None
*/
void ceDmdL_setStepMode(CeDmdL* ceDmdL, CE_DMD_L_STEP_MODE ceDmdLStepMode)
{
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
    ceDmdL->around = 0;
    ceDmdL->setpMode = ceDmdLStepMode;
}

/**
  * @brief  模块用作步进电机，后退一步
  * @param  ceDmdL:CeDmdL属性对象指针
  * @return None
  */
void ceDmdL_stepBackward(CeDmdL* ceDmdL)
{
    if (ceDmdL->setpMode == CE_DMD_L_SINGLE_4_SHOOT)
    {
        switch(ceDmdL->around)
        {
        case 0:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 1:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 2:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 3:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        }
        ceDmdL->around++;
        if (ceDmdL->around >= 0x04)
        {
            ceDmdL->around = 0x00;
        }
    }
    else if (ceDmdL->setpMode == CE_DMD_L_DOUBLE_4_SHOOT)
    {
        switch (ceDmdL->around)
        {
        case 0:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        case 1:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 2:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 3:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        }
        ceDmdL->around++;
        if (ceDmdL->around >= 0x04)
        {
            ceDmdL->around = 0x00;
        }
    }
    else
    {
        switch (ceDmdL->around)
        {
        case 0:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        case 1:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 2:
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 3:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 4:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 5:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            break;
        case 6:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        case 7:
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg1));
            ceGpioOp.resetBit(&(ceDmdL->ceTg2));
            ceGpioOp.setBit(&(ceDmdL->ceTg2));
            break;
        }
        ceDmdL->around++;
        if (ceDmdL->around >= 0x08)
        {
            ceDmdL->around = 0x00;
        }
    }
}

const CeDmdLOp ceDmdLOp = { ceDmdL_initial,ceDmdL_setStepMode , ceDmdL_setOn, ceDmdL_setOff, ceDmdL_stepForward, ceDmdL_stepBackward};


#else //CE_DMD_L_USE_TO_SETP_MOTOR

/**
  * @brief  CeDmdL模块初始化第一个通道。
  * @param  ceDmdL:CeDmdL属性对象
  * @param  cePwm1:CeDmdL模块第一个通道使用的Pwm资源号
  * @param  ceTg1:CeDmdL模块第一个通道使用的Tg资源号
  * @return 系统状态码，可能的值:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdL_initialCh1(CeDmdL* ceDmdL, CE_RESOURCE cePwm1, CE_RESOURCE ceTg1)
{
    ceDmdL->duty1 = CE_PWM_MIN_CYCLE_NS;
    ceDmdL->cePwm1.ceResource = cePwm1;
    ceDmdL->cePwm1.cycleNs = CE_DMD_L_PWM1_CYCLE_NS;
    ceDmdL->cePwm1.dutyNs = CE_PWM_MIN_CYCLE_NS;//注意要和上面的ceDmdMc->duty保持一致，直接用宏，效率较高
    cePwmOp.initial(&(ceDmdL->cePwm1));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm1));//设置Pwm为低电平，防止不确定的电平导致意外

    ceDmdL->ceTg1.ceResource = ceTg1;
    ceTgOp.initial(&(ceDmdL->ceTg1), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN1
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN2
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//未使用，给低电平
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeDmdL模块初始化第二个通道。
  * @param  ceDmdL:CeDmdL属性对象
  * @param  cePwm2:CeDmdL模块第二个通道使用的Pwm资源号
  * @param  ceTg2:CeDmdL模块第二个通道使用的Tg资源号
  * @return 系统状态码，可能的值:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdL_initialCh2(CeDmdL* ceDmdL, CE_RESOURCE cePwm2, CE_RESOURCE ceTg2)
{
    ceDmdL->duty2 = CE_PWM_MIN_CYCLE_NS;
    ceDmdL->cePwm2.ceResource = cePwm2;
    ceDmdL->cePwm2.cycleNs = CE_DMD_L_PWM2_CYCLE_NS;
    ceDmdL->cePwm2.dutyNs = CE_PWM_MIN_CYCLE_NS;//注意要和上面的ceDmdMc->duty保持一致，直接用宏，效率较高
    cePwmOp.initial(&(ceDmdL->cePwm2));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm2));//设置Pwm为低电平，防止不确定的电平导致意外

    ceDmdL->ceTg2.ceResource = ceTg2;
    ceTgOp.initial(&(ceDmdL->ceTg2), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN3
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN4
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//未使用，给低电平
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  第一个通道输出打开。在此操作前必须要设置转动方向。
  * @param  ceDmdL:CeDmdL属性对象
  * @return None
  */
void ceDmdL_setCh1On(CeDmdL* ceDmdL)
{
    cePwmOp.start(&(ceDmdL->cePwm1));
}

/**
  * @brief  第二个通道输出打开。在此操作前必须要设置转动方向。
  * @param  ceDmdL:CeDmdL属性对象
  * @return None
  */
void ceDmdL_setCh2On(CeDmdL* ceDmdL)
{
    cePwmOp.start(&(ceDmdL->cePwm2));
}

/**
  * @brief  调整第一个通道电机驱动强度
  * @param  ceDmdL:CeDmdL属性对象
  * @param  driveStrength:电机驱动的强度，范围0-10000
  * @return None
  */
void ceDmdL_setCh1DriveStrength(CeDmdL* ceDmdL, uint16 driveStrength)
{
    uint32 duty = ((uint64)driveStrength * CE_DMD_L_PWM1_CYCLE_NS) / 10000;
    if (duty > CE_DMD_L_PWM1_CYCLE_NS)
    {
        duty = CE_DMD_L_PWM1_CYCLE_NS;
    }
    else
    {
        if (duty < CE_PWM_MIN_CYCLE_NS)
        {
            duty = CE_PWM_MIN_CYCLE_NS;
        }
    }
    ceDmdL->duty1 = duty;
    ceDmdL->cePwm1.dutyNs = duty;
    cePwmOp.updata(&(ceDmdL->cePwm1));
}

/**
  * @brief  调整第二个通道电机驱动强度
  * @param  ceDmdL:CeDmdL属性对象
  * @param  driveStrength:电机驱动的强度，范围0-10000
  * @return None
  */
void ceDmdL_setCh2DriveStrength(CeDmdL* ceDmdL, uint16 driveStrength)
{
    uint32 duty = ((uint64)driveStrength * CE_DMD_L_PWM2_CYCLE_NS) / 10000;
    if (duty > CE_DMD_L_PWM2_CYCLE_NS)
    {
        duty = CE_DMD_L_PWM2_CYCLE_NS;
    }
    else
    {
        if (duty < CE_PWM_MIN_CYCLE_NS)
        {
            duty = CE_PWM_MIN_CYCLE_NS;
        }
    }
    ceDmdL->duty2 = duty;
    ceDmdL->cePwm2.dutyNs = duty;
    cePwmOp.updata(&(ceDmdL->cePwm2));
}

/**
  * @brief  设置第一个通道电机的转动方向
  * @param  ceDmdL:CeDmdL属性对象
  * @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向
  * @return None
  */
void ceDmdL_setCh1Direction(CeDmdL* ceDmdL, uint8 direction)
{
    if(direction == 0x00)
    {
        ceGpioOp.resetBit(&(ceDmdL->ceTg1));
        ceGpioOp.setBit(&(ceDmdL->ceTg1));
    }
    else
    {
        ceGpioOp.setBit(&(ceDmdL->ceTg1));
        ceGpioOp.resetBit(&(ceDmdL->ceTg1));
    }
}

/**
  * @brief  设置第二个通道电机的转动方向
  * @param  ceDmdL:CeDmdL属性对象
  * @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向
  * @return None
  */
void ceDmdL_setCh2Direction(CeDmdL* ceDmdL, uint8 direction)
{
    if(direction == 0x00)
    {
        ceGpioOp.resetBit(&(ceDmdL->ceTg2));
        ceGpioOp.setBit(&(ceDmdL->ceTg2));
    }
    else
    {
        ceGpioOp.setBit(&(ceDmdL->ceTg2));
        ceGpioOp.resetBit(&(ceDmdL->ceTg2));
    }
}

/**
  * @brief  第一个通道刹车，而后进行输出关闭操作。
  * @param  ceDmdL:CeDmdL属性对象
  * @return None
  */
void ceDmdL_ch1Brake(CeDmdL* ceDmdL)
{
    ceGpioOp.setBit(&(ceDmdL->ceTg1));//IN1和IN2都为高，即电机的两端接通，则电机惯性转动产生的电动势将被短路，形成阻碍运动的感应电流，行成“刹车”作用。
    ceGpioOp.setBit(&(ceDmdL->ceTg1));
    ceSystemOp.delayNs(100);
    cePwmOp.stop(&(ceDmdL->cePwm1));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm1));//Pwm停止后，强制设置Pwm低电平！
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
}

/**
  * @brief  第二个通道刹车，而后进行输出关闭操作。
  * @param  ceDmdL:CeDmdL属性对象
  * @return None
  */
void ceDmdL_ch2Brake(CeDmdL* ceDmdL)
{
    ceGpioOp.setBit(&(ceDmdL->ceTg2));//IN3和IN4都为高，即电机的两端接通，则电机惯性转动产生的电动势将被短路，形成阻碍运动的感应电流，行成“刹车”作用。
    ceGpioOp.setBit(&(ceDmdL->ceTg2));
    ceSystemOp.delayNs(100);
    cePwmOp.stop(&(ceDmdL->cePwm2));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm2));//Pwm停止后，强制设置Pwm为低电平！
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
}

/**
  * @brief  第一个通道输出关闭
  * @param  ceDmdL:CeDmdL属性对象
  * @return None
  */
void ceDmdL_setCh1Off(CeDmdL* ceDmdL)
{
    cePwmOp.stop(&(ceDmdL->cePwm1));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm1));
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
}

/**
  * @brief  第一个通道输出关闭
  * @param  ceDmdL:CeDmdL属性对象
  * @return None
  */
void ceDmdL_setCh2Off(CeDmdL* ceDmdL)
{
    cePwmOp.stop(&(ceDmdL->cePwm2));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm2));
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
}

const CeDmdLOp ceDmdLOp = { ceDmdL_initialCh1, ceDmdL_initialCh2, ceDmdL_setCh1On, ceDmdL_setCh2On, ceDmdL_setCh1DriveStrength, ceDmdL_setCh2DriveStrength,
                                    ceDmdL_setCh1Direction, ceDmdL_setCh2Direction, ceDmdL_ch1Brake, ceDmdL_ch2Brake, ceDmdL_setCh1Off, ceDmdL_setCh2Off};

#endif //CE_DMD_L_USE_TO_SETP_MOTOR

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeLed3C.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeLed3C模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeLed3C.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  CeLed3C模块使用Gpio进行初始化
  * @param  ceLed3C:CeLed3C属性对象指针
  * @param  ceGpioRed:CeLed3C模块使用的红色LED的资源号
  * @param  ceGpioGreen:CeLed3C模块使用的绿色LED的资源号
  * @param  ceGpioBlue:CeLed3C模块使用的蓝色LED的资源号
  * @return 系统状态码
  */
CE_STATUS ceLed3C_initialByGpio(CeLed3C* ceLed3C, CE_RESOURCE ceGpioRed, CE_RESOURCE ceGpioGreen, CE_RESOURCE ceGpioBlue)
{
    ceLed3C->ceTg.ceResource = CE_NULL_RESOURCE;
    ceLed3C->ceTg.ceResource0 = ceGpioRed;
    ceLed3C->ceTg.ceResource1 = ceGpioGreen;
    ceLed3C->ceTg.ceResource2 = ceGpioBlue;
    ceTgOp.initial(&(ceLed3C->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.setBit(&(ceLed3C->ceTg));
    ceGpioOp.setBit(&(ceLed3C->ceTg));
    ceGpioOp.setBit(&(ceLed3C->ceTg));
    ceLed3C->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeLed3C模块使用Tg进行初始化
  * @param  ceLed3C:CeLed3C属性对象指针
  * @param  ceTg:CeLed3C模块使用的Tg的资源号
  * @return 系统状态码
  */
CE_STATUS ceLed3C_initialByTg(CeLed3C* ceLed3C,CE_RESOURCE ceTg)
{
    ceLed3C->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceLed3C->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.setBit(&(ceLed3C->ceTg));
    ceGpioOp.setBit(&(ceLed3C->ceTg));
    ceGpioOp.setBit(&(ceLed3C->ceTg));
    ceLed3C->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
 * @brief   设置Led的颜色
 * @param   ceLed3C:CeLed3C属性对象指针
 * @param   colorStatus:欲设置的颜色
 */
void ceLed3C_setColor(CeLed3C* ceLed3C, uint16 color)
{
    if(ceLed3C->workMode == 0x00)
    {
        switch (color)
        {
        case CE_LED_3C_RED:
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            break;
        case CE_LED_3C_GREEN:
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            break;
        case CE_LED_3C_BLUE:
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            break;
        case CE_LED_3C_YELLOW:
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            break;
        case CE_LED_3C_CYAN:
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            break;
        case CE_LED_3C_PURPLE:
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            ceGpioOp.resetBit(&(ceLed3C->ceTg));
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            break;
        case CE_LED_3C_WHITE:
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            ceGpioOp.setBit(&(ceLed3C->ceTg));
            break;
        default:
            break;
        }
        ceLed3C->led3CColor = color;

    }
    else
    {
        uint16 R = (color>> 11)& 0x001F;
        uint16 G = (color>>5)&0x003F;
        uint16 B = (color)& 0x001F;
        ceLed3C->cePwmRed.dutyNs = (ceLed3C->cePwmRed.cycleNs/0x001F )*R;
        ceLed3C->cePwmGreen.dutyNs = (ceLed3C->cePwmGreen.cycleNs/0x003F )*G;
        ceLed3C->cePwmBlue.dutyNs = (ceLed3C->cePwmBlue.cycleNs/0x001F )*B;
        if(ceLed3C->cePwmRed.dutyNs > ceLed3C->cePwmRed.cycleNs)
        {
            ceLed3C->cePwmRed.dutyNs = ceLed3C->cePwmRed.cycleNs-1;
        }
        else if(ceLed3C->cePwmRed.dutyNs < CE_PWM_MIN_CYCLE_NS)
        {
            ceLed3C->cePwmRed.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
        }

        if(ceLed3C->cePwmGreen.dutyNs > ceLed3C->cePwmGreen.cycleNs)
        {
            ceLed3C->cePwmGreen.dutyNs = ceLed3C->cePwmGreen.cycleNs-1;
        }
        else if(ceLed3C->cePwmGreen.dutyNs < CE_PWM_MIN_CYCLE_NS)
        {
            ceLed3C->cePwmGreen.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
        }

        if(ceLed3C->cePwmBlue.dutyNs > ceLed3C->cePwmBlue.cycleNs)
        {
            ceLed3C->cePwmBlue.dutyNs = ceLed3C->cePwmBlue.cycleNs-1;
        }
        else if(ceLed3C->cePwmBlue.dutyNs < CE_PWM_MIN_CYCLE_NS)
        {
            ceLed3C->cePwmBlue.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
        }

        cePwmOp.updata(&(ceLed3C->cePwmRed));
        cePwmOp.updata(&(ceLed3C->cePwmGreen));
        cePwmOp.updata(&(ceLed3C->cePwmBlue));
    }
}

/**
  * @brief   设置Led状态为开
  * @param   ceLed3C:CeLed3C属性对象指针
  */
void ceLed3C_setOn(CeLed3C* ceLed3C)
{
    ceLed3C_setColor(ceLed3C, ceLed3C->led3CColor);
}

/**
  * @brief   设置Led状态为关
  * @param   ceLed3C:CeLed3C属性对象指针
  */
void ceLed3C_setOff(CeLed3C* ceLed3C)
{
    if(ceLed3C->workMode == 0x00)
    {
    ceGpioOp.resetBit(&(ceLed3C->ceTg));
    ceGpioOp.resetBit(&(ceLed3C->ceTg));
    ceGpioOp.resetBit(&(ceLed3C->ceTg));
    }
    else
    {
        ceLed3C_setColor(ceLed3C, 0x0000);
    }

}

/**
  * @brief CeLed3C模块使用3个Gpio口来完成初始化
  * @param ceLed3C:CeLed3C属性对象指针
  * @param cePwmRed:CeLed3C模块使用的红色LED的资源号
  * @param cePwmGreen:CeLed3C模块使用的绿色LED的资源号
  * @param cePwmBlue:CeLed3C模块使用的蓝色LED的资源号
  */
#ifdef CE_LED_3C_ALL_COLOR
CE_STATUS ceLed3C_initialByThreePwm(CeLed3C* ceLed3C, CE_RESOURCE cePwmRed, CE_RESOURCE cePwmGreen, CE_RESOURCE cePwmBlue)
{
    ceLed3C->cePwmRed.ceResource = cePwmRed;
    ceLed3C->cePwmRed.cycleNs = 6000000;
    ceLed3C->cePwmRed.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
    //ceLed3C->cePwmRed.dutyNs = 6000000/2;
    cePwmOp.initial(&(ceLed3C->cePwmRed));
    cePwmOp.start(&(ceLed3C->cePwmRed));

    ceLed3C->cePwmGreen.ceResource = cePwmGreen;
    ceLed3C->cePwmGreen.cycleNs = 6000000;
    ceLed3C->cePwmGreen.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
    //ceLed3C->cePwmGreen.dutyNs = 6000000/2;
    cePwmOp.initial(&(ceLed3C->cePwmGreen));
    cePwmOp.start(&(ceLed3C->cePwmGreen));

    ceLed3C->cePwmBlue.ceResource = cePwmBlue;
    ceLed3C->cePwmBlue.cycleNs = 6000000;
    ceLed3C->cePwmBlue.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
    //ceLed3C->cePwmBlue.dutyNs = 6000000/2;
    cePwmOp.initial(&(ceLed3C->cePwmBlue));
    cePwmOp.start(&(ceLed3C->cePwmBlue));

    ceLed3C->workMode = 0x01;
    return CE_STATUS_SUCCESS;
}
#endif

#ifdef CE_LED_3C_ALL_COLOR
const CeLed3COp ceLed3COp = {ceLed3C_initialByGpio, ceLed3C_initialByThreePwm, ceLed3C_initialByTg, ceLed3C_setColor, ceLed3C_setOn, ceLed3C_setOff};
#else
const CeLed3COp ceLed3COp = {ceLed3C_initialByGpio, ceLed3C_initialByTg, ceLed3C_setColor, ceLed3C_setOn, ceLed3C_setOff};
#endif

#ifdef __cplusplus
 }
#endif //__cplusplus

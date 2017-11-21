/**
  ******************************************************************************
  * @file    CeLedH3C.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeLedH3Cģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeLedH3C.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
 * @brief   CeLedH3Cģ��ʹ��Gpio���г�ʼ��
 * @param   ceLedH3C:CeLedH3C���Զ���ָ��
 * @param   ceGpioRed:CeLedH3Cģ��ʹ�õĺ�ɫLED����Դ��
 * @param   ceGpioGreen:CeLedH3Cģ��ʹ�õ���ɫLED����Դ��
 * @param   ceGpioBlue:CeLedH3Cģ��ʹ�õ���ɫLED����Դ��
 * @return  ϵͳ״̬��
 */
CE_STATUS ceLedH3C_initialByGpio(CeLedH3C* ceLedH3C, CE_RESOURCE ceGpioRed, CE_RESOURCE ceGpioGreen, CE_RESOURCE ceGpioBlue)
{
    ceLedH3C->ceTg.ceResource = CE_NULL_RESOURCE;
    ceLedH3C->ceTg.ceResource0 = ceGpioRed;
    ceLedH3C->ceTg.ceResource1 = ceGpioGreen;
    ceLedH3C->ceTg.ceResource2 = ceGpioBlue;
    ceTgOp.initial(&(ceLedH3C->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.setBit(&(ceLedH3C->ceTg));
    ceGpioOp.setBit(&(ceLedH3C->ceTg));
    ceGpioOp.setBit(&(ceLedH3C->ceTg));
    ceLedH3C->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
 * @brief   CeLedH3Cģ��ʹ��Tg���г�ʼ��
 * @param   ceLedH3C:CeLedH3C���Զ���ָ��
 * @param   ceTg:CeLedH3Cģ��ʹ�õ�Tg����Դ��
 * @return ϵͳ״̬��
 */
CE_STATUS ceLedH3C_initialByTg(CeLedH3C* ceLedH3C,CE_RESOURCE ceTg)
{
    ceLedH3C->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceLedH3C->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.setBit(&(ceLedH3C->ceTg));
    ceGpioOp.setBit(&(ceLedH3C->ceTg));
    ceGpioOp.setBit(&(ceLedH3C->ceTg));
    ceLedH3C->workMode = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
 * @brief   ����Led����ɫ
 * @param   ceLedH3C:CeLedH3C���Զ���ָ��
 * @param   colorStatus:�����õ���ɫ
 */
void ceLedH3C_setColor(CeLedH3C* ceLedH3C, uint16 color)
{
    if(ceLedH3C->workMode == 0x00)
    {
        switch (color)
        {
        case CE_LED_3C_RED:
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            break;
        case CE_LED_3C_GREEN:
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            break;
        case CE_LED_3C_BLUE:
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            break;
        case CE_LED_3C_YELLOW:
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            break;
        case CE_LED_3C_CYAN:
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            break;
        case CE_LED_3C_PURPLE:
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            ceGpioOp.resetBit(&(ceLedH3C->ceTg));
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            break;
        case CE_LED_3C_WHITE:
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            ceGpioOp.setBit(&(ceLedH3C->ceTg));
            break;
        default:
            break;
        }
        ceLedH3C->led3CColor = color;

    }else
    {
        uint16 R = (color>> 11)& 0x001F;
        uint16 G = (color>>5)&0x003F;
        uint16 B = (color)& 0x001F;
        ceLedH3C->cePwmRed.dutyNs = (ceLedH3C->cePwmRed.cycleNs/0x001F )*R;
        ceLedH3C->cePwmGreen.dutyNs = (ceLedH3C->cePwmGreen.cycleNs/0x003F )*G;
        ceLedH3C->cePwmBlue.dutyNs = (ceLedH3C->cePwmBlue.cycleNs/0x001F )*B;
        if(ceLedH3C->cePwmRed.dutyNs > ceLedH3C->cePwmRed.cycleNs)
        {
            ceLedH3C->cePwmRed.dutyNs = ceLedH3C->cePwmRed.cycleNs-1;
        }else if(ceLedH3C->cePwmRed.dutyNs < CE_PWM_MIN_CYCLE_NS)
        {
            ceLedH3C->cePwmRed.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
        }

        if(ceLedH3C->cePwmGreen.dutyNs > ceLedH3C->cePwmGreen.cycleNs)
        {
            ceLedH3C->cePwmGreen.dutyNs = ceLedH3C->cePwmGreen.cycleNs-1;
        }else if(ceLedH3C->cePwmGreen.dutyNs < CE_PWM_MIN_CYCLE_NS)
        {
            ceLedH3C->cePwmGreen.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
        }

        if(ceLedH3C->cePwmBlue.dutyNs > ceLedH3C->cePwmBlue.cycleNs)
        {
            ceLedH3C->cePwmBlue.dutyNs = ceLedH3C->cePwmBlue.cycleNs-1;
        }else if(ceLedH3C->cePwmBlue.dutyNs < CE_PWM_MIN_CYCLE_NS)
        {
            ceLedH3C->cePwmBlue.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
        }

        cePwmOp.updata(&(ceLedH3C->cePwmRed));
        cePwmOp.updata(&(ceLedH3C->cePwmGreen));
        cePwmOp.updata(&(ceLedH3C->cePwmBlue));
    }
}

/**
* @brief   ����Led״̬Ϊ��
* @param   ceLedH3C:CeLedH3C���Զ���ָ��
*/
void ceLedH3C_setOn(CeLedH3C* ceLedH3C)
{
    ceLedH3C_setColor(ceLedH3C, ceLedH3C->led3CColor);
}

/**
  * @brief   ����Led״̬Ϊ��
  * @param   ceLedH3C:CeLedH3C���Զ���ָ��
  */
void ceLedH3C_setOff(CeLedH3C* ceLedH3C)
{
    if(ceLedH3C->workMode == 0x00)
    {
    ceGpioOp.resetBit(&(ceLedH3C->ceTg));
    ceGpioOp.resetBit(&(ceLedH3C->ceTg));
    ceGpioOp.resetBit(&(ceLedH3C->ceTg));
    }else
    {
        ceLedH3C_setColor(ceLedH3C, 0x0000);
    }

}

/**
  * @brief CeLedH3Cģ��ʹ��3��Gpio������ɳ�ʼ��
  * @param ceLedH3C:CeLedH3C���Զ���ָ��
  * @param cePwmRed:CeLedH3Cģ��ʹ�õĺ�ɫLED����Դ��
  * @param cePwmGreen:CeLedH3Cģ��ʹ�õ���ɫLED����Դ��
  * @param cePwmBlue:CeLedH3Cģ��ʹ�õ���ɫLED����Դ��
  */
#ifdef CE_LED_3C_ALL_COLOR
CE_STATUS ceLedH3C_initialByThreePwm(CeLedH3C* ceLedH3C, CE_RESOURCE cePwmRed, CE_RESOURCE cePwmGreen, CE_RESOURCE cePwmBlue)
{
    ceLedH3C->cePwmRed.ceResource = cePwmRed;
    ceLedH3C->cePwmRed.cycleNs = 6000000;
    ceLedH3C->cePwmRed.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
    //ceLedH3C->cePwmRed.dutyNs = 6000000/2;
    cePwmOp.initial(&(ceLedH3C->cePwmRed));
    cePwmOp.start(&(ceLedH3C->cePwmRed));

    ceLedH3C->cePwmGreen.ceResource = cePwmGreen;
    ceLedH3C->cePwmGreen.cycleNs = 6000000;
    ceLedH3C->cePwmGreen.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
    //ceLedH3C->cePwmGreen.dutyNs = 6000000/2;
    cePwmOp.initial(&(ceLedH3C->cePwmGreen));
    cePwmOp.start(&(ceLedH3C->cePwmGreen));

    ceLedH3C->cePwmBlue.ceResource = cePwmBlue;
    ceLedH3C->cePwmBlue.cycleNs = 6000000;
    ceLedH3C->cePwmBlue.dutyNs = CE_PWM_MIN_CYCLE_NS+1;
    //ceLedH3C->cePwmBlue.dutyNs = 6000000/2;
    cePwmOp.initial(&(ceLedH3C->cePwmBlue));
    cePwmOp.start(&(ceLedH3C->cePwmBlue));

    ceLedH3C->workMode = 0x01;
    return CE_STATUS_SUCCESS;
}
#endif

#ifdef CE_LED_3C_ALL_COLOR
const CeLedH3COp ceLedH3COp = {ceLedH3C_initialByGpio, ceLedH3C_initialByThreePwm, ceLedH3C_initialByTg, ceLedH3C_setColor, ceLedH3C_setOn, ceLedH3C_setOff};
#else
const CeLedH3COp ceLedH3COp = {ceLedH3C_initialByGpio, ceLedH3C_initialByTg, ceLedH3C_setColor, ceLedH3C_setOn, ceLedH3C_setOff};
#endif

#ifdef __cplusplus
 }
#endif //__cplusplus

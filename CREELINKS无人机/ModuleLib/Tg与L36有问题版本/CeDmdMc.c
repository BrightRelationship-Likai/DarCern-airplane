/**
  ******************************************************************************
  * @file    CeDmdMc.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeDmdMcģ����������ļ�
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
  * @brief  CeDmdMcģ���ʼ��
  * @param  ceDmdTb:CeDmdMc���Զ���
  * @param  cePwm:CeDmdMcģ��ʹ�õ�Pwm��Դ��
  * @param  ceTg:CeDmdMcģ��ʹ�õ�Tg��Դ��
  * @return ϵͳ״̬�룬���ܵ�ֵ:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdMc_initial(CeDmdMc* ceDmdMc, CE_RESOURCE cePwm, CE_RESOURCE ceTg)
{
    ceDmdMc->duty = CE_PWM_MIN_CYCLE_NS;
    ceDmdMc->cePwm.ceResource = cePwm;
    ceDmdMc->cePwm.cycleNs = CE_DMD_MC_PWM_CYCLE_NS;
    ceDmdMc->cePwm.dutyNs = CE_PWM_MIN_CYCLE_NS;  //ע��Ҫ�������ceDmdMc->duty����һ�£�ֱ���ú꣬Ч�ʽϸ�
    cePwmOp.initial(&(ceDmdMc->cePwm));
    cePwmOp.resetGpioBit(&(ceDmdMc->cePwm));      //����PwmΪ�͵�ƽ����ֹ��ȷ���ĵ�ƽ��������

    ceDmdMc->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceDmdMc->ceTg), CE_GPIO_MODE_IPU, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    //ceGpioOp.resetBit(&(ceDmdMc->ceTg));        //FS��H�ŵĹ���״̬����©�͵�ƽ��Ч��ֻ����ģʽ��ȥ������Gpio��
    ceGpioOp.resetBit(&(ceDmdMc->ceTg));          //IN1����IN1Ϊ1ʱ��OUT1Ϊ�ߣ��Դ�������ת������
    ceGpioOp.resetBit(&(ceDmdMc->ceTg));          //IN2����IN2Ϊ1ʱ��OUT2Ϊ�ߣ��Դ�������ת������
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  �����
  * @param  ceDmdMc:CeDmdMc���Զ���
  * @return None
  */
void ceDmdMc_setOn(CeDmdMc* ceDmdMc)
{
    cePwmOp.start(&(ceDmdMc->cePwm));
}

/**
  * @brief  �����������ǿ�ȣ���������н��е���
  * @param  ceDmdMc:CeDmdMc���Զ���
  * @param  driveStrength:���������ǿ�ȣ���Χ0-10000
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
  * @brief  ���õ����ת������
  * @param  ceDmdMc:CeDmdMc���Զ���
  * @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����
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
  * @brief  ����ر�
  * @param  ceDmdMc:CeDmdMc���Զ���
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

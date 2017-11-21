/**
  ******************************************************************************
  * @file    CeDmdL.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeDmdLģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)оƬ�ͺ�L289N��������Ϊ2·ֱ�������������һ·�������������
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeDmdL.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#ifdef CE_DMD_L_USE_TO_SETP_MOTOR       /*!< �Ƿ�ģ�����ڲ������*/

/**
  * @brief  CeDmdLģ���������������ʼ��
  * @param  ceDmdL:CeDmdL���Զ���ָ��
  * @param  ceTg1:CeDmdLģ��������������ĵ�һ��Tg��Դ��
  * @param  ceTg2:CeDmdLģ��������������ĵڶ���Tg��Դ��
  * @return ϵͳ״̬�룬���ܵ�ֵ:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdL_initial(CeDmdL* ceDmdL, CE_RESOURCE ceTg1, CE_RESOURCE ceTg2)
{
    ceDmdL->around = 0x00;
    ceDmdL->status = 0x00;
    ceDmdL->ceTg1.ceResource = ceTg1;
    ceTgOp.initial(&(ceDmdL->ceTg1), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN1
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN2
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//δʹ�ã����͵�ƽ

    ceDmdL->ceTg2.ceResource = ceTg2;
    ceTgOp.initial(&(ceDmdL->ceTg2), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN3
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN4
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//δʹ�ã����͵�ƽ
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ģ��������������������
  * @param  ceDmdL:CeDmdL���Զ���ָ��
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
  * @brief  ģ�������������������ر�
  * @param  ceDmdL:CeDmdL���Զ���ָ��
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
  * @brief  ģ���������������ǰ��һ��
  * @param  ceDmdL:CeDmdL���Զ���ָ��
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
  * @brief  ������������з�ʽ
  * @param  ceDmdL:CeDmdL���Զ���ָ��
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
  * @brief  ģ�������������������һ��
  * @param  ceDmdL:CeDmdL���Զ���ָ��
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
  * @brief  CeDmdLģ���ʼ����һ��ͨ����
  * @param  ceDmdL:CeDmdL���Զ���
  * @param  cePwm1:CeDmdLģ���һ��ͨ��ʹ�õ�Pwm��Դ��
  * @param  ceTg1:CeDmdLģ���һ��ͨ��ʹ�õ�Tg��Դ��
  * @return ϵͳ״̬�룬���ܵ�ֵ:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdL_initialCh1(CeDmdL* ceDmdL, CE_RESOURCE cePwm1, CE_RESOURCE ceTg1)
{
    ceDmdL->duty1 = CE_PWM_MIN_CYCLE_NS;
    ceDmdL->cePwm1.ceResource = cePwm1;
    ceDmdL->cePwm1.cycleNs = CE_DMD_L_PWM1_CYCLE_NS;
    ceDmdL->cePwm1.dutyNs = CE_PWM_MIN_CYCLE_NS;//ע��Ҫ�������ceDmdMc->duty����һ�£�ֱ���ú꣬Ч�ʽϸ�
    cePwmOp.initial(&(ceDmdL->cePwm1));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm1));//����PwmΪ�͵�ƽ����ֹ��ȷ���ĵ�ƽ��������

    ceDmdL->ceTg1.ceResource = ceTg1;
    ceTgOp.initial(&(ceDmdL->ceTg1), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN1
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//IN2
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));//δʹ�ã����͵�ƽ
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeDmdLģ���ʼ���ڶ���ͨ����
  * @param  ceDmdL:CeDmdL���Զ���
  * @param  cePwm2:CeDmdLģ��ڶ���ͨ��ʹ�õ�Pwm��Դ��
  * @param  ceTg2:CeDmdLģ��ڶ���ͨ��ʹ�õ�Tg��Դ��
  * @return ϵͳ״̬�룬���ܵ�ֵ:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdL_initialCh2(CeDmdL* ceDmdL, CE_RESOURCE cePwm2, CE_RESOURCE ceTg2)
{
    ceDmdL->duty2 = CE_PWM_MIN_CYCLE_NS;
    ceDmdL->cePwm2.ceResource = cePwm2;
    ceDmdL->cePwm2.cycleNs = CE_DMD_L_PWM2_CYCLE_NS;
    ceDmdL->cePwm2.dutyNs = CE_PWM_MIN_CYCLE_NS;//ע��Ҫ�������ceDmdMc->duty����һ�£�ֱ���ú꣬Ч�ʽϸ�
    cePwmOp.initial(&(ceDmdL->cePwm2));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm2));//����PwmΪ�͵�ƽ����ֹ��ȷ���ĵ�ƽ��������

    ceDmdL->ceTg2.ceResource = ceTg2;
    ceTgOp.initial(&(ceDmdL->ceTg2), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN3
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//IN4
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));//δʹ�ã����͵�ƽ
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��һ��ͨ������򿪡��ڴ˲���ǰ����Ҫ����ת������
  * @param  ceDmdL:CeDmdL���Զ���
  * @return None
  */
void ceDmdL_setCh1On(CeDmdL* ceDmdL)
{
    cePwmOp.start(&(ceDmdL->cePwm1));
}

/**
  * @brief  �ڶ���ͨ������򿪡��ڴ˲���ǰ����Ҫ����ת������
  * @param  ceDmdL:CeDmdL���Զ���
  * @return None
  */
void ceDmdL_setCh2On(CeDmdL* ceDmdL)
{
    cePwmOp.start(&(ceDmdL->cePwm2));
}

/**
  * @brief  ������һ��ͨ���������ǿ��
  * @param  ceDmdL:CeDmdL���Զ���
  * @param  driveStrength:���������ǿ�ȣ���Χ0-10000
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
  * @brief  �����ڶ���ͨ���������ǿ��
  * @param  ceDmdL:CeDmdL���Զ���
  * @param  driveStrength:���������ǿ�ȣ���Χ0-10000
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
  * @brief  ���õ�һ��ͨ�������ת������
  * @param  ceDmdL:CeDmdL���Զ���
  * @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����
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
  * @brief  ���õڶ���ͨ�������ת������
  * @param  ceDmdL:CeDmdL���Զ���
  * @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����
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
  * @brief  ��һ��ͨ��ɲ���������������رղ�����
  * @param  ceDmdL:CeDmdL���Զ���
  * @return None
  */
void ceDmdL_ch1Brake(CeDmdL* ceDmdL)
{
    ceGpioOp.setBit(&(ceDmdL->ceTg1));//IN1��IN2��Ϊ�ߣ�����������˽�ͨ����������ת�������ĵ綯�ƽ�����·���γ��谭�˶��ĸ�Ӧ�������гɡ�ɲ�������á�
    ceGpioOp.setBit(&(ceDmdL->ceTg1));
    ceSystemOp.delayNs(100);
    cePwmOp.stop(&(ceDmdL->cePwm1));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm1));//Pwmֹͣ��ǿ������Pwm�͵�ƽ��
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
    ceGpioOp.resetBit(&(ceDmdL->ceTg1));
}

/**
  * @brief  �ڶ���ͨ��ɲ���������������رղ�����
  * @param  ceDmdL:CeDmdL���Զ���
  * @return None
  */
void ceDmdL_ch2Brake(CeDmdL* ceDmdL)
{
    ceGpioOp.setBit(&(ceDmdL->ceTg2));//IN3��IN4��Ϊ�ߣ�����������˽�ͨ����������ת�������ĵ綯�ƽ�����·���γ��谭�˶��ĸ�Ӧ�������гɡ�ɲ�������á�
    ceGpioOp.setBit(&(ceDmdL->ceTg2));
    ceSystemOp.delayNs(100);
    cePwmOp.stop(&(ceDmdL->cePwm2));
    cePwmOp.resetGpioBit(&(ceDmdL->cePwm2));//Pwmֹͣ��ǿ������PwmΪ�͵�ƽ��
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
    ceGpioOp.resetBit(&(ceDmdL->ceTg2));
}

/**
  * @brief  ��һ��ͨ������ر�
  * @param  ceDmdL:CeDmdL���Զ���
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
  * @brief  ��һ��ͨ������ر�
  * @param  ceDmdL:CeDmdL���Զ���
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

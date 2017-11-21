/**
  ******************************************************************************
  * @file    CeDmdTb.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeDmdTbģ����������ļ�
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
  * @brief  CeDmdTbģ���ʼ����һ��ͨ������һ��ͨ�����Ե���ʹ�ã��ڶ���ͨ�������������һ��ͨ������ʹ�ã�
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @param  cePwm1:CeDmdTbģ���һ��ͨ��ʹ�õ�Pwm��Դ��
  * @param  ceTg1:CeDmdTbģ���һ��ͨ��ʹ�õ�Tg��Դ��
  * @return ϵͳ״̬�룬���ܵ�ֵ:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdTb_initialCh1(CeDmdTb* ceDmdTb, CE_RESOURCE cePwm1, CE_RESOURCE ceTg1)
{
    ceDmdTb->duty1 = CE_PWM_MIN_CYCLE_NS;
    ceDmdTb->cePwm1.ceResource = cePwm1;
    ceDmdTb->cePwm1.cycleNs = CE_DMD_TB_PWM1_CYCLE_NS;
    ceDmdTb->cePwm1.dutyNs = CE_PWM_MIN_CYCLE_NS;//ע��Ҫ�������ceDmdMc->duty����һ�£�ֱ���ú꣬Ч�ʽϸ�
    cePwmOp.initial(&(ceDmdTb->cePwm1));
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm1));//����PwmΪ�͵�ƽ����ֹ��ȷ���ĵ�ƽ��������

    ceDmdTb->ceTg1.ceResource = ceTg1;
    ceTgOp.initial(&(ceDmdTb->ceTg1), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.setBit(&(ceDmdTb->ceTg1));//TB6612FNG��STBY(StandBy)Ϊ��ʱоƬ���ڴ���״̬��Ϊ�ߴ��ڹ���״̬�����Դ�����Ϊ��оƬ��������������
    ceGpioOp.resetBit(&(ceDmdTb->ceTg1));//AIN1
    ceGpioOp.resetBit(&(ceDmdTb->ceTg1));//AIN2
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeDmdTbģ���ʼ���ڶ���ͨ������һ��ͨ�����Ե���ʹ�ã��ڶ���ͨ�������������һ��ͨ������ʹ�ã�
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @param  cePwm2:CeDmdTbģ��ڶ���ͨ��ʹ�õ�Pwm��Դ��
  * @param  ceTg2:CeDmdTbģ��ڶ���ͨ��ʹ�õ�Tg��Դ��
  * @return ϵͳ״̬�룬���ܵ�ֵ:CE_STATUS_SUCCESS
  */
CE_STATUS ceDmdTb_initialCh2(CeDmdTb* ceDmdTb, CE_RESOURCE cePwm2, CE_RESOURCE ceTg2)
{
    ceDmdTb->duty2 = CE_PWM_MIN_CYCLE_NS;
    ceDmdTb->cePwm2.ceResource = cePwm2;
    ceDmdTb->cePwm2.cycleNs = CE_DMD_TB_PWM2_CYCLE_NS;
    ceDmdTb->cePwm2.dutyNs = CE_PWM_MIN_CYCLE_NS;//ע��Ҫ�������ceDmdMc->duty����һ�£�ֱ���ú꣬Ч�ʽϸ�
    cePwmOp.initial(&(ceDmdTb->cePwm2));
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm2));//����PwmΪ�͵�ƽ����ֹ��ȷ���ĵ�ƽ��������

    ceDmdTb->ceTg2.ceResource = ceTg2;
    ceTgOp.initial(&(ceDmdTb->ceTg2), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceDmdTb->ceTg2));//δʹ��
    ceGpioOp.resetBit(&(ceDmdTb->ceTg2));//BIN1
    ceGpioOp.resetBit(&(ceDmdTb->ceTg2));//BIN2
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��һ��ͨ������򿪡��ڴ˲���ǰ����Ҫ����ת�����������ɲ������Բ�������ת������ת�������򱣳�Ϊɲ��ǰ��ת������
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @return None
  */
void ceDmdTb_setCh1On(CeDmdTb* ceDmdTb)
{
    cePwmOp.start(&(ceDmdTb->cePwm1));
}

/**
  * @brief  �ڶ���ͨ������򿪡��ڴ˲���ǰ����Ҫ����ת�����������ɲ������Բ�������ת������ת�������򱣳�Ϊɲ��ǰ��ת������
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @return None
  */
void ceDmdTb_setCh2On(CeDmdTb* ceDmdTb)
{
    cePwmOp.start(&(ceDmdTb->cePwm2));
}

/**
  * @brief  ������һ��ͨ���������ǿ��
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @param  driveStrength:���������ǿ�ȣ���Χ0-10000
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
  * @brief  �����ڶ���ͨ���������ǿ��
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @param  driveStrength:���������ǿ�ȣ���Χ0-10000
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
  * @brief  ���õ�һ��ͨ�������ת������
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����
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
  * @brief  ���õڶ���ͨ�������ת������
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @param  direction:ת���ķ���0x00��ʾ����0x01�����0x00��ʾ����
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
  * @brief  ��һ��ͨ��ɲ���������ͣ
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @return None
  */
void ceDmdTb_ch1Brake(CeDmdTb* ceDmdTb)
{
    cePwmOp.stop(&(ceDmdTb->cePwm1));//ֻҪPwmΪ�ͣ�ģʽ״̬��Ϊ�ƶ�
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm1));//Pwmֹͣ��ǿ������PwmΪ�͵�ƽ��
}

/**
  * @brief  �ڶ���ͨ��ɲ���������ͣ
  * @param  ceDmdTb:CeDmdTb���Զ���
  * @return None
  */
void ceDmdTb_ch2Brake(CeDmdTb* ceDmdTb)
{
    cePwmOp.stop(&(ceDmdTb->cePwm2));//ֻҪPwmΪ�ͣ�ģʽ״̬��Ϊ�ƶ�
    cePwmOp.resetGpioBit(&(ceDmdTb->cePwm2));//Pwmֹͣ��ǿ������PwmΪ�͵�ƽ��
}

/**
  * @brief  ��һ��ͨ������ر�
  * @param  ceDmdTb:CeDmdTb���Զ���
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
  * @brief  ��һ��ͨ������ر�
  * @param  ceDmdTb:CeDmdTb���Զ���
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

/**
  ******************************************************************************
  * @file    CeTempDh11.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTempDh11��ʪ�ȴ�����ģ����������ļ�
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
  * @brief    ��DH11�������ж�һ���ֽ�
  * @param    ceTempDh11:CeTempDh11����ָ��
  * @return ��ȡ�����ֽ�
  */
char ceTempDh11_readByte(CeTempDh11* ceTempDh11)
{
    uint32 sysTick = 0;
    char i, U8temp, U8comdata=0;
    for (i = 0; i < 8; i++)
    {
        sysTick = ceSystemOp.getSystemTickMs();
        while (ceGpioOp.getBit(&ceTempDh11->ceGpio) == 0x00)    //��ʾ ��ȡ�ĸߵ�λ��ʱ����20��us ���ȡ����1 �����ȡ����0
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
        ceSystemOp.delayUs(35);                                       //ͨ��U8FLAG ���ж�    bit11 ��ʾ���ݵ�����
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
  * @brief    CeTempDh11ģ���ʼ��
  * @param    ceTempDh11:CeTempDh11����ָ��
  * @return ϵͳ״̬��
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
  * @brief    ��ʼһ���¶�ת��
  * @param  ceTempDh11:CeTempDh11����ָ��
*/
void startConvert(CeTempDh11* ceTempDh11)
{
    ceGpioOp.setMode(&(ceTempDh11->ceGpio), CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ceTempDh11->ceGpio));
    ceTempDh11->systemTick = ceSystemOp.getSystemTickMs();
}

/**
  * @brief    ����һ��ת���������ת�����
  * @param    ceTempDh11:CeTempDh11����ָ��
  * @return ת�����
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
        ceTempDh11Temp[1] = ceTempDh11_readByte(ceTempDh11);            //��8λһֱΪ0��������ʱ������
        ceTempDh11Temp[2] = ceTempDh11_readByte(ceTempDh11);
        ceTempDh11Temp[3] = ceTempDh11_readByte(ceTempDh11);            //��9λʼ��Ϊ0��������ʱ������
        U8checkdata = ceTempDh11_readByte(ceTempDh11);
    }
    ceTaskOp.outCriticalSection();
    if (U8checkdata == (uint8) (ceTempDh11Temp[0] + ceTempDh11Temp[2]))
    {
        ceTempDh11->ceTempDh11Result.temperature = ceTempDh11Temp[2];            //�¶�
        ceTempDh11->ceTempDh11Result.humidity = ceTempDh11Temp[0];                //ʪ��
    }

    return &(ceTempDh11->ceTempDh11Result);
}

const CeTempDh11Op ceTempDh11Op = {ceTempDh11_initial,startConvert, ceTempDh11_getTemperatureAndHumidity};

#ifdef __cplusplus
 }
#endif //__cplusplus

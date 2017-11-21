/**
  ******************************************************************************
  * @file    CeBtnTouch.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBtnTouchģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeBtnTouch.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  Gpio��ʽ��������ʱ�Ļص�����
  * @return None
*/
void ceBtnTouch_callBackTick(void* pAddPar)
{
    if (ceGpioOp.getBit(&((CeBtnTouch*)pAddPar)->ceGpio) == 0x00)//�������������
    {
        if ((((CeBtnTouch*)pAddPar)->status & 0x01) == 0x00)
        {
            if (((CeBtnTouch*)pAddPar)->callBackPressEvent != CE_NULL)
            {
                ((CeBtnTouch*)pAddPar)->callBackPressEvent();
            }
            ((CeBtnTouch*)pAddPar)->status |= 0x01;//��ֹ�ظ�����
        }
    }
    else
    {
        ((CeBtnTouch*)pAddPar)->status &= (~0x01);
    }
}

/**
  * @brief  Int��ʽ��������ʱ�Ļص�����
  * @return None
*/
void ceBtnTouch_callBackInt(void* pAddPar)
{
    if (((CeBtnTouch*)pAddPar)->callBackPressEvent != CE_NULL)
    {
        ((CeBtnTouch*)pAddPar)->callBackPressEvent();
    }
}

/**
  * @brief  CeBtnTouchģ���ʼ��
  * @param  ceBtnTouch:CeBtnTouch���Զ���
  * @param  ceGpio:CeBtnTouchģ��ʹ�õ���Դ��
  * @param  callBackPressEvent:��������ʱ�Ļص�����
  * @return ϵͳ״̬��
*/
CE_STATUS ceBtnTouch_initialByGpio(CeBtnTouch* ceBtnTouch, CE_RESOURCE ceGpio, void(*callBackPressEvent)(void))
{
    ceBtnTouch->status = 0x00;
    ceBtnTouch->callBackPressEvent = callBackPressEvent;
    ceBtnTouch->ceGpio.ceResource = ceGpio;
    ceBtnTouch->ceGpio.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceBtnTouch->ceGpio));

    ceBtnTouch->ceTicker.ID = ceGpio;
    ceBtnTouch->ceTicker.callBack = ceBtnTouch_callBackTick;
    ceBtnTouch->ceTicker.intervalMs = 100;
    ceBtnTouch->ceTicker.pAddPar = ceBtnTouch;

    ceTickerOp.registerTicker(&(ceBtnTouch->ceTicker));
    ceTickerOp.start(&(ceBtnTouch->ceTicker));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeBtnTouchģ���ʼ��
  * @param  ceBtnTouch:CeBtnTouch���Զ���
  * @param  ceInt:CeBtnTouchģ��ʹ�õ���Դ��
  * @param  callBackPressEvent:��������ʱ�Ļص�����
  * @return ϵͳ״̬��
*/
CE_STATUS ceBtnTouch_initialByInt(CeBtnTouch* ceBtnTouch, CE_RESOURCE ceInt, void(*callBackPressEvent)(void))
{
    ceBtnTouch->status = 0x80;
    ceBtnTouch->callBackPressEvent = callBackPressEvent;
    ceBtnTouch->ceInt.ceResource = ceInt;
    ceBtnTouch->ceInt.callBack = ceBtnTouch_callBackInt;
    ceBtnTouch->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_FALLING;//��̬�ߵ�ƽ���½��ش���
    ceBtnTouch->ceInt.pAddPar = ceBtnTouch;
    ceIntOp.initial(&(ceBtnTouch->ceInt));
    ceIntOp.start(&(ceBtnTouch->ceInt));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡCeBtnTouch��Ӧ��GPIO�ڵ�״̬��0x01��0x00
  * @return None
*/
uint8 ceBtnTouch_getGpioStatus(CeBtnTouch* ceBtnTouch)
{
    if ((ceBtnTouch->status & 0x80) == 0x80)
    {
        return ceIntOp.getBit(&(ceBtnTouch->ceInt));
    }
    else
    {
        return ceGpioOp.getBit(&(ceBtnTouch->ceGpio));
    }
}

/**
  * @brief  �ȴ��������£���ʱʱ��ΪCE_BTN_X1_OUT_TIME_MS
  * @return None
*/
void ceBtnTouch_waitForPressDown(CeBtnTouch* ceBtnTouch)
{
    uint32 temp = ceSystemOp.getSystemTickMs();
    if ((ceBtnTouch->status & 0x80) == 0x80)
    {
        while ((ceIntOp.getBit(&(ceBtnTouch->ceInt)) == 0x01) || (ceSystemOp.getSystemTickMs() - temp < CE_BTN_TOUCH_OUT_TIME_MS));
    }
    else
    {
        while ((ceGpioOp.getBit(&(ceBtnTouch->ceGpio)) == 0x01) || (ceSystemOp.getSystemTickMs() - temp < CE_BTN_TOUCH_OUT_TIME_MS));
    }
}

/**
  * @brief  �ȴ��������𣬳�ʱʱ��ΪCE_BTN_X1_OUT_TIME_MS
  * @return None
*/
void ceBtnTouch_waitForPressUp(CeBtnTouch* ceBtnTouch)
{
    uint32 temp = ceSystemOp.getSystemTickMs();
    if ((ceBtnTouch->status & 0x80) == 0x80)
    {
        while ((ceIntOp.getBit(&(ceBtnTouch->ceInt)) == 0x00) || (ceSystemOp.getSystemTickMs() - temp < CE_BTN_TOUCH_OUT_TIME_MS));
    }
    else
    {
        while ((ceGpioOp.getBit(&(ceBtnTouch->ceGpio)) == 0x00) || (ceSystemOp.getSystemTickMs() - temp < CE_BTN_TOUCH_OUT_TIME_MS));
    }
}

CeBtnTouchOp ceBtnTouchOp = {ceBtnTouch_initialByGpio, ceBtnTouch_initialByInt, ceBtnTouch_getGpioStatus, ceBtnTouch_waitForPressDown, ceBtnTouch_waitForPressUp};

#ifdef __cplusplus
}
#endif //__cplusplus

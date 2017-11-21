/**
  ******************************************************************************
  * @file    CeBtnTouch.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtnTouch模块的驱动库文件
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
  * @brief  Gpio方式按键按下时的回调处理
  * @return None
*/
void ceBtnTouch_callBackTick(void* pAddPar)
{
    if (ceGpioOp.getBit(&((CeBtnTouch*)pAddPar)->ceGpio) == 0x00)//如果按键被按下
    {
        if ((((CeBtnTouch*)pAddPar)->status & 0x01) == 0x00)
        {
            if (((CeBtnTouch*)pAddPar)->callBackPressEvent != CE_NULL)
            {
                ((CeBtnTouch*)pAddPar)->callBackPressEvent();
            }
            ((CeBtnTouch*)pAddPar)->status |= 0x01;//防止重复进入
        }
    }
    else
    {
        ((CeBtnTouch*)pAddPar)->status &= (~0x01);
    }
}

/**
  * @brief  Int方式按键按下时的回调处理
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
  * @brief  CeBtnTouch模块初始化
  * @param  ceBtnTouch:CeBtnTouch属性对象
  * @param  ceGpio:CeBtnTouch模块使用的资源号
  * @param  callBackPressEvent:按键按下时的回调函数
  * @return 系统状态码
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
  * @brief  CeBtnTouch模块初始化
  * @param  ceBtnTouch:CeBtnTouch属性对象
  * @param  ceInt:CeBtnTouch模块使用的资源号
  * @param  callBackPressEvent:按键按下时的回调函数
  * @return 系统状态码
*/
CE_STATUS ceBtnTouch_initialByInt(CeBtnTouch* ceBtnTouch, CE_RESOURCE ceInt, void(*callBackPressEvent)(void))
{
    ceBtnTouch->status = 0x80;
    ceBtnTouch->callBackPressEvent = callBackPressEvent;
    ceBtnTouch->ceInt.ceResource = ceInt;
    ceBtnTouch->ceInt.callBack = ceBtnTouch_callBackInt;
    ceBtnTouch->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_FALLING;//常态高电平，下降沿触发
    ceBtnTouch->ceInt.pAddPar = ceBtnTouch;
    ceIntOp.initial(&(ceBtnTouch->ceInt));
    ceIntOp.start(&(ceBtnTouch->ceInt));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取CeBtnTouch对应的GPIO口的状态，0x01和0x00
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
  * @brief  等待按键按下，超时时间为CE_BTN_X1_OUT_TIME_MS
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
  * @brief  等待按键弹起，超时时间为CE_BTN_X1_OUT_TIME_MS
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

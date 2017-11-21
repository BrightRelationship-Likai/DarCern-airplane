/**
  ******************************************************************************
  * @file    CeEvSw.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeEvSw模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeEvSw.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  外部中断Int回调函数
  * @param  pAddPar:CeEvSw属性对象指针
  */
void ceEvSw_intCallBack(void* pAddPar)
{
    ((CeEvSw*)(pAddPar))->callBackEvent();
}

/**
  * @brief  CeEvSw模块初始化
  * @param  ceEvSw:CeEvSw属性对象
  * @param  ceInt:CeEvSw模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceEvSw_initial(CeEvSw* ceEvSw, CE_RESOURCE ceInt, void (*callBackEvent)(void))
{
    ceEvSw->ceInt.ceResource = ceInt;
    ceEvSw->ceInt.callBack = ceEvSw_intCallBack;
    ceEvSw->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_RISING;//常态低电平，上升沿触发
    ceEvSw->ceInt.pAddPar = CE_NULL;
    ceEvSw->callBackEvent = callBackEvent;
    ceIntOp.initial(&(ceEvSw->ceInt));
    ceIntOp.start(&(ceEvSw->ceInt));

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取EvSw对应的GPIO口的电平状态，0x01和0x00
  * @param  ceEvSw:CeEvSw属性对象
  * @return 返回0低电平，模块处于未触发状态；1高电平，模块处于触发状态
  */
uint8 ceEvSw_getBit(CeEvSw* ceEvSw)
{
    return ceIntOp.getBit(&(ceEvSw->ceInt));
}

CeEvSwOp ceEvSwOp = {ceEvSw_initial, ceEvSw_getBit};

#ifdef __cplusplus
 }
#endif //__cplusplus

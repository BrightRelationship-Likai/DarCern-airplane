/**
  ******************************************************************************
  * @file    CeBtn16S.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtn16S模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeBtn16S.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  CeBtn16S模块Task资源使用的回调函数
  * @param  pAddPar:CeBtn16S属性对象指针
*/
void ceBtn16S_taskCallBack(void* pAddPar)
{
    CeBtn16S* ceBtn16S = (CeBtn16S*)pAddPar;
    uint8 i;
    ceGpioOp.setBit(&(ceBtn16S->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ceBtn16S->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.setBit(&(ceBtn16S->ceTg));
    ceSystemOp.delayUs(1);
    for( i = 0; i < 16; i++)
    {
        if(ceTgOp.getGpio2Bit(&(ceBtn16S->ceTg)) == 0x00)
        {
            if ((ceBtn16S->keyStatus & (uint16)(0x0001 << i)) != (uint16)(0x0001 << i))
            {
                ceBtn16S->callBackKeyPressEvent(15 - i);
                ceBtn16S->keyStatus |= ((uint16)0x0001<<i);
            }
        }
        else
        {
            ceBtn16S->keyStatus &= ~((uint16)0x0001 << i);
        }

        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ceBtn16S->ceTg));
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ceBtn16S->ceTg));
        ceSystemOp.delayUs(1);
    }
}

/**
  * @brief  CeBtn16S模块使用Gpio进行初始化
  * @param  ceBtn16S:CeBtn16S属性对象
  * @param  ceGpio0:CeBtn16S模块使用的第一个Gpio资源号
  * @param  ceGpio1:CeBtn16S模块使用的第二个Gpio资源号
  * @param  ceGpio2:CeBtn16S模块使用的第三个Gpio资源号
  * @param  callBackKeyPressEvent:键盘按下事件发生时，需要执行的函数；keyCode:被按下的键码
  * @return 系统状态码
  */
CE_STATUS ceBtn16S_initialByGpio(CeBtn16S* ceBtn16S, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackKeyPressEvent)(uint8 keyCode))
{
    ceBtn16S->keyStatus = (uint16)0xffff;

    ceBtn16S->ceTg.ceResource = CE_NULL_RESOURCE;
    ceBtn16S->ceTg.ceResource0 = ceGpio0;//SL,锁存
    ceBtn16S->ceTg.ceResource1 = ceGpio1;//CLK,时钟
    ceBtn16S->ceTg.ceResource2 = ceGpio2;//QH,数据
    ceBtn16S->callBackKeyPressEvent = callBackKeyPressEvent;
    ceTgOp.initial(&(ceBtn16S->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_IPU);//注意：Tg三个IO的配置模式，此模块需要检测输入电平，故输入引脚需设置为上拉输入

    ceBtn16S->ceTask.ID = ceGpio0;
    ceBtn16S->ceTask.callBack = ceBtn16S_taskCallBack;
    ceBtn16S->ceTask.pAddPar = ceBtn16S;
    ceTaskOp.registerTask(&(ceBtn16S->ceTask));
    ceTaskOp.start(&(ceBtn16S->ceTask));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeBtn16S模块初始化
  * @param  ceBtn16S:CeBtn16S属性对象
  * @param  ceTg:CeBtn16S模块使用的资源号
  * @param  callBackKeyPressEvent:键盘按下事件发生时，需要执行的函数；keyCode:被按下的键码
  * @return 系统状态码
  */
CE_STATUS ceBtn16S_initialByTg(CeBtn16S* ceBtn16S, CE_RESOURCE ceTg, void (*callBackKeyPressEvent)(uint8 keyCode))
{
    ceBtn16S->callBackKeyPressEvent = callBackKeyPressEvent;

    ceBtn16S->keyStatus = (uint16)0xffff;

    ceBtn16S->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceBtn16S->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_IPU);

    ceBtn16S->ceTask.ID = ceTg;
    ceBtn16S->ceTask.callBack = ceBtn16S_taskCallBack;
    ceBtn16S->ceTask.pAddPar = ceBtn16S;
    ceTaskOp.registerTask(&(ceBtn16S->ceTask));
    ceTaskOp.start(&(ceBtn16S->ceTask));

    return CE_STATUS_SUCCESS;
}

CeBtn16SOp ceBtn16SOp = { ceBtn16S_initialByGpio, ceBtn16S_initialByTg};

#ifdef __cplusplus
 }
#endif //__cplusplus


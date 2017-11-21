/**
  ******************************************************************************
  * @file    CeBtnx4.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtnx4模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeBtnx4.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeBtnx4模块Task资源使用的回调函数
  * @param  pAddPar:CeBtnx4属性对象指针
*/
void ceBtnx4_taskCallBack(void* pAddPar)
{
    CeBtnx4* ceBtnx4 = (CeBtnx4*)pAddPar;
    uint8 i;
    ceGpioOp.setBit(&(ceBtnx4->ceGpio2));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ceBtnx4->ceGpio2));
    ceSystemOp.delayUs(1);
    ceGpioOp.setBit(&(ceBtnx4->ceGpio2));
    ceSystemOp.delayUs(1);
    for( i = 0; i < 4; i++)//只扫描高四位即可
    {
        if(ceGpioOp.getBit(&(ceBtnx4->ceGpio2)) == 0x00)
        {
            if ((ceBtnx4->keyStatus & (uint8)(0x01 << i)) != (uint8)(0x01 << i))
            {
                ceBtnx4->keyStatus |= ((uint8)0x01<<i);
                ceBtnx4->callBackKeyPressEvent(i);
            }
        }
        else
        {
            ceBtnx4->keyStatus &= ~((uint8)0x01 << i);
        }

        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ceBtnx4->ceGpio1));
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ceBtnx4->ceGpio1));
        ceSystemOp.delayUs(1);
    }
}

/**
  * @brief  CeBtnx4模块使用Gpio进行初始化
  * @param  ceBtnx4:CeBtnx4属性对象
  * @param  ceGpio0:CeBtnx4模块使用的第一个Gpio资源号
  * @param  ceGpio1:CeBtnx4模块使用的第二个Gpio资源号
  * @param  ceGpio2:CeBtnx4模块使用的第三个Gpio资源号
  * @param  callBackKeyPressEvent:键盘按下事件发生时，需要执行的函数:keyCode:被按下的键码，范围0-3
  * @return 系统状态码
  */
CE_STATUS ceBtnx4_initial(CeBtnx4* ceBtnx4, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackKeyPressEvent)(uint8 keyCode))
{
    ceBtnx4->keyStatus = (uint8)0xFF;

    ceBtnx4->ceGpio0.ceResource = ceGpio0;//SL,锁存
    ceBtnx4->ceGpio0.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceBtnx4->ceGpio0));

    ceBtnx4->ceGpio1.ceResource = ceGpio1;//CLK,时钟
    ceBtnx4->ceGpio1.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceBtnx4->ceGpio1));

    ceBtnx4->ceGpio2.ceResource = ceGpio2;//QH,数据
    ceBtnx4->ceGpio2.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceBtnx4->ceGpio2));

    ceBtnx4->callBackKeyPressEvent = callBackKeyPressEvent;

    ceBtnx4->ceTask.ID = ceGpio0;
    ceBtnx4->ceTask.callBack = ceBtnx4_taskCallBack;
    ceBtnx4->ceTask.pAddPar = ceBtnx4;
    ceTaskOp.registerTask(&(ceBtnx4->ceTask));
    ceTaskOp.start(&(ceBtnx4->ceTask));
    return CE_STATUS_SUCCESS;
}

const CeBtnx4Op ceBtnx4Op = {ceBtnx4_initial};

#ifdef __cplusplus
 }
#endif //__cplusplus

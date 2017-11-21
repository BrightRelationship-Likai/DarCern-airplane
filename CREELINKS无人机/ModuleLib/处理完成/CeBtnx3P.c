/**
  ******************************************************************************
  * @file    CeBtnx3P.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeBtnx3P模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeBtnx3P.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  task任务处理函数
  * @param  pAddPar:CeBtnx3P属性对象
  * @return None
  */
void ceBtnx3P_taskCallBack(void* pAddPar)
{
    CeBtnx3P* ceBtnx3P = (CeBtnx3P*)(pAddPar);
    if (ceGpioOp.getBit(&(ceBtnx3P->ceGpio0)) == 0x00)
    {
        if ((ceBtnx3P->btnStatus & 0x01) == 0x01)//检测是否在上一次扫描时调用过回调
        {
            ceBtnx3P->btnStatus &= (~0x01);
            if(ceBtnx3P->callBackPressEvent != CE_NULL)
            {
                ceBtnx3P->callBackPressEvent(0x00);
            }
        }
    }
    else
    {
        ceBtnx3P->btnStatus |= 0x01;
    }

    if (ceGpioOp.getBit(&(ceBtnx3P->ceGpio1)) == 0x00)
    {
        if ((ceBtnx3P->btnStatus & 0x02) == 0x02)//检测是否在上一次扫描时调用过回调
        {
            ceBtnx3P->btnStatus &= (~0x02);
            if(ceBtnx3P->callBackPressEvent != CE_NULL)
            {
                ceBtnx3P->callBackPressEvent(0x01);
            }
        }
    }
    else
    {
        ceBtnx3P->btnStatus |= 0x02;
    }

    if (ceGpioOp.getBit(&(ceBtnx3P->ceGpio2)) == 0x00)
    {
        if ((ceBtnx3P->btnStatus & 0x04) == 0x04)//检测是否在上一次扫描时调用过回调
        {
            ceBtnx3P->btnStatus &= (~0x04);
            if(ceBtnx3P->callBackPressEvent != CE_NULL)
            {
                ceBtnx3P->callBackPressEvent(0x02);
            }
        }
    }
    else
    {
        ceBtnx3P->btnStatus |= 0x04;
    }
#ifdef CE_USE_RTOS          //如果是在操作系统环境下，查询完成后，要切换进行任务切换
    ceSystemOp.delayMs(100);
#endif
}


/**
  * @brief  CeBtnx3P模块使用三个Gpio口来完成初始化
  * @param  ceBtnx3P:CeBtnx3P属性对象
  * @param  ceGpio0:CeBtnx3P模块使用的第一个Gpio的资源号
  * @param  ceGpio1:CeBtnx3P模块使用的第二个Gpio的资源号
  * @param  ceGpio2:CeBtnx3P模块使用的第三个Gpio的资源号
  * @return 系统状态码
  */
CE_STATUS ceBtnx3P_initial(CeBtnx3P* ceBtnx3P, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void(*callBackPressEvent)(uint8 btnIndex))
{
    ceBtnx3P->callBackPressEvent = callBackPressEvent;
    ceBtnx3P->ceTask.ID = ceGpio0;

    ceBtnx3P->ceGpio0.ceResource = ceGpio0;
    ceBtnx3P->ceGpio0.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceBtnx3P->ceGpio0));

    ceBtnx3P->ceGpio1.ceResource = ceGpio1;   
    ceBtnx3P->ceGpio1.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceBtnx3P->ceGpio1));

    ceBtnx3P->ceGpio2.ceResource = ceGpio2;
    ceBtnx3P->ceGpio2.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceBtnx3P->ceGpio2));


    ceBtnx3P->btnStatus = 0x07;
    ceBtnx3P->ceTask.pAddPar = ceBtnx3P;
    ceBtnx3P->ceTask.callBack = ceBtnx3P_taskCallBack;
#ifdef CE_USE_RTOS          //如果是在操作系统环境下，则回调查询为一个单独的任务
    ceBtnx3P->ceTask.isNewThread = 0x01;
    ceBtnx3P->ceTask.ceTaskPriority = CE_TASK_PRIORITY_L;
#endif
    ceTaskOp.registerTask(&(ceBtnx3P->ceTask));
    ceTaskOp.start(&(ceBtnx3P->ceTask));

    return CE_STATUS_SUCCESS;
}

const CeBtnx3POp ceBtnx3POp = {ceBtnx3P_initial};

#ifdef __cplusplus
 }
#endif //__cplusplus

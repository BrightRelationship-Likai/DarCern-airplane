/**
  ******************************************************************************
  * @file    CePCM.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于PC_33V模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CePCM.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CePCM模块初始化
  * @param  cePCM:CePCM属性对象
  * @param  ceXX:PC_33V模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS cePCM_initial(CePCM* cePCM, CE_RESOURCE ceInt0,CE_RESOURCE ceInt1,CE_RESOURCE ceInt2,CE_RESOURCE ceInt3,CE_RESOURCE ceGpio0,CE_RESOURCE ceGpio1,CE_RESOURCE ceGpio2,CE_RESOURCE ceGpio3)
{

    return CE_STATUS_SUCCESS;
}


fp32  cePCM_getDuty(CePCM* cePCM, uint8 index)
{
    return 0;
}

const CePCMOpBase cePCMOp = {cePCM_initial, cePCM_getDuty};

#ifdef __cplusplus
}
#endif //__cplusplus

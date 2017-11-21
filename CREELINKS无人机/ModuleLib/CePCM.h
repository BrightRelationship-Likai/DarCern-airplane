/**
  ******************************************************************************
  * @file     CePCM.h
  * @author   Creelinks Application Team
  * @version  V1.0.0
  * @date    2017-01-06
  * @brief    适用于CePCM模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_PCM_H__
#define __CE_PCM_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_PCM_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_PCM_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_PCM_VERSION__ > __CE_PCM_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CePCM.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

#define CE_PCM_PWM_CYCLE_MS     24
#define CE_PCM_PWM_MIX_DUTY_MS  10
#define CE_PCM_PWM_MAX_DUTY_MS  20
/*
 *CePCM属性对像
 */
typedef struct
{
    CeInt ceInt0;
    CeInt ceInt1;
    CeInt ceInt2;
    CeInt ceInt3;
    CeGpio ceGpio0;
    CeGpio ceGpio1;
    CeGpio ceGpio2;
    CeGpio ceGpio3;
}CePCM;
/*
 *CePCM操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CePCM* cePCM, CE_RESOURCE ceInt0,CE_RESOURCE ceInt1,CE_RESOURCE ceInt2,CE_RESOURCE ceInt3,CE_RESOURCE ceGpio0,CE_RESOURCE ceGpio1,CE_RESOURCE ceGpio2,CE_RESOURCE ceGpio3);             /*!< @brief  CePCM模块初始化
                                                                                 @param  cePCM:CePCM属性对象指针
                                                                                 @param  ceXX:CePCM模块使用的资源号*/

    fp32        (*getDuty)(CePCM* cePCM, uint8 index);  

}CePCMOpBase;

/*
 *CePCM操作对象实例
 */
extern const CePCMOpBase cePCMOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_PCM_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_PCM_H__

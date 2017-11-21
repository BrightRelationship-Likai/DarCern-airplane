/**
  ******************************************************************************
  * @file    CeLight.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeLight模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_LIGHT_H__
#define __CE_LIGHT_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_LIGHT_VERSION__ 1                                              /*!< 此驱动文件的版本号*/
#define __CE_LIGHT_NEED_CREELINKS_VERSION__ 1                               /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_LIGHT_NEED_CREELINKS_VERSION__)        /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeLight.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeLight属性对像
 */
typedef struct
{
    CeAd ceAd;                                                          /*!< 模块使用到的Ad对象*/
    int16 lightDark;                                                     /*!< 无光环境下光线亮度校准值*/
    int16 lightHard;                                                     /*!< 强光环境下光线亮度校准值，此时光线传感器处于饱和状态*/                                               
}CeLight;
/*
 *CeLight操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeLight* ceLight, CE_RESOURCE ceAd);         /*!< @brief CeLight模块初始化
                                                                             @param ceLight:CeLight属性对象指针
                                                                             @param ceAd:CeLight模块使用的资源号*/

    int16       (*getLight)(CeLight* ceLight);                          /*!< @brief 获取光线亮度，范围0-100，表示光线弱强
                                                                             @param ceLight:CeLight属性对象指针*/

    void        (*calibration)(CeLight* ceLight, int16 lightDark,int16 lightHard);       /*!< 
                                                                             @brief 校准光线，请在无光的真实环境中使用getLight获取一次光线的亮度，然后填入此值，以此来修正光线亮度计算的误差
                                                                             @param ceLight:CeLight属性对象指针
                                                                             @param lightDark:模块在无光环境中的实际采样值*/


}CeLightOp;
/*
 *CeLight操作对象实例
 */
extern const CeLightOp ceLightOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_LIGHT_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_LIGHT_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 将当前环境光的亮度值通过串口发送到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeLight.h"
CeLight myLight;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceLightOp.initial(&myLight, R1AGP);         //使用R1AGP的Ad功能初始化光线传感器
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceDebugOp.printf("The light is :%d\n", ceLightOp.getLight(&myLight));
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

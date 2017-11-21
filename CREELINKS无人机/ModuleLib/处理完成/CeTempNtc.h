/**
  ******************************************************************************
  * @file    CeTempNtc.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTempNtc模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TEMP_NTC_H__
#define __CE_TEMP_NTC_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TEMP_NTC_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_TEMP_NTC_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_TEMP_NTC_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeTempNtc.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeTempNtc属性对像
 */
typedef struct
{
    CeAd ceAd;                                               /*!< 模块使用到的Ad对象*/
    uint16 temp0C;                                           /*!< TempNtc在0度环境下的温度校准值*/
    uint16 temp100C;                                         /*!< TempNtc在100度环境下的温度校准值*/
}CeTempNtc;
/*
 *CeTempNtc操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeTempNtc* ceTempNtc, CE_RESOURCE ceAd);/*!<
                                                                 @brief CeTempNtc模块初始化
                                                                 @param ceTempNtc:CeTempNtc属性对象指针
                                                                 @param ceAd:CeTempNtc模块使用的Ad资源号*/

    fp32        (*getTemperature)(CeTempNtc* ceTempNtc);    /*!< @brief 获取温度值，有两位小数点
                                                                 @param ceTempNtc:CeTempNtc属性对象指针*/

    void        (*calibration)(CeTempNtc* ceTempNtc, fp32 temp0C, fp32 temp100C);/*!<
                                                                 @brief 校准，请在0度和100度的环境中分别使用getTemperature获取一次温度值，然后填入对应值，以此来修正温度计算的误差。
                                                                 @param ceTempNtc:CeTempNtc属性对象指针
                                                                 @param temp0C:模块在0度环境中的实际采样值
                                                                 @param temp100C:模块在100度环境中的实际采样值*/
}CeTempNtcOp;
/*
 *CeTempNtc操作对象实例
 */
extern CeTempNtcOp ceTempNtcOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_TEMP_NTC_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TEMP_NTC_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 将当前环境温度值通过串口发送到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeTempNtc.h"
CeTempNtc myTemp;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceTempNtcOp.initial(&myTemp, R1AGP);        //使用R1AGP的Ad功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceDebugOp.printf("The Temperature is :%f\n", ceTempNtcOp.getTemperature(&myTemp));
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeRadar.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRadar模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_REDAR_H__
#define __CE_REDAR_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_REDAR_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_REDAR_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_REDAR_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeRadar.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeRadar属性对像
 */
typedef struct
{
    CeGpio      ceGpio;                                 /*!< CeRadar的TRING引脚使用的Gpio资源对象*/
    CeInt       ceInt;                                  /*!< CeRadar的ECHO引脚使用的外部中断Int资源对象*/
    uint32      timeCostUs;                             /*!< CeRadar用于计算时间花费的属性对象*/
    uint32      timeCost;                               /*!< CeRadar测距得到的高电平时间*/
    uint8       status;                                 /*!< CeRadar的状态*/
}CeRadar;
/*
 *CeRadar操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeRadar* ceRadar, CE_RESOURCE ceGpio, CE_RESOURCE ceInt);/*!<
                                                             @brief CeRadar模块初始化
                                                             @param ceRadar:CeRadar属性对象指针
                                                             @param ceGpio:CeRadar模块使用的Gpio资源号
                                                             @param ceInt:CeRadar模块使用的Int资源号，此外部中断Int须支持上升沿和下降沿触发*/

    uint32      (*getDistance)(CeRadar* ceRadar);       /*!< @brief 开始雷达探测并获取探测到的物理离模块的距离，单位mm。测量范围2cm-400cm，测量精度3mm。
                                                             @param ceRadar:CeRadar属性对象指针*/

}CeRadarOp;
/*
 *CeRadar操作对象实例
 */
extern const CeRadarOp ceRadarOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_REDAR_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_REDAR_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 采集雷达模块与物体的距离，并通过串口将信息显示到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeRadar.h"
CeRadar myRadar;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceRadarOp.initial(&myRadar,R1AGP, R6ADIG);  //使用R1AGP的Gpio功能 和 R6ADIG的Int功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceDebugOp.printf("The distance is:%dmm\n",ceRadarOp.getDistance(&myRadar));
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

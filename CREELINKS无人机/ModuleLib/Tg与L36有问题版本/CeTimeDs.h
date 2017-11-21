/**
  ******************************************************************************
  * @file    CeTimeDs.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTimeDs模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TIME_DS_H__
#define __CE_TIME_DS_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TIME_DS_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_TIME_DS_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_TIME_DS_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeTimeDs.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/**
  * @brief  结构体，TimeDs对象的日期时间
  */
typedef struct
{
    uint16 year;        /*!< TimeDs时间的年*/
    uint8  month;       /*!< TimeDs时间的月*/
    uint8  day;         /*!< TimeDs时间的日*/
    uint8  hour;        /*!< TimeDs时间的时*/
    uint8  minute;      /*!< TimeDs时间的分钟*/
    uint8  second;      /*!< TimeDs时间的秒*/
    uint8  week;        /*!< TimeDs时间的星期*/
}CeTimeDsDate;
/*
 *CeTimeDs属性对像
 */
typedef struct
{
    CeTg ceTg;
    CeTimeDsDate ceTimeDsDate;
}CeTimeDs;
/*
 *CeTimeDs操作对像
 */
typedef struct
{
    CE_STATUS       (*initialByGpio)(CeTimeDs* ceTimeDs, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                                 @brief CeTimeDs模块使用Gpio进行初始化
                                                                                 @param ceTimeDs:CeTimeDs属性对象指针
                                                                                 @param ceGpio0:CeTimeDs模块使用的第一个Gpio资源号
                                                                                 @param ceGpio1:CeTimeDs模块使用的第二个Gpio资源号
                                                                                 @param ceGpio2:CeTimeDs模块使用的第三个Gpio资源号*/

    CE_STATUS       (*initialByTg)(CeTimeDs* ceTimeDs,CE_RESOURCE ceTg);    /*!< @brief CeTimeDs模块初始化
                                                                                 @param ceTimeDs:CeTimeDs属性对象指针
                                                                                 @param ceTg:CeTimeDs模块使用的资源号*/

    CE_STATUS       (*setTime)(CeTimeDs* ceTimeDs, CeTimeDsDate ceTimeDsData);/*!<
                                                                                 @brief 设置日期时间
                                                                                 @param ceTimeDs:CeTimeDs属性对象指针
                                                                                 @param ceTimeDsData:要设置的时间结构体的指针*/

    CeTimeDsDate*   (*getTime)(CeTimeDs* ceTimeDs);                         /*!< @brief 获取日期时间
                                                                                 @param ceTimeDs:CeTimeDs属性对象指针
                                                                                 @return 返回获取到的日期时间的结构体指针*/
}CeTimeDsOp;
/*
 *CeTimeDs操作对象实例
 */
const extern CeTimeDsOp ceTimeDsOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_TIME_DS_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TIME_DS_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 获取日期日间，并通过串口显示到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeTimeDs.h"
CeTimeDs myTime;
CeTimeDsDate* pCeTimeDsDate;
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                              //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceTimeDsOp.initialByTg(&myTime, R2TI2c);                //使用R2TI2c的Tg功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        pCeTimeDsDate = ceTimeDsOp.getTime(&myTime);
        ceDebugOp.printf("Now Time: %d:%d:%d: %d:%d:%d\n", pCeTimeDsDate->year, pCeTimeDsDate->month, pCeTimeDsDate->day, pCeTimeDsDate->hour, pCeTimeDsDate->minute, pCeTimeDsDate->second);
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

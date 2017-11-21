/**
  ******************************************************************************
  * @file    CeTempDs.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTempDs模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TEMP_DS_H__
#define __CE_TEMP_DS_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TEMP_DS_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_TEMP_DS_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_TEMP_DS_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeTempDs.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeTempDs属性对像
 */
typedef struct
{
    CeGpio ceGpio;      /*!< 模块使用到的Gpio对象*/
}CeTempDs;
/*
 *CeTempDs操作对像
 */
typedef struct
{
    CE_STATUS    (*initial)(CeTempDs* ceTempDs, CE_RESOURCE ceGpio);    /*!< @brief CeTempDs模块初始化
                                                                             @param ceTempDs:CeTempDs属性对象指针
                                                                             @param ceGpio:CeTempDs模块使用的Gpio资源号*/

    fp32         (*getTemperature)(CeTempDs* cedDS18b20);               /*!< @brief 获取温度值，范围-55至+125度
                                                                             @param ceTempDs:CeTempDs属性对象指针
                                                                             @return 返回获取到的温度值，有四位小数点*/
}CeTempDsOp;
/*
 *CeTempDs操作对象实例
 */
extern const  CeTempDsOp ceTempDsOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_TEMP_DS_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TEMP_DS_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 获取温度并通过串口打印到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeTempDs.h"
CeTempDs myTemp;
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                              //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceTempDsOp.initial(&myTemp, R1AGP);                     //使用R1AGP的Gpio功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceDebugOp.printf("The temperature is: %f \n", ceTempDsOp.getTemperature(&myTemp));
    };
}
******************************************************************************
*/

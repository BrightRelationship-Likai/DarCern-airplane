/**
  ******************************************************************************
  * @file    CeTempDh11.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTempDh11温湿度传感器模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TEMP_DH11_H__
#define __CE_TEMP_DH11_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TEMP_DH11_VERSION__ 1                                           /*!< 此驱动文件的版本号*/
#define __CE_TEMP_DH11_NEED_CREELINKS_VERSION__ 1                            /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_TEMP_DH11_NEED_CREELINKS_VERSION__)     /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeTempDh11.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *@brief CeTEMP_DH11转换结果
 */
typedef struct
{
    uint8 temperature;                      /*!< TempDh11转换结果，温度*/
    uint8 humidity;                         /*!< TempDh11转换结果，湿度*/
}CeTempDh11Result;

/*
 *@brief CeTempDh11属性对象
 */
typedef struct
{
    CeGpio ceGpio;                          /*!< CeTempDh11模块使用到的Gpio资源号*/
    CeTempDh11Result ceTempDh11Result;              /*!< CeTempDh11转换结果*/
    uint32  systemTick;                     /*!< 用于检测CeTempDh11从开始转换到获取转换结果的时间*/
}CeTempDh11;

/*
 *@brief CeTempDh11操作对象
 */
typedef struct
{
    CE_STATUS       (*initial)(CeTempDh11* ceTempDh11,CE_RESOURCE ceGpio);  /*!< @brief CeTempDh11模块的初始化
                                                                         @param ceTempDh11:CeTempDh11属性对象指针
                                                                         @param ceGpio:CeTempDh11模块使用的资源号*/

    void            (*startConvert)(CeTempDh11* ceTempDh11);                /*!< @brief 开始一次温度转换
                                                                         @param ceTempDh11:CeTempDh11属性对象指针*/

    CeTempDh11Result*   (*getTemperatureAndHumidity)(CeTempDh11* ceTempDh11);   /*!< @brief 获取温温度转换结果。注意：TEMP_DH11完成一次温度转换的时间约为20ms，
                                                                                请尽量保证调用startConvert()函数与此函数之间的时间间隔大于20ms。
                                                                                如果小于20ms，此函数将会阻塞直到满足20ms的条件。
                                                                         @param ceTempDh11:CeTempDh11属性对象指针
                                                                         @return TempDh11的转换结果*/
}CeTempDh11Op;

/*
 *@brief CeTempDh11操作对象实例
 */
extern const CeTempDh11Op ceTempDh11Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_TEMP_DH11_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TEMP_DH11_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 采集环境温度和湿度信息，并通过Uart在上位机上显示
******************************************************************************
#include "Creelinks.h"
CeTempDh11 myTempDh11;                                      //定义CeTempDh11对象
CeTempDh11Result* result;                                   //定义转换结果指针
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                              //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceTempDh11Op.initial(&myTempDh11, R1AGP);               //使用RxG资源初始化此模块
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceTempDh11Op.startConvert(&myTempDh11);             //开始一次转换
        ceSystemOp.delayMs(50);                             //延时并等待转换结束
        result = ceTempDh11Op.getTemperatureAndHumidity(&myTempDh11);   //获得转换结果
        ceDebugOp.printf("Convert Finish:Temperature=%d, Humidity=%d \n",result->temperature,result->humidity);//打印并输出转换结果
    };
}
******************************************************************************
*/

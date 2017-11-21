/**
  ******************************************************************************
  * @file    CeMS5611.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeMS5611模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_MS5611_H__
#define __CE_MS5611_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_MS5611_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_MS5611_NEED_CREELINKS_VERSION__ 1                               /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_MS5611_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeMS5611.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else



typedef struct
{
    fp32     temperature;        /*!< 温度值*/
    int32    pressure;           /*!< 气压值*/
    fp32     altitude;           /*!< 海拔高度*/
}CeMS5611Environment;

/*
 *CeMS5611属性对像
 */
typedef struct
{
    CeI2cMaster ceI2cMaster;
    int16       AC1;
    int16       AC2;
    int16       AC3;
    uint16      AC4;
    uint16      AC5;
    uint16      AC6;
    int16       B1;
    int16       B2;
    int16       MB;
    int16       MC;
    int16       MD;
    int32       UT;
    int32       UP;
    CeMS5611Environment environment;
    uint32 lastSystemTimeMs;    /*!< 由于MS5611进行一次气压读取需要至少4.5ms时间，此值用于计算从开始转换到*/
    uint8       asyncStep;
    fp32        lastAltiude;

}CeMS5611;
/*
 *CeMS5611操作对像
 */
typedef struct
{
    CE_STATUS               (*initial)(CeMS5611* ceMS5611, CE_RESOURCE ceI2cMaster);/*!< 
                                                                                 @brief CeMS5611模块初始化
                                                                                 @param ceMS5611:CeMS5611属性对象指针
                                                                                 @param ceI2cMaster:CeMS5611模块使用的资源号*/
                                                                             
    CeMS5611Environment*    (*getEnvironment)(CeMS5611* ceMS5611);          /*!< @brief 获取已经过校正的温度、气压、海拔高度
                                                                                 @param ceMS5611:CeMS5611属性对象指针*/

}CeMS5611Op;
/*
 *CeMS5611操作对象实例
 */
extern const CeMS5611Op ceMS5611Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_MS5611_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_MS5611_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function xxxxxzzzz
******************************************************************************
#include "Creelinks.h"
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(Uartx);                        //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作

    };
}
******************************************************************************
*/

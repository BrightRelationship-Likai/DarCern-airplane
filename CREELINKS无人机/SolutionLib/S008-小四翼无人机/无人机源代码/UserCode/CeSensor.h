/**
  ******************************************************************************
  * @file    CeSensor.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   无人机传感器接口对象
  ******************************************************************************
  * @attention
  * 
  * 
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_SENSOR_H__
#define __CE_SENSOR_H__
#include "Creelinks.h"
#ifdef __cpluslus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  结构体，加速度,
  *         单位：g
  *         方向：向前方加速X+，向后方加速X-，向左方加速Y+，向右方加速Y-，向上方加速Z+，向下方加速Z-
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeAcc;

/**
  * @brief  结构体，陀螺仪角速度，
  *         单位：度/s
  *         方向：右翻滚X+， 左翻滚X-， 前俯Y+， 后仰Y-， 逆时针偏航Z+， 顺时针偏航Z-
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeGyr;

/**
  * @brief  结构体，地磁传感器（电子罗盘）
  *         单位：度
  *         方向：暂未指定
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeMag;

/**
  * @brief  结构体，气压计
  */
typedef struct
{
    fp32 altitude;                          /*!< 海拔高度，单位米(m)*/
    fp32 pressure;                          /*!< 大气压强，单位帕斯卡(Pa)*/
}CeAlt;

/**
  * @brief  结构体，GPS地面定位信息结构体
  */
typedef struct
{
    fp32  latitude;                         /*!< 当前纬度坐标*/           
    char  latitudeHemisphere;               /*!< 当前纬度半球，N:北半球； S:南半球*/
    fp32  longitude;                        /*!< 当前经度坐标*/
    char  longitudeHemisphere;              /*!< 当前经度半球，E:东经；W:西经*/
}CeGps;



/**
  * @brief  结构体，当前无人机所处环境温度
  */
typedef struct
{
    fp32  temperature;                      /*!< 当前温度，单位度*/           
}CeTem;

/*
 *CeSensor操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(void);           /*!< @brief  无人可传感器合集对象初始化*/

    CE_STATUS   (*getAcc)(CeAcc* outCeAcc); /*!< @brief  获取当前无人机的加速度
                                                 @param  outCeAcc:加速度结果保存地址*/

    CE_STATUS   (*getGyr)(CeGyr* outCeGyr); /*!< @brief  获取当前无人机的角速度
                                                 @param  outCeGyr:角速度结果保存地址*/

    CE_STATUS   (*getMag)(CeMag* outCeMag); /*!< @brief  获取当前无人机的地磁数据
                                                 @param  outCeMag:地磁数据保存地址*/

    CE_STATUS   (*getAlt)(CeAlt* outCeAlt); /*!< @brief  获取当前无人机海拔高度信息
                                                 @param  outCeAlt:当前无人机海拔高度数据*/

    CE_STATUS   (*getGps)(CeGps* outCeGps); /*!< @brief  获取当前无人机位置信息
                                                 @param  outCeGps:当前无人机位置信息保存地址*/

    CE_STATUS   (*getTem)(CeTem* outCeTem); /*!< @brief  获取当前无人机所处环境温度信息
                                                 @param  outCeTem:当前无人机温度信息保存地址*/

}CeSensorOp;

/*
 *CeSensor操作对象实例
 */
extern const CeSensorOp ceSensorOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SENSOR_H__



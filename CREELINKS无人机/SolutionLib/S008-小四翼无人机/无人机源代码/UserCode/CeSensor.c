/**
  ******************************************************************************
  * @file    CeSensor.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   数据传输管理，用于WIFI、蓝牙、2.4G模块的初始化；数据发送接收等处理
  ******************************************************************************
  * @attention
  *
  *1)移植请注意：请在initial函数中，定义各个模块使用到的资源。
  *2)发送数据调用send函数，输入Byte数组即可；
  *3)接收到数据后自动调用初始化时提供的回调，传入未经任何处理的Byte数组。
  *4)接收到数据后，调用的回调函数，在ceTaskOp.mainTask()中执行，请保证主main函数中的ceTaskOp.mainTask()能够被周期调用 
  * 
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeSensor.h"
#include "CeMPU6050.h"
#include "CeMS5611.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define     CE_MPU6050_RESOURCE I2c1        /*!< 定义MPU6050模块使用到的I2C资源号*/ 
#define     CE_MS5611_RESOURCE  I2c2        /*!< 定义MS5611模块使用到的I2C资源号*/ 

CeMPU6050   ceMPU6050;                      /*!< CeMPU6050模块对象*/ 
CeMS5611    ceMS5611;                       /*!< CeMS5611模块对象*/ 

/**
  * @brief  无人可传感器合集对象初始化
  */
CE_STATUS   ceSensor_initial(void)
{
    ceMPU6050Op.initial(&ceMPU6050,CE_MPU6050_RESOURCE);
    //ceMS5611Op.initial(&ceMS5611, CE_MS5611_RESOURCE);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取当前无人机的加速度
  * @param  outCeAcc:加速度结果保存地址
  */
CE_STATUS   ceSensor_getAcc(CeAcc* outCeAcc)
{
    CeMPU6050Acc* acc = ceMPU6050Op.getAcceleration(&ceMPU6050);
    if(acc == CE_NULL)
        return CE_STATUS_FAILE;

    outCeAcc->x = acc->x;
    outCeAcc->y = acc->y;
    outCeAcc->z = acc->z;

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取当前无人机的角速度
  * @param  outCeGyr:角速度结果保存地址
  */
CE_STATUS   ceSensor_getGyr(CeGyr* outCeGyr)
{
    CeMPU6050Gyr* gyr = ceMPU6050Op.getGyroscope(&ceMPU6050);
    if(gyr == CE_NULL)
        return CE_STATUS_FAILE;
    outCeGyr->x = gyr->x;
    outCeGyr->y = gyr->y;
    outCeGyr->z = gyr->z;

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取当前无人机的地磁数据
  * @param  outCeMag:地磁数据保存地址
  */
CE_STATUS   ceSensor_getMag(CeMag* outCeMag)
{

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取当前无人机海拔高度信息
  * @param  outCeAlt:当前无人机海拔高度数据
  */
CE_STATUS   ceSensor_getAlt(CeAlt* outCeAlt)
{

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取当前无人机位置信息
  * @param  outCeGps:当前无人机位置信息保存地址
  */
CE_STATUS   ceSensor_getGps(CeGps* outCeGps)
{

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取当前无人机所处环境温度信息
  * @param  outCeTem:当前无人机温度信息保存地址
  */
CE_STATUS  ceSensor_getTem(CeTem* outCeTem)
{

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeSensor模块操作对象定义
  */
const CeSensorOp ceSensorOp = {ceSensor_initial,ceSensor_getAcc,ceSensor_getGyr,ceSensor_getMag,ceSensor_getAlt,ceSensor_getGps,ceSensor_getTem};

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeMPU6050.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeMPU6050模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_MPU6050_H__
#define __CE_MPU6050_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#include "Creelinks.h"
#define __CE_MPU6050_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_MPU6050_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_MPU6050_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeMPU6050.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

/**
  * @brief  结构体，加速度
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeMPU6050Acc;

/**
  * @brief  结构体，陀螺仪角速度
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeMPU6050Gyr;

/*
 *CeMPU6050属性对象
 */
typedef struct
{
    CeI2cMaster         ceI2cMaster;
    CeMPU6050Acc  acceleration;
    CeMPU6050Gyr     gyroscope;
    CeMPU6050Gyr     gyroscopeZero;
}CeMPU6050;

/*
 *CeMPU6050操作对象
 */
typedef struct
{
    CE_STATUS              (*initial)(CeMPU6050* CeMPU6050, CE_RESOURCE ceI2c);/*!<
                                                                      @brief CeMPU6050模块初始化
                                                                      @param CeMPU6050:CeMPU6050属性对象指针
                                                                      @param ceI2cMaster:CeMPU6050模块使用的资源号*/

    CeMPU6050Acc*    (*getAcceleration)(CeMPU6050* CeMPU6050);   /*!< @brief 获取加速度
                                                                      @param CeMPU6050:CeMPU6050属性对象指针*/

    CeMPU6050Gyr*       (*getGyroscope)(CeMPU6050* CeMPU6050);      /*!< @brief 获取陀螺仪角速度
                                                                      @param CeMPU6050:CeMPU6050属性对象指针*/
}CeMPU6050Op;
/*
 *CeMPU6050操作对象实例
 */
extern const CeMPU6050Op ceMPU6050Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_MPU6050_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_MPU6050_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 读取6轴信息，并通过Uart在上位机上显示
******************************************************************************
#include "Creelinks.h"
#include "CeMPU6050.h"
CeMPU6050 myMPU6050;                                //定义属性对象
CeMPU6050Acc* acceleration;              //定义三轴加速度参数指针
CeMPU6050Gyr* gyroscope;                    //定义三轴陀螺参数指针
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(Uartx);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceMPU6050Op.initial(&myMPU6050,I2cx);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        acceleration = ceMPU6050Op.getAcceleration(&myMPU6050);
        ceDebugOp.printf("Acceleration: x=%d, y=%d, z=%d\n", acceleration->x, acceleration->y,acceleration->z);

        gyroscope = ceMPU6050Op.getGyroscope(&myMPU6050);
        ceDebugOp.printf("Gyroscope: x=%d, y=%d, z=%d\n", gyroscope->x, gyroscope->y,gyroscope->z);

        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/




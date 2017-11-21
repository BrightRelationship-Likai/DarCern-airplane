/**
  ******************************************************************************
  * @file    Ce10Dof.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeAnSw模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_10_DOF_H__
#define __CE_10_DOF_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_10_DOF_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_10_DOF_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_10_DOF_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件Ce10Dof.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
typedef struct
{
    int16 AC1;
    int16 AC2;
    int16 AC3;
    uint16 AC4;
    uint16 AC5;
    uint16 AC6;
    int16 B1;
    int16 B2;
    int16 MB;
    int16 MC;
    int16 MD;

    int16 _oss;
    int32 B5;
    int32 UT;
    int32 UP;
    int32 Pressure0;
}Ce10DofBMP180;

/**
  * @brief  结构体，加速度
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}Ce10DofAcceleration;

/**
  * @brief  结构体，陀螺仪角速度
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}Ce10DofGyroscope;

/**
  * @brief  结构体，电子罗盘倾角
  */
typedef struct
{
    int16 x;
    int16 y;
    int16 z;
}Ce10DofMagnetic;


/**
  * @brief  三维向量
  */
typedef struct
{
    fp32 x;
    fp32 y;
    fp32 z;
}CeVector3;


typedef struct
{
    fp32     temperature;        /*!< 温度值*/
    int32    pressure;           /*!< 气压值*/
    fp32     altitude;           /*!< 海拔高度*/
}Ce10DofEnvironment;
/*
 *Ce10Dof属性对象
 */
typedef struct
{
    CeI2cMaster ceI2cMaster;
    Ce10DofAcceleration acceleration;
    Ce10DofGyroscope gyroscope;
    Ce10DofGyroscope gyroscopeZero;
    Ce10DofMagnetic magnetic;
    Ce10DofEnvironment environment;
    Ce10DofBMP180  exBmp180;

    CeVector3 gyroscopeVector3;
}Ce10Dof;

/*
 *Ce10Dof操作对象
 */
typedef struct
{
    CE_STATUS               (*initial)(Ce10Dof* ce10Dof, CE_RESOURCE ceI2c);/*!<
                                                                         @brief Ce10Dof模块初始化
                                                                         @param ce10Dof:Ce10Dof属性对象指针
                                                                         @param ceI2cMaster:Ce10Dof模块使用的资源号*/

    Ce10DofAcceleration*    (*getAcceleration)(Ce10Dof* ce10Dof);   /*!< @brief 获取加速度
                                                                         @param ce10Dof:Ce10Dof属性对象指针*/

    Ce10DofGyroscope*       (*getGyroscope)(Ce10Dof* ce10Dof);      /*!< @brief 获取陀螺仪角速度
                                                                         @param ce10Dof:Ce10Dof属性对象指针*/

    Ce10DofMagnetic*        (*getMagnetic)(Ce10Dof* ce10Dof);       /*!< @brief 获取电子罗盘倾角
                                                                         @param ce10Dof:Ce10Dof属性对象指针*/

    Ce10DofEnvironment*     (*getEnvironment)(Ce10Dof* ce10Dof);    /*!< @brief 获取已经过校正的温度、气压、海拔高度
                                                                         @param ce10Dof:Ce10Dof属性对象指针*/

}Ce10DofOp;
/*
 *Ce10Dof操作对象实例
 */
extern const Ce10DofOp ce10DofOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_10_DOF_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_10_DOF_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 读取10轴信息，并通过Uart在上位机上显示
******************************************************************************
#include "Creelinks.h"
#include "Ce10Dof.h"
Ce10Dof my10Dof;                                //定义属性对象
Ce10DofAcceleration* acceleration;              //定义三轴加速度参数指针
Ce10DofGyroscope* gyroscope;                    //定义三轴陀螺参数指针
Ce10DofMagnetic* magnetic;                      //定义地磁参数指针
Ce10DofEnvironment* environment;                //定义温度、气压、海拔高度
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ce10DofOp.initial(&my10Dof,R2TI2c);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        acceleration = ce10DofOp.getAcceleration(&my10Dof);
        ceDebugOp.printf("Acceleration: x=%d, y=%d, z=%d\n", acceleration->x, acceleration->y,acceleration->z);

        gyroscope = ce10DofOp.getGyroscope(&my10Dof);
        ceDebugOp.printf("Gyroscope: x=%d, y=%d, z=%d\n", gyroscope->x, gyroscope->y,gyroscope->z);

        magnetic = ce10DofOp.getMagnetic(&my10Dof);
        ceDebugOp.printf("Magnetic: x=%d, y=%d, z=%d\n", magnetic->x, magnetic->y,magnetic->z);

        environment = ce10DofOp.getEnvironment(&my10Dof);
        ceDebugOp.printf("Environment: temperature=%f, pressure=%d, altitude=%f\n", environment->temperature, environment->pressure,environment->altitude);

        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    main.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-23
  * @brief   CREELINKS小四轴无人机飞行器主入口程序
  ******************************************************************************
  * @attention
  *
  * 1)注意：不建议直接阅读源代码，可先简要阅览CREELINKS小四轴无人机的软件结构及框架，
  *   下载地址：http://www.creelinks.com/uav/uav.html
  * 2)注意：有关CREELINKS抽象接口的定义、使用方法、移植方法，请访问官网下载相关资料。
  *   官方网站：http://www.creelinks.com
  * 3)注意：可加入CREELINKS小四轴交流群623083844
  *
  * 1)基于CREELINKS平台V1.0
  * 2)支持WIFI、蓝牙、2.4G射频三种通讯方式，当前版本(V1.0)暂不支持蓝牙通讯
  * 3)开机时按下右按钮，直到听到滴..滴..两声后，系统进入蓝牙工作方式
  * 4)开机时按下左按钮，直到听到滴..一声后，系统进入WIFI工作方式
  * 5)开机时不按任何按钮，系统默认进入2.4G射频工作方式
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "Creelinks.h"                              //CREELINKS平台头文件
#include "CePID.h"                                  //PID参数计算
#include "CeFilter.h"                               //卡尔曼滤波、四元数法姿态解算
#include "CeMDCtl.h"                                //电机电调控制模块驱动
#include "CeSysCtl.h"                               //系统控制操作全集                         
#include "CeStatus.h"                               //无人机状态管理头文件

CeStatus         ceNowStatus;                       //定义当前的无人机姿态
CeStatus         ceHopeStatus;                      //定义期望的无人机姿态 

CeMDDrivePower*  drivePower;                        //定义电机的驱动强度结构体指针
fp32             dtS = 0;                           //程序主while执行周期，单位S

/**
  * @brief  CREELINKS平台主入口函数(裸奔)
  * @return 0
  */
int main(void)
{
    ceSystemOp.initial();                           //Creelinks环境初始化
    ceDebugOp.initial(Uart1);                       //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceMDCtlOp.initial();                            //初始化四个电机
    ceSysCtlOp.initial();                           //四个LED初始化
    ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_CFG);  //LED灯显示为配置状态
    ceStatusOp.initial();                           //初始化无人机状态参数管理
    ceFilterOp.initial();                           //无人机姿态解析及滤波控制对像，四种：一、二阶、四元数、卡尔曼 
    cePIDOp.initial();                              //无人机串级PID控制对象
    ceSysCtlOp.setAlarm(1000,0,1);                  //蜂鸣器发出1S响，提示已初始化完成，可以起飞
    ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_NORMAL);  //LED灯提示为可以起飞状态
    while (1)
    {
        ceTaskOp.mainTask();                        //Creelinks环境主循环任务，请保证此函数能够被周期调用        
        //TODO:请在此处插入用户操作   
        ceStatusOp.getNowStatus(&ceNowStatus);      //获取当前无人机的状态信息，如加/角速度传感器等等

        ceFilterOp.filter(&ceNowStatus,dtS);        //对当前加速度、当前角速度进行姿态解析及滤波，以获取无人机姿态角数据，注：会将计算结果更新到三个指针参数所指内容。 

        ceStatusOp.getHopeStatus(&ceNowStatus, &ceHopeStatus);     //获取期望的无人机状态信息

        drivePower = cePIDOp.calculate(&ceNowStatus, &ceHopeStatus,dtS);//根据当前加速度及角速度、姿态角、还有期望姿态进行串级PID运算，并获得四个电机的驱动强度  

        ceMDCtlOp.setDriverPower(drivePower);       //配置电机的驱动强度
    
        dtS = ceSysCtlOp.getSysRunCycleS();         //计算程序执行周期时间   
    };
}

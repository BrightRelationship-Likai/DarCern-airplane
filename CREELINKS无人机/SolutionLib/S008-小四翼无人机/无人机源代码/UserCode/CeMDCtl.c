/**
  ******************************************************************************
  * @file    CeMD.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   电机电调驱动文件，即将0~1000的驱动为转化为0~100%占空比的PWM输出
  ******************************************************************************
  * @attention
  *
  *1)输入0~1000的驱动强度，输出对应为0~100%的占空比
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeMDCtl.h"
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
#define  CE_MD_CTL_RESOURCE_0   PC6GIP                  /*!< 定义第0路电机电调使用的PWM资源号*/
#define  CE_MD_CTL_RESOURCE_1   PC7GIP                  /*!< 定义第1路电机电调使用的PWM资源号*/
#define  CE_MD_CTL_RESOURCE_2   PC8GIP                  /*!< 定义第2路电机电调使用的PWM资源号*/
#define  CE_MD_CTL_RESOURCE_3   PC9GIP                  /*!< 定义第3路电机电调使用的PWM资源号*/
CeMD        ceMD0;                                      /*!< 定义第0路电机电调控制对象*/
CeMD        ceMD1;                                      /*!< 定义第1路电机电调控制对象*/
CeMD        ceMD2;                                      /*!< 定义第2路电机电调控制对象*/
CeMD        ceMD3;                                      /*!< 定义第3路电机电调控制对象*/
/**
  * @brief  CeMD模块初始化
  * @return 系统状态码
  */
void ceMDCtl_initial(void)
{
    ceMDOp.initial(&(ceMD0), CE_MD_CTL_RESOURCE_0);     //使用一路Pwm资源号初始化电机电调0
    ceMDOp.initial(&(ceMD0), CE_MD_CTL_RESOURCE_0);     //使用一路Pwm资源号初始化电机电调0,注：此处初始化两次PC6对应的Pwm，是因为STM32F103和TIM8定时器似乎有BUG，四路通道，初始化次数及顺序均影响输出的PWM正反向，后继再做研究。
    ceMDOp.initial(&(ceMD1), CE_MD_CTL_RESOURCE_1);     //使用一路Pwm资源号初始化电机电调1
    ceMDOp.initial(&(ceMD3), CE_MD_CTL_RESOURCE_3);     //使用一路Pwm资源号初始化电机电调3
    ceMDOp.initial(&(ceMD2), CE_MD_CTL_RESOURCE_2);     //使用一路Pwm资源号初始化电机电调2
}

/**
  * @brief  设置Pwm的驱动强度，0~1000，对应占空比为0%~100%
  * @param  driverPower[]:Pwm的驱动强度，0~1000，对应占空比为0%~100%
  */
void ceMDCtl_setDriverPower(CeMDDrivePower* drivePower)
{
    ceMDOp.setDriverPower(&ceMD0,drivePower->motorDrivePower0);//配置第0路电机驱动强度，0~1000                
    ceMDOp.setDriverPower(&ceMD1,drivePower->motorDrivePower1);//配置第1路电机驱动强度，0~1000
    ceMDOp.setDriverPower(&ceMD2,drivePower->motorDrivePower2);//配置第2路电机驱动强度，0~1000
    ceMDOp.setDriverPower(&ceMD3,drivePower->motorDrivePower3);//配置第3路电机驱动强度，0~1000
}

/**
  * @brief  初始化CeMD模块操作对象
  */
const CeMDCtlOp ceMDCtlOp = {ceMDCtl_initial,ceMDCtl_setDriverPower};


#ifdef __cplusplus
}
#endif //__cplusplus

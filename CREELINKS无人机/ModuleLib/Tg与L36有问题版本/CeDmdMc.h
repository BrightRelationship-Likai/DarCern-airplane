/**
  ******************************************************************************
  * @file    CeDmdMc.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeDmdMc模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)芯片型号为MC33886VW。由于芯片没有提供刹车(制动)，用户可以控制转动方向使电机反转来进行刹车(制动)。
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_DMD_MC_H__
#define __CE_DMD_MC_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_DMD_MC_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_DMD_MC_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_DMD_MC_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeDmdMc.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
#define CE_DMD_MC_PWM_CYCLE_NS     10000000
/*
 *CeDmdMc属性对像
 */
typedef struct
{
    CePwm   cePwm;                                                              /*!< 模块使用的Pwm对象*/
    CeTg    ceTg;                                                               /*!< 模块使用的Tg对象*/
    uint32  duty;                                                               /*!< 模块电机驱动强度对应的Pwm高电平的时间*/
}CeDmdMc;
/*
 *CeDmdMc操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeDmdMc* ceDmdMc, CE_RESOURCE cePwm, CE_RESOURCE ceTg);
                                                                                /*!< @brief  CeDmdMc模块初始化
                                                                                     @param  ceDmdTb:CeDmdMc属性对象
                                                                                     @param  cePwm:CeDmdMc模块使用的Pwm资源号
                                                                                     @param  ceTg:CeDmdMc模块使用的Tg资源号*/

    void        (*setOn)(CeDmdMc* ceDmdMc);                                     /*!< @brief  输出打开
                                                                                     @param  ceDmdMc:CeDmdMc属性对象指针*/

    void        (*setDriveStrength)(CeDmdMc* ceDmdMc, uint16 driveStrength);    /*!< @brief  调整电机驱动强度，可在输出中进行调整
                                                                                     @param  ceDmdMc:CeDmdMc属性对象指针
                                                                                     @param  driveStrength:电机驱动的强度，范围0-10000*/

    void        (*setDirection)(CeDmdMc* ceDmdMc, uint8 direction);             /*!< @brief  设置电机的转动方向
                                                                                     @param  ceDmdMc:CeDmdMc属性对象指针
                                                                                     @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向*/


    void        (*setOff)(CeDmdMc* ceDmdMc);                                    /*!< @brief  输出关闭
                                                                                     @param  ceDmdMc:CeDmdMc属性对象指针*/

}CeDmdMcOp;
/*
 *CeDmdMc操作对象实例
 */
extern const CeDmdMcOp ceDmdMcOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_DMD_MC_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_DMD_MC_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 设置电机通道由慢到快正转，再配置为返转。
******************************************************************************
#include "Creelinks.h"
#include "CeDmdMc.h"
CeDmdMc myDmdMc;
uint16 drivePower;                              //电机驱动力，0－10000

int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceDmdMcOp.initial(&myDmdMc,R1AGP,R2TI2c);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceDmdMcOp.setDirection(&myDmdMc,0x01);                  //配置通道方向为正向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道电机的驱动力到最大
        {
            ceDmdMcOp.setDriveStrength(&myDmdMc,drivePower);
            ceSystemOp.delayMs(2000);
        }

        ceDmdMcOp.setDirection(&myDmdMc,0x00);                  //配置通道方向为反向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道电机的驱动力到最大
        {
            ceDmdMcOp.setDriveStrength(&myDmdMc,drivePower);
            ceSystemOp.delayMs(2000);
        }
    };
}
******************************************************************************
*/

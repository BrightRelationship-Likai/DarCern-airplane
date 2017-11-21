/**
  ******************************************************************************
  * @file    CeDmdL.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeDmdL模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_DMD_L_H__
#define __CE_DMD_L_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_DMD_L_VERSION__ 1                                                  /*!< 此驱动文件的版本号*/
#define __CE_DMD_L_NEED_CREELINKS_VERSION__ 1                                   /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_DMD_L_NEED_CREELINKS_VERSION__)            /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeDmdL.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

//#define CE_DMD_L_USE_TO_SETP_MOTOR                                            /*!< 是否将模块用于步进电机*/

#ifdef CE_DMD_L_USE_TO_SETP_MOTOR

/*
 *CeDmdL作为步进电机使用时的工作方式
*/
typedef enum
{
    CE_DMD_L_SINGLE_4_SHOOT =0,                                                 /*!< 单四拍*/
    CE_DMD_L_DOUBLE_4_SHOOT,                                                    /*!< 双四拍*/
    CE_DMD_L_8_SHOOT,                                                           /*!< 八拍*/
}CE_DMD_L_STEP_MODE;
/*
 *CeDmdL属性对像
 */
typedef struct
{
    CeTg    ceTg1;                                                              /*!< 模块用作步进电机的第一个Tg对象*/
    CeTg    ceTg2;                                                              /*!< 模块用作步进电机的第二个Tg对象*/
    uint8   around;                                                             /*!< 步进电机转动的步数是否满足一圈*/
    uint8   setpMode;                                                           /*!< 步进电机的工作方式*/
    uint8   status;                                                             /*!< 步进电机的工作状态*/
}CeDmdL;
/*
 *CeDmdL操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeDmdL* ceDmdL, CE_RESOURCE ceTg1, CE_RESOURCE ceTg2);/*!<
                                                                                     @brief  CeDmdL模块用作步进电机初始化
                                                                                     @param  ceDmdL:CeDmdL属性对象指针
                                                                                     @param  ceTg1:CeDmdL模块用作步进电机的第一个Tg资源号
                                                                                     @param  ceTg2:CeDmdL模块用作步进电机的第二个Tg资源号*/

    void        (*setStepMode)(CeDmdL* ceDmdL, CE_DMD_L_STEP_MODE ceDmdLStepMode);/*!<
                                                                                     @brief  步进电机的运行方式
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*setOn)(CeDmdL* ceDmdL);                                       /*!< @brief  模块用作步进电机，输出打开
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*setOff)(CeDmdL* ceDmdL);                                      /*!< @brief  模块用作步进电机，输出关闭
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*stepForward)(CeDmdL* ceDmdL);                                 /*!< @brief  模块用作步进电机，前进一步
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*stepBackward)(CeDmdL* ceDmdL);                                /*!< @brief  模块用作步进电机，后退一步
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

}CeDmdLOp;
/*
 *CeDmdL操作对象实例
 */
extern const CeDmdLOp ceDmdLOp;

#else //CE_DMD_L_USE_TO_SETP_MOTOR

#define CE_DMD_L_PWM1_CYCLE_NS     10000000                                     /*!< DmdL模块第一个通道的Pwm控制转速的周期*/
#define CE_DMD_L_PWM2_CYCLE_NS     10000000                                     /*!< DmdL模块第二个通道的Pwm控制转速的周期*/
/*
 *CeDmdL属性对像
 */
typedef struct
{
    CePwm   cePwm1;                                                             /*!< 模块的第一个通道使用的Pwm对象*/
    CeTg    ceTg1;                                                              /*!< 模块的第一个通道使用的Tg对象*/
    uint32  duty1;                                                              /*!< 模块的第一个通道电机驱动强度对应的Pwm高电平的时间*/
    CePwm   cePwm2;                                                             /*!< 模块的第二个通道使用的Pwm对象*/
    CeTg    ceTg2;                                                              /*!< 模块的第二个通道使用的Tg对象*/
    uint32  duty2;                                                              /*!< 模块的第二个通道电机驱动强度对应的Pwm高电平的时间*/
}CeDmdL;
/*
 *CeDmdL操作对像
 */
typedef struct
{
    CE_STATUS   (*initialCh1)(CeDmdL* ceDmdL, CE_RESOURCE cePwm1, CE_RESOURCE ceTg1);/*!<
                                                                                     @brief  CeDmdL模块初始化第一个通道。
                                                                                     @param  ceDmdL:CeDmdL属性对象指针
                                                                                     @param  cePwm1:CeDmdL模块第一个通道使用的Pwm资源号
                                                                                     @param  ceTg1:CeDmdL模块第一个通道使用的Tg资源号*/

    CE_STATUS   (*initialCh2)(CeDmdL* ceDmdL, CE_RESOURCE cePwm2, CE_RESOURCE ceTg2);/*!<
                                                                                     @brief  CeDmdL模块初始化第一个通道。
                                                                                     @param  ceDmdL:CeDmdL属性对象指针
                                                                                     @param  cePwm2:CeDmdL模块第二个通道使用的Pwm资源号
                                                                                     @param  ceTg2:CeDmdL模块第二个通道使用的Tg资源号*/

    void        (*setCh1On)(CeDmdL* ceDmdL);                                    /*!< @brief  第一个通道输出打开。在此操作前必须要设置转动方向。
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*setCh2On)(CeDmdL* ceDmdL);                                    /*!< @brief  第二个通道输出打开。在此操作前必须要设置转动方向。
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*setCh1DriveStrength)(CeDmdL* ceDmdL, uint16 driveStrength);   /*!< @brief  调整第一个通道电机驱动强度
                                                                                     @param  ceDmdL:CeDmdL属性对象指针
                                                                                     @param  driveStrength:电机驱动的强度，范围0-10000*/

    void        (*setCh2DriveStrength)(CeDmdL* ceDmdL, uint16 driveStrength);   /*!< @brief  调整第二个通道电机驱动强度
                                                                                     @param  ceDmdL:CeDmdL属性对象指针
                                                                                     @param  driveStrength:电机驱动的强度，范围0-10000*/

    void        (*setCh1Direction)(CeDmdL* ceDmdL, uint8 direction);            /*!< @brief  设置第一个通道电机的转动方向
                                                                                     @param  ceDmdL:CeDmdL属性对象指针
                                                                                     @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向*/

    void        (*setCh2Direction)(CeDmdL* ceDmdL, uint8 direction);            /*!< @brief  设置第二个通道电机的转动方向
                                                                                     @param  ceDmdL:CeDmdL属性对象指针
                                                                                     @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向*/

    void        (*ch1Brake)(CeDmdL* ceDmdL);                                    /*!< @brief  第一个通道刹车，而后进行输出关闭操作。
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*ch2Brake)(CeDmdL* ceDmdL);                                    /*!< @brief  第二个通道刹车，而后进行输出关闭操作。
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*setCh1Off)(CeDmdL* ceDmdL);                                   /*!< @brief  第一个通道输出关闭
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

    void        (*setCh2Off)(CeDmdL* ceDmdL);                                   /*!< @brief  第二个通道输出关闭
                                                                                     @param  ceDmdL:CeDmdL属性对象指针*/

}CeDmdLOp;
/*
 *CeDmdL操作对象实例
 */
extern const CeDmdLOp ceDmdLOp;

#endif //CE_DMD_L_USE_TO_SETP_MOTOR

#endif //(__CE_CREELINKS_VERSION__ < __CE_DMD_L_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_DMD_L_H__


/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 模块工作在步进电机方式，测试程序实现前进1000步，然后再后退1000步。注意：需打开宏CE_DMD_L_USE_TO_SETP_MOTOR
******************************************************************************
#include "Creelinks.h"
#include "CeDmdL.h"
CeDmdL myDmdL;
uint16 il;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceDmdLOp.initial(&myDmdL,R2TI2c,R10TI2c);   //注意：模块作为步进电机使用时，无需使用Pwm信号，同时应将模块上两处跳线位置加上挑线。
    ceDmdLOp.setStepMode(&myDmdL,CE_DMD_L_SINGLE_4_SHOOT);//配置步进电机工作方式：单四拍。
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        for(i=0;i<1000;i++)
        {
            ceDmdLOp.stepForward(&myDmdL);      //步进电机前近一步
            ceSystemOp.delayMs(10);
        }

        for(i=0;i<1000;i++)
        {
            ceDmdLOp.stepBackward(&myDmdL);     //步进电机后退一步
            ceSystemOp.delayMs(10);
        }
    };
}
******************************************************************************
*/

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 设置第一个电机通道由慢到快正转，再配置为返转；然后设置第二个电机通道由慢到快正转 ，再配置为反转。注意：需关闭宏CE_DMD_L_USE_TO_SETP_MOTOR
******************************************************************************
#include "Creelinks.h"
#include "CeDmdL.h"
CeDmdL myDmdL;
uint16 drivePower;                              //电机驱动力，0－10000
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceDmdLOp.initialCh1(&myDmdL,R1AGP,R2TI2c);
    ceDmdLOp.initialCh2(&myDmdL,R5ACGPW,R10TI2c);

    while (1)
    {
        ceTaskOp.mainTask();                                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceDmdLOp.setCh1Direction(&myDmdL,0x01);                 //配置通道1方向为正向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道1电机的驱动力到最大
        {
            ceDmdLOp.setCh1DriveStrength(&myDmdL,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdLOp.ch1Brake(&myDmdL);                             //通道1的电机进行刹车操作

        ceDmdLOp.setCh1Direction(&myDmdL,0x00);                 //配置通道1方向为反向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道1电机的驱动力到最大
        {
            ceDmdLOp.setCh1DriveStrength(&myDmdL,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdLOp.ch1Brake(&myDmdL);                             //通道1的电机进行刹车操作


        ceDmdLOp.setCh2Direction(&myDmdL,0x01);                 //配置通道2方向为正向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道2电机的驱动力到最大
        {
            ceDmdLOp.setCh2DriveStrength(&myDmdL,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdLOp.ch2Brake(&myDmdL);                             //通道2的电机进行刹车操作

        ceDmdLOp.setCh2Direction(&myDmdL,0x00);                 //配置通道2方向为反向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道2电机的驱动力到最大
        {
            ceDmdLOp.setCh2DriveStrength(&myDmdL,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdLOp.ch2Brake(&myDmdL);                             //通道2的电机进行刹车操作
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeDmdTb.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeDmdTb模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)芯片型号为TB6612FNG
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_DMD_TB_H__
#define __CE_DMD_TB_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_DMD_TB_VERSION__ 1                                                 /*!< 此驱动文件的版本号*/
#define __CE_DMD_TB_NEED_CREELINKS_VERSION__ 1                                  /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_DMD_TB_NEED_CREELINKS_VERSION__)           /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeDmdTb.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
#define CE_DMD_TB_PWM1_CYCLE_NS     10000000                                    /*!< DmdTb模块第一个通道的Pwm控制转速的周期*/
#define CE_DMD_TB_PWM2_CYCLE_NS     10000000                                    /*!< DmdTb模块第二个通道的Pwm控制转速的周期*/
/*
 *CeDmdTb属性对像
 */
typedef struct
{
    CePwm   cePwm1;                                                             /*!< 模块的第一个通道使用的Pwm对象*/
    CeTg    ceTg1;                                                              /*!< 模块的第一个通道使用的Tg对象*/
    uint32  duty1;                                                              /*!< 模块的第一个通道电机驱动强度对应的Pwm高电平的时间*/
    CePwm   cePwm2;                                                             /*!< 模块的第二个通道使用的Pwm对象*/
    CeTg    ceTg2;                                                              /*!< 模块的第二个通道使用的Tg对象*/
    uint32  duty2;                                                              /*!< 模块的第二个通道电机驱动强度对应的Pwm高电平的时间*/
}CeDmdTb;
/*
 *CeDmdTb操作对像
 */
typedef struct
{
    CE_STATUS   (*initialCh1)(CeDmdTb* ceDmdTb, CE_RESOURCE cePwm1, CE_RESOURCE ceTg1);
                                                                                /*!< @brief  CeDmdTb模块初始化第一个通道。第一个通道可以单独使用，第二个通道不可以脱离第一个通道单独使用！
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针
                                                                                     @param  cePwm1:CeDmdTb模块第一个通道使用的Pwm资源号
                                                                                     @param  ceTg1:CeDmdTb模块第一个通道使用的Tg资源号*/

    CE_STATUS   (*initialCh2)(CeDmdTb* ceDmdTb, CE_RESOURCE cePwm2, CE_RESOURCE ceTg2);
                                                                                /*!< @brief  CeDmdTb模块初始化第一个通道。第一个通道可以单独使用，第二个通道不可以脱离第一个通道单独使用！
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针
                                                                                     @param  cePwm2:CeDmdTb模块第二个通道使用的Pwm资源号
                                                                                     @param  ceTg2:CeDmdTb模块第二个通道使用的Tg资源号*/

    void        (*setCh1On)(CeDmdTb* ceDmdTb);                                  /*!< @brief  第一个通道输出打开。在此操作必须要设置转动方向，如果是刹车后可以不用设置转动方向，转动方向则保持为刹车前的转动方向。
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针*/

    void        (*setCh2On)(CeDmdTb* ceDmdTb);                                  /*!< @brief  第二个通道输出打开。在此操作必须要设置转动方向，如果是刹车后可以不用设置转动方向，转动方向则保持为刹车前的转动方向。
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针*/

    void        (*setCh1DriveStrength)(CeDmdTb* ceDmdTb, uint16 driveStrength); /*!< @brief  调整第一个通道电机驱动强度
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针
                                                                                     @param  driveStrength:电机驱动的强度，范围0-10000*/

    void        (*setCh2DriveStrength)(CeDmdTb* ceDmdTb, uint16 driveStrength); /*!< @brief  调整第二个通道电机驱动强度
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针
                                                                                     @param  driveStrength:电机驱动的强度，范围0-10000*/

    void        (*setCh1Direction)(CeDmdTb* ceDmdTb, uint8 direction);          /*!< @brief  设置第一个通道电机的转动方向
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针
                                                                                     @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向*/

    void        (*setCh2Direction)(CeDmdTb* ceDmdTb, uint8 direction);          /*!< @brief  设置第二个通道电机的转动方向
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针
                                                                                     @param  direction:转动的方向，0x00表示反向，0x01或大于0x00表示正向*/

    void        (*ch1Brake)(CeDmdTb* ceDmdTb);                                  /*!< @brief  第一个通道刹车，输出暂停
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针*/

    void        (*ch2Brake)(CeDmdTb* ceDmdTb);                                  /*!< @brief  第二个通道刹车，输出暂停
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针*/

    void        (*setCh1Off)(CeDmdTb* ceDmdTb);                                 /*!< @brief  第一个通道输出关闭
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针*/

    void        (*setCh2Off)(CeDmdTb* ceDmdTb);                                 /*!< @brief  第二个通道输出关闭
                                                                                     @param  ceDmdTb:CeDmdTb属性对象指针*/

}CeDmdTbOp;
/*
 *CeDmdTb操作对象实例
 */
extern const CeDmdTbOp ceDmdTbOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_DMD_TB_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_DMD_TB_H__


/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 设置第一个电机通道由慢到快正转，再配置为返转；然后设置第二个电机通道由慢到快正转 ，再配置为反转。
******************************************************************************
#include "Creelinks.h"
#include "CeDmdTb.h"
CeDmdTb myDmdTb;
uint16 drivePower;                              //电机驱动力，0－10000
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceDmdTbOp.initialCh1(&myDmdTb,R1AGP,R2TI2c);
    ceDmdTbOp.initialCh2(&myDmdTb,R5ACGPW,R10TI2c);

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceDmdTbOp.setCh1Direction(&myDmdTb,0x01);               //配置通道1方向为正向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道1电机的驱动力到最大
        {
            ceDmdTbOp.setCh1DriveStrength(&myDmdTb,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdTbOp.ch1Brake(&myDmdTb);                           //通道1的电机进行刹车操作

        ceDmdTbOp.setCh1Direction(&myDmdTb,0x00);               //配置通道1方向为反向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道1电机的驱动力到最大
        {
            ceDmdTbOp.setCh1DriveStrength(&myDmdTb,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdTbOp.ch1Brake(&myDmdTb);                           //通道1的电机进行刹车操作


        ceDmdTbOp.setCh2Direction(&myDmdTb,0x01);               //配置通道2方向为正向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道2电机的驱动力到最大
        {
            ceDmdTbOp.setCh2DriveStrength(&myDmdTb,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdTbOp.ch2Brake(&myDmdTb);                           //通道2的电机进行刹车操作

        ceDmdTbOp.setCh2Direction(&myDmdTb,0x00);               //配置通道2方向为反向
        for(drivePower=0;drivePower<=10000;drivePower+= 1000)   //从0开始配置通道2电机的驱动力到最大
        {
            ceDmdTbOp.setCh2DriveStrength(&myDmdTb,drivePower);
            ceSystemOp.delayMs(2000);
        }
        ceDmdTbOp.ch2Brake(&myDmdTb);                           //通道2的电机进行刹车操作
    };
}
******************************************************************************
*/

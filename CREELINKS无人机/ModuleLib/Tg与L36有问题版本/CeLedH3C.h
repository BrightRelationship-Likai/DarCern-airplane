/**
  ******************************************************************************
  * @file    CeLedH3C.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeXxxZzz模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_LED_3C_H__
#define __CE_LED_3C_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_LED_3C_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_LED_3C_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_LED_3C_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeLedH3C.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

#define CE_LED_3C_ALL_COLOR                                                 /*!< 如果想显示6.5K真色彩，请打开此宏定义*/


#define CE_LED_3C_RED       0xF800                                          /*!< 红色*/
#define CE_LED_3C_GREEN     0x07E0                                          /*!< 绿色*/
#define CE_LED_3C_BLUE      0x001F                                          /*!< 蓝色*/
#define CE_LED_3C_YELLOW    0xFFE0                                          /*!< 黄色*/
#define CE_LED_3C_CYAN      0x051D                                          /*!< 青色*/
#define CE_LED_3C_PURPLE    0xA254                                          /*!< 紫色*/
#define CE_LED_3C_WHITE     0xFFFF                                          /*!< 白色*/

/*
 *CeLedH3C属性对象
 */
typedef struct
{
    CeTg    ceTg;                                                            /*!< 模块使用到的Tg资源属性对象*/
    uint16  led3CColor;                                                      /*!< CeLedH3C当前显示的颜色*/
    uint8   workMode;                                                        /*!< 模块的工作模式标志*/
#ifdef CE_LED_3C_ALL_COLOR
    CePwm   cePwmRed;                                                        /*!< 模块在真彩色下，控制红色Led的Pwm资源属性对象*/
    CePwm   cePwmGreen;                                                      /*!< 模块在真彩色下，控制绿色Led的Pwm资源属性对象*/
    CePwm   cePwmBlue;                                                       /*!< 模块在真彩色下，控制蓝色Led的Pwm资源属性对象*/
#endif
}CeLedH3C;

/*
 *CeLedH3C操作对象
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeLedH3C* ceLedH3C,CE_RESOURCE ceGpioRed, CE_RESOURCE ceGpioGreen, CE_RESOURCE ceGpioBlue);/*!<
                                                                                  @brief CeLedH3C模块使用3个Gpio口来完成初始化
                                                                                  @param ceLedH3C:CeLedH3C属性对象指针
                                                                                  @param ceGpioRed:CeLedH3C模块使用的红色LED的资源号
                                                                                  @param ceGpioGreen:CeLedH3C模块使用的绿色LED的资源号
                                                                                  @param ceGpioBlue:CeLedH3C模块使用的蓝色LED的资源号*/
#ifdef CE_LED_3C_ALL_COLOR
    CE_STATUS   (*initialByThreePwm)(CeLedH3C* ceLedH3C, CE_RESOURCE cePwmRed, CE_RESOURCE cePwmGreen, CE_RESOURCE cePwmBlue);/*!<
                                                                                  @brief CeLedH3C模块使用3个Gpio口来完成初始化
                                                                                  @param ceLedH3C:CeLedH3C属性对象指针
                                                                                  @param cePwmRed:CeLedH3C模块使用的红色LED的资源号
                                                                                  @param cePwmGreen:CeLedH3C模块使用的绿色LED的资源号
                                                                                  @param cePwmBlue:CeLedH3C模块使用的蓝色LED的资源号*/
#endif

    CE_STATUS   (*initialByTg)(CeLedH3C* ceLedH3C,CE_RESOURCE ceTg);         /*!< @brief CeLedH3C模块使用Tg进行初始化
                                                                                  @param ceLedH3C:CeLedH3C属性对象指针
                                                                                  @param ceTg:CeLedH3C模块使用的资源号*/

    void        (*setColor)(CeLedH3C* ceLedH3C, uint16 color);               /*!< @brief 设置Led的颜色,如果设置的是真色彩，请打开宏定义CE_LED_3C_ALL_COLOR,否则只能使用宏定义的标准色
                                                                                  @param ceLedH3C:CeLedH3C属性对象指针
                                                                                  @param colorStatus:欲设置的颜色*/

    void        (*setOn)(CeLedH3C* ceLedH3C);                                /*!< @brief 设置Led状态为开
                                                                                  @param ceLedH3C:CeLedH3C属性对象指针*/

    void        (*setOff)(CeLedH3C* ceLedH3C);                               /*!< @brief 设置Led状态为关
                                                                                  @param ceLedH3C:CeLedH3C属性对象指针*/
}CeLedH3COp;
/*
*CeLedH3C操作对象实例
*/
extern const CeLedH3COp ceLedH3COp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_LED_3C_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_LED_3C_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境),基于ELinkSTM核心板
* @function 使模块重复显示7种颜色
******************************************************************************
#include "Creelinks.h"
#include "CeLedH3C.h"
CeLedH3C myLedH3C;
int main(void)
{
    ceSystemOp.initial();                               //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                          //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceLedH3COp.initialByTg(&myLedH3C, R2TI2c);          //使用Tg口初始化myLedH3C对象
    while (1)
    {
        ceTaskOp.mainTask();                            //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_RED);    //显示红色
        ceSystemOp.delayMs(200);                        //延时200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_GREEN);  //显示绿色
        ceSystemOp.delayMs(200);                        //延时200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_BLUE);   //显示蓝色
        ceSystemOp.delayMs(200);                        //延时200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_YELLOW); //显示黄色
        ceSystemOp.delayMs(200);                        //延时200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_CYAN);   //显示青色
        ceSystemOp.delayMs(200);                        //延时200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_PURPLE); //显示紫色
        ceSystemOp.delayMs(200);                        //延时200ms
        ceLedH3COp.setColor(&myLedH3C, CE_LED_3C_WHITE);  //显示白色
        ceSystemOp.delayMs(200);                        //延时200ms
        ceLedH3COp.setOff(&myLedH3C);                     //关闭显示
        ceSystemOp.delayMs(1000);                       //延时1000ms
    };
}
******************************************************************************
*/

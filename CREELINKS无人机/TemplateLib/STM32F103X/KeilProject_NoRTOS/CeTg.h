/**
  ******************************************************************************
  * @file    CeTg.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2016-08-05
  * @brief   Creelinks平台 CeTg(Three Gpio)库头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TG_H__
#define __CE_TG_H__

#include "CeMcu.h"

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplu

#ifdef __CE_USE_TG__

/**
  * @brief  结构体，Tg对象可用属性集合
  */
typedef struct
{
    CE_RESOURCE ceResource;                     /*!< Tg对应的资源号*/
    CE_RESOURCE ceResource0;                    /*!< Tg的第一个Gpio口对应的资源号*/
    CE_RESOURCE ceResource1;                    /*!< Tg的第二个Gpio口对应的资源号*/
    CE_RESOURCE ceResource2;                    /*!< Tg的第三个Gpio口对应的资源号*/

    CeExTgPar   ceExTgPar;                      /*!< 与处理器平台相关的额外参数结构体，用以提高代码效率，用户无须关注*/
} CeTg;
/**
  * @brief  结构体，Tg对象可用操作集合
  */
typedef struct
{
    CE_STATUS   (*initial)(CeTg* ceTg, CE_GPIO_MODE ceGpioMode0, CE_GPIO_MODE ceGpioMode1, CE_GPIO_MODE ceGpioMode2);/*!<
                                                     @brief 初始化一个Tg资源
                                                     @param ceTg:Tg属性对象指针
                                                     @param ceGpioMode0:Tg第一个Gpio口的工作方式
                                                     @param ceGpioMode1:Tg第二个Gpio口的工作方式
                                                     @param ceGpioMode2:Tg第三个Gpio口的工作方式*/

    void        (*setGpio0)(CeTg* ceTg);        /*!< @brief 设置Tg第一个GPIO的值为1
                                                     @param ceTg:Tg属性对象指针*/

    void        (*resetGpio0)(CeTg* ceTg);      /*!< @brief 设置Tg第一个GPIO的值为0
                                                     @param ceTg:Tg属性对象指针*/

    uint8       (*getGpio0Bit)(CeTg* ceTg);     /*!< @brief 获取Tg资源第一个GPIO口的值
                                                     @param ceTg:Tg属性对象指针
                                                     @return Tg资源第一个Gpio口的电平*/

    void        (*setGpio0Mode)(CeTg* ceTg,  CE_GPIO_MODE ceGpioMode);/*!<
                                                     @brief 设置Tg第一个GPIO的工作模式
                                                     @param ceTg:Tg属性对象指针
                                                     @param ceGpioMode:Gpio的工作方式*/

    void        (*setGpio1)(CeTg* ceTg);        /*!< @brief 设置Tg第二个GPIO的值为1
                                                     @param ceTg:Tg属性对象指针*/

    void        (*resetGpio1)(CeTg* ceTg);      /*!< @brief 设置Tg第二个GPIO的值为0
                                                     @param ceTg:Tg属性对象指针*/

    uint8       (*getGpio1Bit)(CeTg* ceTg);     /*!< @brief 获取Tg资源第二个GPIO口的值
                                                     @param ceTg:Tg属性对象指针*/

    void        (*setGpio1Mode)(CeTg* ceTg,  CE_GPIO_MODE ceGpioMode);/*!<
                                                     @brief 设置Tg第二个GPIO的工作模式
                                                     @param ceTg:Tg属性对象指针
                                                     @param ceGpioMode:Gpio的工作方式*/

    void        (*setGpio2)(CeTg* ceTg);        /*!< @brief 设置Tg第三个GPIO的值为1
                                                     @param ceTg:Tg属性对象指针*/

    void        (*resetGpio2)(CeTg* ceTg);      /*!< @brief 设置Tg第三个GPIO的值为0
                                                     @param ceTg:Tg属性对象指针*/

    uint8       (*getGpio2Bit)(CeTg* ceTg);     /*!< @brief 获取Tg资源第三个GPIO口的值
                                                     @param ceTg:Tg属性对象指针*/

    void        (*setGpio2Mode)(CeTg* ceTg,  CE_GPIO_MODE ceGpioMode);/*!<
                                                     @brief 设置Tg第三个GPIO的工作模式
                                                     @param ceTg:Tg属性对象指针
                                                     @param ceGpioMode:Gpio的工作方式*/
} CeTgOp;
extern const CeTgOp ceTgOp;                 /*!< 所有与Tg相关的操作*/

#endif //__CE_USE_TG__

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TG_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境)
* @function 设置Tg的三个Gpio口，按顺序每500ms切换一次电平状态
******************************************************************************

#include "Creelinks.h"
CeTg myTg;                                      //定义Tg属性对象
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(Uartx);                        //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    myTg.ceResource = RxT;                      //指定Tg使用的资源号
    //myTg.ceResource0 = RxG;                   //第二种确定Tg使用的资源号方法，即使用三个Gpio资源
    //myTg.ceResource1 = RxG;                   //第二种确定Tg使用的资源号方法，即使用三个Gpio资源
    //myTg.ceResource2 = RxG;                   //第二种确定Tg使用的资源号方法，即使用三个Gpio资源
    ceTgOp.initial(&myTg, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);//初始化Tg口，并指定三个口的工作模式
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环
        //TODO:请在此处插入用户操作
        ceGpioOp.setBit(&myTg);                 //设置Tg的第一个IO口为高电平
        ceSystemOp.delayMs(500);                //延时500ms
        ceGpioOp.resetBit(&myTg);               //设置Tg的第一个IO口为低电平

        ceGpioOp.setBit(&myTg);                 //设置Tg的第二个IO口为高电平
        ceSystemOp.delayMs(500);                //延时500ms
        ceGpioOp.resetBit(&myTg);               //设置Tg的第二个IO口为低电平

        ceGpioOp.setBit(&myTg);                 //设置Tg的第三个IO口为高电平
        ceSystemOp.delayMs(500);                //延时500ms
        ceGpioOp.resetBit(&myTg);               //设置Tg的第三个IO口为低电平
    };
}
******************************************************************************
*/

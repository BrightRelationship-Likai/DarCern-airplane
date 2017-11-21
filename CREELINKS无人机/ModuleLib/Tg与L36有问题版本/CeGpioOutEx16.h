/**
  ******************************************************************************
  * @file    CeGpioOutEx16.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeGpioOutEx16模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_GPIO_OUT_EX16_H__
#define __CE_GPIO_OUT_EX16_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_GPIO_OUT_EX16_VERSION__ 1                                              /*!< 此驱动文件的版本号*/
#define __CE_GPIO_OUT_EX16_NEED_CREELINKS_VERSION__ 1                               /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_GPIO_OUT_EX16_NEED_CREELINKS_VERSION__)        /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeGpioOutEx16.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

/*
 *CeGpioOutEx16属性对像
 */
typedef struct
{
    CeTg ceTg;              /*!< CeGpioOutEx16模块使用到的Tg资源号*/
    uint16 ceGpioStatus;    /*!< CeGpioOutEx16模块全部的Gpio口的状态*/
}CeGpioOutEx16;

/*
 *CeGpioOutEx16操作对像
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(CeGpioOutEx16* ceGpioOutEx16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                                     @brief  CeGpioOutEx16模块使用Gpio进行初始化
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16属性对象指针
                                                                                     @param ceGpio0:CeGpioOutEx16模块使用的第一个Gpio的资源号
                                                                                     @param ceGpio1:CeGpioOutEx16模块使用的第二个Gpio的资源号
                                                                                     @param ceGpio2:CeGpioOutEx16模块使用的第三个Gpio的资源号*/

    CE_STATUS   (*initialByTg)(CeGpioOutEx16* ceGpioOutEx16, CE_RESOURCE ceTg); /*!< @brief CeGpioOutEx16模块初始化
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16属性对象指针
                                                                                     @param ceTg:CeGpioOutEx16模块使用的资源号*/

    void        (*setBit)(CeGpioOutEx16* ceGpioOutEx16, uint8 index);           /*!< @brief 设置指定索引的Gpio口
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16属性对象指针
                                                                                     @param index:欲操作Gpio口的索引，范围0-15*/

    void        (*resetBit)(CeGpioOutEx16* ceGpioOutEx16, uint8 index);         /*!< @brief 复位指定索引的Gpio口
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16属性对象指针
                                                                                     @param index:欲操作的Gpio口的索引，范围0-15*/

    void        (*setData)(CeGpioOutEx16* ceGpioOutEx16,uint16 data);           /*!< @brief 以一个16位数值设置全部Gpio口的状态，其中最低位对应Gpio0。
                                                                                     @param ceGpioOutEx16:CeGpioOutEx16属性对象指针
                                                                                     @param data:模块所有口的电平输出值*/
}CeGpioOutEx16Op;

/*
 *CeGpioOutEx16操作对象实例
 */
extern const CeGpioOutEx16Op ceGpioOutEx16Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_GPIO_OUT_EX16_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_GPIO_OUT_EX16_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 依次控制16个Gpio口输出高电平，达到流水灯效果
******************************************************************************
#include "Creelinks.h"
#include "CeGpioOutEx16.h"
CeGpioOutEx16 myEx;
uint8 index = 0;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceGpioOutEx16Op.initialByTg(&myEx, R2TI2c); //使用R2TI2c资源号初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceGpioOutEx16Op.setBit(&myEx, index%16);//设置index%16口高电平
        ceSystemOp.delayMs(1000);
        ceGpioOutEx16Op.resetBit(&myEx,index%16);//设置index%16口低电平
        index++;
    };
}
******************************************************************************
*/

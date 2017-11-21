/**
  ******************************************************************************
  * @file    CeGpioInEx16.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeGpioInEx16模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_GPIO_IN_EX16_H__
#define __CE_GPIO_IN_EX16_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_GPIO_IN_EX16_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_GPIO_IN_EX16_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_GPIO_IN_EX16_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeGpioInEx16.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeGpioInEx16属性对像
 */
typedef struct
{
    CeTg ceTg;                                                                  /*!< */
}CeGpioInEx16;
/*
 *CeGpioInEx16操作对像
 */
typedef struct
{

    CE_STATUS   (*initialByGpio)(CeGpioInEx16* ceGpioInEx16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                                     @brief  CeGpioInEx16模块使用Gpio进行初始化
                                                                                     @param ceGpioInEx16:CeGpioInEx16属性对象指针
                                                                                     @param ceGpio0:CeGpioInEx16模块使用的第一个Gpio的资源号
                                                                                     @param ceGpio1:CeGpioInEx16模块使用的第二个Gpio的资源号
                                                                                     @param ceGpio2:CeGpioInEx16模块使用的第三个Gpio的资源号*/

    CE_STATUS   (*initialByTg)(CeGpioInEx16* ceGpioInEx16, CE_RESOURCE ceTg);   /*!< @brief CeGpioInEx16模块初始化
                                                                                     @param ceGpioInEx16:CeGpioInEx16属性对象指针
                                                                                     @param ceTg:CeGpioInEx16模块使用的资源号*/

    uint8       (*getBit)(CeGpioInEx16* ceGpioInEx16, uint8 index);             /*!< @brief 获取指定索引的Gpio口电平
                                                                                     @param ceGpioInEx16:CeGpioInEx16属性对象指针
                                                                                     @param index:欲操作Gpio口的索引，范围0-15
                                                                                     @return 返回0x01:高电平；返回0x00:低电平*/

    uint16      (*getData)(CeGpioInEx16* ceGpioInEx16);                         /*!< @brief 获取全部IO口的状态，高位对应Gpio15
                                                                                     @param ceGpioInEx16:CeGpioInEx16属性对象指针*/
}CeGpioInEx16Op;
/*
 *CeGpioInEx16操作对象实例
 */
extern const CeGpioInEx16Op ceGpioInEx16Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_GPIO_IN_EX16_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_GPIO_IN_EX16_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 在0、6两个In口上各连接一个按钮，软件获取两个按钮的状态，并发送至上位机
******************************************************************************
#include "Creelinks.h"
#include "CeGpioInEx16.h"
CeGpioInEx16 myGpioInEx16;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceGpioInEx16Op.initialByTg(&myGpioInEx16,R2TI2c);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceDebugOp.printf("In 0 status:%d \n",ceGpioInEx16Op.getBit(&myGpioInEx16,0));
        ceDebugOp.printf("In 6 status:%d \n\n",ceGpioInEx16Op.getBit(&myGpioInEx16,6));
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

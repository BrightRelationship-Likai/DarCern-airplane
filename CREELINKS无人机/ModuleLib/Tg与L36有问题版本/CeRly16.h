/**
  ******************************************************************************
  * @file    CeRly16.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRly16模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY16_H__
#define __CE_RLY16_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY16_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_RLY16_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY16_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeRly16.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeRly16属性对像
*/
typedef struct
{
    uint16  rlyStatus;                                              /*!< 保存所有的继电器状态*/
    CeTg    ceTg;                                                   /*!< 模块使用到的Tg接口资源*/
}CeRly16;
/*
 *CeRly16操作对像
*/
typedef struct
{
    CE_STATUS(*initialWithTg)(CeRly16* ceRly16, CE_RESOURCE ceTg);  /*!< @brief  CeRly16模块初始化
                                                                         @param  ceRly16:CeRly16属性对象指针
                                                                         @param  ceTg:CeRly16模块使用的资源号*/

    CE_STATUS(*initialWithGpio)(CeRly16* ceRly16, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);
                                                                    /*!< @brief  使用三个Gpio口来完成CeRly16模块初始化
                                                                         @param  ceRly16:CeRly16属性对象指针
                                                                         @param  ceGpio0:第一个Gpio口
                                                                         @param  ceGpio1:第二个Gpio口
                                                                         @param  ceGpio2:第三个Gpio口*/

    void(*setOn)(CeRly16* ceRly16, uint8 rlyIndex);                 /*!< @brief 设置继电器闭合
                                                                         @param ceRly16:CeRly16属性对象指针
                                                                         @param rlyIndex:需要闭合的继电器序号*/

    void(*setOff)(CeRly16* ceRly16, uint8 rlyIndex);                /*!< @brief 设置继电器断开
                                                                         @param ceRly16:CeRly16属性对象指针
                                                                         @param rlyIndex:需要断开的继电器序号*/
}CeRly16Op;
/*
*CeRly16操作对象实例
*/
extern const CeRly16Op ceRly16Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY16_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_RLY16_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 配置继电器依次吸合与断开
******************************************************************************
#include "Creelinks.h"
#include "CeRly16.h"
CeRly16 myRly;
uint8 index = 0;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceRly16Op.initialWithTg(&myRly, R2TI2c);    //使用R2TI2c的Tg功能初始化模块
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceRly16Op.setOn(&myRly, index % 16);    //设置继电器状态为吸合
        ceSystemOp.delayMs(500);
        ceRly16Op.setOff(&myRly, index % 16);   //设置继电器状态为断开
        ceSystemOp.delayMs(500);
        index++;
    };
}
******************************************************************************
*/

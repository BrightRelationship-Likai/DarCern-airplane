/**
  ******************************************************************************
  * @file    CeSysCtl.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSysCtl模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_SYS_CTL_H__
#define __CE_SYS_CTL_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "creelinks.h"
/*
 *枚举，定义四个LED的闪烁方式
 */
typedef enum 
{
    CE_LED_CTL_MODE_OFF = 0x00,             /*!< 所有LED均不亮状态*/
    CE_LED_CTL_MODE_IN_CFG,                 /*!< 处于初始化及参数配置状态*/
    CE_LED_CTL_MODE_IN_NORMAL,              /*!< 正常工作状态*/
    CE_LED_CTL_MODE_IN_ERROR,               /*!< 故障状态*/
    CE_LED_CTL_MODE_FLASH_CYCLE_P,          /*!< 偏航正*/
    CE_LED_CTL_MODE_FLASH_CYCLE_N,          /*!< 偏航负*/
    CE_LED_CTL_MODE_GOTO_FRONT,             /*!< 俯*/
    CE_LED_CTL_MODE_GOTO_BACK,              /*!< 仰*/
    CE_LED_CTL_MODE_GOTO_LEFT,              /*!< 左翻滚*/
    CE_LED_CTL_MODE_GOTO_RIGHT,             /*!< 右翻滚*/
}CE_LED_CTL_MODE;

/*
 *CeSysCtl操作对像
 */
typedef struct
{
    void        (*initial)(void);               /*!< @brief  系统控制函数初始化*/

    fp32        (*getBatVol)(void);             /*!< @brief  获取锂电池电压
                                                     @return 当前锂电池的电压值，单位V*/

    void        (*setAlarm)(uint16 sayMs,uint16 sleepMs, uint8 sayTimes); /*!< 
                                                     @brief  配置发声装置的发声方式，即配置一个周期的发声时间与停止发声息时间，及周期次数，使发出滴...滴...声
                                                     @param  sayMs:发声时间长度，单位Ms
                                                     @param  sleepMs:停止发声时间长度，单位Ms
                                                     @param  sayTimes:发声次数*/

    uint8       (*getBtnSta)(uint8 btnIndex);   /*!< @brief  获取可用按钮状态
                                                     @param  btnIndex:按钮索引
                                                     @return 0:表示未按下；1:表示已按下*/

    fp32        (*getSysRunCycleS)(void);       /*!< @brief  采用定时器或其它方式，统计两次调用此函数的时间间隔，单位秒
                                                     @return 两次调用此函数的时间间隔，单位秒*/

    uint8       (*checkConnectStatus)(void);    /*!< @brief 检测是否通讯中断
                                                     @return 1：通讯正常； 0：通讯中断*/

    void        (*setLedMode)(CE_LED_CTL_MODE ctlMode);/*!< 
                                                     @brief 配置四个LED闪烁的方式
                                                     @param ctlMode:四个LED闪烁的方式*/

    CE_LED_CTL_MODE (*getLedMode)(void);        /*!< @brief 获取当前四个LED闪烁的方式
                                                     @return 当前四个LED闪烁的方式*/

   // void        (*delayMs)(uint32 ms);

}CeSysCtlOp;
/*
 *CeSysCtl操作对象实例
 */
extern const CeSysCtlOp ceSysCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SYS_CTL_H__

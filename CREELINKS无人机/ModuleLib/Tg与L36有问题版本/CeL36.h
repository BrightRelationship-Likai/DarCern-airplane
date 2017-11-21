/**
  ******************************************************************************
  * @file    CeL36.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2016-09-28
  * @brief
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_L36_H__
#define __CE_L36_H__

#include "CeMcu.h"
#include "CeSpi.h"
#include "CeI2c.h"
#include "CeInt.h"
#include "CeGpio.h"
#include "CePwm.h"

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#ifdef __CE_USE_L36__

/**
  * @brief  枚举，LCD通讯的速率
  */
typedef enum
{
    CE_L36_BUS_SPEED_H,
    CE_L36_BUS_SPEED_M,
    CE_L36_BUS_SPEED_L,
}CE_L36_BUS_SPEED;

/**
  * @brief  结构体，L36属性对象操作集合
  */
typedef struct
{
    CE_RESOURCE         ceResource;
    CE_L36_BUS_SPEED    ceL36BusSpeed;
    CePwm               cePwm;
    CeSpiMaster         ceSpiMaster;
    CeI2cMaster         ceI2cMaster;
    CeInt               ceInt;
    CeGpio              ceGpioEx0;
    CeGpio              ceGpioEx1;
}CeL36;

/**
  * @brief  结构体，L36操作对象集合
  */
typedef struct
{

    CE_STATUS   (*initial)(CeL36* ceL36);               /*!< @brief 初始化L36*/

    void        (*writeData)(uint16 addr, uint16 data); /*!< @brief 向L36写数据
                                                             @param addr:欲写数据的地址
                                                             @param data:欲写的数据*/

    uint32      (*readData)(uint16 addr);               /*!< @brief 从L36读数据
                                                             @param addr:欲读数据的地址
                                                             @return 读取到的数据*/

    void        (*setRST)(void);                        /*!< @brief 设置L36RST对应的Gpio值为1，用来对挂载在L36的外部设备进行复位*/

    void        (*resetRST)(void);                      /*!< @brief 设置L36RST对应的Gpio值为0，用来对挂载在L36的外部设备进行复位*/

}CeL36Op;
extern const CeL36Op ceL36Op;                       /*!< 所有与L36相关的操作*/

#endif //__CE_USE_L36__

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_L36_H__

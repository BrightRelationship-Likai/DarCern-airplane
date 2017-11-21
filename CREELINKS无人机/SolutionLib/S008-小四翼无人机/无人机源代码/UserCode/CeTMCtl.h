/**
  ******************************************************************************
  * @file    CeTMCtl.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   数据传输管理，用于WIFI、蓝牙、2.4G模块的初始化；数据发送接收等处理
  ******************************************************************************
  * @attention
  *
  *1)移植请注意：请在initial函数中，定义各个模块使用到的资源。
  *2)发送数据调用send函数，输入Byte数组即可；
  *3)接收到数据后自动调用初始化时提供的回调，传入未经任何处理的Byte数组。
  *4)接收到数据后，调用的回调函数，在ceTaskOp.mainTask()中执行，请保证主main函数中的ceTaskOp.mainTask()能够被周期调用 
  * 
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TMU_CTL_H__
#define __CE_TMU_CTL_H__
#include "Creelinks.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/*
 *CeTMCtl操作对像
 */
typedef struct
{
    CE_STATUS (*initial)(uint8 iniArg);                         /*!< @brief CeTMCtl模块初始化
                                                                     @param iniArg:初始化时，传递的可自由配置参数*/

    void      (*setRecvCallBack)(void (*recvCallBack)(uint8* recvBuf, uint16 recvCount));/*!< 
                                                                     @brief CeTMCtl模块配置接收数据的回调
                                                                     @param recvCallBack:用户需提供的回调函数*/

    CE_STATUS (*sendData)(uint8* dataBuf, uint16 dataCount);    /*!< @brief 发送数据，注意：函数内部会检测距离上一次发送数据的时间是否大于intervalMs，如果小于则直接返回
                                                                     @param dataBuf:发送缓存地址
                                                                     @param dataCount:发送缓存数据长度*/

    CE_STATUS (*checkConnectStatus)(void);                      /*!< @brief 检测是否通讯中断
                                                                     @return CE_STATUS_SUCCESS：通讯正常； 其它：通讯中断*/

    uint32    (*getSendIntervalMs)(void);                       /*!< @brief 检测距离上一次发送数据到此时的时间间隔
                                                                     @return 距离上一次发送数据到现在的时间间隔，单位ms*/
}CeTMCtlOp;
/*
 *CeTMCtl操作对象实例
 */
extern const CeTMCtlOp ceTMCtlOp;

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_TMU_CTL_H__



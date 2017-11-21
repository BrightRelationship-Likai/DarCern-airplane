/**
  ******************************************************************************
  * @file    CeTMCtl.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   数据传输管理，用于ESP8266、蓝牙、2.4G模块的初始化；数据发送接收等处理
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
#include "CeTMCtl.h"
#include "CeESP8266.h"
#include "CeNRF24L01P.h"

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_TM_CTL_ESP8266_RESOURCE      Uart2               /*!< 配置CeESP8266模块使用到的UART资源号*/

#define CE_TM_CTL_ESP8266_SSID        "CC Technology"             /*!< 配置无人机需要连接ESP8266的SSID*/
#define CE_TM_CTL_ESP8266_PWD         "12345678"            /*!< 配置无人机需要连接ESP8266的密码*/
#define CE_TM_CTL_ESP8266_SERVER_IP   "172.20.10.14"       /*!< 配置无人机需要连接服务器的IP*/
#define CE_TM_CTL_ESP8266_SERVER_PORT  2121                 /*!< 配置无人机需要连接服务器的端口*/


#define CE_TM_CTL_NRF24L01P_RESOURCE_0  Spi2                /*!< 配置NRF24L01模块使用到的SPI资源号*/
#define CE_TM_CTL_NRF24L01P_RESOURCE_1  PB4GIP              /*!< 配置NRF24L01模块使用到的GPIO资源号*/
#define CE_TM_CTL_NRF24L01P_RESOURCE_2  PB8GIP              /*!< 配置NRF24L01模块使用到的INT资源号*/

/**
  * @brief  枚举，当前无人机通讯方式
  */
typedef enum 
{
    CE_TM_CTL_USE_ESP8266 = 0,                              /*!< 使用Wifi传输方式*/
    CE_TM_CTL_USE_NRF,                                      /*!< 使用无线射频传输方式*/
}CE_TM_CTL_USE;

uint8           ceTMCtl_nrfAddress[5] = {0x01,0x13,0x5C,0x0C,0x03};//设置发送地址

CeESP8266       ceTMCtl_ceESP8266;                          /*!< CeESP8266模块对象，基于ESP8266-12E*/
CeNRF24L01P     ceTMCtl_ceNRF24L01P;                        /*!< CeNRF24L01P模块对象，基于NRF24L01+*/

uint32          ceTMCtl_sendPackCount;                      /*!< 发送到数据的次数，用于断连检测*/
uint32          ceTMCtl_recvPackCount;                      /*!< 接收到数据的次数，用于断连检测*/
uint32          ceTMCtl_lastSendTime;                       /*!< 用于计算两次发送时间间隔是否大于sendIntervalMs*/
CE_TM_CTL_USE   ceTMCtl_useType;                            /*!< 当前无人机通讯方式*/
void          (*ceTMCtl_pRecvCallBack)(uint8* recvBuf, uint16 recvCount);/*!< 接收到数据后，直接TMU对象需调用的回调*/

/**
  * @brief  供通讯模块接收数据后调用的回调函数
  * @param  recvBuf:接收到数据的缓存地址
  * @param  recvCount:接收到数据的长度
  */
void ceTMCtl_recvCallBack(uint8* recvBuf, uint16 recvCount)
{
    ceTMCtl_recvPackCount++;
    ceTMCtl_pRecvCallBack(recvBuf,recvCount);
}

/**
  * @brief CeTMCtl模块初始化
  * @param useType:配置TMU模块使用什么通讯方式进行数据传输
  * @param intervalMs:定义发送时间间隔
  * @param recvCallBack:用户需提供的回调函数
  */
CE_STATUS ceTMCtl_initial(uint8 iniArg)
{
    ceTMCtl_sendPackCount = 0;
    ceTMCtl_recvPackCount = 0;
    ceTMCtl_useType = (CE_TM_CTL_USE)iniArg;
    if(ceTMCtl_useType == CE_TM_CTL_USE_ESP8266)//如果处于ESP8266工作模式
    {
        ceESP8266Op.initial(&(ceTMCtl_ceESP8266),CE_TM_CTL_ESP8266_RESOURCE);//还需要定议回调函数，后面再调
        while(CE_STATUS_SUCCESS != ceESP8266Op.setWorkMode(&(ceTMCtl_ceESP8266),CE_ESP8266_MODE_STA));
        while(CE_STATUS_SUCCESS != ceESP8266Op.connectWifi(&(ceTMCtl_ceESP8266),CE_TM_CTL_ESP8266_SSID,CE_TM_CTL_ESP8266_PWD));
        while (CE_STATUS_SUCCESS != ceESP8266Op.connectServer(&(ceTMCtl_ceESP8266),0,CE_TM_CTL_ESP8266_SERVER_IP,CE_TM_CTL_ESP8266_SERVER_PORT,CE_ESP8266_SOCKET_MODE_TCP,ceTMCtl_recvCallBack));
        ceESP8266Op.startUTSendOnClient(&(ceTMCtl_ceESP8266));
    }else if(ceTMCtl_useType == CE_TM_CTL_USE_NRF)//如果处于2.4G无线工作方式
    {
        ceNRF24L01POp.initial(&ceTMCtl_ceNRF24L01P,CE_TM_CTL_NRF24L01P_RESOURCE_0,CE_TM_CTL_NRF24L01P_RESOURCE_1,CE_TM_CTL_NRF24L01P_RESOURCE_2);
    }
    ceTMCtl_lastSendTime = ceSystemOp.getSystemTickMs();
    return CE_STATUS_SUCCESS;
}

/**
  * @brief CeTMCtlCtl模块配置接收数据的回调
  * @param recvCallBack:用户需提供的回调函数
  */
void   setRecvCallBack(void (*recvCallBack)(uint8* recvBuf, uint16 recvCount))
{
    ceTMCtl_pRecvCallBack = recvCallBack;
}

/**
  * @brief 发送数据，注意：函数内部会检测距离上一次发送数据的时间是否大于intervalMs，如果小于则直接返回
  * @param dataBuf:发送缓存地址
  * @param dataCount:发送缓存数据长度
  */
CE_STATUS ceTMCtl_sendData(uint8* dataBuf, uint16 dataCount)
{
    ceTMCtl_sendPackCount++;    
    if(ceTMCtl_useType == CE_TM_CTL_USE_ESP8266)//如果处于ESP8266工作模式
    {
        ceESP8266Op.sendData(&ceTMCtl_ceESP8266,0,dataBuf,dataCount);
    }else if(ceTMCtl_useType == CE_TM_CTL_USE_NRF)//如果处于2.4G无线工作方式
    {
        ceNRF24L01POp.send(&ceTMCtl_ceNRF24L01P,ceTMCtl_nrfAddress,dataBuf,dataCount);//发送数据给控制器
        ceNRF24L01POp.recv(&ceTMCtl_ceNRF24L01P,0,ceTMCtl_nrfAddress,ceTMCtl_recvCallBack);//启动接收
    }
    ceTMCtl_lastSendTime = ceSystemOp.getSystemTickMs();

    return     CE_STATUS_SUCCESS;
}

/**
  * @brief 检测是否通讯中断
  * @return CE_STATUS_SUCCESS：通讯正常； 其它：通讯中断
  */
CE_STATUS ceTMCtl_checkConnectStatus()
{
    CE_STATUS ceStatus = CE_STATUS_SUCCESS;
    if(ceTMCtl_sendPackCount >= 20)
    {
        if(ceMathOp.abs((int)(ceTMCtl_recvPackCount) - (int)(ceTMCtl_sendPackCount)) >= 20)//连续发送10帧，但没有收到回复，则认为与控制器断连
            ceStatus = CE_STATUS_FAILE;    

        ceTMCtl_sendPackCount=0;
        ceTMCtl_recvPackCount=0;    
    }
    return ceStatus;
}

/**
  * @brief 检测距离上一次发送数据到此时的时间间隔
  * @return 距离上一次发送数据到现在的时间间隔，单位ms
  */
uint32 ceTMCtl_getSendIntervalMs(void)   
{
    return  ceSystemOp.getSystemTickMs() - ceTMCtl_lastSendTime;
}

/**
  * @brief  CeTMCtl模块操作对象定义
  */
const CeTMCtlOp ceTMCtlOp = {ceTMCtl_initial,setRecvCallBack,ceTMCtl_sendData,ceTMCtl_checkConnectStatus,ceTMCtl_getSendIntervalMs};

#ifdef __cplusplus
 }
#endif //__cplusplus

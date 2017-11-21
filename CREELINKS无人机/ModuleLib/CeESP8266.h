/**
  ******************************************************************************
  * @file    CeESP8266.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeESP8266ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_ESP8266_H__
#define __CE_ESP8266_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_ESP8266_VERSION__ 1                                       /*!< �������ļ��İ汾��*/
#define __CE_ESP8266_NEED_CREELINKS_VERSION__ 1                        /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_ESP8266_NEED_CREELINKS_VERSION__) /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeESP8266.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
#define CE_ESP8266_UT                                                /*!< ESP8266�Ƿ�����͸��(Ĭ�Ϲر�)��ע�⣺������STA�ĵ�����ģʽ�ſ�������͸������������ã���ֻ����Ϊ�ͻ�������һ��������*/

#define CE_ESP8266_RECV_BUF_SIZE       256                            /*!< UARTʹ�õ���fifo���������ɸ���ʵ��������ӻ���٣�����Ҫ��֤����һ�ε�������С�ڴ�ֵ*/
#define CE_ESP8266_MAX_CONNECT_BUF     10                              /*!< �鿴���豸��ͻ��������б�����ֵ*/
/*
 *ö�� ��ģʽ�Ĺ�����ʽ
*/
typedef enum
{
    CE_ESP8266_MODE_STA = 1,                                           /*!< STAģʽ: Station, �����������նˣ�sta�������������ߵĽ��룬���������ӵ�AP��һ�����������������ڸ�ģʽ*/
    CE_ESP8266_MODE_AP = 2,                                            /*!< APģʽ: Access Point���ṩ���߽�������������������豸���룬�ṩ���ݷ��ʣ�һ�������·��/���Ź����ڸ�ģʽ��*/
    CE_ESP8266_MODE_STA_AP=3,                                          /*!< AP+STA*/
}CE_ESP8266_MODE;

/*
 *ö�� APģʽ�£�������Wifiʱ�ļ��ܷ�ʽ
*/
 typedef enum
{
    CE_ESP8266_ECN_OPEN = 0,                                           /*!< ����ʽ*/
    CE_ESP8266_ECN_WEP = 1,                                            /*!< WEP�����ߵ�Ч���ܣ���������WEP 64λ����128λ���ݼ���*/
    CE_ESP8266_ECN_WPA_PSK = 2,                                        /*!< WPA-PSK[TKIP]��������Ԥ������Կ��Wi-Fi�������ʣ�����WPA-PSK��׼���ܼ�������������ΪTKIP*/
    CE_ESP8266_ECN_WPA2_PSK = 3,                                       /*!< WPA2-PSK[AES]��������Ԥ������Կ��Wi-Fi�������ʣ��汾2��������WPA2-PSK��׼���ܼ�������������ΪAES*/
    CE_ESP8266_ECN_WPA_WPA2_PSK = 4,                                   /*!< WPA-PSK[TKIP] + WPA2-PSK [AES]��������ͻ���ʹ��WPA-PSK [TKIP]����WPA2-PSK [AES]*/
}CE_ESP8266_ECN;

/*
 *ö�� SOCKET�����ӷ�ʽ
*/
typedef enum
{
    CE_ESP8266_SOCKET_MODE_TCP=0,                                      /*!< TCP���ӷ�ʽ*/
    CE_ESP8266_SOCKET_MODE_UDP=1                                       /*!< UDP���ӷ�ʽ*/
}CE_ESP8266_SOCKET_MODE;
/*
 *ö�� APģʽ�룬���ģ���������豸��Ϣ
*/
typedef struct
{
    char ip[16];                                                        /*!< IP��ַ���ַ���"192.168.1.1"��ʽ*/
    char mac[18];                                                       /*!< MAC��ַ���ַ���"8F:34:32:A4:56:76"��ʽ*/
}CeESP8266APLinkDevInfo;

/*
    *ö�� �Ѿ�������SOCKET������ϸ��Ϣ
*/
typedef struct
{
    CE_ESP8266_SOCKET_MODE socketMode;                                  /*!< ��TCP����UDP*/
    char                    ip[16];                                     /*!< IP��ַ���ַ���"192.168.1.1"��ʽ*/
    uint16                  port;                                       /*!< �˿ں�*/
    uint8                   linkID;                                     /*!< �������ӵ�ID��ESP8266һ��������5������ͬʱ����*/
    uint8                   moduleLinkType;                             /*!< ָ�����ӣ�ģ���������Ƿ������Ľ�ɫ�����ǿͻ��˵Ľ�ɫ��1��Ϊ��������0��Ϊ�ͻ���*/
}CeESP8266LinkInfo;

/*
 *ö�� �����п���Wifi����ϸ��Ϣ����
*/
typedef struct
{
    CE_ESP8266_ECN ceWifiEpsEcn;                                        /*!< ���ܷ�ʽ*/
    char ssid[64];                                                      /*!< wifi��ssid����*/
    int signal;                                                         /*!< �ź�ǿ��*/
    char mac[18];                                                       /*!< Mac��ַ*/
    uint16 other1;                                                      /*!< */
    uint16 other2;                                                      /*!< */
}CeESP8266CanConnectWifiInfo;

/*
 *CeESP8266���Զ���
 */
typedef struct
{
    CeUart              ceUart;                                                     /*!< ģ��ʹ�õ���UART��Դ�ӿڶ���*/
    CeTask              ceTask;                                                     /*!< ��ģ��ʹ�õ�������������Ҫ�𵽽������ݵļ�飬��ִ���û��ṩ�Ľ��ջص�����*/
    CE_ESP8266_MODE    wifiEspMode;                                                 /*!< ��ģ��Ĺ�����ʽ��AP��STA����*/
    CeESP8266APLinkDevInfo      apLinkDevInfoList[CE_ESP8266_MAX_CONNECT_BUF];      /*!< APģʽ�£����ӵ���ģ���Wifi�µ��豸����*/
    CeESP8266LinkInfo           linkInfoList[CE_ESP8266_MAX_CONNECT_BUF];           /*!< ��������ͻ��������½�����SOCKET��������*/
    CeESP8266CanConnectWifiInfo staCanConnectWifiList[CE_ESP8266_MAX_CONNECT_BUF];  /*!< ģ�����Χ�Ŀ���Wifi�������������ҵ��Ŀ���Wifi����*/
    void    (*callBackClientRecv[5])(uint8* recvBuf, uint16 recvCount);             /*!< ���ڿͻ���ģʽʱ���ɽ���5���ͻ��˷ֱ��Ӧ�Ľ��ջص�*/
    void    (*callBackServerRecv)(uint8 linkID,uint8* recvBuf, uint16 recvCount);   /*!< ���ڷ�����ģʽʱ���������յ����ݺ�ִ�еĻص�,linkID:�ڼ����ͻ��˷�����������*/
    uint8   isLockRecvBuf;                                                          /*!< �������ջ��棬��ֹ����ʱ�����ʱ���������ͻ*/
    uint8   isServerMode;                                                           /*!< ��ǰ�����Ǵ��ڷ����������ǿͻ���״̬�������жϵ��÷������ص������ǿͻ��˻ص�*/
    uint8   apLinkDeviceCount;                                                      /*!< APģʽ�£��ж��ٸ��豸���ӵ���ģ���Wifi��*/
    uint8   linkInfoCount;                                                          /*!< AP��STAģʽ�£��ж��ٸ�SOCKET���Ӵ��ڣ�UDP��TCP*/
    uint8   staCanConnectwifiCount;                                                 /*!< ��STAģʽ�£����ҵ��Ļ����еĿ���Wifi����*/
    uint8   isInUTSend;                                                             /*!< �ͷ��������£��Ƿ���͸��ģʽ��*/
    uint8   uartRecvBuf[CE_ESP8266_RECV_BUF_SIZE];                                  /*!< Uart����ʹ�õ��Ľ��ջ���*/
    uint8   recvData[CE_ESP8266_RECV_BUF_SIZE];                                     /*!< ��Ž��յ������ݣ������û�ֱ�ӵ��ô������ݴ���ص�������ɺ󣬴��е����ݲ��ܹ���ˢ�£��������ݾ������浽fifo��*/
}CeESP8266;

/*
 *CeESP8266��������
 */
typedef struct
{

    CE_STATUS   (*initial)(CeESP8266* ceESP8266,CE_RESOURCE ceUart);                                    /*!< @brief  ʹ��һ��UART��Դ����ʼ��CeESP8266ģ��
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @param  ceUart:��ģ��ʹ�õ���Uart��Դ�ӿ�*/

    CE_STATUS   (*setWorkMode)(CeESP8266* ceESP8266,CE_ESP8266_MODE ceESP8266Mode);                     /*!< @brief  ��APģʽ��STAģʽ��ʼ��WIFI
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @param  ceESP8266Mode:��ģ��Ĺ�����ʽ����AP��STA��ʽ��
                                                                                                                    ��APģʽ��ģ����Ϊ�ȵ㣬�����豸����ģ�飩����ģ�����ã�
                                                                                                                    ��STA��ģ����Ϊ���豸�����������Ѵ��ڵ��ȵ㣬�����·�������ֻ��Ͻ������ȵ�ȣ�����ģ������*/


    CE_STATUS   (*createWifi)(CeESP8266* ceESP8266,const char* ip,const char* ssid, const char* passWord,uint8 channelNumber,CE_ESP8266_ECN ceESP8266Ecn);
                                                                                                        /*!< @brief  ����һ��AP�ȵ�
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @param  ip:��AP�ȵ��IP��ַ���������ӵ���ģ����豸��IP�ڴ˻���������
                                                                                                             @param  ssid:��AP�ȵ��Wifi����
                                                                                                             @param  channelNumber:Wifi�����ŵ�����Χ1��13����ʼ��ʱ����Χ������ֵ���ɡ�
                                                                                                             @param  ceESP8266Ecn:��AP�ȵ㴴����Wifi���ܷ�ʽ������CE_ESP8266_ECN_WPA2_PSK*/

    CeESP8266APLinkDevInfo* (*getConnectedDeviceList)(CeESP8266* ceESP8266);                            /*!< @brief  AP������ʽ�£�������AP�ݵ����ӵĴ��豸��IP��MAC��ַ����
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @return ���豸��Ϣ����*/

    uint8       (*getConnectedDeviceCount)(CeESP8266* ceESP8266);                                       /*!< @brief  AP������ʽ�£�������AP�ݵ����ӵĴ��豸���������������ж������豸���ӵ���Wifi֮��
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @return ���豸������*/

    CeESP8266CanConnectWifiInfo* (*getCanConnectWifiList)(CeESP8266* ceESP8266);                        /*!< @brief  STA������ʽ�£�������Χ�����п����ӵ�Wifi�ź�
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @return ����Wifi������ָ��*/

    uint8       (*getCanConnectWifiCount)(CeESP8266* ceESP8266);                                        /*!< @brief  STA������ʽ�£�������Χ�����п����ӵ�Wifi�ź�����
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @return ����Wifi������*/

    CE_STATUS   (*checkCanConnectSsidIsExist)(CeESP8266* ceESP8266, const char* ssid);                  /*!< @brief  STA������ʽ�£�������Χ�������Ƿ��и�����ssid��Wifi�ź�
                                                                                                             @param  ceESP8266:CeESP8266���Զ���*/

    CE_STATUS   (*connectWifi)(CeESP8266* ceESP8266, const char* ssid, const char* passWord);           /*!< @brief  STA������ʽ������һ���Ѿ����ڵ��ȵ㣬����Ϊ�ȵ��SSID��PWD
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @param  ssid:��Ҫ���ӵ�Wifi����
                                                                                                             @param  passWord:Wifi����*/

    CE_STATUS   (*setStaIp)(CeESP8266* ceESP8266, const char* ip);                                      /*!< @brief  STA������ʽ�£����ӵ��ȵ���IP��ע���ʱ���õ�IPӦ���ȵ�����ID��ƥ�䡣
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @param  ip:��Ҫ�趨��IP��ַ*/

    CE_STATUS   (*createServer)(CeESP8266* ceESP8266,uint16 serVerPortNum,CE_ESP8266_SOCKET_MODE ceESP8266SocketMode, void (*callBackServerRecv)(uint8 linkID,uint8* recvBuf, uint16 recvCount));
                                                                                                        /*!< @brief  ����һ�������������������뷢�����ݣ�AP��STAģʽ���ɴ���
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @param  serVerPortNum:�贴���ķ������˿ں�
                                                                                                             @param  linkID:�����Ǵ����˷���������˷��������ֻ����5���ͻ����������ӣ�linkIDָ�ľ�����5���ͻ��˵ı�ţ����������������Ŀͻ���Ϊ0���ص���LinkID��ʾ���������յ������ݣ����������ĸ��ͻ��˷�������
                                                                                                             @param  callBackServerRecv:���������յ����ݺ�Ļص�*/

    CE_STATUS   (*connectServer)(CeESP8266* ceESP8266, uint8 linkID, const char* serverIP,uint16 serVerPortNum,CE_ESP8266_SOCKET_MODE ceESP8266SocketMode, void (*callBackClientRecv)(uint8* recvBuf, uint16 recvCount));
                                                                                                        /*!< @brief  ����һ���Ѵ��ڵķ����������������뷢�����ݣ�AP��STAģʽ���ɴ���
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @param  linkID:ESP8266���Դ���5���ͻ��ˣ����0��4���ֱ����Ӹ��Եķ�������LinkIDָʹ���ĸ��ͻ��˱�ź����ӷ�����
                                                                                                             @param  serverIP:��Ҫ���ӵķ�������IP
                                                                                                             @param  serVerPortNum:��Ҫ���ӵķ������Ķ˿�
                                                                                                             @param ceESP8266SocketMode:���ӷ�ʽ��TCP��UDP
                                                                                                             @param callBackClientRecv:�˿ͻ��˽��յ����ݺ�Ļص�*/

    CE_STATUS           (*startUTSendOnClient)(CeESP8266* ceESP8266);                                   /*!< @brief  ����͸����ֻ��ģ���ǵ����ӣ���Ϊ�ͻ��˲ſ����д˹���
                                                                                                             @param  ceESP8266:CeESP8266���Զ���*/

    CE_STATUS           (*stopUTSendOnClient)(CeESP8266* ceESP8266);                                    /*!< @brief  �˳�͸����ֻ��ģ���ǵ����ӣ���Ϊ�ͻ��˲ſ����д˹���
                                                                                                             @param  ceESP8266:CeESP8266���Զ���*/

    CeESP8266LinkInfo*  (*getLinkList)(CeESP8266* ceESP8266);                                           /*!< @brief  ��ñ�ģ���������������б�����������ģʽ�£���˷��������ӵĿͻ����������ͻ���ģʽ�£��ж���ٿͻ������ڽ����������������ӣ�����5����
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @return SOCKET��������*/

    uint8               (*getLinkCount)(CeESP8266* ceESP8266);                                          /*!< @brief  ��ñ�ģ�����������������������������жϣ�������������ʽ�£����޿ͻ������ӡ��ͻ��˷�ʽ�£��Ƿ��������ӵ���������
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @return SOCKET��������*/

    CE_STATUS           (*sendData)(CeESP8266* ceESP8266,uint8 linkID, uint8* dataBuf,uint16 dataSize); /*!< @brief  ��һ�����Ӻ�linkID�������ݡ�
                                                                                                             @param  ceESP8266:CeESP8266���Զ���
                                                                                                             @param  linkID:������ģʽ�£������Ӻ�ָ�����������ӵĿͻ�����ţ��ͻ���ģʽ�£������Ӻ�ָʹ���ĸ��ͻ��ˣ����0��4��
                                                                                                             @param  dataBuf:��Ҫ���͵����ݻ���
                                                                                                             @param  dataSize:��Ҫ���͵����ݳ���*/

}CeESP8266OpBase;
/*
 *CeESP8266��������ʵ��
 */
extern const CeESP8266OpBase ceESP8266Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_ESP8266_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_ESP8266_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ʹ�������Ӽ�������·�ĵ��Ի��ֻ�����һ���������������ذ�װ����������֣���
          ����CeESP8266ģ�����Ӵ��ȵ㣨Wifi���������Ӹմ����ķ����������շ�����������
          �����ݣ���ͨ�����ڴ�ӡ��ͬʱÿ1S�����������һ�����ݰ���
******************************************************************************
#include "Creelinks.h"
#include "CeESP8266.h"
CeESP8266 myESP8266;

void callBackClient0(uint8* recvBuf, uint16 recvCount)
{
    uint16 i;
    ceDebugOp.printf("CeESP8266 has recv data from server, DataCount:%d, Data:\n",recvCount);
    for(i=0;i<recvCount;i++)
    {
        ceDebugOp.printf("%c",recvBuf[i]);
    }
    ceDebugOp.printf("\n");
}

int main(void)
{
    ceSystemOp.initial();                                        //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                                   //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceESP8266Op.initial(&myESP8266,R14Uart,CE_ESP8266_MODE_STA);//ʹ��R14Uart��Դ����ʹ��STA������ʽ����ģ����Ϊ�նˣ�����һ��Wifi��
    while(CE_STATUS_SUCCESS !=  ceESP8266Op.checkCanConnectSsidIsExist(&myESP8266,"Creelinks"))//ѭ����黷�����Ƿ����Creelinks��Wifi�źţ��û��������ѵ�Wifi�������޸�SSID��
    {
        ceDebugOp.printf("Cannot find wifi signal by ssid: Creelinks");
        ceSystemOp.delayMs(1000);
    }
    //ceESP8266Op.setStaIp(&myESP8266,"192.168.1.188");//����ģ���IP��ַ����Ҫ��·��������һ�£�Ҳ�ɲ������ã�ģ�齫���Զ���ȡһ��IP��
    while(CE_STATUS_SUCCESS != ceESP8266Op.connectServer(&myESP8266,0,"192.168.1.156",2121,CE_ESP8266_SOCKET_MODE_TCP,callBackClient0))//����һ������������������úõķ����������ṩ������IP��˿ڡ�
    {
        ceDebugOp.printf("Cannot connect server,IP:192.168.1.156, Port:2121\n");
        ceSystemOp.delayMs(1000);
    }

    while (1)
    {
        ceTaskOp.mainTask();                           //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceESP8266Op.sendData(&myESP8266,0,(uint8*)("Hello server!\n"),ceStringOp.strlen("Hello server!\n"));//����������������
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ʹ��CeESP8266����һ���������ȵ㣬������һ����������ͨ���ֻ���ʼǱ��������Ӵ�wifi�źţ����������ݰ���
******************************************************************************
#include "Creelinks.h"
#include "CeESP8266.h"
CeESP8266 myESP8266;

void callBackServerRecv(uint8 linkID,uint8* recvBuf, uint16 recvCount)
{
    uint16 i;
    ceDebugOp.printf("CeESP8266 has recv data from client, linkID:%d,  DataCount:%d, Data:\n",linkID,recvCount);
    for(i=0;i<recvCount;i++)
    {
        ceDebugOp.printf("%c",recvBuf[i]);
    }
    ceDebugOp.printf("\n");
}

int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceESP8266Op.initial(&myESP8266,R14Uart,CE_ESP8266_MODE_AP);//ʹ��R14Uart��Դ����ʹ��AP������ʽ����ģ����Ϊ·���������������豸����������
    while(CE_STATUS_SUCCESS !=  ceESP8266Op.createWifi(&myESP8266,"192.168.1.188","Creelinks","12345678",1,CE_ESP8266_ECN_WPA2_PSK))//����һ��ָ��IP��Wifi�������롢���ܷ�ʽ��Wifi�ȵ㣬ʹ���ֻ���ʼǱ�������֮����
    {
        ceDebugOp.printf("Cannot create wifi!\n");
        ceSystemOp.delayMs(1000);
    }

    while(ceESP8266Op.getConnectedDeviceCount(&myESP8266) == 0)                              //��鲢�ȴ������豸��֮������
    {
        ceDebugOp.printf("Wait for device connect wifi...\n");
        ceSystemOp.delayMs(1000);
    }

    while(CE_STATUS_SUCCESS !=  ceESP8266Op.createServer(&myESP8266,2121,callBackServerRecv))//����һ���˿�Ϊ2121�ķ�����
    {
        ceDebugOp.printf("Cannot create server!\n");
        ceSystemOp.delayMs(1000);
    }

    while(ceESP8266Op.getLinkCount(&myESP8266) == 0)//��鲢�ȴ��ͻ�����֮����
    {
        ceDebugOp.printf("Wait for client connect server...\n");
        ceSystemOp.delayMs(1000);
    }
    while (1)
    {
        ceTaskOp.mainTask();                       //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceESP8266Op.sendData(&myESP8266,0,(uint8*)("Hello server!\n"),ceStringOp.strlen("Hello server!\n"));//�����������ͻ���
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/



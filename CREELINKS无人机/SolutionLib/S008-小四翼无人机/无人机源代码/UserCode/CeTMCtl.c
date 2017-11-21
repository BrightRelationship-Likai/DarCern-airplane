/**
  ******************************************************************************
  * @file    CeTMCtl.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   ���ݴ����������ESP8266��������2.4Gģ��ĳ�ʼ�������ݷ��ͽ��յȴ���
  ******************************************************************************
  * @attention
  *
  *1)��ֲ��ע�⣺����initial�����У��������ģ��ʹ�õ�����Դ��
  *2)�������ݵ���send����������Byte���鼴�ɣ�
  *3)���յ����ݺ��Զ����ó�ʼ��ʱ�ṩ�Ļص�������δ���κδ����Byte���顣
  *4)���յ����ݺ󣬵��õĻص���������ceTaskOp.mainTask()��ִ�У��뱣֤��main�����е�ceTaskOp.mainTask()�ܹ������ڵ��� 
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

#define CE_TM_CTL_ESP8266_RESOURCE      Uart2               /*!< ����CeESP8266ģ��ʹ�õ���UART��Դ��*/

#define CE_TM_CTL_ESP8266_SSID        "CC Technology"             /*!< �������˻���Ҫ����ESP8266��SSID*/
#define CE_TM_CTL_ESP8266_PWD         "12345678"            /*!< �������˻���Ҫ����ESP8266������*/
#define CE_TM_CTL_ESP8266_SERVER_IP   "172.20.10.14"       /*!< �������˻���Ҫ���ӷ�������IP*/
#define CE_TM_CTL_ESP8266_SERVER_PORT  2121                 /*!< �������˻���Ҫ���ӷ������Ķ˿�*/


#define CE_TM_CTL_NRF24L01P_RESOURCE_0  Spi2                /*!< ����NRF24L01ģ��ʹ�õ���SPI��Դ��*/
#define CE_TM_CTL_NRF24L01P_RESOURCE_1  PB4GIP              /*!< ����NRF24L01ģ��ʹ�õ���GPIO��Դ��*/
#define CE_TM_CTL_NRF24L01P_RESOURCE_2  PB8GIP              /*!< ����NRF24L01ģ��ʹ�õ���INT��Դ��*/

/**
  * @brief  ö�٣���ǰ���˻�ͨѶ��ʽ
  */
typedef enum 
{
    CE_TM_CTL_USE_ESP8266 = 0,                              /*!< ʹ��Wifi���䷽ʽ*/
    CE_TM_CTL_USE_NRF,                                      /*!< ʹ��������Ƶ���䷽ʽ*/
}CE_TM_CTL_USE;

uint8           ceTMCtl_nrfAddress[5] = {0x01,0x13,0x5C,0x0C,0x03};//���÷��͵�ַ

CeESP8266       ceTMCtl_ceESP8266;                          /*!< CeESP8266ģ����󣬻���ESP8266-12E*/
CeNRF24L01P     ceTMCtl_ceNRF24L01P;                        /*!< CeNRF24L01Pģ����󣬻���NRF24L01+*/

uint32          ceTMCtl_sendPackCount;                      /*!< ���͵����ݵĴ��������ڶ������*/
uint32          ceTMCtl_recvPackCount;                      /*!< ���յ����ݵĴ��������ڶ������*/
uint32          ceTMCtl_lastSendTime;                       /*!< ���ڼ������η���ʱ�����Ƿ����sendIntervalMs*/
CE_TM_CTL_USE   ceTMCtl_useType;                            /*!< ��ǰ���˻�ͨѶ��ʽ*/
void          (*ceTMCtl_pRecvCallBack)(uint8* recvBuf, uint16 recvCount);/*!< ���յ����ݺ�ֱ��TMU��������õĻص�*/

/**
  * @brief  ��ͨѶģ��������ݺ���õĻص�����
  * @param  recvBuf:���յ����ݵĻ����ַ
  * @param  recvCount:���յ����ݵĳ���
  */
void ceTMCtl_recvCallBack(uint8* recvBuf, uint16 recvCount)
{
    ceTMCtl_recvPackCount++;
    ceTMCtl_pRecvCallBack(recvBuf,recvCount);
}

/**
  * @brief CeTMCtlģ���ʼ��
  * @param useType:����TMUģ��ʹ��ʲôͨѶ��ʽ�������ݴ���
  * @param intervalMs:���巢��ʱ����
  * @param recvCallBack:�û����ṩ�Ļص�����
  */
CE_STATUS ceTMCtl_initial(uint8 iniArg)
{
    ceTMCtl_sendPackCount = 0;
    ceTMCtl_recvPackCount = 0;
    ceTMCtl_useType = (CE_TM_CTL_USE)iniArg;
    if(ceTMCtl_useType == CE_TM_CTL_USE_ESP8266)//�������ESP8266����ģʽ
    {
        ceESP8266Op.initial(&(ceTMCtl_ceESP8266),CE_TM_CTL_ESP8266_RESOURCE);//����Ҫ����ص������������ٵ�
        while(CE_STATUS_SUCCESS != ceESP8266Op.setWorkMode(&(ceTMCtl_ceESP8266),CE_ESP8266_MODE_STA));
        while(CE_STATUS_SUCCESS != ceESP8266Op.connectWifi(&(ceTMCtl_ceESP8266),CE_TM_CTL_ESP8266_SSID,CE_TM_CTL_ESP8266_PWD));
        while (CE_STATUS_SUCCESS != ceESP8266Op.connectServer(&(ceTMCtl_ceESP8266),0,CE_TM_CTL_ESP8266_SERVER_IP,CE_TM_CTL_ESP8266_SERVER_PORT,CE_ESP8266_SOCKET_MODE_TCP,ceTMCtl_recvCallBack));
        ceESP8266Op.startUTSendOnClient(&(ceTMCtl_ceESP8266));
    }else if(ceTMCtl_useType == CE_TM_CTL_USE_NRF)//�������2.4G���߹�����ʽ
    {
        ceNRF24L01POp.initial(&ceTMCtl_ceNRF24L01P,CE_TM_CTL_NRF24L01P_RESOURCE_0,CE_TM_CTL_NRF24L01P_RESOURCE_1,CE_TM_CTL_NRF24L01P_RESOURCE_2);
    }
    ceTMCtl_lastSendTime = ceSystemOp.getSystemTickMs();
    return CE_STATUS_SUCCESS;
}

/**
  * @brief CeTMCtlCtlģ�����ý������ݵĻص�
  * @param recvCallBack:�û����ṩ�Ļص�����
  */
void   setRecvCallBack(void (*recvCallBack)(uint8* recvBuf, uint16 recvCount))
{
    ceTMCtl_pRecvCallBack = recvCallBack;
}

/**
  * @brief �������ݣ�ע�⣺�����ڲ����������һ�η������ݵ�ʱ���Ƿ����intervalMs�����С����ֱ�ӷ���
  * @param dataBuf:���ͻ����ַ
  * @param dataCount:���ͻ������ݳ���
  */
CE_STATUS ceTMCtl_sendData(uint8* dataBuf, uint16 dataCount)
{
    ceTMCtl_sendPackCount++;    
    if(ceTMCtl_useType == CE_TM_CTL_USE_ESP8266)//�������ESP8266����ģʽ
    {
        ceESP8266Op.sendData(&ceTMCtl_ceESP8266,0,dataBuf,dataCount);
    }else if(ceTMCtl_useType == CE_TM_CTL_USE_NRF)//�������2.4G���߹�����ʽ
    {
        ceNRF24L01POp.send(&ceTMCtl_ceNRF24L01P,ceTMCtl_nrfAddress,dataBuf,dataCount);//�������ݸ�������
        ceNRF24L01POp.recv(&ceTMCtl_ceNRF24L01P,0,ceTMCtl_nrfAddress,ceTMCtl_recvCallBack);//��������
    }
    ceTMCtl_lastSendTime = ceSystemOp.getSystemTickMs();

    return     CE_STATUS_SUCCESS;
}

/**
  * @brief ����Ƿ�ͨѶ�ж�
  * @return CE_STATUS_SUCCESS��ͨѶ������ ������ͨѶ�ж�
  */
CE_STATUS ceTMCtl_checkConnectStatus()
{
    CE_STATUS ceStatus = CE_STATUS_SUCCESS;
    if(ceTMCtl_sendPackCount >= 20)
    {
        if(ceMathOp.abs((int)(ceTMCtl_recvPackCount) - (int)(ceTMCtl_sendPackCount)) >= 20)//��������10֡����û���յ��ظ�������Ϊ�����������
            ceStatus = CE_STATUS_FAILE;    

        ceTMCtl_sendPackCount=0;
        ceTMCtl_recvPackCount=0;    
    }
    return ceStatus;
}

/**
  * @brief ��������һ�η������ݵ���ʱ��ʱ����
  * @return ������һ�η������ݵ����ڵ�ʱ��������λms
  */
uint32 ceTMCtl_getSendIntervalMs(void)   
{
    return  ceSystemOp.getSystemTickMs() - ceTMCtl_lastSendTime;
}

/**
  * @brief  CeTMCtlģ�����������
  */
const CeTMCtlOp ceTMCtlOp = {ceTMCtl_initial,setRecvCallBack,ceTMCtl_sendData,ceTMCtl_checkConnectStatus,ceTMCtl_getSendIntervalMs};

#ifdef __cplusplus
 }
#endif //__cplusplus

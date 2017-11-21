/**
  ******************************************************************************
  * @file    CeESP8266.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeESP8266ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeESP8266.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#ifdef CE_ESP8266_UT
#define CE_ESP8266_CONNECT_MUL         0                               /*!< ESP8266����������0Ϊ�����ӣ�1Ϊ������*/
#else
#define CE_ESP8266_CONNECT_MUL         1                               /*!< ESP8266����������0Ϊ�����ӣ�1Ϊ������*/
#endif

/**
  * @brief  ��������
  * @param  desBuf:Ŀ�Ļ���
  * @param  srcBuf:Դ����
  * @param  cpCount:�踴�Ƶ����ݳ���
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
void ceESP8266_cpData(uint8* desBuf, uint8* srcBuf, uint16 cpCount)
{
    uint16 i;
    for (i = 0; i < cpCount; i++)
    {
        desBuf[i] = srcBuf[i];
    }
}

/**
  * @brief  ��Uart�ж�ȡ���ݣ���endChar��β��β
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  buf:��������������õĻ���
  * @param  bufSize:�����С
  * @param  endChar:�����ݣ�ֱ���Դ��ַ�����β
  * @param  outTimeMs:��ʱʱ��
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
uint16 ceESP8266_readStringByEndChar(CeESP8266* ceESP8266, uint8* buf,uint16 bufSize, char* endChar, uint16 outTimeMs)
{
    uint16 tickMs = 0;
    uint16 checkIndex = 0;
    uint16 bufIndex = 0;
    char temp[2];
    temp[1] = '\0';
    buf[0] = '\0';

    //ceDebugOp.printf("endChar:%s\n ,",endChar);
    
    while (1)
    {
        if (ceUartOp.getRecvDataCount(&(ceESP8266->ceUart)) <= 0)   //���û���յ���
        {
            if (tickMs >= outTimeMs)
            {
                buf[0] = '\0';
                return 0;
            }
            tickMs += 10;
            ceSystemOp.delayMs(10);
        }
        else   //������յ���
        {
            ceUartOp.readData(&(ceESP8266->ceUart), (uint8*)(temp), 1);//��ȡһ���ֽ�

            if (ceESP8266->isServerMode != 0x00 || ceESP8266->isInUTSend == 0x01)
            {
//ceDebugOp.printf("%s,",temp[0]);//���յ������ݴ����������ʱʹ��
            }
                        

            buf[bufIndex] = temp[0];
            bufIndex++;
            if (bufIndex == bufSize)//��ȡ�������ݳ����˽��ջ������󳤶ȣ���ʱӦ���ǽ��յ�������������Ӧ��ֱ�ӷ��ء�
            {
                buf[0] = '\0';            
//ceDebugOp.printf("ddd\n");                            
                return 0;
            }
            if (temp[0] == endChar[checkIndex])        //�Ƚ϶�ȡ�����ֽ�����Ҫ�Աȵ������Ƿ���ͬ
            {
                checkIndex++;                       //�����ͬ�����ñȽϵ���������1
                if (endChar[checkIndex] == '\0')    //�������1�󣬼���һ��Ҫ�Ƚϵ��ֽ��ǿգ�������Ƚ���ɣ����سɹ�
                {
                    buf[bufIndex - ceStringOp.strlen(endChar)] = '\0';
                    return bufIndex - ceStringOp.strlen(endChar)+1;
                }
            }
            else                                    //�������ͬ������������Ϊ0���ٴ�0���¿�ʼ�Ƚ�
            {
                checkIndex = 0;
            }
        }
    }

}

/**
  * @brief  ��Uart�з����ݸ�ģ�飬���ȴ�ģ�鷵�ؽ��
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  sendMsg:Ҫ���ͳ�ȥ������
  * @param  recvMsg:�������յ�������,����ֻ����Ƿ����
  * @param  outTimeMs:��ʱʱ��
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_sendDataAndCheck(CeESP8266* ceESP8266, char* sendMsg, char* recvMsg, uint16 outTimeMs)
{
    if (sendMsg == CE_NULL && ceESP8266->isInUTSend == 0x01)
    {
        return CE_STATUS_SUCCESS;
    }
    else
    {
        uint16 tickMs = 0;
        uint16 checkIndex = 0;
        uint16 checkEIndex = 0;
        uint16 timeOutMs = 0;
        char temp[2];
        char* tempError = "ERROR";
        temp[1] = '\0';


        while (ceESP8266->isLockRecvBuf == 0x01)
        {
            ceSystemOp.delayMs(1);
            timeOutMs++;
            if (timeOutMs >= 2000)
            {
                break;
            }
        }
        ceESP8266->isLockRecvBuf = 0x01;

        if (sendMsg != CE_NULL)
        {
            ceUartOp.clearRecvBuf(&(ceESP8266->ceUart));
            ceUartOp.sendData(&(ceESP8266->ceUart), (uint8*)sendMsg, ceStringOp.strlen(sendMsg));
        }
        while (1)
        {
            if (ceUartOp.getRecvDataCount(&(ceESP8266->ceUart)) <= 0)   //���û���յ���
            {
                ceSystemOp.delayMs(10);
                tickMs += 10;
                if (tickMs >= outTimeMs)
                {
                    ceESP8266->isLockRecvBuf = 0x00;
                    return CE_STATUS_OUT_TIME;
                }
            }
            else   //������յ���
            {
                ceUartOp.readData(&(ceESP8266->ceUart), (uint8*)(temp), 1);//��ȡһ���ֽ�

                //ceDebugOp.printf(temp);//���յ������ݴ����������ʱʹ��

                if (temp[0] == tempError[checkEIndex])
                {
                    checkEIndex++;
                    if (tempError[checkEIndex] == '\0')
                    {
                        return CE_STATUS_FAILE;
                    }
                }

                if (temp[0] == recvMsg[checkIndex])        //�Ƚ϶�ȡ�����ֽ�����Ҫ�Աȵ������Ƿ���ͬ
                {
                    checkIndex++;                       //�����ͬ�����ñȽϵ���������1
                    if (recvMsg[checkIndex] == '\0')    //�������1�󣬼���һ��Ҫ�Ƚϵ��ֽ��ǿգ�������Ƚ���ɣ����سɹ�
                    {
                        ceESP8266->isLockRecvBuf = 0x00;
                        return CE_STATUS_SUCCESS;
                    }
                }
                else                                    //�������ͬ������������Ϊ0���ٴ�0���¿�ʼ�Ƚ�
                {
                    checkIndex = 0;
                }
            }
        }
    }
}

/**
  * @brief  ����ģ�鳬ʱʱ��
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  outTime:��ʱʱ��
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_atCIpSto(CeESP8266* ceESP8266,uint16 outTime)
{
    char sendBuf[30];
    CE_STATUS ceStatus;
    ceDebugOp.sprintf(sendBuf, "AT+CIPSTO=%d\r\n", outTime);
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "\r\nOK\r\n",500);
    #ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%s, run result:%s\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
    #endif
    return ceStatus;
}
/**
  * @brief  ��͸��ģʽ�£���������ǰ������
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  id:linkID��
  * @param  dataSize:���ݳ���
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_atCIpSend(CeESP8266* ceESP8266,uint8 id, uint16 dataSize)
{
    if ((ceESP8266->isInUTSend == 0x01 || CE_ESP8266_CONNECT_MUL == 0 )&& ceESP8266->isServerMode != 0x01)
    {
        return CE_STATUS_SUCCESS;
    }
    else
    {
        char sendBuf[30];
        CE_STATUS ceStatus;
        if (CE_ESP8266_CONNECT_MUL == 0)
        {
                      if(ceESP8266->isServerMode == 0x01)
                            ceDebugOp.sprintf(sendBuf, "AT+CIPSEND=%d,%d\r\n", id, dataSize);
             else
                ceDebugOp.sprintf(sendBuf, "AT+CIPSEND=%d\r\n", dataSize);
        }
        else
        {
            ceDebugOp.sprintf(sendBuf, "AT+CIPSEND=%d,%d\r\n", id, dataSize);                    
        }
        ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, ">",1000);
#ifdef __CE_CHECK_PAR__
        ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
        return ceStatus;
    }
}

/**
  * @brief  ��Uart������
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  dataBuf:Ҫ���͵����ݻ���
  * @param  dataSize:Ҫ���͵����ݳ���
  */
void ceESP8266_sendUartData(CeESP8266* ceESP8266, uint8* dataBuf, uint16 dataSize)
{
    uint16 timeOutMs = 0;
    while (ceESP8266->isLockRecvBuf == 0x01)
    {
        ceSystemOp.delayMs(1);
        timeOutMs++;
        if (timeOutMs >= 2000)
        {
            break;
        }
    }
    ceESP8266->isLockRecvBuf = 0x01;
    ceUartOp.sendData(&(ceESP8266->ceUart), dataBuf, dataSize);
    ceESP8266->isLockRecvBuf = 0x00;
}

/**
  * @brief  ����Task���������ڼ��������ݣ��������û��ص�
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  pAddPar:CeESP8266ָ��
  */
void ceESP8266_taskCallBack(void* pAddPar)
{
    CeESP8266* ceESP8266 = (CeESP8266*)(pAddPar);
    if (ceESP8266->isLockRecvBuf == 0x01)
        return;

    if ((ceESP8266->isInUTSend == 0x00 &&ceUartOp.getRecvDataCount(&ceESP8266->ceUart) <= 9) || (ceESP8266->isInUTSend == 0x01 &&ceUartOp.getRecvDataCount(&ceESP8266->ceUart) == 0))
        return;

    else
    {
        uint16 recvDataCount; 
        uint8 linkID = 0;
        if (ceESP8266->isInUTSend == 0x01)
        {
            recvDataCount = ceUartOp.getRecvDataCount(&ceESP8266->ceUart);
        }
        else
        {
            uint8 dataBuf[30];
            uint16 outTimeMs = 0;
            recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, (uint8*)dataBuf, 30, "+IPD,",500);//
            if (recvDataCount == 0)         //���û�ж������ݣ���ʱuart����������Ѷ��꣬����Ҳ������ʱ��
                return;

            if(ceESP8266->isServerMode == 1 || CE_ESP8266_CONNECT_MUL == 1)//������ģʽ��һ��Ϊ������
            {
                recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, ",",500);//��ȡ���ĸ��ͻ������ӷ�����������
                if (recvDataCount == 0 || recvDataCount > 2 || (dataBuf[0] - 0x30) > 4)
                    return;

                linkID = dataBuf[0] - 0x30;
            }else if(CE_ESP8266_CONNECT_MUL == 0)
                linkID = 0;                                            

            recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, ":",500);//��ȡ���ݳ���
            if (recvDataCount == 0 || recvDataCount > 6)
                return;


            recvDataCount = ceStringOp.atoi((char*)dataBuf);
            if (recvDataCount <= 0 || recvDataCount >= 1500)//�����������ݳ����Ƿ�����Ҫ��
                return;

            while (ceUartOp.getRecvDataCount(&ceESP8266->ceUart) < recvDataCount)//Uart���ջ����е����ݣ���������Ҫ��ȡ�����ݳ���
            {
                ceSystemOp.delayMs(1);
                outTimeMs++;
                if (outTimeMs > 2000)
                    return;
            }
        }
        if (recvDataCount != ceUartOp.readData(&(ceESP8266->ceUart), ceESP8266->recvData, recvDataCount))
            return;

        ceESP8266->recvData[recvDataCount] = '\0';

        if (ceESP8266->isServerMode == 0x00)
        {
            if (ceESP8266->callBackClientRecv[linkID] == CE_NULL)
                return;

            ceESP8266->callBackClientRecv[linkID](ceESP8266->recvData, recvDataCount);//����Ļص������⣬����Ǻ���ָ�����������
        }
        else
        {
            if (ceESP8266->callBackServerRecv == CE_NULL)
            {
                return;
            }
            ceESP8266->callBackServerRecv(linkID, ceESP8266->recvData, recvDataCount);
        }
    }
}

/**
  * @brief  ʹ��һ��UART��Դ����ʼ��CeESP8266ģ��
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  ceUart:��ģ��ʹ�õ���Uart��Դ�ӿ�
  * @param  ceESP8266Mode:��ģ��Ĺ�����ʽ����AP��STA��ʽ
  *         ��APģʽ��ģ����Ϊ�ȵ㣬�����豸����ģ�飩����ģ������
  *         ��STA��ģ����Ϊ���豸�����������Ѵ��ڵ��ȵ㣬�����·�������ֻ��Ͻ������ȵ�ȣ�����ģ������
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_initial(CeESP8266* ceESP8266, CE_RESOURCE ceUart)
{
   
    ceESP8266->isLockRecvBuf = 0x00;
    ceESP8266->isInUTSend = 0x00;
    ceESP8266->isServerMode = 0x00;
    ceESP8266->linkInfoCount = 0;
    ceESP8266->apLinkDeviceCount = 0;
    ceESP8266->staCanConnectwifiCount = 0;
    ceESP8266->callBackServerRecv = CE_NULL;
    ceESP8266->callBackClientRecv[0] = CE_NULL;
    ceESP8266->callBackClientRecv[1] = CE_NULL;
    ceESP8266->callBackClientRecv[2] = CE_NULL;
    ceESP8266->callBackClientRecv[3] = CE_NULL;
    ceESP8266->callBackClientRecv[4] = CE_NULL;

    ceESP8266->ceUart.ceResource = ceUart;
    ceESP8266->ceUart.uartBaudRate = CE_UART_BAUD_RATE_115200;
    ceESP8266->ceUart.uartParity = CE_UART_PARITY_NO;
    ceESP8266->ceUart.uartStopBits = CE_UART_STOP_BITS_1;
    ceESP8266->ceUart.uartWordLength = CE_UART_WORD_LENGTH_8B;
    ceESP8266->ceUart.recvBufSize = CE_ESP8266_RECV_BUF_SIZE;
    ceESP8266->ceUart.recvBuf = ceESP8266->uartRecvBuf;
    ceESP8266->ceUart.pAddPar = ceESP8266;
    ceUartOp.initial(&(ceESP8266->ceUart));
    ceUartOp.start(&(ceESP8266->ceUart));

    ceESP8266->ceTask.ID = ceUart;
    ceESP8266->ceTask.callBack = ceESP8266_taskCallBack;
    ceESP8266->ceTask.pAddPar = ceESP8266;
#ifdef CE_USE_RTOS
    ceESP8266->ceTask.isNewThread = 0x01;
    ceESP8266->ceTaskPriority = CE_TASK_PRIORITY_H;
#endif
    ceTaskOp.registerTask(&(ceESP8266->ceTask));
    ceTaskOp.start(&(ceESP8266->ceTask));

    return CE_STATUS_SUCCESS;
}


CE_STATUS   ceESP8266_setWorkMode(CeESP8266* ceESP8266,CE_ESP8266_MODE ceESP8266Mode)
{
    char sendBuf[128];
    CE_STATUS ceStatus;

    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, "AT\r\n", "OK", 2000);       //AT+RST
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%s\nRun result:%s\n\n", "AT",ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        ceESP8266Op.stopUTSendOnClient(ceESP8266);//�������ATָ��û�л�Ӧ��������ǵ�ǰ������͸��ģʽ�£����ȳ����˳�͸��ģʽ
        ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, "AT\r\n", "OK", 2000);       //AT+RST
        if(ceStatus != CE_STATUS_SUCCESS)
            return ceStatus;
    }

    ceDebugOp.sprintf(sendBuf, "AT+CWMODE=%d\r\n", ceESP8266Mode);                     //AT+CWMODE=? ������ʽ��1��STA�� 2��AP�� 3��STA+AP
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        return ceStatus;
    }

    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, "AT+RST\r\n", "ready", 8000);       //AT+RST
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%s\nRun result:%s\n\n", "AT+RST",ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        return ceStatus;
    }

    ceDebugOp.sprintf(sendBuf, "AT+CIPMUX=%d\r\n", CE_ESP8266_CONNECT_MUL);           //AT+CIPMUX=? �Ƿ������0�������ӣ� 1��������
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        return ceStatus;
    }
    return ceStatus;
}


/**
  * @brief  ����һ��AP�ȵ�
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  ip:��AP�ȵ��IP��ַ���������ӵ���ģ����豸��IP�ڴ˻���������
  * @param  ssid:��AP�ȵ��Wifi����
  * @param  channelNumber:Wifi�����ŵ�����Χ1��13����ʼ��ʱ����Χ������ֵ���ɡ�
  * @param  ceESP8266Ecn:��AP�ȵ㴴����Wifi���ܷ�ʽ������CE_ESP8266_ECN_WPA2_PSK
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_createWifi(CeESP8266* ceESP8266, const char* ip, const char* ssid, const char* passWord,uint8 channelNumber,CE_ESP8266_ECN ceESP8266Ecn)
{
    char sendBuf[128];
    CE_STATUS ceStatus;

    ceDebugOp.sprintf(sendBuf, "AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n", ssid, passWord, channelNumber, ceESP8266Ecn);
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        return ceStatus;
    }

    ceDebugOp.sprintf(sendBuf, "AT+CIPAP=\"%s\"\r\n", ip);
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        return ceStatus;
    }

    return ceStatus;
}

/**
  * @brief  AP������ʽ�£�������AP�ݵ����ӵĴ��豸��IP��MAC��ַ����
  * @param  ceESP8266:CeESP8266���Զ���
  * @return ���豸��Ϣ����
  */
CeESP8266APLinkDevInfo* ceESP8266_getConnectedDeviceList(CeESP8266* ceESP8266)
{
    uint8 dataBuf[30];
    uint8 i;
    uint16 recvDataCount;
    CE_STATUS ceStatus;

    for (i = 0; i < CE_ESP8266_MAX_CONNECT_BUF; i++)
    {
        ceESP8266->apLinkDevInfoList[i].ip[0] = '\0';
        ceESP8266->apLinkDevInfoList[i].mac[0] = '\0';
    }

#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("CeESP8266 try to find connect device...\n");
#endif

    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, "AT+CWLIF\r\n", "AT+CWLIF\r\r\n", 1000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", "AT+CWLIF\r\n", ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        ceESP8266->apLinkDeviceCount = 0;
        return ceESP8266->apLinkDevInfoList;
    }

    for (i = 0; i < CE_ESP8266_MAX_CONNECT_BUF; i++)
    {
        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, ",",2000);//��ȡip
        if (recvDataCount == 0 || recvDataCount > 16)
        {
            ceESP8266->apLinkDeviceCount = i;
            return  ceESP8266->apLinkDevInfoList;
        }
        ceESP8266_cpData((uint8*)(ceESP8266->apLinkDevInfoList[i].ip), dataBuf, recvDataCount);

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, "\r\n", 2000);//��ȡMAC��ַ
        if (recvDataCount == 0 || recvDataCount > 19)
        {
            ceESP8266->apLinkDevInfoList[i].ip[0] = '\0';
            ceESP8266->apLinkDeviceCount = i;
            return  ceESP8266->apLinkDevInfoList;
        }
        ceESP8266_cpData((uint8*)(ceESP8266->apLinkDevInfoList[i].mac), dataBuf, recvDataCount);

#ifdef __CE_CHECK_PAR__
        ceDebugOp.printf("CeESP8266 find connect device on AP Mode:\nIP:%s    MAC:%s\n", ceESP8266->apLinkDevInfoList[i].ip, ceESP8266->apLinkDevInfoList[i].mac);
#endif
    }
    return ceESP8266->apLinkDevInfoList;
}

/**
  * @brief  AP������ʽ�£�������AP�ݵ����ӵĴ��豸���������������ж������豸���ӵ���Wifi֮��
  * @param  ceESP8266:CeESP8266���Զ���
  * @return ���豸������
  */
uint8 ceESP8266_getConnectedDeviceCount(CeESP8266* ceESP8266)
{
    ceESP8266_getConnectedDeviceList(ceESP8266);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("CeESP8266 find connect device count: %d\n", ceESP8266->apLinkDeviceCount);
#endif
    return ceESP8266->apLinkDeviceCount;
}

/**
  * @brief  STA������ʽ�£�������Χ�����п����ӵ�Wifi�ź�
  * @param  ceESP8266:CeESP8266���Զ���
  * @return ����Wifi������ָ��
  */
CeESP8266CanConnectWifiInfo*  ceESP8266_getCanConnectWifiList(CeESP8266* ceESP8266)
{
    uint16 i;
    uint8 dataBuf[50];
    uint16 recvDataCount;
    CE_STATUS ceStatus;
    for (i = 0; i < CE_ESP8266_MAX_CONNECT_BUF; i++)//����������е�����
    {
        ceESP8266->staCanConnectWifiList[i].ssid[0] = '\0';
        ceESP8266->staCanConnectWifiList[i].mac[0] = '\0';
    }

    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, "AT+CWLAP\r\n", "AT+CWLAP", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", "AT+CWLAP\r\n", ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        ceESP8266->staCanConnectwifiCount = 0;
        return ceESP8266->staCanConnectWifiList;
    }

    for (i = 0; i < CE_ESP8266_MAX_CONNECT_BUF; i++)//
    {
        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 50, "+CWLAP:(", 8000);//���ҿ���wifi�ʱ�䣬���������Щ��ʱʱ��
        if (recvDataCount <= 0)
        {
            ceESP8266->staCanConnectwifiCount = i;
            return  ceESP8266->staCanConnectWifiList;
        }

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 50, ",\"", 2000);//ecn
        if (recvDataCount != 2 || dataBuf[0] - 0x30 > 5)
        {
            ceESP8266->staCanConnectwifiCount = i;
            return  ceESP8266->staCanConnectWifiList;
        }
        ceESP8266->staCanConnectWifiList[i].ceWifiEpsEcn = (CE_ESP8266_ECN)(dataBuf[0] - 0x30);

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 50, "\",", 2000);//ssid
        if (recvDataCount <= 1)
        {
            ceESP8266->staCanConnectwifiCount = i;
            return  ceESP8266->staCanConnectWifiList;
        }
        ceESP8266_cpData((uint8*)(ceESP8266->staCanConnectWifiList[i].ssid), dataBuf, recvDataCount);

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 50, ",\"", 2000);//signal
        if (recvDataCount <= 1 || recvDataCount >= 6)
        {
            ceESP8266->staCanConnectwifiCount = i;
            return  ceESP8266->staCanConnectWifiList;
        }
        ceESP8266->staCanConnectWifiList[i].signal = ceStringOp.atoi((char*)dataBuf);

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 50, "\",", 2000);//MAC
        if (recvDataCount != 18)
        {
            ceESP8266->staCanConnectwifiCount = i;
            return  ceESP8266->staCanConnectWifiList;
        }
        ceESP8266_cpData((uint8*)(ceESP8266->staCanConnectWifiList[i].mac), dataBuf, recvDataCount);

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 50, ",", 2000);//other1
        if (recvDataCount <= 0 || recvDataCount > 6)
        {
            ceESP8266->staCanConnectwifiCount = i;
            return  ceESP8266->staCanConnectWifiList;
        }
        ceESP8266->staCanConnectWifiList[i].other1 = ceStringOp.atoi((char*)dataBuf);

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 50, ")", 2000);//other2
        if (recvDataCount <= 0 || recvDataCount > 6)
        {
            ceESP8266->staCanConnectwifiCount = i;
            return  ceESP8266->staCanConnectWifiList;
        }
        ceESP8266->staCanConnectWifiList[i].other2 = ceStringOp.atoi((char*)dataBuf);

#ifdef __CE_CHECK_PAR__
        ceDebugOp.printf("CeESP8266 find can connect wifi on STA Mode:\n ECN:%d, SSID:%s, Signal:%d, MAC:%s, O1:%d, O2:%d\n",
            ceESP8266->staCanConnectWifiList[i].ceWifiEpsEcn, ceESP8266->staCanConnectWifiList[i].ssid,
            ceESP8266->staCanConnectWifiList[i].signal,ceESP8266->staCanConnectWifiList[i].mac,
            ceESP8266->staCanConnectWifiList[i].other1, ceESP8266->staCanConnectWifiList[i].other2);
#endif
    }
    return ceESP8266->staCanConnectWifiList;
}

/**
  * @brief  STA������ʽ�£�������Χ�����п����ӵ�Wifi�ź�����
  * @param  ceESP8266:CeESP8266���Զ���
  * @return ����Wifi������
  */
uint8  ceESP8266_getCanConnectWifiCount(CeESP8266* ceESP8266)
{
    ceESP8266_getCanConnectWifiList(ceESP8266);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("CeESP8266 find can connect wifi count: %d\n", ceESP8266->staCanConnectwifiCount);
#endif
    return ceESP8266->staCanConnectwifiCount;
}

/**
  * @brief  STA������ʽ�£�������Χ�������Ƿ��и�����ssid��Wifi�ź�
  * @param  ceESP8266:CeESP8266���Զ���
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_checkCanConnectSsidIsExist(CeESP8266* ceESP8266, const char* ssid)
{
    uint8  i;
    CeESP8266CanConnectWifiInfo* canConnectWifiInfo = ceESP8266_getCanConnectWifiList(ceESP8266);
    if (ceESP8266->staCanConnectwifiCount == 0)
    {
#ifdef __CE_CHECK_PAR__
        ceDebugOp.printf("CeESP8266 cannot find wifi by name: %s\n", ssid);
#endif
        return CE_STATUS_FAILE;
    }
    for (i = 0; i < CE_ESP8266_MAX_CONNECT_BUF; i++)
    {
        if (ceStringOp.strcmp(ceESP8266->staCanConnectWifiList[i].ssid, ssid) == 0)
        {
#ifdef __CE_CHECK_PAR__
            ceDebugOp.printf("CeESP8266 has find wifi by name: %s\n ECN:%d, SSID:%s, Signal:%d, MAC:%s, O1:%d, O2:%d\n", ssid,
                ceESP8266->staCanConnectWifiList[i].ceWifiEpsEcn, ceESP8266->staCanConnectWifiList[i].ssid,
                ceESP8266->staCanConnectWifiList[i].signal, ceESP8266->staCanConnectWifiList[i].mac,
                ceESP8266->staCanConnectWifiList[i].other1, ceESP8266->staCanConnectWifiList[i].other2);
#endif
            return CE_STATUS_SUCCESS;
        }
    }
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("CeESP8266 cannot find wifi by name: %s\n", ssid);
#endif
    return CE_STATUS_FAILE;
}

/**
  * @brief  STA������ʽ������һ���Ѿ����ڵ��ȵ㣬����Ϊ�ȵ��SSID��PWD
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  ssid:��Ҫ���ӵ�Wifi����
  * @param  passWord:Wifi����
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_connectWifi(CeESP8266* ceESP8266, const char* ssid, const char* passWord)
{
    CE_STATUS ceStatus;
    char sendBuf[100];

    ceDebugOp.sprintf(sendBuf, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, passWord);
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 12000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif

#ifdef CE_ESP8266_UT
    ceDebugOp.sprintf(sendBuf, "AT+CIPMODE=%d\r\n", 1);
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%s Run result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif

#endif

    return ceStatus;
}

/**
  * @brief  STA������ʽ�£����ӵ��ȵ���IP��ע���ʱ���õ�IPӦ���ȵ�����ID��ƥ�䡣
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  ip:��Ҫ�趨��IP��ַ
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_setStaIp(CeESP8266* ceESP8266, const char* ip)
{
    char sendBuf[64];
    CE_STATUS ceStatus;
    ceDebugOp.sprintf(sendBuf, "AT+CIPAP=\"%s\"\r\n", ip);
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
    return ceStatus;
}

/**
  * @brief  ����һ�������������������뷢�����ݣ�AP��STAģʽ���ɴ���
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  serVerPortNum:�贴���ķ������˿ں�
  * @param  linkID:�����Ǵ����˷���������˷��������ֻ����5���ͻ����������ӣ�linkIDָ�ľ�����5���ͻ��˵ı�ţ����������������Ŀͻ���Ϊ0���ص���LinkID��ʾ���������յ������ݣ����������ĸ��ͻ��˷�������
  * @param  callBackServerRecv:���������յ����ݺ�Ļص�
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS    ceESP8266_createServer(CeESP8266* ceESP8266,uint16 serverPortNum, CE_ESP8266_SOCKET_MODE ceESP8266SocketMode, void (*callBackServerRecv)(uint8 linkID,uint8* recvBuf, uint16 recvCount))
{
    char sendBuf[30];
    CE_STATUS ceStatus;
    ceESP8266->isServerMode = 0x01;
    ceESP8266->callBackServerRecv = callBackServerRecv;
    
      ceDebugOp.sprintf(sendBuf, "AT+CIPMUX=%d\r\n", 1);           //AT+CIPMUX=? �Ƿ������0�������ӣ� 1��������
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
        return ceStatus;
    }
    
    
    ceDebugOp.sprintf(sendBuf, "AT+CIPSERVER=%d,%d\r\n", 1, serverPortNum);
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
    return ceStatus;
}

/**
  * @brief  ����һ���Ѵ��ڵķ����������������뷢�����ݣ�AP��STAģʽ���ɴ���
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  linkID:ESP8266���Դ���5���ͻ��ˣ����0��4���ֱ����Ӹ��Եķ�������LinkIDָʹ���ĸ��ͻ��˱�ź����ӷ�����
  * @param  serverIP:��Ҫ���ӵķ�������IP
  * @param  serVerPortNum:��Ҫ���ӵķ������Ķ˿�
  * @param ceESP8266SocketMode:���ӷ�ʽ��TCP��UDP
  * @param callBackClientRecv:�˿ͻ��˽��յ����ݺ�Ļص�
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_connectServer(CeESP8266* ceESP8266,uint8 linkID, const char* serverIP,uint16 serVerPortNum,CE_ESP8266_SOCKET_MODE ceESP8266SocketMode, void (*callBackServerRecv)(uint8* recvBuf, uint16 recvCount))
{

    char sendBuf[50];
    CE_STATUS ceStatus;    
    
    ceESP8266->isServerMode = 0x00;
    ceESP8266->callBackClientRecv[linkID] = callBackServerRecv;

    if (CE_ESP8266_CONNECT_MUL == 0)
        ceDebugOp.sprintf(sendBuf, "AT+CIPSTART=\"%s\",\"%s\",%d\r\n", ((ceESP8266SocketMode == CE_ESP8266_SOCKET_MODE_TCP) ? "TCP" : "UDP"), serverIP, serVerPortNum);
    else
        ceDebugOp.sprintf(sendBuf, "AT+CIPSTART=%d,\"%s\",\"%s\",%d\r\n", linkID, ((ceESP8266SocketMode == CE_ESP8266_SOCKET_MODE_TCP) ? "TCP" : "UDP"), serverIP, serVerPortNum);

    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, sendBuf, "OK", 2000);

#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", sendBuf, ceSystemOp.getErrorMsg(ceStatus));
#endif
    return ceStatus;
}

/**
  * @brief  ��ñ�ģ���������������б�����������ģʽ�£���˷��������ӵĿͻ����������ͻ���ģʽ�£��ж���ٿͻ������ڽ����������������ӣ�����5����
  * @param  ceESP8266:CeESP8266���Զ���
  * @return SOCKET��������
  */
CeESP8266LinkInfo* ceESP8266_getLinkList(CeESP8266* ceESP8266)
{
    uint16 i;
    uint8 dataBuf[30];
    uint16 recvDataCount;
    CE_STATUS ceStatus;
    for (i = 0; i < CE_ESP8266_MAX_CONNECT_BUF; i++)
    {
        ceESP8266->linkInfoList[i].ip[0] = '\0';
    }

    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, "AT+CIPSTATUS\r\n", "+CIPSTATUS:", 2000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", "AT+CIPSTATUS\r\n", ceSystemOp.getErrorMsg(ceStatus));
#endif
    if (ceStatus != CE_STATUS_SUCCESS)
    {
#ifdef __CE_CHECK_PAR__
        ceDebugOp.printf("CeESP8266 cannot find link on server or client mode.\n");
#endif
        ceESP8266->linkInfoCount = 0;
        return ceESP8266->linkInfoList;
    }
    for (i = 0; i < CE_ESP8266_MAX_CONNECT_BUF; i++)
    {
        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, ",\"", 2000);//���Ӻţ�0��4
        if (recvDataCount == 0 || recvDataCount > 2 || (dataBuf[0] - 0x30) > 4)
        {
            ceESP8266->linkInfoCount = i;
            return  ceESP8266->linkInfoList;
        }
        ceESP8266->linkInfoList[i].linkID = (dataBuf[0] - 0x30);


        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, "\",\"", 2000);//��ȡ���ӷ�ʽ��TCP��UDP
        if (recvDataCount == 0 || recvDataCount > 4)
        {
            ceESP8266->linkInfoCount = i;
            return  ceESP8266->linkInfoList;
        }
        if (dataBuf[0] == 'T' && dataBuf[1] == 'C' && dataBuf[2] == 'P')
        {
            ceESP8266->linkInfoList[i].socketMode = CE_ESP8266_SOCKET_MODE_TCP;
        }
        else if (dataBuf[0] == 'U' && dataBuf[1] == 'D' && dataBuf[2] == 'P')
        {
            ceESP8266->linkInfoList[i].socketMode = CE_ESP8266_SOCKET_MODE_UDP;
        }
        else
        {
            ceESP8266->linkInfoList[i].ip[0] = '\0';
            ceESP8266->linkInfoCount = i;
            return  ceESP8266->linkInfoList;
        }

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, "\",", 2000);//��ȡIP
        if (recvDataCount <7 || recvDataCount > 20)
        {
            ceESP8266->linkInfoList[i].ip[0] = '\0';
            ceESP8266->linkInfoCount = i;
            return  ceESP8266->linkInfoList;
        }
        ceESP8266_cpData((uint8*)(ceESP8266->linkInfoList[i].ip), dataBuf, recvDataCount);

        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, ",", 2000);//��ȡ�˿ں�
        if (recvDataCount == 0 || recvDataCount > 6)
        {
            ceESP8266->linkInfoList[i].ip[0] = '\0';
            ceESP8266->linkInfoCount = i;
            return  ceESP8266->linkInfoList;
        }
        ceESP8266->linkInfoList[i].port = (uint16)(ceStringOp.atoi((char*)dataBuf));


        recvDataCount = ceESP8266_readStringByEndChar(ceESP8266, dataBuf, 30, "\r\n", 2000);//��ȡ��ģ������Ϊ�����������ǿͻ������ӣ�1��Ϊ��������0��Ϊ�ͻ���
        if (recvDataCount == 0 || recvDataCount > 2)
        {
            ceESP8266->linkInfoList[i].ip[0] = '\0';
            ceESP8266->linkInfoCount = i;
            return  ceESP8266->linkInfoList;
        }
        ceESP8266->linkInfoList[i].moduleLinkType = (uint16)(ceStringOp.atoi((char*)dataBuf));

#ifdef __CE_CHECK_PAR__
        ceDebugOp.printf("CeESP8266 find one link:\n LinkID:%d, Socket mode:%s, IP:%s, Port:%d, LinkProperty:Module as %s\n",
            ceESP8266->linkInfoList[i].linkID, ((ceESP8266->linkInfoList[i].socketMode == CE_ESP8266_SOCKET_MODE_TCP)?"TCP":"UDP"),
            ceESP8266->linkInfoList[i].ip, ceESP8266->linkInfoList[i].port,((ceESP8266->linkInfoList[i].moduleLinkType == 1)?"Server":"Client"));
#endif
    }
    return ceESP8266->linkInfoList;
}

/**
  * @brief  ��ñ�ģ�����������������������������жϣ�������������ʽ�£����޿ͻ������ӡ��ͻ��˷�ʽ�£��Ƿ��������ӵ���������
  * @param  ceESP8266:CeESP8266���Զ���
  * @return SOCKET��������
  */
uint8 ceESP8266_getLinkCount(CeESP8266* ceESP8266)
{
    ceESP8266_getLinkList(ceESP8266);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("CeESP8266 find link count: %d\n", ceESP8266->linkInfoCount);
#endif
    return ceESP8266->linkInfoCount;
}

/**
  * @brief  ����͸����ֻ��ģ���ǵ����ӣ���Ϊ�ͻ��˲ſ����д˹���
  * @param  ceESP8266:CeESP8266���Զ���
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_startUTSendOnClient(CeESP8266* ceESP8266)
{
    CE_STATUS ceStatus;
    ceStatus = ceESP8266_sendDataAndCheck(ceESP8266, "AT+CIPSEND\r\n", ">",8000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%sRun result:%s\n\n", "AT+CIPSEND\r\n", ceSystemOp.getErrorMsg(ceStatus));
#endif
    ceESP8266->isInUTSend = 0x01;
    return ceStatus;
}

/**
  * @brief  ֹͣ͸����ֻ��ģ���ǵ����ӣ���Ϊ�ͻ��˲ſ����д˹���
  * @param  ceESP8266:CeESP8266���Զ���
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_stopUTSendOnClient(CeESP8266* ceESP8266)
{
    ceESP8266_sendDataAndCheck(ceESP8266, "+++", CE_NULL,8000);
#ifdef __CE_CHECK_PAR__
    ceDebugOp.printf("Run CMD:%s\n\n", "+++");
#endif
    ceESP8266->isInUTSend = 0x00;
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��һ�����Ӻ�linkID�������ݡ�
  * @param  ceESP8266:CeESP8266���Զ���
  * @param  linkID:������ģʽ�£������Ӻ�ָ�����������ӵĿͻ�����ţ��ͻ���ģʽ�£������Ӻ�ָʹ���ĸ��ͻ��ˣ����0��4��
  * @param  dataBuf:��Ҫ���͵����ݻ���
  * @param  dataSize:��Ҫ���͵����ݳ���
  * @return ϵͳ״̬�룬���ܵ�ֵ��CE_STATUS_SUCCESS,CE_STATUS_OUT_TIME
  */
CE_STATUS ceESP8266_sendData(CeESP8266* ceESP8266, uint8 linkID, uint8* dataBuf, uint16 dataSize)
{
    if (dataSize <= 1400)//socket һ�������1480���ֽڣ������1400���ֽ�
    {
        if (ceESP8266_atCIpSend(ceESP8266, linkID, dataSize) != CE_STATUS_SUCCESS)
        {
            return CE_STATUS_FAILE;
        }
        ceESP8266_sendUartData(ceESP8266, dataBuf, dataSize);
        if (ceESP8266->isInUTSend)
            return CE_STATUS_SUCCESS;
        else
            return ceESP8266_sendDataAndCheck(ceESP8266, CE_NULL, "OK",1000);
    }
    else
    {
        uint8 loop = dataSize / 1400;
        uint16 lastData = dataSize % 1400;
        uint8 i;
        for (i = 0; i < loop; i++)
        {
            if (ceESP8266_atCIpSend(ceESP8266, linkID, 1400) != CE_STATUS_SUCCESS)
            {
                return CE_STATUS_FAILE;
            }
            ceESP8266_sendUartData(ceESP8266, (uint8*)(dataBuf + i * 1400), dataSize);
            if (CE_STATUS_SUCCESS != ceESP8266_sendDataAndCheck(ceESP8266, CE_NULL, "OK",1000))
            {
                return CE_STATUS_FAILE;
            }
        }
        if (lastData != 0)
        {
            if (ceESP8266_atCIpSend(ceESP8266, linkID, lastData) != CE_STATUS_SUCCESS)
            {
                return CE_STATUS_FAILE;
            }
            ceESP8266_sendUartData(ceESP8266,  (uint8*)(dataBuf + loop * 1400), lastData);
            if (CE_STATUS_SUCCESS != ceESP8266_sendDataAndCheck(ceESP8266, CE_NULL, "OK",1000))
            {
                return CE_STATUS_FAILE;
            }
        }
    }
    return CE_STATUS_SUCCESS;
}

const CeESP8266OpBase ceESP8266Op = { ceESP8266_initial, ceESP8266_setWorkMode, ceESP8266_createWifi, ceESP8266_getConnectedDeviceList, ceESP8266_getConnectedDeviceCount,
                                        ceESP8266_getCanConnectWifiList, ceESP8266_getCanConnectWifiCount, ceESP8266_checkCanConnectSsidIsExist,
                                        ceESP8266_connectWifi, ceESP8266_setStaIp, ceESP8266_createServer, ceESP8266_connectServer,
                                        ceESP8266_startUTSendOnClient, ceESP8266_stopUTSendOnClient,
                                        ceESP8266_getLinkList, ceESP8266_getLinkCount, ceESP8266_sendData
                                    };

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeNRF24L01P.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeNRF24L01Pģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_NRF24L01P_H__
#define __CE_NRF24L01P_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_NRF24L01P_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_NRF24L01P_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_NRF24L01P_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeNRF24L01P.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

#define CE_NRF24L01P_RECV_BUF_SIZE    128             /*!< ���ջ�������鳤��*/

#define CE_NRF24L01P_PACKET_LENGTH    32              /*!< ���ý����뷢�͵���Pack���ĳ���*/

typedef struct
{
    CeSpiMaster ceSpiMaster;                        /*!< ģ��ʹ�õ�Spi��Դ*/
    CeGpio      ceGpio;                             /*!< ģ��ʹ�õ�Gpio��Դ*/
    CeInt       ceInt;                              /*!< ģ��ʹ�õ�Int��Դ*/
    void        (*callBackRecv[6])(uint8* dataBuf, uint16 dataBufSize);/*!< ����ͨ��*/
    uint8       recvAddress[6][5];                  /*!< ���յ�ַ����*/
    uint8       recvBuf[CE_NRF24L01P_RECV_BUF_SIZE];  /*!< ���ջ���*/
    uint16      recvBufSize;                        /*!< ���ջ���������Ч���ݵ��ֽ���*/
    uint8       status;                             /*!< ����״̬���Ǵ��ڷ���״̬���ǽ���״̬*/
}CeNRF24L01P;
/*
*CeNRF24L01P��������
*/
typedef struct
{
    CE_STATUS   (*initial)(CeNRF24L01P* ceNRF24L01P, CE_RESOURCE ceSpi, CE_RESOURCE ceGpio,CE_RESOURCE ceInt);/*!<
                                                         @brief CeNRF24L01Pģ���ʼ��
                                                         @param ceNRF24L01P:CeNRF24L01P���Զ���ָ��
                                                         @param ceSpi:ģ��ʹ�õ�Spi��Դ��
                                                         @param ceGpio:ģ��ʹ�õ�ceGpio��Դ��
                                                         @param ceInt:ģ��ʹ�õ�ceInt��Դ��
                                                         @param ��ģ�����Ч��ַ����5���ֽڣ�һ��ģ���Ӧһ����ַ*/

    CE_STATUS   (*send)(CeNRF24L01P* ceNRF24L01P, uint8* sendAddress, uint8* dataBuf, uint16 dataBufSize);/*!<
                                                         @brief ���뷢��ģʽ�����Ͳ�����ɺ󣬺����ŷ���
                                                         @param ceNRF24L01P:CeNRF24L01P���Զ���ָ��
                                                         @param sendAddress:���͵�ַ������ն�6������ͨ���е�һ����ͬ
                                                         @param dataBuf:Ҫ���͵����ݻ�����
                                                         @param dataBufSize:Ҫ���͵����ݳ��ȣ�ע�⣺һ��ҪΪCE_NRF24L01P_PACKET_LENGTH��������
                                                         @return ����CE_STATUS_SUCCESS��������ͳɹ����������������ʧ��*/

    CE_STATUS   (*recv)(CeNRF24L01P* ceNRF24L01P, uint8 pipeIndex, uint8* recvAddress, void(callBackRecv)(uint8* dataBuf, uint16 dataBufSize));/*!<
                                                         @brief �������״̬����ʼ�������ݡ�ע�⣺������send������һ��Ҫ�ٴε��ô˺�������ʵ�����ݽ��գ��첽ִ�У�����ֱ�ӷ��ء�
                                                         @param ceNRF24L01P:CeNRF24L01P���Զ���ָ��
                                                         @param pipeIndex:ģ�鹲��6�����ý���ͨ������ֵָ��ʹ���ĸ�����ͨ���������ݣ����Ҫʹ�ö������ͨ���������ݣ�����ظ����ô˺������
                                                         @param recvAddress:����ͨ����Ӧ�Ľ��յ�ַ�����յ�ַ����ϸ������ϸ�Ķ�ģ���ֲ�
                                                         @param callBackRecv:����Ӧͨ�����յ����ݺ󣬵��õĻص�������ÿ��ͨ���Ļص�����������
                                                         @return ����CE_STATUS_SUCCESS��������óɹ����������������ʧ��*/
}CeNRF24L01POpBase;
/*
*CeNRF24L01P��������ʵ��
*/
extern const CeNRF24L01POpBase ceNRF24L01POp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_NRF24L01P_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_NRF24L01P_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ʹ��CeNRF24L01Pģ�齨�����ͻ���նˣ�ͨ���궨����ѡ��
          ���ͷ�1S����һ�����ݣ��������͵����ݼ����͵�״̬ͨ�����ڴ�ӡ
          ���շ������յ������ݺͽ��յĴ���ͨ�����ڴ�ӡ
******************************************************************************
#include "Creelinks.h"
#include "CeNRF24L01P.h"

CeNRF24L01P myNRF24L01P;

CE_STATUS ceStatus = CE_STATUS_SUCCESS;               //��������̬
uint8 datBuffer[CE_NRF24L01P_PACKET_LENGTH] = { 0 };    //���ݻ�����
#define NRF24L01P_SEND                                  //ѡ���Ƿ��ͻ��ǽ��գ�����ǽ��������δ˺꣡

#ifdef NRF24L01P_SEND
uint8 sendAddress[5] = {0x34, 0xC3, 0x10, 0xc1, 0x00};//���÷��͵�ַ
uint32 sendCount     = 0;                             //���ͼ���
uint32 sendOkCount   = 0;                             //���ͳɹ�����
#else
uint8 recvAddress[5] = {0x34, 0xC3, 0x10, 0xc1, 0x00};//���ý��յ�ַ�����շ�ֻҪ֪���Լ��ĵ�ַ����
uint32 recvCount     = 0;                             //���ռ���
#endif

#ifndef NRF24L01P_SEND
void callBackNrfRecv(uint8* dataBuf, uint16 dataBufSize)
{
    ceDebugOp.printf((char*)dataBuf);          //ͨ�����ڴ�ӡ����
    recvCount++;
    ceDebugOp.printf( "Recvount=%u.", recvCount);//��ӡ���ռ���
}
#endif

int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���

    while(ceNRF24L01POp.initial(&myNRF24L01P, R7Spi, R2TI2c) != CE_STATUS_SUCCESS)//ʹ��R7SPI��R2TI2c��ʼ��CeNRF24L01Pģ�飬���ȴ���ģ���������ӳ�ʼ���ɹ���
    {
        ceDebugOp.printf("CeNRF24L01P initial return %s!\n", ceSystemOp.getErrorMsg(ceStatus));
        ceSystemOp.delayMs(100);
    };

#ifndef NRF24L01P_SEND
    ceStatus = ceNRF24L01POp.recv(&myNRF24L01P, 0, recvAddress, callBackNrfRecv);//����ģʽ�£�ע����ջص��������ȴ�
    if(ceStatus != CE_STATUS_SUCCESS)
    {
        ceDebugOp.printf("CeNRF24L01P recv return %s\n", ceSystemOp.getErrorMsg(ceStatus));
    }
#endif

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����

#ifdef NRF24L01P_SEND
        ceDebugOp.sprintf((char*)datBuffer, "SendCount=%u.", sendCount);//׼���������ݣ����ݵĳ��Ȳ��ܳ��� CE_NRF24L01P_PACKET_LENGTH
        ceStatus = ceNRF24L01POp.send(&myNRF24L01P, sendAddress, datBuffer, CE_NRF24L01P_PACKET_LENGTH);//�������ݲ���ȡ����״̬
        if (ceStatus == CE_STATUS_SUCCESS)
            sendOkCount++;                      //��¼���ͳɹ��Ĵ���
        sendCount ++;                           //���ͼ�������
        ceDebugOp.printf("SendData: %s SendtCount: %u SendOkCount: %u Status: %s.\n", datBuffer, sendCount, sendOkCount, ceSystemOp.getErrorMsg(ceStatus));//��ӡ���͵����ݺͷ��͵�״̬
#endif
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/


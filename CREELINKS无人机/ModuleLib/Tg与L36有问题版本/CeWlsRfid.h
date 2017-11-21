/**
  ******************************************************************************
  * @file    CeWlsRfid.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeWlsRfidģ����������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)initialSection�Ĺ�����δʵ�֣�ʵ��������Ҫ���ֲᣬ�Ƚ��鷳������������
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_WLS_RFID_H__
#define __CE_WLS_RFID_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_WLS_RFID_VERSION__ 1                                            /*!< �������ļ��İ汾��*/
#define __CE_WLS_RFID_NEED_CREELINKS_VERSION__ 18                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_WLS_RFID_NEED_CREELINKS_VERSION__)      /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeWlsRfid.h��Ҫ����18���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

/**
  * @brief  ö�٣�CeWlsRfid����֧�ֵĿ�Ƭ����
  */
typedef enum
{
    CE_WLS_RFID_CARD_TYPE_MIFARE_ULTRALIGHT =    0x4400, /*!< Mifare_UltraLight*/
    CE_WLS_RFID_CARD_TYPE_MIFARE_ONE_S50 =       0x0400, /*!< Mifare_One(S50)*/
    CE_WLS_RFID_CARD_TYPE_MIFARE_ONE_S70 =       0x0200, /*!< Mifare_One(S70)*/
    CE_WLS_RFID_CARD_TYPE_MIFARE_PRO_X =         0x0800, /*!< Mifare_Pro(X)*/
    CE_WLS_RFID_CARD_TYPE_MIFARE_DESFIRE =       0x4403, /*!< Mifare_DESFire*/
    CE_WLS_RFID_CARD_TYPE_OTHER,                         /*!< ��������14443A��׼�Ŀ�*/
}CE_WLS_RFID_CARD_TYPE;

/*
 * @brief  �ṹ�壬CeWlsRfid�������ڴ洢��Ƭ��Ϣ�Ľṹ��
 */
typedef struct
{
    CE_WLS_RFID_CARD_TYPE     cardType;                 /*!< �洢��ǰ��ģ�����ӿ�Ƭ�Ŀ�Ƭ����*/
    uint8                    serialNumber[4];           /*!< �洢��ǰ��ģ�����ӿ�Ƭ��Ψһ���кţ�32λ*/
}CeWlsRfidCardInfo;

/*
 *CeWlsRfid���Զ���
 */
typedef struct
{
    CeSpiMaster         ceSpiMaster;                    /*!< ģ��ʹ�õ�SpiMaster��Դ���Զ���*/
    CeGpio              ceGpioRst;                      /*!< ģ��ʹ�õ�Gpio��Դ�������ڿ���ģ��ĸ�λ*/
    CeWlsRfidCardInfo    ceWlsRfidCardInfo;             /*!< ��ŵ�ǰ��ģ�����ӿ�Ƭ����Ϣ�ṹ��*/
}CeWlsRfid;
/*
 *CeWlsRfid��������
 */
typedef struct
{
    CE_STATUS           (*initial)(CeWlsRfid* ceWlsRfid,CE_RESOURCE ceSpi,CE_RESOURCE ceGpio);/*!<
                                                             @brief CeRfidRģ���ʼ��
                                                             @param ceWlsRfid:ceWlsRfid���Զ���ָ��
                                                             @param ceSpi:ceWlsRfidģ��ʹ�õ�Spi��Դ��
                                                             @param ceGpio:ceWlsRfidģ��ʹ�õ�Gpio��Դ��*/

    CE_STATUS           (*setOn)(CeWlsRfid* ceWlsRfid); /*!< @brief ʹCeWlsRfidģ����й���״̬
                                                             @param ceWlsRfid:ceWlsRfid���Զ���ָ��*/

    CeWlsRfidCardInfo*  (*connectCard)(CeWlsRfid* ceWlsRfid);/*!<
                                                             @brief ��CeWlsRfid�ɸ�Ӧ����Χ���鿨���˺���Ӧ����ѭ�������ڵ���
                                                             @param ceWlsRfid:ceWlsRfid���Զ���ָ��
                                                             @return ����CE_NULL:��ʾδ����Χ�ҵ��������򷵻��ҵ��Ŀ���Ϣ*/

    CE_STATUS           (*initialSection)(CeWlsRfid* ceWlsRfid, uint8 blockIndex, char* defaultPasswordA, char* defaultPasswordB, char* newPasswordARead, char* newPasswordBWrite);/*!<
                                                             @brief ��ʼ��һ��δʹ�ù��������������޸�һ������������A��B
                                                             @param blockIndex:Ҫд�������������S50��Ϊ1~15��ע��0��������д
                                                             @param defaultPasswordA:IC������ʱ������Ĭ��A��6���ֽ�;
                                                             @param defaultPasswordB:IC������ʱ������Ĭ��B��6���ֽ�
                                                             @param newPasswordARead:�����õ�����A����������Ϊ�����룬6���ֽ�;
                                                             @param newPasswordBWrite:�����õ�����B����������Ϊд���룬6���ֽ�
                                                             @return CE_STATUS_SUCCESS:�����ɹ�;CE_STATUS_PAR_ERROR:ת��Ĳ�������;CE_STATUS_FAILE:����ʧ�ܣ����ܳ�ʼ���벻��ȷ*/

    CE_STATUS           (*readSection)(CeWlsRfid* ceWlsRfid, uint8 sectorIndex, uint8 blockIndex, char* passwordARead, char* dataOut);/*!<
                                                             @brief ��ȡָ�����е����ݣ����СΪ16�ֽ�
                                                             @param sectorIndex:�������������������S50��Ϊ0~15
                                                             @param blockIndex:���������������S50��ÿ�����������ڴ������ݵĿ�Ϊ0-2
                                                             @param passwordBRead:�����룬������ȷ����������ݣ�6���ֽ�
                                                             @param dataOut:�û��ṩ�Ķ����ݻ����������S50������������ڵ���16
                                                             @return CE_STATUS_SUCCESS:�����ɹ�;CE_STATUS_PAR_ERROR:����Ĳ�������;CE_STATUS_FAILE:����ʧ�ܣ��������벻��ȷ*/

    CE_STATUS           (*writeSection)(CeWlsRfid* ceWlsRfid, uint8 sectorIndex, uint8 blockIndex, char* passwordBWrite, char* dataIn);/*!<
                                                             @brief ��ָ������д�����ݣ����СΪ16���ֽ�
                                                             @param sectorIndex:�������������������S50��Ϊ1~15��ע����0��������д����ų��̴��룬�Ѿ��̻������ɸ��ģ�
                                                             @param blockIndex:���������������S50��ÿ�����������ڴ������ݵĿ�Ϊ0-2
                                                             @param passwordBWrite:д���룬6���ֽڣ�������ȷ�ſ�д��
                                                             @param dataIn:��д�������,����Ϊ16���ֽڣ�����16����Ҫ�û���䵽16���ֽڡ�
                                                             @return CE_STATUS_SUCCESS:�����ɹ�;CE_STATUS_PAR_ERROR:����Ĳ�������;CE_STATUS_FAILE:����ʧ�ܣ��������벻��ȷ�������������д*/

    CE_STATUS           (*releaseCard)(CeWlsRfid* ceWlsRfid);/*!<
                                                             @brief �ͷ�һ���Ѿ�������ɵĿ�Ƭ����,��ʹ�䴦������״̬��
                                                             @param ceWlsRfid:ceWlsRfid���Զ���ָ��*/

    CE_STATUS           (*setOff)(CeWlsRfid* ceWlsRfid);/*!< @brief ʹCeWlsRfidģ����е͹���״̬
                                                             @param ceWlsRfid:ceWlsRfid���Զ���ָ��*/
}CeWlsRfidOpBase;
/*
 *CeWlsRfid��������ʵ��
 */
extern CeWlsRfidOpBase ceWlsRfidOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_WLS_RFID_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_WLS_RFID_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����)
* @function ����Rfid���������ȴ��뿨Ƭ���ӡ�������֮���ӡ��Ƭ�����ͼ�Ψһ���кţ�������Ĭ���������������д����
******************************************************************************
#include "Creelinks.h"
#include "CeWlsRfid.h"
CeWlsRfid myWlsRfid;
CeWlsRfidCardInfo* ceWlsRfidCardInfo;
char defaultPasswordA[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
char writeBuffer[16] = { 0 };
char readBuffer[16]  = { 0 };
uint32 serialNumber = 0x00000000;
CE_STATUS ceStatus = CE_STATUS_SUCCESS;
int i = 0;
int main(void)
{
    ceSystemOp.initial();                        //Creelinks������ʼ��
    ceSystemOp.initialDebug(R9Uart);             //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���

    ceWlsRfidOp.initial(&myWlsRfid, R12Spi, R4AG); //ʹ��R12Spi��Դ��R4AG��Դ��ʼ��
    ceWlsRfidOp.setOn(&myWlsRfid);                 //��ģ����빤��״̬

    while (1)
    {
        ceSystemOp.mainTask();                  //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceWlsRfidCardInfo = ceWlsRfidOp.connectCard(&myWlsRfid);//�ȴ���Ƭ����
        if (ceWlsRfidCardInfo != CE_NULL)
        {
            serialNumber =  (ceWlsRfidCardInfo->serialNumber[0] & 0x000000FF) << 24;//����ƬΨһ���к�תΪuin32������ͨ��ʮ�����ƴ�ӡ���
            serialNumber |= (ceWlsRfidCardInfo->serialNumber[1] & 0x000000FF) << 16;
            serialNumber |= (ceWlsRfidCardInfo->serialNumber[2] & 0x000000FF) << 8;
            serialNumber |= (ceWlsRfidCardInfo->serialNumber[3] & 0x000000FF);
            ceSystemOp.printf("CeWlsRfid findCard\nCardInfo: Type: 0x%X ID: 0x%X\n", ceWlsRfidCardInfo->cardType, serialNumber);//��ӡ��ǰ���ӵĿ�Ƭ���ͼ�Ψһ���к�

            for(i = 0; i < 16; i++)
            {
                writeBuffer[i] = 0xAA + i;//����д������������
                readBuffer[i] = 0x00;     //��ն�������
            }

            do
            {
                ceStatus = ceWlsRfidOp.writeSection(&myWlsRfid, 2, 1, defaultPasswordA, writeBuffer);//��ָ��������ָ������д������
                if(ceStatus != CE_STATUS_SUCCESS)
                {
                    ceSystemOp.printf("CeWlsRfid writeSection return %s.\n", ceSystemOp.getErrorMsg(ceStatus));
                    break;
                }

                ceStatus = ceWlsRfidOp.readSection(&myWlsRfid, 2, 1, defaultPasswordA, readBuffer);//��ָ��������ָ�����ж�ȡ����
                if(ceStatus != CE_STATUS_SUCCESS)
                {
                    ceSystemOp.printf("CeWlsRfid readSection return %s.\n", ceSystemOp.getErrorMsg(ceStatus));
                    break;
                }

                for(i = 0; i < 16; i++)
                {
                    if(writeBuffer[i] != readBuffer[i])//У������
                    {
                        ceStatus = CE_STATUS_FAILE;//У��ʧ��
                        break;
                    }
                }

                if(ceStatus == CE_STATUS_SUCCESS)
                {
                    ceSystemOp.printf("CeWlsRfid verify success!\n");
                }
                else
                {
                    ceSystemOp.printf("CeWlsRfid Read and write successfully but check failed!\n");
                }
            } while (0);

            ceWlsRfidOp.releaseCard(&myWlsRfid);//�ͷŵ�ǰ���ӵĿ�Ƭ
        }
        else
        {
            //ceSystemOp.printf("CeWlsRfid no find Card!.\n");
        }

        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

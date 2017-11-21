/**
  ******************************************************************************
  * @file    CeEpmAtxx.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeEpmAtxxģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_EPM_ATXX_H__
#define __CE_EPM_ATXX_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_EPM_ATXX_VERSION__ 1                                           /*!< �������ļ��İ汾��*/
#define __CE_EPM_ATXX_NEED_CREELINKS_VERSION__ 1                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_EPM_ATXX_NEED_CREELINKS_VERSION__)     /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeFlsWxxx.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
//#define CE_EPM_ATXX_USE_AT24C01   127     /*!< CeEpmAtxx������оƬ�ͺ�ΪAT24C01������Ϊ126�ֽڣ���ַΪ8λ������8�ֽ����ݵ�ҳ��д����*/
#define CE_EPM_ATXX_USE_AT24C02     255     /*!< CeEpmAtxx������оƬ�ͺ�ΪAT24C02������Ϊ256�ֽڣ���ַΪ8λ������8�ֽ����ݵ�ҳ��д����*/
//#define CE_EPM_ATXX_USE_AT24C04   511     /*!< CeEpmAtxx������оƬ�ͺ�ΪAT24C04������Ϊ512�ֽڣ���ַΪ16λ������16�ֽ����ݵ�ҳ��д����*/
//#define CE_EPM_ATXX_USE_AT24C08   1023
//#define CE_EPM_ATXX_USE_AT24C16   2047
//#define CE_EPM_ATXX_USE_AT24C32   4095
//#define CE_EPM_ATXX_USE_AT24C64   8191
//#define CE_EPM_ATXX_USE_AT24C128  16383
//#define CE_EPM_ATXX_USE_AT24C256  32768
//#define CE_EPM_ATXX_USE_AT24C512  65535
/*
 *CeEpmAtxx���Զ���
 */
typedef struct
{
    CeI2cMaster ceI2cMaster;
}CeEpmAtxx;
/*
 *CeEpmAtxx��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeEpmAtxx* ceEpmAtxx, CE_RESOURCE ceI2c);    /*!< @brief CeEpmAtxxģ���ʼ��
                                                                             @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
                                                                             @param ceI2x:CeEpmAtxxģ��ʹ�õ���Դ��*/

    void        (*writeByte)(CeEpmAtxx* ceEpmAtxx, uint16 address, uint8 data);/*!<
                                                                             @brief ��ָ����ַ��д����
                                                                             @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
                                                                             @param address:��Ҫд��ĵ�ַ
                                                                             @param data:��Ҫд�������*/

    uint8       (*readByte)(CeEpmAtxx* ceEpmAtxx, uint16 address);      /*!< @brief ��ָ����ַ�ж�����
                                                                             @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
                                                                             @param address:��Ҫ���ĵ�ַ
                                                                             @param data:��Ҫ��������*/

    uint16      (*writeData)(CeEpmAtxx* ceEpmAtxx, uint16 startAddress, uint8* dataInBuf, uint16 dataInBufSize);/*!<
                                                                             @brief ��ָ����ʼ��ַ�У�����д������
                                                                             @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
                                                                             @param startAddress:��д�����ʼ��ַ
                                                                             @param dataInBuf:��д������ݻ���
                                                                             @param dataInBufSize:��д������ݳ���
                                                                             @return ʵ��д������ݳ���*/

    uint16      (*readData)(CeEpmAtxx* ceEpmAtxx, uint16 startAddress, uint8* dataOutBuf, uint16 dataOutBufSize);/*!<
                                                                             @brief ��ָ����ʼ��ַ�У����Ӷ�ȡ����
                                                                             @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
                                                                             @param ceI2x:CeEpmAtxxģ��ʹ�õ���Դ��
                                                                             @param startAddress:���ȡ����ʼ��ַ
                                                                             @param dataOutBuf:���ȡ�����ݻ���
                                                                             @param dataOutBufSize:���ȡ�����ݳ���
                                                                             @return ʵ�ʶ�ȡ�������ݳ���*/
}CeEpmAtxxOp;
/*
 *CeEpmAtxx��������ʵ��
 */
extern CeEpmAtxxOp ceEpmAtxxOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_EPM_ATXX_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_EPM_ATXX_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��Eeprom��д���ݣ��ٶ�ȡ��У�鶨�����ȡ��ֵ�Ƿ���ͬ
******************************************************************************
#include "Creelinks.h"
#include "CeEpmAtxx.h"
CeEpmAtxx myEpm;                                //�������Զ���
uint8 sendBuf[10] = {1,2,3,4,5,6,7,8,9,0};
uint8 recvBuf[10];
uint8 i;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceEpmAtxxOp.initial(&myEpm,R2TI2c);         //ʹ��R2TI2c��ʼ����ע���¼��ص�����
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceEpmAtxxOp.writeData(&myEpm, 0x16, sendBuf, 10);   //��Eeprom��д����
        ceEpmAtxxOp.readData(&myEpm, 0x16, recvBuf, 10);    //��Eeprom�ж�����
        for (i = 0; i < 10; i++)
        {
            if (sendBuf[i] == recvBuf[i])
            {
                ceDebugOp.printf("Right In: Write:%d, Read:%d\n", sendBuf[i], recvBuf[i]);
            }
            else
            {
                 ceDebugOp.printf("Error In: Write:%d, Read:%d\n", sendBuf[i], recvBuf[i]);
            }
        }
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeEpmAtxx.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeEpmAtxxģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeEpmAtxx.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_EPM_ATXX_DEV_WRITE   0xA0
#define CE_EPM_ATXX_DEV_READ    0xA1
/**
  * @brief  CeEpmAtxxģ���ʼ��
  * @param  ceEpmAtxx:CeEpmAtxx���Զ���
  * @param  ceI2c:CeEpmAtxxģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceEpmAtxx_initial(CeEpmAtxx* ceEpmAtxx, CE_RESOURCE ceI2c)
{
    ceEpmAtxx->ceI2cMaster.ceResource = ceI2c;
    ceEpmAtxx->ceI2cMaster.ceI2cMasterSpeed = CE_I2C_SPEED_3_4MBPS;
    ceI2cMasterOp.initial(&ceEpmAtxx->ceI2cMaster);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief ��ָ����ַ��д����
  * @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
  * @param address:��Ҫд��ĵ�ַ
  * @param data:��Ҫд�������
  */
void ceEpmAtxx_writeByte(CeEpmAtxx* ceEpmAtxx, uint16 address, uint8 data)
{
    ceI2cMasterOp.start(&(ceEpmAtxx->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), CE_EPM_ATXX_DEV_WRITE); //����д������Ӧ��λ
    if (ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster)) == CE_STATUS_SUCCESS)
    {
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), (uint8)(address >> 8) & 0x00FF); //���͵�ַ
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), (uint8)(address & 0x00FF)); //���͵�ַ
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), data); //��������
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
    }
    ceI2cMasterOp.stop(&(ceEpmAtxx->ceI2cMaster));
}

/**
  * @brief ��ָ����ַ�ж�����
  * @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
  * @param address:��Ҫ���ĵ�ַ
  * @param data:��Ҫ��������
  */
uint8 ceEpmAtxx_readByte(CeEpmAtxx* ceEpmAtxx, uint16 address)
{
    uint8 data;
    ceI2cMasterOp.start(&(ceEpmAtxx->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), CE_EPM_ATXX_DEV_WRITE); //����д������Ӧ��λ
    if (ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster)) == CE_STATUS_SUCCESS)
    {
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), (uint8)(address >> 8) & 0x00FF); //���͵�ַ
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), (uint8)(address & 0x00FF)); //���͵�ַ
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        ceI2cMasterOp.start(&(ceEpmAtxx->ceI2cMaster)); //��������
        ceI2cMasterOp.writeByte(&(ceEpmAtxx->ceI2cMaster), CE_EPM_ATXX_DEV_READ); //���Ͷ�����
        ceI2cMasterOp.waitAck(&(ceEpmAtxx->ceI2cMaster));
        data = ceI2cMasterOp.readByte(&(ceEpmAtxx->ceI2cMaster), 0x00); //�����ݺ��ͷ�Ӧ���źŽ���ͨѶ
    }
    ceI2cMasterOp.stop(&(ceEpmAtxx->ceI2cMaster));
    return data;
}

/**
  * @brief ��ָ����ʼ��ַ�У�����д������
  * @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
  * @param startAddress:��д�����ʼ��ַ
  * @param dataInBuf:��д������ݻ���
  * @param dataInBufSize:��д������ݳ���
  * @return ʵ��д������ݳ���
  */
uint16 ceEpmAtxx_writeData(CeEpmAtxx* ceEpmAtxx, uint16 startAddress, uint8* dataInBuf, uint16 dataInBufSize)
{
    uint16 t;
    for(t=0;t<dataInBufSize;t++)
    {
        ceEpmAtxx_writeByte(ceEpmAtxx, startAddress + t, dataInBuf[t]);
        ceSystemOp.delayMs(2);//������ʱд���ʧ��...
    }
    return t;
}

/**
  * @brief ��ָ����ʼ��ַ�У����Ӷ�ȡ����
  * @param ceEpmAtxx:CeEpmAtxx���Զ���ָ��
  * @param ceI2x:CeEpmAtxxģ��ʹ�õ���Դ��
  * @param startAddress:���ȡ����ʼ��ַ
  * @param dataOutBuf:���ȡ�����ݻ���
  * @param dataOutBufSize:���ȡ�����ݳ���
  * @return ʵ�ʶ�ȡ�������ݳ���
  */
uint16 ceEpmAtxx_readData(CeEpmAtxx* ceEpmAtxx, uint16 startAddress, uint8* dataOutBuf, uint16 dataOutBufSize)
{
    uint16 t;
    for(t=0;t<dataOutBufSize;t++)
    {
        dataOutBuf[t] = ceEpmAtxx_readByte(ceEpmAtxx, startAddress + t);
    }
    return t;
}

CeEpmAtxxOp ceEpmAtxxOp = {ceEpmAtxx_initial, ceEpmAtxx_writeByte, ceEpmAtxx_readByte, ceEpmAtxx_writeData, ceEpmAtxx_readData};

#ifdef __cplusplus
 }
#endif //__cplusplus

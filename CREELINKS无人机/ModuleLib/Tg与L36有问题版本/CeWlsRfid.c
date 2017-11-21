/**
  ******************************************************************************
  * @file    CeWlsRfid.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeWlsRfidģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeWlsRfid.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_WLS_RFID_MAXR_LEN 18
/*!< MF522������*/
#define CE_WLS_RFID_PCD_IDLE              0x00               /*!< ȡ����ǰ����*/
#define CE_WLS_RFID_PCD_AUTHENT           0x0E               /*!< ��֤��Կ*/
#define CE_WLS_RFID_PCD_RECEIVE           0x08               /*!< ��������*/
#define CE_WLS_RFID_PCD_TRANSMIT          0x04               /*!< ��������*/
#define CE_WLS_RFID_PCD_TRANSCEIVE        0x0C               /*!< ���Ͳ���������*/
#define CE_WLS_RFID_PCD_RESETPHASE        0x0F               /*!< ��λ*/
#define CE_WLS_RFID_PCD_CALCCRC           0x03               /*!< CRC����*/

/*!< Mifare_One��Ƭ������*/
#define CE_WLS_RFID_PICC_REQIDL           0x26               /*!< Ѱ��������δ��������״̬*/
#define CE_WLS_RFID_PICC_REQALL           0x52               /*!< Ѱ��������ȫ����*/
#define CE_WLS_RFID_PICC_ANTICOLL1        0x93               /*!< ����ײ*/
#define CE_WLS_RFID_PICC_ANTICOLL2        0x95               /*!< ����ײ*/
#define CE_WLS_RFID_PICC_AUTHENT1A        0x60               /*!< ��֤A��Կ*/
#define CE_WLS_RFID_PICC_AUTHENT1B        0x61               /*!< ��֤B��Կ*/
#define CE_WLS_RFID_PICC_READ             0x30               /*!< ������*/
#define CE_WLS_RFID_PICC_WRITE            0xA0               /*!< д����*/
#define CE_WLS_RFID_PICC_DECREMENT        0xC0               /*!< �ۿ�*/
#define CE_WLS_RFID_PICC_INCREMENT        0xC1               /*!< ��ֵ*/
#define CE_WLS_RFID_PICC_RESTORE          0xC2               /*!< ���������ݵ�������*/
#define CE_WLS_RFID_PICC_TRANSFER         0xB0               /*!< ���滺����������*/
#define CE_WLS_RFID_PICC_HALT             0x50               /*!< ����*/

/*!< MF522 FIFO���ȶ���*/
#define CE_WLS_RFID_DEF_FIFO_LENGTH       64                 /*!< FIFO size=64byte*/

/*!< MF522�Ĵ�������*/
/*!< PAGE 0*/
#define     CE_WLS_RFID_RFU00                 0x00
#define     CE_WLS_RFID_CommandReg            0x01
#define     CE_WLS_RFID_ComIEnReg             0x02
#define     CE_WLS_RFID_DivlEnReg             0x03
#define     CE_WLS_RFID_ComIrqReg             0x04
#define     CE_WLS_RFID_DivIrqReg             0x05
#define     CE_WLS_RFID_ErrorReg              0x06
#define     CE_WLS_RFID_Status1Reg            0x07
#define     CE_WLS_RFID_Status2Reg            0x08
#define     CE_WLS_RFID_FIFODataReg           0x09
#define     CE_WLS_RFID_FIFOLevelReg          0x0A
#define     CE_WLS_RFID_WaterLevelReg         0x0B
#define     CE_WLS_RFID_ControlReg            0x0C
#define     CE_WLS_RFID_BitFramingReg         0x0D
#define     CE_WLS_RFID_CollReg               0x0E
#define     CE_WLS_RFID_RFU0F                 0x0F
/*!< PAGE 1*/
#define     CE_WLS_RFID_RFU10                 0x10
#define     CE_WLS_RFID_ModeReg               0x11
#define     CE_WLS_RFID_TxModeReg             0x12
#define     CE_WLS_RFID_RxModeReg             0x13
#define     CE_WLS_RFID_TxControlReg          0x14
#define     CE_WLS_RFID_TxAutoReg             0x15
#define     CE_WLS_RFID_TxSelReg              0x16
#define     CE_WLS_RFID_RxSelReg              0x17
#define     CE_WLS_RFID_RxThresholdReg        0x18
#define     CE_WLS_RFID_DemodReg              0x19
#define     CE_WLS_RFID_RFU1A                 0x1A
#define     CE_WLS_RFID_RFU1B                 0x1B
#define     CE_WLS_RFID_MifareReg             0x1C
#define     CE_WLS_RFID_RFU1D                 0x1D
#define     CE_WLS_RFID_RFU1E                 0x1E
#define     CE_WLS_RFID_SerialSpeedReg        0x1F
/*!< PAGE 2*/
#define     CE_WLS_RFID_RFU20                 0x20
#define     CE_WLS_RFID_CRCResultRegM         0x21
#define     CE_WLS_RFID_CRCResultRegL         0x22
#define     CE_WLS_RFID_RFU23                 0x23
#define     CE_WLS_RFID_ModWidthReg           0x24
#define     CE_WLS_RFID_RFU25                 0x25
#define     CE_WLS_RFID_RFCfgReg              0x26
#define     CE_WLS_RFID_GsNReg                0x27
#define     CE_WLS_RFID_CWGsCfgReg            0x28
#define     CE_WLS_RFID_ModGsCfgReg           0x29
#define     CE_WLS_RFID_TModeReg              0x2A
#define     CE_WLS_RFID_TPrescalerReg         0x2B
#define     CE_WLS_RFID_TReloadRegH           0x2C
#define     CE_WLS_RFID_TReloadRegL           0x2D
#define     CE_WLS_RFID_TCounterValueRegH     0x2E
#define     CE_WLS_RFID_TCounterValueRegL     0x2F
/*!< PAGE 3*/
#define     CE_WLS_RFID_RFU30                 0x30
#define     CE_WLS_RFID_TestSel1Reg           0x31
#define     CE_WLS_RFID_TestSel2Reg           0x32
#define     CE_WLS_RFID_TestPinEnReg          0x33
#define     CE_WLS_RFID_TestPinValueReg       0x34
#define     CE_WLS_RFID_TestBusReg            0x35
#define     CE_WLS_RFID_AutoTestReg           0x36
#define     CE_WLS_RFID_VersionReg            0x37
#define     CE_WLS_RFID_AnalogTestReg         0x38
#define     CE_WLS_RFID_TestDAC1Reg           0x39
#define     CE_WLS_RFID_TestDAC2Reg           0x3A
#define     CE_WLS_RFID_TestADCReg            0x3B
#define     CE_WLS_RFID_RFU3C                 0x3C
#define     CE_WLS_RFID_RFU3D                 0x3D
#define     CE_WLS_RFID_RFU3E                 0x3E
#define     CE_WLS_RFID_RFU3F                 0x3F

/*!< ��MF522ͨѶʱ���صĴ������*/
#define CE_WLS_RFID_MI_OK                     (uint8)(0x00)
#define CE_WLS_RFID_MI_NOTAGERR               (uint8)(0x01)
#define CE_WLS_RFID_MI_ERR                    (uint8)(0x02)

uint8 ceWlsRfid_pcdComMF522(CeWlsRfid *ceWlsRfid, uint8 Command, uint8 *pIn, uint8 InLenByte, uint8 *pOut, uint8 *pOutLenBit);
void ceWlsRfid_calulateCRC(CeWlsRfid *ceWlsRfid, uint8 *pIn , uint8   len, uint8 *pOut);
void ceWlsRfid_pcdAntennaOn(CeWlsRfid *ceWlsRfid);

/**
  * @brief  ��RC522�Ĵ���
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  Address:�����Ĵ�����ַ
  * @return ���ض�ȡ����ֵ
  */
uint8 ceWlsRfid_readRawRC(CeWlsRfid *ceWlsRfid, uint8 Address)
{
    uint8   ucAddr;
    uint8   ucResult = 0;
    ceSpiMasterOp.resetSpiMasterNSSBit(&(ceWlsRfid->ceSpiMaster));
    ucAddr = ((Address << 1) & 0x7E) | 0x80;
    ceSpiMasterOp.writeReadSpiMasterByte(&(ceWlsRfid->ceSpiMaster),  ucAddr);
    ucResult = ceSpiMasterOp.writeReadSpiMasterByte(&(ceWlsRfid->ceSpiMaster), 0x00);
    ceSpiMasterOp.setSpiMasterNSSBit(&(ceWlsRfid->ceSpiMaster));
    return ucResult;
}

/**
  * @brief  дRC522�Ĵ���
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  Address:�����Ĵ�����ַ
  * @param  value:д���ֵ
  * @return None
  */
void ceWlsRfid_writeRawRC(CeWlsRfid *ceWlsRfid, uint8 Address, uint8 value)
{
    uint8   ucAddr;
    ceSpiMasterOp.resetSpiMasterNSSBit(&(ceWlsRfid->ceSpiMaster));
    ucAddr = ((Address << 1) & 0x7E);
    ceSpiMasterOp.writeReadSpiMasterByte(&(ceWlsRfid->ceSpiMaster),  ucAddr);
    ceSpiMasterOp.writeReadSpiMasterByte(&(ceWlsRfid->ceSpiMaster),  value);
    ceSpiMasterOp.setSpiMasterNSSBit(&(ceWlsRfid->ceSpiMaster));
}

/**
  * @brief  ��RC522�Ĵ�����ָ��λ��1
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  reg:�Ĵ�����ַ
  * @param  mask:������ָ��λ
  * @return None
  */
void ceWlsRfid_setBitMask(CeWlsRfid *ceWlsRfid, uint8 reg, uint8 mask)
{
    uint8   tmp = 0x0;
    tmp = ceWlsRfid_readRawRC(ceWlsRfid, reg);
    ceWlsRfid_writeRawRC(ceWlsRfid, reg, tmp | mask); // set bit mask
}

/**
  * @brief  ��RC522�Ĵ�����ָ��λ��0
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  reg:�Ĵ�����ַ
  * @param  mask:������ָ��λ
  * @return None
  */
void ceWlsRfid_clearBitMask(CeWlsRfid *ceWlsRfid, uint8 reg, uint8 mask)
{
    uint8   tmp = 0x0;
    tmp = ceWlsRfid_readRawRC(ceWlsRfid, reg);
    ceWlsRfid_writeRawRC(ceWlsRfid, reg, tmp & ~mask);  // clear bit mask
}

/**
  * @brief  Ѱ��
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  req_code:Ѱ����ʽ��0x52��ʾѰ��Ӧ�������з���14443A��׼�Ŀ���0x26��ʾѰδ��������״̬�Ŀ�
  * @param  pTagType:Ѱ����Ƭ�Ŀ�Ƭ���ʹ��룬���忴 CE_WLS_RFID_CARD_TYPE
  * @return �ɹ�����MI_OK
  */
uint8 ceWlsRfid_pcdRequest(CeWlsRfid *ceWlsRfid, uint8 req_code, uint8 *pTagType)
{
    uint8   status;
    uint8   unLen;
    uint8   ucComMF522Buf[CE_WLS_RFID_MAXR_LEN];
    ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_Status2Reg, 0x08);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_BitFramingReg, 0x07);
    ceWlsRfid_setBitMask(ceWlsRfid, CE_WLS_RFID_TxControlReg, 0x03);
    ucComMF522Buf[0] = req_code;
    status = ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_TRANSCEIVE, ucComMF522Buf, 1, ucComMF522Buf, &unLen);
    if((status == CE_WLS_RFID_MI_OK) && (unLen == 0x10))
    {
        *pTagType     = ucComMF522Buf[0];
        *(pTagType + 1) = ucComMF522Buf[1];
    }
    else
    {
        status = CE_WLS_RFID_MI_ERR;
    }
    return status;
}

/**
  * @brief  ����ײ
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  pSnr:��Ƭ���кţ�4�ֽڣ�32λ
  * @return �ɹ�����MI_OK
  */
uint8 ceWlsRfid_pcdAnticoll(CeWlsRfid *ceWlsRfid, uint8 *pSnr)
{
    uint8   status;
    uint8   i, snr_check = 0;
    uint8   unLen;
    uint8   ucComMF522Buf[CE_WLS_RFID_MAXR_LEN];
    ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_Status2Reg, 0x08);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_BitFramingReg, 0x00);
    ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_CollReg, 0x80);
    ucComMF522Buf[0] = CE_WLS_RFID_PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;
    status = ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, &unLen);
    if(status == CE_WLS_RFID_MI_OK)
    {
        for(i = 0; i < 4; i++)
        {
            *(pSnr + i)  = ucComMF522Buf[i];
            snr_check ^= ucComMF522Buf[i];
        }
        if(snr_check != ucComMF522Buf[i])
        {
            status = CE_WLS_RFID_MI_ERR;
        }
    }
    ceWlsRfid_setBitMask(ceWlsRfid, CE_WLS_RFID_CollReg, 0x80);
    return status;
}

/**
  * @brief  ѡ����Ƭ
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  pSnr:��Ƭ���кţ�4�ֽڣ�32λ
  * @return �ɹ�����MI_OK
  */
uint8 ceWlsRfid_pcdSelect(CeWlsRfid *ceWlsRfid, uint8 *pSnr)
{
    uint8   status;
    uint8   i;
    uint8   unLen;
    uint8   ucComMF522Buf[CE_WLS_RFID_MAXR_LEN];
    ucComMF522Buf[0] = CE_WLS_RFID_PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
    for(i = 0; i < 4; i++)
    {
        ucComMF522Buf[i + 2] = *(pSnr + i);
        ucComMF522Buf[6]  ^= *(pSnr + i);
    }
    ceWlsRfid_calulateCRC(ceWlsRfid, ucComMF522Buf, 7, &ucComMF522Buf[7]);
    ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_Status2Reg, 0x08);
    status = ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, &unLen);
    if((status == CE_WLS_RFID_MI_OK) && (unLen == 0x18))
    {
        status = CE_WLS_RFID_MI_OK;
    }
    else
    {
        status = CE_WLS_RFID_MI_ERR;
    }
    return status;
}

/**
  * @brief  ��֤��Ƭ����
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  auth_mode:������֤ģʽ��0x60��ʾA��Կ��0x61��ʾB��Կ
  * @param  addr:��֤�Ŀ��ַ
  * @param  pkey:��֤�����뻺����
  * @param  pSnr:��Ƭ���кţ�4�ֽڣ�32λ
  * @return �ɹ�����MI_OK
  */
uint8 ceWlsRfid_pcdAuthState(CeWlsRfid *ceWlsRfid, uint8 auth_mode, uint8 addr, uint8 *pKey, uint8 *pSnr)
{
    uint8   status;
    uint8   unLen;
    uint8   i, ucComMF522Buf[CE_WLS_RFID_MAXR_LEN];
    ucComMF522Buf[0] = auth_mode;
    ucComMF522Buf[1] = addr;
    for(i = 0; i < 6; i++)
    {
        ucComMF522Buf[i + 2] = *(pKey + i);
    }
    for(i = 0; i < 6; i++)
    {
        ucComMF522Buf[i + 8] = *(pSnr + i);
    }
    status = ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, &unLen);
    if((status != CE_WLS_RFID_MI_OK) || (!(ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_Status2Reg) & 0x08)))
    {
        status = CE_WLS_RFID_MI_ERR;
    }
    return status;
}

/**
  * @brief  ��ȡM1��ָ���������
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  addr:��ȡ�Ŀ��ַ
  * @param  p:��ȡ��������ǵĻ�������16�ֽ�
  * @return �ɹ�����MI_OK
  */
uint8 ceWlsRfid_pcdRead(CeWlsRfid *ceWlsRfid, uint8 addr, uint8 *pOutBuf)
{
    uint8   status;
    uint8   unLen;
    uint8   i, ucComMF522Buf[CE_WLS_RFID_MAXR_LEN];
    ucComMF522Buf[0] = CE_WLS_RFID_PICC_READ;
    ucComMF522Buf[1] = addr;
    ceWlsRfid_calulateCRC(ceWlsRfid, ucComMF522Buf, 2, &ucComMF522Buf[2]);
    status = ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);
    if((status == CE_WLS_RFID_MI_OK) && (unLen == 0x90))
    {
        for(i = 0; i < 16; i++)
        {
            *(pOutBuf + i) = ucComMF522Buf[i];
        }
    }
    else
    {
        status = CE_WLS_RFID_MI_ERR;
    }
    return status;
}

/**
  * @brief  д���ݵ�M1����ָ����
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  addr:д��Ŀ��ַ
  * @param  p:д������ݣ�16�ֽ�
  * @return �ɹ�����MI_OK
  */
uint8 ceWlsRfid_pcdWrite(CeWlsRfid *ceWlsRfid, uint8 addr, uint8 *pInBuf)
{
    uint8   status;
    uint8   unLen;
    uint8   i, ucComMF522Buf[CE_WLS_RFID_MAXR_LEN];
    ucComMF522Buf[0] = CE_WLS_RFID_PICC_WRITE;
    ucComMF522Buf[1] = addr;
    ceWlsRfid_calulateCRC(ceWlsRfid, ucComMF522Buf, 2, &ucComMF522Buf[2]);
    status = ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);
    if((status != CE_WLS_RFID_MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {
        status = CE_WLS_RFID_MI_ERR;
    }
    if(status == CE_WLS_RFID_MI_OK)
    {
        for(i = 0; i < 16; i++)
        {
            ucComMF522Buf[i] = *(pInBuf + i);
        }
        ceWlsRfid_calulateCRC(ceWlsRfid, ucComMF522Buf, 16, &ucComMF522Buf[16]);
        status = ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, &unLen);
        if((status != CE_WLS_RFID_MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {
            status = CE_WLS_RFID_MI_ERR;
        }
    }
    return status;
}

/**
  * @brief  ���Ƭ��������״̬
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @return �ɹ�����MI_OK
  */
uint8 ceWlsRfid_pcdHalt(CeWlsRfid *ceWlsRfid)
{
    uint8   unLen;
    uint8   ucComMF522Buf[CE_WLS_RFID_MAXR_LEN];
    ucComMF522Buf[0] = CE_WLS_RFID_PICC_HALT;
    ucComMF522Buf[1] = 0;
    ceWlsRfid_calulateCRC(ceWlsRfid, ucComMF522Buf, 2, &ucComMF522Buf[2]);
    //status = ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);//��δ�õ��˱���
    ceWlsRfid_pcdComMF522(ceWlsRfid, CE_WLS_RFID_PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);
    return CE_WLS_RFID_MI_OK;
}

/**
  * @brief  ��RC522����CRC16
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  pIn:���������
  * @param  len:��������ݳ���
  * @param  pOut:�����Ľ��
  * @return �ɹ�����MI_OK
  */
void ceWlsRfid_calulateCRC(CeWlsRfid *ceWlsRfid, uint8 *pIn , uint8 len, uint8 *pOut)
{
    uint8   i, n;
    ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_DivIrqReg, 0x04);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_CommandReg, CE_WLS_RFID_PCD_IDLE);
    ceWlsRfid_setBitMask(ceWlsRfid, CE_WLS_RFID_FIFOLevelReg, 0x80);
    for(i = 0; i < len; i++)
    {
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_FIFODataReg, *(pIn + i));
    }
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_CommandReg, CE_WLS_RFID_PCD_CALCCRC);
    i = 0xFF;
    do
    {
        n = ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_DivIrqReg);
        i--;
    }
    while((i != 0) && !(n & 0x04));
    pOut [0] = ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_CRCResultRegL);
    pOut [1] = ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_CRCResultRegM);
}

/**
  * @brief  ��λRC522
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @return �ɹ�����MI_OK
  */
uint8 ceWlsRfid_pcdReset(CeWlsRfid *ceWlsRfid)
{
    ceGpioOp.setGpioBit(&(ceWlsRfid->ceGpioRst));
    ceSystemOp.delayNs(10);
    ceGpioOp.resetGpioBit(&(ceWlsRfid->ceGpioRst));
    ceSystemOp.delayNs(10);
    ceGpioOp.setGpioBit(&(ceWlsRfid->ceGpioRst));
    ceSystemOp.delayNs(10);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_CommandReg, CE_WLS_RFID_PCD_RESETPHASE);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_CommandReg, CE_WLS_RFID_PCD_RESETPHASE);
    ceSystemOp.delayNs(10);

    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_ModeReg, 0x3D);//��Mifare��ͨѶ��CRC��ʼֵ0x6363
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TReloadRegL, 30);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TReloadRegH, 0);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TModeReg, 0x8D);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TPrescalerReg, 0x3E);
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TxAutoReg, 0x40);

    return CE_WLS_RFID_MI_OK;
}

/**
  * @brief  ����RC522�Ĺ�����ʽ
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  type:�����ķ�ʽ
  * @return None
  */
uint8 ceWlsRfid_pcdConfigISOType(CeWlsRfid *ceWlsRfid, uint8 mode)
{
    if(mode == 'A')                      //ISO14443_A
    {
        ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_Status2Reg, 0x08);
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_ModeReg, 0x3D); //3F
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_RxSelReg, 0x86); //84
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_RFCfgReg, 0x7F);  //4F
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TReloadRegL, 30); //tmoLength);// TReloadVal = 'h6a =tmoLength(dec)
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TReloadRegH, 0);
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TModeReg, 0x8D);
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_TPrescalerReg, 0x3E);
        ceSystemOp.delayUs(1);
        ceWlsRfid_pcdAntennaOn(ceWlsRfid);
    }
    else
    {
        return 1;
    }
    return CE_WLS_RFID_MI_OK;
}

/**
  * @brief  ͨ��RC522��ISO14443��ͨѶ
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  Command:RC522������
  * @param  pIn:ͨ��RC522���͵���Ƭ�����ݻ�����
  * @param  InLenByte:�������ݵ��ֽڳ���
  * @param  pOut:��Ž������Կ�Ƭ�������ݵĻ�����
  * @param  pOutLenBit:���ؽ������ݵ�λ����
  * @return None
  */
uint8 ceWlsRfid_pcdComMF522(CeWlsRfid *ceWlsRfid, uint8 Command, uint8 *pIn, uint8 InLenByte, uint8 *pOut, uint8 *pOutLenBit)
{
    uint8   status = CE_WLS_RFID_MI_ERR;
    uint8   irqEn   = 0x00;
    uint8   waitFor = 0x00;
    uint8   lastBits;
    uint8   n;
    u16   i;
    switch(Command)
    {
    case CE_WLS_RFID_PCD_AUTHENT:
        irqEn   = 0x12;
        waitFor = 0x10;
        break;
    case CE_WLS_RFID_PCD_TRANSCEIVE:
        irqEn   = 0x77;
        waitFor = 0x30;
        break;
    default:
        break;
    }
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_ComIEnReg, irqEn | 0x80);
    ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_ComIrqReg, 0x80);  //�������ж�λ
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_CommandReg, CE_WLS_RFID_PCD_IDLE);
    ceWlsRfid_setBitMask(ceWlsRfid, CE_WLS_RFID_FIFOLevelReg, 0x80);     //��FIFO����
    for(i = 0; i < InLenByte; i++)
    {
        ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_FIFODataReg, pIn [i]);
    }
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_CommandReg, Command);
    if(Command == CE_WLS_RFID_PCD_TRANSCEIVE)
    {
        ceWlsRfid_setBitMask(ceWlsRfid, CE_WLS_RFID_BitFramingReg, 0x80);     //��ʼ����
    }
    //i = 600;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
    i = 2000;
    do
    {
        n = ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_ComIrqReg);
        i--;
    }
    while((i != 0) && !(n & 0x01) && !(n & waitFor));

    ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_BitFramingReg, 0x80);
    if(i != 0)
    {
        if(!(ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_ErrorReg) & 0x1B))
        {
            status = CE_WLS_RFID_MI_OK;
            if(n & irqEn & 0x01)
            {
                status = CE_WLS_RFID_MI_NOTAGERR;
            }
            if(Command == CE_WLS_RFID_PCD_TRANSCEIVE)
            {
                n = ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_FIFOLevelReg);
                lastBits = ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_ControlReg) & 0x07;
                if(lastBits)
                {
                    *pOutLenBit = (n - 1) * 8 + lastBits;
                }
                else
                {
                    *pOutLenBit = n * 8;
                }
                if(n == 0)
                {
                    n = 1;
                }
                if(n > CE_WLS_RFID_MAXR_LEN)
                {
                    n = CE_WLS_RFID_MAXR_LEN;
                }
                for(i = 0; i < n; i++)
                {
                    pOut [i] = ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_FIFODataReg);
                }
            }
        }
        else
        {
            status = CE_WLS_RFID_MI_ERR;
        }
    }
    ceWlsRfid_setBitMask(ceWlsRfid, CE_WLS_RFID_ControlReg, 0x80);          // stop timer now
    ceWlsRfid_writeRawRC(ceWlsRfid, CE_WLS_RFID_CommandReg, CE_WLS_RFID_PCD_IDLE);
    return status;
}

/**
  * @brief  �������ߣ��������ߺ͹ر����߷���֮��������1ms�ļ����
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @return None
  */
void ceWlsRfid_pcdAntennaOn(CeWlsRfid *ceWlsRfid)
{
    uint8   i;
    i = ceWlsRfid_readRawRC(ceWlsRfid, CE_WLS_RFID_TxControlReg);
    if(!(i & 0x03))
    {
        ceWlsRfid_setBitMask(ceWlsRfid, CE_WLS_RFID_TxControlReg, 0x03);
    }
}

/**
  * @brief  �ر�����
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @return None
  */
void ceWlsRfid_pcdAntennaOff(CeWlsRfid *ceWlsRfid)
{
    ceWlsRfid_clearBitMask(ceWlsRfid, CE_WLS_RFID_TxControlReg, 0x03);
}

/**
  * @brief  CeWlsRfidģ���ʼ��
  * @param  ceWlsRfid:CeWlsRfid���Զ���
  * @param  ceSpi:CeWlsRfidģ��ʹ�õ�Spi��Դ��
  * @param  ceGpio:CeWlsRfidģ��ʹ�õ�Gpio��Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceWlsRfid_initial(CeWlsRfid *ceWlsRfid, CE_RESOURCE ceSpi, CE_RESOURCE ceGpio)
{
    ceWlsRfid->ceGpioRst.ceResource = ceGpio;
    ceWlsRfid->ceGpioRst.ceGpioMode = CE_GPIO_MODE_OUT_PP;//CE_GPIO_MODE_IPD
    ceGpioOp.initial(&(ceWlsRfid->ceGpioRst));
    ceGpioOp.setGpioBit(&(ceWlsRfid->ceGpioRst));

    ceWlsRfid->ceSpiMaster.ceResource = ceSpi;
    ceWlsRfid->ceSpiMaster.ceSpiMasterSpeed = CE_SPI_MASTER_SPEED_100KBPS;
    ceSpiMasterOp.initial(&(ceWlsRfid->ceSpiMaster));
    ceSpiMasterOp.start(&(ceWlsRfid->ceSpiMaster));

    ceWlsRfid_pcdReset(ceWlsRfid);
    ceWlsRfid_pcdAntennaOff(ceWlsRfid);
    ceSystemOp.delayMs(2);
    ceWlsRfid_pcdAntennaOn(ceWlsRfid);
    ceWlsRfid_pcdConfigISOType(ceWlsRfid, 'A');

    return CE_STATUS_SUCCESS;
}

CE_STATUS ceWlsRfid_setOn(CeWlsRfid *ceWlsRfid)
{
    ceWlsRfid_pcdAntennaOn(ceWlsRfid);
    return CE_STATUS_SUCCESS;
}

CeWlsRfidCardInfo *ceWlsRfid_connectCard(CeWlsRfid *ceWlsRfid)
{
    uint8 pTagType[4];
    if(CE_WLS_RFID_MI_OK == ceWlsRfid_pcdRequest(ceWlsRfid, 0x52, pTagType))
    {
        if(CE_WLS_RFID_MI_OK == ceWlsRfid_pcdAnticoll(ceWlsRfid, ceWlsRfid->ceWlsRfidCardInfo.serialNumber))
        {
            if(CE_WLS_RFID_MI_OK == ceWlsRfid_pcdSelect(ceWlsRfid, ceWlsRfid->ceWlsRfidCardInfo.serialNumber))
            {
                ceWlsRfid->ceWlsRfidCardInfo.cardType = (CE_WLS_RFID_CARD_TYPE)(((((uint16)pTagType[0]) << 8) | (pTagType[1] & 0xFF)));
                return &(ceWlsRfid->ceWlsRfidCardInfo);
            }
        }
    }
    return CE_NULL;
}

CE_STATUS ceWlsRfid_initialSection(CeWlsRfid *ceWlsRfid, uint8 blockIndex, char *defaultPasswordA, char *defaultPasswordB, char *newPasswordARead, char *newPasswordBWrite)
{
    return CE_STATUS_SUCCESS;
}

CE_STATUS ceWlsRfid_readSection(CeWlsRfid *ceWlsRfid, uint8 sectorIndex, uint8 blockIndex, char *passwordARead, char *dataOut)
{
    uint8 blockAbsoluteIndex = (sectorIndex * 4) + blockIndex;
    if (sectorIndex > 15 || blockIndex > 2)
    {
        return CE_STATUS_PAR_ERROR;
    }

    if(CE_WLS_RFID_MI_OK == ceWlsRfid_pcdAuthState(ceWlsRfid, 0x60, blockAbsoluteIndex, (uint8 *)passwordARead, ceWlsRfid->ceWlsRfidCardInfo.serialNumber))
    {
        ceWlsRfid_pcdRead(ceWlsRfid, blockAbsoluteIndex, (uint8 *)dataOut);
        return CE_STATUS_SUCCESS;
    }
    else
    {
        return CE_STATUS_FAILE;
    }
}

CE_STATUS ceWlsRfid_writeSection(CeWlsRfid *ceWlsRfid, uint8 sectorIndex, uint8 blockIndex, char *passwordBWrite, char *dataIn)
{
    uint8 blockAbsoluteIndex = (sectorIndex * 4) + blockIndex;
    if (sectorIndex == 0 || sectorIndex > 15 || blockIndex > 2)
    {
        return CE_STATUS_PAR_ERROR;
    }

    if(CE_WLS_RFID_MI_OK == ceWlsRfid_pcdAuthState(ceWlsRfid, 0x60, blockAbsoluteIndex, (uint8 *)passwordBWrite, ceWlsRfid->ceWlsRfidCardInfo.serialNumber))
    {
        ceWlsRfid_pcdWrite(ceWlsRfid, blockAbsoluteIndex, (uint8 *)dataIn);
        return CE_STATUS_SUCCESS;
    }
    else
    {
        return CE_STATUS_FAILE;
    }
}

CE_STATUS ceWlsRfid_releaseCard(CeWlsRfid *ceWlsRfid)
{
    ceWlsRfid_pcdHalt(ceWlsRfid);
    return CE_STATUS_SUCCESS;
}

CE_STATUS ceWlsRfid_setOff(CeWlsRfid *ceWlsRfid)
{
    ceWlsRfid_pcdAntennaOff(ceWlsRfid);
    return CE_STATUS_SUCCESS;
}

CeWlsRfidOpBase ceWlsRfidOp = {ceWlsRfid_initial, ceWlsRfid_setOn, ceWlsRfid_connectCard, ceWlsRfid_initialSection, ceWlsRfid_readSection, ceWlsRfid_writeSection,
                             ceWlsRfid_releaseCard, ceWlsRfid_setOff
                            };

#ifdef __cplusplus
 }
#endif //__cplusplus

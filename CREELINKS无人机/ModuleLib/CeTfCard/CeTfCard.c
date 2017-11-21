/**
  ******************************************************************************
  * @file    CeTfCard.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTfCard模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)如需对FatFs文件系统进行裁剪或其他操作请修改ffconf.h中的宏定义，如果FatFs的版本没有变动，无需对CeTfCrad.h及.c进行任何修改！
  *2)FatFs文件管理系统提供的功能接口，模块内没有进行任何封装，直接进行指针调用
  *3).h及.c中的某些函数跟FatFs文件系统开启的功能有关，如有改动请保持.h和.c完全一致
  *4).h及.c中某些函数在ff.h中是宏定义实现，所以对其进行了封装。
  *5).h及.c中某些函数的返回值或者参数的类型引用自ffxx/src/integer.h，如有改动请注意！
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeTfCard.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

//#define CE_TF_CARD_DEBUG                      /*!< 模块调试初始的开关*/
#define CE_TF_CARD_TYPE_MMC     	     0x00   /*!< 模块的类型为MMC*/
#define CE_TF_CARD_TYPE_SDV1      	     0x01   /*!< 模块的类型为SDV1*/
#define CE_TF_CARD_TYPE_SDV2      	     0x02   /*!< 模块的类型为SDV2*/
#define CE_TF_CARD_TYPE_SDV2HC    	     0x04   /*!< 模块的类型为SDV2HC */

#define CE_TF_CARD_SPI_NO_RELEASE_BUS    0x00   /*!< Spi传输数据结束后不需要释放总线宏定义*/
#define CE_TF_CARD_SPI_RELEASE_BUS       0x01   /*!< Spi传输数据结束后需要释放总线宏定义*/

/* SD/MMC指令集 - SPI模式*/
#define CE_TF_CARD_CMD_0        0       /*!< 卡复位*/
#define CE_TF_CARD_CMD_1        1       /*!< Send Operator Condition - SEND_OP_COND*/
#define CE_TF_CARD_CMD_8        8       /*!< Send Interface Condition - SEND_IF_COND*/
#define CE_TF_CARD_CMD_9        9       /*!< 命令9 ，读CSD数据*/
#define CE_TF_CARD_CMD_10       10      /*!< 命令10，读CID数据*/
#define CE_TF_CARD_CMD_12       12      /*!< 命令12，停止数据传输*/
#define CE_TF_CARD_CMD_16       16      /*!< 命令16，设置SectorSize 应返回0x00*/
#define CE_TF_CARD_CMD_17       17      /*!< 命令17，读sector*/
#define CE_TF_CARD_CMD_18       18      /*!< 命令18，读Multi sector*/
#define CE_TF_CARD_A_CMD_23     23      /*!< 命令23，设置多sector写入前预先擦除N个block*/
#define CE_TF_CARD_CMD_24       24      /*!< 命令24，写sector*/
#define CE_TF_CARD_CMD_25       25      /*!< 命令25，写Multi sector*/
#define CE_TF_CARD_A_CMD_41     41      /*!< 命令41，应返回0x00*/
#define CE_TF_CARD_CMD_55       55      /*!< 命令55，应返回0x01*/
#define CE_TF_CARD_CMD_58       58      /*!< 命令58，读OCR信息*/
#define CE_TF_CARD_CMD_59       59      /*!< 命令59，使能/禁止CRC，应返回0x00*/

#define CE_TF_CARD_DUMMY_BYTE   0xFF    /*!< Spi读操作写的数据*/
#define CE_TF_CARD_BLOCK_SIZE   512     /*!< Block大小*/

// #define CE_TF_CARD_INITIAL_ERROR 0x01      /*!< CeTftCrad失败*/
// #define CE_TF_CARD_NO_DISK       0x02      /*!< CeTftCrad无磁盘*/
// #define CE_TF_CARD_PROTECT       0x04      /*!< CeTftCrad写保护*/
// #define CE_TF_CARD_IS_IDLE       0x08      /*!< CeTftCrad空闲标志*/
// #define CE_TF_CARD_IS_BUSY       0x10      /*!< CeTftCrad忙碌标志*/

CeSpiMaster ceSpiMaster;                    /*!< CeTfCard模块用到的Spi资源对象，用于进行SPI通讯，目前仅支持一个CeTfCard模块*/
CeGpio      ceGpio;                         /*!< CeTfCard模块用到的Gpio资源对象，用于检测Tf卡师傅插入，目前仅支持一个CeTfCard模块*/
CeTfCard_CardInfo ceTfCard_cardInfo;        /*!< CeTfCard模块获取信息的全局变量*/

/**
  * @brief  设置Mcu和CeTfCard模块通讯的速率
  * @param  SpeedSet:1位高速率，其他为低速率
  * @param  arg:欲发送的指令对应的参数
  * @param  crc:CRC校验值
  * @return 返回操作状态
  */
void ceTfCard_tfSetSpeed(uint8 SpeedSet)
{
    //最好在CeSpi中增加修改速率的函数
    ceSpiMaster.ceSpiMasterSpeed = (SpeedSet == 0x01) ? CE_SPI_MASTER_SPEED_100MBPS : CE_SPI_MASTER_SPEED_100KBPS;
    ceSpiMasterOp.stop(&ceSpiMaster);
    ceSpiMasterOp.initial(&ceSpiMaster);
    ceSpiMasterOp.start(&ceSpiMaster);
}

/**
  * @brief  发送指令
  * @param  cmd:欲发送的指令
  * @param  arg:欲发送的指令对应的参数
  * @param  crc:CRC校验值
  * @return 返回操作状态
  */
uint8 ceTfCrad_tfSendCommand(uint8 cmd, uint32 arg, uint8 crc)
{
    uint8 readVal;
    uint8 retry;

    /* Dummy byte and chip enable */
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
    ceSpiMasterOp.resetSpiMasterNSSBit(&ceSpiMaster);//片选端置低，使能SD卡

    /* Command, argument and crc */
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, cmd | 0x40);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, arg >> 24);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, arg >> 16);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, arg >> 8);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, arg);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, crc);

    /* Wait response, quit till timeout */
    for(retry=0; retry<200; retry++)
    {
        readVal = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
        if(readVal != 0xFF)
        {
            break;
        }
    }

    /* Chip disable and dummy byte */
    ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);

    return readVal;
}

/**
  * @brief  发送指令并保持总线处于工作状态
  * @param  cmd:欲发送的指令
  * @param  arg:欲发送的指令对应的参数
  * @param  crc:CRC校验值
  * @return 返回操作状态
  */
uint8 ceTfCard_rdSendCommandHold(uint8 cmd, uint32 arg, uint8 crc)
{
    uint8 readVal;
    uint8 retry;

    /* Dummy byte and chip enable */
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
    ceSpiMasterOp.resetSpiMasterNSSBit(&ceSpiMaster);//片选端置低，使能SD卡

    /* Command, argument and crc */
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, cmd | 0x40);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, arg >> 24);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, arg >> 16);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, arg >> 8);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, arg);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, crc);

    /* Wait response, quit till timeout */
    for(retry=0; retry<200; retry++)
    {
        readVal = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
        if(readVal != 0xFF)
        {
            break;
        }
    }
    return readVal;
}

/**
  * @brief  接收数据
  * @param  buff:存储数据的缓冲区指针
  * @param  len:接收的长度
  * @param  release:接收完毕后是否释放SPI总线(芯片片选置高)
  * @return 返回0表示接收成功，返回1表示接收超时
  */
uint8 ceTfCard_tfReceiveData(uint8 *buff, uint16 len, uint8 release)
{
    uint8 readVal;
    uint16 retry;

    /* Card enable, Prepare to read	*/
    ceSpiMasterOp.resetSpiMasterNSSBit(&ceSpiMaster);//片选端置低，使能SD卡

    /* Wait start-token 0xFE */
    for(retry=0; retry<2000; retry++)
    {
        readVal = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
        if(readVal == 0xFE)
        {
            retry = 0;
            break;
        }
    }

    /* Timeout return	*/
    if(retry == 2000)
    {
        ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
        return 1;
    }

    /* Start reading */
    for(retry=0; retry<len; retry++)
    {
        *(buff+retry) = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
    }

    /* 2bytes dummy CRC */
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);

    /* chip disable and dummy byte */
    if(release)
    {
        ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
        ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
    }

    return 0;
}

/**
  * @brief  CeTfCard模块初始化
  * @return 返回小于0的数值表示初始化的状态，返回大于0的数值表示错误码，返回-表示成功(如需调试或修改，请参照上下文进行分析)
  */
int16 ceTfCard_tfInitial(void)
{
    uint8 readVal;
    uint8 buff[6] = {0};
    uint16 retry;

    /* Check , if no card insert */
    if(ceGpioOp.getGpioBit(&ceGpio) == 0x01)
    {
        /* FATFS error flag */
        return CE_TF_CARD_NO_DISK;
    }

    /* Power on and delay some times */
    for(retry=0; retry<0x100; retry++)
    {
        //MSD0_card_power_on();
    }

    /* Satrt send 74 clocks at least */
    for(retry=0; retry<10; retry++)
    {
        ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
    }

    /* Start send CMD0 till return 0x01 means in IDLE state */
    for(retry=0; retry<0xFFF; retry++)
    {
        readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_0, 0, 0x95);
        if(readVal == 0x01)
        {
            retry = 0;
            break;
        }
    }
    /* Timeout return */
    if(retry == 0xFFF)
    {
        return CE_TF_CARD_INITIAL_FAILE;
    }

    /* Get the card type, version */
    readVal = ceTfCard_rdSendCommandHold(CE_TF_CARD_CMD_8, 0x1AA, 0x87);
    /* r1=0x05 -> V1.0 */
    if(readVal == 0x05)
    {
        ceTfCard_cardInfo.CardType = CE_TF_CARD_TYPE_SDV1;

        /* End of CMD8, chip disable and dummy byte */
        ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
        ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);

        /* SD1.0/MMC start initialize */
        /* Send CMD55+ACMD41, No-response is a MMC card, otherwise is a SD1.0 card */
        for(retry=0; retry<0xFFF; retry++)
        {
            readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_55, 0, 0);			/* should be return 0x01 */
            if(readVal != 0x01)
            {
#ifdef CE_TF_CARD_DEBUG
                ceSystemOp.printf("CetfCard Send CMD55 should return 0x01, response=0x%02x\r\n", readVal);
#endif
                return (int16)readVal;
            }

            readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_A_CMD_41, 0, 0);			/* should be return 0x00 */
            if(readVal == 0x00)
            {
                retry = 0;
                break;
            }
        }

        /* MMC card initialize start */
        if(retry == 0xFFF)
        {
            for(retry=0; retry<0xFFF; retry++)
            {
                readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_1, 0, 0);		/* should be return 0x00 */
                if(readVal == 0x00)
                {
                    retry = 0;
                    break;
                }
            }

            /* Timeout return */
            if(retry == 0xFFF)
            {
#ifdef CE_TF_CARD_DEBUG
                ceSystemOp.printf("CetfCard Send CMD1 should return 0x00, response=0x%02x\r\n", readVal);
#endif
                return CE_TF_CARD_INITIAL_FAILE;
            }

            ceTfCard_cardInfo.CardType = CE_TF_CARD_TYPE_MMC;
#ifdef CE_TF_CARD_DEBUG
            ceSystemOp.printf("CetfCard CardType: MMC\r\n");
#endif
        }
        /* SD1.0 card detected, print information */
#ifdef CE_TF_CARD_DEBUG
        else
        {
            ceSystemOp.printf("CetfCard CardType: SD V1\r\n");
        }
#endif

        /* Set spi speed high */
        ceTfCard_tfSetSpeed(1);

        /* CRC disable */
        readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_59, 0, 0x01);
        if(readVal != 0x00)
        {
#ifdef CE_TF_CARD_DEBUG
            ceSystemOp.printf("CetfCard Send CMD59 should return 0x00, response=0x%02x\r\n", readVal);
#endif
            return (int16)readVal;		/* response error, return r1 */
        }

        /* Set the block size */
        readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_16, CE_TF_CARD_BLOCK_SIZE, CE_TF_CARD_DUMMY_BYTE);
        if(readVal != 0x00)
        {
#ifdef CE_TF_CARD_DEBUG
            ceSystemOp.printf("CetfCard Send CMD16 should return 0x00, response=0x%02x\r\n", readVal);
#endif
            return readVal;		/* response error, return r1 */
        }
    }

    /* r1=0x01 -> V2.x, read OCR register, check version */
    else if(readVal == 0x01)
    {
        /* 4Bytes returned after CMD8 sent	*/
        buff[0] = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);				/* should be 0x00 */
        buff[1] = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);				/* should be 0x00 */
        buff[2] = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);				/* should be 0x01 */
        buff[3] = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);				/* should be 0xAA */

        /* End of CMD8, chip disable and dummy byte */
        ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
        ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);

        /* Check voltage range be 2.7-3.6V	*/
        if(buff[2]==0x01 && buff[3]==0xAA)
        {
            for(retry=0; retry<0xFFF; retry++)
            {
                readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_55, 0, 0);			/* should be return 0x01 */
                if(readVal!=0x01)
                {
#ifdef CE_TF_CARD_DEBUG
                    ceSystemOp.printf("CetfCard Send CMD55 should return 0x01, response=0x%02x\r\n", readVal);
#endif
                    return (int16)readVal;
                }

                readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_A_CMD_41, 0x40000000, 0);	/* should be return 0x00 */
                if(readVal == 0x00)
                {
                    retry = 0;
                    break;
                }
            }

            /* Timeout return */
            if(retry == 0xFFF)
            {
#ifdef CE_TF_CARD_DEBUG
                ceSystemOp.printf("CetfCard Send ACMD41 should return 0x00, response=0x%02x\r\n", readVal);
#endif
                return CE_TF_CARD_INITIAL_FAILE;
            }

            /* Read OCR by CMD58 */
            readVal = ceTfCard_rdSendCommandHold(CE_TF_CARD_CMD_58, 0, 0);
            if(readVal!=0x00)
            {
#ifdef CE_TF_CARD_DEBUG
                ceSystemOp.printf("CetfCard Send CMD58 should return 0x00, response=0x%02x\r\n", readVal);
#endif
                return (int16)readVal;		/* response error, return r1 */
            }

            buff[0] = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
            buff[1] = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
            buff[2] = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);
            buff[3] = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, CE_TF_CARD_DUMMY_BYTE);

            /* End of CMD58, chip disable and dummy byte */
            ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
            ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);

            /* OCR -> CCS(bit30)  1: SDV2HC	 0: SDV2 */
            if(buff[0] & 0x40)
            {
                ceTfCard_cardInfo.CardType = CE_TF_CARD_TYPE_SDV2HC;
#ifdef CE_TF_CARD_DEBUG
                ceSystemOp.printf("CetfCard CardType: SD V2HC\r\n");
#endif
            }
            else
            {
                ceTfCard_cardInfo.CardType = CE_TF_CARD_TYPE_SDV2;
#ifdef CE_TF_CARD_DEBUG
                ceSystemOp.printf("CetfCard CardType: SD V2\r\n");
#endif
            }
            /* Set spi speed high */
            ceTfCard_tfSetSpeed(1);
        }
    }
    return CE_TF_CARD_INITIAL_SUCCESS;
}

/**
  * @brief  获取CeTfCard模块的信息
  * @param  ceTfCard_CardInfo:存放信息的结构体指针
  * @return 返回0表示获取成功，返回大于0的表示不同的错误
  */
uint8 ceTfCard_tfGetCardInfo(PCeTfCard_CardInfo ceTfCard_CardInfo)
{
    uint8 readVal;
    uint8 CSD_Tab[16];
    uint8 CID_Tab[16];

    /* Send CMD9, Read CSD */
    readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_9, 0, 0xFF);
    if(readVal != 0x00)
    {
        return readVal;
    }

    if(ceTfCard_tfReceiveData(CSD_Tab, 16, CE_TF_CARD_SPI_RELEASE_BUS))
    {
        return 1;
    }

    /* Send CMD10, Read CID */
    readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_10, 0, 0xFF);
    if(readVal != 0x00)
    {
        return readVal;
    }

    if(ceTfCard_tfReceiveData(CID_Tab, 16, CE_TF_CARD_SPI_RELEASE_BUS))
    {
        return 2;
    }

    /* Byte 0 */
    ceTfCard_CardInfo->CSD.CSDStruct = (CSD_Tab[0] & 0xC0) >> 6;
    ceTfCard_CardInfo->CSD.SysSpecVersion = (CSD_Tab[0] & 0x3C) >> 2;
    ceTfCard_CardInfo->CSD.Reserved1 = CSD_Tab[0] & 0x03;
    /* Byte 1 */
    ceTfCard_CardInfo->CSD.TAAC = CSD_Tab[1] ;
    /* Byte 2 */
    ceTfCard_CardInfo->CSD.NSAC = CSD_Tab[2];
    /* Byte 3 */
    ceTfCard_CardInfo->CSD.MaxBusClkFrec = CSD_Tab[3];
    /* Byte 4 */
    ceTfCard_CardInfo->CSD.CardComdClasses = CSD_Tab[4] << 4;
    /* Byte 5 */
    ceTfCard_CardInfo->CSD.CardComdClasses |= (CSD_Tab[5] & 0xF0) >> 4;
    ceTfCard_CardInfo->CSD.RdBlockLen = CSD_Tab[5] & 0x0F;
    /* Byte 6 */
    ceTfCard_CardInfo->CSD.PartBlockRead = (CSD_Tab[6] & 0x80) >> 7;
    ceTfCard_CardInfo->CSD.WrBlockMisalign = (CSD_Tab[6] & 0x40) >> 6;
    ceTfCard_CardInfo->CSD.RdBlockMisalign = (CSD_Tab[6] & 0x20) >> 5;
    ceTfCard_CardInfo->CSD.DSRImpl = (CSD_Tab[6] & 0x10) >> 4;
    ceTfCard_CardInfo->CSD.Reserved2 = 0; /* Reserved */
    ceTfCard_CardInfo->CSD.DeviceSize = (CSD_Tab[6] & 0x03) << 10;
    /* Byte 7 */
    ceTfCard_CardInfo->CSD.DeviceSize |= (CSD_Tab[7]) << 2;
    /* Byte 8 */
    ceTfCard_CardInfo->CSD.DeviceSize |= (CSD_Tab[8] & 0xC0) >> 6;
    ceTfCard_CardInfo->CSD.MaxRdCurrentVDDMin = (CSD_Tab[8] & 0x38) >> 3;
    ceTfCard_CardInfo->CSD.MaxRdCurrentVDDMax = (CSD_Tab[8] & 0x07);
    /* Byte 9 */
    ceTfCard_CardInfo->CSD.MaxWrCurrentVDDMin = (CSD_Tab[9] & 0xE0) >> 5;
    ceTfCard_CardInfo->CSD.MaxWrCurrentVDDMax = (CSD_Tab[9] & 0x1C) >> 2;
    ceTfCard_CardInfo->CSD.DeviceSizeMul = (CSD_Tab[9] & 0x03) << 1;
    /* Byte 10 */
    ceTfCard_CardInfo->CSD.DeviceSizeMul |= (CSD_Tab[10] & 0x80) >> 7;
    ceTfCard_CardInfo->CSD.EraseGrSize = (CSD_Tab[10] & 0x7C) >> 2;
    ceTfCard_CardInfo->CSD.EraseGrMul = (CSD_Tab[10] & 0x03) << 3;
    /* Byte 11 */
    ceTfCard_CardInfo->CSD.EraseGrMul |= (CSD_Tab[11] & 0xE0) >> 5;
    ceTfCard_CardInfo->CSD.WrProtectGrSize = (CSD_Tab[11] & 0x1F);
    /* Byte 12 */
    ceTfCard_CardInfo->CSD.WrProtectGrEnable = (CSD_Tab[12] & 0x80) >> 7;
    ceTfCard_CardInfo->CSD.ManDeflECC = (CSD_Tab[12] & 0x60) >> 5;
    ceTfCard_CardInfo->CSD.WrSpeedFact = (CSD_Tab[12] & 0x1C) >> 2;
    ceTfCard_CardInfo->CSD.MaxWrBlockLen = (CSD_Tab[12] & 0x03) << 2;
    /* Byte 13 */
    ceTfCard_CardInfo->CSD.MaxWrBlockLen |= (CSD_Tab[13] & 0xc0) >> 6;
    ceTfCard_CardInfo->CSD.WriteBlockPaPartial = (CSD_Tab[13] & 0x20) >> 5;
    ceTfCard_CardInfo->CSD.Reserved3 = 0;
    ceTfCard_CardInfo->CSD.ContentProtectAppli = (CSD_Tab[13] & 0x01);
    /* Byte 14 */
    ceTfCard_CardInfo->CSD.FileFormatGrouop = (CSD_Tab[14] & 0x80) >> 7;
    ceTfCard_CardInfo->CSD.CopyFlag = (CSD_Tab[14] & 0x40) >> 6;
    ceTfCard_CardInfo->CSD.PermWrProtect = (CSD_Tab[14] & 0x20) >> 5;
    ceTfCard_CardInfo->CSD.TempWrProtect = (CSD_Tab[14] & 0x10) >> 4;
    ceTfCard_CardInfo->CSD.FileFormat = (CSD_Tab[14] & 0x0C) >> 2;
    ceTfCard_CardInfo->CSD.ECC = (CSD_Tab[14] & 0x03);
    /* Byte 15 */
    ceTfCard_CardInfo->CSD.CSD_CRC = (CSD_Tab[15] & 0xFE) >> 1;
    ceTfCard_CardInfo->CSD.Reserved4 = 1;

    if(ceTfCard_CardInfo->CardType == CE_TF_CARD_TYPE_SDV2HC)
    {
        /* Byte 7 */
        ceTfCard_CardInfo->CSD.DeviceSize = (u16)(CSD_Tab[8]) *256;
        /* Byte 8 */
        ceTfCard_CardInfo->CSD.DeviceSize += CSD_Tab[9] ;
    }

    ceTfCard_CardInfo->Capacity = (uint64)(((uint64)ceTfCard_CardInfo->CSD.DeviceSize * (uint64)CE_TF_CARD_BLOCK_SIZE) * (uint64)1024);
    ceTfCard_CardInfo->BlockSize = CE_TF_CARD_BLOCK_SIZE;

    /* Byte 0 */
    ceTfCard_CardInfo->CID.ManufacturerID = CID_Tab[0];
    /* Byte 1 */
    ceTfCard_CardInfo->CID.OEM_AppliID = CID_Tab[1] << 8;
    /* Byte 2 */
    ceTfCard_CardInfo->CID.OEM_AppliID |= CID_Tab[2];
    /* Byte 3 */
    ceTfCard_CardInfo->CID.ProdName1 = CID_Tab[3] << 24;
    /* Byte 4 */
    ceTfCard_CardInfo->CID.ProdName1 |= CID_Tab[4] << 16;
    /* Byte 5 */
    ceTfCard_CardInfo->CID.ProdName1 |= CID_Tab[5] << 8;
    /* Byte 6 */
    ceTfCard_CardInfo->CID.ProdName1 |= CID_Tab[6];
    /* Byte 7 */
    ceTfCard_CardInfo->CID.ProdName2 = CID_Tab[7];
    /* Byte 8 */
    ceTfCard_CardInfo->CID.ProdRev = CID_Tab[8];
    /* Byte 9 */
    ceTfCard_CardInfo->CID.ProdSN = CID_Tab[9] << 24;
    /* Byte 10 */
    ceTfCard_CardInfo->CID.ProdSN |= CID_Tab[10] << 16;
    /* Byte 11 */
    ceTfCard_CardInfo->CID.ProdSN |= CID_Tab[11] << 8;
    /* Byte 12 */
    ceTfCard_CardInfo->CID.ProdSN |= CID_Tab[12];
    /* Byte 13 */
    ceTfCard_CardInfo->CID.Reserved1 |= (CID_Tab[13] & 0xF0) >> 4;
    /* Byte 14 */
    ceTfCard_CardInfo->CID.ManufactDate = (CID_Tab[13] & 0x0F) << 8;
    /* Byte 15 */
    ceTfCard_CardInfo->CID.ManufactDate |= CID_Tab[14];
    /* Byte 16 */
    ceTfCard_CardInfo->CID.CID_CRC = (CID_Tab[15] & 0xFE) >> 1;
    ceTfCard_CardInfo->CID.Reserved2 = 1;

    return 0;
}

/**
  * @brief  读单个Sector
  * @param  sector:欲操作的扇区地址(Sector值，非物理地址)
  * @param  buffer:数据存储地址(大小至少512byte)
  * @return 返回操作的状态
  */
uint8 ceTfCard_tfReadSingleBlock(uint32 sector, uint8 *buffer)
{
    uint8 readVal;

    /* if ver = SD2.0 HC, sector need <<9 */
    if(ceTfCard_cardInfo.CardType != CE_TF_CARD_TYPE_SDV2HC)
    {
        sector = sector<<9;
    }

    /* Send CMD17 : Read single block command */
    readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_17, sector, 0);

    if(readVal != 0x00)
    {
        return 1;
    }

    /* Start read and return the result */
    readVal = ceTfCard_tfReceiveData(buffer, CE_TF_CARD_BLOCK_SIZE, CE_TF_CARD_SPI_RELEASE_BUS);

    /* Send stop data transmit command - CMD12 */
    ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_12, 0, 0);

    return readVal;
}

/**
  * @brief  读多个Sector
  * @param  sector:欲操作的扇区地址(Sector值，非物理地址)
  * @param  buffer:数据存储地址(大小至少512byte)
  * @param  NbrOfSector:连续读N个Sector
  * @return 返回操作的状态
  */
uint8 ceTfCard_tfReadMultiBlock(uint32 sector, uint8 *buffer, uint32 NbrOfSector)
{
    uint8 readVal;
    uint32 i;

    /* if ver = SD2.0 HC, sector need <<9 */
    if(ceTfCard_cardInfo.CardType != CE_TF_CARD_TYPE_SDV2HC)
    {
        sector = sector<<9;
    }

    /* Send CMD18 : Read multi block command */
    readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_18, sector, 0);
    if(readVal != 0x00)
    {
        return 1;
    }

    /* Start read	*/
    for(i=0; i<NbrOfSector; i++)
    {
        if(ceTfCard_tfReceiveData(buffer+i*CE_TF_CARD_BLOCK_SIZE, CE_TF_CARD_BLOCK_SIZE, 0x00))
        {
            /* Send stop data transmit command - CMD12	*/
            ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_12, 0, 0);
            /* chip disable and dummy byte */
            ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
            return 2;
        }
    }

    /* Send stop data transmit command - CMD12 */
    ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_12, 0, 0);

    /* chip disable and dummy byte */
    ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);

    return 0;
}

/**
  * @brief  写单个Sector
  * @param  sector:欲操作的扇区地址(Sector值，非物理地址)
  * @param  buffer:数据存储地址(大小至少512byte)
  * @return 返回操作的状态
  */
uint8 ceTfCard_tfWriteSingleBlock(uint32 sector, uint8 *buffer)
{
    uint8 readVal;
    uint16 i;
    uint32 retry;

    /* if ver = SD2.0 HC, sector need <<9 */
    if(ceTfCard_cardInfo.CardType != CE_TF_CARD_TYPE_SDV2HC)
    {
        sector = sector<<9;
    }

    /* Send CMD24 : Write single block command */
    readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_24, sector, 0);

    if(readVal != 0x00)
    {
        return 1;
    }

    /* Card enable, Prepare to write */
    ceSpiMasterOp.resetSpiMasterNSSBit(&ceSpiMaster);//片选端置低，使能SD卡
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
    /* Start data write token: 0xFE */
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFE);

    /* Start single block write the data buffer */
    for(i=0; i<CE_TF_CARD_BLOCK_SIZE; i++)
    {
        ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, *buffer++);
    }

    /* 2Bytes dummy CRC */
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);

    /* MSD card accept the data */
    readVal = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
    if((readVal&0x1F) != 0x05)
    {
        ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
        return 2;
    }

    /* Wait all the data programm finished */
    retry = 0;
    while(ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF) == 0x00)
    {
        /* Timeout return */
        if(retry++ == 0x40000)
        {
            ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
            return 3;
        }
    }

    /* chip disable and dummy byte */
    ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);

    return 0;
}

/**
  * @brief  写多个Sector
  * @param  sector:欲操作的扇区地址(Sector值，非物理地址)
  * @param  buffer:数据存储地址(大小至少512byte)
  * @param  NbrOfSector:连续写N个Sector
  * @return 返回操作的状态
  */
uint8 ceTfCard_tfWriteMultiBlock(uint32 sector, uint8 *buffer, uint32 NbrOfSector)
{
    uint8 readVal;
    register uint16 i;
    register uint32 n;
    uint32 retry;

    /* if ver = SD2.0 HC, sector need <<9 */
    if(ceTfCard_cardInfo.CardType != CE_TF_CARD_TYPE_SDV2HC)
    {
        sector = sector<<9;
    }

    /* Send command ACMD23 berfore multi write if is not a MMC card */
    if(ceTfCard_cardInfo.CardType != CE_TF_CARD_TYPE_MMC)
    {
        ceTfCrad_tfSendCommand(CE_TF_CARD_A_CMD_23, NbrOfSector, 0x00);
    }

    /* Send CMD25 : Write nulti block command	*/
    readVal = ceTfCrad_tfSendCommand(CE_TF_CARD_CMD_25, sector, 0);

    if(readVal != 0x00)
    {
        return 1;
    }

    /* Card enable, Prepare to write */
    ceSpiMasterOp.resetSpiMasterNSSBit(&ceSpiMaster);//片选端置低，使能SD卡
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
    //ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
    //ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);

    for(n=0; n<NbrOfSector; n++)
    {
        /* Start multi block write token: 0xFC */
        ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFC);

        for(i=0; i<CE_TF_CARD_BLOCK_SIZE; i++)
        {
            ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, *buffer++);
        }

        /* 2Bytes dummy CRC */
        ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
        ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);

        /* MSD card accept the data */
        readVal = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);
        if((readVal&0x1F) != 0x05)
        {
            ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
            return 2;
        }

        /* Wait all the data programm finished	*/
        retry = 0;
        while(ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF) != 0xFF)
        {
            /* Timeout return */
            if(retry++ == 0x40000)
            {
                ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
                return 3;
            }
        }
    }

    /* Send end of transmit token: 0xFD */
    readVal = ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFD);
    if(readVal == 0x00)
    {
        return 4;
    }

    /* Wait all the data programm finished */
    retry = 0;
    while(ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF) != 0xFF)
    {
        /* Timeout return */
        if(retry++ == 0x40000)
        {
            ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
            return 5;
        }
    }

    /* chip disable and dummy byte */
    ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//片选端置高，失能SD卡
    ceSpiMasterOp.writeReadSpiMasterByte(&ceSpiMaster, 0xFF);

    return 0;
}

/**
  * @brief  CeTfCard模块初始化
  * @param  ceTfCard:CeTfCard属性对象
  * @param  ceSpi:CeTfCard模块使用的Spi资源号
  * @param  ceResourceGpio:CeTfCard模块使用的Gpio资源号
  * @return 系统状态码
  */
CE_STATUS ceTfCard_initial(CeTfCard* ceTfCard, CE_RESOURCE ceSPi, CE_RESOURCE ceResourceGpio)
{
    ceSpiMaster.ceResource = ceSPi;
    ceSpiMaster.ceSpiMasterSpeed = CE_SPI_MASTER_SPEED_10MBPS;
    ceSpiMasterOp.initial(&ceSpiMaster);
    ceSpiMasterOp.start(&ceSpiMaster);
    ceSpiMasterOp.setSpiMasterNSSBit(&ceSpiMaster);//使能TfCard

    ceGpio.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpio.ceResource = ceResourceGpio;
    ceGpioOp.initial(&ceGpio);//gd，检测是否插入Tf卡

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取是否插入TfCard
  * @param  ceTfCard:CeTfCard属性对象
  * @return 存在返回 CE_STATUS_SUCCESS，不存在返回 CE_STATUS_FAILE
  */
CE_STATUS ceTfCard_getExists(CeTfCard* ceTfCard)
{
    if (ceGpioOp.getGpioBit(&ceGpio) == 0x01)
    {
        return CE_STATUS_FAILE;
    }
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  获取容量
  * @param  ceTfCard:CeTfCard属性对象
  * @return 返回容量大小，单位KB
  */
uint32 ceTfCard_getCapacity(CeTfCard* ceTfCard)
{
    ceTfCard_tfGetCardInfo(&ceTfCard_cardInfo);
    return (uint32)(ceTfCard_cardInfo.Capacity / 1024);
}

/**
  * @brief  获取总空间
  * @param  ceTfCard:CeTfCard属性对象
  * @param  drive:逻辑驱动器号
  * @return 返回总空间大小，单位KB
  */
uint32 ceTfCard_getTotalSpace(CeTfCard* ceTfCard, uint8 drive)
{
    FATFS fatfs;
    FATFS* pfatfs;
    DWORD fre_clust = 0;
    FRESULT result;
    char path[] = { "0:" };
    ceSystemOp.sprintf(path, "%d:", drive);
    result = f_getfree(path, &fre_clust, &pfatfs);  /* 必须是根目录，选择磁盘0 */
    if (result == FR_NOT_ENABLED)
    {
        result = f_mount(drive, &fatfs);
        result = f_getfree(path, &fre_clust, &pfatfs);  /* 必须是根目录，选择磁盘0 */
        result = f_mount(drive, CE_NULL);
    }

    if (fre_clust != 0)
    {
        return (uint32)((pfatfs->n_fatent - 2) * pfatfs->csize ) / 2;
    }
    return fre_clust;
}

/**
  * @brief  获取可用空间
  * @param  ceTfCard:CeTfCard属性对象
  * @param  drive:逻辑驱动器号
  * @return 返回可用空间大小，单位KB
  */
uint32 ceTfCard_getAvailableSpace(CeTfCard* ceTfCard, uint8 drive)
{
    FATFS fatfs;
    FATFS* pfatfs;
    DWORD fre_clust = 0;
    FRESULT result;
    char path[] = { "0:" };
    ceSystemOp.sprintf(path, "%d:", drive);
    result = f_getfree(path, &fre_clust, &pfatfs);  /* 必须是根目录，选择磁盘0 */
    if (result == FR_NOT_ENABLED)
    {
        result = f_mount(drive, &fatfs);
        result = f_getfree(path, &fre_clust, &pfatfs);  /* 必须是根目录，选择磁盘0 */
        result = f_mount(drive, CE_NULL);
    }

    if (fre_clust != 0)
    {
        return (uint32)(fre_clust * pfatfs->csize) / 2;
    }
    return fre_clust;
}

/**
  * @brief  测试一个文件是否到达文件末尾。
  * @param  fileObject:指向打开文件对象结构的指针。
  * @return 如果读/写指针到达文件末尾，f_eof 函数返回一个非零值；否则返回0。
  */
BYTE ceTfCard_f_eof(FIL* fileObject)
{
    return (((fileObject)->fptr == (fileObject)->fsize) ? 1 : 0);
}

/**
  * @brief  测试文件是否出错。
  * @param  fileObject:指向打开文件对象结构的指针。
  * @return 如果有错误返回非零值；否则返回 0。
  */
BYTE ceTfCard_f_error(FIL* fileObject)
{
    return (((fileObject)->flag & FA__ERROR) ? 1 : 0);
}

/**
  * @brief  获取一个文件的当前读/写指针。
  * @param  fileObject:指向打开文件对象结构的指针。
  * @return 返回文件的当前读/写指针。
  */
DWORD ceTfCard_f_tell(FIL* fileObject)
{
    return ((fileObject)->fptr);
}

/**
  * @brief   获取一个文件的大小。
  * @param  fileObject:指向打开文件对象结构的指针。
  * @return 返回文件的当前读/写指针。
  */
DWORD ceTfCard_f_size(FIL* fileObject)
{
    return ((fileObject)->fsize);
}

/**
* @brief    CeTfCard模块操作对象定义
*/
const CeTfCardOpBase ceTfCardOp = {ceTfCard_initial, ceTfCard_getExists, ceTfCard_getCapacity, ceTfCard_getTotalSpace, ceTfCard_getAvailableSpace,
                                    f_mount, f_open, f_read, f_lseek, f_close, f_opendir, f_readdir, f_stat, f_write, f_getfree,
                                    f_truncate, f_sync, f_unlink, f_mkdir, f_chmod, f_utime, f_rename,
#if _FS_RPATH >= 1  /*!< 以下函数跟FatFs文件系统开启的功能有关，如有改动请保持.h和.c完全一致*/
                                    f_chdrive, f_chdir,
#if _FS_RPATH >= 2
                                    f_getcwd,
#endif //_FS_RPATH >= 2
#endif //_FS_RPATH >= 1
#if _USE_FORWARD && _FS_TINY
                                    f_forward,
#endif //_USE_FORWARD && _FS_TINY
#if _USE_MKFS && !_FS_READONLY
                                    f_mkfs,
#if _MULTI_PARTITION == 2
                                    f_fdisk,
#endif //_MULTI_PARTITION == 2
#endif //_USE_MKFS && !_FS_READONLY
#if _USE_STRFUNC
                                    f_putc, f_puts, f_printf, f_gets,
#endif //_USE_STRFUNC
                                    /*!< 以下为FatFs文件管理系统提供的接口，由于FatFs内是宏定义实现，所以对其进行了封装*/
                                    ceTfCard_f_eof, ceTfCard_f_error, ceTfCard_f_tell, ceTfCard_f_size
                                    };

#ifdef __cplusplus
 }
#endif //__cplusplus

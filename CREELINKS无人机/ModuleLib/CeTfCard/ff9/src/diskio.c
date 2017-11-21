
#define __USE_TF_CARD__ //使用TfCrad，不定义则不会调用CeTfCard中的任何IO操作

#ifdef __USE_TF_CARD__
#include "../CeTfCard/CeTfCard.h"
extern uint8        ceTfCard_status;
extern CeSpiMaster  ceSpiMaster;
extern CeGpio       ceGpio;
extern CeTfCard_CardInfo ceTfCard_cardInfo;
#endif

#include "./diskio.h"

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
    int status = 0;
    status = status;
    switch (drv)
    {
    case 0 :
#ifdef __CE_TF_CARD_H__
        status = ceTfCard_tfInitial();
        if(status == CE_TF_CARD_INITIAL_SUCCESS)
        {
            return RES_OK;
        }
        else if(status == CE_TF_CARD_INITIAL_FAILE)
        {
            return STA_NOINIT;
        }
        else if(status == CE_TF_CARD_NO_DISK)
        {
            return STA_NODISK;
        }
        else if(status == CE_TF_CARD_PROTECT)
        {
            return STA_PROTECT;
        }
        else
        {
            return STA_NOINIT;
        }
#else
        return STA_NOINIT;
#endif

    case 1 :
        return RES_OK;
    case 2 :
        return RES_OK;
    case 3 :
        return RES_OK;
    default:
        return STA_NOINIT;
    }
}

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
    switch (drv)
    {
    case 0 :
        return RES_OK;
    case 1 :
        return RES_OK;
    case 2 :
        return RES_OK;
    default:
        return STA_NOINIT;
    }
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
    int Status;
    if( !count )
    {
        return RES_PARERR;  /* count不能等于0，否则返回参数错误 */
    }
    switch (drv)
    {
    case 0:
        if(count==1)            /* 1个sector的读操作 */
        {
#ifdef __CE_TF_CARD_H__
            Status =  ceTfCard_tfReadSingleBlock(sector, buff);
#else
            Status = RES_ERROR;
#endif

            if(Status == 0)
            {
                return RES_OK;
            }else
            {
                return RES_ERROR;
            }
        }
        else                    /* 多个sector的读操作 */
        {
#ifdef __CE_TF_CARD_H__
            Status = ceTfCard_tfReadMultiBlock(sector, buff ,count);
#else
            Status = RES_ERROR;
#endif
            if(Status == 0)
            {
                return RES_OK;
            }else
            {
                return RES_ERROR;
            }
        }
    case 1:
        if(count==1)            /* 1个sector的读操作 */
        {
            return RES_OK;
        }
        else                    /* 多个sector的读操作 */
        {
            return RES_OK;
        }

    default:
        return RES_ERROR;
    }
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	        /* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
    int Status;
    if( !count )
    {
        return RES_PARERR;  /* count不能等于0，否则返回参数错误 */
    }
    switch (drv)
    {
    case 0:
        if(count==1)            /* 1个sector的写操作 */
        {
#ifdef __CE_TF_CARD_H__
            Status = ceTfCard_tfWriteSingleBlock(sector, (uint8_t *)(&buff[0]));
#else
            Status = RES_ERROR;
#endif
            if(Status == 0)
            {
                return RES_OK;
            }else
            {
                return RES_ERROR;
            }
        }
        else                    /* 多个sector的写操作 */
        {
#ifdef __CE_TF_CARD_H__
            Status = ceTfCard_tfWriteMultiBlock(sector, (uint8_t *)(&buff[0]) , count);
#else
            Status = RES_ERROR;
#endif
            if(Status == 0)
            {
                return RES_OK;
            }else
            {
                return RES_ERROR;
            }
        }
    case 1:
        if(count==1)            /* 1个sector的写操作 */
        {
            return RES_OK;
        }
        else                    /* 多个sector的写操作 */
        {
            return RES_OK;
        }

    default:return RES_ERROR;
    }
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
    if (drv==0)
    {
#ifdef __CE_TF_CARD_H__
        ceTfCard_tfGetCardInfo(&ceTfCard_cardInfo);
#endif
        switch (ctrl)
        {
        case CTRL_SYNC :
            return RES_OK;
        case GET_SECTOR_COUNT :
#ifdef __CE_TF_CARD_H__
            *(DWORD*)buff = ceTfCard_cardInfo.Capacity / ceTfCard_cardInfo.BlockSize;
            return RES_OK;
#else
            return RES_ERROR;
#endif
        case GET_BLOCK_SIZE :
#ifdef __CE_TF_CARD_H__
            *(WORD*)buff = ceTfCard_cardInfo.BlockSize;
            return RES_OK;
#else
            return RES_ERROR;
#endif
        case CTRL_POWER :
            break;
        case CTRL_LOCK :
            break;
        case CTRL_EJECT :
            break;
            /* MMC/SDC command */
        case MMC_GET_TYPE :
            break;
        case MMC_GET_CSD :
            break;
        case MMC_GET_CID :
            break;
        case MMC_GET_OCR :
            break;
        case MMC_GET_SDSTAT :
            break;
        }
    }else if(drv==1){
        switch (ctrl)
        {
        case CTRL_SYNC :
            return RES_OK;
        case GET_SECTOR_COUNT :
            return RES_OK;
        case GET_SECTOR_SIZE :
            return RES_OK;
        case GET_BLOCK_SIZE :
            return RES_OK;
        case CTRL_POWER :
            break;
        case CTRL_LOCK :
            break;
        case CTRL_EJECT :
            break;
            /* MMC/SDC command */
        case MMC_GET_TYPE :
            break;
        case MMC_GET_CSD :
            break;
        case MMC_GET_CID :
            break;
        case MMC_GET_OCR :
            break;
        case MMC_GET_SDSTAT :
            break;
        }
    }
    else{
        return RES_PARERR;
    }
    return RES_PARERR;
}

/* 得到文件Calendar格式的建立日期,是DWORD get_fattime (void) 逆变换 */
/*-----------------------------------------------------------------------*/
/* User defined function to give a current time to fatfs module          */
/* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
/* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
DWORD get_fattime (void)
{
    return 0;
}



/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

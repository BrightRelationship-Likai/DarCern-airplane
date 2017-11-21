/*-----------------------------------------------------------------------
/  Low level disk interface modlue include file
/-----------------------------------------------------------------------*/

#ifndef _DISKIO

#define _READONLY	0	/* 1: Remove write functions */
#define _USE_IOCTL	1	/* 1: Use disk_ioctl fucntion */

#include "integer.h"


/* Status of Disk Functions */
typedef BYTE	DSTATUS;

/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */

int assign_drives (int, int);
DSTATUS disk_initialize (BYTE);
DSTATUS disk_status (BYTE);
DRESULT disk_read (BYTE, BYTE*, DWORD, BYTE);
#if	_READONLY == 0
DRESULT disk_write (BYTE, const BYTE*, DWORD, BYTE);
#endif
DRESULT disk_ioctl (BYTE, BYTE, void*);



/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */


/* Command code for disk_ioctrl fucntion */

/* Generic command (defined for FatFs) */
#define CTRL_SYNC			0	/* Flush disk cache (for write functions) */
#define GET_SECTOR_COUNT	1	/* Get media size (for only f_mkfs()) */
#define GET_SECTOR_SIZE		2	/* Get sector size (for multiple sector size (_MAX_SS >= 1024)) */
#define GET_BLOCK_SIZE		3	/* Get erase block size (for only f_mkfs()) */
#define CTRL_ERASE_SECTOR	4	/* Force erased a block of sectors (for only _USE_ERASE) */

/* Generic command */
#define CTRL_POWER			5	/* Get/Set power status */
#define CTRL_LOCK			6	/* Lock/Unlock media removal */
#define CTRL_EJECT			7	/* Eject media */

/* MMC/SDC specific ioctl command */
#define MMC_GET_TYPE		10	/* Get card type */
#define MMC_GET_CSD			11	/* Get CSD */
#define MMC_GET_CID			12	/* Get CID */
#define MMC_GET_OCR			13	/* Get OCR */
#define MMC_GET_SDSTAT		14	/* Get SD status */

/* ATA/CF specific ioctl command */
#define ATA_GET_REV			20	/* Get F/W revision */
#define ATA_GET_MODEL		21	/* Get model name */
#define ATA_GET_SN			22	/* Get serial number */

/* NAND specific ioctl command */
#define NAND_FORMAT			30	/* Create physical format */


#define _DISKIO



#ifdef __CE_TF_CARD_H__

#define CE_TF_CARD_INITIAL_SUCCESS    (int16)0      /*!< CeTftCradÊ§°Ü*/
#define CE_TF_CARD_INITIAL_FAILE    (int16)-1      /*!< CeTftCradÊ§°Ü*/
#define CE_TF_CARD_NO_DISK          (int16)-2      /*!< CeTftCradÎÞ´ÅÅÌ*/
#define CE_TF_CARD_PROTECT          (int16)-3      /*!< CeTftCradÐ´±£»¤*/

typedef struct               /* Card Specific Data */
{
    vu8  CSDStruct;            /* CSD structure */
    vu8  SysSpecVersion;       /* System specification version */
    vu8  Reserved1;            /* Reserved */
    vu8  TAAC;                 /* Data read access-time 1 */
    vu8  NSAC;                 /* Data read access-time 2 in CLK cycles */
    vu8  MaxBusClkFrec;        /* Max. bus clock frequency */
    vu16 CardComdClasses;      /* Card command classes */
    vu8  RdBlockLen;           /* Max. read data block length */
    vu8  PartBlockRead;        /* Partial blocks for read allowed */
    vu8  WrBlockMisalign;      /* Write block misalignment */
    vu8  RdBlockMisalign;      /* Read block misalignment */
    vu8  DSRImpl;              /* DSR implemented */
    vu8  Reserved2;            /* Reserved */
    vu32 DeviceSize;           /* Device Size */
    vu8  MaxRdCurrentVDDMin;   /* Max. read current @ VDD min */
    vu8  MaxRdCurrentVDDMax;   /* Max. read current @ VDD max */
    vu8  MaxWrCurrentVDDMin;   /* Max. write current @ VDD min */
    vu8  MaxWrCurrentVDDMax;   /* Max. write current @ VDD max */
    vu8  DeviceSizeMul;        /* Device size multiplier */
    vu8  EraseGrSize;          /* Erase group size */
    vu8  EraseGrMul;           /* Erase group size multiplier */
    vu8  WrProtectGrSize;      /* Write protect group size */
    vu8  WrProtectGrEnable;    /* Write protect group enable */
    vu8  ManDeflECC;           /* Manufacturer default ECC */
    vu8  WrSpeedFact;          /* Write speed factor */
    vu8  MaxWrBlockLen;        /* Max. write data block length */
    vu8  WriteBlockPaPartial;  /* Partial blocks for write allowed */
    vu8  Reserved3;            /* Reserded */
    vu8  ContentProtectAppli;  /* Content protection application */
    vu8  FileFormatGrouop;     /* File format group */
    vu8  CopyFlag;             /* Copy flag (OTP) */
    vu8  PermWrProtect;        /* Permanent write protection */
    vu8  TempWrProtect;        /* Temporary write protection */
    vu8  FileFormat;           /* File Format */
    vu8  ECC;                  /* ECC code */
    vu8  CSD_CRC;              /* CSD CRC */
    vu8  Reserved4;            /* always 1*/
}
MSD_CSD;

typedef struct				 /*Card Identification Data*/
{
    vu8  ManufacturerID;       /* ManufacturerID */
    vu16 OEM_AppliID;          /* OEM/Application ID */
    vu32 ProdName1;            /* Product Name part1 */
    vu8  ProdName2;            /* Product Name part2*/
    vu8  ProdRev;              /* Product Revision */
    vu32 ProdSN;               /* Product Serial Number */
    vu8  Reserved1;            /* Reserved1 */
    vu16 ManufactDate;         /* Manufacturing Date */
    vu8  CID_CRC;              /* CID CRC */
    vu8  Reserved2;            /* always 1 */
}
MSD_CID;

typedef struct
{
    MSD_CSD CSD;
    MSD_CID CID;
    uint64  Capacity;              /* Card Capacity */
    uint32  BlockSize;             /* Card Block Size */
    uint16  RCA;
    uint8   CardType;
    //uint32  SpaceTotal;            /* Total space size in file system */
    //uint32  SpaceFree;      	   /* Free space size in file system */
}
CeTfCard_CardInfo, *PCeTfCard_CardInfo;

/* Private variables ---------------------------------------------------------*/

int16 ceTfCard_tfInitial(void);
uint8 ceTfCard_tfGetCardInfo(PCeTfCard_CardInfo ceTfCard_CardInfo);
uint8 ceTfCard_tfReadSingleBlock(uint32 sector, uint8 *buffer);
uint8 ceTfCard_tfReadMultiBlock(uint32 sector, uint8 *buffer, uint32 NbrOfSector);
uint8 ceTfCard_tfWriteSingleBlock(uint32 sector, uint8 *buffer);
uint8 ceTfCard_tfWriteMultiBlock(uint32 sector, uint8 *buffer, uint32 NbrOfSector);

#endif //__CE_TF_CARD_H__

#endif //_DISKIO

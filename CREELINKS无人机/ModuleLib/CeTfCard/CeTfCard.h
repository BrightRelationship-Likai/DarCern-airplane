/**
  ******************************************************************************
  * @file    CeTfCard.h
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
#ifndef __CE_TF_CARD_H__
#define __CE_TF_CARD_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TF_CARD_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_TF_CARD_NEED_CREELINKS_VERSION__ 18                            /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_TF_CARD_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeTfCard.h需要高于18以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
#include "./ff9/src/diskio.h"                               /*!< 引用FatFs文件系统Io操作的头文件，在此头文件中存放了CeTfCard操作有关的函数声明及宏定义等*/
#include "./ff9/src/ff.h"                                   /*!< 引用FatFs文件系统功能操作的头文件*/
/*
 *CeTfCard属性对像
 */
typedef struct
{
    uint8 backup;                                           /*!< 保留*/
}CeTfCard;

/*
 *CeTfCard操作对像
 */
typedef struct
{
    CE_STATUS       (*initial)(CeTfCard* ceTfCard, CE_RESOURCE ceSpi, CE_RESOURCE ceResourceGpio);/*!<
                                                                 @brief CeTfCard模块初始化
                                                                 @param ceTfCard:CeTfCard属性对象指针
                                                                 @param ceSpi:CeTfCard模块使用的SPI资源号
                                                                 @param ceSpi:CeTfCard模块使用的Gpio资源号*/

    CE_STATUS       (*getExists)(CeTfCard* ceTfCard);       /*!< @brief 获取是否插入TfCard
                                                                 @param ceTfCard:CeTfCard属性对象指针
                                                                 @return 存在返回 CE_STATUS_SUCCESS，不存在返回 CE_STATUS_FAILE*/

    uint32          (*getCapacity)(CeTfCard* ceTfCard);     /*!< @brief 获取容量
                                                                 @param ceTfCard:CeTfCard属性对象指针
                                                                 @return 返回容量大小，单位KB*/

    uint32          (*getTotalSpace)(CeTfCard* ceTfCard, uint8 drive);/*!<
                                                                 @brief 获取总空间
                                                                 @param ceTfCard:CeTfCard属性对象指针
                                                                 @param drive:逻辑驱动器号
                                                                 @return 返回总空间大小，单位KB*/

    uint32          (*getAvailableSpace)(CeTfCard* ceTfCard, uint8 drive);/*!<
                                                                 @brief 获取可用空间
                                                                 @param ceTfCard:CeTfCard属性对象指针
                                                                 @param drive:逻辑驱动器号
                                                                 @return 返回可用空间大小，单位KB*/

    /*!< 以下为FatFs文件管理系统提供的接口，没有进行任何封装，直接进行指针调用*/

    FRESULT         (*f_mount)(BYTE driver, FATFS* fileSystemObject);/*!<
                                                                 @brief 在FatFs 模块上注册/注销一个工作区(文件系统对象)，在使用任何其他文件操作函数之前们必须使用该函数为每个卷注册一个工作区
                                                                 @param driver:注册/注销工作区的逻辑驱动器号(0-9)
                                                                 @param fileSystemObject:工作区(文件系统对象)指针，注销时传入 CE_NULL即可
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_open)(FIL* fileObject, const TCHAR* fileName, BYTE modeFlags);/*!<
                                                                 @brief 创建/打开一个用于访问文件的文件对象
                                                                 @param fileObject:将被创建的文件对象结构的指针
                                                                 @param fileName:'\0'结尾的字符串指针，该字符串指定了将被创建或打开的文件名
                                                                 @param modeFlags:指定文件的访问类型和打开方法。它是由下列标志的一个组合指定的。
                                                                                    FA_READ:指定读访问对象。可以从文件中读取数据。与 FA_WRITE 结合可以进行读写访问。
                                                                                    FA_WRITE:指定写访问对象。可以向文件中写入数据。与 FA_READ 结合可以进行读写访问。
                                                                                    FA_OPEN_EXISTING:打开文件。如果文件不存在，则打开失败。(默认)
                                                                                    FA_OPEN_ALWAYS:如果文件存在，则打开；否则，创建一个新文件。
                                                                                    FA_CREATE_NEW:创建一个新文件。如果文件已存在，则创建失败。
                                                                                    FA_CREATE_ALWAYS:创建一个新文件。如果文件已存在，则它将被截断并覆盖。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_read)(FIL* fileObject, void* buffer, UINT byteToRead, UINT* byteRead);/*!<
                                                                 @brief 从一个文件读取数据
                                                                 @param fileObject:指向将被读取的已打开的文件对象结构的指针。
                                                                 @param buffer:指向存储读取数据的缓冲区的指针。
                                                                 @param byteToRead:要读取的字节数，UINT 范围内。
                                                                 @param byteRead:指向返回已读取字节数的UINT 变量的指针。在调用该函数后，无论结果如何，数值都是有效的。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_lseek)(FIL* fileObject, DWORD offset);/*!<
                                                                 @brief 移动一个打开的文件对象的文件读/写指针。也可以被用来扩展文件大小(簇预分配)。
                                                                 @param fileObject:打开的文件对象的指针
                                                                 @param offset:相对于文件起始处的字节数。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_close)(FIL* fileObject);            /*!< @brief 关闭一个打开的文件
                                                                 @param fileObject:指向将被关闭的已打开的文件对象结构的指针。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_opendir)(DIR* dirObject, const TCHAR* dirName);/*!<
                                                                 @brief 打开一个目录
                                                                 @param dirObject:待创建的空白目录对象的指针。
                                                                 @param dirName:'\0'结尾的字符串指针，该字符串指定了将被打开的目录名。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_readdir) (DIR* dirObject, FILINFO* fileInfo);/*!<
                                                                 @brief 读取目录项
                                                                 @param dirObject:打开的目录对象的指针。
                                                                 @param fileInfo:存储已读取项的文件信息结构指针。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_stat)(const TCHAR* fileName, FILINFO* fileInfo);/*!<
                                                                 @brief 获取文件状态
                                                                 @param fileName:'\0'结尾的字符串指针，该字符串指定了待获取其信息的文件或目录。
                                                                 @param fileInfo:存储信息的空白FILINFO 结构的指针。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_write)(FIL* fileObject, const void* buffer, UINT byteToRead, UINT* byteRead);/*!<
                                                                 @brief 写入数据到一个文件
                                                                 @param fileObject:指向将被写入的已打开的文件对象结构的指针。
                                                                 @param buffer:指向存储写入数据的缓冲区的指针。
                                                                 @param byteToRead:要写入的字节数，UINT 范围内。
                                                                 @param byteRead:指向返回已写入字节数的UINT 变量的指针。在调用该函数后，无论结果如何，数值都是有效的。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_getfree)(const TCHAR* path, DWORD* clusters, FATFS** fileSystemObject);/*!<
                                                                 @brief 获取空闲簇的数目
                                                                 @param path:'\0'结尾的字符串指针，该字符串指定了逻辑驱动器的目录。
                                                                 @param clusters:存储空闲簇数目的DWORD 变量的指针。
                                                                 @param fileSystemObject:相应文件系统对象指针的指针。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_truncate)(FIL* fileObject);         /*!< @brief 截断文件大小
                                                                 @param fileObject:待截断的打开的文件对象的指针。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_sync)(FIL* fileObject);             /*!< @brief 冲洗一个写文件的缓存信息
                                                                 @param fileObject:待冲洗的打开的文件对象的指针。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_unlink)(const TCHAR* fileName);     /*!< @brief 移除一个对象
                                                                 @param fileName:'\0'结尾的字符串指针，该字符串指定了一个待移除的对象
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_mkdir)(const TCHAR* dirName);       /*!< @brief 创建一个目录
                                                                 @param dirName:'\0'结尾的字符串指针，该字符串指定了待创建的目录名。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_chmod)(const TCHAR* fileName, BYTE attribute, BYTE attributeMask);/*!<
                                                                 @brief 修改一个文件或目录的属性。
                                                                 @param fileName:'\0'结尾的字符串指针，该字符串指定了一个待被修改属性的文件或目录。
                                                                 @param attribute:待被设置的属性标志，可以是下列标志的一个或任意组合。指定的标志被设置，其他的被清除。
                                                                                     AM_RDO 只读、AM_ARC 存档、AM_SYS 系统、AM_HID 隐藏
                                                                 @param attributeMask:属性掩码，指定修改哪个属性。指定的属性被设置或清除。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_utime)(const TCHAR*, const FILINFO* timeDate);/*!<
                                                                 @brief 函数修改一个文件或目录的时间戳。
                                                                 @param fileName:'\0'结尾的字符串的指针，该字符串指定了一个待修改时间戳的文件或目录。
                                                                 @param timeDate:文件信息结构指针，其中成员ftime 和fdata 存储了一个待被设置的的时间戳。不关心任何其他成员。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_rename)(const TCHAR* oldName, const TCHAR* newName);/*!<
                                                                 @brief 重命名一个对象(文件或者目录)。
                                                                 @param oldName:'\0'结尾的字符串的指针，该字符串指定了待被重命名的原对象名。
                                                                 @param newName:'\0'结尾的字符串的指针，该字符串指定了重命名后的新对象名，不能包含驱动器号。
                                                                 @return 返回函数执行的状态*/

#if _FS_RPATH >= 1  /*!< 以下函数跟FatFs文件系统开启的功能有关，如有改动请保持.h和.c完全一致*/
    FRESULT         (*f_chdrive)(BYTE drive);               /*!< @brief 改变一个驱动器的当前目录。
                                                                 @param drive: 指定将被设置为当前驱动器的逻辑驱动器号。
                                                                 @return 返回函数执行的状态*/

    FRESULT         (*f_chdir)(const TCHAR* path);          /*!< @brief 改变一个驱动器的当前目录。
                                                                 @param path:'\0'结尾的字符串的指针，该字符串指定了将要进去的目录。
                                                                 @return 返回函数执行的状态*/

#if _FS_RPATH >= 2
    FRESULT         (*f_getcwd)(TCHAR* buffer, UINT bufferLen);/*!<
                                                                 @brief 恢复当前目录。
                                                                 @param buffer:指向接收当前目录字符串的缓冲区
                                                                 @param bufferLen:缓冲区的大小，单位为TCHAR
                                                                 @return 返回函数执行的状态*/
#endif //_FS_RPATH >= 2
#endif //_FS_RPATH >= 1

#if _USE_FORWARD && _FS_TINY
    FRESULT         (*f_forward)(FIL* fileObject, UINT(*func)(const BYTE* buffer, UINT bufferLen), UINT byteToFwd, UINT* byteFwd);/*!<
                                                                 @brief 读取文件数据并将其转发到数据流设备。
                                                                 @param fileObject:打开的文件对象的指针。
                                                                 @param func:用户定义的数据流函数的指针。详情参考示例代码。
                                                                                buffer:将被发送的数据块的指针
                                                                                bufferLen:>0: 传输调用(将被发送的字节数)。0: 检测调用
                                                                 @param byteToFwd:要转发的字节数，UINT 范围内。
                                                                 @param byteFwd:返回已转发的字节数的UINT 变量的指针。
                                                                 @return 返回函数执行的状态*/
#endif //_USE_FORWARD && _FS_TINY

#if _USE_MKFS && !_FS_READONLY
    FRESULT         (*f_mkfs)(BYTE drive, BYTE partitioningRule, UINT allocSize);/*!<
                                                                 @brief 在驱动器上创建一个文件系统
                                                                 @param drive:待格式化的逻辑驱动器号(0-9)。
                                                                 @param partitioningRule:当给定0 时，首先在驱动器上的第一个扇区创建一个分区表，然后文件系统被创建在分区上。
                                                                                            这被称为FDISK格式化，用于硬盘和存储卡。当给定1 时，文件系统从第一个扇区开始创建，而没有分区表。
                                                                                            这被称为超级软盘(SFD)格式化，用于软盘和可移动磁盘。
                                                                 @param allocSize 指定每簇中以字节为单位的分配单元大小。数值必须是0 或从512 到32K 之间2 的幂。当指定0 时，簇大小取决于卷大小。
                                                                 @return 返回函数执行的状态*/
#if _MULTI_PARTITION == 2
    FRESULT         (*f_fdisk)(BYTE drive, const DWORD[] partitions, void* work);/*!<
                                                                 @brief 划分一个物理驱动器。
                                                                 @param drive:指定要划分的物理驱动器
                                                                 @param partitions[]:分区映象表，必须有四个项目。
                                                                 @param work:指向函数工作区的指针。其大小必须至少为_MAX_SS 字节。
                                                                 @return 返回函数执行的状态*/
#endif //_MULTI_PARTITION == 2
#endif //_USE_MKFS && !_FS_READONLY

#if _USE_STRFUNC
    TCHAR           (*f_putc)(TCHAR chr, FIL* fileObject);/*!<
                                                                 @brief 向文件中写入一个字符。
                                                                 @param chr:待写入的字符。
                                                                 @param fileObject:打开的文件对象结构的指针。
                                                                 @return 当字符被成功地写入后，函数返回该字符。由于磁盘满或任何错误而导致函数失败，将返回 EOF。*/

    INT             (*f_puts)(const TCHAR* str, FIL* fileObject);/*!<
                                                                 @brief 向文件中写入一个字符串
                                                                 @param str:待写入的'\0'结尾的字符串的指针。'\0'字符不会被写入。
                                                                 @param fileObject:打开的文件对象结构的指针。
                                                                 @return 函数成功后，将返回写入的字符数。由于磁盘满或任何错误而导致函数失败，将返回 EOF。*/

    INT             (*f_printf)(FIL* fileObject, const TCHAR* format, ...);/*!<
                                                                 @brief 向文件中写入一个格式化字符串。
                                                                 @param fileObject:已打开的文件对象结构的指针。
                                                                 @param format:'\0'结尾的格式化字符串指针。
                                                                 @param ...:可选参数
                                                                 @return 函数成功后，将返回写入的字符数。由于磁盘满或任何错误而导致函数失败，将返回 EOF。*/

    TCHAR*          (*f_gets)(TCHAR* str, int size, FIL* fileObject);/*!<
                                                                 @brief 文件中读取一个字符串。
                                                                 @param str:存储读取字符串的读缓冲区指针。
                                                                 @param size:读缓冲区大小。
                                                                 @param fileObject:打开的文件对象结构指针。
                                                                 @return 函数成功后，str将被返回。*/

#endif //_USE_STRFUNC

    /*!< 以下为FatFs文件管理系统提供的接口，由于FatFs内是宏定义实现，所以对其进行了封装*/
    BYTE           (*f_eof)(FIL* fileObject);
                                                            /*!< @brief 测试一个文件是否到达文件末尾。
                                                                 @param fileObject:指向打开文件对象结构的指针。
                                                                 @return 如果读/写指针到达文件末尾，f_eof 函数返回一个非零值；否则返回0。*/
    BYTE           (*f_error)(FIL* fileObject);
                                                            /*!< @brief 测试文件是否出错。
                                                                 @param fileObject:指向打开文件对象结构的指针。
                                                                 @return 如果有错误返回非零值；否则返回 0。*/
    DWORD          (*f_tell)(FIL* fileObject);
                                                            /*!< @brief 获取一个文件的当前读/写指针。
                                                                 @param fileObject:指向打开文件对象结构的指针。
                                                                 @return 返回文件的当前读/写指针。*/
    DWORD           (*f_size)(FIL* fileObject);
                                                            /*!< @brief 获取一个文件的大小。
                                                                 @param fileObject:指向打开文件对象结构的指针。
                                                                 @return 返回文件的大小，单位为字节。*/
}CeTfCardOpBase;
/*
 *CeTfCard操作对象实例
 */
extern const CeTfCardOpBase ceTfCardOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_TF_CARD_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_TF_CARD_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境),基于ELinkSTM核心板
  @function CeTfCard读写文件，遍历目录，获取容量等测试(可使用CeTft系列任意屏幕进行调试输出，只需改动下面的宏定义即可。使用宏替换使代码改动降到最小)
******************************************************************************
#include "Creelinks.h"
#include "CeTfCard/CeTfCard.h"  //编译时请将CeTfCard\ff9\src目录下的diskio.c和ff.c加入到工程中，不然链接时会报错
#include "CeTft320Nt.h"

#define XXX()            ceTft320Nt
#define CE_TFTXXX( _x_ ) ceTft320Nt##_x_
#define TFTXXX()         CeTft320Nt
TFTXXX() CE_TFTXXX(;)

CeTfCard ceTfCard;
FATFS fatFs;          //Work area (file system object) for logical drive
FIL fileObject;       //file objects
FRESULT result;
char filePath[128] = { 0 };
char buffer[4096]  = { 0 };
uint32 bufferByte = 0;

void appendString(const char* msg)
{
    CE_TFTXXX(Op.appendString(msg));
}

// **
//  * @brief  搜索根目录下所有文件
//  * @param  path:指定搜索的根目录
//  * @return 返回FRESULT
//  *
FRESULT scan_files(char* path)                           //Start node to be scanned (also used as work area)
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
    char* fn;                                             //This function is assuming non-Unicode cfg.
#if _USE_LFN
    static char lfn[_MAX_LFN + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif
    res = ceTfCardOp.f_opendir(&dir, path);                //Open the directory
    if (res == FR_OK)
    {
        i = ceStringOp.strlen(path);
        for (; ;)
        {
            res = ceTfCardOp.f_readdir(&dir, &fno);        //Read a directory item
            if (res != FR_OK || fno.fname[0] == 0)
            {
                break;                                     //Break on error or end of dir
            }
            if (fno.fname[0] == '.')
            {
                continue;                                  //Ignore dot entry
            }
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if (fno.fattrib & AM_DIR)
            {
                ceSystemOp.sprintf(&path[i], "/%s", fn);    //It is a directory
                ceSystemOp.printf("CeTfCard scan file: %s\n\r", path);
                res = scan_files(path);
                if (res != FR_OK)
                {
                    break;
                }
                path[i] = 0;
            }
            else
            {
                ceSystemOp.printf("CeTfCard scan file: %s/%s\n\r", path, fn);//It is a file.
            }
        }
    }
    else
    {
        ceSystemOp.printf("CeTfCard scan files error: %d\n\r", res);
    }

    return res;
}

int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceSystemOp.initialDebug(R14Uart);           //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作

    CE_TFTXXX(Op.initial(&(XXX()), R26L36));
    CE_TFTXXX(Op.setOn());

    ceSystemOp.registerAppendString(appendString);
    ceSystemOp.printf("ELinkSTM build Data: %s Time: %s.\n", __DATE__, __TIME__);

    ceTfCardOp.initial(&ceTfCard, R7Spi, R5ACGPW);

    while (1)
    {
        ceSystemOp.mainTask();                  //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作

        if (ceTfCardOp.getExists(&ceTfCard) == CE_STATUS_SUCCESS)//检测是否存在
        {
            ceSystemOp.delayMs(3000);

            ceSystemOp.sprintf(filePath, "%s", "0:/Darcern.txt");

            //挂载文件系统
            result = ceTfCardOp.f_mount(0, &fatFs);
            if (result != FR_OK)
            {
                ceSystemOp.printf("CeTfCard mount filesystem: %d failed: %d\n\r", 0, result);
            }

            //写文件测试
            ceSystemOp.printf("CeTfCard write file test......\n\r");
            result = ceTfCardOp.f_open(&fileObject, filePath, FA_CREATE_ALWAYS | FA_WRITE);
            if (result != FR_OK)
            {
                ceSystemOp.printf("CeTfCard open file error: %d\n\r", result);
            }
            else
            {
                bufferByte = ceSystemOp.sprintf(buffer, "%s", "北京大信科技有限公司\r\nBeiJing Darcern\r\n");

                result = ceTfCardOp.f_write(&fileObject, buffer, bufferByte, &bufferByte);
                if (result == FR_OK)
                {
                    ceSystemOp.printf("CeTfCard write data ok! %d\n\r", bufferByte);
                }
                else
                {
                    ceSystemOp.printf("CeTfCard write data error: %d\n\r", result);
                }
                ceTfCardOp.f_close(&fileObject);//close file
            }

            //读文件测试
            ceSystemOp.printf("CeTfCard read file test......\n\r");
            result = ceTfCardOp.f_open(&fileObject, filePath, FA_OPEN_ALWAYS | FA_READ);
            if (result != FR_OK)
            {
                ceSystemOp.printf("CeTfCard open file error: %d\n\r", result);
            }
            else
            {
                ceSystemOp.printf("CeTfCard ceTfCardOp.f_open() success .. \r\n");
                result = ceTfCardOp.f_read(&fileObject, buffer, bufferByte, &bufferByte);
                if (result == FR_OK)
                {
                    ceSystemOp.printf("CeTfCard  read data num: %d\n\r", bufferByte);
                    ceSystemOp.printf("%s\n\r", buffer);
                }
                else
                {
                    ceSystemOp.printf("CeTfCard  read file error: %d\n\r", result);
                }
                ceTfCardOp.f_close(&fileObject);  //close file
            }

            //扫描已经存在的文件
            ceSystemOp.printf("\n\rCeTfCard begin scan files path0......\n\r");
            ceSystemOp.sprintf(filePath, "%s", "0:");
            scan_files(filePath);

            ceSystemOp.printf("CeTfCard Capacity: %u\n", ceTfCardOp.getCapacity(&ceTfCard));
            ceSystemOp.printf("CeTfCard SpaceTotal: %u\n", ceTfCardOp.getTotalSpace(&ceTfCard, 0));
            ceSystemOp.printf("CeTfCard SpaceFree: %u\n", ceTfCardOp.getAvailableSpace(&ceTfCard, 0));

            //卸载文件系统
            result = f_mount(0, CE_NULL);
        }
        else
        {
            ceSystemOp.printf("\n\rCeTfCard TfCard not exits......\n\r");
        }

        ceSystemOp.delayMs(3000);
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeTfCard.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTfCardģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)�����FatFs�ļ�ϵͳ���вü��������������޸�ffconf.h�еĺ궨�壬���FatFs�İ汾û�б䶯�������CeTfCrad.h��.c�����κ��޸ģ�
  *2)FatFs�ļ�����ϵͳ�ṩ�Ĺ��ܽӿڣ�ģ����û�н����κη�װ��ֱ�ӽ���ָ�����
  *3).h��.c�е�ĳЩ������FatFs�ļ�ϵͳ�����Ĺ����йأ����иĶ��뱣��.h��.c��ȫһ��
  *4).h��.c��ĳЩ������ff.h���Ǻ궨��ʵ�֣����Զ�������˷�װ��
  *5).h��.c��ĳЩ�����ķ���ֵ���߲���������������ffxx/src/integer.h�����иĶ���ע�⣡
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
#define __CE_TF_CARD_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_TF_CARD_NEED_CREELINKS_VERSION__ 18                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_TF_CARD_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeTfCard.h��Ҫ����18���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
#include "./ff9/src/diskio.h"                               /*!< ����FatFs�ļ�ϵͳIo������ͷ�ļ����ڴ�ͷ�ļ��д����CeTfCard�����йصĺ����������궨���*/
#include "./ff9/src/ff.h"                                   /*!< ����FatFs�ļ�ϵͳ���ܲ�����ͷ�ļ�*/
/*
 *CeTfCard���Զ���
 */
typedef struct
{
    uint8 backup;                                           /*!< ����*/
}CeTfCard;

/*
 *CeTfCard��������
 */
typedef struct
{
    CE_STATUS       (*initial)(CeTfCard* ceTfCard, CE_RESOURCE ceSpi, CE_RESOURCE ceResourceGpio);/*!<
                                                                 @brief CeTfCardģ���ʼ��
                                                                 @param ceTfCard:CeTfCard���Զ���ָ��
                                                                 @param ceSpi:CeTfCardģ��ʹ�õ�SPI��Դ��
                                                                 @param ceSpi:CeTfCardģ��ʹ�õ�Gpio��Դ��*/

    CE_STATUS       (*getExists)(CeTfCard* ceTfCard);       /*!< @brief ��ȡ�Ƿ����TfCard
                                                                 @param ceTfCard:CeTfCard���Զ���ָ��
                                                                 @return ���ڷ��� CE_STATUS_SUCCESS�������ڷ��� CE_STATUS_FAILE*/

    uint32          (*getCapacity)(CeTfCard* ceTfCard);     /*!< @brief ��ȡ����
                                                                 @param ceTfCard:CeTfCard���Զ���ָ��
                                                                 @return ����������С����λKB*/

    uint32          (*getTotalSpace)(CeTfCard* ceTfCard, uint8 drive);/*!<
                                                                 @brief ��ȡ�ܿռ�
                                                                 @param ceTfCard:CeTfCard���Զ���ָ��
                                                                 @param drive:�߼���������
                                                                 @return �����ܿռ��С����λKB*/

    uint32          (*getAvailableSpace)(CeTfCard* ceTfCard, uint8 drive);/*!<
                                                                 @brief ��ȡ���ÿռ�
                                                                 @param ceTfCard:CeTfCard���Զ���ָ��
                                                                 @param drive:�߼���������
                                                                 @return ���ؿ��ÿռ��С����λKB*/

    /*!< ����ΪFatFs�ļ�����ϵͳ�ṩ�Ľӿڣ�û�н����κη�װ��ֱ�ӽ���ָ�����*/

    FRESULT         (*f_mount)(BYTE driver, FATFS* fileSystemObject);/*!<
                                                                 @brief ��FatFs ģ����ע��/ע��һ��������(�ļ�ϵͳ����)����ʹ���κ������ļ���������֮ǰ�Ǳ���ʹ�øú���Ϊÿ����ע��һ��������
                                                                 @param driver:ע��/ע�����������߼���������(0-9)
                                                                 @param fileSystemObject:������(�ļ�ϵͳ����)ָ�룬ע��ʱ���� CE_NULL����
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_open)(FIL* fileObject, const TCHAR* fileName, BYTE modeFlags);/*!<
                                                                 @brief ����/��һ�����ڷ����ļ����ļ�����
                                                                 @param fileObject:�����������ļ�����ṹ��ָ��
                                                                 @param fileName:'\0'��β���ַ���ָ�룬���ַ���ָ���˽���������򿪵��ļ���
                                                                 @param modeFlags:ָ���ļ��ķ������ͺʹ򿪷��������������б�־��һ�����ָ���ġ�
                                                                                    FA_READ:ָ�������ʶ��󡣿��Դ��ļ��ж�ȡ���ݡ��� FA_WRITE ��Ͽ��Խ��ж�д���ʡ�
                                                                                    FA_WRITE:ָ��д���ʶ��󡣿������ļ���д�����ݡ��� FA_READ ��Ͽ��Խ��ж�д���ʡ�
                                                                                    FA_OPEN_EXISTING:���ļ�������ļ������ڣ����ʧ�ܡ�(Ĭ��)
                                                                                    FA_OPEN_ALWAYS:����ļ����ڣ���򿪣����򣬴���һ�����ļ���
                                                                                    FA_CREATE_NEW:����һ�����ļ�������ļ��Ѵ��ڣ��򴴽�ʧ�ܡ�
                                                                                    FA_CREATE_ALWAYS:����һ�����ļ�������ļ��Ѵ��ڣ����������ضϲ����ǡ�
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_read)(FIL* fileObject, void* buffer, UINT byteToRead, UINT* byteRead);/*!<
                                                                 @brief ��һ���ļ���ȡ����
                                                                 @param fileObject:ָ�򽫱���ȡ���Ѵ򿪵��ļ�����ṹ��ָ�롣
                                                                 @param buffer:ָ��洢��ȡ���ݵĻ�������ָ�롣
                                                                 @param byteToRead:Ҫ��ȡ���ֽ�����UINT ��Χ�ڡ�
                                                                 @param byteRead:ָ�򷵻��Ѷ�ȡ�ֽ�����UINT ������ָ�롣�ڵ��øú��������۽����Σ���ֵ������Ч�ġ�
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_lseek)(FIL* fileObject, DWORD offset);/*!<
                                                                 @brief �ƶ�һ���򿪵��ļ�������ļ���/дָ�롣Ҳ���Ա�������չ�ļ���С(��Ԥ����)��
                                                                 @param fileObject:�򿪵��ļ������ָ��
                                                                 @param offset:������ļ���ʼ�����ֽ�����
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_close)(FIL* fileObject);            /*!< @brief �ر�һ���򿪵��ļ�
                                                                 @param fileObject:ָ�򽫱��رյ��Ѵ򿪵��ļ�����ṹ��ָ�롣
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_opendir)(DIR* dirObject, const TCHAR* dirName);/*!<
                                                                 @brief ��һ��Ŀ¼
                                                                 @param dirObject:�������Ŀհ�Ŀ¼�����ָ�롣
                                                                 @param dirName:'\0'��β���ַ���ָ�룬���ַ���ָ���˽����򿪵�Ŀ¼����
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_readdir) (DIR* dirObject, FILINFO* fileInfo);/*!<
                                                                 @brief ��ȡĿ¼��
                                                                 @param dirObject:�򿪵�Ŀ¼�����ָ�롣
                                                                 @param fileInfo:�洢�Ѷ�ȡ����ļ���Ϣ�ṹָ�롣
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_stat)(const TCHAR* fileName, FILINFO* fileInfo);/*!<
                                                                 @brief ��ȡ�ļ�״̬
                                                                 @param fileName:'\0'��β���ַ���ָ�룬���ַ���ָ���˴���ȡ����Ϣ���ļ���Ŀ¼��
                                                                 @param fileInfo:�洢��Ϣ�Ŀհ�FILINFO �ṹ��ָ�롣
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_write)(FIL* fileObject, const void* buffer, UINT byteToRead, UINT* byteRead);/*!<
                                                                 @brief д�����ݵ�һ���ļ�
                                                                 @param fileObject:ָ�򽫱�д����Ѵ򿪵��ļ�����ṹ��ָ�롣
                                                                 @param buffer:ָ��洢д�����ݵĻ�������ָ�롣
                                                                 @param byteToRead:Ҫд����ֽ�����UINT ��Χ�ڡ�
                                                                 @param byteRead:ָ�򷵻���д���ֽ�����UINT ������ָ�롣�ڵ��øú��������۽����Σ���ֵ������Ч�ġ�
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_getfree)(const TCHAR* path, DWORD* clusters, FATFS** fileSystemObject);/*!<
                                                                 @brief ��ȡ���дص���Ŀ
                                                                 @param path:'\0'��β���ַ���ָ�룬���ַ���ָ�����߼���������Ŀ¼��
                                                                 @param clusters:�洢���д���Ŀ��DWORD ������ָ�롣
                                                                 @param fileSystemObject:��Ӧ�ļ�ϵͳ����ָ���ָ�롣
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_truncate)(FIL* fileObject);         /*!< @brief �ض��ļ���С
                                                                 @param fileObject:���ضϵĴ򿪵��ļ������ָ�롣
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_sync)(FIL* fileObject);             /*!< @brief ��ϴһ��д�ļ��Ļ�����Ϣ
                                                                 @param fileObject:����ϴ�Ĵ򿪵��ļ������ָ�롣
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_unlink)(const TCHAR* fileName);     /*!< @brief �Ƴ�һ������
                                                                 @param fileName:'\0'��β���ַ���ָ�룬���ַ���ָ����һ�����Ƴ��Ķ���
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_mkdir)(const TCHAR* dirName);       /*!< @brief ����һ��Ŀ¼
                                                                 @param dirName:'\0'��β���ַ���ָ�룬���ַ���ָ���˴�������Ŀ¼����
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_chmod)(const TCHAR* fileName, BYTE attribute, BYTE attributeMask);/*!<
                                                                 @brief �޸�һ���ļ���Ŀ¼�����ԡ�
                                                                 @param fileName:'\0'��β���ַ���ָ�룬���ַ���ָ����һ�������޸����Ե��ļ���Ŀ¼��
                                                                 @param attribute:�������õ����Ա�־�����������б�־��һ����������ϡ�ָ���ı�־�����ã������ı������
                                                                                     AM_RDO ֻ����AM_ARC �浵��AM_SYS ϵͳ��AM_HID ����
                                                                 @param attributeMask:�������룬ָ���޸��ĸ����ԡ�ָ�������Ա����û������
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_utime)(const TCHAR*, const FILINFO* timeDate);/*!<
                                                                 @brief �����޸�һ���ļ���Ŀ¼��ʱ�����
                                                                 @param fileName:'\0'��β���ַ�����ָ�룬���ַ���ָ����һ�����޸�ʱ������ļ���Ŀ¼��
                                                                 @param timeDate:�ļ���Ϣ�ṹָ�룬���г�Աftime ��fdata �洢��һ���������õĵ�ʱ������������κ�������Ա��
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_rename)(const TCHAR* oldName, const TCHAR* newName);/*!<
                                                                 @brief ������һ������(�ļ�����Ŀ¼)��
                                                                 @param oldName:'\0'��β���ַ�����ָ�룬���ַ���ָ���˴�����������ԭ��������
                                                                 @param newName:'\0'��β���ַ�����ָ�룬���ַ���ָ��������������¶����������ܰ����������š�
                                                                 @return ���غ���ִ�е�״̬*/

#if _FS_RPATH >= 1  /*!< ���º�����FatFs�ļ�ϵͳ�����Ĺ����йأ����иĶ��뱣��.h��.c��ȫһ��*/
    FRESULT         (*f_chdrive)(BYTE drive);               /*!< @brief �ı�һ���������ĵ�ǰĿ¼��
                                                                 @param drive: ָ����������Ϊ��ǰ���������߼��������š�
                                                                 @return ���غ���ִ�е�״̬*/

    FRESULT         (*f_chdir)(const TCHAR* path);          /*!< @brief �ı�һ���������ĵ�ǰĿ¼��
                                                                 @param path:'\0'��β���ַ�����ָ�룬���ַ���ָ���˽�Ҫ��ȥ��Ŀ¼��
                                                                 @return ���غ���ִ�е�״̬*/

#if _FS_RPATH >= 2
    FRESULT         (*f_getcwd)(TCHAR* buffer, UINT bufferLen);/*!<
                                                                 @brief �ָ���ǰĿ¼��
                                                                 @param buffer:ָ����յ�ǰĿ¼�ַ����Ļ�����
                                                                 @param bufferLen:�������Ĵ�С����λΪTCHAR
                                                                 @return ���غ���ִ�е�״̬*/
#endif //_FS_RPATH >= 2
#endif //_FS_RPATH >= 1

#if _USE_FORWARD && _FS_TINY
    FRESULT         (*f_forward)(FIL* fileObject, UINT(*func)(const BYTE* buffer, UINT bufferLen), UINT byteToFwd, UINT* byteFwd);/*!<
                                                                 @brief ��ȡ�ļ����ݲ�����ת�����������豸��
                                                                 @param fileObject:�򿪵��ļ������ָ�롣
                                                                 @param func:�û������������������ָ�롣����ο�ʾ�����롣
                                                                                buffer:�������͵����ݿ��ָ��
                                                                                bufferLen:>0: �������(�������͵��ֽ���)��0: ������
                                                                 @param byteToFwd:Ҫת�����ֽ�����UINT ��Χ�ڡ�
                                                                 @param byteFwd:������ת�����ֽ�����UINT ������ָ�롣
                                                                 @return ���غ���ִ�е�״̬*/
#endif //_USE_FORWARD && _FS_TINY

#if _USE_MKFS && !_FS_READONLY
    FRESULT         (*f_mkfs)(BYTE drive, BYTE partitioningRule, UINT allocSize);/*!<
                                                                 @brief ���������ϴ���һ���ļ�ϵͳ
                                                                 @param drive:����ʽ�����߼���������(0-9)��
                                                                 @param partitioningRule:������0 ʱ���������������ϵĵ�һ����������һ��������Ȼ���ļ�ϵͳ�������ڷ����ϡ�
                                                                                            �ⱻ��ΪFDISK��ʽ��������Ӳ�̺ʹ洢����������1 ʱ���ļ�ϵͳ�ӵ�һ��������ʼ��������û�з�����
                                                                                            �ⱻ��Ϊ��������(SFD)��ʽ�����������̺Ϳ��ƶ����̡�
                                                                 @param allocSize ָ��ÿ�������ֽ�Ϊ��λ�ķ��䵥Ԫ��С����ֵ������0 ���512 ��32K ֮��2 ���ݡ���ָ��0 ʱ���ش�Сȡ���ھ��С��
                                                                 @return ���غ���ִ�е�״̬*/
#if _MULTI_PARTITION == 2
    FRESULT         (*f_fdisk)(BYTE drive, const DWORD[] partitions, void* work);/*!<
                                                                 @brief ����һ��������������
                                                                 @param drive:ָ��Ҫ���ֵ�����������
                                                                 @param partitions[]:����ӳ����������ĸ���Ŀ��
                                                                 @param work:ָ������������ָ�롣���С��������Ϊ_MAX_SS �ֽڡ�
                                                                 @return ���غ���ִ�е�״̬*/
#endif //_MULTI_PARTITION == 2
#endif //_USE_MKFS && !_FS_READONLY

#if _USE_STRFUNC
    TCHAR           (*f_putc)(TCHAR chr, FIL* fileObject);/*!<
                                                                 @brief ���ļ���д��һ���ַ���
                                                                 @param chr:��д����ַ���
                                                                 @param fileObject:�򿪵��ļ�����ṹ��ָ�롣
                                                                 @return ���ַ����ɹ���д��󣬺������ظ��ַ������ڴ��������κδ�������º���ʧ�ܣ������� EOF��*/

    INT             (*f_puts)(const TCHAR* str, FIL* fileObject);/*!<
                                                                 @brief ���ļ���д��һ���ַ���
                                                                 @param str:��д���'\0'��β���ַ�����ָ�롣'\0'�ַ����ᱻд�롣
                                                                 @param fileObject:�򿪵��ļ�����ṹ��ָ�롣
                                                                 @return �����ɹ��󣬽�����д����ַ��������ڴ��������κδ�������º���ʧ�ܣ������� EOF��*/

    INT             (*f_printf)(FIL* fileObject, const TCHAR* format, ...);/*!<
                                                                 @brief ���ļ���д��һ����ʽ���ַ�����
                                                                 @param fileObject:�Ѵ򿪵��ļ�����ṹ��ָ�롣
                                                                 @param format:'\0'��β�ĸ�ʽ���ַ���ָ�롣
                                                                 @param ...:��ѡ����
                                                                 @return �����ɹ��󣬽�����д����ַ��������ڴ��������κδ�������º���ʧ�ܣ������� EOF��*/

    TCHAR*          (*f_gets)(TCHAR* str, int size, FIL* fileObject);/*!<
                                                                 @brief �ļ��ж�ȡһ���ַ�����
                                                                 @param str:�洢��ȡ�ַ����Ķ�������ָ�롣
                                                                 @param size:����������С��
                                                                 @param fileObject:�򿪵��ļ�����ṹָ�롣
                                                                 @return �����ɹ���str�������ء�*/

#endif //_USE_STRFUNC

    /*!< ����ΪFatFs�ļ�����ϵͳ�ṩ�Ľӿڣ�����FatFs���Ǻ궨��ʵ�֣����Զ�������˷�װ*/
    BYTE           (*f_eof)(FIL* fileObject);
                                                            /*!< @brief ����һ���ļ��Ƿ񵽴��ļ�ĩβ��
                                                                 @param fileObject:ָ����ļ�����ṹ��ָ�롣
                                                                 @return �����/дָ�뵽���ļ�ĩβ��f_eof ��������һ������ֵ�����򷵻�0��*/
    BYTE           (*f_error)(FIL* fileObject);
                                                            /*!< @brief �����ļ��Ƿ����
                                                                 @param fileObject:ָ����ļ�����ṹ��ָ�롣
                                                                 @return ����д��󷵻ط���ֵ�����򷵻� 0��*/
    DWORD          (*f_tell)(FIL* fileObject);
                                                            /*!< @brief ��ȡһ���ļ��ĵ�ǰ��/дָ�롣
                                                                 @param fileObject:ָ����ļ�����ṹ��ָ�롣
                                                                 @return �����ļ��ĵ�ǰ��/дָ�롣*/
    DWORD           (*f_size)(FIL* fileObject);
                                                            /*!< @brief ��ȡһ���ļ��Ĵ�С��
                                                                 @param fileObject:ָ����ļ�����ṹ��ָ�롣
                                                                 @return �����ļ��Ĵ�С����λΪ�ֽڡ�*/
}CeTfCardOpBase;
/*
 *CeTfCard��������ʵ��
 */
extern const CeTfCardOpBase ceTfCardOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_TF_CARD_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_TF_CARD_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����),����ELinkSTM���İ�
  @function CeTfCard��д�ļ�������Ŀ¼����ȡ�����Ȳ���(��ʹ��CeTftϵ��������Ļ���е��������ֻ��Ķ�����ĺ궨�弴�ɡ�ʹ�ú��滻ʹ����Ķ�������С)
******************************************************************************
#include "Creelinks.h"
#include "CeTfCard/CeTfCard.h"  //����ʱ�뽫CeTfCard\ff9\srcĿ¼�µ�diskio.c��ff.c���뵽�����У���Ȼ����ʱ�ᱨ��
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
//  * @brief  ������Ŀ¼�������ļ�
//  * @param  path:ָ�������ĸ�Ŀ¼
//  * @return ����FRESULT
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
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceSystemOp.initialDebug(R14Uart);           //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���

    CE_TFTXXX(Op.initial(&(XXX()), R26L36));
    CE_TFTXXX(Op.setOn());

    ceSystemOp.registerAppendString(appendString);
    ceSystemOp.printf("ELinkSTM build Data: %s Time: %s.\n", __DATE__, __TIME__);

    ceTfCardOp.initial(&ceTfCard, R7Spi, R5ACGPW);

    while (1)
    {
        ceSystemOp.mainTask();                  //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����

        if (ceTfCardOp.getExists(&ceTfCard) == CE_STATUS_SUCCESS)//����Ƿ����
        {
            ceSystemOp.delayMs(3000);

            ceSystemOp.sprintf(filePath, "%s", "0:/Darcern.txt");

            //�����ļ�ϵͳ
            result = ceTfCardOp.f_mount(0, &fatFs);
            if (result != FR_OK)
            {
                ceSystemOp.printf("CeTfCard mount filesystem: %d failed: %d\n\r", 0, result);
            }

            //д�ļ�����
            ceSystemOp.printf("CeTfCard write file test......\n\r");
            result = ceTfCardOp.f_open(&fileObject, filePath, FA_CREATE_ALWAYS | FA_WRITE);
            if (result != FR_OK)
            {
                ceSystemOp.printf("CeTfCard open file error: %d\n\r", result);
            }
            else
            {
                bufferByte = ceSystemOp.sprintf(buffer, "%s", "�������ſƼ����޹�˾\r\nBeiJing Darcern\r\n");

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

            //���ļ�����
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

            //ɨ���Ѿ����ڵ��ļ�
            ceSystemOp.printf("\n\rCeTfCard begin scan files path0......\n\r");
            ceSystemOp.sprintf(filePath, "%s", "0:");
            scan_files(filePath);

            ceSystemOp.printf("CeTfCard Capacity: %u\n", ceTfCardOp.getCapacity(&ceTfCard));
            ceSystemOp.printf("CeTfCard SpaceTotal: %u\n", ceTfCardOp.getTotalSpace(&ceTfCard, 0));
            ceSystemOp.printf("CeTfCard SpaceFree: %u\n", ceTfCardOp.getAvailableSpace(&ceTfCard, 0));

            //ж���ļ�ϵͳ
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

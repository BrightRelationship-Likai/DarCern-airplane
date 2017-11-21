/**
  ******************************************************************************
  * @file    CeHC05.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeHC05ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_HC05_H__
#define __CE_HC05_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_HC05_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_HC05_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_HC05_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeHC05.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

#define CE_HC05_RECV_BUF_SIZE        256                            /*!< �������н��յĻ��泤��*/
#define CE_HC05_DEV_LIST_SIZE        3                               /*!< ָʾ�����豸ʱ�����ɲ��ҵ��Ĵ��豸����*/
#define CE_HC05_FIND_DEV_OUT_TIME    48                              /*!< ָʾ�����豸�ĳ�ʱʱ��*/


#define  CE_HC05_DEV_TYPE_NO_STANDARD    "0x1F1F"                           /*!< �Ǳ�׼�����豸��*/
#define  CE_HC05_DEV_TYPE_IPHONE         "0x7A020C"                          /*!< ƻ���ֻ������豸��*/
#define  CE_HC05_DEV_TYPE_ANDROID        "0x5A020C"                          /*!< ��׿�ֻ������豸�ࣨ���壬��Ϊ�ȣ�*/


/**
  * @brief  ö�٣�CeHC05����Ĺ���ģʽ
  */
typedef enum
{
    CE_HC05_WORK_MODE_MASTER = 1,                                       /*!< ���豸�����������������豸��������������*/
    CE_HC05_WORK_MODE_SLAVE = 0,                                        /*!< ���豸�����������豸���ң������������豸����������*/
    CE_HC05_WORK_MODE_LOOP = 2,                                         /*!< �ػ���ɫ���������ӣ�����Զ���������豸���ݲ�������ԭ�����ظ�Զ���������豸*/
}CE_HC05_WORK_MODE;


typedef struct
{
    char devName[32];                                                   /*!< ģ��ʹ�õ�Uart��Դ*/
    char devAdress[32];                                                 /*!< ģ��ʹ�õ�Uart��Դ*/
}CeHC05DevInfo;

/*
 *CeHC05���Զ���
 */
typedef struct
{
    CeUart  ceUart;                                                     /*!< ģ��ʹ�õ�Uart��Դ*/
    CeGpio  ceGpio0;                                                    /*!< ģ��ʹ�õ�Gpio��Դ*/
    CeGpio  ceGpio1;                                                    /*!< ģ��ʹ�õ�Gpio��Դ*/
    CeGpio  ceGpio2;                                                    /*!< ģ��ʹ�õ�Gpio��Դ*/
    CeHC05DevInfo ceHC05DevInfoList[CE_HC05_DEV_LIST_SIZE];             /*!< ������ģʽ�£����Ҵ��豸ʱ�����ҵ����豸����Ĵ�ŵ�*/
    uint8   ceHC05DevInfoFindDevCount;                                  /*!< ��Ų��ҵ��Ĵ��豸����*/
    uint8   uartRecvBuf[CE_HC05_RECV_BUF_SIZE];                         /*!< Uart����ʹ�õ��Ľ��ջ���*/
    uint8   isLockRecvBuf;                                              /*!< �������ջ��棬��ֹ����ʱ�����ʱ���������ͻ*/
}CeHC05;
/*
 *CeHC05��������
 */
typedef struct
{
    CE_STATUS           (*initial)(CeHC05* ceHC05, CE_RESOURCE ceUart, CE_RESOURCE ceGpio0,CE_RESOURCE ceGpio1,CE_RESOURCE ceGpio2);/*!<
                                                                             @brief CeHC05ģ���ʼ��
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @param ceUart:CeHC05ģ��ʹ�õ�Uart��Դ��
                                                                             @param ceGpio0-2:CeHC05ģ��ʹ�õ�Gpio��Դ��*/

    CE_STATUS           (*parmentConfig)(CeHC05* ceHC05, CE_HC05_WORK_MODE ceHC05WorkMode, const char* ceHC05DevType,const char* devName, const char* password);/*!<
                                                                             @brief CeHC05ģ���������
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @param ceHC05WorkMode:CeHC05ģ��Ĺ�����ʽ������ģ��ʹ�ģ��
                                                                             @param ceHC05DevType:��ģ�鹤������ģʽʱ�����Ҵ��豸ʱֻ���Ҵ����͵ģ���ģ�鹤���ڴ�ģʽʱ��Ϊ��ģ�������
                                                                             @param devName:���豸������
                                                                             @param password:���豸���������*/

    void                (*outParmentConfig)(CeHC05* ceHC05);            /*!< @brief �˳���������״̬��AT״̬����ģ�������ϵ磬��������������ģʽ
                                                                             @param ceHC05:CeHC05���Զ���ָ��*/


    CeHC05DevInfo*    (*getCanConnectDevInfo)(CeHC05* ceHC05);          /*!< @brief ģʽ��������ģʽʱ��������Χ�п����ӵ�������Ϣ
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @return �������ӵ�������Ϣ����*/

    uint8               (*getCanConnectDevCount)(CeHC05* ceHC05);       /*!< @brief ģʽ��������ģʽʱ��������Χ�п����ӵ������豸����
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @return ���ؿ����ӵ������豸����*/

    CE_STATUS           (*checkDevIsExist)(CeHC05* ceHC05, const char* devBlueName);/*!<
                                                                             @brief ģʽ��������ģʽʱ������ָ���������Ƶ��豸�Ƿ���ڲ����ڿ�����״̬
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @param devBlueName:��Ҫ���Ĵ��豸����
                                                                             @return ����CE_STATUS_SUCCESS��ʾ�����ӣ� ����������ʾ��������*/

    CE_STATUS           (*connectDevByName)(CeHC05* ceHC05, const char* devBlueName);/*!<
                                                                             @brief ģʽ��������ģʽʱ��ʹ���豸����������һ�����豸
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @param devBlueName:��Ҫ���ӵĴ��豸����
                                                                             @return ����CE_STATUS_SUCCESS��ʾ���ӳɹ��� ����������ʾ����ʧ��*/

    uint8               (*getConnectStatus)(CeHC05* ceHC05);            /*!< @brief ��ȡģ�������״̬
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @return ����0x00:ģ�鴦��δ���״̬������0x01:ģ�鴦����Գɹ�״̬�����Խ������ݴ���*/

    void               (*sendData)(CeHC05* ceHC05, uint8* dataInBuf, uint16 sendCount);/*!<
                                                                             @brief ��������
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @param dataInBuf:��Ҫ���͵����ݻ���
                                                                             @param sendCount:��Ҫ���͵����ݳ���
                                                                             @return ʵ�ʷ�����ɵ����ݳ���*/

    uint16              (*getRecvDataCount)(CeHC05* ceHC05);            /*!< @brief ��ȡ���ջ����еĿɶ�ȡ�����ݳ���
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @return ���ջ����еĿɶ�ȡ����������*/

    uint16              (*readData)(CeHC05* ceHC05, uint8* dataOutBuf, uint16 readCount);/*!<
                                                                             @brief �ӽ��ջ����ж�ȡ����
                                                                             @param ceHC05:CeHC05���Զ���ָ��
                                                                             @param dataOutBuf:��ȡ���ݴ�ŵĻ���
                                                                             @param readCount:��Ҫ��ȡ�����ݳ���
                                                                             @return ʵ�ʶ�ȡ�������ݳ���*/
}CeHC05OpBase;
/*
 *CeHC05��������ʵ��
 */
extern const CeHC05OpBase ceHC05Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_HC05_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__CE_HC05_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function xxxxxzzzz
******************************************************************************

#include "Creelinks.h"
#include "CeHC05.h"
#include "CeTft320Nt.h"

CeTft320Nt ceTft320Nt;
CeHC05 ceHC05;


int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceTft320NtOp.initial(&ceTft320Nt,R26L36);
    ceDebugOp.registerAppendString(ceTft320NtOp.appendString);
    ceHC05Op.initial(&ceHC05,R18Uart,R10TI2c);

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        while(CE_STATUS_SUCCESS != ceHC05Op.parmentConfig(&ceHC05,CE_HC05_WORK_MODE_MASTER,CE_HC05_DEV_TYPE_NO_STANDARD,"haha","1234"))
        {
            ceSystemOp.delayMs(100);
            ceDebugOp.printf("parmentConfig Faile \n");
        }

        while(CE_STATUS_SUCCESS != ceHC05Op.checkDevIsExist(&ceHC05,"CC Technology"))
        {
            ceSystemOp.delayMs(100);
            ceDebugOp.printf("checkDevIsExist Faile \n");
        }

        while(CE_STATUS_SUCCESS != ceHC05Op.connectDevByName(&ceHC05,"CC Technology"))
        {
            ceSystemOp.delayMs(100);
            ceDebugOp.printf("connectDevByName Faile \n");
        }

        ceHC05Op.outParmentConfig(&ceHC05);

        while(1)
        {
            ceSystemOp.delayMs(1000);
            ceDebugOp.printf("status %d\n",ceHC05Op.getConnectStatus(&ceHC05));
        }
    };
}

******************************************************************************
*/


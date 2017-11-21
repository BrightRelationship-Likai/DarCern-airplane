/**
  ******************************************************************************
  * @file    CeFontGt.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeFontGtģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_FONT_GT_H__
#define __CE_FONT_GT_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_FONT_GT_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_FONT_GT_NEED_CREELINKS_VERSION__ 1                              /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_FONT_GT_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeFontGt.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *��Ҫ��ȡ����ģ����
 */
typedef enum
{
    CE_FONT_GT_TYPE_GB2312_16x16,                                     /*!< 16*16��GB2312��ģ*/
}CE_FONT_GT_TYPE;

/*
 *CeFontGt���Զ���
 */
typedef struct
{
    CeSpiMaster ceSpiMaster;                                          /*!< ģ��ʹ�õ���SpiMaster��Դ*/
}CeFontGt;


/*
 *CeFontGt��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeFontGt* ceFontGt, CE_RESOURCE ceSpi);    /*!< @brief  CeFontGtģ���ʼ��
                                                                           @param  ceFontGt:CeFontGt���Զ���ָ��
                                                                           @param  ceSpi:CeFontGtģ��ʹ�õ���Դ��*/

    void        (*getFontData)(CeFontGt* ceFontGt, char* msg, uint8* outBuf, CE_FONT_GT_TYPE ceFontGtType);/*!<
                                                                           @brief  ����ģоƬ�л�ȡ����
                                                                           @param  ceFontGt:CeFontGt���Զ���
                                                                           @param  msg:����ȡ������ַ���ָ��
                                                                           @param  outBuf:��Ż�ȡ��������Ļ�����
                                                                           @param  ceFontGtType:����ȡ����ģ����*/
}CeFontGtOp;
/*
 *CeFontGt��������ʵ��
 */
extern const CeFontGtOp ceFontGtOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_FONT_GT_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_FONT_GT_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��ȡ������ģ������Tft180����ʾ����
******************************************************************************
#include "Creelinks.h"
#include "CeTft180.h"
#include "CeFontGt.h"
CeTft180 myTft180;                              //����CeTft180ģ�����Զ���
CeFontGt myFontGt;                              //����CeFontGtģ�����Զ���
uint8 fontTemp[32];                             //�����õ���ģ������ʱ�������
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceTft180Op.initial(&myTft180, R7Spi, R2TI2c);
    ceFontGtOp.initial(&myFontGt, R12Spi);

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,16,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,32,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,48,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,64,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,80,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,96,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);
    };
}
******************************************************************************
*/

/*****************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����),����ELinkSTM���İ�
* @function CeFontGt��ģ��CeTft320Nt�е���ģ��������(ʹ��CeTft320Nt���е������)
******************************************************************************
#include "Creelinks.h"
#include "CeTft320Nt.h"
#include "CeFontGt.h"
CeTft320Nt ceTft320Nt;
CeFontGt ceFontGt;
#define FONT_DAT_BUF_SIZE 512
uint8 fontDataBuf[FONT_DAT_BUF_SIZE];
char outBuffer[96] = { 0 };
char inBuffer[2] = "��";
int i = 0;
int x = 0;
int y = 0;
void appendString(char* msg)
{
    ceTft320NtOp.appendString(msg);
}
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R14Uart);                 //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���

    ceTft320NtOp.initial(&ceTft320Nt, R26L36);
    ceTft320NtOp.setOn();

    ceTft320NtOp.fill(CE_TFT320_NT_COLOR_GRAY0);

    ceDebugOp.sprintf(outBuffer, "ELinkSTM build Data: %s Time: %s.\n", __DATE__, __TIME__);
    ceTft320NtOp.showString(0, 0, CE_TFT320_NT_COLOR_RED, CE_TFT320_NT_COLOR_BLACK, outBuffer, CE_TFT320_NT_EN_SIZE_F8X16);
    //ceDebugOp.registerAppendString(appendString); 

    ceFontGtOp.initial(&ceFontGt, R12Spi);

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����

        for (i = 0; i < 6763; i++)
        {

            if(inBuffer[1] >= (char)0xFF)
            {
                inBuffer[0] = inBuffer[0] + 1;
                inBuffer[1] = 0x00;
            }
            else
            {
                inBuffer[1] = inBuffer[1] + 1;
            }

            ceFontGtOp.getFontData(&ceFontGt, inBuffer, fontDataBuf, CE_FONT_GT_TYPE_GB2312_16x16);
            //ceTft320NtOp.getFontData(inBuffer, fontDataBuf, CE_TFT320_NT_GBK_TYPE_16X16);
            ceTft320NtOp.showCN1616(x, y, CE_TFT320_NT_COLOR_RED, CE_TFT320_NT_COLOR_BLACK, fontDataBuf);
            x += 16;

            if (x >= CE_TFT320_NT_WIDTH)
            {
                x = 0;
                y += 16;
            }
            if(y >= CE_TFT320_NT_HIGHT)
            {
                y = 0;
                ceSystemOp.delayMs(2000);
                ceTft320NtOp.fill(CE_TFT320_NT_COLOR_BLACK);
            }
        }
    };
}
******************************************************************************
*/

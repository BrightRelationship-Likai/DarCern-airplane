/**
  ******************************************************************************
  * @file    CeSpiEx.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSpiExģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_SPI_EX_H__
#define __CE_SPI_EX_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_SPI_EX_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_SPI_EX_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_SPI_EX_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeSpiEx.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeSpiEx���Զ���
 */
typedef struct
{
    CeGpio ceGpio0;                                                         /*!< ����ʹ�õ���Gpio�ӿ���Դ*/
    CeGpio ceGpio1;
    CeGpio ceGpio2;
}CeSpiEx;
/*
 *CeSpiEx��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeSpiEx* ceSpiEx,CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                             @brief CeSpiExģ���ʼ��
                                                                             @param ceSpiEx:CeSpiEx���Զ���ָ��
                                                                             @param ceGpio0:CeSpiExģ��ʹ�õĵ�һ��Gpio��Դ��
                                                                             @param ceGpio1:CeSpiExģ��ʹ�õĵڶ���Gpio��Դ��
                                                                             @param ceGpio2:CeSpiExģ��ʹ�õĵ�����Gpio��Դ��
                                                                             */

    void        (*enablePort)(CeSpiEx* ceSpiEx, uint8 portIndex);       /*!< @brief ʹ��ͨ��
                                                                             @param ceSpiEx:CeSpiEx���Զ���ָ��
                                                                             @param portIndex:��Ҫʹ�ܵ�ͨ���ţ�0��2*/
}CeSpiExOp;
/*
 *CeSpiEx��������ʵ��
 */
extern const CeSpiExOp ceSpiExOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_SPI_EX_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SPI_EX_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��һ��CeSpiEx������һ��CeTft180Һ����ʾ����һ��CeFontGt������ģģ�飬
*         ����CeFontGt��ȡ���֣���ʾ��CeTft180�ڡ�ע��CeTft180��CeFontGt�ֱ�ӵ�Spi0��Spi1�ϡ�
******************************************************************************
#include "Creelinks.h"
#include "CeTft180.h"
#include "CeFontGt.h"
#include "CeSpiEx.h"
CeTft180 myTft180;
CeFontGt myFontGt;
CeSpiEx mySpiEx;
uint8 fontTemp[32];
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceSpiExOp.initialWithTg(&mySpiEx,R10TI2c);  //ʹ��R10TI2c��Tg���ܳ�ʼ��mySpiEx
    ceSpiExOp.enablePort(&mySpiEx,0);           //ʹ��SpiEx�ĵ�0��Spi��
    ceTft180Op.initial(&myTft180,R7Spi,R2TI2c); //ʹ��R7Spi��R2TI2c��Դ����ʼ��myTft180

    ceSpiExOp.enablePort(&mySpiEx,1);           //ʹ��SpiEx�ĵ�1��Spi��
    ceFontGtOp.initial(&myFontGt,R7Spi);          //Ҳʹ��R7Spi����ʼ��myFontGt
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.fill(&myTft180,CE_TFT180_COLOR_RED);
        ceSystemOp.delayMs(1000);
        ceTft180Op.fill(&myTft180,CE_TFT180_COLOR_GREEN);
        ceSystemOp.delayMs(1000);
        ceTft180Op.fill(&myTft180,CE_TFT180_COLOR_BLUE);
        ceSystemOp.delayMs(1000);
        ceTft180Op.fill(&myTft180,CE_TFT180_COLOR_BLACK);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 40, 40,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 40 + 16, 40,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 40 + 32, 40, CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK,fontTemp);

        ceTft180Op.showString(&myTft180, 28, 56, CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK,"CREELINKS", CE_TFT180_EN_SIZE_F8X16);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 16*1, 72, CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK,fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 16*2, 72, CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK,fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 16*3, 72,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 16*4, 72,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 16*5, 72,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�1��Spi�ڣ�����������FontGtģ��
        ceFontGtOp.getFontData(&myFontGt,"��",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//��ȡ������ģ����
        ceSpiExOp.enablePort(&mySpiEx,0);       //ʹ��SpiEx�ĵ�0��Spi�ڣ�����������Tft180ģ��
        ceTft180Op.showCN1616(&myTft180, 16*6, 72,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSystemOp.delayMs(2000);
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeSpiEx.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSpiEx模块的驱动头文件
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
#define __CE_SPI_EX_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_SPI_EX_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_SPI_EX_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeSpiEx.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeSpiEx属性对像
 */
typedef struct
{
    CeGpio ceGpio0;                                                         /*!< 操作使用到的Gpio接口资源*/
    CeGpio ceGpio1;
    CeGpio ceGpio2;
}CeSpiEx;
/*
 *CeSpiEx操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeSpiEx* ceSpiEx,CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                             @brief CeSpiEx模块初始化
                                                                             @param ceSpiEx:CeSpiEx属性对象指针
                                                                             @param ceGpio0:CeSpiEx模块使用的第一个Gpio资源号
                                                                             @param ceGpio1:CeSpiEx模块使用的第二个Gpio资源号
                                                                             @param ceGpio2:CeSpiEx模块使用的第三个Gpio资源号
                                                                             */

    void        (*enablePort)(CeSpiEx* ceSpiEx, uint8 portIndex);       /*!< @brief 使能通道
                                                                             @param ceSpiEx:CeSpiEx属性对象指针
                                                                             @param portIndex:需要使能的通道号，0－2*/
}CeSpiExOp;
/*
 *CeSpiEx操作对象实例
 */
extern const CeSpiExOp ceSpiExOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_SPI_EX_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SPI_EX_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 在一个CeSpiEx上连接一个CeTft180液晶显示屏和一个CeFontGt汉字字模模块，
*         并从CeFontGt获取汉字，显示到CeTft180内。注意CeTft180和CeFontGt分别接到Spi0与Spi1上。
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
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceSpiExOp.initialWithTg(&mySpiEx,R10TI2c);  //使用R10TI2c的Tg功能初始化mySpiEx
    ceSpiExOp.enablePort(&mySpiEx,0);           //使能SpiEx的第0个Spi口
    ceTft180Op.initial(&myTft180,R7Spi,R2TI2c); //使用R7Spi与R2TI2c资源来初始化myTft180

    ceSpiExOp.enablePort(&mySpiEx,1);           //使能SpiEx的第1个Spi口
    ceFontGtOp.initial(&myFontGt,R7Spi);          //也使用R7Spi来初始化myFontGt
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.fill(&myTft180,CE_TFT180_COLOR_RED);
        ceSystemOp.delayMs(1000);
        ceTft180Op.fill(&myTft180,CE_TFT180_COLOR_GREEN);
        ceSystemOp.delayMs(1000);
        ceTft180Op.fill(&myTft180,CE_TFT180_COLOR_BLUE);
        ceSystemOp.delayMs(1000);
        ceTft180Op.fill(&myTft180,CE_TFT180_COLOR_BLACK);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"创",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 40, 40,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"ｅ",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 40 + 16, 40,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"联",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 40 + 32, 40, CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK,fontTemp);

        ceTft180Op.showString(&myTft180, 28, 56, CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK,"CREELINKS", CE_TFT180_EN_SIZE_F8X16);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"北",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 16*1, 72, CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK,fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"京",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 16*2, 72, CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK,fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"大",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 16*3, 72,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"信",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 16*4, 72,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"科",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 16*5, 72,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第1个Spi口，以正常操作FontGt模块
        ceFontGtOp.getFontData(&myFontGt,"技",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);//获取汉字字模数据
        ceSpiExOp.enablePort(&mySpiEx,0);       //使能SpiEx的第0个Spi口，以正常操作Tft180模块
        ceTft180Op.showCN1616(&myTft180, 16*6, 72,CE_TFT180_COLOR_WHITE,CE_TFT180_COLOR_BLACK, fontTemp);

        ceSystemOp.delayMs(2000);
    };
}
******************************************************************************
*/

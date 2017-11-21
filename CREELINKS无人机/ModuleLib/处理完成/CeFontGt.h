/**
  ******************************************************************************
  * @file    CeFontGt.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeFontGt模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)无
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
#define __CE_FONT_GT_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_FONT_GT_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_FONT_GT_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeFontGt.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *需要获取的字模类型
 */
typedef enum
{
    CE_FONT_GT_TYPE_GB2312_16x16,                                     /*!< 16*16的GB2312字模*/
}CE_FONT_GT_TYPE;

/*
 *CeFontGt属性对像
 */
typedef struct
{
    CeSpiMaster ceSpiMaster;                                          /*!< 模块使用到的SpiMaster资源*/
}CeFontGt;


/*
 *CeFontGt操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeFontGt* ceFontGt, CE_RESOURCE ceSpi);    /*!< @brief  CeFontGt模块初始化
                                                                           @param  ceFontGt:CeFontGt属性对象指针
                                                                           @param  ceSpi:CeFontGt模块使用的资源号*/

    void        (*getFontData)(CeFontGt* ceFontGt, char* msg, uint8* outBuf, CE_FONT_GT_TYPE ceFontGtType);/*!<
                                                                           @brief  从字模芯片中获取字体
                                                                           @param  ceFontGt:CeFontGt属性对象
                                                                           @param  msg:欲获取字体的字符串指针
                                                                           @param  outBuf:存放获取到的字体的缓冲区
                                                                           @param  ceFontGtType:欲获取的字模类型*/
}CeFontGtOp;
/*
 *CeFontGt操作对象实例
 */
extern const CeFontGtOp ceFontGtOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_FONT_GT_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_FONT_GT_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 获取汉字字模，并在Tft180上显示出来
******************************************************************************
#include "Creelinks.h"
#include "CeTft180.h"
#include "CeFontGt.h"
CeTft180 myTft180;                              //定义CeTft180模块属性对象
CeFontGt myFontGt;                              //定义CeFontGt模块属性对象
uint8 fontTemp[32];                             //定义获得的字模数据临时存放数组
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceTft180Op.initial(&myTft180, R7Spi, R2TI2c);
    ceFontGtOp.initial(&myFontGt, R12Spi);

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceFontGtOp.getFontData(&myFontGt,"北",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,16,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"京",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,32,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"大",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,48,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"信",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,64,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"科",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,80,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);

        ceFontGtOp.getFontData(&myFontGt,"技",fontTemp,CE_FONT_GT_TYPE_GB2312_16x16);
        ceTft180Op.showCN1616(&myTft180,96,80,CE_TFT180_COLOR_BLACK,CE_TFT180_COLOR_WHITE,fontTemp);
    };
}
******************************************************************************
*/

/*****************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境),基于ELinkSTM核心板
* @function CeFontGt字模或CeTft320Nt中的字模遍历测试(使用CeTft320Nt进行调试输出)
******************************************************************************
#include "Creelinks.h"
#include "CeTft320Nt.h"
#include "CeFontGt.h"
CeTft320Nt ceTft320Nt;
CeFontGt ceFontGt;
#define FONT_DAT_BUF_SIZE 512
uint8 fontDataBuf[FONT_DAT_BUF_SIZE];
char outBuffer[96] = { 0 };
char inBuffer[2] = "、";
int i = 0;
int x = 0;
int y = 0;
void appendString(char* msg)
{
    ceTft320NtOp.appendString(msg);
}
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R14Uart);                 //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作

    ceTft320NtOp.initial(&ceTft320Nt, R26L36);
    ceTft320NtOp.setOn();

    ceTft320NtOp.fill(CE_TFT320_NT_COLOR_GRAY0);

    ceDebugOp.sprintf(outBuffer, "ELinkSTM build Data: %s Time: %s.\n", __DATE__, __TIME__);
    ceTft320NtOp.showString(0, 0, CE_TFT320_NT_COLOR_RED, CE_TFT320_NT_COLOR_BLACK, outBuffer, CE_TFT320_NT_EN_SIZE_F8X16);
    //ceDebugOp.registerAppendString(appendString); 

    ceFontGtOp.initial(&ceFontGt, R12Spi);

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作

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

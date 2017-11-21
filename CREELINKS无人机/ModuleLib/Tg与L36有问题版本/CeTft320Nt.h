/**
  ******************************************************************************
  * @file    CeTft320Nt.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTft320Nt模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)CeTft320Nt使用L36口，而针对一个核心板，仅有一个L36口，故只需在初始化时提供
  *  CeTft320Nt属性对象指针，其它操作则不用再提供。
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TFT320_NT_H__
#define __CE_TFT320_NT_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_TFT320_NT_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_TFT320_NT_NEED_CREELINKS_VERSION__ 1                          /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_TFT320_NT_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeTft320Nt.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

#ifndef __CE_USE_L36__
#error "未启用L36资源接口,请在CeMcu.h中检查宏定义是否开启，或确认核心板是否支持！"
#else
#define CE_TFT320_NT_USE_BUFFER                /*!< 是否使用缓冲，即在内存中开辟(WIDTH * HIGHT * 2)的缓存，以提高显示效果*/

//#define CE_TFT320_NT_SHOW_HORIZONTAL         /*!< 如果需要横向显示，则定义此行 注：V1.0版本暂仅支持竖屏*/

#ifdef CE_TFT320_NT_SHOW_HORIZONTAL
#define CE_TFT320_NT_WIDTH     480
#define CE_TFT320_NT_HIGHT     320
#else
#define CE_TFT320_NT_WIDTH     320
#define CE_TFT320_NT_HIGHT     480
#endif

#define CE_TFT320_NT_DRAW_POINT(x, y, color)                  ceTft320NtOp.drawPoint((x), (y), color);
#define CE_TFT320_NT_DRAW_RECTANGLE(sX, sY, eX, eY, color)    ceTft320NtOp.drawRectangle((sX), (sY), (eX), (eY), (color));

/**
  * @brief  枚举，CeTft320Nt对象常用显示的颜色列表
  */
typedef enum
{
    CE_TFT320_NT_COLOR_RED     =   0xF800,                      /*!< 红色*/
    CE_TFT320_NT_COLOR_GREEN   =   0x07E0,                      /*!< 绿色*/
    CE_TFT320_NT_COLOR_BLUE    =   0x001F,                      /*!< 蓝色*/
    CE_TFT320_NT_COLOR_WHITE   =   0xFFFF,                      /*!< 白色*/
    CE_TFT320_NT_COLOR_BLACK   =   0x0000,                      /*!< 黑色*/
    CE_TFT320_NT_COLOR_YELLOW  =   0xFFE0,                      /*!< 黄色*/
    CE_TFT320_NT_COLOR_GRAY0   =   0xEF7D,                      /*!< 灰白色*/
    CE_TFT320_NT_COLOR_GRAY1   =   0x8410,                      /*!< 浅灰色*/
    CE_TFT320_NT_COLOR_GRAY2   =   0x4208,                      /*!< 灰色*/
} CE_TFT320_NT_COLOR_LIST;

/**
  * @brief  枚举，CeTft320Nt对象显示英文字符的字模大小
  */
typedef enum
{
    CE_TFT320_NT_EN_SIZE_F6X8,                                  /*!< 字符宽占6个像素点，高占8个像素点*/
    CE_TFT320_NT_EN_SIZE_F8X16,                                 /*!< 字符宽占8个像素点，高占16个像素点*/
} CE_TFT320_NT_EN_SIZE;

/**
  * @brief  枚举，CeTft320Nt对象显示中文字符的字模大小
  */
typedef enum
{
    CE_TFT320_NT_GBK_TYPE_16X16,                                /*!< 中文字符宽占16个像素点，高占16个像素点*/
} CE_TFT320_NT_GBK_TYPE;

/**
  *CeTft320Nt属性对像
  */
typedef struct
{
    CeL36   ceL36;                                              /*!< 模块使用到的L36的资源属性对象*/
    char    asBuf[CE_TFT320_NT_WIDTH / 6][CE_TFT320_NT_HIGHT / 8];/*!< 用于打印调试信息的缓存*/
    uint16  asXIndex;                                           /*!< 用于打印调试信息的光标x轴*/
    uint16  asYIndex;                                           /*!< 用于打印调试信息的光标y轴*/
}CeTft320Nt;

/**
  *CeTft320Nt操作对像
  */
typedef struct
{
    CE_STATUS   (*initial)(CeTft320Nt* ceTft320Nt, CE_RESOURCE ceL36);/*!<
                                                                     @brief CeTft320Nt模块初始化
                                                                     @param ceL36:CeTft320Nt模块使用的资源号*/

    void        (*setOn)(void);                                 /*!< @brief 打开显示*/

    void        (*setBrightness)(uint8 brightness);             /*!< @brief 设置屏幕亮度
                                                                     @param brightness:屏亮度百分比，0－100*/

    void        (*fill)(uint16 color);                          /*!< @brief CeTft320Nt用指定数据(颜色)进行全屏填充
                                                                     @param color:全屏填充的数据(颜色)*/

    void        (*drawPoint)(int16 x, int16 y, uint16 color);   /*!< @brief CeTft320Nt在指定位置画点
                                                                     @param x:设置开始显示字符串的x轴坐标
                                                                     @param y:设置开始显示字符串的y轴坐标
                                                                     @param color:要显示的数据(颜色)*/

    void        (*drawRectangle)(uint16 startX, uint16 startY, uint16 endX, uint16 endY, int16 color);/*!<
                                                                     @brief CeTft320Nt绘制矩形
                                                                     @param startX:矩形左上角x坐标
                                                                     @param startY:矩形左上角y坐标
                                                                     @param endX:矩形右下角x坐标
                                                                     @param endY:矩形右下角y坐标
                                                                     @param color:要显示的数据(颜色)*/

    void        (*drawData)(uint16 x, uint16 y, const uint8* colorBuf, uint16 bufSizeWidth, uint16 bufSizeHight);/*!<
                                                                     @brief CeTft320Nt绘制图片
                                                                     @param x:图片的起始点x坐标
                                                                     @param y:图片的起始点y坐标
                                                                     @param colorBuf:图片数据
                                                                     @param bufSizeWidth:图片宽
                                                                     @param bufSizeHight:图片高*/

    void        (*showString)(int16 x, int16 y, uint16 foreColor, uint16 backColor, const char* msg, CE_TFT320_NT_EN_SIZE showSize);/*!<
                                                                     @brief CeTft320Nt显示字符串，不支持中文
                                                                     @param x:设置开始显示字符串的x轴坐标
                                                                     @param y:设置开始显示字符串的y轴坐标
                                                                     @param foreColor:显示字体的前景色
                                                                     @param backColor:显示字体的背景色
                                                                     @param msg:要显示的字符串指针
                                                                     @param showSize:显示的字体大小，可选CE_LCD_EN_SIZE_F6X8或CE_LCD_EN_SIZE_F8X16*/

    void        (*showInt)(int16 x, int16 y, uint16 foreColor, uint16 backColor, const int32 val, CE_TFT320_NT_EN_SIZE showSize);/*!<
                                                                     @brief CeTft320Nt显示32位有符号的数字，最大值0x7FFFFFFF，最小值0x80000001
                                                                     @param x:设置开始显示32位有符号的数字的x轴坐标
                                                                     @param y:设置开始显示32位有符号的数字的y轴坐标
                                                                     @param foreColor:显示字体的前景色
                                                                     @param backColor:显示字体的背景色
                                                                     @param val:要显示的32位有符号的数字
                                                                     @param showSize:显示的字体大小，可选CE_LCD_EN_SIZE_F6X8或CE_LCD_EN_SIZE_F8X16*/

    void        (*showCN1616)(int16 x, int16 y, uint16 foreColor, uint16 backColor, const uint8* cn1616);/*!<
                                                                     @brief CeTft320Nt显示16x16的中文字体，字模cn1616可从CeCN1616.h中获取
                                                                     @param x:设置开始显示字符串的x轴坐标
                                                                     @param y:设置开始显示字符串的y轴坐标
                                                                     @param foreColor:显示字体的前景色
                                                                     @param backColor:显示字体的背景色
                                                                     @param cn1616:要显示的文字模，字模cn1616可从CeCN1616.h中获取*/

    void        (*appendString)(const char* msg);               /*!< @brief 一般用于代码调试，以控制台的方式打印调试信息
                                                                     @param msg:要显示的信息*/

    void        (*setOff)(void);                                /*!< @brief 关闭显示*/

    void        (*getFontData)(char* msgGBK, uint8* outBuf, CE_TFT320_NT_GBK_TYPE ceTft320NtGBKType);/*!<
                                                                     @brief 从字模芯片中获取字体
                                                                     @param ceTft320Nt:CeTft320Nt属性对象*/
}CeTft320NtOp;

/**
  *CeTft320Nt操作对象实例
  */
extern const CeTft320NtOp ceTft320NtOp;

#endif
#endif //(__CE_CREELINKS_VERSION__ < __CE_TFT320_NT_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus

#endif //__CE_TFT320_NT_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 在CeTft320NtNt液晶屏上显示R、G、B三色，并显示汉字、英文
******************************************************************************
#include "Creelinks.h"
#include "CeTft320Nt.h"
CeTft320Nt myTft320Nt;
uint8 fontTemp[32];
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceTft320NtOp.initial(&myTft320Nt,R26L36);
    ceDebugOp.registerAppendString(ceTft320NtOp.appendString);//注册调试信息显示函数，并打印系统信息
    ceSystemOp.delayMs(2000);

    ceTft320NtOp.fill(CE_TFT320_NT_COLOR_RED);
    ceSystemOp.delayMs(1000);
    ceTft320NtOp.fill(CE_TFT320_NT_COLOR_GREEN);
    ceSystemOp.delayMs(1000);
    ceTft320NtOp.fill(CE_TFT320_NT_COLOR_BLUE);
    ceSystemOp.delayMs(1000);
    ceTft320NtOp.fill(CE_TFT320_NT_COLOR_BLACK);

    ceTft320NtOp.getFontData("创",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616( 136, 216,CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK, fontTemp);
    ceTft320NtOp.getFontData("ｅ",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616(136 + 16, 216,CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK, fontTemp);
    ceTft320NtOp.getFontData("联",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616( 136 + 32, 216, CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK,fontTemp);

    ceTft320NtOp.showString( 84, 232, CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK,"CREELINKS", CE_TFT320_NT_EN_SIZE_F8X16);

    ceTft320NtOp.getFontData("北",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616( 142+16*1, 248, CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK,fontTemp);
    ceTft320NtOp.getFontData("京",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616( 142+16*2, 248, CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK,fontTemp);
    ceTft320NtOp.getFontData("大",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616( 142+16*3, 248,CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK, fontTemp);
    ceTft320NtOp.getFontData("信",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616( 142+16*4, 248,CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK, fontTemp);
    ceTft320NtOp.getFontData("科",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616( 142+16*5, 248,CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK, fontTemp);
    ceTft320NtOp.getFontData("技",fontTemp,CE_TFT320_NT_GBK_TYPE_16X16);
    ceTft320NtOp.showCN1616( 142+16*6, 248,CE_TFT320_NT_COLOR_WHITE,CE_TFT320_NT_COLOR_BLACK, fontTemp);

    ceSystemOp.delayMs(2000);
    ceTft320NtOp.fill(CE_TFT320_NT_COLOR_BLACK);     //刷黑屏，并开始手写响应
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
    };
}
******************************************************************************
*/

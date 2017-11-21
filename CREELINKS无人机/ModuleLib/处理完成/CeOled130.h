/**
  ******************************************************************************
  * @file    CeOled130.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeOled130模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_OLED130_H__
#define __CE_OLED130_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_OLED130_VERSION__ 1                                               /*!< 此驱动文件的版本号*/
#define __CE_OLED130_NEED_CREELINKS_VERSION__ 1                                /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_OLED130_NEED_CREELINKS_VERSION__)         /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeOled130.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
#define CE_OLED130_WIDTH     128
#define CE_OLED130_HIGHT     64
/*
 *CeOled130属性对像
 */
typedef struct
{
    CeI2cMaster ceI2cMaster;
    char asBuf[CE_OLED130_WIDTH / 6][CE_OLED130_HIGHT / 8];/*!< 用于打印调试信息的缓存*/
    uint16 asXIndex;                                   /*!< 用于打印调试信息的光标x轴*/
    uint16 asYIndex;                                   /*!< 用于打印调试信息的光标y轴*/
}
CeOled130;

typedef enum
{
    CE_OLED130_EN_SIZE_F6X8 = 0x01,                    /*!< CeOled130使用6*8的点阵来进行显示*/
    CE_OLED130_EN_SIZE_F8X16,                          /*!< CeOled130使用8*16的点阵来进行显示*/
} CE_OLED130_EN_SIZE;
/*
 *CeOled130操作对像
 */
typedef struct
{
    CE_STATUS   (*initial)(CeOled130* ceOled130,CE_RESOURCE ceI2c);/*!<
                                                         @brief CeOled130模块初始化
                                                         @param ceOled130:CeOled130属性对象指针
                                                         @param ceI2c:CeOled130模块使用的资源号*/

    void        (*setOn)(CeOled130* ceOled130);     /*!< @brief CeOled130打开显示
                                                         @param ceOled130:CeOled130属性对象指针*/

    void        (*fill)(CeOled130* ceOled130, uint8 fillData);/*!<
                                                         @brief CeOled130用指定数据进行全屏填充
                                                         @param ceOled130:CeOled130属性对象
                                                         @param fillData:全屏填充的数据*/

    void        (*clr)(CeOled130* ceOled130);       /*!< @brief CeOled130清屏
                                                         @param ceOled130:CeOled130属性对象*/

    void        (*showString)(CeOled130* ceOled130, uint8 x, uint8 y, char* msg, CE_OLED130_EN_SIZE showSize);/*!<
                                                         @brief CeOled130显示字符串
                                                         @param ceOled130:CeOled130属性对象
                                                         @param x:设置开始显示字符串的x轴坐标。
                                                         @param y:设置开始显示字符串的y轴坐标(也就是行坐标，CeOled130可以显示8行F6x8，和4行F8x16的字体，范围0-7)
                                                         @param msg:要显示的字符串指针
                                                         @param showSize:显示的字体大小，可选CE_OLED_SIZE_F6X8或CE_OLED_SIZE_F8X16*/

    void        (*showInt)(CeOled130* ceOled130, uint8 x, uint8 y, int32 val, CE_OLED130_EN_SIZE showSize);/*!<
                                                         @brief CeOled130显示32位有符号的数字
                                                         @param ceOled130:CeOled130属性对象
                                                         @param x:设置开始显示32位有符号的数字的x轴坐标
                                                         @param y:设置开始显示32位有符号的数字的y轴坐标(也就是行坐标，CeOled130可以显示8行F6x8，和4行F8x16的字体，范围0-3)
                                                         @param val:要显示的32位有符号的数字
                                                         @param showSize:显示的字体大小，可选CE_OLED_SIZE_F6X8或CE_OLED_SIZE_F8X16*/

    void        (*showCN1616)(CeOled130* ceOled130, uint8 x, uint8 y, const uint8* cn1616);/*!<
                                                         @brief CeOled130显示16x16的汉字
                                                         @param ceOled130:CeOled130属性对象
                                                         @param x:设置开始显示32位有符号的数字的x轴坐标
                                                         @param y:设置开始显示32位有符号的数字的y轴坐标(也就是行坐标，CeOled130可以显示4行16x16的汉字，范围0-3)
                                                         @param cn1616:要显示的汉字字模，可从"CeCN1616.h"中获取*/

    void        (*drawData)(CeOled130* ceOled130, uint8 x, uint8 y, uint8 dataWidth, uint8 dataHight, const uint8* dataBuf);/*!<
                                                         @brief CeOled130显示图片等
                                                         @param ceOled130:CeOled130属性对象
                                                         @param x:设置开始显示32位有符号的数字的x轴坐标
                                                         @param y:设置开始显示32位有符号的数字的y轴坐标（也就是行坐标，范围0-7）
                                                         @param dataWidth:绘制数据或图像的宽（以像素为单位）
                                                         @param dataHightm:绘制数据或图像的高（以字节为单位）
                                                         @param cn1616:要显示的图片数据，有关图片的大小与取模详细部分可查看模块使用手册*/

    void        (*appendString)(CeOled130* ceOled130, const char* msg);/*!<
                                                         @brief 一般用于代码调试，以控制台的方式打印调试信息
                                                         @param ceOled130:CeOled130属性对象
                                                         @param msg:要显示的信息*/

    void        (*setOff)(CeOled130* ceOled130);    /*!< @brief CeOled130关闭显示
                                                         @param ceOled130:CeOled130属性对象指针*/
}CeOled130Op;
/*
 *CeOled130操作对象实例
 */
extern const CeOled130Op ceOled130Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_OLED130_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_OLED130_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 在屏上打印英文和中文汉字
******************************************************************************
#include "Creelinks.h"
#include "CeOled130.h"

const unsigned char CN1616_B4B4[] = //创
{ 0x0C, 0x06, 0x0C, 0x06, 0x1E, 0x06, 0x1B, 0x36, 0x31, 0xB6, 0x60, 0xF6, 0xFF, 0x36, 0x33, 0x36, 0x33, 0x36, 0x33, 0x36, 0x3F, 0x36, 0x36, 0x36, 0x30, 0xC6, 0x30, 0xC6, 0x1F, 0xDE, 0x00, 0x0C };
const unsigned char CN1616_A3E5[] = //ｅ
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x06, 0x60, 0x0C, 0x30, 0x0F, 0xF0, 0x0C, 0x00, 0x0C, 0x00, 0x06, 0x30, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned char CN1616_C1AA[] = //联
{0x00, 0xCC, 0xFE, 0x6C, 0x6C, 0x78, 0x6C, 0x00, 0x7D, 0xFE, 0x6C, 0x30, 0x6C, 0x30, 0x7C, 0x30, 0x6F, 0xFF, 0x6C, 0x30, 0x6E, 0x78, 0x7C, 0x78, 0xEC, 0xCC, 0x0C, 0xCC, 0x0D, 0x86, 0x0F, 0x03};

const unsigned char CN1616_B1B1[] = //北
{0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x66, 0x06, 0x6C, 0x7E, 0x78, 0x06, 0x70, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x63, 0x1E, 0x63, 0xF6, 0x63, 0x66, 0x3F, 0x06, 0x00};
const unsigned char CN1616_BEA9[] = //京
{0x03, 0x00, 0x01, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0xF8, 0x01, 0x80, 0x19, 0x98, 0x19, 0x8C, 0x31, 0x86, 0x67, 0x86, 0x03, 0x00};
const unsigned char CN1616_B4F3[] = //大
{0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0xFF, 0xFF, 0x01, 0x80, 0x01, 0x80, 0x03, 0xC0, 0x03, 0xC0, 0x06, 0x60, 0x06, 0x60, 0x0C, 0x30, 0x18, 0x18, 0x30, 0x0C, 0xE0, 0x07};
const unsigned char CN1616_D0C5[] = //信
{0x0C, 0x60, 0x0C, 0x30, 0x0F, 0xFF, 0x18, 0x00, 0x18, 0x00, 0x39, 0xFE, 0x38, 0x00, 0x78, 0x00, 0xD9, 0xFE, 0x18, 0x00, 0x18, 0x00, 0x19, 0xFE, 0x19, 0x86, 0x19, 0x86, 0x19, 0xFE, 0x19, 0x86};
const unsigned char CN1616_BFC6[] = //科
{0x0C, 0x18, 0x1F, 0x98, 0xF8, 0xD8, 0x18, 0xD8, 0x18, 0x18, 0xFF, 0x98, 0x18, 0xD8, 0x3C, 0xD8, 0x3E, 0x18, 0x78, 0x1F, 0x7B, 0xF8, 0xD8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
const unsigned char CN1616_BCBC[] = //技
{0x18, 0x30, 0x18, 0x30, 0x18, 0x30, 0x1B, 0xFF, 0xFE, 0x30, 0x18, 0x30, 0x18, 0x30, 0x1F, 0xFE, 0x1C, 0xC6, 0x38, 0xCC, 0xF8, 0x6C, 0x18, 0x78, 0x18, 0x30, 0x18, 0x78, 0x79, 0xCC, 0x37, 0x07};

CeOled130 myOled;
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                              //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceOled130Op.initial(&myOled, R2TI2c);
    ceOled130Op.setOn(&myOled);
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceOled130Op.clr(&myOled);
        ceOled130Op.showCN1616(&myOled, 40, 2, CN1616_B4B4);
        ceOled130Op.showCN1616(&myOled, 40 + 16, 2, CN1616_A3E5);
        ceOled130Op.showCN1616(&myOled, 40 + 32, 2, CN1616_C1AA);

        ceOled130Op.showString(&myOled, 28, 4, "CREELINKS", CE_OLED130_EN_SIZE_F8X16);

        ceOled130Op.showCN1616(&myOled, 16*1, 6, CN1616_B1B1);
        ceOled130Op.showCN1616(&myOled, 16*2, 6, CN1616_BEA9);
        ceOled130Op.showCN1616(&myOled, 16*3, 6, CN1616_B4F3);
        ceOled130Op.showCN1616(&myOled, 16*4, 6, CN1616_D0C5);
        ceOled130Op.showCN1616(&myOled, 16*5, 6, CN1616_BFC6);
        ceOled130Op.showCN1616(&myOled, 16*6, 6, CN1616_BCBC);

        ceSystemOp.delayMs(2000);
        ceOled130Op.clr(&myOled);
        //ceOled130Op.drawData();
    };
}
******************************************************************************
*/

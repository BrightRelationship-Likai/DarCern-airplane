/**
  ******************************************************************************
  * @file    CeTft400.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeTft400模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)显示屏驱动芯片为NT35510
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeTft400.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_TFT400_CMD_ADDR      0x60000000      /*!< CeTft400写命令的地址*/
#define CE_TFT400_DATA_ADDR     0x60020000      /*!< CeTft400写数据的地址*/

#define CE_TFT400_PWM_CYCLE     1000000         /*!< CeTft400控制亮度的PWM周期*/

#define CE_TFT320_DEVICE_NT35510    0x8000      /*!< CeTft400控制芯片NT35510的ID*/


#define CE_TFT400_CAN_SET_REGIION               /*!< 如果需要直接操作绘制区域来提高绘制效率，则定义此行*/

#ifdef __CE_USE_RTOS__
#define CE_TFT400_TASK_STACK_BUF_SIZE 1024                  /*!< 使用操作系统时，任务堆栈缓冲区的长度*/
CE_STK ceTft400_taskBuf[CE_TFT400_TASK_STACK_BUF_SIZE];     /*!< 使用操作系统时，为CeTft400分配的任务堆栈缓冲区*/
#endif //__CE_USE_RTOS__

/**
  * @brief  CeTft400用的6*8的点阵
  */
const unsigned char CE_TFT400_F6x8[][6] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // sp
    0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, // !
    0x00, 0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14, // #
    0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
    0x00, 0x62, 0x64, 0x08, 0x13, 0x23, // %
    0x00, 0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, // (
    0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, // )
    0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, // *
    0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x00, 0x00, 0xA0, 0x60, 0x00, // ,
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // /
    0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x00, 0x08, 0x14, 0x22, 0x41, 0x00, // <
    0x00, 0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x00, 0x00, 0x41, 0x22, 0x14, 0x08, // >
    0x00, 0x02, 0x01, 0x51, 0x09, 0x06, // ?
    0x00, 0x32, 0x49, 0x59, 0x51, 0x3E, // @
    0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // A
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, // D
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // F
    0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A, // G
    0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
    0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, // O
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // S
    0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, // W
    0x00, 0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // Y
    0x00, 0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x00, 0x7F, 0x41, 0x41, 0x00, // [
    0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55, // 55
    0x00, 0x00, 0x41, 0x41, 0x7F, 0x00, // ]
    0x00, 0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x00, 0x40, 0x40, 0x40, 0x40, 0x40, // _
    0x00, 0x00, 0x01, 0x02, 0x04, 0x00, // '
    0x00, 0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, // b
    0x00, 0x38, 0x44, 0x44, 0x44, 0x20, // c
    0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, // d
    0x00, 0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, // f
    0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g
    0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x00, 0x40, 0x80, 0x84, 0x7D, 0x00, // j
    0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, // m
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x00, 0x38, 0x44, 0x44, 0x44, 0x38, // o
    0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, // p
    0x00, 0x18, 0x24, 0x24, 0x18, 0xFC, // q
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x00, 0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, // t
    0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x00, 0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y
    0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, // horiz lines
};

/**
  * @brief  CeTft400使用的8*16的点阵
  */
const unsigned char CE_TFT400_F8X16[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0
    0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x30, 0x00, 0x00, 0x00, //! 1
    0x00, 0x10, 0x0C, 0x06, 0x10, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //" 2
    0x40, 0xC0, 0x78, 0x40, 0xC0, 0x78, 0x40, 0x00, 0x04, 0x3F, 0x04, 0x04, 0x3F, 0x04, 0x04, 0x00, //# 3
    0x00, 0x70, 0x88, 0xFC, 0x08, 0x30, 0x00, 0x00, 0x00, 0x18, 0x20, 0xFF, 0x21, 0x1E, 0x00, 0x00, //$ 4
    0xF0, 0x08, 0xF0, 0x00, 0xE0, 0x18, 0x00, 0x00, 0x00, 0x21, 0x1C, 0x03, 0x1E, 0x21, 0x1E, 0x00, //% 5
    0x00, 0xF0, 0x08, 0x88, 0x70, 0x00, 0x00, 0x00, 0x1E, 0x21, 0x23, 0x24, 0x19, 0x27, 0x21, 0x10, //& 6
    0x10, 0x16, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //' 7
    0x00, 0x00, 0x00, 0xE0, 0x18, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x18, 0x20, 0x40, 0x00, //( 8
    0x00, 0x02, 0x04, 0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x18, 0x07, 0x00, 0x00, 0x00, //) 9
    0x40, 0x40, 0x80, 0xF0, 0x80, 0x40, 0x40, 0x00, 0x02, 0x02, 0x01, 0x0F, 0x01, 0x02, 0x02, 0x00, //* 10
    0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x1F, 0x01, 0x01, 0x01, 0x00, //+ 11
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xB0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, //, 12
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, //- 13
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, //. 14
    0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x04, 0x00, 0x60, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00, /// 15
    0x00, 0xE0, 0x10, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x00, 0x0F, 0x10, 0x20, 0x20, 0x10, 0x0F, 0x00, //0 16
    0x00, 0x10, 0x10, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00, //1 17
    0x00, 0x70, 0x08, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00, 0x30, 0x28, 0x24, 0x22, 0x21, 0x30, 0x00, //2 18
    0x00, 0x30, 0x08, 0x88, 0x88, 0x48, 0x30, 0x00, 0x00, 0x18, 0x20, 0x20, 0x20, 0x11, 0x0E, 0x00, //3 19
    0x00, 0x00, 0xC0, 0x20, 0x10, 0xF8, 0x00, 0x00, 0x00, 0x07, 0x04, 0x24, 0x24, 0x3F, 0x24, 0x00, //4 20
    0x00, 0xF8, 0x08, 0x88, 0x88, 0x08, 0x08, 0x00, 0x00, 0x19, 0x21, 0x20, 0x20, 0x11, 0x0E, 0x00, //5 21
    0x00, 0xE0, 0x10, 0x88, 0x88, 0x18, 0x00, 0x00, 0x00, 0x0F, 0x11, 0x20, 0x20, 0x11, 0x0E, 0x00, //6 22
    0x00, 0x38, 0x08, 0x08, 0xC8, 0x38, 0x08, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, //7 23
    0x00, 0x70, 0x88, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00, 0x1C, 0x22, 0x21, 0x21, 0x22, 0x1C, 0x00, //8 24
    0x00, 0xE0, 0x10, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x00, 0x00, 0x31, 0x22, 0x22, 0x11, 0x0F, 0x00, //9 25
    0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, //: 26
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x00, 0x00, 0x00, 0x00, //; 27
    0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, //< 28
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, //= 29
    0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, //> 30
    0x00, 0x70, 0x48, 0x08, 0x08, 0x08, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x36, 0x01, 0x00, 0x00, //? 31
    0xC0, 0x30, 0xC8, 0x28, 0xE8, 0x10, 0xE0, 0x00, 0x07, 0x18, 0x27, 0x24, 0x23, 0x14, 0x0B, 0x00, //@ 32
    0x00, 0x00, 0xC0, 0x38, 0xE0, 0x00, 0x00, 0x00, 0x20, 0x3C, 0x23, 0x02, 0x02, 0x27, 0x38, 0x20, //A 33
    0x08, 0xF8, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x20, 0x3F, 0x20, 0x20, 0x20, 0x11, 0x0E, 0x00, //B 34
    0xC0, 0x30, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00, 0x07, 0x18, 0x20, 0x20, 0x20, 0x10, 0x08, 0x00, //C 35
    0x08, 0xF8, 0x08, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x20, 0x3F, 0x20, 0x20, 0x20, 0x10, 0x0F, 0x00, //D 36
    0x08, 0xF8, 0x88, 0x88, 0xE8, 0x08, 0x10, 0x00, 0x20, 0x3F, 0x20, 0x20, 0x23, 0x20, 0x18, 0x00, //E 37
    0x08, 0xF8, 0x88, 0x88, 0xE8, 0x08, 0x10, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x03, 0x00, 0x00, 0x00, //F 38
    0xC0, 0x30, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x07, 0x18, 0x20, 0x20, 0x22, 0x1E, 0x02, 0x00, //G 39
    0x08, 0xF8, 0x08, 0x00, 0x00, 0x08, 0xF8, 0x08, 0x20, 0x3F, 0x21, 0x01, 0x01, 0x21, 0x3F, 0x20, //H 40
    0x00, 0x08, 0x08, 0xF8, 0x08, 0x08, 0x00, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00, //I 41
    0x00, 0x00, 0x08, 0x08, 0xF8, 0x08, 0x08, 0x00, 0xC0, 0x80, 0x80, 0x80, 0x7F, 0x00, 0x00, 0x00, //J 42
    0x08, 0xF8, 0x88, 0xC0, 0x28, 0x18, 0x08, 0x00, 0x20, 0x3F, 0x20, 0x01, 0x26, 0x38, 0x20, 0x00, //K 43
    0x08, 0xF8, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x30, 0x00, //L 44
    0x08, 0xF8, 0xF8, 0x00, 0xF8, 0xF8, 0x08, 0x00, 0x20, 0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x20, 0x00, //M 45
    0x08, 0xF8, 0x30, 0xC0, 0x00, 0x08, 0xF8, 0x08, 0x20, 0x3F, 0x20, 0x00, 0x07, 0x18, 0x3F, 0x00, //N 46
    0xE0, 0x10, 0x08, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x0F, 0x10, 0x20, 0x20, 0x20, 0x10, 0x0F, 0x00, //O 47
    0x08, 0xF8, 0x08, 0x08, 0x08, 0x08, 0xF0, 0x00, 0x20, 0x3F, 0x21, 0x01, 0x01, 0x01, 0x00, 0x00, //P 48
    0xE0, 0x10, 0x08, 0x08, 0x08, 0x10, 0xE0, 0x00, 0x0F, 0x18, 0x24, 0x24, 0x38, 0x50, 0x4F, 0x00, //Q 49
    0x08, 0xF8, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x03, 0x0C, 0x30, 0x20, //R 50
    0x00, 0x70, 0x88, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x38, 0x20, 0x21, 0x21, 0x22, 0x1C, 0x00, //S 51
    0x18, 0x08, 0x08, 0xF8, 0x08, 0x08, 0x18, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x00, 0x00, //T 52
    0x08, 0xF8, 0x08, 0x00, 0x00, 0x08, 0xF8, 0x08, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x20, 0x1F, 0x00, //U 53
    0x08, 0x78, 0x88, 0x00, 0x00, 0xC8, 0x38, 0x08, 0x00, 0x00, 0x07, 0x38, 0x0E, 0x01, 0x00, 0x00, //V 54
    0xF8, 0x08, 0x00, 0xF8, 0x00, 0x08, 0xF8, 0x00, 0x03, 0x3C, 0x07, 0x00, 0x07, 0x3C, 0x03, 0x00, //W 55
    0x08, 0x18, 0x68, 0x80, 0x80, 0x68, 0x18, 0x08, 0x20, 0x30, 0x2C, 0x03, 0x03, 0x2C, 0x30, 0x20, //X 56
    0x08, 0x38, 0xC8, 0x00, 0xC8, 0x38, 0x08, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x00, 0x00, //Y 57
    0x10, 0x08, 0x08, 0x08, 0xC8, 0x38, 0x08, 0x00, 0x20, 0x38, 0x26, 0x21, 0x20, 0x20, 0x18, 0x00, //Z 58
    0x00, 0x00, 0x00, 0xFE, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x40, 0x40, 0x40, 0x00, //[ 59
    0x00, 0x0C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x38, 0xC0, 0x00, //\ 60
    0x00, 0x02, 0x02, 0x02, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x7F, 0x00, 0x00, 0x00, //] 61
    0x00, 0x00, 0x04, 0x02, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //^ 62
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, //_ 63
    0x00, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //` 64
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x19, 0x24, 0x22, 0x22, 0x22, 0x3F, 0x20, //a 65
    0x08, 0xF8, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x11, 0x20, 0x20, 0x11, 0x0E, 0x00, //b 66
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x0E, 0x11, 0x20, 0x20, 0x20, 0x11, 0x00, //c 67
    0x00, 0x00, 0x00, 0x80, 0x80, 0x88, 0xF8, 0x00, 0x00, 0x0E, 0x11, 0x20, 0x20, 0x10, 0x3F, 0x20, //d 68
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x1F, 0x22, 0x22, 0x22, 0x22, 0x13, 0x00, //e 69
    0x00, 0x80, 0x80, 0xF0, 0x88, 0x88, 0x88, 0x18, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00, //f 70
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x6B, 0x94, 0x94, 0x94, 0x93, 0x60, 0x00, //g 71
    0x08, 0xF8, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x20, 0x3F, 0x21, 0x00, 0x00, 0x20, 0x3F, 0x20, //h 72
    0x00, 0x80, 0x98, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00, //i 73
    0x00, 0x00, 0x00, 0x80, 0x98, 0x98, 0x00, 0x00, 0x00, 0xC0, 0x80, 0x80, 0x80, 0x7F, 0x00, 0x00, //j 74
    0x08, 0xF8, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x20, 0x3F, 0x24, 0x02, 0x2D, 0x30, 0x20, 0x00, //k 75
    0x00, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x3F, 0x20, 0x20, 0x00, 0x00, //l 76
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x20, 0x3F, 0x20, 0x00, 0x3F, 0x20, 0x00, 0x3F, //m 77
    0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x20, 0x3F, 0x21, 0x00, 0x00, 0x20, 0x3F, 0x20, //n 78
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x20, 0x1F, 0x00, //o 79
    0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xA1, 0x20, 0x20, 0x11, 0x0E, 0x00, //p 80
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x0E, 0x11, 0x20, 0x20, 0xA0, 0xFF, 0x80, //q 81
    0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x20, 0x20, 0x3F, 0x21, 0x20, 0x00, 0x01, 0x00, //r 82
    0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x33, 0x24, 0x24, 0x24, 0x24, 0x19, 0x00, //s 83
    0x00, 0x80, 0x80, 0xE0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x20, 0x00, 0x00, //t 84
    0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x10, 0x3F, 0x20, //u 85
    0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x01, 0x0E, 0x30, 0x08, 0x06, 0x01, 0x00, //v 86
    0x80, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x80, 0x0F, 0x30, 0x0C, 0x03, 0x0C, 0x30, 0x0F, 0x00, //w 87
    0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x20, 0x31, 0x2E, 0x0E, 0x31, 0x20, 0x00, //x 88
    0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x81, 0x8E, 0x70, 0x18, 0x06, 0x01, 0x00, //y 89
    0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x21, 0x30, 0x2C, 0x22, 0x21, 0x30, 0x00, //z 90
    0x00, 0x00, 0x00, 0x00, 0x80, 0x7C, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x40, 0x40, //{ 91
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, //| 92
    0x00, 0x02, 0x02, 0x7C, 0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x3F, 0x00, 0x00, 0x00, 0x00, //} 93
    0x00, 0x06, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //~ 94
};

CeTft400* ceTft400_ceTft400 = CE_NULL;//用于保存唯一的一个使用L36接口的LCD模块指针
void ceTft400_fill( uint16 color);

/**
  * @brief  获取触摸屏按下的点的坐标
  * @param  pX:存放x轴坐标值的int32指针
  * @param  pY:存放y轴坐标值的int32指针
  * @return None
  */
void ceTft400_getTouchPix(int32* pX, int32* pY)
{
    uint16 temp = 0;
    ceGpioOp.setBit(&(ceTft400_ceTft400->ceL36.ceGpioEx1));//字模片选拉高
    ceSpiMasterOp.resetNSSBit(&(ceTft400_ceTft400->ceL36.ceSpiMaster));
    //while(ceL36Op.getBitEx0() == 0x00);//保留

    ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster), 0x90);//读取Y坐标指令
    ceSystemOp.delayUs(6);
    temp = ((ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster),0x00) & 0xFFFF) << 8);
    temp |= (ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster),0x00) & 0xFF);
    temp  >>= 3;//因为最高位无效，从第二位才是有效数据(看时序图和参考相关代码所知)，所有只需要右移3位
#ifdef CE_TFT400_SHOW_HORIZONTAL
    *pX = (temp / 5);
#else
    *pY = (temp / 5);
#endif

    temp = 0;
    ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster), 0xD0);//读取X坐标指令
    ceSystemOp.delayUs(6);
    temp = ((ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster),0x00) & 0xFFFF) << 8);
    temp |= (ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster),0x00) & 0xFF);
    temp  >>= 3;//因为最高位无效，从第二位才是有效数据(看时序图和参考相关代码所知)，所有只需要右移3位
#ifdef CE_TFT400_SHOW_HORIZONTAL
    *pY = ((temp / 8));
#else
    *pX = (CE_TFT400_WIDTH - (temp / 8));
#endif


    ceSpiMasterOp.setNSSBit(&(ceTft400_ceTft400->ceL36.ceSpiMaster));
}

/**
  * @brief  周期检测是否按下触摸屏
  * @param  pAddPar:CeTft400对象指针
  * @return None
  */
void ceTft400_callBackTouch(void* pAddPar)
{
    if(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x00)//没有按下按钮
    {
        CeTft400* ceTft400 = (CeTft400*)(pAddPar);
        if(ceTft400->callBackTouch != CE_NULL)
        {
            if(ceTft400->isInCalibration == 0x00)
            {
                int32 xVal1 = 0, yVal1 = 0, xVal2 = 0, yVal2 = 0;
                int i;
                for(i = 0; i < 10; i++)
                {
                    int32 tX = 0, tY = 0;
                    ceTft400_getTouchPix(&tX, &tY);
                    xVal1 += tX;
                    yVal1 += tY;
                }
                xVal1 /= 10;
                yVal1 /= 10;
                xVal2 = (xVal1 - ceTft400_ceTft400->clbTempX[1]) / (ceTft400_ceTft400->clbTempX[0]) + CE_TFT400_WIDTH / 2; //在这里校准
                yVal2 = (yVal1 - ceTft400_ceTft400->clbTempY[1]) / (ceTft400_ceTft400->clbTempY[0]) + CE_TFT400_HIGHT / 2; //在这里校准
                if(xVal2 < 0)
                {
                    xVal2 = 0;
                }
                if(xVal2 > CE_TFT400_WIDTH)
                {
                    xVal2 = CE_TFT400_WIDTH - 1;
                }
                if(yVal2 < 0)
                {
                    yVal2 = 0;
                }
                if(yVal2 > CE_TFT400_HIGHT)
                {
                    yVal2 = CE_TFT400_HIGHT - 1;
                }
                ceTft400->callBackTouch((int16)xVal2, (int16)yVal2);
                //ceDebugOp.printf("X:%d  Y:%d\n",xVal2,yVal2);
            }
        }
    }
#ifdef __CE_USE_RTOS__
    ceSystemOp.delayMs(50);
#endif
}

/**
  * @brief  CeTft400模块初始化
  * @param  ceXX:CeTft400模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceTft400_tftInitial(void)
{
    uint16 i, j;
    for(j = 0; j < CE_TFT400_WIDTH / 6; j++)
    {
        for(i = 0; i < CE_TFT400_HIGHT / 8; i++)
        {
            ceTft400_ceTft400->asBuf[j][i] = ' ';
        }
    }
    ceTft400_ceTft400->asXIndex = 0;
    ceTft400_ceTft400->asYIndex = 0;

    //可以从Flash/Eeprom中读取这四个参数
    ceTft400_ceTft400->clbTempX[0] = 1;
    ceTft400_ceTft400->clbTempX[1] = CE_TFT400_WIDTH / 2;

    ceTft400_ceTft400->clbTempY[0] = 1;
    ceTft400_ceTft400->clbTempY[1] = CE_TFT400_HIGHT / 2;

    ceTft400_ceTft400->isInCalibration = 0x00;

    ceL36Op.setRST();
    ceSystemOp.delayMs(10);
    ceL36Op.resetRST();
    ceSystemOp.delayMs(10);
    ceL36Op.setRST();
    ceSystemOp.delayMs(10);

    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x0400);//Read Display ID(0400h)
    CE_L36_READ_DATA(CE_TFT400_DATA_ADDR);//0x0000

    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xDA00);//the module’s manufacture ID
    CE_L36_READ_DATA(CE_TFT400_DATA_ADDR);//0x0000

    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xDB00);//the module/driver version ID.
    ceTft400_ceTft400->deviceCode = CE_L36_READ_DATA(CE_TFT400_DATA_ADDR);//0x80
    ceTft400_ceTft400->deviceCode <<= 8;

    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xDC00);//the module/driver ID.
    ceTft400_ceTft400->deviceCode |= CE_L36_READ_DATA(CE_TFT400_DATA_ADDR);//0x00

    if (ceTft400_ceTft400->deviceCode == CE_TFT320_DEVICE_NT35510)
    {
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf000);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0055);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf001);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00aa);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf002);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0052);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf003);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0008);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf004);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbc01);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0086);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbc02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x006a);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbd01);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0086);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbd02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x006a);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbe01);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0067);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd100);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd101);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x005d);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd102);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd103);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x006b);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd104);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd105);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0084);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd106);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd107);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x009c);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd108);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd109);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b1);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd10a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd10b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00d9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd10c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd10d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fd);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd10e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd10f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0038);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd110);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd111);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0068);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd112);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd113);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd114);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd115);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd116);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd117);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0063);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd118);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd119);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd11a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd11b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00bb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd11c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd11d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd11e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd11f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0046);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd120);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd121);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0069);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd122);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd123);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x008f);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd124);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd125);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00a4);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd126);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd127);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd128);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd129);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c7);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd12a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd12b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd12c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd12d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd12e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd12f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd130);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd131);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd132);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd133);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cc);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd200);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd201);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x005d);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd202);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd203);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x006b);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd204);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd205);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0084);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd206);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd207);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x009c);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd208);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd209);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b1);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd20a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd20b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00d9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd20c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd20d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fd);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd20e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd20f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0038);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd210);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd211);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0068);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd212);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd213);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd214);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd215);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd216);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd217);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0063);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd218);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd219);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd21a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd21b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00bb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd21c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd21d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd21e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd21f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0046);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd220);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd221);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0069);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd222);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd223);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x008f);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd224);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd225);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00a4);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd226);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd227);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd228);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd229);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c7);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd22a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd22b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd22c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd22d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd22e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd22f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd230);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd231);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd232);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd233);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cc);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd300);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd301);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x005d);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd302);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd303);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x006b);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd304);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd305);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0084);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd306);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd307);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x009c);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd308);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd309);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b1);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd30a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd30b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00d9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd30c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd30d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fd);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd30e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd30f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0038);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd310);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd311);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0068);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd312);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd313);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd314);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd315);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd316);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd317);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0063);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd318);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd319);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd31a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd31b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00bb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd31c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd31d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd31e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd31f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0046);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd320);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd321);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0069);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd322);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd323);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x008f);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd324);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd325);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00a4);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd326);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd327);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd328);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd329);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c7);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd32a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd32b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd32c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd32d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd32e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd32f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd330);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd331);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd332);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd333);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cc);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd400);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd401);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x005d);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd402);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd403);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x006b);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd404);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd405);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0084);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd406);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd407);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x009c);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd408);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd409);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b1);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd40a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd40b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00d9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd40c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd40d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fd);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd40e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd40f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0038);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd410);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd411);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0068);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd412);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd413);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd414);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd415);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd416);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd417);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0063);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd418);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd419);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd41a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd41b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00bb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd41c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd41d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd41e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd41f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0046);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd420);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd421);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0069);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd422);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd423);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x008f);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd424);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd425);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00a4);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd426);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd427);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd428);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd429);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c7);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd42a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd42b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd42c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd42d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd42e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd42f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd430);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd431);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd432);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd433);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cc);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd500);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd501);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x005d);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd502);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd503);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x006b);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd504);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd505);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0084);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd506);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd507);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x009c);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd508);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd509);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b1);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd50a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd50b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00D9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd50c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd50d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fd);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd50e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd50f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0038);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd510);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd511);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0068);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd512);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd513);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd514);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd515);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd516);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd517);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0063);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd518);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd519);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd51a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd51b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00bb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd51c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd51d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd51e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd51f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0046);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd520);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd521);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0069);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd522);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd523);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x008f);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd524);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd525);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00a4);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd526);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd527);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd528);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd529);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c7);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd52a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd52b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd52c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd52d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd52e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd52f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd530);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd531);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd532);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd533);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cc);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd600);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd601);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x005d);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd602);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd603);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x006b);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd604);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd605);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0084);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd606);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd607);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x009c);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd608);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd609);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b1);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd60a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd60b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00d9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd60c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd60d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fd);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd60e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd60f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0038);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd610);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd611);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0068);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd612);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd613);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd614);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd615);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00fb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd616);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd617);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0063);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd618);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd619);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd61a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd61b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00bb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd61c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd61d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd61e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd61f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0046);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd620);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd621);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0069);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd622);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd623);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x008f);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd624);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd625);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00a4);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd626);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd627);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00b9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd628);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd629);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c7);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd62a);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd62b);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00c9);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd62c);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd62d);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd62e);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd62f);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd630);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd631);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cb);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd632);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xd633);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cc);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xba00);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0024);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xba01);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0024);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xba02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0024);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xb900);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0024);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xb901);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0024);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xb902);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0024);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf000);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0055);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf001);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00aa);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf002);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0052);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf003);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0008);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf004);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xb100);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00cc);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbc00);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0005);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbc01);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0005);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbc02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0005);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xb800);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xb801);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xb802);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xb803);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbd02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0007);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbd03);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0031);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbe02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0007);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbe03);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0031);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbf02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0007);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xbf03);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0031);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xff00);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00aa);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xff01);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0055);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xff02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0025);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xff03);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf304);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0011);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf306);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0010);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0xf308);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x3500);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2a00);//Column Address Set
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2a01);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2a02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2a03);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x00df);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2b00);//Row Address Set
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2b01);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2b02);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2b03);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x001f);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x1100);//Sleep Out
        ceSystemOp.delayUs(120);



        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2900);//Display On

        //CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2C00);//Memory Write
        ceSystemOp.delayUs(10);

        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x3A00);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0055);
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x3600);

#ifndef CE_TFT400_SHOW_HORIZONTAL
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0008);//竖屏，从右上角开始，从右到左，从上到下(注意:D5-D7和方向也有关系，具体看Datasheet)
#else
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x078);//横屏，从左上角开始，从左到右，从上到下(注意:D5-D7和方向也有关系，具体看Datasheet)
#endif
        CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x00F0);
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, 0x0003);
        ceTft400_fill(CE_TFT400_COLOR_BLACK);
    }
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  设置绘制区域
  * @param  startX:矩形左上角x坐标
  * @param  startY:矩形左上角y坐标
  * @param  endX:矩形右下角x坐标
  * @param  endY:矩形右下角y坐标
  * @return None
  */
void ceTft400_setRegion(int16 startX, int16 startY, int16 endX, int16 endY)
{
    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2a00);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, startX >> 8);
    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2a01);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, startX & 0xff);
    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2a02);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, endX >> 8);
    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2a03);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, endX & 0xff);

    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2b00);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, startY >> 8);
    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2b01);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, startY & 0xff);
    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2b02);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, endY >> 8);
    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2b03);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, endY & 0xff);

    CE_L36_WRITE_DATA(CE_TFT400_CMD_ADDR, 0x2c00);
}

/**
  * @brief  CeTft400在指定位置画点
  * @param  x:设置开始显示字符串的x轴坐标
  * @param  y:设置开始显示字符串的y轴坐标
  * @param  color:要显示的数据(颜色)
  * @return None
  */
void ceTft400_drawPoint(int16 x, int16 y, uint16 color)
{
    if (x < 0 || y < 0)
    {
        return;
    }
    if (x > CE_TFT400_WIDTH || y > CE_TFT400_HIGHT)
    {
        return;
    }
    ceTft400_setRegion(x, y, x, y);
    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, color);
}

/**
  * @brief  CeTft400绘制矩形
  * @param  startX:矩形左上角x坐标
  * @param  startY:矩形左上角y坐标
  * @param  endX:矩形右下角x坐标
  * @param  endY:矩形右下角y坐标
  * @param  color:要显示的数据(颜色)
  * @return None
  */
void ceTft400_drawRectangle(uint16 startX, uint16 startY, uint16 endX, uint16 endY, int16 color)
{
    int i, j;
    if(startX > endX || startY > endY)
    {
        return;
    }
    if(endX >= CE_TFT400_WIDTH)
    {
        endX = CE_TFT400_WIDTH - 1;
    }
    if(endY > CE_TFT400_HIGHT)
    {
        endY = CE_TFT400_HIGHT - 1;
    }

#ifdef CE_TFT400_CAN_SET_REGIION
    ceTft400_setRegion(startX, startY, endX, endY);
    endX++;
    endY++;
    for(i = startY; i < endY; i++)
    {
        for(j = startX; j < endX; j++)
        {
            CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, color);
        }
    }
#else
    endX++;
    endY++;
    for(i = startY; i < endY; i++)
    {
        for(j = startX; j < endX; j++)
        {
            ceTft400_drawPoint(i, j, color);
        }
    }
#endif
}

/**
  * @brief  CeTft400显示字符
  * @param  x:设置开始显示字符的x轴坐标
  * @param  y:设置开始显示字符的y轴坐标
  * @param  foreColor:显示字体的前景色
  * @param  backColor:显示字体的背景色
  * @param  msg:要显示的字符串指针
  * @param showSize:显示的字体大小，可选CE_TFT400_EN_SIZE_F6X8或CE_TFT400_EN_SIZE_F8X16
  * @return None
  */
void ceTft400_showChar(int16 x, int16 y, uint16 foreColor, uint16 backColor, const char ch, CE_TFT400_EN_SIZE showSize)
{
#ifdef CE_TFT400_CAN_SET_REGIION
    if(showSize == CE_TFT400_EN_SIZE_F6X8)
    {
        uint16  i, j, c, index;
        c = ch - 32;
        ceTft400_setRegion(x,  y, x + 6 - 1, y + 8 - 1);
        index = 0x01;
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 6; j++)
            {
                if((CE_TFT400_F6x8[c][j] & index) == index)
                {
                    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, foreColor);
                }
                else
                {
                    CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, backColor);
                }
            }
            index <<= 1;
        }
    }
    else
    {
        uint8 i, j, c, m, index;
        c = ch - 32;
        ceTft400_setRegion(x,  y, x + 8 - 1, y + 16 - 1);
        for(i = 0; i < 2; i++)
        {
            index = 0x01;
            for(j = 0; j < 8; j++)
            {
                for(m = 0; m < 8; m++)
                {
                    if((CE_TFT400_F8X16[c * 16 + i * 8 + m] & index) == index)
                    {
                        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, foreColor);
                    }
                    else
                    {
                        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, backColor);
                    }
                }
                index <<= 1;
            }
        }
    }
#else
    uint16  j, m, n, c, temp, index;
    c = ch - 32;
    if(showSize == CE_TFT400_EN_SIZE_F6X8)
    {
        ceTft400_setRegion(x,  y, x + 6 - 1, y + 8 - 1);
        for(j = 0; j < 6; j++)
        {
            temp = CE_TFT400_F6x8[c][j];
            index = 0x01;
            for(m = 0; m < 8; m++)
            {
                if((temp & index) == index)
                {
                    ceTft400_drawPoint(x + j, y + m, foreColor);
                }
                else
                {
                    ceTft400_drawPoint(x + j, y + m, backColor);
                }
                index <<= 1;
            }
        }
        x += 6;
    }
    else
    {
        ceTft400_setRegion(x, y, x + 8 - 1, y + 16 - 1);
        for(j = 0; j < 2; j++)
        {
            for(m = 0; m < 8; m++)
            {
                temp = CE_TFT400_F8X16[c * 16 + j * 8 + m];
                index = 0x01;
                for(n = 0; n < 8; n++)
                {
                    if((temp & index) == index)
                    {
                        ceTft400_drawPoint(x + m, y + n + j * 8, foreColor);
                    }
                    else
                    {
                        ceTft400_drawPoint(x + m, y + n + j * 8, backColor);
                    }
                    index <<= 1;
                }
            }
        }
        x += 8;
    }
#endif
}

/**
  * @brief  CeTft400显示字符串，不支持中文
  * @param  x:设置开始显示字符串的x轴坐标
  * @param  y:设置开始显示字符串的y轴坐标
  * @param  foreColor:显示字体的前景色
  * @param  backColor:显示字体的背景色
  * @param  msg:要显示的字符串指针
  * @param showSize:显示的字体大小，可选CE_TFT400_EN_SIZE_F6X8或CE_TFT400_EN_SIZE_F8X16
  * @return None
  */
void ceTft400_showString(int16 x, int16 y, uint16 foreColor, uint16 backColor, const char* msg, CE_TFT400_EN_SIZE showSize)
{
    uint16 i, count;
    count = ceStringOp.strlen(msg);
    for(i = 0; i < count; i++)
    {
        ceTft400_showChar(x + i * ((showSize == CE_TFT400_EN_SIZE_F6X8) ? 6 : 8), y, foreColor, backColor, msg[i], showSize);
    }
}

/**
  * @brief  CeTft400显示16x16的中文字体，字模cn1616可从CeCN1616.h中获取
  * @param  x:设置开始显示字符串的x轴坐标
  * @param  y:设置开始显示字符串的y轴坐标
  * @param  foreColor:显示字体的前景色
  * @param  backColor:显示字体的背景色
  * @param  cn1616:要显示的文字模，字模cn1616可从CeCN1616.h中获取
  * @return None
  */
void ceTft400_showCN1616(int16 x, int16 y, uint16 foreColor, uint16 backColor, const uint8* cn1616)
{
#ifdef CE_TFT400_CAN_SET_REGIION
    int i, j;
    uint8 index;
    ceTft400_setRegion(x, y, x + 16 - 1, y + 16 - 1);
    for (i = 0; i < 32; i++)
    {
        index = 0x80;
        for (j = 0; j < 8; j++)
        {
            if ((cn1616[i] & index) == index)
            {
                CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, backColor);
            }
            else
            {
                CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, foreColor);
            }
            index >>= 1;
        }
    }
#else
    int i, j, m, temp;
    for (j = 0; j < 16; j++)
    {
        for (i = 0; i < 2; i++)
        {
            temp = cn1616[j * 2 + i];
            for (m = 0; m < 8; m++)
            {
                if ((temp & 0x80) == 0x80)
                {
                    ceTft400_drawPoint(x + i * 8 + m, j + y, backColor);
                }
                else
                {
                    ceTft400_drawPoint(x + i * 8 + m, j + y, foreColor);
                }
                temp <<= 1;
            }
        }
    }
#endif
}

/**
  * @brief  CeTft400显示32位有符号的数字，最大值0x7FFFFFFF，最小值0x80000001
  * @param  x:设置开始显示32位有符号的数字的x轴坐标
  * @param  y:设置开始显示32位有符号的数字的y轴坐标
  * @param  foreColor:显示字体的前景色
  * @param  backColor:显示字体的背景色
  * @param val:要显示的32位有符号的数字
  * @param showSize:显示的字体大小，可选CE_TFT400_EN_SIZE_F6X8或CE_TFT400_EN_SIZE_F8X16
  * @return None
  */
void ceTft400_showInt(int16 x, int16 y, uint16 foreColor, uint16 backColor, const int32 val, CE_TFT400_EN_SIZE showSize)
{
    char temp[20];
    ceDebugOp.sprintf(temp, "%d", val);
    ceTft400_showString(x, y, foreColor, backColor, temp, showSize);
}

/**
  * @brief  一般用于代码调试，以控制台的方式打印调试信息
  * @param  msg:要显示的信息
  * @return None
  */
void ceTft400_appendString(const char* msg)
{
    uint16 msgCoung = ceStringOp.strlen(msg);
    uint16 i, j;
    for(i = 0; i < msgCoung + 1; i++)
    {
        if(msg[i] == '\r' || msg[i] == '\n')
        {
            for(j = ceTft400_ceTft400->asXIndex; j < CE_TFT400_WIDTH / 6; j++)
            {
                ceTft400_ceTft400->asBuf[j][ceTft400_ceTft400->asYIndex] = ' ';
            }
            ceTft400_ceTft400->asXIndex = 0;
            ceTft400_ceTft400->asYIndex++;
            if(ceTft400_ceTft400->asYIndex >= CE_TFT400_HIGHT / 8)
            {
                uint16 m, n;
                for(m = 0; m < CE_TFT400_HIGHT / 8 - 1; m++)
                {
                    for(n = 0; n < CE_TFT400_WIDTH / 6; n++)
                    {
                        ceTft400_ceTft400->asBuf[n][m] = ceTft400_ceTft400->asBuf[n][m + 1];
                    }
                }
                for(n = 0; n < CE_TFT400_WIDTH / 6; n++)
                {
                    ceTft400_ceTft400->asBuf[n][CE_TFT400_HIGHT / 8 - 1] = ' ';
                }
                ceTft400_ceTft400->asYIndex--;
            }
        }
        else if(msg[i] == '\0')
        {
            break;
        }
        else
        {
            ceTft400_ceTft400->asBuf[ceTft400_ceTft400->asXIndex][ceTft400_ceTft400->asYIndex] = msg[i];
            ceTft400_ceTft400->asXIndex++;
            if(ceTft400_ceTft400->asXIndex >= CE_TFT400_WIDTH / 6)
            {
                ceTft400_ceTft400->asXIndex = 0;
                ceTft400_ceTft400->asYIndex++;
                if(ceTft400_ceTft400->asYIndex >= CE_TFT400_HIGHT / 8)
                {
                    uint16 m, n;
                    for(m = 0; m < CE_TFT400_HIGHT / 8 - 1; m++)
                    {
                        for(n = 0; n < CE_TFT400_WIDTH / 6; n++)
                        {
                            ceTft400_ceTft400->asBuf[n][m] = ceTft400_ceTft400->asBuf[n][m + 1];
                        }
                    }
                    for(n = 0; n < CE_TFT400_WIDTH / 6; n++)
                    {
                        ceTft400_ceTft400->asBuf[n][CE_TFT400_HIGHT / 8 - 1] = ' ';
                    }
                    ceTft400_ceTft400->asYIndex--;
                }
            }
        }
    }
    for(i = 0; i < CE_TFT400_HIGHT / 8; i++)
    {
        for(j = 0; j < CE_TFT400_WIDTH / 6; j++)
        {
            ceTft400_showChar(j * 6, i * 8, CE_TFT400_COLOR_YELLOW, CE_TFT400_COLOR_BLACK, ceTft400_ceTft400->asBuf[j][i], CE_TFT400_EN_SIZE_F6X8);
        }
    }
}

/**
  * @brief  CeTft400用指定数据(颜色)进行全屏填充
  * @param  color:全屏填充的数据(颜色)
  * @return None
  */
void ceTft400_fill( uint16 color)
{
    int i, j;
    ceTft400_setRegion(0, 0, CE_TFT400_WIDTH - 1, CE_TFT400_HIGHT - 1);
    
    for(i = 0; i < CE_TFT400_WIDTH; i++)
    {
        for(j = 0; j < CE_TFT400_HIGHT; j++)
        {
            CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, color);
        }
    }
}

/**
  * @brief  CeTft400绘制图片
  * @param  x:图片的起始点x坐标
  * @param  y:图片的起始点y坐标
  * @param  colorBuf:图片数据
  * @param  bufSizeWidth:图片宽
  * @param  bufSizeHight:图片高
  * @return None
  */
void ceTft400_drawData(uint16 x, uint16 y, const uint8* colorBuf, uint16 bufSizeWidth, uint16 bufSizeHight)
{
#ifdef CE_TFT400_CAN_SET_REGIION
    uint32 i;
    uint32 lgh = bufSizeHight * bufSizeWidth * 2;
    ceTft400_setRegion(x, y, x + bufSizeWidth - 1, y + bufSizeHight - 1);
    for(i = 0; i < lgh; i += 2)
    {
        CE_L36_WRITE_DATA(CE_TFT400_DATA_ADDR, (colorBuf[i]) | (uint16)(colorBuf[i + 1] << 8));
    }
#else
    int i, j;
    ceTft400_setRegion(x, y, x + bufSizeWidth - 1, y + bufSizeHight - 1);
    for(j = 0; j < bufSizeHight; j++)
    {
        for(i = 0; i < bufSizeWidth; i++)
        {
            uint16 temp = (uint16)colorBuf[(j * bufSizeWidth + i) * 2 + 1] << 8 | colorBuf[(j * bufSizeWidth + i) * 2];
            ceTft400_drawPoint(x + i, y + j, temp);
        }
    }
#endif
}

/**
  * @brief  打开显示
  * @return None
  */
void ceTft400_setOn(void)
{
    cePwmOp.start(&(ceTft400_ceTft400->ceL36.cePwm));
}

/**
  * @brief  校准触摸屏，可以校准完成后，将校准结果保存到Flash/Eeprom中，在初始化时载入
  * @return 校准成功返回 CE_STATUS_SUCCESS，校准失败返回 CE_STATUS_FAILE
  */
CE_STATUS ceTft400_calibration(void)
{
    int32 tempX[5] = {0, 0, 0, 0, 0};
    int32 tempY[5] = {0, 0, 0, 0, 0};
    ceTft400_ceTft400->isInCalibration = 0x01;
    ceTft400_fill(CE_TFT400_COLOR_BLACK);

    ceTft400_drawRectangle(30 - 5, 30 - 5, 30 + 5, 30 + 5, CE_TFT400_COLOR_RED); //在30，30处画加号
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x01)          //等待用户点击屏幕
        ceSystemOp.delayMs(10);
    ceTft400_getTouchPix(&(tempX[1]), &(tempY[1]));
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x00)          //等待用户释放屏幕
        ceSystemOp.delayMs(10);

    ceTft400_fill(CE_TFT400_COLOR_BLACK);
    ceTft400_drawRectangle(CE_TFT400_WIDTH - 30 - 5, 30 - 5, CE_TFT400_WIDTH - 30 + 5, 30 + 5, CE_TFT400_COLOR_RED); //在CE_TFT400_WIDTH-30，30处画加号
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x01)          //等待用户点击屏幕
        ceSystemOp.delayMs(10);
    ceTft400_getTouchPix(&(tempX[2]), &(tempY[2]));
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x00)          //等待用户释放屏幕
        ceSystemOp.delayMs(10);

    ceTft400_fill(CE_TFT400_COLOR_BLACK);
    ceTft400_drawRectangle(30 - 5, CE_TFT400_HIGHT - 30 - 5, 30 + 5, CE_TFT400_HIGHT - 30 + 5, CE_TFT400_COLOR_RED); //在30，CE_TFT400_HIGHT-30处画加号
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x01)          //等待用户点击屏幕
        ceSystemOp.delayMs(10);
    ceTft400_getTouchPix(&(tempX[3]), &(tempY[3]));
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x00)          //等待用户释放屏幕
        ceSystemOp.delayMs(10);

    ceTft400_fill(CE_TFT400_COLOR_BLACK);
    ceTft400_drawRectangle(CE_TFT400_WIDTH - 30 - 5, CE_TFT400_HIGHT - 30 - 5, CE_TFT400_WIDTH - 30 + 5, CE_TFT400_HIGHT - 30 + 5, CE_TFT400_COLOR_RED); //在CE_TFT400_WIDTH-30，30处画加号
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x01)          //等待用户点击屏幕
        ceSystemOp.delayMs(10);
    ceTft400_getTouchPix(&(tempX[4]), &(tempY[4]));
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x00)          //等待用户释放屏幕
        ceSystemOp.delayMs(10);

    ceTft400_fill(CE_TFT400_COLOR_BLACK);
    ceTft400_drawRectangle(CE_TFT400_WIDTH / 2 - 5, CE_TFT400_HIGHT / 2 - 5, CE_TFT400_WIDTH / 2 + 5, CE_TFT400_HIGHT / 2 + 5, CE_TFT400_COLOR_RED); //在CE_TFT400_WIDTH/2，CE_TFT400_HIGHT/2处画加号
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x01)          //等待用户点击屏幕
        ceSystemOp.delayMs(10);
    ceTft400_getTouchPix(&(tempX[0]), &(tempY[0]));
    while(ceIntOp.getBit(&(ceTft400_ceTft400->ceL36.ceInt)) == 0x00)          //等待用户释放屏幕
        ceSystemOp.delayMs(10);

    if(tempX[1] < tempX[2] && tempX[1] < tempX[0] && tempX[0] < tempX[2] && tempX[3] < tempX[0] && tempX[3] < tempX[4]   &&
        tempY[1] < tempY[3] && tempY[2] < tempY[4] && tempY[0] < tempY[3] && tempY[0] < tempY[4] && tempY[0] > tempY[1] && tempY[0] > tempY[2]) //在这里进行坐标判断，即如tempX[1] 一定会是小于tempX[0]的坐标等。如果判断不对，则直接返回校准失败
    {
        //可以将以下四个参数保存到Flash/Eeprom中，在TFT初始化时直接读取即可。
        ceTft400_ceTft400->clbTempX[0] = ((CE_TFT400_WIDTH - 30 - 30) * 2) / ((tempX[2] - tempX[1]) + (tempX[4] - tempX[3]));
        ceTft400_ceTft400->clbTempX[1] = tempX[0];
        ceTft400_ceTft400->clbTempY[0] = ((CE_TFT400_HIGHT - 30 - 30) * 2) / ((tempY[3] - tempY[1]) + (tempY[4] - tempY[2]));
        ceTft400_ceTft400->clbTempY[1] = tempY[0];

        ceTft400_ceTft400->isInCalibration = 0x00;
        ceTft400_appendString("Calibration Success!!\n");
        return CE_STATUS_SUCCESS;//返回校准成功
    }
    ceTft400_appendString("Calibration Error!!\n");
    ceTft400_ceTft400->isInCalibration = 0x00;
    return CE_STATUS_FAILE;
}

/**
  * @brief  关闭显示
  * @return None
  */
void ceTft400_setOff(void)
{
    cePwmOp.stop(&(ceTft400_ceTft400->ceL36.cePwm));
    cePwmOp.resetBit(&(ceTft400_ceTft400->ceL36.cePwm));
}

/**
  * @brief  设置屏幕亮度
  * @param  brightness:屏亮度百分比，0－100
  * @return None
  */
void ceTft400_setBrightness(uint8 brightness)
{
    uint32 duty = ((uint64)brightness * CE_TFT400_PWM_CYCLE) / 10000;
    if (duty > CE_TFT400_PWM_CYCLE)
    {
        duty = CE_TFT400_PWM_CYCLE;
    }
    else
    {
        if (duty < CE_PWM_MIN_CYCLE_NS)
        {
            duty = CE_PWM_MIN_CYCLE_NS;
        }
    }
    ceTft400_ceTft400->ceL36.cePwm.dutyNs = duty;
    cePwmOp.updata(&(ceTft400_ceTft400->ceL36.cePwm));
}

/**
  * @brief  获取字模
  * @param  msgGBK:需要获取的字符
  * @param  outBuf:输出缓存
  * @return None
  */
void ceTft400_getFontData(char* msgGBK, uint8* outBuf, CE_TFT400_GBK_TYPE ceTft400GBKType)
{
    int i = 0;
    uint32 address = 0;
    uint32 baseAddress = 0;
    uint8  readBuf[32] = { 0 };
    uint8 j, m, index, temp;

    if(((uint8)msgGBK[i] == 0xA9) && ((uint8)msgGBK[i + 1] >= 0xA1))
    {
        address = (282 + (msgGBK[i + 1] - 0xA1)) * 32 + baseAddress;
    }
    else if(((uint8)msgGBK[i] >= 0xA4) && ((uint8)msgGBK[i] <= 0xA9) && ((uint8)msgGBK[i + 1] >= 0xA1))
    {
        address = ((msgGBK[i] - 0xA1) * 94 + (msgGBK[i + 1] - 0xA1))  * 32  + baseAddress;
    }
    else if(((uint8)msgGBK[i] >= 0xA1) && ((uint8)msgGBK[i] <= 0xA9) && ((uint8)msgGBK[i + 1] >= 0xA1))
    {
        address = ((msgGBK[i] - 0xA1) * 94 + (msgGBK[i + 1] - 0xA1)) * 32 + baseAddress;
    }
    else if(((uint8)msgGBK[i] >= 0xB0) && ((uint8)msgGBK[i] <= 0xF7) && ((uint8)msgGBK[i + 1] >= 0xA1))
    {
        address = ((msgGBK[i] - 0xB0) * 94 + (msgGBK[i + 1] - 0xA1) + 846)  * 32  + baseAddress;//啊
    }
    else
    {
        address = ((msgGBK[i] - 0xA1) * 94 + (msgGBK[i + 1] - 0xA1))  * 32  + baseAddress;
    }
    ceGpioOp.resetBit(&(ceTft400_ceTft400->ceL36.ceGpioEx1));//开始从字库里获得数据
    ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster), 0x03);//0x03指令为一般读取，还有快速读取(一次读取多个)
    ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster), (address >> 16) & 0xFF);
    ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster), (address >> 8) & 0xFF);
    ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster), (address) & 0xFF);
    for(i = 0; i < 32; i++)
    {
        readBuf[i] = ceSpiMasterOp.writeReadByte(&(ceTft400_ceTft400->ceL36.ceSpiMaster), 0xFF);
    }
    ceGpioOp.setBit(&(ceTft400_ceTft400->ceL36.ceGpioEx1));

    for(m = 0; m < 2; m++)
    {
        for(j = 0; j < 2; j++)
        {
            index = 0x01;
            for(i = 0; i < 8; i++)
            {
                temp = 0;
                temp |= (((readBuf[0 + j * 8 + m * 16] & index) == 0) ? 0x80 : 0x00);
                temp |= (((readBuf[1 + j * 8 + m * 16] & index) == 0) ? 0x40 : 0x00);
                temp |= (((readBuf[2 + j * 8 + m * 16] & index) == 0) ? 0x20 : 0x00);
                temp |= (((readBuf[3 + j * 8 + m * 16] & index) == 0) ? 0x10 : 0x00);
                temp |= (((readBuf[4 + j * 8 + m * 16] & index) == 0) ? 0x08 : 0x00);
                temp |= (((readBuf[5 + j * 8 + m * 16] & index) == 0) ? 0x04 : 0x00);
                temp |= (((readBuf[6 + j * 8 + m * 16] & index) == 0) ? 0x02 : 0x00);
                temp |= (((readBuf[7 + j * 8 + m * 16] & index) == 0) ? 0x01 : 0x00);
                index <<= 1;
                outBuf[i * 2 + j + m * 16] = temp;
            }
        }
    }
}

/**
  * @brief  CeTft400模块初始化
  * @param  ceTft400:CeTft400属性对象
  * @param  ceL36:CeTft400模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ceTft400_initial(CeTft400* ceTft400, CE_RESOURCE ceL36, void(*callBackTouch)(int16 x, int16 y))
{
    ceTft400->ceL36.ceL36BusSpeed = CE_L36_BUS_SPEED_H;
    ceL36Op.initial(&(ceTft400->ceL36));

    ceTft400->ceL36.cePwm.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_PWM);
    ceTft400->ceL36.cePwm.cycleNs = CE_TFT400_PWM_CYCLE;
    ceTft400->ceL36.cePwm.dutyNs = CE_TFT400_PWM_CYCLE - 1;
    cePwmOp.initial(&(ceTft400->ceL36.cePwm));//Bl_CTR
    cePwmOp.resetBit(&(ceTft400->ceL36.cePwm));//初始化时先关闭显示，初始化完成时在打开

    ceTft400->ceL36.ceSpiMaster.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_SPI);
    ceTft400->ceL36.ceSpiMaster.ceSpiMasterSpeed = CE_SPI_MASTER_SPEED_5MBPS;
    ceSpiMasterOp.initial(&(ceTft400->ceL36.ceSpiMaster));//SPI NSS控制ADS7843E

    ceTft400->ceL36.ceInt.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_INT);
    ceTft400->ceL36.ceInt.ceMode = CE_INT_TRIGGER_FALLING;
    ceTft400->ceL36.ceInt.pAddPar = ceTft400;
    ceTft400->ceL36.ceInt.callBack = ceTft400_callBackTouch;
    ceIntOp.initial(&( ceTft400->ceL36.ceInt));//不使用中断，但必须进行初始化，因为要获取这个引脚的高低电平来判断是否触摸
    // ceIntOp.start(&( ceTft400->ceL36.ceInt));//采用软件查询方式，而不使用中断方式

    ceTft400->ceL36.ceGpioEx0.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_GPIO_EX0);
    ceTft400->ceL36.ceGpioEx0.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceTft400->ceL36.ceGpioEx0));
    ceGpioOp.setBit(&(ceTft400->ceL36.ceGpioEx0));//T_BUST ADS7843E

    ceTft400->ceL36.ceGpioEx1.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_GPIO_EX1);
    ceTft400->ceL36.ceGpioEx1.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceTft400->ceL36.ceGpioEx1));
    ceGpioOp.setBit(&(ceTft400->ceL36.ceGpioEx1));//NSS_2 GT20K16S1Y

    ceTft400_ceTft400 = ceTft400;
    ceTft400_tftInitial();//Tft屏初始化    
    cePwmOp.start(&(ceTft400->ceL36.cePwm));

    if(callBackTouch != CE_NULL)
    {
        ceTft400_ceTft400->callBackTouch = callBackTouch;//初始化触摸回调，在CeTask里执行，即暂时不使用中断的方式
        ceTft400->ceTask.ID = ceTft400->ceL36.ceResource;
        ceTft400->ceTask.callBack = ceTft400_callBackTouch;
        ceTft400->ceTask.pAddPar = ceTft400;
#ifdef __CE_USE_RTOS__
        ceTft400->ceTask.isNewThread = 0x01;
        ceTft400->ceTask.taskPriority = CE_TASK_PRIORITY_M;
        ceTft400->ceTask.ID = ceL36;
        ceTft400->ceTask.pAddPar = ceTft400;
        ceTft400->ceTask.taskName = "CeTft400 Touch Task";
        ceTft400->ceTask.callBack= ceTft400_callBackTouch;//因读取触摸点，如果在中断中执行，会花费大量时间，故这里采用循环扫描的方式来读取触摸点
        ceTft400->ceTask.taskStackBuf = ceTft400_taskBuf;
        ceTft400->ceTask.taskStackBufSize = CE_TFT400_TASK_STACK_BUF_SIZE;
#endif
        ceTaskOp.registerTask(&(ceTft400->ceTask));
        ceTaskOp.start(&(ceTft400->ceTask));
    }
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeTft400模块操作对象定义
  */
const CeTft400Op ceTft400Op = {ceTft400_initial, ceTft400_setOn, ceTft400_calibration, ceTft400_setBrightness, ceTft400_fill, ceTft400_drawPoint,
                                    ceTft400_drawRectangle, ceTft400_drawData, ceTft400_showString, ceTft400_showInt, ceTft400_showCN1616, ceTft400_appendString,
                                    ceTft400_setOff, ceTft400_getFontData};

#ifdef __cplusplus
 }
#endif //__cplusplus

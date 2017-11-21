/**
  ******************************************************************************
  * @file    CeTft320.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTft320ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)���°��Tft����ICΪR61509V��ģ���֧��֮ǰ�ĺ����ڵ�R61509V����IC��
  *  ��ʼ���������ȶ�ȡ����IC��ID�������ж��ǲ���R61509V��Ȼ����ݿ���IC��ID�ڲ�����
  *  ���в�ͬ�Ĵ���
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeTft320.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_TFT320_CMD_ADDR      0x60000000      /*!< CeTft320д����ĵ�ַ*/
#define CE_TFT320_DATA_ADDR     0x60020000      /*!< CeTft320д���ݵĵ�ַ*/

#define CE_TFT320_PWM_CYCLE     1000000         /*!< CeTft320�������ȵ�PWM����*/
#define CE_TFT320_DEVICE_R61509V    0xB509      /*!< CeTft320����оƬR61509V��ID*/
#define CE_TFT320_CAN_SET_REGIION               /*!< �����Ҫֱ�Ӳ���������������߻���Ч�ʣ��������*/

#ifdef __CE_USE_RTOS__
#define CE_TFT320_TASK_STACK_BUF_SIZE 1024                  /*!< ʹ�ò���ϵͳʱ�������ջ�������ĳ���*/
CE_STK ceTft320_taskBuf[CE_TFT320_TASK_STACK_BUF_SIZE];     /*!< ʹ�ò���ϵͳʱ��ΪCeTft320����������ջ������*/
#endif //__CE_USE_RTOS__

/**
  * @brief  CeTft320�õ�6*8�ĵ���
  */
const unsigned char CE_TFT320_F6x8[][6] =
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
  * @brief  CeTft320ʹ�õ�8*16�ĵ���
  */
const unsigned char CE_TFT320_F8X16[] =
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

CeTft320* ceTft320_ceTft320 = CE_NULL;//���ڱ���Ψһ��һ��ʹ��L36�ӿڵ�LCDģ��ָ��
void ceTft320_fill(uint16 color);

uint32  ceTft320_getTouchAdX(void)
{
    uint16 temp = 0;
    #ifdef CE_TFT320_SHOW_HORIZONTAL
    ceGpioOp.setBit(&(ceTft320_ceTft320->ceL36.ceGpioEx1));//��ģƬѡ����
    ceSpiMasterOp.resetNSSBit(&(ceTft320_ceTft320->ceL36.ceSpiMaster));
    //while(ceL36Op.getBitEx0() == 0x00);//����

    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), 0x90);//��ȡY����ָ��
    ceSystemOp.delayUs(6);
    temp = ((ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFFFF) << 8);
    temp |= (ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFF);
    temp  >>= 3;//��Ϊ���λ��Ч���ӵڶ�λ������Ч����(��ʱ��ͼ�Ͳο���ش�����֪)������ֻ��Ҫ����3λ
    #else 
    temp = 0;
    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), 0xD0);//��ȡX����ָ��
    ceSystemOp.delayUs(6);
    temp = ((ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFFFF) << 8);
    temp |= (ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFF);
    temp  >>= 3;//��Ϊ���λ��Ч���ӵڶ�λ������Ч����(��ʱ��ͼ�Ͳο���ش�����֪)������ֻ��Ҫ����3λ
    #endif
    return temp;
}

uint32 ceTft320_getTouchAdY(void)
{
    uint16 temp = 0;
#ifndef CE_TFT320_SHOW_HORIZONTAL
    ceGpioOp.setBit(&(ceTft320_ceTft320->ceL36.ceGpioEx1));//��ģƬѡ����
    ceSpiMasterOp.resetNSSBit(&(ceTft320_ceTft320->ceL36.ceSpiMaster));
    //while(ceL36Op.getBitEx0() == 0x00);//����

    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), 0x90);//��ȡY����ָ��
    ceSystemOp.delayUs(6);
    temp = ((ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFFFF) << 8);
    temp |= (ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFF);
    temp  >>= 3;//��Ϊ���λ��Ч���ӵڶ�λ������Ч����(��ʱ��ͼ�Ͳο���ش�����֪)������ֻ��Ҫ����3λ
    #else 
    temp = 0;
    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), 0xD0);//��ȡX����ָ��
    ceSystemOp.delayUs(6);
    temp = ((ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFFFF) << 8);
    temp |= (ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFF);
    temp  >>= 3;//��Ϊ���λ��Ч���ӵڶ�λ������Ч����(��ʱ��ͼ�Ͳο���ش�����֪)������ֻ��Ҫ����3λ
    #endif
    return temp;
}


/**
  * @brief  ��ȡ���������µĵ������
  * @param  pX:���x������ֵ��int32ָ��
  * @param  pY:���y������ֵ��int32ָ��
  * @return None
  */
void ceTft320_getTouchPix(int32* pX, int32* pY)
{
    uint16 temp = 0;
    ceGpioOp.setBit(&(ceTft320_ceTft320->ceL36.ceGpioEx1));//��ģƬѡ����
    ceSpiMasterOp.resetNSSBit(&(ceTft320_ceTft320->ceL36.ceSpiMaster));
    //while(ceL36Op.getBitEx0() == 0x00);//����

    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), 0x90);//��ȡY����ָ��
    ceSystemOp.delayUs(6);
    temp = ((ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFFFF) << 8);
    temp |= (ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFF);
    temp  >>= 3;//��Ϊ���λ��Ч���ӵڶ�λ������Ч����(��ʱ��ͼ�Ͳο���ش�����֪)������ֻ��Ҫ����3λ

#ifdef CE_TFT320_SHOW_HORIZONTAL
    *pX = CE_TFT320_WIDTH - ((temp / 10));
#else 
    *pY = (CE_TFT320_HIGHT - (temp / 10));
#endif


    temp = 0;
    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), 0xD0);//��ȡX����ָ��
    ceSystemOp.delayUs(6);
    temp = ((ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFFFF) << 8);
    temp |= (ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster),0x00) & 0xFF);
    temp  >>= 3;//��Ϊ���λ��Ч���ӵڶ�λ������Ч����(��ʱ��ͼ�Ͳο���ش�����֪)������ֻ��Ҫ����3λ

#ifdef CE_TFT320_SHOW_HORIZONTAL
    *pY = (temp / 16);
#else 
    *pX = CE_TFT320_WIDTH - (temp / 16);
#endif



    ceSpiMasterOp.setNSSBit(&(ceTft320_ceTft320->ceL36.ceSpiMaster));
}

/**
  * @brief  ���ڼ���Ƿ��´�����
  * @param  pAddPar:CeTft320����ָ��
  * @return None
  */
void ceTft320_callBackTouch(void* pAddPar)
{
    if(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x00)//û�а��°�ť
    {
        CeTft320* ceTft320 = (CeTft320*)(pAddPar);
        if(ceTft320->callBackTouch != CE_NULL)
        {
            if(ceTft320->isInCalibration == 0x00)
            {
                int32 xVal1 = 0, yVal1 = 0, xVal2 = 0, yVal2 = 0;
                int i;
                for(i = 0; i < 10; i++)
                {
                    int32 tX = 0, tY = 0;
                    ceTft320_getTouchPix(&tX, &tY);
                    xVal1 += tX;
                    yVal1 += tY;
                }
                xVal1 /= 10;
                yVal1 /= 10;

                xVal2 = (xVal1 - ceTft320_ceTft320->clbTempX[1])  / (ceTft320_ceTft320->clbTempX[0] ) +  CE_TFT320_WIDTH/ 2; //������У׼
                yVal2 = (yVal1 - ceTft320_ceTft320->clbTempY[1])  / (ceTft320_ceTft320->clbTempY[0] ) +  CE_TFT320_HIGHT/ 2; //������У׼
                if(xVal2 < 0)
                {
                    xVal2 = 0;
                }
                if(xVal2 > CE_TFT320_WIDTH)
                {
                    xVal2 = CE_TFT320_WIDTH - 1;
                }
                if(yVal2 < 0)
                {
                    yVal2 = 0;
                }
                if(yVal2 > CE_TFT320_HIGHT) 
                {
                    yVal2 = CE_TFT320_HIGHT - 1;
                }
                ceTft320->callBackTouch((int16)xVal2,(int16)yVal2);
                //ceDebugOp.printf("X:%d  Y:%d\n",xVal2,yVal2);
            }
        }
    }
#ifdef __CE_USE_RTOS__
    ceSystemOp.delayMs(50);
#endif
}

/**
  * @brief  CeTft320ģ���ʼ��
  * @param  ceXX:CeTft320ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceTft320_tftInitial(void)
{
    uint16 i, j;
    for(j = 0; j < CE_TFT320_WIDTH / 6; j++)
    {
        for(i = 0; i < CE_TFT320_HIGHT / 8; i++)
        {
            ceTft320_ceTft320->asBuf[j][i] = ' ';
        }
    }
    ceTft320_ceTft320->asXIndex = 0;
    ceTft320_ceTft320->asYIndex = 0;

    //���Դ�Flash/Eeprom�ж�ȡ���ĸ�����
    ceTft320_ceTft320->clbTempX[0] = 1;
    ceTft320_ceTft320->clbTempX[1] = CE_TFT320_WIDTH / 2;

    ceTft320_ceTft320->clbTempY[0] = 1;
    ceTft320_ceTft320->clbTempY[1] = CE_TFT320_HIGHT / 2;

        
    ceTft320_ceTft320->isInCalibration = 0x00;

    ceTft320_ceTft320->deviceCode = 0x0000;

    ceL36Op.setRST();
    ceSystemOp.delayMs(10);
    ceL36Op.resetRST();
    ceSystemOp.delayMs(10);
    ceL36Op.setRST();
    ceSystemOp.delayMs(10);

    CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0000);//�Ĵ�д0x00
    CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);
    CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0000);
    CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000)
    CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0000);
    CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000)
    CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0000);
    CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);

    CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0000);//Device code read(R000h)
    ceTft320_ceTft320->deviceCode = CE_L36_READ_DATA(CE_TFT320_DATA_ADDR);

    if (ceTft320_ceTft320->deviceCode == CE_TFT320_DEVICE_R61509V)
    {
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0400);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x6200);     //base image ���� 400��
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x010);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0019);     //���Ƶ��
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0100);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0330);//���õ�Դ���ƣ�ƽ����ʾ�������
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0102);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0xD1B0);//PSON,PON ����Ϊ1����Դ��Ӧ��
        ceSystemOp.delayMs(5);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0280);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0xBF00);//VCM
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x5030);//RGB��Ϊ5-6-5ģʽ  // 1030 : BGR, 0030 : RGB
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0100);//When SS = ��1�� and BGR = ��1��, RGB dots are assigned one to one from S720 to S1.
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0007);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0100);//������ʾ����base image�Ĺ��뿪
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x200);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);//����RAM ADDRESS
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0201);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0401);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0001);//����base image ����ģʽ����������
        ceSystemOp.delayMs(5);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x000C);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);//�ⲿ��ʾ�ӿڿ��ƣ�Ĭ��ֵ
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0090);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x8000);//���������ƣ�FMARK interface
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0404);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);//��0�߿�ʼ��
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0502);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x005f);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0200);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);//RAM address ����
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0201);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);
        ceSystemOp.delayMs(5);

        ceTft320_fill(CE_TFT320_COLOR_BLACK);
        ceSystemOp.delayUs(10);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0202);
    }
    else
    {
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0083);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0002);//TESTM=1

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0085);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0003);//VDC_SEL=011
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x008B);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x008C);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0093);//STBA[7]=1,STBA[5:4]=01,STBA[1:0]=11

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0091);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0001);//DCDC_SYNC=1

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0083);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);//TESTM=0

        //Gamma Setting
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x003E);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x00B0);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x003F);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0040);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0010);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0041);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0056);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0042);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0013);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0043);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0046);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0044);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0023);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0045);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0076);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0046);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0047);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x005E);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0048);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x004F);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0049);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0040);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0017);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0091);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x002B);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x00F9);
        ceSystemOp.delayMs(1);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x001B);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0014);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x001A);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0011);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x001C);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0006);//0d

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x001F);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0042);
        ceSystemOp.delayMs(1);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0019);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x000A);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0019);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x001A);
        ceSystemOp.delayMs(1);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0019);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0012);
        ceSystemOp.delayMs(1);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x001E);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0027);
        ceSystemOp.delayMs(1);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0024);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0060);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x003D);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0040);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0034);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0038);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0035);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0038);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0024);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0038);
        ceSystemOp.delayMs(1);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0024);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x003C);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0016);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x001C);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0006);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0055);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0002);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0004);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0005);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x00ef);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0006);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0007);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0000);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0008);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x0001);
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0009);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, 0x008f);

        ceTft320_fill(CE_TFT320_COLOR_BLACK);
        ceSystemOp.delayUs(10);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0022); //display on
    }

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ���û�������
  * @param  startX:�������Ͻ�x����
  * @param  startY:�������Ͻ�y����
  * @param  endX:�������½�x����
  * @param  endY:�������½�y����
  * @return None
  */
void ceTft320_setRegion(int16 startX, int16 startY, int16 endX, int16 endY)
{
    if (ceTft320_ceTft320->deviceCode == CE_TFT320_DEVICE_R61509V)
    {
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0200);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, startX);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0201);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, startY);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0210);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, startX);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0211);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, endX);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0212);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, startY);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0213);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, endY);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0202);
    }
    else
    {
        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0003);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, startX);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0006);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, startY >> 8);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0007);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, startY);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0005);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, endX);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0008);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, endY >> 8);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0009);
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, endY);

        CE_L36_WRITE_DATA(CE_TFT320_CMD_ADDR, 0x0022);
    }
}

/**
  * @brief  CeTft320��ָ��λ�û���
  * @param  x:���ÿ�ʼ��ʾ�ַ�����x������
  * @param  y:���ÿ�ʼ��ʾ�ַ�����y������
  * @param  color:Ҫ��ʾ������(��ɫ)
  * @return None
  */
void ceTft320_drawPoint(int16 x, int16 y, uint16 color)
{
    if (ceTft320_ceTft320->deviceCode == CE_TFT320_DEVICE_R61509V)
    {
        color = ~color;
    }
#ifdef  CE_TFT320_SHOW_HORIZONTAL
    y = CE_TFT320_HIGHT-y;
    if (x < 0 || y < 0)
    {
        return;
    }
    if (x > CE_TFT320_WIDTH || y > CE_TFT320_HIGHT)
    {
        return;
    }
    ceTft320_setRegion(y, x, y, x);
#else
    if (x < 0 || y < 0)
    {
        return;
    }
    if (x > CE_TFT320_WIDTH || y > CE_TFT320_HIGHT)
    {
        return;
    }
    ceTft320_setRegion(x, y, x, y);
#endif
    CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, color);
}

/**
  * @brief  CeTft320���ƾ���
  * @param  startX:�������Ͻ�x����
  * @param  startY:�������Ͻ�y����
  * @param  endX:�������½�x����
  * @param  endY:�������½�y����
  * @param  color:Ҫ��ʾ������(��ɫ)
  * @return None
  */
void ceTft320_drawRectangle(uint16 startX, uint16 startY, uint16 endX, uint16 endY, uint16 color)
{
    int i, j;
    if(startX > endX || startY > endY)
    {
        return;
    }
    if(endX >= CE_TFT320_WIDTH)
    {
        endX = CE_TFT320_WIDTH - 1;
    }
    if(endY > CE_TFT320_HIGHT)
    {
        endY = CE_TFT320_HIGHT - 1;
    }
    if (ceTft320_ceTft320->deviceCode == CE_TFT320_DEVICE_R61509V)
    {
        color = ~color;
    }

#ifndef CE_TFT320_SHOW_HORIZONTAL
    ceTft320_setRegion(startX, startY, endX, endY);
    endX++;
    endY++;
    for(i = startY; i < endY; i++)
    {
        for(j = startX; j < endX; j++)
        {
            CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, color);
        }
    }
#else
    endX++;
    endY++;
    for(i = startX; i < endX; i++)
    {
        for(j = startY; j < endY; j++)
        {
            ceTft320_drawPoint(i, j, color);
        }
    }
#endif
}

/**
  * @brief  CeTft320��ʾ�ַ�
  * @param  x:���ÿ�ʼ��ʾ�ַ���x������
  * @param  y:���ÿ�ʼ��ʾ�ַ���y������
  * @param  foreColor:��ʾ�����ǰ��ɫ
  * @param  backColor:��ʾ����ı���ɫ
  * @param  msg:Ҫ��ʾ���ַ���ָ��
  * @param showSize:��ʾ�������С����ѡCE_TFT320_EN_SIZE_F6X8��CE_TFT320_EN_SIZE_F8X16
  * @return None
  */
void ceTft320_showChar(int16 x, int16 y, uint16 foreColor, uint16 backColor, const char ch, CE_TFT320_EN_SIZE showSize)
{
#ifndef CE_TFT320_SHOW_HORIZONTAL
    if (ceTft320_ceTft320->deviceCode == CE_TFT320_DEVICE_R61509V)
    {
        foreColor = ~foreColor;
        backColor = ~backColor;
    }
    if(showSize == CE_TFT320_EN_SIZE_F6X8)
    {
        uint16  i, j, c, index;
        c = ch - 32;
        ceTft320_setRegion(x,  y, x + 6 - 1, y + 8 - 1);
        index = 0x01;
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 6; j++)
            {
                if((CE_TFT320_F6x8[c][j] & index) == index)
                {
                    CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, foreColor);
                }
                else
                {
                    CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, backColor);
                }
            }
            index <<= 1;
        }
    }
    else
    {
        uint8 i, j, c, m, index;
        c = ch - 32;
        ceTft320_setRegion(x,  y, x + 8 - 1, y + 16 - 1);
        for(i = 0; i < 2; i++)
        {
            index = 0x01;
            for(j = 0; j < 8; j++)
            {
                for(m = 0; m < 8; m++)
                {
                    if((CE_TFT320_F8X16[c * 16 + i * 8 + m] & index) == index)
                    {
                        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, foreColor);
                    }
                    else
                    {
                        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, backColor);
                    }
                }
                index <<= 1;
            }
        }
    }
#else
    uint16  j, m, n, c, temp, index;
    c = ch - 32;
    if(showSize == CE_TFT320_EN_SIZE_F6X8)
    {
        ceTft320_setRegion(x,  y, x + 6 - 1, y + 8 - 1);
        for(j = 0; j < 6; j++)
        {
            temp = CE_TFT320_F6x8[c][j];
            index = 0x01;
            for(m = 0; m < 8; m++)
            {
                if((temp & index) == index)
                {
                    ceTft320_drawPoint(x + j, y + m, foreColor);
                }
                else
                {
                    ceTft320_drawPoint(x + j, y + m, backColor);
                }
                index <<= 1;
            }
        }
        x += 6;
    }
    else
    {
        ceTft320_setRegion(x, y, x + 8 - 1, y + 16 - 1);
        for(j = 0; j < 2; j++)
        {
            for(m = 0; m < 8; m++)
            {
                temp = CE_TFT320_F8X16[c * 16 + j * 8 + m];
                index = 0x01;
                for(n = 0; n < 8; n++)
                {
                    if((temp & index) == index)
                    {
                        ceTft320_drawPoint(x + m, y + n + j * 8, foreColor);
                    }
                    else
                    {
                        ceTft320_drawPoint(x + m, y + n + j * 8, backColor);
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
  * @brief  CeTft320��ʾ�ַ�������֧������
  * @param  x:���ÿ�ʼ��ʾ�ַ�����x������
  * @param  y:���ÿ�ʼ��ʾ�ַ�����y������
  * @param  foreColor:��ʾ�����ǰ��ɫ
  * @param  backColor:��ʾ����ı���ɫ
  * @param  msg:Ҫ��ʾ���ַ���ָ��
  * @param showSize:��ʾ�������С����ѡCE_TFT320_EN_SIZE_F6X8��CE_TFT320_EN_SIZE_F8X16
  * @return None
  */
void ceTft320_showString(int16 x, int16 y, uint16 foreColor, uint16 backColor, const char* msg, CE_TFT320_EN_SIZE showSize)
{
    uint16 i, count;
    count = ceStringOp.strlen(msg);
    for(i = 0; i < count; i++)
    {
        ceTft320_showChar(x + i * ((showSize == CE_TFT320_EN_SIZE_F6X8) ? 6 : 8), y, foreColor, backColor, msg[i], showSize);
    }
}

/**
  * @brief  CeTft320��ʾ16x16���������壬��ģcn1616�ɴ�CeCN1616.h�л�ȡ
  * @param  x:���ÿ�ʼ��ʾ�ַ�����x������
  * @param  y:���ÿ�ʼ��ʾ�ַ�����y������
  * @param  foreColor:��ʾ�����ǰ��ɫ
  * @param  backColor:��ʾ����ı���ɫ
  * @param  cn1616:Ҫ��ʾ������ģ����ģcn1616�ɴ�CeCN1616.h�л�ȡ
  * @return None
  */
void ceTft320_showCN1616(int16 x, int16 y, uint16 foreColor, uint16 backColor, const uint8* cn1616)
{
#ifndef CE_TFT320_SHOW_HORIZONTAL
    int i, j;
    uint8 index;
    if (ceTft320_ceTft320->deviceCode == CE_TFT320_DEVICE_R61509V)
    {
        foreColor = ~foreColor;
        backColor = ~backColor;
    }
    ceTft320_setRegion(x, y, x + 16 - 1, y + 16 - 1);
    for (i = 0; i < 32; i++)
    {
        index = 0x80;
        for (j = 0; j < 8; j++)
        {
            if ((cn1616[i] & index) == index)
            {
                CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, backColor);
            }
            else
            {
                CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, foreColor);
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
                    ceTft320_drawPoint(x + i * 8 + m, j + y, backColor);
                }
                else
                {
                    ceTft320_drawPoint(x + i * 8 + m, j + y, foreColor);
                }
                temp <<= 1;
            }
        }
    }
#endif
}

/**
  * @brief  CeTft320��ʾ32λ�з��ŵ����֣����ֵ0x7FFFFFFF����Сֵ0x80000001
  * @param  x:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�x������
  * @param  y:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�y������
  * @param  foreColor:��ʾ�����ǰ��ɫ
  * @param  backColor:��ʾ����ı���ɫ
  * @param  val:Ҫ��ʾ��32λ�з��ŵ�����
  * @param  showSize:��ʾ�������С����ѡCE_TFT320_EN_SIZE_F6X8��CE_TFT320_EN_SIZE_F8X16
  * @return None
  */
void ceTft320_showInt(int16 x, int16 y, uint16 foreColor, uint16 backColor, const int32 val, CE_TFT320_EN_SIZE showSize)
{
    char temp[20];
    ceDebugOp.sprintf(temp, "%d", val);
    ceTft320_showString(x, y, foreColor, backColor, temp, showSize);
}

/**
  * @brief  һ�����ڴ�����ԣ��Կ���̨�ķ�ʽ��ӡ������Ϣ
  * @param  msg:Ҫ��ʾ����Ϣ
  * @return None
  */
void ceTft320_appendString(const char* msg)
{
    uint16 msgCoung = ceStringOp.strlen(msg);
    uint16 i, j;
    for(i = 0; i < msgCoung + 1; i++)
    {
        if(msg[i] == '\r' || msg[i] == '\n')
        {
            for(j = ceTft320_ceTft320->asXIndex; j < CE_TFT320_WIDTH / 6; j++)
            {
                ceTft320_ceTft320->asBuf[j][ceTft320_ceTft320->asYIndex] = ' ';
            }
            ceTft320_ceTft320->asXIndex = 0;
            ceTft320_ceTft320->asYIndex++;
            if(ceTft320_ceTft320->asYIndex >= CE_TFT320_HIGHT / 8)
            {
                uint16 m, n;
                for(m = 0; m < CE_TFT320_HIGHT / 8 - 1; m++)
                {
                    for(n = 0; n < CE_TFT320_WIDTH / 6; n++)
                    {
                        ceTft320_ceTft320->asBuf[n][m] = ceTft320_ceTft320->asBuf[n][m + 1];
                    }
                }
                for(n = 0; n < CE_TFT320_WIDTH / 6; n++)
                {
                    ceTft320_ceTft320->asBuf[n][CE_TFT320_HIGHT / 8 - 1] = ' ';
                }
                ceTft320_ceTft320->asYIndex--;
            }
        }
        else if(msg[i] == '\0')
        {
            break;
        }
        else
        {
            ceTft320_ceTft320->asBuf[ceTft320_ceTft320->asXIndex][ceTft320_ceTft320->asYIndex] = msg[i];
            ceTft320_ceTft320->asXIndex++;
            if(ceTft320_ceTft320->asXIndex >= CE_TFT320_WIDTH / 6)
            {
                ceTft320_ceTft320->asXIndex = 0;
                ceTft320_ceTft320->asYIndex++;
                if(ceTft320_ceTft320->asYIndex >= CE_TFT320_HIGHT / 8)
                {
                    uint16 m, n;
                    for(m = 0; m < CE_TFT320_HIGHT / 8 - 1; m++)
                    {
                        for(n = 0; n < CE_TFT320_WIDTH / 6; n++)
                        {
                            ceTft320_ceTft320->asBuf[n][m] = ceTft320_ceTft320->asBuf[n][m + 1];
                        }
                    }
                    for(n = 0; n < CE_TFT320_WIDTH / 6; n++)
                    {
                        ceTft320_ceTft320->asBuf[n][CE_TFT320_HIGHT / 8 - 1] = ' ';
                    }
                    ceTft320_ceTft320->asYIndex--;
                }
            }
        }
    }
    for(i = 0; i < CE_TFT320_HIGHT / 8; i++)
    {
        for(j = 0; j < CE_TFT320_WIDTH / 6; j++)
        {
            ceTft320_showChar(j * 6, i * 8, CE_TFT320_COLOR_YELLOW, CE_TFT320_COLOR_BLACK, ceTft320_ceTft320->asBuf[j][i], CE_TFT320_EN_SIZE_F6X8);
        }
    }
}

/**
  * @brief  CeTft320��ָ������(��ɫ)����ȫ�����
  * @param  color:ȫ����������(��ɫ)
  * @return None
  */
void ceTft320_fill( uint16 color)
{
    int i, j;
    if (ceTft320_ceTft320->deviceCode == CE_TFT320_DEVICE_R61509V)
    {
        color = ~color;
    }
#ifdef CE_TFT320_SHOW_HORIZONTAL
    ceTft320_setRegion(0, 0,  CE_TFT320_HIGHT- 1,  CE_TFT320_WIDTH- 1);
    for(i = 0; i < CE_TFT320_HIGHT; i++)
    {
        for(j = 0; j < CE_TFT320_WIDTH; j++)
        {
            CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, color);
        }
    }
#else
    ceTft320_setRegion(0, 0, CE_TFT320_WIDTH - 1, CE_TFT320_HIGHT - 1);
    for(i = 0; i < CE_TFT320_WIDTH; i++)
    {
        for(j = 0; j < CE_TFT320_HIGHT; j++)
        {
            CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, color);
        }
    }
#endif

}

/**
  * @brief  CeTft320����ͼƬ
  * @param  x:ͼƬ����ʼ��x����
  * @param  y:ͼƬ����ʼ��y����
  * @param  colorBuf:ͼƬ����
  * @param  bufSizeWidth:ͼƬ��
  * @param  bufSizeHight:ͼƬ��
  * @return None
  */
void ceTft320_drawData(uint16 x, uint16 y, const uint8* colorBuf, uint16 bufSizeWidth, uint16 bufSizeHight)
{
#ifdef CE_TFT320_CAN_SET_REGIION
    uint32 i;
    uint32 lgh = bufSizeHight * bufSizeWidth * 2;
    uint16 writeVal;
    ceTft320_setRegion(x, y, x + bufSizeWidth - 1, y + bufSizeHight - 1);
    for(i = 0; i < lgh; i += 2)
    {
        if (ceTft320_ceTft320->deviceCode == CE_TFT320_DEVICE_R61509V)
        {
            writeVal = ~((colorBuf[i]) | (uint16)(colorBuf[i + 1] << 8));
        }
        else
        {
            writeVal = (colorBuf[i]) | (uint16)(colorBuf[i + 1] << 8);
        }
        CE_L36_WRITE_DATA(CE_TFT320_DATA_ADDR, writeVal);
    }
#else
    int i, j;
    ceTft320_setRegion(x, y, x + bufSizeWidth - 1, y + bufSizeHight - 1);
    for(j = 0; j < bufSizeHight; j++)
    {
        for(i = 0; i < bufSizeWidth; i++)
        {
            uint16 temp = (uint16)colorBuf[(j * bufSizeWidth + i) * 2 + 1] << 8 | colorBuf[(j * bufSizeWidth + i) * 2];
            ceTft320_drawPoint(x + i, y + j, temp);
        }
    }
#endif
}

/**
  * @brief  ����ʾ
  * @return None
  */
void ceTft320_setOn(void)
{
    cePwmOp.start(&(ceTft320_ceTft320->ceL36.cePwm));
}

/**
  * @brief  У׼������������У׼��ɺ󣬽�У׼������浽Flash/Eeprom�У��ڳ�ʼ��ʱ����
  * @return У׼�ɹ����� CE_STATUS_SUCCESS��У׼ʧ�ܷ��� CE_STATUS_FAILE
  */
CE_STATUS ceTft320_calibration(void)
{
    int32 tempX[5] = {0, 0, 0, 0, 0};
    int32 tempY[5] = {0, 0, 0, 0, 0};
    ceTft320_ceTft320->isInCalibration = 0x01;
    ceTft320_fill(CE_TFT320_COLOR_BLACK);

    ceTft320_drawRectangle(30 - 5, 30 - 5, 30 + 5, 30 + 5, CE_TFT320_COLOR_RED); //��30��30�����Ӻ�
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x01)          //�ȴ��û������Ļ
        ceSystemOp.delayMs(10);
    ceTft320_getTouchPix(&(tempX[1]), &(tempY[1]));
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x00)          //�ȴ��û��ͷ���Ļ
        ceSystemOp.delayMs(10);

    ceTft320_fill(CE_TFT320_COLOR_BLACK);
    ceTft320_drawRectangle(CE_TFT320_WIDTH - 30 - 5, 30 - 5, CE_TFT320_WIDTH - 30 + 5, 30 + 5, CE_TFT320_COLOR_RED); //��CE_TFT320_WIDTH-30��30�����Ӻ�
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x01)          //�ȴ��û������Ļ
        ceSystemOp.delayMs(10);
    ceTft320_getTouchPix(&(tempX[2]), &(tempY[2]));
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x00)          //�ȴ��û��ͷ���Ļ
        ceSystemOp.delayMs(10);

    ceTft320_fill(CE_TFT320_COLOR_BLACK);
    ceTft320_drawRectangle(30 - 5, CE_TFT320_HIGHT - 30 - 5, 30 + 5, CE_TFT320_HIGHT - 30 + 5, CE_TFT320_COLOR_RED); //��30��CE_TFT320_HIGHT-30�����Ӻ�
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x01)          //�ȴ��û������Ļ
        ceSystemOp.delayMs(10);
    ceTft320_getTouchPix(&(tempX[3]), &(tempY[3]));
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x00)          //�ȴ��û��ͷ���Ļ
        ceSystemOp.delayMs(10);

    ceTft320_fill(CE_TFT320_COLOR_BLACK);
    ceTft320_drawRectangle(CE_TFT320_WIDTH - 30 - 5, CE_TFT320_HIGHT - 30 - 5, CE_TFT320_WIDTH - 30 + 5, CE_TFT320_HIGHT - 30 + 5, CE_TFT320_COLOR_RED); //��CE_TFT320_WIDTH-30��30�����Ӻ�
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x01)          //�ȴ��û������Ļ
        ceSystemOp.delayMs(10);
    ceTft320_getTouchPix(&(tempX[4]), &(tempY[4]));
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x00)          //�ȴ��û��ͷ���Ļ
        ceSystemOp.delayMs(10);

    ceTft320_fill(CE_TFT320_COLOR_BLACK);
    ceTft320_drawRectangle(CE_TFT320_WIDTH / 2 - 5, CE_TFT320_HIGHT / 2 - 5, CE_TFT320_WIDTH / 2 + 5, CE_TFT320_HIGHT / 2 + 5, CE_TFT320_COLOR_RED); //��CE_TFT320_WIDTH/2��CE_TFT320_HIGHT/2�����Ӻ�
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x01)          //�ȴ��û������Ļ
        ceSystemOp.delayMs(10);
    ceTft320_getTouchPix(&(tempX[0]), &(tempY[0]));
    while(ceIntOp.getBit(&(ceTft320_ceTft320->ceL36.ceInt)) == 0x00)          //�ȴ��û��ͷ���Ļ
        ceSystemOp.delayMs(10);

    if(tempX[1] < tempX[2] && tempX[1] < tempX[0] && tempX[0] < tempX[2] && tempX[3] < tempX[0] && tempX[3] < tempX[4]   &&
        tempY[1] < tempY[3] && tempY[2] < tempY[4] && tempY[0] < tempY[3] && tempY[0] < tempY[4] && tempY[0] > tempY[1] && tempY[0] > tempY[2]) //��������������жϣ�����tempX[1] һ������С��tempX[0]������ȡ�����жϲ��ԣ���ֱ�ӷ���У׼ʧ��
    {
        //���Խ������ĸ��������浽Flash/Eeprom�У���TFT��ʼ��ʱֱ�Ӷ�ȡ���ɡ�
        ceTft320_ceTft320->clbTempX[0] = ((CE_TFT320_WIDTH - 30 - 30) * 2) / ((tempX[2] - tempX[1]) + (tempX[4] - tempX[3]));
        ceTft320_ceTft320->clbTempX[1] = tempX[0];
        ceTft320_ceTft320->clbTempY[0] = ((CE_TFT320_HIGHT - 30 - 30) * 2) / ((tempY[3] - tempY[1]) + (tempY[4] - tempY[2]));
        ceTft320_ceTft320->clbTempY[1] = tempY[0];

        ceTft320_ceTft320->isInCalibration = 0x00;
        ceTft320_appendString("Calibration Success!!\n");
        return CE_STATUS_SUCCESS;//����У׼�ɹ�
    }
    ceTft320_appendString("Calibration Error!!\n");
    ceTft320_ceTft320->isInCalibration = 0x00;
    return CE_STATUS_FAILE;
}

/**
  * @brief  �ر���ʾ
  * @return None
  */
void ceTft320_setOff(void)
{
    cePwmOp.stop(&(ceTft320_ceTft320->ceL36.cePwm));
    cePwmOp.resetBit(&(ceTft320_ceTft320->ceL36.cePwm));
}

/**
  * @brief  ������Ļ����
  * @param  brightness:�����Ȱٷֱȣ�0��100
  * @return None
  */
void ceTft320_setBrightness(uint8 brightness)
{
    uint32 duty = ((uint64)brightness * CE_TFT320_PWM_CYCLE) / 10000;
    if (duty > CE_TFT320_PWM_CYCLE)
    {
        duty = CE_TFT320_PWM_CYCLE;
    }
    else
    {
        if (duty < CE_PWM_MIN_CYCLE_NS)
        {
            duty = CE_PWM_MIN_CYCLE_NS;
        }
    }
    ceTft320_ceTft320->ceL36.cePwm.dutyNs = duty;
    cePwmOp.updata(&(ceTft320_ceTft320->ceL36.cePwm));
}

/**
  * @brief  ��ȡ��ģ
  * @param  msgGBK:��Ҫ��ȡ���ַ�
  * @param  outBuf:�������
  * @return None
  */
void ceTft320_getFontData(char* msgGBK, uint8* outBuf, CE_TFT320_GBK_TYPE ceTft320GBKType)
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
        address = ((msgGBK[i] - 0xB0) * 94 + (msgGBK[i + 1] - 0xA1) + 846)  * 32  + baseAddress;//��
    }
    else
    {
        address = ((msgGBK[i] - 0xA1) * 94 + (msgGBK[i + 1] - 0xA1))  * 32  + baseAddress;
    }

    ceGpioOp.resetBit(&(ceTft320_ceTft320->ceL36.ceGpioEx1));//��ʼ���ֿ���������
    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), 0x03);//0x03ָ��Ϊһ���ȡ�����п��ٶ�ȡ(һ�ζ�ȡ���)
    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), (address >> 16) & 0xFF);
    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), (address >> 8) & 0xFF);
    ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), (address) & 0xFF);
    for(i = 0; i < 32; i++)
    {
        readBuf[i] = ceSpiMasterOp.writeReadByte(&(ceTft320_ceTft320->ceL36.ceSpiMaster), 0xFF);
    }
    ceGpioOp.setBit(&(ceTft320_ceTft320->ceL36.ceGpioEx1));

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
  * @brief  CeTft320ģ���ʼ��
  * @param  ceTft320:CeTft320���Զ���
  * @param  ceL36:CeTft320ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceTft320_initial(CeTft320* ceTft320, CE_RESOURCE ceL36, void(*callBackTouch)(int16 x, int16 y))
{
    ceTft320->ceL36.ceL36BusSpeed = CE_L36_BUS_SPEED_H;
    ceL36Op.initial(&(ceTft320->ceL36));

    ceTft320->ceL36.cePwm.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_PWM);
    ceTft320->ceL36.cePwm.cycleNs = CE_TFT320_PWM_CYCLE;
    ceTft320->ceL36.cePwm.dutyNs = CE_TFT320_PWM_CYCLE - 1;
    cePwmOp.initial(&(ceTft320->ceL36.cePwm));
    cePwmOp.resetBit(&(ceTft320->ceL36.cePwm));//��ʼ��ʱ�ȹر���ʾ����ʼ�����ʱ�ڴ�

    ceTft320->ceL36.ceSpiMaster.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_SPI);
    ceTft320->ceL36.ceSpiMaster.ceSpiMasterSpeed = CE_SPI_MASTER_SPEED_5MBPS;
    ceSpiMasterOp.initial(&(ceTft320->ceL36.ceSpiMaster));

    ceTft320->ceL36.ceInt.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_INT);
    ceTft320->ceL36.ceInt.ceMode = CE_INT_TRIGGER_FALLING;
    ceTft320->ceL36.ceInt.pAddPar = ceTft320;
    ceTft320->ceL36.ceInt.callBack = ceTft320_callBackTouch;
    ceIntOp.initial(&( ceTft320->ceL36.ceInt));//��ʹ���жϣ���������г�ʼ������ΪҪ��ȡ������ŵĸߵ͵�ƽ���ж��Ƿ���
    // ceIntOp.start(&( ceTft320->ceL36.ceInt));//���������ѯ��ʽ������ʹ���жϷ�ʽ

    // ceTft320->ceL36.ceI2cMaster.ceResource = (CE_RESOURCE)(ceL36  + CE_RES_MARK_L36_I2C);     //��ʱû���õ�I2c���
    // ceTft320->ceL36.ceI2cMaster.ceI2cMasterSpeed = CE_I2C_SPEED_400KBPS;
    // ceI2cMasterOp.initial(&(ceTft320->ceL36.ceI2cMaster));

    ceTft320->ceL36.ceGpioEx0.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_GPIO_EX0);
    ceTft320->ceL36.ceGpioEx0.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceTft320->ceL36.ceGpioEx0));
    ceGpioOp.setBit(&(ceTft320->ceL36.ceGpioEx0));

    ceTft320->ceL36.ceGpioEx1.ceResource = (CE_RESOURCE)(ceL36 + CE_RES_MARK_L36_GPIO_EX1);
    ceTft320->ceL36.ceGpioEx1.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceTft320->ceL36.ceGpioEx1));
    ceGpioOp.setBit(&(ceTft320->ceL36.ceGpioEx1));

    ceTft320_ceTft320 = ceTft320;
    ceTft320_tftInitial();//Tft����ʼ��
    cePwmOp.start(&(ceTft320->ceL36.cePwm));

    if(callBackTouch != CE_NULL)
    {
        ceTft320->callBackTouch = callBackTouch;//��ʼ�������ص�����CeTask��ִ�У�����ʱ��ʹ���жϵķ�ʽ
        
        ceTft320->ceTask.ID = ceTft320->ceL36.ceResource;
        ceTft320->ceTask.callBack = ceTft320_callBackTouch;
        ceTft320->ceTask.pAddPar = ceTft320;
#ifdef __CE_USE_RTOS__
        ceTft320->ceTask.isNewThread = 0x01;
        ceTft320->ceTask.taskPriority = CE_TASK_PRIORITY_M;
        ceTft320->ceTask.ID = ceL36;
        ceTft320->ceTask.pAddPar = ceTft320;
        ceTft320->ceTask.taskName = "CeTft320 Touch Task";
        ceTft320->ceTask.callBack= ceTft320_callBackTouch;//���ȡ�����㣬������ж���ִ�У��Ứ�Ѵ���ʱ�䣬���������ѭ��ɨ��ķ�ʽ����ȡ������
        ceTft320->ceTask.taskStackBuf = ceTft320_taskBuf;
        ceTft320->ceTask.taskStackBufSize = CE_TFT320_TASK_STACK_BUF_SIZE;
#endif
        ceTaskOp.registerTask(&(ceTft320->ceTask));
        ceTaskOp.start(&(ceTft320->ceTask));
    }
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeTft320ģ�����������
  */
const CeTft320Op ceTft320Op = {ceTft320_initial, ceTft320_setOn, ceTft320_calibration, ceTft320_setBrightness, ceTft320_fill, ceTft320_drawPoint,
                                    ceTft320_drawRectangle, ceTft320_drawData, ceTft320_showString, ceTft320_showInt, ceTft320_showCN1616, ceTft320_appendString,
                                    ceTft320_setOff, ceTft320_getFontData,
                                    ceTft320_getTouchAdX,ceTft320_getTouchAdY};

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeOled130.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeOled130ģ�������ͷ�ļ�
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
#define __CE_OLED130_VERSION__ 1                                               /*!< �������ļ��İ汾��*/
#define __CE_OLED130_NEED_CREELINKS_VERSION__ 1                                /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_OLED130_NEED_CREELINKS_VERSION__)         /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeOled130.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
#define CE_OLED130_WIDTH     128
#define CE_OLED130_HIGHT     64
/*
 *CeOled130���Զ���
 */
typedef struct
{
    CeI2cMaster ceI2cMaster;
    char asBuf[CE_OLED130_WIDTH / 6][CE_OLED130_HIGHT / 8];/*!< ���ڴ�ӡ������Ϣ�Ļ���*/
    uint16 asXIndex;                                   /*!< ���ڴ�ӡ������Ϣ�Ĺ��x��*/
    uint16 asYIndex;                                   /*!< ���ڴ�ӡ������Ϣ�Ĺ��y��*/
}
CeOled130;

typedef enum
{
    CE_OLED130_EN_SIZE_F6X8 = 0x01,                    /*!< CeOled130ʹ��6*8�ĵ�����������ʾ*/
    CE_OLED130_EN_SIZE_F8X16,                          /*!< CeOled130ʹ��8*16�ĵ�����������ʾ*/
} CE_OLED130_EN_SIZE;
/*
 *CeOled130��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeOled130* ceOled130,CE_RESOURCE ceI2c);/*!<
                                                         @brief CeOled130ģ���ʼ��
                                                         @param ceOled130:CeOled130���Զ���ָ��
                                                         @param ceI2c:CeOled130ģ��ʹ�õ���Դ��*/

    void        (*setOn)(CeOled130* ceOled130);     /*!< @brief CeOled130����ʾ
                                                         @param ceOled130:CeOled130���Զ���ָ��*/

    void        (*fill)(CeOled130* ceOled130, uint8 fillData);/*!<
                                                         @brief CeOled130��ָ�����ݽ���ȫ�����
                                                         @param ceOled130:CeOled130���Զ���
                                                         @param fillData:ȫ����������*/

    void        (*clr)(CeOled130* ceOled130);       /*!< @brief CeOled130����
                                                         @param ceOled130:CeOled130���Զ���*/

    void        (*showString)(CeOled130* ceOled130, uint8 x, uint8 y, char* msg, CE_OLED130_EN_SIZE showSize);/*!<
                                                         @brief CeOled130��ʾ�ַ���
                                                         @param ceOled130:CeOled130���Զ���
                                                         @param x:���ÿ�ʼ��ʾ�ַ�����x�����ꡣ
                                                         @param y:���ÿ�ʼ��ʾ�ַ�����y������(Ҳ���������꣬CeOled130������ʾ8��F6x8����4��F8x16�����壬��Χ0-7)
                                                         @param msg:Ҫ��ʾ���ַ���ָ��
                                                         @param showSize:��ʾ�������С����ѡCE_OLED_SIZE_F6X8��CE_OLED_SIZE_F8X16*/

    void        (*showInt)(CeOled130* ceOled130, uint8 x, uint8 y, int32 val, CE_OLED130_EN_SIZE showSize);/*!<
                                                         @brief CeOled130��ʾ32λ�з��ŵ�����
                                                         @param ceOled130:CeOled130���Զ���
                                                         @param x:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�x������
                                                         @param y:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�y������(Ҳ���������꣬CeOled130������ʾ8��F6x8����4��F8x16�����壬��Χ0-3)
                                                         @param val:Ҫ��ʾ��32λ�з��ŵ�����
                                                         @param showSize:��ʾ�������С����ѡCE_OLED_SIZE_F6X8��CE_OLED_SIZE_F8X16*/

    void        (*showCN1616)(CeOled130* ceOled130, uint8 x, uint8 y, const uint8* cn1616);/*!<
                                                         @brief CeOled130��ʾ16x16�ĺ���
                                                         @param ceOled130:CeOled130���Զ���
                                                         @param x:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�x������
                                                         @param y:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�y������(Ҳ���������꣬CeOled130������ʾ4��16x16�ĺ��֣���Χ0-3)
                                                         @param cn1616:Ҫ��ʾ�ĺ�����ģ���ɴ�"CeCN1616.h"�л�ȡ*/

    void        (*drawData)(CeOled130* ceOled130, uint8 x, uint8 y, uint8 dataWidth, uint8 dataHight, const uint8* dataBuf);/*!<
                                                         @brief CeOled130��ʾͼƬ��
                                                         @param ceOled130:CeOled130���Զ���
                                                         @param x:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�x������
                                                         @param y:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�y�����꣨Ҳ���������꣬��Χ0-7��
                                                         @param dataWidth:�������ݻ�ͼ��Ŀ�������Ϊ��λ��
                                                         @param dataHightm:�������ݻ�ͼ��ĸߣ����ֽ�Ϊ��λ��
                                                         @param cn1616:Ҫ��ʾ��ͼƬ���ݣ��й�ͼƬ�Ĵ�С��ȡģ��ϸ���ֿɲ鿴ģ��ʹ���ֲ�*/

    void        (*appendString)(CeOled130* ceOled130, const char* msg);/*!<
                                                         @brief һ�����ڴ�����ԣ��Կ���̨�ķ�ʽ��ӡ������Ϣ
                                                         @param ceOled130:CeOled130���Զ���
                                                         @param msg:Ҫ��ʾ����Ϣ*/

    void        (*setOff)(CeOled130* ceOled130);    /*!< @brief CeOled130�ر���ʾ
                                                         @param ceOled130:CeOled130���Զ���ָ��*/
}CeOled130Op;
/*
 *CeOled130��������ʵ��
 */
extern const CeOled130Op ceOled130Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_OLED130_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_OLED130_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function �����ϴ�ӡӢ�ĺ����ĺ���
******************************************************************************
#include "Creelinks.h"
#include "CeOled130.h"

const unsigned char CN1616_B4B4[] = //��
{ 0x0C, 0x06, 0x0C, 0x06, 0x1E, 0x06, 0x1B, 0x36, 0x31, 0xB6, 0x60, 0xF6, 0xFF, 0x36, 0x33, 0x36, 0x33, 0x36, 0x33, 0x36, 0x3F, 0x36, 0x36, 0x36, 0x30, 0xC6, 0x30, 0xC6, 0x1F, 0xDE, 0x00, 0x0C };
const unsigned char CN1616_A3E5[] = //��
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x06, 0x60, 0x0C, 0x30, 0x0F, 0xF0, 0x0C, 0x00, 0x0C, 0x00, 0x06, 0x30, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned char CN1616_C1AA[] = //��
{0x00, 0xCC, 0xFE, 0x6C, 0x6C, 0x78, 0x6C, 0x00, 0x7D, 0xFE, 0x6C, 0x30, 0x6C, 0x30, 0x7C, 0x30, 0x6F, 0xFF, 0x6C, 0x30, 0x6E, 0x78, 0x7C, 0x78, 0xEC, 0xCC, 0x0C, 0xCC, 0x0D, 0x86, 0x0F, 0x03};

const unsigned char CN1616_B1B1[] = //��
{0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x66, 0x06, 0x6C, 0x7E, 0x78, 0x06, 0x70, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x60, 0x06, 0x63, 0x1E, 0x63, 0xF6, 0x63, 0x66, 0x3F, 0x06, 0x00};
const unsigned char CN1616_BEA9[] = //��
{0x03, 0x00, 0x01, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0xF8, 0x01, 0x80, 0x19, 0x98, 0x19, 0x8C, 0x31, 0x86, 0x67, 0x86, 0x03, 0x00};
const unsigned char CN1616_B4F3[] = //��
{0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0xFF, 0xFF, 0x01, 0x80, 0x01, 0x80, 0x03, 0xC0, 0x03, 0xC0, 0x06, 0x60, 0x06, 0x60, 0x0C, 0x30, 0x18, 0x18, 0x30, 0x0C, 0xE0, 0x07};
const unsigned char CN1616_D0C5[] = //��
{0x0C, 0x60, 0x0C, 0x30, 0x0F, 0xFF, 0x18, 0x00, 0x18, 0x00, 0x39, 0xFE, 0x38, 0x00, 0x78, 0x00, 0xD9, 0xFE, 0x18, 0x00, 0x18, 0x00, 0x19, 0xFE, 0x19, 0x86, 0x19, 0x86, 0x19, 0xFE, 0x19, 0x86};
const unsigned char CN1616_BFC6[] = //��
{0x0C, 0x18, 0x1F, 0x98, 0xF8, 0xD8, 0x18, 0xD8, 0x18, 0x18, 0xFF, 0x98, 0x18, 0xD8, 0x3C, 0xD8, 0x3E, 0x18, 0x78, 0x1F, 0x7B, 0xF8, 0xD8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
const unsigned char CN1616_BCBC[] = //��
{0x18, 0x30, 0x18, 0x30, 0x18, 0x30, 0x1B, 0xFF, 0xFE, 0x30, 0x18, 0x30, 0x18, 0x30, 0x1F, 0xFE, 0x1C, 0xC6, 0x38, 0xCC, 0xF8, 0x6C, 0x18, 0x78, 0x18, 0x30, 0x18, 0x78, 0x79, 0xCC, 0x37, 0x07};

CeOled130 myOled;
int main(void)
{
    ceSystemOp.initial();                                   //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                              //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceOled130Op.initial(&myOled, R2TI2c);
    ceOled130Op.setOn(&myOled);
    while (1)
    {
        ceTaskOp.mainTask();                                //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
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

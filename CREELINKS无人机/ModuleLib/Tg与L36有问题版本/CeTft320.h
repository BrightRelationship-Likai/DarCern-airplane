/**
  ******************************************************************************
  * @file    CeTft320.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeTft320ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)CeTft320ʹ��L36�ڣ������һ�����İ壬����һ��L36�ڣ���ֻ���ڳ�ʼ��ʱ�ṩ
  *  CeTft320���Զ���ָ�룬���������������ṩ��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_TFT320_H__
#define __CE_TFT320_H__

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus


#include "Creelinks.h"
#define __CE_TFT320_VERSION__ 1                                         /*!< �������ļ��İ汾��*/
#define __CE_TFT320_NEED_CREELINKS_VERSION__ 1                          /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_TFT320_NEED_CREELINKS_VERSION__)   /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeTft320.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else

#define CE_TFT320_USE_BUFFER                /*!< �Ƿ�ʹ�û��壬�����ڴ��п���(WIDTH * HIGHT * 2)�Ļ��棬�������ʾЧ��*/

//#define CE_TFT320_SHOW_HORIZONTAL         /*!< �����Ҫ������ʾ��������� ע��V1.0�汾�ݽ�֧������*/

#ifdef CE_TFT320_SHOW_HORIZONTAL
#define CE_TFT320_WIDTH     400
#define CE_TFT320_HIGHT     240
#else
#define CE_TFT320_WIDTH     240
#define CE_TFT320_HIGHT     400
#endif

#define CE_TFT320_DRAW_POINT(x, y, color)                   ceTft320Op.drawPoint((x), (y), (color));
#define CE_TFT320_DRAW_RECTANGLE( sX, sY, eX, eY, color)    ceTft320Op.drawRectangle((sX), (sY), (eX), (eY), (color));

/**
  * @brief  ö�٣�CeTft320��������ʾ����ɫ�б�
  */
typedef enum
{
    CE_TFT320_COLOR_RED     =   0xF800,                         /*!< ��ɫ*/
    CE_TFT320_COLOR_GREEN   =   0x07E0,                         /*!< ��ɫ*/
    CE_TFT320_COLOR_BLUE    =   0x001F,                         /*!< ��ɫ*/
    CE_TFT320_COLOR_WHITE   =   0xFFFF,                         /*!< ��ɫ*/
    CE_TFT320_COLOR_BLACK   =   0x0000,                         /*!< ��ɫ*/
    CE_TFT320_COLOR_YELLOW  =   0xFFE0,                         /*!< ��ɫ*/
    CE_TFT320_COLOR_GRAY0   =   0xEF7D,                         /*!< �Ұ�ɫ*/
    CE_TFT320_COLOR_GRAY1   =   0x8410,                         /*!< ǳ��ɫ*/
    CE_TFT320_COLOR_GRAY2   =   0x4208,                         /*!< ��ɫ*/
} CE_TFT320_COLOR_LIST;

/**
  * @brief  ö�٣�CeTft320������ʾӢ���ַ�����ģ��С
  */
typedef enum
{
    CE_TFT320_EN_SIZE_F6X8,                                     /*!< �ַ���ռ6�����ص㣬��ռ8�����ص�*/
    CE_TFT320_EN_SIZE_F8X16,                                    /*!< �ַ���ռ8�����ص㣬��ռ16�����ص�*/
} CE_TFT320_EN_SIZE;

/**
  * @brief  ö�٣�CeTft320������ʾ�����ַ�����ģ��С
  */
typedef enum
{
    CE_TFT320_GBK_TYPE_16X16,                                   /*!< �����ַ���ռ16�����ص㣬��ռ16�����ص�*/
} CE_TFT320_GBK_TYPE;

/**
  *CeTft320���Զ���
  */
typedef struct
{
    CeL36   ceL36;                                              /*!< ģ��ʹ�õ���L36����Դ���Զ���*/
    CeTask  ceTask;                                             /*!< ��ģ��ʹ�õ���Task��������ѭ��ɨ��ķ�ʽ����ȡ�����㡣��Ϊ��ȡ�����㣬������ж���ִ�У��Ứ�Ѵ���ʱ�䣬����δ�����жϷ�ʽ*/
    void    (*callBackTouch)(int16 x, int16 y);                 /*!< ��Ŵ�����������ʱ����Ҫִ�еĺ��� x:�����µ�x������ֵ��y:�����µ�y������ֵ*/

    char    asBuf[CE_TFT320_WIDTH / 6][CE_TFT320_HIGHT / 8];    /*!< ���ڴ�ӡ������Ϣ�Ļ���*/
    uint16  asXIndex;                                           /*!< ���ڴ�ӡ������Ϣ�Ĺ��x��*/
    uint16  asYIndex;                                           /*!< ���ڴ�ӡ������Ϣ�Ĺ��y��*/
    int32   clbTempX[2];                                        /*!< ���ڴ�Ŵ�����У׼��x������ֵ*/
    int32   clbTempY[2];                                        /*!< ���ڴ�Ŵ�����У׼��y������ֵ*/
    uint8   isInCalibration;                                    /*!< ����ָʾ�Ƿ��ڴ�����У׼��*/
    uint16  deviceCode;                                         /*!< ��Ŵ�Tft����IC�ж�ȡ����ID*/
}CeTft320;

/**
  *CeTft320��������
  */
typedef struct
{
    CE_STATUS   (*initial)(CeTft320* ceTft320, CE_RESOURCE ceL36, void(*callBackTouch)(int16 x, int16 y));
                                                                /*!< @brief CeTft320ģ���ʼ��
                                                                     @param ceXX:CeTft320ģ��ʹ�õ���Դ��
                                                                     @param callBackTouch:������������ʱ����Ҫִ�еĺ��� x:�����µ�x������ֵ��y:�����µ�y������ֵ*/

    void        (*setOn)(void);                                 /*!< @brief ����ʾ*/

    CE_STATUS   (*calibration)(void);                           /*!< @brief ���д�����У׼
                                                                     @return У׼�ɹ����� CE_STATUS_SUCCESS��У׼ʧ�ܷ��� CE_STATUS_FAILE*/

    void        (*setBrightness)(uint8 brightness);             /*!< @brief ������Ļ����
                                                                     @param brightness:�����Ȱٷֱȣ�0��100*/

    void        (*fill)(uint16 color);                          /*!< @brief CeTft320��ָ������(��ɫ)����ȫ�����
                                                                     @param color:ȫ����������(��ɫ)*/

    void        (*drawPoint)(int16 x, int16 y, uint16 color);   /*!< @brief CeTft320��ָ��λ�û���
                                                                     @param x:���ÿ�ʼ��ʾ�ַ�����x������
                                                                     @param y:���ÿ�ʼ��ʾ�ַ�����y������
                                                                     @param color:Ҫ��ʾ������(��ɫ)*/

    void        (*drawRectangle)(uint16 startX, uint16 startY, uint16 endX, uint16 endY, uint16 color);/*!<
                                                                     @brief CeTft320���ƾ���
                                                                     @param startX:�������Ͻ�x����
                                                                     @param startY:�������Ͻ�y����
                                                                     @param endX:�������½�x����
                                                                     @param endY:�������½�y����
                                                                     @param color:Ҫ��ʾ������(��ɫ)*/

    void        (*drawData)(uint16 x, uint16 y, const uint8* colorBuf, uint16 bufSizeWidth, uint16 bufSizeHight);/*!<
                                                                     @brief CeTft320����ͼƬ
                                                                     @param x:ͼƬ����ʼ��x����
                                                                     @param y:ͼƬ����ʼ��y����
                                                                     @param colorBuf:ͼƬ����
                                                                     @param bufSizeWidth:ͼƬ��
                                                                     @param bufSizeHight:ͼƬ��*/

    void        (*showString)(int16 x, int16 y, uint16 foreColor, uint16 backColor, const char* msg, CE_TFT320_EN_SIZE showSize);/*!<
                                                                     @brief CeTft320��ʾ�ַ�������֧������
                                                                     @param x:���ÿ�ʼ��ʾ�ַ�����x������
                                                                     @param y:���ÿ�ʼ��ʾ�ַ�����y������
                                                                     @param foreColor:��ʾ�����ǰ��ɫ
                                                                     @param backColor:��ʾ����ı���ɫ
                                                                     @param msg:Ҫ��ʾ���ַ���ָ��
                                                                     @param  showSize:��ʾ�������С����ѡCE_LCD_EN_SIZE_F6X8��CE_LCD_EN_SIZE_F8X16*/

    void        (*showInt)(int16 x, int16 y, uint16 foreColor, uint16 backColor, const int32 val, CE_TFT320_EN_SIZE showSize);/*!<
                                                                     @brief CeTft320��ʾ32λ�з��ŵ����֣����ֵ0x7FFFFFFF����Сֵ0x80000001
                                                                     @param x:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�x������
                                                                     @param y:���ÿ�ʼ��ʾ32λ�з��ŵ����ֵ�y������
                                                                     @param foreColor:��ʾ�����ǰ��ɫ
                                                                     @param backColor:��ʾ����ı���ɫ
                                                                     @param val:Ҫ��ʾ��32λ�з��ŵ�����
                                                                     @param showSize:��ʾ�������С����ѡCE_LCD_EN_SIZE_F6X8��CE_LCD_EN_SIZE_F8X16*/

    void        (*showCN1616)(int16 x, int16 y, uint16 foreColor, uint16 backColor, const uint8* cn1616);/*!<
                                                                     @brief CeTft320��ʾ16x16���������壬��ģcn1616�ɴ�CeCN1616.h�л�ȡ
                                                                     @param x:���ÿ�ʼ��ʾ�ַ�����x������
                                                                     @param y:���ÿ�ʼ��ʾ�ַ�����y������
                                                                     @param foreColor:��ʾ�����ǰ��ɫ
                                                                     @param backColor:��ʾ����ı���ɫ
                                                                     @param cn1616:Ҫ��ʾ������ģ����ģcn1616�ɴ�CeCN1616.h�л�ȡ*/

    void        (*appendString)(const char* msg);               /*!< @brief һ�����ڴ�����ԣ��Կ���̨�ķ�ʽ��ӡ������Ϣ
                                                                     @param msg:Ҫ��ʾ����Ϣ*/

    void        (*setOff)(void);                                /*!< @brief �ر���ʾ*/

    void        (*getFontData)(char* msgGBK, uint8* outBuf, CE_TFT320_GBK_TYPE ceTft320GBKType);/*!<
                                                                     @brief ����ģоƬ�л�ȡ����
                                                                     @param ceTft320:CeTft320���Զ���*/

    uint32  (*getTouchAdX)(void);

    uint32 (*getTouchAdY)(void);
}CeTft320Op;

/**
  *CeTft320��������ʵ��
  */
extern const CeTft320Op ceTft320Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_TFT320_NEED_CREELINKS_VERSION__)

#ifdef __cplusplus
 }
#endif //__cplusplus

#endif //__CE_TFT320_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ��CeTft320Һ��������ʾ���֡�Ӣ�ģ���ʵ�ִ�������д
******************************************************************************
#include "Creelinks.h"
#include "CeTft320.h"
CeTft320 myTft320;
uint8 fontTemp[32];
void touchPressCallBack(int16 x, int16 y)                         //������Ļ����õĻص�
{
    ceTft320Op.drawPoint(x,y,CE_TFT320_COLOR_WHITE);
}

int main(void)
{
    ceSystemOp.initial();                                         //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                                    //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceTft320Op.initial(&myTft320,R26L36,touchPressCallBack);
    ceDebugOp.registerAppendString(ceTft320Op.appendString);     //ע�������Ϣ��ʾ����
    ceSystemOp.delayMs(1000);
    ceTft320Op.calibration();                                     //����У׼����������
    ceSystemOp.delayMs(2000);
    ceSystemOp.unRegisterAppendString();                          //ȡ��ע�������Ϣ��ʾ����

    ceTft320Op.fill(CE_TFT320_COLOR_RED);
    ceSystemOp.delayMs(1000);
    ceTft320Op.fill(CE_TFT320_COLOR_GREEN);
    ceSystemOp.delayMs(1000);
    ceTft320Op.fill(CE_TFT320_COLOR_BLUE);
    ceSystemOp.delayMs(1000);
    ceTft320Op.fill(CE_TFT320_COLOR_BLACK);

    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616( 96, 160,CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK, fontTemp);
    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616(96 + 16, 160,CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK, fontTemp);
    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616( 96 + 32, 160, CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK,fontTemp);

    ceTft320Op.showString( 84, 176, CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK,"CREELINKS", CE_TFT320_EN_SIZE_F8X16);

    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616( 56+16*1, 192, CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK,fontTemp);
    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616( 56+16*2, 192, CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK,fontTemp);
    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616( 56+16*3, 192,CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK, fontTemp);
    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616( 56+16*4, 192,CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK, fontTemp);
    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616( 56+16*5, 192,CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK, fontTemp);
    ceTft320Op.getFontData("��",fontTemp,CE_TFT320_GBK_TYPE_16X16);
    ceTft320Op.showCN1616( 56+16*6, 192,CE_TFT320_COLOR_WHITE,CE_TFT320_COLOR_BLACK, fontTemp);

    ceSystemOp.delayMs(2000);
    ceTft320Op.fill(CE_TFT320_COLOR_BLACK);     //ˢ����������ʼ��д��Ӧ
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
    };
}
******************************************************************************
*/

/**
******************************************************************************
* @file       main.c
* @author     Creelinks Application Team
* @version    V1.1.0
* @date       2016-11-10
* @brief      ����ǰ��̨���㱼��Creelinksƽ̨����ں���
******************************************************************************
* @attention
*1)��uCGUI_Config/LCDConf.h���޸ĺ궨��LCD_XSIZE��LCD_YSIZE��LCD_BITSPERPIXEL��
*1)��uCGUI������������ʾģ��ʱ����������Ҫ�����¹�����
*   a,���ģ�������⵽����
*   b,��uCGUI_LCDDriver\LCDDummy.c,�����ļ������ͷ�ļ�������������ʾģ���������ӣ�#include"CeTft320.h"��CeTft320 myTft320;
*   c,��LCDDummy.c�ļ����ҵ�int  LCD_L0_Init(void)�������������������ʾģ���ʼ������������ӣ�ceTft320Op.initial(&myTft320,R26L36,touchCallBack);
*   d,�ں���LCD_L0_SetPixelIndex�����ģ�黭�㺯������ceTft320Op.drawPoint(x,y,PixelIndex)��Ҳ���޸��ļ��������������ʾЧ�ʡ�

* <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
******************************************************************************
*/

#include "Creelinks.h"
#include "GUI.h"

void DemoShowColorBar(void)
{
    int x0 = 60, y0 = 40, yStep = 15, i;
    int xsize = LCD_GetDevCap(LCD_DEVCAP_XSIZE) - x0;
    GUI_SetFont(&GUI_Font8x16);
#if (LCD_FIXEDPALETTE)
    y0 = 66;
    yStep = 13;
    GUI_DispStringAt("Fixed palette: ", 0, 40);
    GUI_DispDecMin(LCD_FIXEDPALETTE);
#endif
    GUI_DispStringAt("Red", 0, y0 + yStep);
    GUI_DispStringAt("Green", 0, y0 + 3 * yStep);
    GUI_DispStringAt("Blue", 0, y0 + 5 * yStep);
    GUI_DispStringAt("Grey", 0, y0 + 6 * yStep);
    GUI_DispStringAt("Yellow", 0, y0 + 8 * yStep);
    GUI_DispStringAt("Cyan", 0, y0 + 10 * yStep);
    GUI_DispStringAt("Magenta", 0, y0 + 12 * yStep);
    for (i = 0; i < xsize; i++) {
        U16 cs = (255 * (U32)i) / xsize;
        U16 x = x0 + i;;
        /* Red */
        GUI_SetColor(cs);
        GUI_DrawVLine(x, y0 , y0 + yStep - 1);
        GUI_SetColor(0xff + (255 - cs) * 0x10100L);
        GUI_DrawVLine(x, y0 + yStep, y0 + 2 * yStep - 1);
        /* Green */
        GUI_SetColor(cs<<8);
        GUI_DrawVLine(x, y0 + 2 * yStep, y0 + 3 * yStep - 1);
        GUI_SetColor(0xff00 + (255 - cs) * 0x10001L);
        GUI_DrawVLine(x, y0 + 3 * yStep, y0 + 4 * yStep - 1);
        /* Blue */
        GUI_SetColor(cs * 0x10000L);
        GUI_DrawVLine(x, y0 + 4 * yStep, y0 + 5 * yStep - 1);
        GUI_SetColor(0xff0000 + (255 - cs) * 0x101L);
        GUI_DrawVLine(x, y0 + 5 * yStep, y0 + 6 * yStep - 1);
        /* Gray */
        GUI_SetColor((U32)cs * 0x10101L);
        GUI_DrawVLine(x, y0 + 6 * yStep, y0 + 7 * yStep - 1);
        /* Yellow */
        GUI_SetColor(cs * 0x101);
        GUI_DrawVLine(x, y0 + 7 * yStep, y0 + 8 * yStep - 1);
        GUI_SetColor(0xffff + (255 - cs) * 0x10000L);
        GUI_DrawVLine(x, y0 + 8 * yStep, y0 + 9 * yStep - 1);
        /* Cyan */
        GUI_SetColor(cs * 0x10100L);
        GUI_DrawVLine(x, y0 + 9 * yStep, y0 + 10 * yStep - 1);
        GUI_SetColor(0xffff00 + (255 - cs) * 0x1L);
        GUI_DrawVLine(x, y0 + 10 * yStep, y0 + 11 * yStep - 1);
        /* Magenta */
        GUI_SetColor(cs * 0x10001);
        GUI_DrawVLine(x, y0 + 11 * yStep, y0 + 12 * yStep - 1);
        GUI_SetColor(0xff00ff + (255 - cs) * 0x100L);
        GUI_DrawVLine(x, y0 + 12 * yStep, y0 + 13 * yStep - 1);
    }
}




int main(void)
{
    ceSystemOp.initial();							//Creelinks������ʼ��
    ceSystemOp.initialDebug(R14Uart);				//ͨ��Uart�������Debug��Ϣ����λ��
	//TODO:���ڴ˴�����ģ���ʼ���Ȳ���
	GUI_Init(); 
	GUI_SetBkColor(GUI_BLUE); 
	GUI_SetColor(GUI_WHITE);
	//GUI_Clear();
	GUI_DispStringAt("Hello World ..",10,10); 
    DemoShowColorBar();
	while (1)
	{
		ceSystemOp.mainTask();						//Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���		

	};
}

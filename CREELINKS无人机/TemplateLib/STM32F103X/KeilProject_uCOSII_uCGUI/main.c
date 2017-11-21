/**
******************************************************************************
* @file       main.c
* @author     Creelinks Application Team
* @version    V1.1.0
* @date       2016-11-10
* @brief      基于前后台（裸奔）Creelinks平台主入口函数
******************************************************************************
* @attention
*1)在uCGUI_Config/LCDConf.h中修改宏定义LCD_XSIZE，LCD_YSIZE，LCD_BITSPERPIXEL，
*1)在uCGUI环境中增加显示模块时，驱动中需要做如下工作：
*   a,添加模块驱动库到工程
*   b,打开uCGUI_LCDDriver\LCDDummy.c,并在文件中添加头文件包含及定义显示模块对象，如添加：#include"CeTft320.h"和CeTft320 myTft320;
*   c,在LCDDummy.c文件中找到int  LCD_L0_Init(void)函数，并在其中添加显示模块初始化函数，如添加：ceTft320Op.initial(&myTft320,R26L36,touchCallBack);
*   d,在函数LCD_L0_SetPixelIndex中添加模块画点函数，如ceTft320Op.drawPoint(x,y,PixelIndex)，也可修改文件中其它以提高显示效率。

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
    ceSystemOp.initial();							//Creelinks环境初始化
    ceSystemOp.initialDebug(R14Uart);				//通过Uart串口输出Debug信息到上位机
	//TODO:请在此处插入模块初始化等操作
	GUI_Init(); 
	GUI_SetBkColor(GUI_BLUE); 
	GUI_SetColor(GUI_WHITE);
	//GUI_Clear();
	GUI_DispStringAt("Hello World ..",10,10); 
    DemoShowColorBar();
	while (1)
	{
		ceSystemOp.mainTask();						//Creelinks环境主循环任务，请保证此函数能够被周期调用		

	};
}


#include "GUITouchConf.h"
#include "GUI.h"

#include "CeTft320.h"

int16 touchPressX;
int16 touchPressY;

void touchPressCallBack(int16 x, int16 y)
{
	touchPressX = x;
	touchPressY = y;
	GUI_TOUCH_Exec();
}

//有关触摸相关的函数
void GUI_TOUCH_X_ActivateX(void) 
{
	
}

void GUI_TOUCH_X_ActivateY(void) 
{
	
}
int  GUI_TOUCH_X_MeasureX(void) 
{
	return touchPressX;
}
	
int  GUI_TOUCH_X_MeasureY(void)
{
	return touchPressY;
}

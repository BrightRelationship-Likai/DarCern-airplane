/**
  ******************************************************************************
  * @file    Ce8Segx2.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于Ce8Segx2模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2017 Darcern</center></h2>
  ******************************************************************************
  */
#include "Ce8Segx2.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
 * @brief   Ce8Segx2使用的8段数码管的字模
 */
const uint8 ce8Segx2_table[95] =
{
    0xFF,/*" ",0*/
    0xFD,/*"!",1*/
    0xBB,/*""",2*/
    0xFD,/*"#",3*/
    0xFD,/*"$",4*/
    0xFD,/*"%",5*/
    0xFD,/*"&",6*/
    0xFB,/*"'",7*/
    0x63,/*"(",8*/
    0x0F,/*")",9*/
    0xFD,/*"*",10*/
    0xFD,/*"+",11*/
    0xFD,/*",",12*/
    0xFD,/*"-",13*/
    0xFD,/*".",14*/
    0xFD,/*"/",15*/
    0x03,/*"0",16*/
    0x9F,/*"1",17*/
    0x25,/*"2",18*/
    0x0D,/*"3",19*/
    0x99,/*"4",20*/
    0x49,/*"5",21*/
    0x41,/*"6",22*/
    0x1F,/*"7",23*/
    0x01,/*"8",24*/
    0x09,/*"9",25*/
    0xFD,/*":",26*/
    0xFD,/*";",27*/
    0xFD,/*"<",28*/
    0xED,/*"=",29*/
    0xFD,/*">",30*/
    0x2F,/*"?",31*/
    0xFD,/*"@",32*/
    0x11,/*"A",33*/
    0xC1,/*"B",34*/
    0x63,/*"C",35*/
    0x85,/*"D",36*/
    0x61,/*"E",37*/
    0x71,/*"F",38*/
    0x43,/*"G",39*/
    0x91,/*"H",40*/
    0x0F,/*"I",41*/
    0x07,/*"J",42*/
    0xA1,/*"K",43*/
    0xE3,/*"L",44*/
    0x55,/*"M",45*/
    0x13,/*"N",46*/
    0x03,/*"O",47*/
    0x31,/*"P",48*/
    0x19,/*"Q",49*/
    0xF5,/*"R",50*/
    0x49,/*"S",51*/
    0xE1,/*"T",52*/
    0x83,/*"U",53*/
    0xC7,/*"V",54*/
    0x47,/*"W",55*/
    0xD9,/*"X",56*/
    0x89,/*"Y",57*/
    0xA5,/*"Z",58*/
    0x63,/*"[",59*/
    0xFD,/*"\",60*/
    0x0F,/*"]",61*/
    0xFD,/*"^",62*/
    0xEF,/*"_",63*/
    0xBF,/*"'",64*/
    0x11,/*"a",65*/
    0xC1,/*"b",66*/
    0xE5,/*"c",67*/
    0x85,/*"d",68*/
    0x21,/*"e",69*/
    0x71,/*"f",70*/
    0x09,/*"g",71*/
    0xD1,/*"h",72*/
    0xF7,/*"i",73*/
    0x87,/*"j",74*/
    0x51,/*"k",75*/
    0xF3,/*"l",76*/
    0x55,/*"m",77*/
    0xD5,/*"n",78*/
    0xC5,/*"o",79*/
    0x31,/*"p",80*/
    0x19,/*"q",81*/
    0xF5,/*"r",82*/
};

/**
 * @brief  向74HC595写数据
 * @param  ceTg:Ce8Segx2属性对象中的CeTg
 * @param  data:欲写到74HC595de595的数据
 * @return None
 */
void ce8Segx2_write595Byte(CeTg* ceTg, uint16 data)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
        if ((data & 0x0001) == 0x0000)
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
        } else
        {
            ceGpioOp.setBit(&(ce8Segx1->ceGpio1));
        }

        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ce8Segx1->ceGpio0));
        ceSystemOp.delayUs(1);
        data >>= 1;
    }
    ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
}

/**
  * @brief  Ce8Segx2模块内部用到的初始化
  * @param  ce8Segx2:Ce8Segx2属性对象
  * @return None
  */
void ce8Segx2_initial(Ce8Segx2* ce8Segx2)
{
    ceGpioOp.resetBit(&(ce8Segx2->ceTg)); //SRCL
    ceGpioOp.resetBit(&(ce8Segx2->ceTg)); //SER
    ceGpioOp.resetBit(&(ce8Segx2->ceTg)); //RCLK
    ce8Segx2->showTable0 = 0xFF; //共阳
    ce8Segx2->showTable1 = 0xFF; //共阳
    ce8Segx2_write595Byte(&(ce8Segx2->ceTg), ((0x0000 | ce8Segx2->showTable0) << 8 | ce8Segx2->showTable1));
}

/**
  * @brief  Ce8Segx2模块使用三个Gpio口来完成初始化
  * @param  ce8Segx2:Ce8Segx2属性对象
  * @param  ceGpio0:Ce8Segx2模块使用的第一个Gpio的资源号
  * @param  ceGpio1:Ce8Segx2模块使用的第二个Gpio的资源号
  * @param  ceGpio2:Ce8Segx2模块使用的第三个Gpio的资源号
  * @return 系统状态码
  */
CE_STATUS ce8Segx2_initialByGpio(Ce8Segx2* ce8Segx2, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ce8Segx2->ceTg.ceResource = CE_NULL_RESOURCE;
    ce8Segx2->ceTg.ceResource0 = ceGpio0;
    ce8Segx2->ceTg.ceResource1 = ceGpio1;
    ce8Segx2->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ce8Segx2->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ce8Segx2_initial(ce8Segx2);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  Ce8Segx2模块使用Tg来完成初始化
  * @param  ce8Segx2:Ce8Segx2属性对象
  * @param  ceTg:Ce8Segx2模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ce8Segx2_initialByTg(Ce8Segx2* ce8Segx2, CE_RESOURCE ceTg)
{
    ce8Segx2->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ce8Segx2->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ce8Segx2_initial(ce8Segx2);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  使模块处于开启显示状态
  * @param  ce8Segx2:Ce8Segx2属性对象
  * @return None
  */
void ce8Segx2_setOn(Ce8Segx2* ce8Segx2)
{
    ce8Segx2_write595Byte(&(ce8Segx2->ceTg), ((0x0000 | ce8Segx2->showTable0) << 8 | ce8Segx2->showTable1));
}

/**
  * @brief  使模块处于关闭显示状态
  * @param  ce8Segx2:Ce8Segx2属性对象
  * @return None
  */
void ce8Segx2_setOff(Ce8Segx2* ce8Segx2)
{
    ce8Segx2_write595Byte(&(ce8Segx2->ceTg), 0xFFFF);
}

/**
 * @brief  显示小数点
 * @param  ce8Segx2:Ce8Segx2属性对象
 * @return None
 */
void ce8Segx2_setDpOn(Ce8Segx2* ce8Segx2, uint8 index)
{
    if (index == 0)
    {
        ce8Segx2->showTable0 &= ~0x01;
    }
    else
    {
        ce8Segx2->showTable1 &= ~0x01;
    }
    ce8Segx2_write595Byte(&(ce8Segx2->ceTg), (((0x0000 | ce8Segx2->showTable0) << 8) | ce8Segx2->showTable1));
}

/**
 * @brief  隐藏小数点
 * @param  ce8Segx2:Ce8Segx2属性对象
 * @return None
 */
void ce8Segx2_setDpOff(Ce8Segx2* ce8Segx2, uint8 index)
{
    if (index == 0)
    {
        ce8Segx2->showTable0 |= 0x01;
    }
    else
    {
        ce8Segx2->showTable1 |= 0x01;
    }
    ce8Segx2_write595Byte(&(ce8Segx2->ceTg), (((0x0000 | ce8Segx2->showTable0) << 8) | ce8Segx2->showTable1));
}

/**
 * @brief  显示十六进制数值
 * @param  ce8Segx2:Ce8Segx2属性对象
 * @param  val:欲显示的数值，范围00-99，模块显示00-99。数值的十位显示在第二段，数值的各位显示在第一段
 * @return None
 */
void ce8Segx2_setVal(Ce8Segx2* ce8Segx2, uint8 val)
{
    if ((val / 10) == 0)
    {
        ce8Segx2->showTable1 = 0xFF;//数值小于10，十位不显示
    }
    else
    {
        ce8Segx2->showTable1 = (ce8Segx2_table[((val / 10) + 16) % 95]) | (ce8Segx2->showTable1 & 0x01);//十位
    }

    ce8Segx2->showTable0 = (ce8Segx2_table[((val % 10) + 16) % 95]) | (ce8Segx2->showTable0 & 0x01);//个位

    ce8Segx2_write595Byte(&(ce8Segx2->ceTg), (((0x0000 | ce8Segx2->showTable0) << 8) | ce8Segx2->showTable1));
}

/**
 * @brief  显示字符
 * @param  ce8Segx2:Ce8Segx2属性对象
 * @param  msg:欲显示的字符，字符0-9或大小写英文字符（只有部分字符能完整的显示）
 * @return None
 */
void ce8Segx2_setChars(Ce8Segx2* ce8Segx2, char* msg)
{
    ce8Segx2->showTable1 = (ce8Segx2_table[(msg[0] - 0x20) % 95]) | (ce8Segx2->showTable1 & 0x01);
    ce8Segx2->showTable0 = (ce8Segx2_table[(msg[1] - 0x20) % 95]) | (ce8Segx2->showTable0 & 0x01);
    ce8Segx2_write595Byte(&(ce8Segx2->ceTg), (((0x0000 | ce8Segx2->showTable0) << 8) | ce8Segx2->showTable1));
}

const Ce8Segx2Op ce8Segx2Op = {ce8Segx2_initialByGpio, ce8Segx2_initialByTg, ce8Segx2_setOn, ce8Segx2_setOff, ce8Segx2_setDpOn, ce8Segx2_setDpOff, ce8Segx2_setVal, ce8Segx2_setChars};

#ifdef __cplusplus
 }
#endif //__cplusplus

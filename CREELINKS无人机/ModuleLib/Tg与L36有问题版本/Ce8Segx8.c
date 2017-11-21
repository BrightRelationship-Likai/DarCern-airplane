/**
  ******************************************************************************
  * @file    Ce8Segx8.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于Ce8Segx8模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)调试后需要小数点的位置！
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "Ce8Segx8.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_8SEGX8_DISPLAY_ON 0x8A           /*!< 关闭显示指令*/
#define CE_8SEGX8_DISPLAY_OFF 0x80          /*!< 开启显示指令*/
#define CE_8SEGX8_ADDRESS_FIX_MODE 0x44     /*!< 数码管的状态数组*/

/**
 * @brief   Ce8Segx8使用的8段数码管的字模
 */
const uint8 ce8Segx8_table[95] =
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
 * @brief  向TM1638写命令
 * @param  ceTg:Ce8Segx8属性对象中的CeTg
 * @param  val:欲写到74HC595de595的数据
 * @param  bitCode:欲操作的段位
 * @return None
 */
void ce8Segx8_WriteCmd(CeTg* ceTg, uint8 cmd)
{
    uint8 i;
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));//使能片选
    for (i = 0; i < 8; i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));//拉低CLK
        ceSystemOp.delayUs(1);
        if ((cmd & 0x01) == 0x01)
        {
            ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
        }
        else
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
        }
        cmd >>= 1;
        ceGpioOp.setBit(&(ce8Segx1->ceGpio1));//拉高CLK
        ceSystemOp.delayUs(1);
    }
    ceGpioOp.setBit(&(ce8Segx1->ceGpio0));//禁止片选
    ceSystemOp.delayUs(2);
}

/**
 * @brief  向TM1638写数据
 * @param  ceTg:Ce8Segx8属性对象中的CeTg
 * @param  val:欲写到74HC595de595的数据
 * @param  bitCode:欲操作的段位
 * @return None
 */
void ce8Segx8_WriteData(CeTg* ceTg, uint8 dig, uint8 data)
{
    uint8 i;
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));//使能片选
    for (i = 0; i < 8; i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));//拉低CLK
        ceSystemOp.delayUs(1);
        if ((dig & 0x01) == 0x01)
        {
            ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
        }
        else
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
        }
        dig >>= 1;//发送数据到信号线上
        ceGpioOp.setBit(&(ce8Segx1->ceGpio1));//拉高CLK
        ceSystemOp.delayUs(1);
    }

    for (i = 0; i < 8; i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));//拉低CLK
        ceSystemOp.delayUs(1);
        if ((data & 0x01) == 0x01)
        {
            ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
        }
        else
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
        }
        data >>= 1;//发送数据到信号线上
        ceGpioOp.setBit(&(ce8Segx1->ceGpio1));//拉高CLK
        ceSystemOp.delayUs(1);
    }
    ceGpioOp.setBit(&(ce8Segx1->ceGpio0));//禁止片选
    ceSystemOp.delayUs(2);
}

/**
  * @brief  向TM1638写入欲显示的数据
  * @param  ceT:Ce8Segx8属性对象中的CeTg
  * @param  showValBit:欲显示的数组数组指针
  * @return None
  */
void ce8Segx8_ShowData(CeTg* ceTg, uint8* showValBit)
{
    uint8 i;
    uint8 des[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8 src[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    src[0] = showValBit[4];//数码管的段顺序为，4567，01234，所以需要将数据移动一下。
    src[1] = showValBit[5];
    src[2] = showValBit[6];
    src[3] = showValBit[7];
    src[4] = showValBit[0];
    src[5] = showValBit[1];
    src[6] = showValBit[2];
    src[7] = showValBit[3];

    for (i = 0; i < 8; i++)
    {
        des[0] |= ((src[i] & 0x80) == 0) ? 0x00 : (0x80 >>i);
        des[1] |= ((src[i] & 0x40) == 0) ? 0x00 : (0x80 >>i);
        des[2] |= ((src[i] & 0x20) == 0) ? 0x00 : (0x80 >>i);
        des[3] |= ((src[i] & 0x10) == 0) ? 0x00 : (0x80 >>i);
        des[4] |= ((src[i] & 0x08) == 0) ? 0x00 : (0x80 >>i);
        des[5] |= ((src[i] & 0x04) == 0) ? 0x00 : (0x80 >>i);
        des[6] |= ((src[i] & 0x02) == 0) ? 0x00 : (0x80 >>i);
        des[7] |= ((src[i] & 0x01) == 0) ? 0x00 : (0x80 >>i);
    }
    for(i = 0; i < 8; i++)
    {
        ce8Segx8_WriteData(ceTg, 0xC0 + (i * 2), (~des[i]));//固定地址写数据，共阳方式
    }
}

/**
  * @brief  Ce8Segx8模块内部用到的初始化
  * @param  ce8Segx8:Ce8Segx8属性对象
  * @return None
  */
void ce8Segx8_initial(Ce8Segx8* ce8Segx8)
{
    uint8 index;
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_DISPLAY_OFF);
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_ADDRESS_FIX_MODE);//固定地址
    //ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), 0x87);//使用默认的脉冲宽度，因为设置最高和不设置好像是一样的。
    for(index = 0; index < 8; index++)
    {
        ce8Segx8_WriteData(&(ce8Segx8->ceTg), 0xC0 + (index * 2), 0x00);//清空显示寄存器，共阳，显示寄存器的时候只用到0x02,0x04,0x06,0x08,0x0A,0x0C
        ce8Segx8_WriteData(&(ce8Segx8->ceTg), 0xC0 + ((index * 2 ) + 1), 0x00);
        ce8Segx8->showValBit[index] = 0x00;
    }
    ce8Segx8_ShowData(&(ce8Segx8->ceTg), ce8Segx8->showValBit);
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_DISPLAY_ON);
}

/**
  * @brief  Ce8Segx8模块使用三个Gpio口来完成初始化
  * @param  ce8Segx8:Ce8Segx8属性对象
  * @param  ceGpio0:Ce8Segx8模块使用的第一个Gpio的资源号
  * @param  ceGpio1:Ce8Segx8模块使用的第二个Gpio的资源号
  * @param  ceGpio2:Ce8Segx8模块使用的第三个Gpio的资源号
  * @return 系统状态码
  */
CE_STATUS ce8Segx8_initialByGpio(Ce8Segx8* ce8Segx8, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ce8Segx8->ceTg.ceResource0 = ceGpio0;
    ce8Segx8->ceTg.ceResource1 = ceGpio1;
    ce8Segx8->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ce8Segx8->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ce8Segx8->ceTg));
    ceGpioOp.resetBit(&(ce8Segx8->ceTg));
    ceGpioOp.resetBit(&(ce8Segx8->ceTg));
    ce8Segx8_initial(ce8Segx8);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  Ce8Segx8模块使用Tg来完成初始化
  * @param  ce8Segx8:Ce8Segx8属性对象
  * @param  ceTg:Ce8Segx8模块使用的资源号
  * @return 系统状态码
  */
CE_STATUS ce8Segx8_initialByTg(Ce8Segx8* ce8Segx8, CE_RESOURCE ceTg)
{
    ce8Segx8->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ce8Segx8->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ce8Segx8->ceTg));
    ceGpioOp.resetBit(&(ce8Segx8->ceTg));
    ceGpioOp.resetBit(&(ce8Segx8->ceTg));
    ce8Segx8_initial(ce8Segx8);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  使模块处理开启显示状态
  * @param  ce8Segx8:Ce8Segx8属性对象指针
  */
void ce8Segx8_setOn(Ce8Segx8* ce8Segx8)
{
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_DISPLAY_ON);
}

/**
  * @brief  显示数值
  * @param  ce8Segx8:Ce8Segx8属性对象指针
  * @param  val:需要显示的值
  */
void ce8Segx8_setVal(Ce8Segx8* ce8Segx8, fp32 val)
{
    char temp[50];
    int8 point = (int8)((val - (int32)val) * 1000);//取出小数部分为三位；
    int index;
    int i;
    if (point == 0)
    {
        ceDebugOp.sprintf(temp, "%d", (int32)val);
        index = ceStringOp.strlen(temp);
        ce8Segx8->showValBit[0] = ((index - 1 >= 0) ? ce8Segx8_table[temp[index - 1] - 0x20] : 0xFF) & (~0x01);//小数点在二进制的哪一位？始终让其显示小数点
        ce8Segx8->showValBit[1] = ((index - 2 >= 0) ? ce8Segx8_table[temp[index - 2] - 0x20] : 0xFF);
        ce8Segx8->showValBit[2] = ((index - 3 >= 0) ? ce8Segx8_table[temp[index - 3] - 0x20] : 0xFF);
        ce8Segx8->showValBit[3] = ((index - 4 >= 0) ? ce8Segx8_table[temp[index - 4] - 0x20] : 0xFF);
        ce8Segx8->showValBit[4] = ((index - 5 >= 0) ? ce8Segx8_table[temp[index - 5] - 0x20] : 0xFF);
        ce8Segx8->showValBit[5] = ((index - 6 >= 0) ? ce8Segx8_table[temp[index - 6] - 0x20] : 0xFF);
        ce8Segx8->showValBit[6] = ((index - 7 >= 0) ? ce8Segx8_table[temp[index - 7] - 0x20] : 0xFF);
        ce8Segx8->showValBit[7] = ((index - 8 >= 0) ? ce8Segx8_table[temp[index - 8] - 0x20] : 0xFF);
    }
    else
    {
        ceDebugOp.sprintf(temp, "%f", val);
        index = ceStringOp.strlen(temp);
        for (i = 0; i < index; i++)
        {
            if (temp[i] == '.')//以下代码可以优化，先判断出是否有小数点，有小数点确定小数点的位置，在进行处理，代码会精简很多
            {
                if (i == 0)//如果没有小数点，怎么处理？
                {
                    ce8Segx8->showValBit[0] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);//注意，如果有小数点，则出去小数点，有效位数应该为index - 1，所以代码中应该用>，而不是>=，在优化代码时在进行此处理
                    ce8Segx8->showValBit[1] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table['0' - 0x20] : 0xFF) & (~0x01);//如果第一位就是小数点，则显示0.xxx
                    break;
                }
                if (i == 1)
                {
                    ce8Segx8->showValBit[0] = ((index >= 8) ? ce8Segx8_table[temp[8] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[1] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF) & (~0x01);//在小数点的上一位显示小数点，然后跳过小数点的这一位，从下一位开始显示
                    break;
                }
                else if (i == 2)
                {
                    ce8Segx8->showValBit[0] = ((index >= 8) ? ce8Segx8_table[temp[8] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[1] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF) & (~0x01);//在小数点的上一位显示小数点，然后跳过小数点的这一位，从下一位开始显示
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else if (i == 3)
                {
                    ce8Segx8->showValBit[0] = ((index >= 8) ? ce8Segx8_table[temp[8] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[1] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF) & (~0x01);//在小数点的上一位显示小数点，然后跳过小数点的这一位，从下一位开始显示
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else  if (i == 4)
                {
                    ce8Segx8->showValBit[0] = ((index >= 8) ? ce8Segx8_table[temp[8] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[1] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF) & (~0x01);//在小数点的上一位显示小数点，然后跳过小数点的这一位，从下一位开始显示
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else  if (i == 5)
                {
                    ce8Segx8->showValBit[0] = ((index >= 8) ? ce8Segx8_table[temp[8] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[1] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF) & (~0x01);//在小数点的上一位显示小数点，然后跳过小数点的这一位，从下一位开始显示
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else  if (i == 6)
                {
                    ce8Segx8->showValBit[0] = ((index >= 8) ? ce8Segx8_table[temp[8] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[1] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF) & (~0x01);//在小数点的上一位显示小数点，然后跳过小数点的这一位，从下一位开始显示
                    ce8Segx8->showValBit[3] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else  if (i == 7)
                {
                    ce8Segx8->showValBit[0] = ((index >= 8) ? ce8Segx8_table[temp[8] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[1] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF) & (~0x01);//在小数点的上一位显示小数点，然后跳过小数点的这一位，从下一位开始显示
                    ce8Segx8->showValBit[2] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else  if (i == 8)
                {
                    ce8Segx8->showValBit[0] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF) & (~0x01);//在小数点的上一位显示小数点，然后跳过小数点的这一位，从下一位开始显示
                    ce8Segx8->showValBit[1] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else
                {
                    ce8Segx8->showValBit[0] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[1] = ((index >= 6) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
            }
        }
    }
    ce8Segx8_ShowData(&(ce8Segx8->ceTg), ce8Segx8->showValBit);
}

/**
  * @brief  显示字符串
  * @param  ce8Segx8:Ce8Segx8属性对象指针
  * @param  msg:需要显示的字符串
  */
void ce8Segx8_setChars(Ce8Segx8* ce8Segx8, char* msg)
{
    int16 index = ceStringOp.strlen(msg);
    switch (index)
    {
    case 0:
        ce8Segx8->showValBit[0] = 0xFF;
        ce8Segx8->showValBit[1] = 0xFF;
        ce8Segx8->showValBit[2] = 0xFF;
        ce8Segx8->showValBit[3] = 0xFF;
        ce8Segx8->showValBit[4] = 0xFF;
        ce8Segx8->showValBit[5] = 0xFF;
        ce8Segx8->showValBit[6] = 0xFF;
        ce8Segx8->showValBit[7] = 0xFF;
        break;
    case 1:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        ce8Segx8->showValBit[1] = 0xFF;
        ce8Segx8->showValBit[2] = 0xFF;
        ce8Segx8->showValBit[3] = 0xFF;
        ce8Segx8->showValBit[4] = 0xFF;
        ce8Segx8->showValBit[5] = 0xFF;
        ce8Segx8->showValBit[6] = 0xFF;
        ce8Segx8->showValBit[7] = 0xFF;
        break;
    case 2:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[1] - 0x20) % 95];
        ce8Segx8->showValBit[1] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        ce8Segx8->showValBit[2] = 0xFF;
        ce8Segx8->showValBit[3] = 0xFF;
        ce8Segx8->showValBit[4] = 0xFF;
        ce8Segx8->showValBit[5] = 0xFF;
        ce8Segx8->showValBit[6] = 0xFF;
        ce8Segx8->showValBit[7] = 0xFF;
        break;
    case 3:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[2] - 0x20) % 95];
        ce8Segx8->showValBit[1] = ce8Segx8_table[(msg[1] - 0x20) % 95];
        ce8Segx8->showValBit[2] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        ce8Segx8->showValBit[3] = 0xFF;
        ce8Segx8->showValBit[4] = 0xFF;
        ce8Segx8->showValBit[5] = 0xFF;
        ce8Segx8->showValBit[6] = 0xFF;
        ce8Segx8->showValBit[7] = 0xFF;
        break;
    case 4:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[3] - 0x20) % 95];
        ce8Segx8->showValBit[1] = ce8Segx8_table[(msg[2] - 0x20) % 95];
        ce8Segx8->showValBit[2] = ce8Segx8_table[(msg[1] - 0x20) % 95];
        ce8Segx8->showValBit[3] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        ce8Segx8->showValBit[4] = 0xFF;
        ce8Segx8->showValBit[5] = 0xFF;
        ce8Segx8->showValBit[6] = 0xFF;
        ce8Segx8->showValBit[7] = 0xFF;
        break;
    case 5:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[4] - 0x20) % 95];
        ce8Segx8->showValBit[1] = ce8Segx8_table[(msg[3] - 0x20) % 95];
        ce8Segx8->showValBit[2] = ce8Segx8_table[(msg[2] - 0x20) % 95];
        ce8Segx8->showValBit[3] = ce8Segx8_table[(msg[1] - 0x20) % 95];
        ce8Segx8->showValBit[4] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        ce8Segx8->showValBit[5] = 0xFF;
        ce8Segx8->showValBit[6] = 0xFF;
        ce8Segx8->showValBit[7] = 0xFF;
        break;
    case 6:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[5] - 0x20) % 95];
        ce8Segx8->showValBit[1] = ce8Segx8_table[(msg[4] - 0x20) % 95];
        ce8Segx8->showValBit[2] = ce8Segx8_table[(msg[3] - 0x20) % 95];
        ce8Segx8->showValBit[3] = ce8Segx8_table[(msg[2] - 0x20) % 95];
        ce8Segx8->showValBit[4] = ce8Segx8_table[(msg[1] - 0x20) % 95];
        ce8Segx8->showValBit[5] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        ce8Segx8->showValBit[6] = 0xFF;
        ce8Segx8->showValBit[7] = 0xFF;
        break;
    case 7:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[6] - 0x20) % 95];
        ce8Segx8->showValBit[1] = ce8Segx8_table[(msg[5] - 0x20) % 95];
        ce8Segx8->showValBit[2] = ce8Segx8_table[(msg[4] - 0x20) % 95];
        ce8Segx8->showValBit[3] = ce8Segx8_table[(msg[3] - 0x20) % 95];
        ce8Segx8->showValBit[4] = ce8Segx8_table[(msg[2] - 0x20) % 95];
        ce8Segx8->showValBit[5] = ce8Segx8_table[(msg[1] - 0x20) % 95];
        ce8Segx8->showValBit[6] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        ce8Segx8->showValBit[7] = 0xFF;
        break;
    case 8:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[7] - 0x20) % 95];
        ce8Segx8->showValBit[1] = ce8Segx8_table[(msg[6] - 0x20) % 95];
        ce8Segx8->showValBit[2] = ce8Segx8_table[(msg[5] - 0x20) % 95];
        ce8Segx8->showValBit[3] = ce8Segx8_table[(msg[4] - 0x20) % 95];
        ce8Segx8->showValBit[4] = ce8Segx8_table[(msg[3] - 0x20) % 95];
        ce8Segx8->showValBit[5] = ce8Segx8_table[(msg[2] - 0x20) % 95];
        ce8Segx8->showValBit[6] = ce8Segx8_table[(msg[1] - 0x20) % 95];
        ce8Segx8->showValBit[7] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        break;
    default:
        ce8Segx8->showValBit[0] = ce8Segx8_table[(msg[7] - 0x20) % 95];
        ce8Segx8->showValBit[1] = ce8Segx8_table[(msg[6] - 0x20) % 95];
        ce8Segx8->showValBit[2] = ce8Segx8_table[(msg[5] - 0x20) % 95];
        ce8Segx8->showValBit[3] = ce8Segx8_table[(msg[4] - 0x20) % 95];
        ce8Segx8->showValBit[4] = ce8Segx8_table[(msg[3] - 0x20) % 95];
        ce8Segx8->showValBit[5] = ce8Segx8_table[(msg[2] - 0x20) % 95];
        ce8Segx8->showValBit[6] = ce8Segx8_table[(msg[1] - 0x20) % 95];
        ce8Segx8->showValBit[7] = ce8Segx8_table[(msg[0] - 0x20) % 95];
        break;
    }
    ce8Segx8_ShowData(&(ce8Segx8->ceTg), ce8Segx8->showValBit);
}
/**
  * @brief  使模块处于关闭显示状态
  * @param  ce8Segx8:Ce8Segx8属性对象指针
  */
void ce8Segx8_setOff(Ce8Segx8* ce8Segx8)
{
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_DISPLAY_OFF);
}

const Ce8Segx8Op ce8Segx8Op = {ce8Segx8_initialByGpio, ce8Segx8_initialByTg, ce8Segx8_setOn, ce8Segx8_setVal, ce8Segx8_setChars, ce8Segx8_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus

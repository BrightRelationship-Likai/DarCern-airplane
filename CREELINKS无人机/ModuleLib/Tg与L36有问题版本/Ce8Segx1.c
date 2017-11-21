/**
  ******************************************************************************
  * @file    Ce8Segx1.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������Ce8Segx1ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "Ce8Segx1.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
 * @brief   Ce8Segx1ʹ�õ�8������ܵ���ģ
 */
const uint8 ce8Segx1_table[95] =
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
  * @brief  ��74HC595д����
  * @param  ceTg:Ce8Segx1���Զ����е�CeTg
  * @param  data:��д��74HC595de595������
  * @return None
  */
void ce8Segx1_write595Byte(CeTg* ceTg, uint8 data)
{
    int i;
    for(i=0;i<8;i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
        if( (data & 0x01) == 0x00)
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
        }else
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
  * @brief  Ce8Segx1ģ���ڲ��õ��ĳ�ʼ��
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @return None
  */
void ce8Segx1_initial(Ce8Segx1* ce8Segx1)
{
    ceGpioOp.resetBit(&(ce8Segx1->ceTg));//SRCL
    ceGpioOp.resetBit(&(ce8Segx1->ceTg));//SER
    ceGpioOp.resetBit(&(ce8Segx1->ceTg));//RCLK
    ce8Segx1->showTable = 0xFF;//����
    ce8Segx1_write595Byte(&(ce8Segx1->ceTg), ce8Segx1->showTable);
}

/**
  * @brief  Ce8Segx1ģ��ʹ������Gpio������ɳ�ʼ��
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @param  ceGpio0:Ce8Segx1ģ��ʹ�õĵ�һ��Gpio����Դ��
  * @param  ceGpio1:Ce8Segx1ģ��ʹ�õĵڶ���Gpio����Դ��
  * @param  ceGpio2:Ce8Segx1ģ��ʹ�õĵ�����Gpio����Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ce8Segx1_initialByGpio(Ce8Segx1* ce8Segx1, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ce8Segx1->ceTg.ceResource = CE_NULL_RESOURCE;
    ce8Segx1->ceTg.ceResource0 = ceGpio0;
    ce8Segx1->ceTg.ceResource1 = ceGpio1;
    ce8Segx1->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ce8Segx1->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ce8Segx1_initial(ce8Segx1);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  Ce8Segx1ģ��ʹ��Tg����ɳ�ʼ��
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @param  ceTg:Ce8Segx1ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ce8Segx1_initialByTg(Ce8Segx1* ce8Segx1, CE_RESOURCE ceTg)
{
    ce8Segx1->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ce8Segx1->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ce8Segx1_initial(ce8Segx1);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ʹģ�鴦�ڿ�����ʾ״̬
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @return None
  */
void ce8Segx1_setOn(Ce8Segx1* ce8Segx1)
{
    ce8Segx1_write595Byte(&(ce8Segx1->ceTg), ce8Segx1->showTable);
}

/**
  * @brief  ʹģ�鴦�ڹر���ʾ״̬
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @return None
  */
void ce8Segx1_setOff(Ce8Segx1* ce8Segx1)
{
    ce8Segx1_write595Byte(&(ce8Segx1->ceTg), 0xFF);
}

/**
  * @brief  ��ʾС����
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @return None
  */
void ce8Segx1_setDpOn(Ce8Segx1* ce8Segx1)
{
    ce8Segx1->showTable &= ~0x01;
    ce8Segx1_write595Byte(&(ce8Segx1->ceTg), ce8Segx1->showTable);
}

/**
  * @brief  ����С����
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @return None
  */
void ce8Segx1_setDpOff(Ce8Segx1* ce8Segx1)
{
    ce8Segx1->showTable |= 0x01;
    ce8Segx1_write595Byte(&(ce8Segx1->ceTg), ce8Segx1->showTable);
}

/**
  * @brief  ��ʾ��ֵ
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @param  val:����ʾ����ֵ����Χ0-9��ģ����ʾ����0-9
  * @return None
  */
void ce8Segx1_setVal(Ce8Segx1* ce8Segx1, uint8 val)
{
    if(val > 0x09)
    {
        ce8Segx1->showTable = (ce8Segx1_table[((val % 0x10) + 23) % 95]) | (ce8Segx1->showTable & 0x01);//����CeSegx1����ʾʮ�����ƹ��ܣ���������
    }
    else
    {
        ce8Segx1->showTable = (ce8Segx1_table[(val + 16) % 95]) | (ce8Segx1->showTable & 0x01);
    }
    ce8Segx1_write595Byte(&(ce8Segx1->ceTg), ce8Segx1->showTable);
}

/**
  * @brief  ��ʾ�ַ�
  * @param  ce8Segx1:Ce8Segx1���Զ���
  * @param  val:����ʾ���ַ����ַ�0-9���СдӢ���ַ���ֻ�в����ַ�����������ʾ��
  * @return None
  */
void ce8Segx1_setChar(Ce8Segx1* ce8Segx1, char val)
{
    ce8Segx1->showTable = (ce8Segx1_table[(val - 0x20) % 95]) | (ce8Segx1->showTable & 0x01);
    ce8Segx1_write595Byte(&(ce8Segx1->ceTg), ce8Segx1->showTable);
}

const Ce8Segx1Op ce8Segx1Op = {ce8Segx1_initialByGpio, ce8Segx1_initialByTg, ce8Segx1_setOn, ce8Segx1_setOff, ce8Segx1_setDpOn, ce8Segx1_setDpOff, ce8Segx1_setVal, ce8Segx1_setChar};

#ifdef __cplusplus
 }
#endif //__cplusplus

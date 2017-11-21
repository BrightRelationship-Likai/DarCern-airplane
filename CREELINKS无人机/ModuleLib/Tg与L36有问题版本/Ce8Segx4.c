/**
  ******************************************************************************
  * @file    Ce8Segx4.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������Ce8Segx4ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "Ce8Segx4.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
 * @brief   Ce8Segx8ʹ�õ�8������ܵ���ģ
 */
const uint8 ce8Segx4_table[95] =
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
 * @param  ceTg:Ce8Segx4���Զ����е�CeTg
 * @param  val:��д��74HC595de595������
 * @param  bitCode:�������Ķ�λ
 * @return None
 */
void ce8Segx4_writeByte(CeTg* ceTg, uint8 val, uint8 bitCode)
{
    int i=0;
    uint16 data = (((0xFFFF & (~bitCode)) << 8) | (val & 0xFF));//�����������һ�����봮����595��Ȼ�����棬������ʾ������Ŀ���Ϊ��4λ��0Ϊ������1Ϊ��������Լ���ȡ���Ĳ�����
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

        ceSystemOp.delayNs(1);
        ceGpioOp.setBit(&(ce8Segx1->ceGpio0));
        ceSystemOp.delayNs(1);
        data >>= 1;
    }
    ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
    ceSystemOp.delayNs(1);
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));
}


/**
 * @brief  ticker�Ļص�����
 * @param  pAddPar:��������ָ��
 * @return None
 */
void ce8Segx4_tickerCallBack(void* pAddPar)
{
    Ce8Segx4* ce8Segx4 = (Ce8Segx4*)pAddPar;
    switch(ce8Segx4->nowBit & 0x0F)//ģ���Ƿ��ڿ�ʼ��ʾ״̬
    {
    case 0:
        ce8Segx4_writeByte(&(ce8Segx4->ceTg), ce8Segx4->showValBit[0], 0x80);
        ce8Segx4->nowBit++;
        break;
    case 1:
        ce8Segx4_writeByte(&(ce8Segx4->ceTg), ce8Segx4->showValBit[1], 0x40);
        ce8Segx4->nowBit++;
        break;
    case 2:
        ce8Segx4_writeByte(&(ce8Segx4->ceTg), ce8Segx4->showValBit[2], 0x20);
        ce8Segx4->nowBit++;
        break;
    case 3:
        ce8Segx4_writeByte(&(ce8Segx4->ceTg) , ce8Segx4->showValBit[3], 0x10);
        ce8Segx4->nowBit &= ~0x0F;
        break;
    default:
        ce8Segx4->nowBit &= ~0x0F;
        break;
    }
}

/**
  * @brief  Ce8Segx4ģ���ڲ��õ��ĳ�ʼ��
  * @param  ce8Segx4:Ce8Segx4���Զ���
  * @return None
  */
void ce8Segx4_initial(Ce8Segx4* ce8Segx4, CE_RESOURCE tickerID)
{
    ce8Segx4->showValBit[0] = 0xFF;
    ce8Segx4->showValBit[1] = 0xFF;
    ce8Segx4->showValBit[2] = 0xFF;
    ce8Segx4->showValBit[3] = 0xFF;
    ce8Segx4->nowBit = 0x00;

    ce8Segx4->ceTicker.ID = tickerID;
    ce8Segx4->ceTicker.pAddPar = ce8Segx4;
    ce8Segx4->ceTicker.intervalMs = 5;
    ce8Segx4->ceTicker.callBack = ce8Segx4_tickerCallBack;
    ceTickerOp.registerTicker(&(ce8Segx4->ceTicker));
    ceTickerOp.start(&(ce8Segx4->ceTicker));
}

/**
  * @brief  Ce8Segx4ģ��ʹ������Gpio������ɳ�ʼ��
  * @param  ce8Segx4:Ce8Segx4���Զ���
  * @param  ceGpio0:Ce8Segx4ģ��ʹ�õĵ�һ��Gpio����Դ��
  * @param  ceGpio1:Ce8Segx4ģ��ʹ�õĵڶ���Gpio����Դ��
  * @param  ceGpio2:Ce8Segx4ģ��ʹ�õĵ�����Gpio����Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ce8Segx4_initialByGpio(Ce8Segx4* ce8Segx4, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ce8Segx4->ceTg.ceResource0 = ceGpio0;
    ce8Segx4->ceTg.ceResource1 = ceGpio1;
    ce8Segx4->ceTg.ceResource2 = ceGpio2;
    ceTgOp.initial(&(ce8Segx4->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ce8Segx4->ceTg));
    ceGpioOp.resetBit(&(ce8Segx4->ceTg));
    ceGpioOp.resetBit(&(ce8Segx4->ceTg));
    ce8Segx4_initial(ce8Segx4, ceGpio0);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  Ce8Segx4ģ��ʹ��Tg����ɳ�ʼ��
  * @param  ce8Segx4:Ce8Segx4���Զ���
  * @param  ceTg:Ce8Segx4ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ce8Segx4_initialByTg(Ce8Segx4* ce8Segx4, CE_RESOURCE ceTg)
{
    ce8Segx4->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ce8Segx4->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP);
    ceGpioOp.resetBit(&(ce8Segx4->ceTg));
    ceGpioOp.resetBit(&(ce8Segx4->ceTg));
    ceGpioOp.resetBit(&(ce8Segx4->ceTg));
    ce8Segx4_initial(ce8Segx4, ceTg);
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ʹģ�鴦������ʾ״̬
  * @param  ce8Segx4:Ce8Segx4���Զ���ָ��
  */
void ce8Segx4_setOn(Ce8Segx4* ce8Segx4)
{
    ce8Segx4->nowBit |= 0x80;
}

/**
  * @brief  ��ʾ��ֵ
  * @param  ce8Segx4:Ce8Segx4���Զ���ָ��
  * @param  val:��Ҫ��ʾ��ֵ
  */
void ce8Segx4_setVal(Ce8Segx4* ce8Segx4, fp32 val)
{
    char temp[36];
    int i;
    int8 point = (int8)((val - (int32)val) * 1000);//ȡ��С������Ϊ��λ��
    int index;
    if (point == 0)
    {
        ceDebugOp.sprintf(temp, "%d", (int32)val);
        index = ceStringOp.strlen(temp);
        ce8Segx4->showValBit[0] = ((index - 1 >= 0) ? ce8Segx4_table[temp[index - 1] - 0x20] : 0xFF) & (~0x01);//С�����ڶ����Ƶ����λ��ʼ��������ʾС����
        ce8Segx4->showValBit[1] = ((index - 2 >= 0) ? ce8Segx4_table[temp[index - 2] - 0x20] : 0xFF);
        ce8Segx4->showValBit[2] = ((index - 3 >= 0) ? ce8Segx4_table[temp[index - 3] - 0x20] : 0xFF);
        ce8Segx4->showValBit[3] = ((index - 4 >= 0) ? ce8Segx4_table[temp[index - 4] - 0x20] : 0xFF);
    }
    else
    {
        ceDebugOp.sprintf(temp, "%f", val);
        index = ceStringOp.strlen(temp);
        for (i = 0; i < index && i < 4; i++)
        {
            if (temp[i] == '.')
            {
                if (i == 0)
                {
                    ce8Segx4->showValBit[0] = ((index >= 3) ? ce8Segx4_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[1] = ((index >= 2) ? ce8Segx4_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[2] = ((index >= 1) ? ce8Segx4_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[3] = ((index >= 0) ? ce8Segx4_table['0' - 0x20] : 0xFF) & (~0x01);//�����һλ����С���㣬����ʾ0.xxx
                    break;
                }
                if (i == 1)
                {
                    ce8Segx4->showValBit[0] = ((index >= 4) ? ce8Segx4_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[1] = ((index >= 3) ? ce8Segx4_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[2] = ((index >= 2) ? ce8Segx4_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[3] = ((index >= 0) ? ce8Segx4_table[temp[0] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
                    break;
                }
                else if (i == 2)
                {
                    ce8Segx4->showValBit[0] = ((index >= 4) ? ce8Segx4_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[1] = ((index >= 3) ? ce8Segx4_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[2] = ((index >= 1) ? ce8Segx4_table[temp[1] - 0x20] : 0xFF) & (~0x01);
                    ce8Segx4->showValBit[3] = ((index >= 0) ? ce8Segx4_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else if (i == 3)
                {
                    ce8Segx4->showValBit[0] = ((index >= 4) ? ce8Segx4_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[1] = ((index >= 2) ? ce8Segx4_table[temp[2] - 0x20] : 0xFF) & (~0x01);
                    ce8Segx4->showValBit[2] = ((index >= 1) ? ce8Segx4_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[3] = ((index >= 0) ? ce8Segx4_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else  if (i == 4)
                {
                    ce8Segx4->showValBit[0] = ((index >= 3) ? ce8Segx4_table[temp[3] - 0x20] : 0xFF) & (~0x01);
                    ce8Segx4->showValBit[1] = ((index >= 2) ? ce8Segx4_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[2] = ((index >= 1) ? ce8Segx4_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[3] = ((index >= 0) ? ce8Segx4_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
                else
                {
                    ce8Segx4->showValBit[0] = ((index >= 3) ? ce8Segx4_table[temp[3] - 0x20] : 0xFF);//������Ӧ������forѭ��
                    ce8Segx4->showValBit[1] = ((index >= 2) ? ce8Segx4_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[2] = ((index >= 1) ? ce8Segx4_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx4->showValBit[3] = ((index >= 0) ? ce8Segx4_table[temp[0] - 0x20] : 0xFF);
                    break;
                }
            }
        }
    }
    ce8Segx4_setOn(ce8Segx4);
}

/**
  * @brief  ��ʾ�ַ���
  * @param  ce8Segx4:Ce8Segx4���Զ���ָ��
  * @param  msg:��Ҫ��ʾ���ַ���
  */
void ce8Segx4_setChars(Ce8Segx4* ce8Segx4, char* msg)
{
    int16 index = ceStringOp.strlen(msg);
    switch (index)
    {
    case 0:
        ce8Segx4->showValBit[0] = 0xFF;
        ce8Segx4->showValBit[1] = 0xFF;
        ce8Segx4->showValBit[2] = 0xFF;
        ce8Segx4->showValBit[3] = 0xFF;
        break;
    case 1:
        ce8Segx4->showValBit[0] = ce8Segx4_table[(msg[0] - 0x20) % 95];
        ce8Segx4->showValBit[1] = 0xFF;
        ce8Segx4->showValBit[2] = 0xFF;
        ce8Segx4->showValBit[3] = 0xFF;
        break;
    case 2:
        ce8Segx4->showValBit[0] = ce8Segx4_table[(msg[1] - 0x20) % 95];
        ce8Segx4->showValBit[1] = ce8Segx4_table[(msg[0] - 0x20) % 95];
        ce8Segx4->showValBit[2] = 0xFF;
        ce8Segx4->showValBit[3] = 0xFF;
        break;
    case 3:
        ce8Segx4->showValBit[0] = ce8Segx4_table[(msg[2] - 0x20) % 95];
        ce8Segx4->showValBit[1] = ce8Segx4_table[(msg[1] - 0x20) % 95];
        ce8Segx4->showValBit[2] = ce8Segx4_table[(msg[0] - 0x20) % 95];
        ce8Segx4->showValBit[3] = 0xFF;
        break;
    case 4:
        ce8Segx4->showValBit[0] = ce8Segx4_table[(msg[3] - 0x20) % 95];
        ce8Segx4->showValBit[1] = ce8Segx4_table[(msg[2] - 0x20) % 95];
        ce8Segx4->showValBit[2] = ce8Segx4_table[(msg[1] - 0x20) % 95];
        ce8Segx4->showValBit[3] = ce8Segx4_table[(msg[0] - 0x20) % 95];
        break;
    default:
        ce8Segx4->showValBit[0] = ce8Segx4_table[(msg[3] - 0x20) % 95];
        ce8Segx4->showValBit[1] = ce8Segx4_table[(msg[2] - 0x20) % 95];
        ce8Segx4->showValBit[2] = ce8Segx4_table[(msg[1] - 0x20) % 95];
        ce8Segx4->showValBit[3] = ce8Segx4_table[(msg[0] - 0x20) % 95];
        break;
    }
    ce8Segx4_setOn(ce8Segx4);
}
/**
  * @brief  ʹģ�鴦�ڹر���ʾ״̬
  * @param  ce8Segx4:Ce8Segx4���Զ���ָ��
  */
void ce8Segx4_setOff(Ce8Segx4* ce8Segx4)
{
    ce8Segx4->nowBit &= 0x7F;
}

const Ce8Segx4Op ce8Segx4Op = {ce8Segx4_initialByGpio, ce8Segx4_initialByTg, ce8Segx4_setOn, ce8Segx4_setVal, ce8Segx4_setChars, ce8Segx4_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus

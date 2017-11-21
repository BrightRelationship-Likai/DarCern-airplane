/**
  ******************************************************************************
  * @file    Ce8Segx8.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������Ce8Segx8ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)���Ժ���ҪС�����λ�ã�
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "Ce8Segx8.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_8SEGX8_DISPLAY_ON 0x8A           /*!< �ر���ʾָ��*/
#define CE_8SEGX8_DISPLAY_OFF 0x80          /*!< ������ʾָ��*/
#define CE_8SEGX8_ADDRESS_FIX_MODE 0x44     /*!< ����ܵ�״̬����*/

/**
 * @brief   Ce8Segx8ʹ�õ�8������ܵ���ģ
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
 * @brief  ��TM1638д����
 * @param  ceTg:Ce8Segx8���Զ����е�CeTg
 * @param  val:��д��74HC595de595������
 * @param  bitCode:�������Ķ�λ
 * @return None
 */
void ce8Segx8_WriteCmd(CeTg* ceTg, uint8 cmd)
{
    uint8 i;
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));//ʹ��Ƭѡ
    for (i = 0; i < 8; i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));//����CLK
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
        ceGpioOp.setBit(&(ce8Segx1->ceGpio1));//����CLK
        ceSystemOp.delayUs(1);
    }
    ceGpioOp.setBit(&(ce8Segx1->ceGpio0));//��ֹƬѡ
    ceSystemOp.delayUs(2);
}

/**
 * @brief  ��TM1638д����
 * @param  ceTg:Ce8Segx8���Զ����е�CeTg
 * @param  val:��д��74HC595de595������
 * @param  bitCode:�������Ķ�λ
 * @return None
 */
void ce8Segx8_WriteData(CeTg* ceTg, uint8 dig, uint8 data)
{
    uint8 i;
    ceGpioOp.resetBit(&(ce8Segx1->ceGpio0));//ʹ��Ƭѡ
    for (i = 0; i < 8; i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));//����CLK
        ceSystemOp.delayUs(1);
        if ((dig & 0x01) == 0x01)
        {
            ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
        }
        else
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
        }
        dig >>= 1;//�������ݵ��ź�����
        ceGpioOp.setBit(&(ce8Segx1->ceGpio1));//����CLK
        ceSystemOp.delayUs(1);
    }

    for (i = 0; i < 8; i++)
    {
        ceGpioOp.resetBit(&(ce8Segx1->ceGpio1));//����CLK
        ceSystemOp.delayUs(1);
        if ((data & 0x01) == 0x01)
        {
            ceGpioOp.setBit(&(ce8Segx1->ceGpio2));
        }
        else
        {
            ceGpioOp.resetBit(&(ce8Segx1->ceGpio2));
        }
        data >>= 1;//�������ݵ��ź�����
        ceGpioOp.setBit(&(ce8Segx1->ceGpio1));//����CLK
        ceSystemOp.delayUs(1);
    }
    ceGpioOp.setBit(&(ce8Segx1->ceGpio0));//��ֹƬѡ
    ceSystemOp.delayUs(2);
}

/**
  * @brief  ��TM1638д������ʾ������
  * @param  ceT:Ce8Segx8���Զ����е�CeTg
  * @param  showValBit:����ʾ����������ָ��
  * @return None
  */
void ce8Segx8_ShowData(CeTg* ceTg, uint8* showValBit)
{
    uint8 i;
    uint8 des[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8 src[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    src[0] = showValBit[4];//����ܵĶ�˳��Ϊ��4567��01234��������Ҫ�������ƶ�һ�¡�
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
        ce8Segx8_WriteData(ceTg, 0xC0 + (i * 2), (~des[i]));//�̶���ַд���ݣ�������ʽ
    }
}

/**
  * @brief  Ce8Segx8ģ���ڲ��õ��ĳ�ʼ��
  * @param  ce8Segx8:Ce8Segx8���Զ���
  * @return None
  */
void ce8Segx8_initial(Ce8Segx8* ce8Segx8)
{
    uint8 index;
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_DISPLAY_OFF);
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_ADDRESS_FIX_MODE);//�̶���ַ
    //ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), 0x87);//ʹ��Ĭ�ϵ������ȣ���Ϊ������ߺͲ����ú�����һ���ġ�
    for(index = 0; index < 8; index++)
    {
        ce8Segx8_WriteData(&(ce8Segx8->ceTg), 0xC0 + (index * 2), 0x00);//�����ʾ�Ĵ�������������ʾ�Ĵ�����ʱ��ֻ�õ�0x02,0x04,0x06,0x08,0x0A,0x0C
        ce8Segx8_WriteData(&(ce8Segx8->ceTg), 0xC0 + ((index * 2 ) + 1), 0x00);
        ce8Segx8->showValBit[index] = 0x00;
    }
    ce8Segx8_ShowData(&(ce8Segx8->ceTg), ce8Segx8->showValBit);
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_DISPLAY_ON);
}

/**
  * @brief  Ce8Segx8ģ��ʹ������Gpio������ɳ�ʼ��
  * @param  ce8Segx8:Ce8Segx8���Զ���
  * @param  ceGpio0:Ce8Segx8ģ��ʹ�õĵ�һ��Gpio����Դ��
  * @param  ceGpio1:Ce8Segx8ģ��ʹ�õĵڶ���Gpio����Դ��
  * @param  ceGpio2:Ce8Segx8ģ��ʹ�õĵ�����Gpio����Դ��
  * @return ϵͳ״̬��
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
  * @brief  Ce8Segx8ģ��ʹ��Tg����ɳ�ʼ��
  * @param  ce8Segx8:Ce8Segx8���Զ���
  * @param  ceTg:Ce8Segx8ģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
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
  * @brief  ʹģ�鴦������ʾ״̬
  * @param  ce8Segx8:Ce8Segx8���Զ���ָ��
  */
void ce8Segx8_setOn(Ce8Segx8* ce8Segx8)
{
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_DISPLAY_ON);
}

/**
  * @brief  ��ʾ��ֵ
  * @param  ce8Segx8:Ce8Segx8���Զ���ָ��
  * @param  val:��Ҫ��ʾ��ֵ
  */
void ce8Segx8_setVal(Ce8Segx8* ce8Segx8, fp32 val)
{
    char temp[50];
    int8 point = (int8)((val - (int32)val) * 1000);//ȡ��С������Ϊ��λ��
    int index;
    int i;
    if (point == 0)
    {
        ceDebugOp.sprintf(temp, "%d", (int32)val);
        index = ceStringOp.strlen(temp);
        ce8Segx8->showValBit[0] = ((index - 1 >= 0) ? ce8Segx8_table[temp[index - 1] - 0x20] : 0xFF) & (~0x01);//С�����ڶ����Ƶ���һλ��ʼ��������ʾС����
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
            if (temp[i] == '.')//���´�������Ż������жϳ��Ƿ���С���㣬��С����ȷ��С�����λ�ã��ڽ��д�������ᾫ��ܶ�
            {
                if (i == 0)//���û��С���㣬��ô����
                {
                    ce8Segx8->showValBit[0] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF);//ע�⣬�����С���㣬���ȥС���㣬��Чλ��Ӧ��Ϊindex - 1�����Դ�����Ӧ����>��������>=�����Ż�����ʱ�ڽ��д˴���
                    ce8Segx8->showValBit[1] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[2] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[3] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF);
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table['0' - 0x20] : 0xFF) & (~0x01);//�����һλ����С���㣬����ʾ0.xxx
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
                    ce8Segx8->showValBit[7] = ((index >= 0) ? ce8Segx8_table[temp[0] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
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
                    ce8Segx8->showValBit[6] = ((index >= 1) ? ce8Segx8_table[temp[1] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
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
                    ce8Segx8->showValBit[5] = ((index >= 2) ? ce8Segx8_table[temp[2] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
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
                    ce8Segx8->showValBit[4] = ((index >= 3) ? ce8Segx8_table[temp[3] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
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
                    ce8Segx8->showValBit[3] = ((index >= 4) ? ce8Segx8_table[temp[4] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
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
                    ce8Segx8->showValBit[2] = ((index >= 5) ? ce8Segx8_table[temp[5] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
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
                    ce8Segx8->showValBit[1] = ((index >= 6) ? ce8Segx8_table[temp[6] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
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
                    ce8Segx8->showValBit[0] = ((index >= 7) ? ce8Segx8_table[temp[7] - 0x20] : 0xFF) & (~0x01);//��С�������һλ��ʾС���㣬Ȼ������С�������һλ������һλ��ʼ��ʾ
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
  * @brief  ��ʾ�ַ���
  * @param  ce8Segx8:Ce8Segx8���Զ���ָ��
  * @param  msg:��Ҫ��ʾ���ַ���
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
  * @brief  ʹģ�鴦�ڹر���ʾ״̬
  * @param  ce8Segx8:Ce8Segx8���Զ���ָ��
  */
void ce8Segx8_setOff(Ce8Segx8* ce8Segx8)
{
    ce8Segx8_WriteCmd(&(ce8Segx8->ceTg), CE_8SEGX8_DISPLAY_OFF);
}

const Ce8Segx8Op ce8Segx8Op = {ce8Segx8_initialByGpio, ce8Segx8_initialByTg, ce8Segx8_setOn, ce8Segx8_setVal, ce8Segx8_setChars, ce8Segx8_setOff};

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeL36.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2016-09-28
  * @brief
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeL36.h"
#include "CeSystem.h"
#ifdef __cplusplus
extern "C"
 {
#endif

#ifdef __CE_USE_L36__

CE_STATUS ceL36_initial(CeL36* ceL36)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //Ĭ�Ͻ����µ�IO������Ϊ��������

    //PD_00(PD14), PD_01(PD15), PD_02(PD00), PD_03(PD01), 
    //PD_04(PE07), PD_05(PE08), PD_06(PE09), PD_07(PE10), PD_08(PE11), PD_09(PE12), PD_10(PE13), PD_11(PE14), PD_12(PE15), 
    //PD_13(PD08), PD_14(PD09), PD_15(PD10)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    //LCD_RS PD11 Ax ��ַ��, LCD_CS PD7 NEx Ƭѡ, LCD_WR PD5 NEW дʹ�ܣ�����LCD��RD��, LCE_RD PD4 NOE ���ʹ�ܣ�����LCD��RW��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_7 | GPIO_Pin_5 | GPIO_Pin_4;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //LCD_RST PC13 ��λ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_SetBits(GPIOD, GPIO_Pin_7);   //LCD_CS PD7 NEx Ƭѡ ����
    GPIO_SetBits(GPIOC, GPIO_Pin_13);  //LCD_RST PC13 ��λ ����
    GPIO_SetBits(GPIOD, GPIO_Pin_5);   //LCD_WR PD5 NEW дʹ�� ����
    GPIO_SetBits(GPIOD, GPIO_Pin_4);   //LCE_RD PD4 NOE ���ʹ�� ����

    if(ceL36->ceL36BusSpeed == CE_L36_BUS_SPEED_H)
    {
        FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 1;//���õ�ַ����ʱ��
        FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;//���õ�ַ����ʱ��
        FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 2;//�������ݽ���ʱ��
        FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0;//���߷�תʱ��
        FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0;//ʱ�ӷ�Ƶ
        FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0;//���ݱ���ʱ��
    }else if(ceL36->ceL36BusSpeed == CE_L36_BUS_SPEED_M)
    {

    }else
    {

    }

    FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_B;//����FSMC����ģʽ
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;//ѡ�����õ�BANK�Լ�Ƭѡ�ź�(BANK1�еĵ�һ��block)
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;//�����Ƿ����ݵ�ַ����ʱ�ָ���(No)
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;//���ô洢������(NOR)
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�������ݿ��(16bit)
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;//�����Ƿ�ʹ�ñŷ�����ģʽ��������дģʽ��(No)
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;//����WAIT�źŵ���Ч��ƽ(�͵�ƽ��Ч)
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;//�����Ƿ�ʹ�û���ģʽ(No)
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;//����WAIT�ź���Чʱ��(��wait״̬֮ǰ)
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;//�����Ƿ�ʹ��д����(Yes)
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;//�����Ƿ�ʹ��WAIT�ź�(No)
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;//�����Ƿ�ʹ����չģʽ����дʱ���໥������(No)
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;//�����Ƿ�ʹ�ñŷ�дģʽ(No)
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;//�趨��дʱ��
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;//�趨дʱ��

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);//ʹ��Bank1�е�block1
    return CE_STATUS_SUCCESS;
}

void ceL36_writeData(uint16 addr, uint16 data)
{
    CE_L36_WRITE_DATA(addr,data);
}

uint32 ceL36_readData(uint16 addr)
{
  return  CE_L36_READ_DATA(addr); 
}

void ceL36_resetRST()
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);//LCD_RST PC13 ��λ ����
}

void ceL36_setRST()
{
    GPIO_SetBits(GPIOC, GPIO_Pin_13);//LCD_RST PC13 ��λ ����
}

const CeL36Op ceL36Op = {ceL36_initial, ceL36_writeData, ceL36_readData, ceL36_setRST, ceL36_resetRST};

#endif //__CE_USE_L36__

#ifdef __cplusplus
 }
#endif

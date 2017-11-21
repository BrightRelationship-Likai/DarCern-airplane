/**
  ******************************************************************************
  * @file    CeLedCtl.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeLedCtlģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeLedCtl.h"
#include "CeLed1C.h"	
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define  CE_SYS_CTL_LED1C_RESOURCE_0    PC0AGI
#define  CE_SYS_CTL_LED1C_RESOURCE_1    PC1AGI
#define  CE_SYS_CTL_LED1C_RESOURCE_2    PC2AGI
#define  CE_SYS_CTL_LED1C_RESOURCE_3    PC3AGI


#define  CE_SYS_CTL_LED1C0_ON    0x01
#define  CE_SYS_CTL_LED1C1_ON    0x02
#define  CE_SYS_CTL_LED1C2_ON    0x03
#define  CE_SYS_CTL_LED1C3_ON    0x08
#define  CE_SYS_CTL_LED1C0_OFF  0x00
#define  CE_SYS_CTL_LED1C1_OFF  0x00
#define  CE_SYS_CTL_LED1C2_OFF  0x00
#define  CE_SYS_CTL_LED1C3_OFF  0x00

int16           ceLedCtl_tick;
CeLed1C         ceLedCtl_ceLed0;                    
CeLed1C         ceLedCtl_ceLed1;                  
CeLed1C         ceLedCtl_ceLed2;                 
CeLed1C         ceLedCtl_ceLed3; 
CeTicker        ceLedCtl_ceTicker;
CE_LED_CTL_MODE ceLedCtl_ctlMode;

/**
  * @brief  ����4��LED��״̬
  * @param  bitVal:bit0~bit3��Ӧled0~led3�� 0:�رգ�1:��
  */
void ceLedCtl_set4Led(uint8 bitVal)
{
    if(bitVal & 0x01 == 0x01)
        ceLed1COp.setOn(&ceLedCtl_ceLed0);
    else 
        ceLed1COp.setOff(&ceLedCtl_ceLed0);

    if(bitVal & 0x02 == 0x02)
        ceLed1COp.setOn(&ceLedCtl_ceLed1);
    else 
        ceLed1COp.setOff(&ceLedCtl_ceLed1);

    if(bitVal & 0x04 == 0x04)
        ceLed1COp.setOn(&ceLedCtl_ceLed2);
    else 
        ceLed1COp.setOff(&ceLedCtl_ceLed2);

    if(bitVal & 0x08 == 0x08)
        ceLed1COp.setOn(&ceLedCtl_ceLed3);
    else 
        ceLed1COp.setOff(&ceLedCtl_ceLed3);
}

/**
  * @brief  ��ʱ������CeTicker�Ļص���������ϸ�ɲο�CREELINKSƽ̨�й�CeTicker����ĵ�
  * @param  pAddPar:ceLedCtl����ָ��
  */
void ceLedCtl_callBack(void* pAddPar)
{
    if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_FLASH_CYCLE_P)//˳ʱ���Led0��Led3ѭ������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:
        case 22:
        case 32:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 10:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 20:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF);break;
        case 30:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }
    }if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_FLASH_CYCLE_N)//˳ʱ���Led3��Led0ѭ������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:
        case 22:
        case 32:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON);break;
        case 10:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF);break;
        case 20:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 30:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_FRONT)//�ɺ���ǰ����
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON );break;
        case 10:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_BACK)//��ǰ�������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 10:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON );break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_LEFT)//������������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF);break;
        case 10:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON );break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_RIGHT)//������������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON );break;
        case 10:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_OFF);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_CFG)//�������ü���ʼ��״̬������
    {
        switch (ceLedCtl_tick)
        {
        case 20:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON );break;
        case 40:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_NORMAL)//����״̬
    {
        switch (ceLedCtl_tick)
        {
        case 2:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON );break;
        case 100:   ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_ERROR)//����״̬������LED����
    {
        switch (ceLedCtl_tick)
        {
        case 2:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON );break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }
    ceLedCtl_tick++;
}

/**
  * @brief  CeLedCtlģ���ʼ��
  * @param  @param ceGpioM0-3:�ĸ�LEDʹ�õ�Gpio��Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceLedCtl_initial()
{
    ceLedCtl_ctlMode = CE_LED_CTL_MODE_OFF;
    ceLedCtl_tick = 0;

    ceLed1COp.initialByGpio(&ceLedCtl_ceLed0,CE_SYS_CTL_LED1C_RESOURCE_0);
    ceLed1COp.initialByGpio(&ceLedCtl_ceLed1,CE_SYS_CTL_LED1C_RESOURCE_1);
    ceLed1COp.initialByGpio(&ceLedCtl_ceLed2,CE_SYS_CTL_LED1C_RESOURCE_2);
    ceLed1COp.initialByGpio(&ceLedCtl_ceLed3,CE_SYS_CTL_LED1C_RESOURCE_3);

    ceLedCtl_ceTicker.callBack = ceLedCtl_callBack;
    ceLedCtl_ceTicker.ID = (uint16)CE_SYS_CTL_LED1C_RESOURCE_0;
    ceLedCtl_ceTicker.intervalMs = 10;
    ceLedCtl_ceTicker.pAddPar = CE_NULL;
    ceTickerOp.registerTicker(&(ceLedCtl_ceTicker)); 
    ceTickerOp.start(&(ceLedCtl_ceTicker));

    return CE_STATUS_SUCCESS;
}

/**
  * @brief �����ĸ�LED��˸�ķ�ʽ
  * @param ctlMode:�ĸ�LED��˸�ķ�ʽ
  */
void ceLedCtl_setMode(CE_LED_CTL_MODE ctlMode)
{
    if(ctlMode == ceLedCtl_ctlMode) return;//��Ҫ���õ�״̬�뵱ǰ״̬��ͬ����ֱ�ӷ���
    ceLedCtl_ctlMode = ctlMode;
    ceLedCtl_tick = 0;  

    ceLed1COp.setOff(&ceLedCtl_ceLed0);
    ceLed1COp.setOff(&ceLedCtl_ceLed1);
    ceLed1COp.setOff(&ceLedCtl_ceLed2);
    ceLed1COp.setOff(&ceLedCtl_ceLed3);
}
/**
  * @brief ��ȡ��ǰ�ĸ�LED��˸�ķ�ʽ
  * @return ��ǰ�ĸ�LED��˸�ķ�ʽ
  */
CE_LED_CTL_MODE ceLedCtl_getMode()
{
    return ceLedCtl_ctlMode;
}
/**
  * @brief  ��ʼ��CeLedCtlģ���������
  */
const CeLedCtlOp ceLedCtlOp = {ceLedCtl_initial,ceLedCtl_setMode,ceLedCtl_getMode};

#ifdef __cplusplus
 }
#endif //__cplusplus

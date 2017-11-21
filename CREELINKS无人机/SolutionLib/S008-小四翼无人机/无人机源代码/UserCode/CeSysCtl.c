/**
  ******************************************************************************
  * @file    CeSysCtl.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSysCtlģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeSysCtl.h"
#include "CePC33V.h"                    /*!< ��ص�ѹ���ģ������������ʵ�ֵ�ص������*/
#include "CeBeepNSrc.h"                 /*!< ���������*/
#include "CeBtnx1.h"                    /*!< ���˻��ϣ�����������ťģ������*/
#include "CeTMCtl.h"
#include "CeLed1C.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define  CE_SYS_CTL_PC33V_RESOURCE      PC4AGI
#define  CE_SYS_CTL_BEEPNSRC_RESOURCE   PA1AGIP
#define  CE_SYS_CTL_BTNX1_RESOURCE_0    PA11GIP
#define  CE_SYS_CTL_BTNX1_RESOURCE_1    PA12CGI

#define  CE_SYS_CTL_LED1C_RESOURCE_0    PC0AGI
#define  CE_SYS_CTL_LED1C_RESOURCE_1    PC1AGI
#define  CE_SYS_CTL_LED1C_RESOURCE_2    PC2AGI
#define  CE_SYS_CTL_LED1C_RESOURCE_3    PC3AGI


#define  CE_SYS_CTL_LED1C0_ON           0x01
#define  CE_SYS_CTL_LED1C1_ON           0x02
#define  CE_SYS_CTL_LED1C2_ON           0x04
#define  CE_SYS_CTL_LED1C3_ON           0x08
#define  CE_SYS_CTL_LED1C0_OFF          0x00
#define  CE_SYS_CTL_LED1C1_OFF          0x00
#define  CE_SYS_CTL_LED1C2_OFF          0x00
#define  CE_SYS_CTL_LED1C3_OFF          0x00

CeBtnx1         ceBtnLeft;                  /*!< �������˻���ť����*/
CeBtnx1         ceBtnRight;                 /*!< �������˻��Ұ�ť����*/
CePC33V         cePC33V;                    /*!< �����ص�ѹ������*/
CeBeepNSrc      ceBeepNSrc;                 /*!< ������Դ����������*/
CeLed1C         ceLedCtl_ceLed0;                    
CeLed1C         ceLedCtl_ceLed1;                  
CeLed1C         ceLedCtl_ceLed2;                 
CeLed1C         ceLedCtl_ceLed3; 

int16           ceLedCtl_tick;
CeTicker        ceLedCtl_ceTicker;
CE_LED_CTL_MODE ceLedCtl_ctlMode;

/**
  * @brief  ����4��LED��״̬
  * @param  bitVal:bit0~bit3��Ӧled0~led3�� 0:�رգ�1:��
  */
void ceSysCtl_set4Led(uint8 bitVal)
{
    if((bitVal & 0x01) == 0x01)
        ceLed1COp.setOn(&ceLedCtl_ceLed0);
    else 
        ceLed1COp.setOff(&ceLedCtl_ceLed0);

    if((bitVal & 0x02) == 0x02)
        ceLed1COp.setOn(&ceLedCtl_ceLed1);
    else 
        ceLed1COp.setOff(&ceLedCtl_ceLed1);

    if((bitVal & 0x04) == 0x04)
        ceLed1COp.setOn(&ceLedCtl_ceLed2);
    else 
        ceLed1COp.setOff(&ceLedCtl_ceLed2);

    if((bitVal & 0x08) == 0x08)
        ceLed1COp.setOn(&ceLedCtl_ceLed3);
    else 
        ceLed1COp.setOff(&ceLedCtl_ceLed3);
}

/**
  * @brief  ��ʱ������CeTicker�Ļص���������ϸ�ɲο�CREELINKSƽ̨�й�CeTicker����ĵ�
  * @param  pAddPar:ceLedCtl����ָ��
  */
void ceSysCtl_callBack(void* pAddPar)
{
    if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_FLASH_CYCLE_P)//˳ʱ���Led0��Led3ѭ������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:
        case 22:
        case 32:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 10:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 20:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_OFF);break;
        case 30:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_ON);break;
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
        case 32:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_ON);break;
        case 10:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_OFF);break;
        case 20:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 30:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_FRONT)//�ɺ���ǰ����
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_ON );break;
        case 10:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_BACK)//��ǰ�������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 10:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_ON );break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_LEFT)//������������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_OFF);break;
        case 10:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_ON );break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_RIGHT)//������������
    {
        switch (ceLedCtl_tick)
        {
        case 2:
        case 12:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_ON );break;
        case 10:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_OFF);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_CFG)//�������ü���ʼ��״̬������
    {
        switch (ceLedCtl_tick)
        {
        case 20:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_ON );break;
        case 40:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_NORMAL)//����״̬
    {
        switch (ceLedCtl_tick)
        {
        case 2:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_ON );break;
        case 100:   ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_ERROR)//����״̬������LED����
    {
        switch (ceLedCtl_tick)
        {
        case 2:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_ON );break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 60:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }
    ceLedCtl_tick++;
}

/**
  * @brief  ϵͳ���ƺ�����ʼ��
  */
void   ceSysCtl_initial(void)
{
    ceBtnx1Op.initialByGpio(&ceBtnLeft,CE_SYS_CTL_BTNX1_RESOURCE_0,CE_NULL);    //ʹ��Gpio�ڳ�ʼ����ťģ��
    ceBtnx1Op.initialByGpio(&ceBtnRight,CE_SYS_CTL_BTNX1_RESOURCE_1,CE_NULL);   //ʹ��Gpio�ڳ�ʼ���Ұ�ťģ��
    ceBeepNSrcOp.initialByGpio(&ceBeepNSrc,CE_SYS_CTL_BEEPNSRC_RESOURCE);       //ʹ��һ·Gpio��Դ�ڳ�ʼ����Դ������
    cePC33VOp.initial(&cePC33V,CE_SYS_CTL_PC33V_RESOURCE);                      //ʹ��һ·Ad��Դ�ڳ�ʼ����ѹ����ģ��   


    ceLedCtl_ctlMode = CE_LED_CTL_MODE_OFF;
    ceLedCtl_tick = 0;

    ceLed1COp.initialByGpio(&ceLedCtl_ceLed0,CE_SYS_CTL_LED1C_RESOURCE_0);
    ceLed1COp.initialByGpio(&ceLedCtl_ceLed1,CE_SYS_CTL_LED1C_RESOURCE_1);
    ceLed1COp.initialByGpio(&ceLedCtl_ceLed2,CE_SYS_CTL_LED1C_RESOURCE_2);
    ceLed1COp.initialByGpio(&ceLedCtl_ceLed3,CE_SYS_CTL_LED1C_RESOURCE_3);

    ceLedCtl_ceTicker.callBack = ceSysCtl_callBack;
    ceLedCtl_ceTicker.ID = (uint16)CE_SYS_CTL_LED1C_RESOURCE_0;
    ceLedCtl_ceTicker.intervalMs = 10;
    ceLedCtl_ceTicker.pAddPar = CE_NULL;
    ceTickerOp.registerTicker(&(ceLedCtl_ceTicker)); 
    ceTickerOp.start(&(ceLedCtl_ceTicker));
}

/**
  * @brief  ��ȡ﮵�ص�ѹ
  * @return ��ǰ﮵�صĵ�ѹֵ����λV
  */
fp32    ceSysCtl_getBatVol(void)
{
    return cePC33VOp.getVoltage(&cePC33V); 
}

/**
  * @brief  ���÷���װ�õķ�����ʽ��������һ�����ڵķ���ʱ����ֹͣ����Ϣʱ�䣬�����ڴ�����ʹ������...��...��
  * @param  sayMs:����ʱ�䳤�ȣ���λMs
  * @param  sleepMs:ֹͣ����ʱ�䳤�ȣ���λMs
  * @param  sayTimes:��������
  */
void    ceSysCtl_setAlarm(uint16 sayMs,uint16 sleepMs, uint8 sayTimes)
{
    ceBeepNSrcOp.say(&ceBeepNSrc,sayMs,sleepMs,sayTimes); 
}

/**
  * @brief  ��ȡ���ð�ť״̬
  * @param  btnIndex:��ť����
  * @return 0:��ʾδ���£�1:��ʾ�Ѱ���
  */
uint8   ceSysCtl_getBtnSta(uint8 btnIndex)
{
    if(btnIndex == 0)
        return ceBtnx1Op.getStatus(&ceBtnLeft);
    else 
        return  ceBtnx1Op.getStatus(&ceBtnRight);
}

/**
  * @brief  �������ÿִ��һ������������ʱ��
  * @return whileִ�����ڣ���λs
  */
fp32 ceSysCtl_getSysRunCycle(void)
{
    fp32 dtS;
    static uint64  lastRecordSysTimeUs= 0;
    dtS = (fp32)(ceSystemOp.getSystemTickUs() - lastRecordSysTimeUs)/1000000;
    lastRecordSysTimeUs = ceSystemOp.getSystemTickUs();
    if(dtS > 0.030f) dtS = 0.030f;//�����������Ϊ30ms
    return dtS;
}

/**
  * @brief  ����Ƿ�ͨѶ�ж�
  * @return CE_STATUS_SUCCESS��ͨѶ������ ������ͨѶ�ж�
  */
uint8   ceSysCtl_checkConnectStatus(void) 
{
    return (ceTMCtlOp.checkConnectStatus()==CE_STATUS_SUCCESS)?1:0;
}


/**
  * @brief �����ĸ�LED��˸�ķ�ʽ
  * @param ctlMode:�ĸ�LED��˸�ķ�ʽ
  */
void ceSysCtl_setMode(CE_LED_CTL_MODE ctlMode)
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
CE_LED_CTL_MODE ceSysCtl_getMode()
{
    return ceLedCtl_ctlMode;
}



/**
  * @brief  ��ʼ��CeSysCtlģ���������
  */
const CeSysCtlOp ceSysCtlOp = {ceSysCtl_initial,ceSysCtl_getBatVol,ceSysCtl_setAlarm,ceSysCtl_getBtnSta,ceSysCtl_getSysRunCycle,ceSysCtl_checkConnectStatus,ceSysCtl_setMode,ceSysCtl_getMode};

#ifdef __cplusplus
 }
#endif //__cplusplus

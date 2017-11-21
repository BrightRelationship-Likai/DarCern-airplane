/**
  ******************************************************************************
  * @file    CeSysCtl.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSysCtl模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeSysCtl.h"
#include "CePC33V.h"                    /*!< 电池电压检测模块驱动，用来实现电池电量检测*/
#include "CeBeepNSrc.h"                 /*!< 峰鸣器相关*/
#include "CeBtnx1.h"                    /*!< 无人机上，左右两个按钮模块驱动*/
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

CeBtnx1         ceBtnLeft;                  /*!< 定义无人机左按钮对象*/
CeBtnx1         ceBtnRight;                 /*!< 定义无人机右按钮对象*/
CePC33V         cePC33V;                    /*!< 定义电池电压检测对象*/
CeBeepNSrc      ceBeepNSrc;                 /*!< 定义无源蜂鸣器对象*/
CeLed1C         ceLedCtl_ceLed0;                    
CeLed1C         ceLedCtl_ceLed1;                  
CeLed1C         ceLedCtl_ceLed2;                 
CeLed1C         ceLedCtl_ceLed3; 

int16           ceLedCtl_tick;
CeTicker        ceLedCtl_ceTicker;
CE_LED_CTL_MODE ceLedCtl_ctlMode;

/**
  * @brief  配置4个LED的状态
  * @param  bitVal:bit0~bit3对应led0~led3； 0:关闭；1:打开
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
  * @brief  定时器任务CeTicker的回调函数，详细可参考CREELINKS平台有关CeTicker相关文档
  * @param  pAddPar:ceLedCtl对象指针
  */
void ceSysCtl_callBack(void* pAddPar)
{
    if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_FLASH_CYCLE_P)//顺时针从Led0到Led3循环点亮
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
    }if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_FLASH_CYCLE_N)//顺时针从Led3到Led0循环点亮
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
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_FRONT)//由后向前闪亮
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
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_BACK)//由前向后闪亮
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
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_LEFT)//从右向左闪亮
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

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_RIGHT)//从左向右闪亮
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

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_CFG)//处在配置及初始化状态，快闪
    {
        switch (ceLedCtl_tick)
        {
        case 20:    ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_ON );break;
        case 40:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_NORMAL)//正常状态
    {
        switch (ceLedCtl_tick)
        {
        case 2:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C1_OFF | CE_SYS_CTL_LED1C2_OFF | CE_SYS_CTL_LED1C3_OFF);break;
        case 0:     ceSysCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C1_ON  | CE_SYS_CTL_LED1C2_ON  | CE_SYS_CTL_LED1C3_ON );break;
        case 100:   ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_ERROR)//错误状态，所有LED常亮
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
  * @brief  系统控制函数初始化
  */
void   ceSysCtl_initial(void)
{
    ceBtnx1Op.initialByGpio(&ceBtnLeft,CE_SYS_CTL_BTNX1_RESOURCE_0,CE_NULL);    //使用Gpio口初始化左按钮模块
    ceBtnx1Op.initialByGpio(&ceBtnRight,CE_SYS_CTL_BTNX1_RESOURCE_1,CE_NULL);   //使用Gpio口初始化右按钮模块
    ceBeepNSrcOp.initialByGpio(&ceBeepNSrc,CE_SYS_CTL_BEEPNSRC_RESOURCE);       //使用一路Gpio资源口初始化无源蜂鸣器
    cePC33VOp.initial(&cePC33V,CE_SYS_CTL_PC33V_RESOURCE);                      //使用一路Ad资源口初始化电压测量模块   


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
  * @brief  获取锂电池电压
  * @return 当前锂电池的电压值，单位V
  */
fp32    ceSysCtl_getBatVol(void)
{
    return cePC33VOp.getVoltage(&cePC33V); 
}

/**
  * @brief  配置发声装置的发声方式，即配置一个周期的发声时间与停止发声息时间，及周期次数，使发出滴...滴...声
  * @param  sayMs:发声时间长度，单位Ms
  * @param  sleepMs:停止发声时间长度，单位Ms
  * @param  sayTimes:发声次数
  */
void    ceSysCtl_setAlarm(uint16 sayMs,uint16 sleepMs, uint8 sayTimes)
{
    ceBeepNSrcOp.say(&ceBeepNSrc,sayMs,sleepMs,sayTimes); 
}

/**
  * @brief  获取可用按钮状态
  * @param  btnIndex:按钮索引
  * @return 0:表示未按下；1:表示已按下
  */
uint8   ceSysCtl_getBtnSta(uint8 btnIndex)
{
    if(btnIndex == 0)
        return ceBtnx1Op.getStatus(&ceBtnLeft);
    else 
        return  ceBtnx1Op.getStatus(&ceBtnRight);
}

/**
  * @brief  计算程序每执行一个周期所花费时间
  * @return while执行周期，单位s
  */
fp32 ceSysCtl_getSysRunCycle(void)
{
    fp32 dtS;
    static uint64  lastRecordSysTimeUs= 0;
    dtS = (fp32)(ceSystemOp.getSystemTickUs() - lastRecordSysTimeUs)/1000000;
    lastRecordSysTimeUs = ceSystemOp.getSystemTickUs();
    if(dtS > 0.030f) dtS = 0.030f;//限制最大周期为30ms
    return dtS;
}

/**
  * @brief  检测是否通讯中断
  * @return CE_STATUS_SUCCESS：通讯正常； 其它：通讯中断
  */
uint8   ceSysCtl_checkConnectStatus(void) 
{
    return (ceTMCtlOp.checkConnectStatus()==CE_STATUS_SUCCESS)?1:0;
}


/**
  * @brief 配置四个LED闪烁的方式
  * @param ctlMode:四个LED闪烁的方式
  */
void ceSysCtl_setMode(CE_LED_CTL_MODE ctlMode)
{
    if(ctlMode == ceLedCtl_ctlMode) return;//需要配置的状态与当前状态相同，则直接返回
    ceLedCtl_ctlMode = ctlMode;
    ceLedCtl_tick = 0;  

    ceLed1COp.setOff(&ceLedCtl_ceLed0);
    ceLed1COp.setOff(&ceLedCtl_ceLed1);
    ceLed1COp.setOff(&ceLedCtl_ceLed2);
    ceLed1COp.setOff(&ceLedCtl_ceLed3);
}

/**
  * @brief 获取当前四个LED闪烁的方式
  * @return 当前四个LED闪烁的方式
  */
CE_LED_CTL_MODE ceSysCtl_getMode()
{
    return ceLedCtl_ctlMode;
}



/**
  * @brief  初始化CeSysCtl模块操作对象
  */
const CeSysCtlOp ceSysCtlOp = {ceSysCtl_initial,ceSysCtl_getBatVol,ceSysCtl_setAlarm,ceSysCtl_getBtnSta,ceSysCtl_getSysRunCycle,ceSysCtl_checkConnectStatus,ceSysCtl_setMode,ceSysCtl_getMode};

#ifdef __cplusplus
 }
#endif //__cplusplus

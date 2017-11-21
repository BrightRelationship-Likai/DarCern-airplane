/**
  ******************************************************************************
  * @file    CeLedCtl.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeLedCtl模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
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
  * @brief  配置4个LED的状态
  * @param  bitVal:bit0~bit3对应led0~led3； 0:关闭；1:打开
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
  * @brief  定时器任务CeTicker的回调函数，详细可参考CREELINKS平台有关CeTicker相关文档
  * @param  pAddPar:ceLedCtl对象指针
  */
void ceLedCtl_callBack(void* pAddPar)
{
    if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_FLASH_CYCLE_P)//顺时针从Led0到Led3循环点亮
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
    }if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_FLASH_CYCLE_N)//顺时针从Led3到Led0循环点亮
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
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_FRONT)//由后向前闪亮
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
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_BACK)//由前向后闪亮
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
    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_LEFT)//从右向左闪亮
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

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_GOTO_RIGHT)//从左向右闪亮
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

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_CFG)//处在配置及初始化状态，快闪
    {
        switch (ceLedCtl_tick)
        {
        case 20:    ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON );break;
        case 40:    ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_NORMAL)//正常状态
    {
        switch (ceLedCtl_tick)
        {
        case 2:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF | CE_SYS_CTL_LED1C0_OFF);break;
        case 0:     ceLedCtl_set4Led(CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON  | CE_SYS_CTL_LED1C0_ON );break;
        case 100:   ceLedCtl_tick = -1;break;
        default:break;
        }

    }else if(ceLedCtl_ctlMode == CE_LED_CTL_MODE_IN_ERROR)//错误状态，所有LED常亮
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
  * @brief  CeLedCtl模块初始化
  * @param  @param ceGpioM0-3:四个LED使用的Gpio资源号
  * @return 系统状态码
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
  * @brief 配置四个LED闪烁的方式
  * @param ctlMode:四个LED闪烁的方式
  */
void ceLedCtl_setMode(CE_LED_CTL_MODE ctlMode)
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
CE_LED_CTL_MODE ceLedCtl_getMode()
{
    return ceLedCtl_ctlMode;
}
/**
  * @brief  初始化CeLedCtl模块操作对象
  */
const CeLedCtlOp ceLedCtlOp = {ceLedCtl_initial,ceLedCtl_setMode,ceLedCtl_getMode};

#ifdef __cplusplus
 }
#endif //__cplusplus

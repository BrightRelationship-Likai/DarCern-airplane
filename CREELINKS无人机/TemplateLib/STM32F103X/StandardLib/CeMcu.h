/**
  ******************************************************************************
  * @file    CeMcu.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2016-08-05
  * @brief   Creelinks与处理器硬件平台相关的配置内容
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_MCU_H__
#define __CE_MCU_H__
#include "stm32f10x.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/*Creelinks平台处理器基本资源配置****************************************/
#define CE_MCU_CLOCK_FREQUENCY_MHZ  72                          /*!< MCU时钟最高频率，单位MHz*/

#define CE_MCU_ROM_SIZE_KB          512                         /*!< MCU ROM容量*/
#define CE_MCU_RAM_SIZE_KB          192                         /*!< MCU RAM容量*/

/*Creelinks平台System资源配置****************************************/
#define CE_SYSTEM_DELAY_USE_TIMX    Timer5                      /*!< 系统delay函数使用一个定时器实现，此处需指派使用哪个定时器，可选TIM2~TIM7*/


/*Creelinks平台Ad转换资源配置****************************************/
#define CE_AD_CONVERT_REF_VCC       (fp32)(3.3f)                /*!< 宏定义Ad转换的参考电压3.3V*/
#define CE_AD_CONVERT_WIDTH         (uint16)(12)                /*!< 宏定义Ad转换宽度*/
#define CE_AD_CONVERT_TIME_NS       (uint16)1000                /*!< 宏定义Ad完成一次转换所用的时间，单位ns*/
#define CE_AD_CONVERT_MAX_VAL       (uint32)(0x0FFF)            /*!< 宏定义Ad转换所得的最大值*/

/*Creelinks平台Ccp资源配置参数***************************************/
#define CE_CCP_MAX_COUNT            (uint32)65535               /*!< CCP所支持的最大计数值*/

/*Creelinks平台Da转换器资源配置参数**********************************/
#define CE_DA_CONVERT_WIDTH         (uint32)12                  /*!< Da资源的转换宽度*/
#define CE_DA_CONVERT_TIME_NS       (uint32)0                   /*!< Da资源数据最小转换时间*/
#define CE_DA_MIN_INTERVAL_NS       (uint32)14                  /*!< 两个数据转换时间间隔小值*/
#define CE_DA_MAX_INTERVAL_NS       (uint32)59652323555         /*!< 两个数据转换时间间隔大值*/
#define CE_DA_CONVERT_MAX_VAL       (uint32)0x0FFF              /*!< Da资源的转换的最大值*/

/*Creelinks平台Flash资源配置参数************************************/
#define CE_FLASH_SIZE               (uint32)2048                /*!< 宏定义Flash总容量，单位Byte*/
#define CE_FLASH_READ_SIZE          (uint32)2                   /*!< 宏定义，进行一次Flash读取的最小长度，读地址需为此值的整数倍*/
#define CE_FLASH_WRITE_SIZE         (uint32)2                   /*!< 宏定义，进行一次Flash写入的最小长度，单位Byte，写地址需为此值的整数倍*/
#define CE_FLASH_ERASE_SIZE         (uint32)2048                /*!< 宏定义，进行一次Flash擦除的最小长度，单位Byte，擦除时的首地址，及需要擦除的长度需为此值的整数倍*/

/*Creelinks平台Gpio资源配置参数*************************************/
#define CE_GPIO_SPEED_MHZ           (uint32)50                  /*!< GPIO口的最大电平翻转速率*/
#define CE_SET_GPIO_BIT(ceGpio)     ((ceGpio)->ceExGpioPar.ceExGpiox->BSRR = (ceGpio)->ceExGpioPar.ceExGpioPinx)   /*!< 宏定义Gpio设置高电平，用于对GPIO效率要求较为严格的场合*/
#define CE_RESET_GPIO_BIT(ceGpio)   ((ceGpio)->ceExGpioPar.ceExGpiox->BRR = (ceGpio)->ceExGpioPar.ceExGpioPinx)    /*!< 宏定义Gpio设置低电平，用于对GPIO效率要求较为严格的场合*/
#define CE_GET_GPIO_BIT(ceGpio)     ((ceGpio)->ceExGpioPar.ceExGpiox->IDR  & (ceGpio)->ceExGpioPar.ceExGpioPinx == 0 ? 0x00:0x01)        /*!< 宏定义获取Gpio电平，用于对GPIO效率要求较为严格的场合*/
#define CE_SET_GPIO_MODE(ceGpio,ceGpioMode)  ceGpio_setMode((ceGpio), (ceGpioMode))                          /*!< 宏定义设置Gpio接口工作模式，用于对GPIO效率要求较为严格的场合*/

/*Creelinks平台Pwm资源配置参数**************************************/
#define CE_PWM_MAX_CYCLE_NS     (uint32)59652323555         /*!< Pwm所支持的最大周期*/
#define CE_PWM_MIN_CYCLE_NS     (uint32)14                  /*!< Pwm所支持的最小周期*/
#define CE_PWM_MIN_DIVIDE_NS    (uint32)14                  /*!< Pwm所支持的最小精度*/

/*Creelinks平台Uart资源配置参数*************************************/
#define CE_UART_MAX_BAUD_RATE   (uint32)115200              /*!< UART所支持的最大波特率*/
#define CE_UART_MIN_BAUD_RATE   (uint32)2400                /*!< UART所支持的最小波特率*/

/*Creelinks平台代码开关控制*****************************************/
#define __CE_CHECK_PAR__                    /*!< 是否进行参数验证宏定义，如果不使用函数形参验证，请注销此行，以减少编译后生成的代码量*/
#define __CE_USE_DEBUG__                    /*!< 是否使用UARTx口进行代码调试宏定义，若不使用，请注销此行，以减少编译后生成的代码量*/

/*Creelinks平台操作系统相关*****************************************/
//#define __CE_USE_RTOS__                   /*!< 是否处于实时操作系统的环境*/
#define CE_TICKER_CALL_TIME_MS  5           /*!< Ticker任务被RTOS调用的周期*/

#ifdef __CE_USE_RTOS__
#include "ucos_ii.h"
#define CE_STK                  OS_STK      /*!< 定义堆栈类型*/
#define CE_TASK_NAME_LENGTH     OS_TASK_NAME_SIZE /*!< 任务名称允许的长度，这里是32*/
#endif //__CE_USE_RTOS__

/*Creelinks平台资源标记相关*****************************************/
#define CE_RES_MARK_BASE    0xFFFFFF00      /*!< 资源验证标记值*/
#define CE_RES_MARK_GPIO    0x01000100      /*!< GPIO资源*/
#define CE_RES_MARK_PWM     0x01000200      /*!< PWM资源*/
#define CE_RES_MARK_CCP     0x01000400      /*!< CCP资源*/
#define CE_RES_MARK_INT     0x01000800      /*!< INT资源*/
#define CE_RES_MARK_AD      0x01001000      /*!< AD资源*/
#define CE_RES_MARK_DA      0x01001100      /*!< DA资源*/

#define CE_RES_MARK_I2C     0x02000100      /*!< I2C资源*/
#define CE_RES_MARK_UART    0x02000200      /*!< UART资源*/
#define CE_RES_MARK_SPI     0x02000400      /*!< SPI资源*/
#define CE_RES_MARK_CAN     0x02000800      /*!< CAN资源*/
#define CE_RES_MARK_I2S     0x02001000      /*!< I2S资源*/
#define CE_RES_MARK_TG      0x02002000      /*!< TG资源*/
#define CE_RES_MARK_USB     0x02008000      /*!< USB资源*/
#define CE_RES_MARK_TIMER   0x04000100      /*!< Mcu内部定时器资源*/
#define CE_RES_MARK_G8       0x04000200      /*!< Mcu内部定时器资源*/
#define CE_RES_MARK_G16     0x04000400      /*!< Mcu内部定时器资源*/
#define CE_RES_MARK_G32     0x04000800      /*!< Mcu内部定时器资源*/

#define CE_NULL     (void*)0                /*!< 空指针宏定义*/

typedef unsigned    char        uint8;
typedef signed      char        int8;
typedef unsigned    short       uint16;
typedef signed      short       int16;
typedef unsigned    int         uint32;
typedef signed      int         int32;
typedef unsigned    long long   uint64;
typedef signed      long long   int64;
typedef             float       fp32;
typedef             double      fp64;


/**
 * @brief  驱动文件状态指示码
 */
typedef enum
{
    CE_STATUS_FAILE             = 0x0000,   /*!< 操作失败*/
    CE_STATUS_SUCCESS           = 0x0001,   /*!< 操作成功*/
    CE_STATUS_RESOURCE_ERROR    = 0x0002,   /*!< 资源指定错误*/
    CE_STATUS_INITIAL_FALSE     = 0x0004,   /*!< 初始化失败*/
    CE_STATUS_NULL_POINTER      = 0x0008,   /*!< 指针为空错误*/
    CE_STATUS_MALLOC_FALSE      = 0x0010,   /*!< 内容分配失败*/
    CE_STATUS_PAR_ERROR         = 0x0011,   /*!< 参数错误*/
    CE_STATUS_OUT_TIME          = 0x0012,   /*!< 超时状态*/
} CE_STATUS;

/**
  * @brief  枚举，GPIO模式配置
  */
typedef enum
{
    CE_GPIO_MODE_AIN         = 0x0,         /*!< 模拟输入*/
    CE_GPIO_MODE_IN_FLOATING = 0x04,        /*!< 浮空输入*/
    CE_GPIO_MODE_IPD         = 0x28,        /*!< 下拉输入*/
    CE_GPIO_MODE_IPU         = 0x48,        /*!< 上拉输入*/
    CE_GPIO_MODE_OUT_OD      = 0x14,        /*!< 开漏输出*/
    CE_GPIO_MODE_OUT_PP      = 0x10,        /*!< 推挽输出*/
    CE_GPIO_MODE_AF_OD       = 0x1C,        /*!< 复用开漏输出*/
    CE_GPIO_MODE_AF_PP       = 0x18         /*!< 复用推挽输出*/
}CE_GPIO_MODE;

/**
  * @brief  驱动文件及核心板可用的资源号，与PCB板丝印对应
  */
typedef enum
{
        CE_NULL_RESOURCE    = 0x00000000,
        PA0ACGIP            = 0x00000000 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_AD | CE_RES_MARK_INT | CE_RES_MARK_CCP,
        PA1AGIP             = 0x00000001 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PA2AGIP             = 0x00000002 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PA3AGIP             = 0x00000003 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PA4ADGI             = 0x00000004 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PA5ADGI             = 0x00000005 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PA6AGI              = 0x00000006 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PA7AGI              = 0x00000007 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PA8ClkGIP           = 0x00000008 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PA9GIP              = 0x00000009 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PA10GIP             = 0x0000000A | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PA11GIP             = 0x0000000B | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PA12CGI             = 0x0000000C | CE_RES_MARK_GPIO | CE_RES_MARK_INT | CE_RES_MARK_CCP,
        PA13GI              = 0x0000000D | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PA14GI              = 0x0000000E | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PA15GIP             = 0x0000000F | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,

        PB0AGIP             = 0x00000010 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PB1AGIP             = 0x00000011 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PB2GI               = 0x00000012 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PB3GIP              = 0x00000013 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PB4GIP              = 0x00000014 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PB5GIP              = 0x00000015 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PB6GIP              = 0x00000016 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PB7GIP              = 0x00000017 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PB8GIP              = 0x00000018 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PB9GI               = 0x00000019 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PB10GIP             = 0x0000001A | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PB11GIP             = 0x0000001B | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PB12GI              = 0x0000001C | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PB13GI              = 0x0000001D | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PB14GI              = 0x0000001E | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PB15GI              = 0x0000001F | CE_RES_MARK_GPIO | CE_RES_MARK_INT,

        PC0AGI              = 0x00000020 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PC1AGI              = 0x00000021 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PC2AGI              = 0x00000022 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PC3AGI              = 0x00000023 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PC4AGI              = 0x00000024 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PC5AGI              = 0x00000025 | CE_RES_MARK_GPIO | CE_RES_MARK_AD | CE_RES_MARK_INT,
        PC6GIP              = 0x00000026 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PC7GIP              = 0x00000027 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PC8GIP              = 0x00000028 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PC9GIP              = 0x00000029 | CE_RES_MARK_GPIO | CE_RES_MARK_PWM | CE_RES_MARK_INT,
        PC10GI              = 0x0000002A | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PC11GI              = 0x0000002B | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PC12GI              = 0x0000002C | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PC13GI              = 0x0000002D | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PC14GI              = 0x0000002E | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PC15GI              = 0x0000002F | CE_RES_MARK_GPIO | CE_RES_MARK_INT,

        PD0GI               = 0x00000030 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD1GI               = 0x00000031 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD2CGI              = 0x00000032 | CE_RES_MARK_GPIO | CE_RES_MARK_INT | CE_RES_MARK_CCP,
        PD3GI               = 0x00000033 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD4GI               = 0x00000034 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD5GI               = 0x00000035 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD6GI               = 0x00000036 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD7GI               = 0x00000037 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD8GI               = 0x00000038 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD9GI               = 0x00000039 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD10GI              = 0x0000003A | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD11GI              = 0x0000003B | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD12GI              = 0x0000003C | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD13GI              = 0x0000003D | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD14GI              = 0x0000003E | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PD15GI              = 0x0000003F | CE_RES_MARK_GPIO | CE_RES_MARK_INT,

        PE0GI               = 0x00000040 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE1GI               = 0x00000041 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE2GI               = 0x00000042 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE3GI               = 0x00000043 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE4GI               = 0x00000044 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE5GI               = 0x00000045 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE6GI               = 0x00000046 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE7GI               = 0x00000047 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE8GI               = 0x00000048 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE9GI               = 0x00000049 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE10GI              = 0x0000004A | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE11GI              = 0x0000004B | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE12GI              = 0x0000004C | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE13GI              = 0x0000004D | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE14GI              = 0x0000004E | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PE15GI              = 0x0000004F | CE_RES_MARK_GPIO | CE_RES_MARK_INT,

        PF0GI               = 0x00000050 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF1GI               = 0x00000051 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF2GI               = 0x00000052 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF3GI               = 0x00000053 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF4GI               = 0x00000054 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF5GI               = 0x00000055 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF6GI               = 0x00000056 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF7GI               = 0x00000057 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF8GI               = 0x00000058 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF9GI               = 0x00000059 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF10GI              = 0x0000005A | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF11GI              = 0x0000005B | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF12GI              = 0x0000005C | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF13GI              = 0x0000005D | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF14GI              = 0x0000005E | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PF15GI              = 0x0000005F | CE_RES_MARK_GPIO | CE_RES_MARK_INT,

        PG0GI               = 0x00000060 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG1GI               = 0x00000061 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG2GI               = 0x00000062 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG3GI               = 0x00000063 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG4GI               = 0x00000064 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG5GI               = 0x00000065 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG6GI               = 0x00000066 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG7GI               = 0x00000067 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG8GI               = 0x00000068 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG9GI               = 0x00000069 | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG10GI              = 0x0000006A | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG11GI              = 0x0000006B | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG12GI              = 0x0000006C | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG13GI              = 0x0000006D | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG14GI              = 0x0000006E | CE_RES_MARK_GPIO | CE_RES_MARK_INT,
        PG15GI              = 0x0000006F | CE_RES_MARK_GPIO | CE_RES_MARK_INT,

        PAG8H               = 0X00000000 | CE_RES_MARK_G8,
        PAG8L               = 0X00000001 | CE_RES_MARK_G8,
        PBG8H               = 0X00000002 | CE_RES_MARK_G8,
        PBG8L               = 0X00000003 | CE_RES_MARK_G8,
        PCG8H               = 0X00000004 | CE_RES_MARK_G8,
        PCG8L               = 0X00000005 | CE_RES_MARK_G8,

        PAG16               = 0X00000006 | CE_RES_MARK_G16,
        PBG16               = 0X00000007 | CE_RES_MARK_G16,
        PCG16               = 0X00000008 | CE_RES_MARK_G16,

        I2c1                = 0x00000000 | CE_RES_MARK_I2C,
        I2c2                = 0x00000001 | CE_RES_MARK_I2C,
        I2c3                = 0x00000002 | CE_RES_MARK_I2C,

        Spi1                = 0x00000000 | CE_RES_MARK_SPI,
        Spi2                = 0x00000001 | CE_RES_MARK_SPI,
        Spi3                = 0x00000002 | CE_RES_MARK_SPI,

        Timer1              = 0x00000000 | CE_RES_MARK_TIMER,
        Timer2              = 0x00000001 | CE_RES_MARK_TIMER,
        Timer3              = 0x00000002 | CE_RES_MARK_TIMER,
        Timer4              = 0x00000003 | CE_RES_MARK_TIMER,
        Timer5              = 0x00000004 | CE_RES_MARK_TIMER,
        Timer6              = 0x00000005 | CE_RES_MARK_TIMER,
        Timer7              = 0x00000006 | CE_RES_MARK_TIMER,
        Timer8              = 0x00000007 | CE_RES_MARK_TIMER,

        Uart1               = 0x00000000 | CE_RES_MARK_UART,
        Uart2               = 0x00000001 | CE_RES_MARK_UART,
        Uart3               = 0x00000002 | CE_RES_MARK_UART,
        Uart4               = 0x00000003 | CE_RES_MARK_UART,
        Uart5               = 0x00000004 | CE_RES_MARK_UART,
}CE_RESOURCE;


/*!< 为兼容ELinkSTM及ELinkSTM_PRO核心板资源定义*/
#define R1AGP           PB0AGIP
#define R2TI2c          I2c1
#define R2TI2c_Gpio0    PB0AGIP
#define R2TI2c_Gpio1    PB6GIP
#define R2TI2c_Gpio2    PB7GIP
#define R3GI            PB6GIP
#define R4AG            PC3AGI
#define R5ACGPW         PA0ACGIP
#define R6ADIG          PA4ADGI
#define R7Spi           Spi1
#define R8ADIG          PA5ADGI
#define R9Uart          Uart3
#define R10TI2c         I2c2
#define R10TI2c_Gpio0   PA8ClkGIP
#define R10TI2c_Gpio1   PB10GIP
#define R10TI2c_Gpio2   PB11GIP
//#define R11I2s        I2s2
#define R12Spi          Spi2
#define R13GP           PA9GIP
#define R14Uart         Uart1
#define R15G            PA10GIP
#define R16Spi          Spi3
#define R17GI           PC12GI
#define R18Uart         Uart5
#define R19G            PD2CGI
#define R20AGI          PC0AGI
#define R21AGI          PC1AGI
#define R22AGI          PC2AGI
#define R23AGI          PC3AGI
#define R24Uart         Uart2
#define R25AG           PA2AGIP
//#define R26L36        L36
#define R27GIP          PC8GIP
//#define R28TI2c       ti2c
#define R28TI2c_Gpio0   PB9GI
#define R28TI2c_Gpio1   PA12CGI
#define R28TI2c_Gpio2   PA11GIP
//#define R29CanUst     usb
#define R30GI           PC11GI
#define R31Uart         Uart4
#define R32GI           PC10GI
#define R33Timer        Timer1
#define R34Timer        Timer2
#define R35Timer        Timer3
#define R36Timer        Timer4
#define R37Timer        Timer6
#define R38Timer        Timer7
#define R39Timer        Timer8

/**
  * @brief  结构体，Pwm对象内部扩展属性集合
  */
typedef struct
{
    TIM_TypeDef*    ceExTimx;                           /*!< Pwm使用的TIMx资源，用户无须关注*/
    GPIO_TypeDef*   ceExGpiox;                          /*!< Pwm对应的STM32F103引脚名，用户无须关注*/
    uint16          ceExGpioPinx;                       /*!< Pwm对应的STM32F103引脚号，用户无须关注*/
    uint16          ceExTimPrescaler;
    uint16          ceExTimPeriod;
    uint16          ceExTimCCRx;
    uint32          ceExOldCycle;
    uint32          ceExOldDuty;
}CeExPwmPar;

/**
  * @brief  结构体，AD对象内部扩展属性集合
  */
typedef struct
{
    GPIO_TypeDef*   ceExGpiox;                          /*!< Ad对应的STM32F103引脚名，用户无须关注*/
    uint16          ceExGpioPinx;                       /*!< Ad对应的STM32F103引脚号，用户无须关注*/
    uint8           ceAdChannelx;                       /*!< Ad对应的STM32F103的AD通道，用户无须关注*/
}CeExAdPar;



/**
  * @brief  结构体，CCP对象内部扩展属性集合
  */
typedef struct
{
    uint32          ceExOutCcpCnt;                      /*!< Ccp溢出的次数，用户无须关注*/

    TIM_TypeDef*    ceExTIMx;                           /*!< Ccp对应的STM32F103的TIMx，用户无须关注*/
}CeExCcpPar;

/**
  * @brief  结构体，DA对象内部扩展属性集合
  */
typedef struct
{
    uint8                   ceExIsConvertFinish;        /*!< Da转换是否完成，用户无须关注*/
    DMA_Channel_TypeDef*    ceExDMAChannel;             /*!< Da对应的STM32F103的DMA通道，用户无须关注*/
    TIM_TypeDef*            ceExTIMx;                   /*!< Da对应的STM32F103的TIMx，用户无须关注*/
    uint32                  ceExDAC_Channel_x;          /*!< Da对应的STM32F103的DA_DMA，用户无须关注*/
    GPIO_TypeDef*           ceExGpiox;                  /*!< Da对应的STM32F103的引脚名，用户无须关注*/
    uint16                  ceExGpioPinx;               /*!< Da对应的STM32F103的引脚号，用户无须关注*/
}CeExDaPar;

/**
  * @brief  结构体，GPIO对象内部扩展属性集合
  */
typedef struct
{
    GPIO_TypeDef*   ceExGpiox;                          /*!< 对应STM32F103的引脚名，用户无须关注*/
    uint16          ceExGpioPinx;                       /*!< 对应STM32F103的引脚编号，用户无须关注*/
}CeExGpioPar;

/**
  * @brief  结构体，I2cMaster对象内部扩展属性集合
  */
typedef struct
{
    uint16              ceExDelayNs;                    /*!< I2C电平建立最小时间，用户无须关注*/
    GPIO_TypeDef*       ceExSCLGpiox;                   /*!< I2C SCL引脚对应的STM32F103引脚名，用户无须关注*/
    uint16              ceExSCLGpioPinx;                /*!< I2C SCL引脚对应的STM32F103引脚号，用户无须关注*/
    GPIO_TypeDef*       ceExSDAGpiox;                   /*!< I2C SDA引脚对应的STM32F103引脚名，用户无须关注*/
    uint16              ceExSDAGpioPinx;                /*!< I2C SDA引脚对应的STM32F103引脚号，用户无须关注*/
    uint8*              ceExI2cMasterStatusx;           /*!< I2c使用的总线状态位地址，用户无须关注*/
}CeExI2cMasterPar;

/**
  * @brief  结构体，外部中断Int对象内部扩展属性集合
  */
typedef struct
{
    GPIO_TypeDef*       ceExGpiox;                      /*!< 外部中断Int对应的STM32F103的引脚名，用户无须关注*/
    uint16              ceExGpioPinx;                   /*!< 外部中断Int对应的STM32F103的引脚号，用户无须关注*/
    uint8               ceExIsStart;                    /*!< 外部中断Int是否处于工作当中，用户无须关注*/
    NVIC_InitTypeDef    ceExNVIC_InitStructure;         /*!< 外部中断Int中断初始化配置结构体，用户无须关注*/
    EXTI_InitTypeDef    ceExEXTI_InitStructure;
}CeExIntPar;

/**
  * @brief  结构体，SpiMaster对象内部扩展属性集合
  */
typedef struct
{
    SPI_TypeDef*        ceExSPIx;                       /*!< SPI对应的STM32F103内部资源，用户无须关注*/
    GPIO_TypeDef*       ceExNSSGpiox;                   /*!< SPI NSS引脚对应的STM32F103引脚名，用户无须关注*/
    uint16              ceExNSSGpioPinx;                /*!< SPI NSS引脚对应的STM32F103引脚号，用户无须关注*/
    GPIO_TypeDef*       ceExSCKGpiox;                   /*!< SPI SCK引脚对应的STM32F103引脚名，用户无须关注*/
    uint16              ceExSCKGpioPinx;                /*!< SPI SCK引脚对应的STM32F103引脚号，用户无须关注*/
    GPIO_TypeDef*       ceExMOSIGpiox;                  /*!< SPI MOSI引脚对应的STM32F103引脚名，用户无须关注*/
    uint16              ceExMOSIGpioPinx;               /*!< SPI MOSI引脚对应的STM32F103引脚号，用户无须关注*/
    GPIO_TypeDef*       ceExMISOGpiox;                  /*!< SPI MISO引脚对应的STM32F103引脚名，用户无须关注*/
    uint16              ceExMISOGpioPinx;               /*!< SPI MISO引脚对应的STM32F103引脚号，用户无须关注*/
    uint8*              ceExSpiMasterStatusx;           /*!< SPI使用的总线状态位地址，用户无须关注*/
}CeExSpiMasterPar;

/**
  * @brief  结构体，Uart对象内部扩展属性集合
  */
typedef struct
{
    DMA_Channel_TypeDef *   ceExDMAChannelTx;           /*!< Uart对应STM32F103的发送DMA通道编号，用户无须关注*/
    DMA_Channel_TypeDef *   ceExDMAChannelRx;           /*!< Uart对应STM32F103的接收DMA通道编号，用户无须关注*/
    uint32                  ceExDMAx_FLAG_GLx_Tx;       /*!< Uart对应STM32F103的DMA发送标志，用户无须关注*/
    uint32                  ceExDMAx_FLAG_GLx_Rx;       /*!< Uart对应STM32F103的DMA接收标志，用户无须关注*/
    uint8                   ceExDMAx_Channelx_IRQn;     /*!< Uart对应STM32F103的UART_DMA中断号，用户无须关注*/
    USART_TypeDef *         ceExUartx;                  /*!< Uart对应STM32F103的资源，用户无须关注*/
    uint8                   ceExIsSendFinishFlag;       /*!< Uart发生是否完成标志*/
}CeExUartPar;

/**
  * @brief  结构体，Tg对象内部扩展属性集合
  */
typedef struct
{
    GPIO_TypeDef*   ceExGpiox0;                         /*!< Tg 第一个GPIO对应的对应的引脚名，用户无须关注*/
    uint16          ceExGpioPinx0;                      /*!< Tg 第一个GPIO对应的对应的引脚编号，用户无须关注*/
    GPIO_TypeDef*   ceExGpiox1;                         /*!< Tg 第二个GPIO对应的对应的引脚名，用户无须关注*/
    uint16          ceExGpioPinx1;                      /*!< Tg 第二个GPIO对应的对应的引脚编号，用户无须关注*/
    GPIO_TypeDef*   ceExGpiox2;                         /*!< Tg 第三个GPIO对应的对应的引脚名，用户无须关注*/
    uint16          ceExGpioPinx2;                      /*!< Tg 第三个GPIO对应的对应的引脚编号，用户无须关注*/
} CeExTgPar;

/**
  * @brief  结构体，Timer对象内部扩展属性集合
  */
typedef struct
{
    TIM_TypeDef*    ceExTimx;
    uint8           ceExIsStart;                        /*!< 高精度定时器Timer是否处于工作当中，用户无须关注*/
    uint16          ceExTimPrescaler;
    uint16          ceExTimPeriod;
    uint64          ceExIntOccCnt;                      /*!< 定时器从start开始到现在所发生的中断次数*/
} CeExTimerPar;

/**
  * @brief  结构体，Ticker对象内部扩展属性集合
  */
typedef struct
{
    uint32      nowTick;                                /*!< 当前心跳数量*/
    uint8       isRunning;                              /*!< 此定时任务是否正在运行*/
}CeExTickerPar;

/**
  * @brief  结构体，Task对象内部扩展属性集合
  */
typedef struct
{
    uint8   isRunning;                                  /*!< 指示当前线程是否正在运行*/
    #ifdef __CE_USE_RTOS__
    uint8   ceExTaskPriority;
    #endif
}CeExTaskPar;

#ifdef __CE_CHECK_PAR__
extern void ce_assert_failed(uint8* file, uint32 line,CE_STATUS ceStatus);              /*!< 程序运行出错，则根据此函数打印错误信息*/
#endif //__CE_CHECK_PAR__

#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_MCU_H__

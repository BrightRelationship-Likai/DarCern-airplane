/**
  ******************************************************************************
  * @file    CeTg.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2016-08-05
  * @brief   基于STM32F103RET6处理器平台的CeTg资源函数实现库文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeTg.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#ifdef __CE_USE_TG__

#ifdef __CE_CHECK_PAR__
/**
  * @brief  检验Tg属性对象的值是否正确
  * @param  ceTg:Tg属性对象指针
  * @return 系统状态码，可能的返回值:CE_STATUS_SUCCESS、CE_STATUS_RESOURCE_ERROR、CE_STATUS_NULL_POINTER
  */
CE_STATUS ceTg_checkPar(CeTg* ceTg)
{
    if (ceTg == CE_NULL)
    {
        return CE_STATUS_NULL_POINTER;
    }
    return CE_STATUS_SUCCESS;
}
#endif //__CE_CHECK_PAR__

/**
  * @brief  根据通用的Creelinks平台GPIO的模式，选择对应SSTM32F103处理器的引脚模式
  * @param  ceTg:Tg属性对象指针
  * @return 对应STM32F103的GPIO配置模式
  */
GPIOMode_TypeDef ceTg_getGpioMode(CE_GPIO_MODE ceGpioMode)
{
    switch (ceGpioMode)
    {
    case CE_GPIO_MODE_AIN:
        return GPIO_Mode_AIN;
    case CE_GPIO_MODE_IN_FLOATING:
        return GPIO_Mode_IN_FLOATING;
    case CE_GPIO_MODE_IPD:
        return GPIO_Mode_IPD;
    case CE_GPIO_MODE_IPU:
        return GPIO_Mode_IPU;
    case CE_GPIO_MODE_OUT_OD:
        return GPIO_Mode_Out_OD;
    case CE_GPIO_MODE_OUT_PP:
        return GPIO_Mode_Out_PP;
    case CE_GPIO_MODE_AF_OD:
        return GPIO_Mode_AF_OD;
    case CE_GPIO_MODE_AF_PP:
        return GPIO_Mode_AF_PP;
    default:
        return GPIO_Mode_IN_FLOATING;
    }
}

uint16 ceTg_getGpioPin(CE_RESOURCE ceResource, GPIO_TypeDef* ceGpiox)
{
    ceGpiox = ceGpiox;//消除编译警告
    switch (ceResource)
    {
#ifndef __CE_IS_MINI__
    case R5ACGPW:
        ceGpiox = GPIOA;
        return GPIO_Pin_0;
    case R6ADIG:
        ceGpiox = GPIOA;
        return GPIO_Pin_4;
    case R8ADIG:
        ceGpiox = GPIOA;
        return GPIO_Pin_5;
    case R13GP:
        ceGpiox = GPIOA;
        return GPIO_Pin_9;
    case R15G:
        ceGpiox = GPIOA;
        return GPIO_Pin_10;
    case R23AGI:
        ceGpiox = GPIOA;
        return GPIO_Pin_3;
    case R25AG:
        ceGpiox = GPIOA;
        return GPIO_Pin_2;
    case R1AGP:
        ceGpiox = GPIOB;
        return GPIO_Pin_0;
    case R3GI:
        ceGpiox = GPIOB;
        return GPIO_Pin_6;
    case R4AG:
        ceGpiox = GPIOC;
        return GPIO_Pin_3;
    case R17GI:
        ceGpiox = GPIOC;
        return GPIO_Pin_12;
    case R20AGI:
        ceGpiox = GPIOC;
        return GPIO_Pin_0;
    case R21AGI:
        ceGpiox = GPIOC;
        return GPIO_Pin_1;
    case R22AGI:
        ceGpiox = GPIOC;
        return GPIO_Pin_2;
    case R27GIP:
        ceGpiox = GPIOC;
        return GPIO_Pin_8;
    case R30GI:
        ceGpiox = GPIOC;
        return GPIO_Pin_11;
    case R32GI:
        ceGpiox = GPIOC;
        return GPIO_Pin_10;
    case R19G:
        ceGpiox = GPIOD;
        return GPIO_Pin_2;
#else
    case R5ACGIPW:
        ceGpiox = GPIOA;
        return GPIO_Pin_0;
    case R8AGIP:
        ceGpiox = GPIOA;
        return GPIO_Pin_1;
    case R7Uart_GPIO0:
        ceGpiox = GPIOA;
        return GPIO_Pin_2;
    case R7Uart_GPIO1:
        ceGpiox = GPIOA;
        return GPIO_Pin_3;
    case R10ADIG:
        ceGpiox = GPIOA;
        return GPIO_Pin_4;
    case R12ADIG:
        ceGpiox = GPIOA;
        return GPIO_Pin_5;
    case R6AGIP:
        ceGpiox = GPIOA;
        return GPIO_Pin_6;
    case R11Uart_GPIO0:
        ceGpiox = GPIOA;
        return GPIO_Pin_9;
    case R11Uart_GPIO1:
        ceGpiox = GPIOA;
        return GPIO_Pin_10;
#endif
    default:
        return CE_STATUS_RESOURCE_ERROR;
    }
}

/**
  * @brief   初始化一个Tg资源
  * @param   ceTg:Tg属性对象指针
  * @return  系统状态码，可能的返回值:CE_STATUS_SUCCESS、CE_STATUS_RESOURCE_ERROR、CE_STATUS_NULL_POINTER
  */
CE_STATUS ceTg_initial(CeTg* ceTg, CE_GPIO_MODE ceGpioMode0, CE_GPIO_MODE ceGpioMode1, CE_GPIO_MODE ceGpioMode2)
{
    GPIO_InitTypeDef GPIO_InitStructure;
#ifdef __CE_CHECK_PAR__
    ce_assert_failed((uint8*)__FILE__, __LINE__, ceTg_checkPar(ceTg));
#endif //__CE_CHECK_PAR__

    if((ceTg->ceResource & CE_RES_MARK_TG) == CE_RES_MARK_TG)
    {
        if (ceTg->ceResource == R2TI2c)//I2c1,PB0,PB6,PB7
        {
#ifndef __CE_IS_MINI__
            ceTg->ceExTgPar.ceExGpiox0 = GPIOB;
            ceTg->ceExTgPar.ceExGpioPinx0 = GPIO_Pin_0;
#else
            ceTg->ceExTgPar.ceExGpiox0 = GPIOB;
            ceTg->ceExTgPar.ceExGpioPinx0 = GPIO_Pin_8;
#endif
            ceTg->ceExTgPar.ceExGpiox1 = GPIOB;
            ceTg->ceExTgPar.ceExGpioPinx1 = GPIO_Pin_6;
            ceTg->ceExTgPar.ceExGpiox2 = GPIOB;
            ceTg->ceExTgPar.ceExGpioPinx2 = GPIO_Pin_7;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        }
#ifndef __CE_IS_MINI__
        else if (ceTg->ceResource == R10TI2c)//I2c2,PA8,PB10,PB11
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
            ceTg->ceExTgPar.ceExGpiox0 = GPIOA;
            ceTg->ceExTgPar.ceExGpioPinx0 = GPIO_Pin_8;
#else
        else if (ceTg->ceResource == R3TI2c)//I2c2,PA8,PB10,PB11
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            ceTg->ceExTgPar.ceExGpiox0 = GPIOB;
            ceTg->ceExTgPar.ceExGpioPinx0 = GPIO_Pin_9;
#endif
            ceTg->ceExTgPar.ceExGpiox1 = GPIOB;
            ceTg->ceExTgPar.ceExGpioPinx1 = GPIO_Pin_10;
            ceTg->ceExTgPar.ceExGpiox2 = GPIOB;
            ceTg->ceExTgPar.ceExGpioPinx2 = GPIO_Pin_11;
        }
#ifndef __CE_IS_MINI__
        else if (ceTg->ceResource == R28TI2c)//SoftWareI2c2,PB9,PA12,PA11
        {
            ceTg->ceExTgPar.ceExGpiox0 = GPIOB;
            ceTg->ceExTgPar.ceExGpioPinx0 = GPIO_Pin_9;
            ceTg->ceExTgPar.ceExGpiox1 = GPIOA;
            ceTg->ceExTgPar.ceExGpioPinx1 = GPIO_Pin_12;
            ceTg->ceExTgPar.ceExGpiox2 = GPIOA;
            ceTg->ceExTgPar.ceExGpioPinx2 = GPIO_Pin_11;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
        }
#endif
        else
        {
            return CE_STATUS_RESOURCE_ERROR;
        }
    }
    else
    {
        ceTg->ceExTgPar.ceExGpioPinx0 = ceTg_getGpioPin(ceTg->ceResource0, ceTg->ceExTgPar.ceExGpiox0);
        ceTg->ceExTgPar.ceExGpioPinx1 = ceTg_getGpioPin(ceTg->ceResource1, ceTg->ceExTgPar.ceExGpiox1);
        ceTg->ceExTgPar.ceExGpioPinx2 = ceTg_getGpioPin(ceTg->ceResource2, ceTg->ceExTgPar.ceExGpiox2);
    }

    GPIO_InitStructure.GPIO_Pin = ceTg->ceExTgPar.ceExGpioPinx0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = ceTg_getGpioMode(ceGpioMode0);
    GPIO_Init(ceTg->ceExTgPar.ceExGpiox0, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ceTg->ceExTgPar.ceExGpioPinx1;
    GPIO_InitStructure.GPIO_Mode = ceTg_getGpioMode(ceGpioMode1);
    GPIO_Init(ceTg->ceExTgPar.ceExGpiox1, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ceTg->ceExTgPar.ceExGpioPinx2;
    GPIO_InitStructure.GPIO_Mode = ceTg_getGpioMode(ceGpioMode2);
    GPIO_Init(ceTg->ceExTgPar.ceExGpiox2, &GPIO_InitStructure);

    return CE_STATUS_SUCCESS;
}
/**
  * @brief   设置Tg第一个GPIO的值为1
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_setGpio0(CeTg* ceTg)
{
#ifdef USE_FULL_ASSERT
    GPIO_SetBits(ceTg->ceExTgPar.ceExGpiox0, ceTg->ceExTgPar.ceExGpioPinx0);
#else
    ceTg->ceExTgPar.ceExGpiox0->BSRR = ceTg->ceExTgPar.ceExGpioPinx0;
#endif //USE_FULL_ASSERT
}

/**
  * @brief   设置Tg第一个GPIO的值为0
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_resetGpio0(CeTg* ceTg)
{
#ifdef USE_FULL_ASSERT
    GPIO_ResetBits(ceTg->ceExTgPar.ceExGpiox0, ceTg->ceExTgPar.ceExGpioPinx0);
#else
    ceTg->ceExTgPar.ceExGpiox0->BRR = ceTg->ceExTgPar.ceExGpioPinx0;
#endif //USE_FULL_ASSERT
}

/**
  * @brief   获取Tg资源第一个GPIO口的值
  * @param   ceTg:Tg属性对象指针
  * @return  对应GPIO口的值
  */
uint8 ceTg_getGpio0Val(CeTg* ceTg)
{
    return GPIO_ReadInputDataBit(ceTg->ceExTgPar.ceExGpiox0, ceTg->ceExTgPar.ceExGpioPinx0);
}

/**
  * @brief   设置Tg第一个GPIO的工作模式
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_setGpio0Mode(CeTg* ceTg, CE_GPIO_MODE ceGpioMode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = ceTg->ceExTgPar.ceExGpioPinx0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  ceTg_getGpioMode(ceGpioMode);
    GPIO_Init(ceTg->ceExTgPar.ceExGpiox0, &GPIO_InitStructure);
}

/**
  * @brief   设置Tg第二个GPIO的值为1
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_setGpio1(CeTg* ceTg)
{
#ifdef USE_FULL_ASSERT
    GPIO_SetBits(ceTg->ceExTgPar.ceExGpiox1, ceTg->ceExTgPar.ceExGpioPinx1);
#else
    ceTg->ceExTgPar.ceExGpiox1->BSRR = ceTg->ceExTgPar.ceExGpioPinx1;
#endif //USE_FULL_ASSERT
}

/**
  * @brief   设置Tg第二个GPIO的值为0
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_resetGpio1(CeTg* ceTg)
{
#ifdef USE_FULL_ASSERT
    GPIO_ResetBits(ceTg->ceExTgPar.ceExGpiox1, ceTg->ceExTgPar.ceExGpioPinx1);
#else
    ceTg->ceExTgPar.ceExGpiox1->BRR = ceTg->ceExTgPar.ceExGpioPinx1;
#endif //USE_FULL_ASSERT
}

/**
  * @brief   获取Tg资源第二个GPIO口的值
  * @param   ceTg:Tg属性对象指针
  * @return  对应GPIO口的值
  */
uint8 ceTg_getGpio1Val(CeTg* ceTg)
{
    return GPIO_ReadInputDataBit(ceTg->ceExTgPar.ceExGpiox1, ceTg->ceExTgPar.ceExGpioPinx1);
}

/**
  * @brief   设置Tg第二个GPIO的工作模式
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_setGpio1Mode(CeTg* ceTg, CE_GPIO_MODE ceGpioMode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = ceTg->ceExTgPar.ceExGpioPinx1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  ceTg_getGpioMode(ceGpioMode);
    GPIO_Init(ceTg->ceExTgPar.ceExGpiox1, &GPIO_InitStructure);
}

/**
  * @brief   设置Tg第三个GPIO的值为1
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_setGpio2(CeTg* ceTg)
{
#ifdef USE_FULL_ASSERT
    GPIO_SetBits(ceTg->ceExTgPar.ceExGpiox2, ceTg->ceExTgPar.ceExGpioPinx2);
#else
    ceTg->ceExTgPar.ceExGpiox2->BSRR = ceTg->ceExTgPar.ceExGpioPinx2;
#endif //USE_FULL_ASSERT
}

/**
  * @brief   设置Tg第三个GPIO的值为0
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_resetGpio2(CeTg* ceTg)
{
#ifdef USE_FULL_ASSERT
    GPIO_ResetBits(ceTg->ceExTgPar.ceExGpiox2, ceTg->ceExTgPar.ceExGpioPinx2);
#else
    ceTg->ceExTgPar.ceExGpiox2->BRR = ceTg->ceExTgPar.ceExGpioPinx2;
#endif //USE_FULL_ASSERT
}

/**
  * @brief   获取Tg资源第三个GPIO口的值
  * @param   ceTg:Tg属性对象指针
  * @return  对应GPIO口的值
  */
uint8 ceTg_getGpio2Val(CeTg* ceTg)
{
    return GPIO_ReadInputDataBit(ceTg->ceExTgPar.ceExGpiox2, ceTg->ceExTgPar.ceExGpioPinx2);
}

/**
  * @brief   设置Tg第三个GPIO的工作模式
  * @param   ceTg:Tg属性对象指针
  * @return  None
  */
void ceTg_setGpio2Mode(CeTg* ceTg, CE_GPIO_MODE ceGpioMode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = ceTg->ceExTgPar.ceExGpioPinx2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode =  ceTg_getGpioMode(ceGpioMode);
    GPIO_Init(ceTg->ceExTgPar.ceExGpiox2, &GPIO_InitStructure);
}

const CeTgOpBase ceTgOp = {ceTg_initial, ceTg_setGpio0, ceTg_resetGpio0, ceTg_getGpio0Val, ceTg_setGpio0Mode,
                                         ceTg_setGpio1, ceTg_resetGpio1, ceTg_getGpio1Val, ceTg_setGpio1Mode,
                                         ceTg_setGpio2, ceTg_resetGpio2, ceTg_getGpio2Val, ceTg_setGpio2Mode};

#endif //__CE_USE_TG__

#ifdef __cplusplus
 }
#endif //__cplusplus

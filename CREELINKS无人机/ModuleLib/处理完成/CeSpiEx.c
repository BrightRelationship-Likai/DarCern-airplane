/**
  ******************************************************************************
  * @file    CeSpiEx.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeSpiExģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include"CeSpiEx.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeSpiExģ���ʼ��
  * @param  ceSpiEx:CeSpiEx���Զ���ָ��
  * @param  ceGpio0:CeSpiExģ��ʹ�õĵ�һ��Gpio��Դ��
  * @param  ceGpio1:CeSpiExģ��ʹ�õĵڶ���Gpio��Դ��
  * @param  ceGpio2:CeSpiExģ��ʹ�õĵ�����Gpio��Դ��
  * @return ϵͳ״̬��
*/
CE_STATUS ceSpiEx_initial(CeSpiEx* ceSpiEx,CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2)
{
    ceSpiEx->ceGpio0.ceResource = ceGpio0;
    ceSpiEx->ceGpio0.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceSpiEx->ceGpio0));

    ceSpiEx->ceGpio1.ceResource = ceGpio1;
    ceSpiEx->ceGpio1.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceSpiEx->ceGpio1));

    ceSpiEx->ceGpio2.ceResource = ceGpio2;
    ceSpiEx->ceGpio2.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceSpiEx->ceGpio2));

    ceGpioOp.resetBit(&(ceSpiEx->ceGpio0));
    ceGpioOp.resetBit(&(ceSpiEx->ceGpio1));
    ceGpioOp.resetBit(&(ceSpiEx->ceGpio2));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ʹ��ͨ��
  * @param  ceSpiEx:CeSpiEx���Զ���ָ��
  * @param  portIndex:��Ҫʹ�ܵ�ͨ���ţ�0��2
*/
void ceSpiEx_enablePort(CeSpiEx* ceSpiEx, uint8 portIndex)
{
     switch (portIndex)
     {
     case 0:
         ceGpioOp.setBit(&(ceSpiEx->ceGpio0));
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio1));
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio2));
          break;
     case 1:
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio0));
         ceGpioOp.setBit(&(ceSpiEx->ceGpio1));
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio2));
          break;
     case 2:
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio0));
         ceGpioOp.resetBit(&(ceSpiEx->ceGpio1));
         ceGpioOp.setBit(&(ceSpiEx->ceGpio2));
          break;
     default:
          break;
     }
}

/*
 *CeSpiEx��������
*/
const CeSpiExOp ceSpiExOp = {ceSpiEx_initial, ceSpiEx_enablePort};

#ifdef __cplusplus
 }
#endif //__cplusplus


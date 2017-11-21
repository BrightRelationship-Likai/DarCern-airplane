/**
  ******************************************************************************
  * @file    CeBtnx4.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBtnx4ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeBtnx4.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  CeBtnx4ģ��Task��Դʹ�õĻص�����
  * @param  pAddPar:CeBtnx4���Զ���ָ��
*/
void ceBtnx4_taskCallBack(void* pAddPar)
{
    CeBtnx4* ceBtnx4 = (CeBtnx4*)pAddPar;
    uint8 i;
    ceGpioOp.setBit(&(ceBtnx4->ceGpio2));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ceBtnx4->ceGpio2));
    ceSystemOp.delayUs(1);
    ceGpioOp.setBit(&(ceBtnx4->ceGpio2));
    ceSystemOp.delayUs(1);
    for( i = 0; i < 4; i++)//ֻɨ�����λ����
    {
        if(ceGpioOp.getBit(&(ceBtnx4->ceGpio2)) == 0x00)
        {
            if ((ceBtnx4->keyStatus & (uint8)(0x01 << i)) != (uint8)(0x01 << i))
            {
                ceBtnx4->keyStatus |= ((uint8)0x01<<i);
                ceBtnx4->callBackKeyPressEvent(i);
            }
        }
        else
        {
            ceBtnx4->keyStatus &= ~((uint8)0x01 << i);
        }

        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ceBtnx4->ceGpio1));
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ceBtnx4->ceGpio1));
        ceSystemOp.delayUs(1);
    }
}

/**
  * @brief  CeBtnx4ģ��ʹ��Gpio���г�ʼ��
  * @param  ceBtnx4:CeBtnx4���Զ���
  * @param  ceGpio0:CeBtnx4ģ��ʹ�õĵ�һ��Gpio��Դ��
  * @param  ceGpio1:CeBtnx4ģ��ʹ�õĵڶ���Gpio��Դ��
  * @param  ceGpio2:CeBtnx4ģ��ʹ�õĵ�����Gpio��Դ��
  * @param  callBackKeyPressEvent:���̰����¼�����ʱ����Ҫִ�еĺ���:keyCode:�����µļ��룬��Χ0-3
  * @return ϵͳ״̬��
  */
CE_STATUS ceBtnx4_initial(CeBtnx4* ceBtnx4, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackKeyPressEvent)(uint8 keyCode))
{
    ceBtnx4->keyStatus = (uint8)0xFF;

    ceBtnx4->ceGpio0.ceResource = ceGpio0;//SL,����
    ceBtnx4->ceGpio0.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceBtnx4->ceGpio0));

    ceBtnx4->ceGpio1.ceResource = ceGpio1;//CLK,ʱ��
    ceBtnx4->ceGpio1.ceGpioMode = CE_GPIO_MODE_OUT_PP;
    ceGpioOp.initial(&(ceBtnx4->ceGpio1));

    ceBtnx4->ceGpio2.ceResource = ceGpio2;//QH,����
    ceBtnx4->ceGpio2.ceGpioMode = CE_GPIO_MODE_IPU;
    ceGpioOp.initial(&(ceBtnx4->ceGpio2));

    ceBtnx4->callBackKeyPressEvent = callBackKeyPressEvent;

    ceBtnx4->ceTask.ID = ceGpio0;
    ceBtnx4->ceTask.callBack = ceBtnx4_taskCallBack;
    ceBtnx4->ceTask.pAddPar = ceBtnx4;
    ceTaskOp.registerTask(&(ceBtnx4->ceTask));
    ceTaskOp.start(&(ceBtnx4->ceTask));
    return CE_STATUS_SUCCESS;
}

const CeBtnx4Op ceBtnx4Op = {ceBtnx4_initial};

#ifdef __cplusplus
 }
#endif //__cplusplus

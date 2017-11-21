/**
  ******************************************************************************
  * @file    CeBtn16S.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBtn16Sģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeBtn16S.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
/**
  * @brief  CeBtn16Sģ��Task��Դʹ�õĻص�����
  * @param  pAddPar:CeBtn16S���Զ���ָ��
*/
void ceBtn16S_taskCallBack(void* pAddPar)
{
    CeBtn16S* ceBtn16S = (CeBtn16S*)pAddPar;
    uint8 i;
    ceGpioOp.setBit(&(ceBtn16S->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.resetBit(&(ceBtn16S->ceTg));
    ceSystemOp.delayUs(1);
    ceGpioOp.setBit(&(ceBtn16S->ceTg));
    ceSystemOp.delayUs(1);
    for( i = 0; i < 16; i++)
    {
        if(ceTgOp.getGpio2Bit(&(ceBtn16S->ceTg)) == 0x00)
        {
            if ((ceBtn16S->keyStatus & (uint16)(0x0001 << i)) != (uint16)(0x0001 << i))
            {
                ceBtn16S->callBackKeyPressEvent(15 - i);
                ceBtn16S->keyStatus |= ((uint16)0x0001<<i);
            }
        }
        else
        {
            ceBtn16S->keyStatus &= ~((uint16)0x0001 << i);
        }

        ceSystemOp.delayUs(1);
        ceGpioOp.resetBit(&(ceBtn16S->ceTg));
        ceSystemOp.delayUs(1);
        ceGpioOp.setBit(&(ceBtn16S->ceTg));
        ceSystemOp.delayUs(1);
    }
}

/**
  * @brief  CeBtn16Sģ��ʹ��Gpio���г�ʼ��
  * @param  ceBtn16S:CeBtn16S���Զ���
  * @param  ceGpio0:CeBtn16Sģ��ʹ�õĵ�һ��Gpio��Դ��
  * @param  ceGpio1:CeBtn16Sģ��ʹ�õĵڶ���Gpio��Դ��
  * @param  ceGpio2:CeBtn16Sģ��ʹ�õĵ�����Gpio��Դ��
  * @param  callBackKeyPressEvent:���̰����¼�����ʱ����Ҫִ�еĺ�����keyCode:�����µļ���
  * @return ϵͳ״̬��
  */
CE_STATUS ceBtn16S_initialByGpio(CeBtn16S* ceBtn16S, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2, void (*callBackKeyPressEvent)(uint8 keyCode))
{
    ceBtn16S->keyStatus = (uint16)0xffff;

    ceBtn16S->ceTg.ceResource = CE_NULL_RESOURCE;
    ceBtn16S->ceTg.ceResource0 = ceGpio0;//SL,����
    ceBtn16S->ceTg.ceResource1 = ceGpio1;//CLK,ʱ��
    ceBtn16S->ceTg.ceResource2 = ceGpio2;//QH,����
    ceBtn16S->callBackKeyPressEvent = callBackKeyPressEvent;
    ceTgOp.initial(&(ceBtn16S->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_IPU);//ע�⣺Tg����IO������ģʽ����ģ����Ҫ��������ƽ������������������Ϊ��������

    ceBtn16S->ceTask.ID = ceGpio0;
    ceBtn16S->ceTask.callBack = ceBtn16S_taskCallBack;
    ceBtn16S->ceTask.pAddPar = ceBtn16S;
    ceTaskOp.registerTask(&(ceBtn16S->ceTask));
    ceTaskOp.start(&(ceBtn16S->ceTask));
    return CE_STATUS_SUCCESS;
}

/**
  * @brief  CeBtn16Sģ���ʼ��
  * @param  ceBtn16S:CeBtn16S���Զ���
  * @param  ceTg:CeBtn16Sģ��ʹ�õ���Դ��
  * @param  callBackKeyPressEvent:���̰����¼�����ʱ����Ҫִ�еĺ�����keyCode:�����µļ���
  * @return ϵͳ״̬��
  */
CE_STATUS ceBtn16S_initialByTg(CeBtn16S* ceBtn16S, CE_RESOURCE ceTg, void (*callBackKeyPressEvent)(uint8 keyCode))
{
    ceBtn16S->callBackKeyPressEvent = callBackKeyPressEvent;

    ceBtn16S->keyStatus = (uint16)0xffff;

    ceBtn16S->ceTg.ceResource = ceTg;
    ceTgOp.initial(&(ceBtn16S->ceTg), CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_OUT_PP, CE_GPIO_MODE_IPU);

    ceBtn16S->ceTask.ID = ceTg;
    ceBtn16S->ceTask.callBack = ceBtn16S_taskCallBack;
    ceBtn16S->ceTask.pAddPar = ceBtn16S;
    ceTaskOp.registerTask(&(ceBtn16S->ceTask));
    ceTaskOp.start(&(ceBtn16S->ceTask));

    return CE_STATUS_SUCCESS;
}

CeBtn16SOp ceBtn16SOp = { ceBtn16S_initialByGpio, ceBtn16S_initialByTg};

#ifdef __cplusplus
 }
#endif //__cplusplus


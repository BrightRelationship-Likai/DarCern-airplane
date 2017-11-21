/**
  ******************************************************************************
  * @file    CeEvSw.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeEvSwģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeEvSw.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

/**
  * @brief  �ⲿ�ж�Int�ص�����
  * @param  pAddPar:CeEvSw���Զ���ָ��
  */
void ceEvSw_intCallBack(void* pAddPar)
{
    ((CeEvSw*)(pAddPar))->callBackEvent();
}

/**
  * @brief  CeEvSwģ���ʼ��
  * @param  ceEvSw:CeEvSw���Զ���
  * @param  ceInt:CeEvSwģ��ʹ�õ���Դ��
  * @return ϵͳ״̬��
  */
CE_STATUS ceEvSw_initial(CeEvSw* ceEvSw, CE_RESOURCE ceInt, void (*callBackEvent)(void))
{
    ceEvSw->ceInt.ceResource = ceInt;
    ceEvSw->ceInt.callBack = ceEvSw_intCallBack;
    ceEvSw->ceInt.ceIntMode = CE_INT_MODE_TRIGGER_RISING;//��̬�͵�ƽ�������ش���
    ceEvSw->ceInt.pAddPar = CE_NULL;
    ceEvSw->callBackEvent = callBackEvent;
    ceIntOp.initial(&(ceEvSw->ceInt));
    ceIntOp.start(&(ceEvSw->ceInt));

    return CE_STATUS_SUCCESS;
}

/**
  * @brief  ��ȡEvSw��Ӧ��GPIO�ڵĵ�ƽ״̬��0x01��0x00
  * @param  ceEvSw:CeEvSw���Զ���
  * @return ����0�͵�ƽ��ģ�鴦��δ����״̬��1�ߵ�ƽ��ģ�鴦�ڴ���״̬
  */
uint8 ceEvSw_getBit(CeEvSw* ceEvSw)
{
    return ceIntOp.getBit(&(ceEvSw->ceInt));
}

CeEvSwOp ceEvSwOp = {ceEvSw_initial, ceEvSw_getBit};

#ifdef __cplusplus
 }
#endif //__cplusplus

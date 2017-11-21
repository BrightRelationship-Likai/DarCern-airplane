/**
  ******************************************************************************
  * @file       main.c
  * @author     Creelinks Application Team
  * @version    V1.1.0
  * @date       2016-11-10
  * @brief      ����ǰ��̨���㱼��Creelinksƽ̨����ں���
  ******************************************************************************
  * @attention
  *
  *1)����ǰ��̨��ʽ�����ǲ���ϵͳ��ʽ����
  *2)�뱣֤�������������ԣ���ceSystem.initial()��ceSystem.mainTask()����ȱ��
  *3)��Ҫ����ʱ�������while(1)ѭ�����Ա�֤����ģ�鹤��������
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************

#include "Creelinks.h"                                        //����Gpio���Զ���
int main(void)
{
    ceSystemOp.initial();                               //Creelinks������ʼ��
    ceDebugOp.initial(Uart4);                                //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    while (1)
    {
        ceTaskOp.mainTask();                            //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
			ceDebugOp.printf("agasg\n");
    };
}
  */

#include "Creelinks.h"
CeInt myInt;

void intEventCallBack(void* pAddPar)
{
    ceDebugOp.printf("Enter the interrupt, Gpio status:%d\n", ceIntOp.getBit((CeInt*)(pAddPar)));//�����ж��¼��󣬴�ӡ������Ϣ
}
int main(void)
{
    ceSystemOp.initial();                           //Creelinks������ʼ��
    ceDebugOp.initial(Uart3);                            //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    myInt.ceResource = PA4ADGI;                         //ָ����Դ�жϹ���ģ��ʹ�õ���Դ��
    myInt.ceIntMode = CE_INT_MODE_TRIGGER_FALLING;          //ָ���ⲿ�ж����½����ж�
    myInt.pAddPar = &myInt;                         //���ÿ�ָ��ָ���Լ������жϻص���ʹ��
    myInt.callBack = intEventCallBack;              //ָ���¼��ص�����
    ceIntOp.initial(&myInt);                        //��ʼ���ⲿ�ж�
    ceIntOp.start(&myInt);                          //ʹ���ⲿ�ж�
    while (1)
    {
        ceTaskOp.mainTask();                        //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
    };
}




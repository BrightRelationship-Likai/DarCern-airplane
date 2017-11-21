/**
  ******************************************************************************
  * @file       main.c
  * @author     Creelinks Application Team
  * @version    V1.1.0
  * @date       2016-11-10
  * @brief      基于前后台（裸奔）Creelinks平台主入口函数
  ******************************************************************************
  * @attention
  *
  *1)采用前后台方式，即非操作系统方式运行
  *2)请保证主函数的完整性，即ceSystem.initial()和ceSystem.mainTask()不可缺少
  *3)不要过长时间的阻塞while(1)循环，以保证各个模块工作正常。
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************

#include "Creelinks.h"                                        //定义Gpio属性对象
int main(void)
{
    ceSystemOp.initial();                               //Creelinks环境初始化
    ceDebugOp.initial(Uart4);                                //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    while (1)
    {
        ceTaskOp.mainTask();                            //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
			ceDebugOp.printf("agasg\n");
    };
}
  */

#include "Creelinks.h"
CeInt myInt;

void intEventCallBack(void* pAddPar)
{
    ceDebugOp.printf("Enter the interrupt, Gpio status:%d\n", ceIntOp.getBit((CeInt*)(pAddPar)));//进入中断事件后，打印调试信息
}
int main(void)
{
    ceSystemOp.initial();                           //Creelinks环境初始化
    ceDebugOp.initial(Uart3);                            //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    myInt.ceResource = PA4ADGI;                         //指定资源中断功能模块使用的资源号
    myInt.ceIntMode = CE_INT_MODE_TRIGGER_FALLING;          //指定外部中断是下降沿中断
    myInt.pAddPar = &myInt;                         //设置空指针指向自己，在中断回调里使用
    myInt.callBack = intEventCallBack;              //指定事件回调函数
    ceIntOp.initial(&myInt);                        //初始化外部中断
    ceIntOp.start(&myInt);                          //使能外部中断
    while (1)
    {
        ceTaskOp.mainTask();                        //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
    };
}




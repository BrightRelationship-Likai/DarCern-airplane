/**
  ******************************************************************************
  * @file    Ce8Segx2.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于Ce8Segx2模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2017 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_8SEG_X2_H__
#define __CE_8SEG_X2_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_8SEG_X2_VERSION__ 1                                            /*!< 此驱动文件的版本号*/
#define __CE_8SEG_X2_NEED_CREELINKS_VERSION__ 1                             /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_8SEG_X2_NEED_CREELINKS_VERSION__)      /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件Ce8Segx2.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *Ce8Segx2属性对像
 */
typedef struct
{
    CeTg        ceTg;                                                       /*!< 模块使用到的Tg资源属性对象*/
    uint8       showTable0;                                                 /*!< 第一位数码管的状态*/
    uint8       showTable1;                                                 /*!< 第二位数码管的状态*/
}Ce8Segx2;
/*
 *Ce8Segx2操作对像
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(Ce8Segx2* ce8Segx2, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                             @brief Ce8Segx2模块使用三个Gpio口来完成初始化
                                                                             @param ce8Segx2:Ce8Segx2属性对象指针
                                                                             @param ceGpio0:Ce8Segx2模块使用的第一个Gpio口资源号
                                                                             @param ceGpio1:Ce8Segx2模块使用的第二个Gpio口资源号
                                                                             @param ceGpio2:Ce8Segx2模块使用的第三个Gpio口资源号*/

    CE_STATUS   (*initialByTg)(Ce8Segx2* ce8Segx2, CE_RESOURCE ceTg);   /*!< @brief Ce8Segx2模块使用Tg来完成初始化
                                                                             @param ce8Segx2:Ce8Segx2属性对象指针
                                                                             @param ceTg:Ce8Segx2模块使用的资源号*/

    void        (*setOn)(Ce8Segx2* ce8Segx2);                           /*!< @brief 使模块处于开启显示状态
                                                                             @param ce8Segx2:ce8Segx2属性对象指针*/

    void        (*setOff)(Ce8Segx2* ce8Segx2);                          /*!< @brief 使模块处于关闭显示状态
                                                                             @param ce8Segx2:ce8Segx2属性对象指针*/

    void        (*setDpOn)(Ce8Segx2* ce8Segx2, uint8 index);            /*!< @brief 显示小数点
                                                                             @param ce8Segx2:ce8Segx2属性对象指针
                                                                             @param index:在第几位数码管上操作小数点，范围0和1*/

    void        (*setDpOff)(Ce8Segx2* ce8Segx2, uint8 index);           /*!< @brief 隐藏小数点
                                                                             @param ce8Segx2:ce8Segx2属性对象指针
                                                                             @param index:在第几位数码管上操作小数点，范围0和1*/

    void        (*setVal)(Ce8Segx2* ce8Segx2, uint8 val);               /*!< @brief 显示数值
                                                                             @param ce8Segx2:ce8Segx2属性对象指针
                                                                             @param val:欲显示的数值，范围00-99，模块显示00-99。数值的十位显示在第二段，数值的各位显示在第一段*/

    void        (*setChars)(Ce8Segx2* ce8Segx2, char* msg);             /*!< @brief 显示字符
                                                                             @param ce8Segx2:ce8Segx2属性对象指针
                                                                             @param msg:欲显示的字符，字符0-9或大小写英文字符（只有部分字符能完整的显示）*/
}Ce8Segx2Op;
/*
 *Ce8Segx2操作对象实例
 */
extern const Ce8Segx2Op ce8Segx2Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_8SEG_X2_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_8SEG_X2_H__

 /**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 以1增加显示数值
******************************************************************************
#include "Creelinks.h"
#include "Ce8Segx2.h"
uint8 i=0;
Ce8Segx2 mySeg;                                 //定义Ce8Segx2属性对象
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ce8Segx2Op.initialByTg(&mySeg, R2TI2c);     //使用资源号R2TI2c初始化mySeg
    ce8Segx2Op.setOn(&mySeg);                   //开始显示
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ce8Segx2Op.setVal(&mySeg, i);           //设置需要显示的值
        i +=1;
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

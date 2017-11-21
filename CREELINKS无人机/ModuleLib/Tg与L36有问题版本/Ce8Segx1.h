/**
  ******************************************************************************
  * @file    Ce8Segx1.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于Ce8Segx1模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_8SEG_X1_H__
#define __CE_8SEG_X1_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_8SEG_X1_VERSION__ 1                                            /*!< 此驱动文件的版本号*/
#define __CE_8SEG_X1_NEED_CREELINKS_VERSION__ 1                             /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_8SEG_X1_NEED_CREELINKS_VERSION__)      /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件Ce8Segx1.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *Ce8Segx1属性对像
 */
typedef struct
{
    CeTg        ceTg;                                                   /*!< 模块使用到的Tg资源属性对象*/
    uint8       showTable;                                              /*!< 第一位数码管的状态*/
}Ce8Segx1;
/*
 *Ce8Segx1操作对像
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(Ce8Segx1* ce8Segx1, CE_RESOURCE ceGpio0, CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                             @brief Ce8Segx1模块使用三个Gpio口来完成初始化
                                                                             @param ce8Segx1:Ce8Segx1属性对象指针
                                                                             @param ceGpio0:Ce8Segx1模块使用的第一个Gpio口资源号
                                                                             @param ceGpio1:Ce8Segx1模块使用的第二个Gpio口资源号
                                                                             @param ceGpio2:Ce8Segx1模块使用的第三个Gpio口资源号*/

    CE_STATUS   (*initialByTg)(Ce8Segx1* ce8Segx1, CE_RESOURCE ceTg );  /*!< @brief Ce8Segx1模块使用Tg来完成初始化
                                                                             @param ce8Segx1:Ce8Segx1属性对象指针
                                                                             @param ceTg:Ce8Segx1模块使用的资源号*/

    void        (*setOn)(Ce8Segx1* ce8Segx1);                           /*!< @brief 使模块处于开启显示状态
                                                                             @param ce8Segx1:ce8Segx1属性对象指针*/

    void        (*setOff)(Ce8Segx1* ce8Segx1);                          /*!< @brief 使模块处于关闭显示状态
                                                                             @param ce8Segx1:ce8Segx1属性对象指针*/

    void        (*setDpOn)(Ce8Segx1* ce8Segx1);                         /*!< @brief 显示小数点
                                                                             @param ce8Segx1:ce8Segx1属性对象指针*/

    void        (*setDpOff)(Ce8Segx1* ce8Segx1);                        /*!< @brief 隐藏小数点
                                                                             @param ce8Segx1:ce8Segx1属性对象指针*/

    void        (*setVal)(Ce8Segx1* ce8Segx1, uint8 val);               /*!< @brief 显示数值
                                                                             @param ce8Segx1:ce8Segx1属性对象指针
                                                                             @param val:欲显示的数值，范围0-9，模块显示数字0-9*/

    void        (*setChar)(Ce8Segx1* ce8Segx1, char val);               /*!< @brief 显示字符
                                                                             @param ce8Segx1:ce8Segx1属性对象指针
                                                                             @param val:欲显示的字符，字符0-9或大小写英文字符（只有部分字符能完整的显示）*/
}Ce8Segx1Op;
/*
 *Ce8Segx1操作对象实例
 */
extern const Ce8Segx1Op ce8Segx1Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_8SEG_X1_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_8SEG_X1_H__


/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 以1增加显示数值
******************************************************************************
#include "Creelinks.h"
#include "Ce8Segx1.h"
uint8 i=0;
Ce8Segx1 mySeg;                                 //定义Ce8Segx1属性对象
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ce8Segx1Op.initialByTg(&mySeg, R2TI2c);     //使用资源号R2TI2c初始化mySeg
    ce8Segx1Op.setOn(&mySeg);                   //开始显示
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ce8Segx1Op.setVal(&mySeg, i);           //设置需要显示的值
        i +=1;
        ceSystemOp.delayMs(1000);
    };
}
******************************************************************************
*/

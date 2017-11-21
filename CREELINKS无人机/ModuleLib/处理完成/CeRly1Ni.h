/**
  ******************************************************************************
  * @file    CeRly1Ni.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeRly1Ni模块的驱动头文件，控制一路继电器的开关
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_RLY1_NI_H__
#define __CE_RLY1_NI_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_RLY1_NI_VERSION__ 1                                         /*!< 此驱动文件的版本号*/
#define __CE_RLY1_NI_NEED_CREELINKS_VERSION__ 1                         /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_RLY1_NI_NEED_CREELINKS_VERSION__)   /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeRly1Ni.h需要高于18以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeRly1Ni属性对像
 */
typedef struct
{
	CeGpio ceGpio;
}CeRly1Ni;
/*
 *CeRly1Ni操作对像
 */
typedef struct
{
	CE_STATUS (*initial)(CeRly1Ni* ceRly1Ni,CE_RESOURCE ceGpio);	    /*!< @brief	CeRly1Ni模块初始化
														 	 	         @param	ceRly1Ni:CeRly1Ni属性对象指针*/

	void	(*setOn)(CeRly1Ni* ceRly1Ni);	                            /*!< @brief 设置继电器闭合
                                                                         @param	ceRly1Ni:CeRly1Ni属性对象指针*/

	void 	(*setOff)(CeRly1Ni* ceRly1Ni);	                            /*!< @brief	设置继电器断开
                                                                         @param	ceRly1Ni:CeRly1Ni属性对象指针*/
}CeRly1NiOpBase;
/*
 *CeRly1Ni操作对象实例
 */
extern const CeRly1NiOpBase ceRly1NiOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_RLY1_NI_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_RLY1_NI_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境),基于ELinkSTM/ELinkSTM_Pro核心板
* @function 配置继电器以1HZ的频率吸合与断开
******************************************************************************
#include "Creelinks.h"
#include "CeRly1Ni.h"
CeRly1Ni myRly;
int main(void)
{
    ceSystemOp.initial();                         //Creelinks环境初始化
    ceSystemOp.initialDebug(R9Uart);              //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceRly1NiOp.initial(&myRly, R1AGP);            //使用R1AGP的Gpio功能初始化模块
    while (1)
    {
        ceSystemOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ceRly1NiOp.setOn(&myRly);                 //设置继电器状态为吸合
        ceSystemOp.delayMs(500);
        ceRly1NiOp.setOff(&myRly);                //设置继电器状态为断开
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    CeSoundDetS.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSoundDetS模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)Ad转换过程中，会有时间消耗，故两个采集点之间所用时间比用户设定的时间略大
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_SOUND_DET_S_H__
#define __CE_SOUND_DET_S_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_SOUND_DET_S_VERSION__ 1                                             /*!< 此驱动文件的版本号*/
#define __CE_SOUND_DET_S_NEED_CREELINKS_VERSION__ 1                              /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_SOUND_DET_S_NEED_CREELINKS_VERSION__)       /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeSoundDetS.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *CeSoundDetS属性对像
 */
typedef struct
{
    CeAd    ceAd;                                                       /*!< 模块使用到的Ad资源*/
}CeSoundDetS;
/*
 *CeSoundDetS操作对像
 */
typedef struct
{
    CE_STATUS (*initial)(CeSoundDetS* ceSoundDetS, CE_RESOURCE ceAd);    /*!< @brief  CeSoundDetS模块初始化
                                                                              @param  ceSoundDetS:CeSoundDetS属性对象指针
                                                                              @param  ceAd:CeSoundDetS模块使用的Ad资源号*/

    uint16  (*startRecord)(CeSoundDetS* ceSoundDetS, uint16* dataBuf, uint16 dataBuffSize, uint32 intervalUs);/*!<
                                                                              @brief  开始录制声音，死循环，真到录制完后才退出
                                                                              @param  dataBuf:录制的数据缓冲区
                                                                              @param  dataBufSize:录制的数据缓冲区大小
                                                                              @param  intervalNs:两个采样点之间的时间间隔*/

    uint32  (*getConvertResult)(CeSoundDetS* ceSoundDetS);               /*!< @brief  进行一次转换采集，通常用于噪声检测
                                                                              @param  ceSoundDetS:CeSoundDetS属性对象指针
                                                                              @return 当前噪声值，无声为0， MIC头饱和时为CE_AD_CONVERT_MAX_VAL*/

}CeSoundDetSOp;
/*
 *CeSoundDetS操作对象实例
 */
extern const CeSoundDetSOp ceSoundDetSOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_SOUND_DET_S_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_SOUND_DET_S_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 检测环境噪声值，并输出到上位机
******************************************************************************
#include "Creelinks.h"
#include "CeSoundDetS.h"
CeSoundDetS mySoundDetS;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceSoundDetSOp.initial(&mySoundDetS,R1AGP);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        ceDebugOp.printf("Sound Val:%d\n",ceSoundDetSOp.getConvertResult(&mySoundDetS));
        ceSystemOp.delayMs(10);
    };
}
******************************************************************************
*/

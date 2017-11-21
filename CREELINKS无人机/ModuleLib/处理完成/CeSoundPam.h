/**
  ******************************************************************************
  * @file    CeSoundPam.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeSoundPam模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_CE_SOUND_PAM_H__
#define __CE_CE_SOUND_PAM_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_CE_SOUND_PAM_VERSION__ 1                                               /*!< 此驱动文件的版本号*/
#define __CE_CE_SOUND_PAM_NEED_CREELINKS_VERSION__ 1                                /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_CE_SOUND_PAM_NEED_CREELINKS_VERSION__)         /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件CeSoundPam.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else

#define L1      (1000000/262)                                                       /*!< 音符 低音1 的周期*/
#define L1U     (1000000/277)                                                       /*!< 音符 低音#1 的周期*/
#define L2      (1000000/294)                                                       /*!< 音符 低音2 的周期*/
#define L2U     (1000000/311)                                                       /*!< 音符 低音#2 的周期*/
#define L3      (1000000/330)                                                       /*!< 音符 低音3 的周期*/
#define L4      (1000000/349)                                                       /*!< 音符 低音4 的周期*/
#define L4U     (1000000/370)                                                       /*!< 音符 低音#4 的周期*/
#define L5      (1000000/392)                                                       /*!< 音符 低音5 的周期*/
#define L5U     (1000000/415)                                                       /*!< 音符 低音#5 的周期*/
#define L6      (1000000/440)                                                       /*!< 音符 低音6 的周期*/
#define L6U     (1000000/466)                                                       /*!< 音符 低音#6 的周期*/
#define L7      (1000000/494)                                                       /*!< 音符 低音7 的周期*/
#define M1      (1000000/523)                                                       /*!< 音符 中音1 的周期*/
#define M1U     (1000000/554)                                                       /*!< 音符 中音#1 的周期*/
#define M2      (1000000/587)                                                       /*!< 音符 中音2 的周期*/
#define M2U     (1000000/622)                                                       /*!< 音符 中音#2 的周期*/
#define M3      (1000000/659)                                                       /*!< 音符 中音3 的周期*/
#define M4      (1000000/698)                                                       /*!< 音符 中音4 的周期*/
#define M4U     (1000000/740)                                                       /*!< 音符 中音#4 的周期*/
#define M5      (1000000/784)                                                       /*!< 音符 中音5 的周期*/
#define M5U     (1000000/831)                                                       /*!< 音符 中音#5 的周期*/
#define M6      (1000000/880)                                                       /*!< 音符 中音6 的周期*/
#define M6U     (1000000/932)                                                       /*!< 音符 中音#6 的周期*/
#define M7      (1000000/988)                                                       /*!< 音符 中音7 的周期*/
#define H1      (1000000/1046)                                                      /*!< 音符 高音1 的周期*/
#define H1U     (1000000/1109)                                                      /*!< 音符 高音#1 的周期*/
#define H2      (1000000/1175)                                                      /*!< 音符 高音2 的周期*/
#define H2U     (1000000/1245)                                                      /*!< 音符 高音#2 的周期*/
#define H3      (1000000/1318)                                                      /*!< 音符 高音3 的周期*/
#define H4      (1000000/1397)                                                      /*!< 音符 高音4 的周期*/
#define H4U     (1000000/1480)                                                      /*!< 音符 高音#4 的周期*/
#define H5      (1000000/1568)                                                      /*!< 音符 高音5 的周期*/
#define H5U     (1000000/1661)                                                      /*!< 音符 高音#5 的周期*/
#define H6      (1000000/1760)                                                      /*!< 音符 高音6 的周期*/
#define H6U     (1000000/1865)                                                      /*!< 音符 高音#6 的周期*/
#define H7      (1000000/1976)                                                      /*!< 音符 高音7 的周期*/

typedef enum
{
    CE_SOUND_PAM_CH_L,
    CE_SOUND_PAM_CH_R,
    CE_SOUND_PAM_CH_L_AND_R,
}CE_SOUND_PAM_CH;

/*
 *CeSoundPam属性对像
 */
typedef struct
{
    CeDa ceDaL;                             /*!< 模块左通道使用到的Da资源*/
    uint8 workModeL;                        /*!< 模块左通道的工作方式，0:未工作，1：固定频率，2：音乐发声*/
    void(*startFinishCallBackL)(void);      /*!< 存放模块左通道播放完成后执行的回调*/

    CeDa ceDaR;                             /*!< 模块右通道使用到的Da资源*/
    uint8 workModeR;                        /*!< 模块右通道的工作方式，0:未工作，1：固定频率，2：音乐发声*/
    void(*startFinishCallBackR)(void);      /*!< 存放模块右通道播放完成后执行的回调*/
}CeSoundPam;
/*
 *CeSoundPam操作对像
 */
typedef struct
{
     CE_STATUS   (*initial)(CeSoundPam* ceSoundPam, CE_RESOURCE ceDaL, CE_RESOURCE ceDaR);                      /*!< @brief  CeSoundPam模块初始化
                                                                                                                     @param  ceSoundPam:CeSoundPam属性对象指针
                                                                                                                     @param  ceDa:CeSoundPam模块使用的资源号*/

     void        (*start)(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR, uint16* dataBuf, uint16 dataBufSize, uint32 intervalNs, void(*startFinishCallBack)(void));/*!<
                                                                                                                     @brief  使模块按照给定的数字序列及两个点之间的时间间隔来发声，通常用于Mp3等音乐播放
                                                                                                                     @param  ceSoundPam:CeSoundPam属性对象指针
                                                                                                                     @param  chLorR:左声道还是右声道
                                                                                                                     @param  dataBuf:数据缓存，宽度因与DA的转换宽度保持相同
                                                                                                                     @param  dataBufSize:数据缓存的大小
                                                                                                                     @param  intervalNs:两个点之间的时间间隔
                                                                                                                     @param  startFinishCallBack:播放完成后的回调*/

    void        (*startFixFrequencySound)(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR, uint32 fixFreHz);     /*!< @brief  以固定频率发出声音,异步发声，函数配置完成后，直接返回
                                                                                                                     @param  ceSoundPam:CeSoundPam属性对象指针
                                                                                                                     @param  chLorR:左声道还是右声道
                                                                                                                     @param  fixFreHz:发声的频率*/

    void        (*stopFixFrequencySound)(CeSoundPam* ceSoundPam, CE_SOUND_PAM_CH chLorR);                       /*!< @brief  停止以固定频率发出声音,异步发声，函数配置完成后，直接返回
                                                                                                                     @param  ceSoundPam:CeSoundPam属性对象指针
                                                                                                                     @param  chLorR:左声道还是右声道*/
}CeSoundPamOp;
/*
 *CeSoundPam操作对象实例
 */
extern const CeSoundPamOp ceSoundPamOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_CE_SOUND_PAM_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_CE_SOUND_PAM_H__

/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 使用模块模拟警笛声
******************************************************************************
#include "Creelinks.h"
#include "CeSoundPam.h"
CeSoundPam mySoundPam;
uint32 i;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ceSoundPamOp.initial(&mySoundPam,R6ADIG,R8ADIG);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操作
        for(i=650;i<=750;i+=1)                  //以低频650Hz到高频750Hz，持续时间0.23s
        {
            ceSoundPamOp.startFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R,i);
            ceSystemOp.delayMs(2);
            ceSoundPamOp.stopFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R);
        }

        for(i=1450;i<=1550;i+=2)                 //以低频1450Hz到高频1550Hz，持续时间0.1s
        {
            ceSoundPamOp.startFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R,i);
            ceSystemOp.delayMs(2);
            ceSoundPamOp.stopFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R);
        }

        for(i=1550;i>=1450;i-=2)                 //以高频1550Hz到低频1450Hz，持续时间0.1s
        {
            ceSoundPamOp.startFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R,i);
            ceSystemOp.delayMs(2);
            ceSoundPamOp.stopFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R);
        }

        for(i=750;i>=650;i-=1)                  //以高频750Hz到低频650Hz，持续时间0.23s
        {
            ceSoundPamOp.startFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R,i);
            ceSystemOp.delayMs(2);
            ceSoundPamOp.stopFixFrequencySound(&mySoundPam,CE_SOUND_PAM_CH_L_AND_R);
        }
    };
}
******************************************************************************
*/

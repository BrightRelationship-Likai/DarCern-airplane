/**
  ******************************************************************************
  * @file    CeMS5611.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeMS5611ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_MS5611_H__
#define __CE_MS5611_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_MS5611_VERSION__ 1                                             /*!< �������ļ��İ汾��*/
#define __CE_MS5611_NEED_CREELINKS_VERSION__ 1                               /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_MS5611_NEED_CREELINKS_VERSION__)       /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeMS5611.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else



typedef struct
{
    fp32     temperature;        /*!< �¶�ֵ*/
    int32    pressure;           /*!< ��ѹֵ*/
    fp32     altitude;           /*!< ���θ߶�*/
}CeMS5611Environment;

/*
 *CeMS5611���Զ���
 */
typedef struct
{
    CeI2cMaster ceI2cMaster;
    int16       AC1;
    int16       AC2;
    int16       AC3;
    uint16      AC4;
    uint16      AC5;
    uint16      AC6;
    int16       B1;
    int16       B2;
    int16       MB;
    int16       MC;
    int16       MD;
    int32       UT;
    int32       UP;
    CeMS5611Environment environment;
    uint32 lastSystemTimeMs;    /*!< ����MS5611����һ����ѹ��ȡ��Ҫ����4.5msʱ�䣬��ֵ���ڼ���ӿ�ʼת����*/
    uint8       asyncStep;
    fp32        lastAltiude;

}CeMS5611;
/*
 *CeMS5611��������
 */
typedef struct
{
    CE_STATUS               (*initial)(CeMS5611* ceMS5611, CE_RESOURCE ceI2cMaster);/*!< 
                                                                                 @brief CeMS5611ģ���ʼ��
                                                                                 @param ceMS5611:CeMS5611���Զ���ָ��
                                                                                 @param ceI2cMaster:CeMS5611ģ��ʹ�õ���Դ��*/
                                                                             
    CeMS5611Environment*    (*getEnvironment)(CeMS5611* ceMS5611);          /*!< @brief ��ȡ�Ѿ���У�����¶ȡ���ѹ�����θ߶�
                                                                                 @param ceMS5611:CeMS5611���Զ���ָ��*/

}CeMS5611Op;
/*
 *CeMS5611��������ʵ��
 */
extern const CeMS5611Op ceMS5611Op;

#endif // (__CE_CREELINKS_VERSION__ < __CE_MS5611_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_MS5611_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function xxxxxzzzz
******************************************************************************
#include "Creelinks.h"
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(Uartx);                        //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���

    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����

    };
}
******************************************************************************
*/

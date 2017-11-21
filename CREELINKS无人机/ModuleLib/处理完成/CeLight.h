/**
  ******************************************************************************
  * @file    CeLight.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeLightģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_LIGHT_H__
#define __CE_LIGHT_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_LIGHT_VERSION__ 1                                              /*!< �������ļ��İ汾��*/
#define __CE_LIGHT_NEED_CREELINKS_VERSION__ 1                               /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_LIGHT_NEED_CREELINKS_VERSION__)        /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeLight.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeLight���Զ���
 */
typedef struct
{
    CeAd ceAd;                                                          /*!< ģ��ʹ�õ���Ad����*/
    int16 lightDark;                                                     /*!< �޹⻷���¹�������У׼ֵ*/
    int16 lightHard;                                                     /*!< ǿ�⻷���¹�������У׼ֵ����ʱ���ߴ��������ڱ���״̬*/                                               
}CeLight;
/*
 *CeLight��������
 */
typedef struct
{
    CE_STATUS   (*initial)(CeLight* ceLight, CE_RESOURCE ceAd);         /*!< @brief CeLightģ���ʼ��
                                                                             @param ceLight:CeLight���Զ���ָ��
                                                                             @param ceAd:CeLightģ��ʹ�õ���Դ��*/

    int16       (*getLight)(CeLight* ceLight);                          /*!< @brief ��ȡ�������ȣ���Χ0-100����ʾ������ǿ
                                                                             @param ceLight:CeLight���Զ���ָ��*/

    void        (*calibration)(CeLight* ceLight, int16 lightDark,int16 lightHard);       /*!< 
                                                                             @brief У׼���ߣ������޹����ʵ������ʹ��getLight��ȡһ�ι��ߵ����ȣ�Ȼ�������ֵ���Դ��������������ȼ�������
                                                                             @param ceLight:CeLight���Զ���ָ��
                                                                             @param lightDark:ģ�����޹⻷���е�ʵ�ʲ���ֵ*/


}CeLightOp;
/*
 *CeLight��������ʵ��
 */
extern const CeLightOp ceLightOp;

#endif //(__CE_CREELINKS_VERSION__ < __CE_LIGHT_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_LIGHT_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ����ǰ�����������ֵͨ�����ڷ��͵���λ��
******************************************************************************
#include "Creelinks.h"
#include "CeLight.h"
CeLight myLight;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(R9Uart);                  //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceLightOp.initial(&myLight, R1AGP);         //ʹ��R1AGP��Ad���ܳ�ʼ�����ߴ�����
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û���
        ceDebugOp.printf("The light is :%d\n", ceLightOp.getLight(&myLight));
        ceSystemOp.delayMs(500);
    };
}
******************************************************************************
*/

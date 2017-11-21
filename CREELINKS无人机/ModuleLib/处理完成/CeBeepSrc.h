/**
  ******************************************************************************
  * @file    CeBeepSrc.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeBtnx1ģ�������ͷ�ļ�
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_BEEP_SRC_H__
#define __CE_BEEP_SRC_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_BEEP_SRC_VERSION__ 1                                           /*!< �������ļ��İ汾��*/
#define __CE_BEEP_SRC_NEED_CREELINKS_VERSION__ 1                            /*!< ��ҪCreelinksƽ̨�����Ͱ汾*/
#if (__CE_CREELINKS_VERSION__ < __CE_BEEP_SRC_NEED_CREELINKS_VERSION__)     /*!< ���Creelinksƽ̨��İ汾�Ƿ�����Ҫ��*/
#error "�����ļ�CeBeepSrc.h��Ҫ����1.0���ϰ汾��Creelink�⣬���½www.creelinks.com�������°汾��Creelinks�⡣"
#else
/*
 *CeBeepSrc���Զ���
 */
typedef struct
{
    CeGpio ceGpio;                                                  /*!< CeBeepSrcģ��ʹ�õ�Gpio��Դ��*/
}CeBeepSrc;

/*
 *CeBeepSrc��������
 */
typedef struct
{
    void    (*initial)(CeBeepSrc* ceBeepSrc,CE_RESOURCE ceGpio);    /*!< @brief CeBeepSrcģ���ʼ��
                                                                         @param ceBeepSrc:CeBeepSrc���Զ���ָ��*/

    void    (*setOn)(CeBeepSrc* ceBeepSrc);                         /*!< @brief ʹ��������ʼ����
                                                                         @param ceBeepSrc:CeBeepSrc���Զ���ָ��*/

    void    (*setOff)(CeBeepSrc* ceBeepSrc);                        /*!< @brief ʹ������ֹͣ����
                                                                         @param ceBeepSrc:CeBeepSrc���Զ���ָ��*/
}CeBeepSrcOp;

/*
 *CeBeepSrc��������ʵ��
 */
extern CeBeepSrcOp ceBeepSrcOp;

#endif // (__CE_CREELINKS_VERSION__ < __CE_BEEP_SRC_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_BEEP_SRC_H__

/**
******************************************************************************
* @brief  ʹ�����̼�ʾ������(����ǰ��̨�ǲ���ϵͳ����) 
* @function ʹBeepÿ��500ms����һ��
******************************************************************************
#include "Creelinks.h"
CeBeepSrc myBeepSrc;
int main(void)
{
    ceSystemOp.initial();                       //Creelinks������ʼ��
    ceDebugOp.initial(Uartx);                        //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceBeepSrcOp.initial(&myBeepSrc,RxG);
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���
        //TODO:���ڴ˴������û�����
        ceBeepSrcOp.setOn(&myBeepSrc);          //ʹģ�鷢��
        ceSystemOp.delayMs(500);                //��ʱ500ms
        ceBeepSrcOp.setOff(&myBeepSrc);         //ʹģ�鲻����
        ceSystemOp.delayMs(500);                //��ʱ500ms
    };
}
******************************************************************************
*/

/**
  ******************************************************************************
  * @file    main.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-23
  * @brief   CREELINKSС�������˻�����������ڳ���
  ******************************************************************************
  * @attention
  *
  * 1)ע�⣺������ֱ���Ķ�Դ���룬���ȼ�Ҫ����CREELINKSС�������˻�������ṹ����ܣ�
  *   ���ص�ַ��http://www.creelinks.com/uav/uav.html
  * 2)ע�⣺�й�CREELINKS����ӿڵĶ��塢ʹ�÷�������ֲ����������ʹ�������������ϡ�
  *   �ٷ���վ��http://www.creelinks.com
  * 3)ע�⣺�ɼ���CREELINKSС���ύ��Ⱥ623083844
  *
  * 1)����CREELINKSƽ̨V1.0
  * 2)֧��WIFI��������2.4G��Ƶ����ͨѶ��ʽ����ǰ�汾(V1.0)�ݲ�֧������ͨѶ
  * 3)����ʱ�����Ұ�ť��ֱ��������..��..������ϵͳ��������������ʽ
  * 4)����ʱ������ť��ֱ��������..һ����ϵͳ����WIFI������ʽ
  * 5)����ʱ�����κΰ�ť��ϵͳĬ�Ͻ���2.4G��Ƶ������ʽ
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "Creelinks.h"                              //CREELINKSƽ̨ͷ�ļ�
#include "CePID.h"                                  //PID��������
#include "CeFilter.h"                               //�������˲�����Ԫ������̬����
#include "CeMDCtl.h"                                //����������ģ������
#include "CeSysCtl.h"                               //ϵͳ���Ʋ���ȫ��                         
#include "CeStatus.h"                               //���˻�״̬����ͷ�ļ�

CeStatus         ceNowStatus;                       //���嵱ǰ�����˻���̬
CeStatus         ceHopeStatus;                      //�������������˻���̬ 

CeMDDrivePower*  drivePower;                        //������������ǿ�Ƚṹ��ָ��
fp32             dtS = 0;                           //������whileִ�����ڣ���λS

/**
  * @brief  CREELINKSƽ̨����ں���(�㱼)
  * @return 0
  */
int main(void)
{
    ceSystemOp.initial();                           //Creelinks������ʼ��
    ceDebugOp.initial(Uart1);                       //ͨ��Uart�������Debug��Ϣ����λ��
    //TODO:���ڴ˴�����ģ���ʼ���Ȳ���
    ceMDCtlOp.initial();                            //��ʼ���ĸ����
    ceSysCtlOp.initial();                           //�ĸ�LED��ʼ��
    ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_CFG);  //LED����ʾΪ����״̬
    ceStatusOp.initial();                           //��ʼ�����˻�״̬��������
    ceFilterOp.initial();                           //���˻���̬�������˲����ƶ������֣�һ�����ס���Ԫ���������� 
    cePIDOp.initial();                              //���˻�����PID���ƶ���
    ceSysCtlOp.setAlarm(1000,0,1);                  //����������1S�죬��ʾ�ѳ�ʼ����ɣ��������
    ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_NORMAL);  //LED����ʾΪ�������״̬
    while (1)
    {
        ceTaskOp.mainTask();                        //Creelinks������ѭ�������뱣֤�˺����ܹ������ڵ���        
        //TODO:���ڴ˴������û�����   
        ceStatusOp.getNowStatus(&ceNowStatus);      //��ȡ��ǰ���˻���״̬��Ϣ�����/���ٶȴ������ȵ�

        ceFilterOp.filter(&ceNowStatus,dtS);        //�Ե�ǰ���ٶȡ���ǰ���ٶȽ�����̬�������˲����Ի�ȡ���˻���̬�����ݣ�ע���Ὣ���������µ�����ָ�������ָ���ݡ� 

        ceStatusOp.getHopeStatus(&ceNowStatus, &ceHopeStatus);     //��ȡ���������˻�״̬��Ϣ

        drivePower = cePIDOp.calculate(&ceNowStatus, &ceHopeStatus,dtS);//���ݵ�ǰ���ٶȼ����ٶȡ���̬�ǡ�����������̬���д���PID���㣬������ĸ����������ǿ��  

        ceMDCtlOp.setDriverPower(drivePower);       //���õ��������ǿ��
    
        dtS = ceSysCtlOp.getSysRunCycleS();         //�������ִ������ʱ��   
    };
}

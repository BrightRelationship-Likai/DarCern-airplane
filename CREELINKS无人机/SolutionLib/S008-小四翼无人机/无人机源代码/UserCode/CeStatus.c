/**
  ******************************************************************************
  * @file    CeStatus.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeStatusģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeStatus.h"
#include "CePackage.h"
#include "CeSysCtl.h"
#include "CeParCtl.h"                //���ղ����뷢�Ͳ����������
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_PACKAGE_BTN_LEFT         0x00000040          /*!< ��ӦCePackage�ṹ���е�status����λ����������ҡ�˰�ť״̬*/
#define CE_PACKAGE_BTN_RIGHT        0x00000080          /*!< ��ӦCePackage�ṹ���е�status����λ��������ҡ���Ұ�ť״̬*/
#define CE_PACKAGE_BTN_S2A          0x00000100          /*!< ��ӦCePackage�ṹ���е�status����λ����ť����ťS2A״̬*/
#define CE_PACKAGE_BTN_S2B          0x00000200          /*!< ��ӦCePackage�ṹ���е�status����λ����ť����ťS2B״̬*/
#define CE_PACKAGE_BTN_S2C          0x00000400          /*!< ��ӦCePackage�ṹ���е�status����λ����ť����ťS2C״̬*/
#define CE_PACKAGE_BTN_S2D          0x00000800          /*!< ��ӦCePackage�ṹ���е�status����λ����ť����ťS2D״̬*/

#define CE_PACKAGE_TYPE_STATION     0x00001000          /*!< ��ӦCePackage�ṹ���е�status����λ�����˻����ܿط�ʽ������վ��*/
#define CE_PACKAGE_TYPE_CTL         0x00002000          /*!< ��ӦCePackage�ṹ���е�status����λ�����˻����ܿط�ʽ��ң����*/
#define CE_PACKAGE_TYPE_PHONE       0x00004000          /*!< ��ӦCePackage�ṹ���е�status����λ�����˻����ܿط�ʽ���ֻ�*/

#define CE_UAV_FLY_MODULE_ERROR     0x00                /*!< ���˻���ǰ����״̬������*/     
#define CE_UAV_FLY_MODULE_NORMAL    0x01                /*!< ���˻���ǰ����״̬������*/
#define CE_UAV_FLY_MODULE_FREE_ACCE 0x02                /*!< ���˻���ǰ����״̬���ֶ�����*/
#define CE_UAV_FLY_MODULE_FIX_HIGHT 0x03                /*!< ���˻���ǰ����״̬���Զ����ţ����ߣ�*/

uint8        ceUavFlyModule=0x01;                                                          /*!< ���˻���ǰ����״̬�����ݴ�ֵ��ȷ��CeHopeStatus�еĸ�����ֵ*/     
extern CePackageSend cePackageSend;                                          /*!< */    
extern CePackageRecv cePackageRecv;                                          /*!< */    
     
/**
  * @brief  ϵͳ���ƺ�����ʼ��
  */
CE_STATUS   ceStatus_initial(void)
{
      ceParCtlOp.initial();                           //��ʼ�����ݴ������,ÿ20ms����һ�����ݷ��͡�ע��ֱ����������ƶ˽���ͨѶ�����ŷ���
        ceSensorOp.initial();                           //��ʼ�����д�����
    return CE_STATUS_SUCCESS;        
}

 /*!< @brief  ��ȡ��ǰ���˻��ķ���״̬������Ϣ
                                                             @param  ���в�����Ϣ�����ַ*/
void  ceStatus_getNowStatus(CeStatus* ceNowStatus)  
{
    ceSensorOp.getAcc(&(ceNowStatus->ceAcc));
    ceSensorOp.getGyr(&(ceNowStatus->ceGyr));
    ceSensorOp.getMag(&(ceNowStatus->ceMag));
    ceSensorOp.getTem(&(ceNowStatus->ceTem));
    ceSensorOp.getGps(&(ceNowStatus->ceGps));
    ceSensorOp.getAlt(&(ceNowStatus->ceAlt));   
}

/**
  * @brief  ��ȡ���յ��ķ���״̬��Ϣ
  * @param  ceHopeStatus:����״̬��Ϣ�����ַ
  * @return ��
  */
void    ceStatus_getHopeStatus(CeStatus* ceNowStatus, CeStatus* ceHopeStatus)
{
    ceParCtlOp.recvDataHook();                  //�������ݽӿں���
    //��������Ƿ�����
    if(ceSysCtlOp.checkConnectStatus() != CE_STATUS_SUCCESS)//��������˻�ʧ������̬���У�������BEEP������ʾ��
    {
        ceHopeStatus->pitch = 0;
        ceHopeStatus->roll = 0;
        ceHopeStatus->yaw = 0;
        ceHopeStatus->accelerator = (ceNowStatus->accelerator - (ceNowStatus->accelerator>10? 10:0));
        if(ceHopeStatus->accelerator<=0) ceHopeStatus->accelerator = 0;
        if(ceHopeStatus->ceAlt.altitude != -9999)   ceHopeStatus->ceAlt.altitude  -=  0.1f;
        ceSysCtlOp.setAlarm(30,0,1);
        ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_CFG);//LED��״̬Ϊ����״̬
    }else 
    {
        if(ceUavFlyModule == CE_UAV_FLY_MODULE_ERROR)        //����״̬��ֱ��ֹͣ���˻������븴λ���˻��ſ���ֱ����������״̬
        {
            ceHopeStatus->pitch = 0;
            ceHopeStatus->roll = 0;
            ceHopeStatus->yaw = 0;
            ceHopeStatus->accelerator =0;
            ceHopeStatus->ceAlt.altitude = -9999; 

            ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_ERROR);
            ceSysCtlOp.setAlarm(10,0,1);
        }else if(ceUavFlyModule == CE_UAV_FLY_MODULE_NORMAL)//�����ȴ����״̬
        {
            ceHopeStatus->pitch = 0;
            ceHopeStatus->roll = 0;
            ceHopeStatus->yaw = 0;
            ceHopeStatus->accelerator =0;
            ceHopeStatus->ceAlt.altitude = -9999; 

            if(ceSysCtlOp.getLedMode() == CE_LED_CTL_MODE_IN_CFG) ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_NORMAL);//LED��״̬Ϊ����״̬ 
            if((cePackageRecv.status & CE_PACKAGE_BTN_RIGHT) == CE_PACKAGE_BTN_RIGHT)//����������ȴ����ģʽ�£�������ң�����Ҽ�
            {
                if(cePackageRecv.leftY <= -100)//�����ʱ����ҡ��Y��ֵС��-100������������ͣ����������˻�Ϊ�ֶ�����״̬; ��������Ϊ�Զ����ţ���ѹ�ƶ��߷���״̬��
                {
                    ceUavFlyModule = CE_UAV_FLY_MODULE_FREE_ACCE;
                }
                else
                {
                    ceUavFlyModule = CE_UAV_FLY_MODULE_FIX_HIGHT;
                    ceHopeStatus->ceAlt.altitude  = (ceNowStatus->ceAlt.altitude + 1.0f);//����ǰ���˻������߶�����Ϊ�������Լ1.0m��
                }
            }
        }else if(ceUavFlyModule == CE_UAV_FLY_MODULE_FREE_ACCE)//�ֶ��������ɷ���״̬
        {
            if((cePackageRecv.status & CE_PACKAGE_BTN_S2B) == CE_PACKAGE_BTN_S2B) ceUavFlyModule = CE_UAV_FLY_MODULE_ERROR;//�����˼�ͣ��ť,ֱ�ӽ������״̬
            if((cePackageRecv.status & CE_PACKAGE_BTN_S2D) == CE_PACKAGE_BTN_S2D) ceUavFlyModule = CE_UAV_FLY_MODULE_NORMAL;//������ֹͣ���а�ť,ֱ�ӽ��������ȴ�����״̬

            ceHopeStatus->yaw = ((ceMathOp.abs(cePackageRecv.leftX) > 100) ? (-(fp32)(cePackageRecv.leftX)/25):0.0f);        //����ƫ����������300����������ֹ������ʱƫ�������·��в��ȶ�
            ceHopeStatus->pitch = ((ceMathOp.abs(cePackageRecv.rightY) > 150) ? ((fp32)(cePackageRecv.rightY) /166) : 0.0f);  //���ƽǶ���-6~+6��֮��,������Pitch�ǵ��������Է�ֹҡ�����µ�Ʈ��
            ceHopeStatus->roll = ((ceMathOp.abs(cePackageRecv.rightX) > 150) ? (-(fp32)(cePackageRecv.rightX) /166) : 0.0f);  //���ƽǶ���-6~+6��֮�� ,������Roll�ǵ��������Է�ֹҡ�����µ�Ʈ�� 

            ceHopeStatus->accelerator = cePackageRecv.leftY/2 + 500;     //��-1000~+1000��ת��Ϊ0~1000���Ա�֤����������0~1000�ķ�Χ��        
            ceHopeStatus->ceAlt.altitude = -9999;   //֪ͨPID����������ʱΪ�ֶ����ŷ���״̬����û�������ĺ���ֵ.
        }else if(ceUavFlyModule == CE_UAV_FLY_MODULE_FIX_HIGHT)//�Զ����ţ����߷���״̬
        {
            if((cePackageRecv.status & CE_PACKAGE_BTN_S2B) == CE_PACKAGE_BTN_S2B) ceUavFlyModule = CE_UAV_FLY_MODULE_ERROR;//�����˼�ͣ��ť,ֱ�ӽ������״̬
            if((cePackageRecv.status & CE_PACKAGE_BTN_S2D) == CE_PACKAGE_BTN_S2D) ceUavFlyModule = CE_UAV_FLY_MODULE_NORMAL;//������ֹͣ���а�ť,ֱ�ӽ��������ȴ�����״̬

            ceHopeStatus->yaw = ((ceMathOp.abs(cePackageRecv.leftX) > 300) ? (-(fp32)(cePackageRecv.leftX)/50):0.0f);        //����ƫ����������300����������ֹ������ʱƫ�������·��в��ȶ�
            ceHopeStatus->pitch = ((ceMathOp.abs(cePackageRecv.rightY) > 150) ? ((fp32)(cePackageRecv.rightY) /166) : 0.0f);  //���ƽǶ���-6~+6��֮��,������Pitch�ǵ��������Է�ֹҡ�����µ�Ʈ��
            ceHopeStatus->roll = ((ceMathOp.abs(cePackageRecv.rightX) > 150) ? (-(fp32)(cePackageRecv.rightX) /166) : 0.0f);  //���ƽǶ���-6~+6��֮�� ,������Roll�ǵ��������Է�ֹҡ�����µ�Ʈ�� 

            //ceHopeStatus->accelerator = cePackageRecv.leftY/2 + 500;//�����Ѿ���PID�����������θ߶��Զ����㣬�����ﲻ��Ҫ��������������
            ceHopeStatus->ceAlt.altitude += (ceMathOp.abs(cePackageRecv.leftY) > 200)?((fp32)(cePackageRecv.leftY)/10000):0.0f;   //��������������ҡ��λ���м�ʱ�ľ�������߶����ӻ��С.
        }
    }
    ceParCtlOp.sendDataHook();                  //�������ݽӿں���

    //������������̬������LED����Ƶ���˸״̬
    if(ceHopeStatus->pitch >3)           ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_GOTO_FRONT);
    else if(ceHopeStatus->pitch <(-3))   ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_GOTO_BACK);
    else if(ceHopeStatus->roll >3)       ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_GOTO_LEFT);
    else if(ceHopeStatus->roll <(-3))    ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_GOTO_RIGHT);
    else if(ceHopeStatus->yaw >3)        ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_FLASH_CYCLE_N);
    else if(ceHopeStatus->yaw <(-3))     ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_FLASH_CYCLE_P);
    else                                ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_NORMAL);
}

/**
  * @brief  ��ʼ��CeStatusģ���������
  */
const CeStatusOp ceStatusOp = {ceStatus_initial,ceStatus_getNowStatus,ceStatus_getHopeStatus};

#ifdef __cplusplus
 }
#endif //__cplusplus

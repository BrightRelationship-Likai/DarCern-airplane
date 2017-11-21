/**
  ******************************************************************************
  * @file    CeParCtl.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������CeParCtlģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)��
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeParCtl.h"
#include "CePID.h"
#include "CeFilter.h"
#include "CeSensor.h"
#include "CeSysCtl.h"
#include "CePackage.h"
#include "CeTMCtl.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_PACKAGE_FILTER_IN_DEBUG      0x00000010  /*!< ��ӦCePackage�ṹ���е�status����λ���Ƿ����˲�����������ģʽ��*/
#define CE_PACKAGE_PID_IN_DEBUG         0x00000020  /*!< ��ӦCePackage�ṹ���е�status����λ���Ƿ���PID��������֮��*/

extern CePackageSend    cePackageSend;              /*!< CePackage.c�ж���ķ��Ͳ����ṹ�壬�ڲ����������跢�͸����ƶ˵Ĳ���*/
extern CePackageRecv    cePackageRecv;              /*!< CePackage.c�ж���Ľ��ղ����ṹ�壬�ڲ��������дӿ��ƶ˽��յ��Ĳ���*/
extern CePID            cePID;                      /*!< CePID.c�ж���Ľṹ�壬���ڱ���PID��������еĸ���ϵ������*/
extern CeFilter         ceFilter;                   /*!< CeFilter.c�ж���Ľṹ�壬���ڱ�����̬��������У������˲�����ϵ������*/

extern CeStatus         ceNowStatus;                /*!< main.c�ж���Ľṹ�壬���浱ǰ�����˻���̬*/  
extern CeStatus         ceHopeStatus;               /*!< main.c�ж���Ľṹ�壬�������������˻���̬*/  

extern CeMDDrivePower*  drivePower;                 /*!< ������������ǿ�Ƚṹ��ָ��*/
/**
  * @brief  TMU���ݴ������ģ��������ݺ󣬵��õĻص�����
  * @param  dataBuf:���յ����ݵĻ����ַ
  * @param  dataCount:���յ����ݵĳ���
  * @return ��
  */
void ceParCtl_recvDataCallBack(uint8* dataBuf, uint16 dataCount) 
{
    if(CE_STATUS_SUCCESS != cePackageOp.dealRecv(dataBuf,dataCount))//���ݽ��㲻��ȷ����ֱ�ӷ���
        return;
}


/**
  * @brief  ϵͳ���ƺ�����ʼ��
  */
void ceParCtl_initial(void)
{
    cePackageOp.initial();        //��ʼ�����ݰ��������
    ceTMCtlOp.setRecvCallBack(ceParCtl_recvDataCallBack);

    if(ceSysCtlOp.getBtnSta(0) == 0x01)             //�򿪿���ʱ��������ť�������WIFIͨѶģʽ
    {
        ceSysCtlOp.setAlarm(100,0,1);   
        ceTMCtlOp.initial(0); 											//��ʼ�����ݴ������,ÿ20ms����һ�����ݷ��͡�ע��ֱ����������ƶ˽���ͨѶ�����ŷ���
    }else                                           //������������NRF24L01ͨѶ��ʽ            
    {
        ceSysCtlOp.setAlarm(100,200,3); 
        ceTMCtlOp.initial(1);  
        ceSystemOp.delayMs(3000);                   //��ʱһ���ʱ�䣬��ȷ�����˻����ڵ��澲ֹ״̬����ֹMPU6050��ʼ��������ٶ����ʱ�������
    }     
}


void ceParCtl_beforeFilterHook(void)
{
    //TODO�����ڵ���ģʽ�£������˲�������
    if((cePackageRecv.status & CE_PACKAGE_FILTER_IN_DEBUG) != 0)//������ڲ�������״̬�������IMU���˲����Ĳ���
    {
        ceFilter.ceFilterYijiePitch.K1 = (fp32)(cePackageRecv.yijieK1) / 1000;
        ceFilter.ceFilterYijiePitch.K1 = (fp32)(cePackageRecv.yijieK1) / 1000;

        ceFilter.ceFilterErjiePitch.K2 = (fp32)(cePackageRecv.erjieK2) / 1000;
        ceFilter.ceFilterErjieRoll.K2 = (fp32)(cePackageRecv.erjieK2) / 1000;
 
        ceFilter.ceFilterIMU.kp = (fp32)(cePackageRecv.imuKp) / 1000;
        ceFilter.ceFilterIMU.ki = (fp32)(cePackageRecv.imuKi) / 1000;

        ceFilter.ceFilterKalmanPitch.R_angle = (fp32)(cePackageRecv.filterR_angle) / 1000;
        ceFilter.ceFilterKalmanPitch.Q_angle = (fp32)(cePackageRecv.filterQ_angle) / 1000;
        ceFilter.ceFilterKalmanPitch.Q_gyro = (fp32)(cePackageRecv.filterQ_gyro) / 1000;
            
        ceFilter.ceFilterKalmanRoll.R_angle = (fp32)(cePackageRecv.filterR_angle) / 1000;
        ceFilter.ceFilterKalmanRoll.Q_angle = (fp32)(cePackageRecv.filterQ_angle)/ 1000;
        ceFilter.ceFilterKalmanRoll.Q_gyro = (fp32)(cePackageRecv.filterQ_gyro) / 1000;

        ceFilter.ceStatusZero.pitch = (fp32)(cePackageRecv.zeroPitch) / 1000;
        ceFilter.ceStatusZero.roll = (fp32)(cePackageRecv.zeroRoll) / 1000;
        ceFilter.ceStatusZero.yaw = (fp32)(cePackageRecv.zeroYaw) / 1000;
    }
    //TODO������ֱ�ӻ�ȡ����δ�����˲������Ĵ���������
    cePackageSend.accX = (int32)(ceNowStatus.ceAcc.x*1000);
    cePackageSend.accY = (int32)(ceNowStatus.ceAcc.y*1000);
    cePackageSend.accZ = (int32)(ceNowStatus.ceAcc.z*1000);

    cePackageSend.gyrX = (int32)(ceNowStatus.ceGyr.x*1000);
    cePackageSend.gyrY = (int32)(ceNowStatus.ceGyr.y*1000);
    cePackageSend.gyrZ = (int32)(ceNowStatus.ceGyr.z*1000);
}


void ceParCtl_afterFilterHook(void)
{
    //TODO����̬������ɺ󣬱����˲������������ݣ������͸����ƶ�
    cePackageSend.accXByFilter = (int32)(ceNowStatus.ceAcc.x*1000);
    cePackageSend.accYByFilter = (int32)(ceNowStatus.ceAcc.y*1000);
    cePackageSend.accZByFilter = (int32)(ceNowStatus.ceAcc.z*1000);

    cePackageSend.gyrXByFilter = (int32)(ceNowStatus.ceGyr.x*1000);
    cePackageSend.gyrYByFilter = (int32)(ceNowStatus.ceGyr.y*1000);
    cePackageSend.gyrZByFilter = (int32)(ceNowStatus.ceGyr.z*1000);

    cePackageSend.pitchByFilter = (int32)(ceNowStatus.pitch*1000);
    cePackageSend.rollByFilter = (int32)(ceNowStatus.roll*1000);
    cePackageSend.yawByFilter = (int32)(ceNowStatus.yaw*1000);
	
    cePackageSend.pitchByAcc = (int32)(ceFilter.pitchByAcc*1000);
		cePackageSend.rollByAcc = (int32)(ceFilter.rollByAcc*1000);
}


void ceParCtl_beforePIDHook(void)
{
    //TODO���������PID����״̬����PID����ǰ������PID����
    if ((cePackageRecv.status & CE_PACKAGE_PID_IN_DEBUG) != 0)//�������PID����״̬������µ�ǰ��PID����
    {
        cePID.outPitchP = (fp32)(cePackageRecv.outPitchP) / 1000;//���͵����ݾ����Ŵ�1000����������Ҫ�ٳ���1000���Ŵ�ԭ���Ǳ��ڽ�fp32������ת��ΪInt16���������ݴ���
        cePID.outPitchI = (fp32)(cePackageRecv.outPitchI) / 1000;
        cePID.outPitchD = (fp32)(cePackageRecv.outPitchD) / 1000;
        cePID.inPitchP = (fp32)(cePackageRecv.inPitchP) / 1000;
        cePID.inPitchI = (fp32)(cePackageRecv.inPitchI) / 1000;
        cePID.inPitchD = (fp32)(cePackageRecv.inPitchD) / 1000;

        cePID.outRollP = (fp32)(cePackageRecv.outRollP) / 1000;
        cePID.outRollI = (fp32)(cePackageRecv.outRollI) / 1000;
        cePID.outRollD = (fp32)(cePackageRecv.outRollD) / 1000;
        cePID.inRollP = (fp32)(cePackageRecv.inRollP) / 1000;
        cePID.inRollI = (fp32)(cePackageRecv.inRollI) / 1000;
        cePID.inRollD = (fp32)(cePackageRecv.inRollD) / 1000;

        cePID.outYawP = (fp32)(cePackageRecv.outYawP) / 1000;
        cePID.outYawI = (fp32)(cePackageRecv.outYawI) / 1000;
        cePID.outYawD = (fp32)(cePackageRecv.outYawD) / 1000;
        cePID.inYawP = (fp32)(cePackageRecv.inYawP) / 1000;
        cePID.inYawI = (fp32)(cePackageRecv.inYawI) / 1000;
        cePID.inYawD = (fp32)(cePackageRecv.inYawD) / 1000;

        cePID.altBase = (fp32)(cePackageRecv.altBase);
        cePID.altKp = (fp32)(cePackageRecv.altKp) / 1000;
        cePID.altKi = (fp32)(cePackageRecv.altKi) / 1000;
        cePID.altKd = (fp32)(cePackageRecv.altKd) / 1000;
    }
}


void ceParCtl_afterPIDHook(void)
{
    //TODO�����澭��PID�����ĵ������ǿ�ȣ��뵱ǰ����ֵ
    cePackageSend.accelerator = (int32)(ceNowStatus.accelerator);
    cePackageSend.driverPower0 = (int32)(drivePower->motorDrivePower0);
    cePackageSend.driverPower1 = (int32)(drivePower->motorDrivePower1);
    cePackageSend.driverPower2 = (int32)(drivePower->motorDrivePower2);
    cePackageSend.driverPower3 = (int32)(drivePower->motorDrivePower3);
}


void ceParCtl_recvDataHook(void)
{
    //TODO����ӽ������ݲ���������CREELINKSƽ̨�������ݲ��ûص���ʽ���ʴ˺���Ϊ�ա�
}

void ceParCtl_sendDataHook(void)
{
    //TODO�����������ϲ����͸����ƶ�
    if(ceTMCtlOp.getSendIntervalMs() < 35)  //�������η������ݵ�ʱ����
        return ;

    cePackageSend.batVoltage =      (int32)(ceSysCtlOp.getBatVol()*1000);   //���ϵ�ǰ���˻���ص�ѹֵ������ͳ�Ƶ�ص���,cePackageSend�е�������������CePID��CeFilter�и���
    cePackageSend.pressure =        (int32)(ceNowStatus.ceAlt.pressure);
    cePackageSend.altitude =        (int32)(ceNowStatus.ceAlt.altitude*1000);		
    cePackageSend.temperature =     (int32)(ceNowStatus.ceTem.temperature*1000);

    cePackageSend.accelerator =     (int32)(ceNowStatus.accelerator);

    ceTMCtlOp.sendData(cePackageOp.dealSend(),CE_PACKAGE_SEND_BUF_SIZE);    //��cePackageSend�ṹ�������˻�״̬���ݴ���������͸�����վ��ң����
}

/**
  * @brief  ��ʼ��CeParCtlģ���������
  */
const CeParCtlOp ceParCtlOp = {ceParCtl_initial,ceParCtl_beforeFilterHook,ceParCtl_afterFilterHook,ceParCtl_beforePIDHook,ceParCtl_afterPIDHook,ceParCtl_recvDataHook,ceParCtl_sendDataHook};

#ifdef __cplusplus
 }
#endif //__cplusplus

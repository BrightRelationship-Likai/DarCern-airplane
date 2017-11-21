/**
  ******************************************************************************
  * @file    CeParCtl.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeParCtl模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
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

#define CE_PACKAGE_FILTER_IN_DEBUG      0x00000010  /*!< 对应CePackage结构体中的status单个位，是否处于滤波器参数调整模式下*/
#define CE_PACKAGE_PID_IN_DEBUG         0x00000020  /*!< 对应CePackage结构体中的status单个位，是否处于PID参数调整之下*/

extern CePackageSend    cePackageSend;              /*!< CePackage.c中定义的发送参数结构体，内部保存所有需发送给控制端的参数*/
extern CePackageRecv    cePackageRecv;              /*!< CePackage.c中定义的接收参数结构体，内部保存所有从控制端接收到的参数*/
extern CePID            cePID;                      /*!< CePID.c中定义的结构体，用于保存PID运算过程中的各项系数参数*/
extern CeFilter         ceFilter;                   /*!< CeFilter.c中定义的结构体，用于保存姿态解算过程中，各种滤波器的系数参数*/

extern CeStatus         ceNowStatus;                /*!< main.c中定义的结构体，保存当前的无人机姿态*/  
extern CeStatus         ceHopeStatus;               /*!< main.c中定义的结构体，保存期望的无人机姿态*/  

extern CeMDDrivePower*  drivePower;                 /*!< 定义电机的驱动强度结构体指针*/
/**
  * @brief  TMU数据传输管理模块接收数据后，调用的回调函数
  * @param  dataBuf:接收到数据的缓存地址
  * @param  dataCount:接收到数据的长度
  * @return 无
  */
void ceParCtl_recvDataCallBack(uint8* dataBuf, uint16 dataCount) 
{
    if(CE_STATUS_SUCCESS != cePackageOp.dealRecv(dataBuf,dataCount))//数据解算不正确，则直接返回
        return;
}


/**
  * @brief  系统控制函数初始化
  */
void ceParCtl_initial(void)
{
    cePackageOp.initial();        //初始化数据包解译对象
    ceTMCtlOp.setRecvCallBack(ceParCtl_recvDataCallBack);

    if(ceSysCtlOp.getBtnSta(0) == 0x01)             //打开开关时，按下左按钮，则进入WIFI通讯模式
    {
        ceSysCtlOp.setAlarm(100,0,1);   
        ceTMCtlOp.initial(0); 											//初始化数据传输对象,每20ms进行一次数据发送。注：直接正常与控制端建立通讯后函数才返回
    }else                                           //其它情况则进入NRF24L01通讯方式            
    {
        ceSysCtlOp.setAlarm(100,200,3); 
        ceTMCtlOp.initial(1);  
        ceSystemOp.delayMs(3000);                   //延时一大段时间，以确保无人机处于地面静止状态，防止MPU6050初始化计算角速度零点时出现误差
    }     
}


void ceParCtl_beforeFilterHook(void)
{
    //TODO：处于调试模式下，更新滤波器参数
    if((cePackageRecv.status & CE_PACKAGE_FILTER_IN_DEBUG) != 0)//如果处于参数调节状态，则更新IMU与滤波器的参数
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
    //TODO：保存直接获取，还未进行滤波操作的传感器数据
    cePackageSend.accX = (int32)(ceNowStatus.ceAcc.x*1000);
    cePackageSend.accY = (int32)(ceNowStatus.ceAcc.y*1000);
    cePackageSend.accZ = (int32)(ceNowStatus.ceAcc.z*1000);

    cePackageSend.gyrX = (int32)(ceNowStatus.ceGyr.x*1000);
    cePackageSend.gyrY = (int32)(ceNowStatus.ceGyr.y*1000);
    cePackageSend.gyrZ = (int32)(ceNowStatus.ceGyr.z*1000);
}


void ceParCtl_afterFilterHook(void)
{
    //TODO：姿态解算完成后，保存滤波及解算后的数据，并发送给控制端
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
    //TODO：如果处于PID调试状态，在PID计算前，更新PID参数
    if ((cePackageRecv.status & CE_PACKAGE_PID_IN_DEBUG) != 0)//如果处于PID调节状态，则更新当前各PID参数
    {
        cePID.outPitchP = (fp32)(cePackageRecv.outPitchP) / 1000;//发送的数据经过放大1000倍，故这里要再除以1000。放大原因是便于将fp32型数据转换为Int16并进行数据传输
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
    //TODO：保存经过PID计算后的电机驱动强度，与当前油门值
    cePackageSend.accelerator = (int32)(ceNowStatus.accelerator);
    cePackageSend.driverPower0 = (int32)(drivePower->motorDrivePower0);
    cePackageSend.driverPower1 = (int32)(drivePower->motorDrivePower1);
    cePackageSend.driverPower2 = (int32)(drivePower->motorDrivePower2);
    cePackageSend.driverPower3 = (int32)(drivePower->motorDrivePower3);
}


void ceParCtl_recvDataHook(void)
{
    //TODO：添加接收数据操作，由于CREELINKS平台接收数据采用回调方式，故此函数为空。
}

void ceParCtl_sendDataHook(void)
{
    //TODO：将数据整合并发送给控制端
    if(ceTMCtlOp.getSendIntervalMs() < 35)  //限制两次发送数据的时间间隔
        return ;

    cePackageSend.batVoltage =      (int32)(ceSysCtlOp.getBatVol()*1000);   //整合当前无人机电池电压值，用于统计电池电量,cePackageSend中的其它参数，在CePID与CeFilter中更新
    cePackageSend.pressure =        (int32)(ceNowStatus.ceAlt.pressure);
    cePackageSend.altitude =        (int32)(ceNowStatus.ceAlt.altitude*1000);		
    cePackageSend.temperature =     (int32)(ceNowStatus.ceTem.temperature*1000);

    cePackageSend.accelerator =     (int32)(ceNowStatus.accelerator);

    ceTMCtlOp.sendData(cePackageOp.dealSend(),CE_PACKAGE_SEND_BUF_SIZE);    //将cePackageSend结构体中无人机状态数据打包，并发送给地面站或遥控器
}

/**
  * @brief  初始化CeParCtl模块操作对象
  */
const CeParCtlOp ceParCtlOp = {ceParCtl_initial,ceParCtl_beforeFilterHook,ceParCtl_afterFilterHook,ceParCtl_beforePIDHook,ceParCtl_afterPIDHook,ceParCtl_recvDataHook,ceParCtl_sendDataHook};

#ifdef __cplusplus
 }
#endif //__cplusplus

/**
  ******************************************************************************
  * @file    CeStatus.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于CeStatus模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)无
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeStatus.h"
#include "CePackage.h"
#include "CeSysCtl.h"
#include "CeParCtl.h"                //接收参数与发送参数管理操作
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define CE_PACKAGE_BTN_LEFT         0x00000040          /*!< 对应CePackage结构体中的status单个位，控制器左摇杆按钮状态*/
#define CE_PACKAGE_BTN_RIGHT        0x00000080          /*!< 对应CePackage结构体中的status单个位，控制器摇杆右按钮状态*/
#define CE_PACKAGE_BTN_S2A          0x00000100          /*!< 对应CePackage结构体中的status单个位，按钮器按钮S2A状态*/
#define CE_PACKAGE_BTN_S2B          0x00000200          /*!< 对应CePackage结构体中的status单个位，按钮器按钮S2B状态*/
#define CE_PACKAGE_BTN_S2C          0x00000400          /*!< 对应CePackage结构体中的status单个位，按钮器按钮S2C状态*/
#define CE_PACKAGE_BTN_S2D          0x00000800          /*!< 对应CePackage结构体中的status单个位，按钮器按钮S2D状态*/

#define CE_PACKAGE_TYPE_STATION     0x00001000          /*!< 对应CePackage结构体中的status单个位，无人机的受控方式：地面站点*/
#define CE_PACKAGE_TYPE_CTL         0x00002000          /*!< 对应CePackage结构体中的status单个位，无人机的受控方式：遥控器*/
#define CE_PACKAGE_TYPE_PHONE       0x00004000          /*!< 对应CePackage结构体中的status单个位，无人机的受控方式：手机*/

#define CE_UAV_FLY_MODULE_ERROR     0x00                /*!< 无人机当前工作状态，错误*/     
#define CE_UAV_FLY_MODULE_NORMAL    0x01                /*!< 无人机当前工作状态，正常*/
#define CE_UAV_FLY_MODULE_FREE_ACCE 0x02                /*!< 无人机当前工作状态，手动油门*/
#define CE_UAV_FLY_MODULE_FIX_HIGHT 0x03                /*!< 无人机当前工作状态，自动油门（定高）*/

uint8        ceUavFlyModule=0x01;                                                          /*!< 无人机当前工作状态，根据此值来确定CeHopeStatus中的各参数值*/     
extern CePackageSend cePackageSend;                                          /*!< */    
extern CePackageRecv cePackageRecv;                                          /*!< */    
     
/**
  * @brief  系统控制函数初始化
  */
CE_STATUS   ceStatus_initial(void)
{
      ceParCtlOp.initial();                           //初始化数据传输对象,每20ms进行一次数据发送。注：直接正常与控制端建立通讯后函数才返回
        ceSensorOp.initial();                           //初始化所有传感器
    return CE_STATUS_SUCCESS;        
}

 /*!< @brief  获取当前无人机的飞行状态基本信息
                                                             @param  飞行参数信息保存地址*/
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
  * @brief  获取接收到的飞行状态信息
  * @param  ceHopeStatus:飞行状态信息保存地址
  * @return 无
  */
void    ceStatus_getHopeStatus(CeStatus* ceNowStatus, CeStatus* ceHopeStatus)
{
    ceParCtlOp.recvDataHook();                  //接收数据接口函数
    //检测连接是否正常
    if(ceSysCtlOp.checkConnectStatus() != CE_STATUS_SUCCESS)//如果与无人机失联，姿态归中，并发出BEEP报警提示音
    {
        ceHopeStatus->pitch = 0;
        ceHopeStatus->roll = 0;
        ceHopeStatus->yaw = 0;
        ceHopeStatus->accelerator = (ceNowStatus->accelerator - (ceNowStatus->accelerator>10? 10:0));
        if(ceHopeStatus->accelerator<=0) ceHopeStatus->accelerator = 0;
        if(ceHopeStatus->ceAlt.altitude != -9999)   ceHopeStatus->ceAlt.altitude  -=  0.1f;
        ceSysCtlOp.setAlarm(30,0,1);
        ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_CFG);//LED灯状态为配置状态
    }else 
    {
        if(ceUavFlyModule == CE_UAV_FLY_MODULE_ERROR)        //错误状态，直接停止无人机，必须复位无人机才可以直入正常工作状态
        {
            ceHopeStatus->pitch = 0;
            ceHopeStatus->roll = 0;
            ceHopeStatus->yaw = 0;
            ceHopeStatus->accelerator =0;
            ceHopeStatus->ceAlt.altitude = -9999; 

            ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_ERROR);
            ceSysCtlOp.setAlarm(10,0,1);
        }else if(ceUavFlyModule == CE_UAV_FLY_MODULE_NORMAL)//正常等待起飞状态
        {
            ceHopeStatus->pitch = 0;
            ceHopeStatus->roll = 0;
            ceHopeStatus->yaw = 0;
            ceHopeStatus->accelerator =0;
            ceHopeStatus->ceAlt.altitude = -9999; 

            if(ceSysCtlOp.getLedMode() == CE_LED_CTL_MODE_IN_CFG) ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_NORMAL);//LED灯状态为正常状态 
            if((cePackageRecv.status & CE_PACKAGE_BTN_RIGHT) == CE_PACKAGE_BTN_RIGHT)//如果在正常等待起飞模式下，按下了遥控器右键
            {
                if(cePackageRecv.leftY <= -100)//如果此时左手摇杆Y的值小于-100，即拉到了最低，则配置无人机为手动油门状态; 否则配置为自动油门（气压计定高飞行状态）
                {
                    ceUavFlyModule = CE_UAV_FLY_MODULE_FREE_ACCE;
                }
                else
                {
                    ceUavFlyModule = CE_UAV_FLY_MODULE_FIX_HIGHT;
                    ceHopeStatus->ceAlt.altitude  = (ceNowStatus->ceAlt.altitude + 1.0f);//将当前无人机期望高度配置为距离地面约1.0m处
                }
            }
        }else if(ceUavFlyModule == CE_UAV_FLY_MODULE_FREE_ACCE)//手动油门自由飞行状态
        {
            if((cePackageRecv.status & CE_PACKAGE_BTN_S2B) == CE_PACKAGE_BTN_S2B) ceUavFlyModule = CE_UAV_FLY_MODULE_ERROR;//按下了急停按钮,直接进入错误状态
            if((cePackageRecv.status & CE_PACKAGE_BTN_S2D) == CE_PACKAGE_BTN_S2D) ceUavFlyModule = CE_UAV_FLY_MODULE_NORMAL;//按下了停止飞行按钮,直接进入正常等待飞行状态

            ceHopeStatus->yaw = ((ceMathOp.abs(cePackageRecv.leftX) > 100) ? (-(fp32)(cePackageRecv.leftX)/25):0.0f);        //设置偏航角有正负300的死区，防止打油门时偏航有误差导致飞行不稳定
            ceHopeStatus->pitch = ((ceMathOp.abs(cePackageRecv.rightY) > 150) ? ((fp32)(cePackageRecv.rightY) /166) : 0.0f);  //限制角度在-6~+6度之间,并配置Pitch角的死区，以防止摇杆误差导致的飘移
            ceHopeStatus->roll = ((ceMathOp.abs(cePackageRecv.rightX) > 150) ? (-(fp32)(cePackageRecv.rightX) /166) : 0.0f);  //限制角度在-6~+6度之间 ,并配置Roll角的死区，以防止摇杆误差导致的飘移 

            ceHopeStatus->accelerator = cePackageRecv.leftY/2 + 500;     //将-1000~+1000，转换为0~1000，以保证期望油门在0~1000的范围内        
            ceHopeStatus->ceAlt.altitude = -9999;   //通知PID控制器，此时为手动油门飞行状态，即没有期望的海拔值.
        }else if(ceUavFlyModule == CE_UAV_FLY_MODULE_FIX_HIGHT)//自动油门，定高飞行状态
        {
            if((cePackageRecv.status & CE_PACKAGE_BTN_S2B) == CE_PACKAGE_BTN_S2B) ceUavFlyModule = CE_UAV_FLY_MODULE_ERROR;//按下了急停按钮,直接进入错误状态
            if((cePackageRecv.status & CE_PACKAGE_BTN_S2D) == CE_PACKAGE_BTN_S2D) ceUavFlyModule = CE_UAV_FLY_MODULE_NORMAL;//按下了停止飞行按钮,直接进入正常等待飞行状态

            ceHopeStatus->yaw = ((ceMathOp.abs(cePackageRecv.leftX) > 300) ? (-(fp32)(cePackageRecv.leftX)/50):0.0f);        //设置偏航角有正负300的死区，防止打油门时偏航有误差导致飞行不稳定
            ceHopeStatus->pitch = ((ceMathOp.abs(cePackageRecv.rightY) > 150) ? ((fp32)(cePackageRecv.rightY) /166) : 0.0f);  //限制角度在-6~+6度之间,并配置Pitch角的死区，以防止摇杆误差导致的飘移
            ceHopeStatus->roll = ((ceMathOp.abs(cePackageRecv.rightX) > 150) ? (-(fp32)(cePackageRecv.rightX) /166) : 0.0f);  //限制角度在-6~+6度之间 ,并配置Roll角的死区，以防止摇杆误差导致的飘移 

            //ceHopeStatus->accelerator = cePackageRecv.leftY/2 + 500;//油门已经由PID根据期望海拔高度自动计算，故这里不需要返回期望的油门
            ceHopeStatus->ceAlt.altitude += (ceMathOp.abs(cePackageRecv.leftY) > 200)?((fp32)(cePackageRecv.leftY)/10000):0.0f;   //配置死区，消除摇杆位于中间时的静差。期望高度增加或减小.
        }
    }
    ceParCtlOp.sendDataHook();                  //发送数据接口函数

    //根据期望的姿态，定义LED航向灯的闪烁状态
    if(ceHopeStatus->pitch >3)           ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_GOTO_FRONT);
    else if(ceHopeStatus->pitch <(-3))   ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_GOTO_BACK);
    else if(ceHopeStatus->roll >3)       ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_GOTO_LEFT);
    else if(ceHopeStatus->roll <(-3))    ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_GOTO_RIGHT);
    else if(ceHopeStatus->yaw >3)        ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_FLASH_CYCLE_N);
    else if(ceHopeStatus->yaw <(-3))     ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_FLASH_CYCLE_P);
    else                                ceSysCtlOp.setLedMode(CE_LED_CTL_MODE_IN_NORMAL);
}

/**
  * @brief  初始化CeStatus模块操作对象
  */
const CeStatusOp ceStatusOp = {ceStatus_initial,ceStatus_getNowStatus,ceStatus_getHopeStatus};

#ifdef __cplusplus
 }
#endif //__cplusplus

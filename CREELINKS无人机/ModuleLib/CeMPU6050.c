/**
  ******************************************************************************
  * @file    ceMPU6050.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   ������ceMPU6050ģ����������ļ�
  ******************************************************************************
  * @attention
  *
  *1)MPU6050
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "CeMPU6050.h"
#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

// ����MPU6050�ڲ���ַ
//****************************************
#define    CE_MPU6050_SMPLRT_DIV       0x19    //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define    CE_MPU6050_CONFIG           0x1A    //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define    CE_MPU6050_GYRO_CONFIG      0x1B    //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define    CE_MPU6050_ACCEL_CONFIG     0x1C    //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define    CE_MPU6050_ACCEL_XOUT_H     0x3B
#define    CE_MPU6050_ACCEL_XOUT_L     0x3C
#define    CE_MPU6050_ACCEL_YOUT_H     0x3D
#define    CE_MPU6050_ACCEL_YOUT_L     0x3E
#define    CE_MPU6050_ACCEL_ZOUT_H     0x3F
#define    CE_MPU6050_ACCEL_ZOUT_L     0x40
#define    CE_MPU6050_TEMP_OUT_H       0x41
#define    CE_MPU6050_TEMP_OUT_L       0x42
#define    CE_MPU6050_GYRO_XOUT_H      0x43
#define    CE_MPU6050_GYRO_XOUT_L      0x44    
#define    CE_MPU6050_GYRO_YOUT_H      0x45
#define    CE_MPU6050_GYRO_YOUT_L      0x46
#define    CE_MPU6050_GYRO_ZOUT_H      0x47
#define    CE_MPU6050_GYRO_ZOUT_L      0x48
#define    CE_MPU6050_PWR_MGMT_1       0x6B    //��Դ��������ֵ��0x00(��������)
#define    CE_MPU6050_WHO_AM_I         0x75    //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define    CE_MPU6050_ADDRESS          0xD0    //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

/**
  * @brief  Write an byte to the specified device address through I2C bus.
  * @param  ceI2cMaster:
  * @param  DevAddr: The address byte of the slave device
  * @param  RegAddr: The address byte of  register of the slave device
  * @param  Data: the data would be writen to the specified device address
  * @return  None
  */
void ceMPU6050_I2C_WriteOneByte(CeI2cMaster *ceI2cMaster, uint8 DevAddr, uint8 RegAddr, uint8 Data)
{
    ceI2cMasterOp.start(ceI2cMaster);
    ceI2cMasterOp.writeByte(ceI2cMaster, DevAddr);
    ceI2cMasterOp.waitAck(ceI2cMaster);
    ceI2cMasterOp.writeByte(ceI2cMaster, RegAddr);
    ceI2cMasterOp.waitAck(ceI2cMaster);
    ceI2cMasterOp.writeByte(ceI2cMaster, Data);
    ceI2cMasterOp.waitAck(ceI2cMaster);
    ceI2cMasterOp.stop(ceI2cMaster);
}

/**
  * @brief Read an byte from the specified device address through I2C bus.
  * @param  ceI2cMaster:
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device
  * @return  the byte read from I2C bus
  */
uint8 ceMPU6050_I2C_ReadOneByte(CeI2cMaster *ceI2cMaster, uint8 DevAddr, uint8 RegAddr)
{
    uint8 TempVal = 0;
    ceI2cMasterOp.start(ceI2cMaster);
    ceI2cMasterOp.writeByte(ceI2cMaster, DevAddr);
    ceI2cMasterOp.waitAck(ceI2cMaster);
    ceI2cMasterOp.writeByte(ceI2cMaster, RegAddr);
    ceI2cMasterOp.waitAck(ceI2cMaster);
    ceI2cMasterOp.start(ceI2cMaster);
    ceI2cMasterOp.writeByte(ceI2cMaster, DevAddr | 0x01);
    ceI2cMasterOp.start(ceI2cMaster);
    TempVal = ceI2cMasterOp.readByte(ceI2cMaster, 0x00);
    ceI2cMasterOp.stop(ceI2cMaster);
    return TempVal;
}

/**
  * @brief  ��ȡ���ٶ�
  * @param  ceMPU6050:ceMPU6050���Զ���
  * @return ���ٶ�����
  */
CeMPU6050Acc *ceMPU6050_getAcceleration(CeMPU6050 *ceMPU6050)
{
    uint8 tempBuf[6] = { 0 };
    tempBuf[0] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_ACCEL_XOUT_L);    
    tempBuf[1] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_ACCEL_XOUT_H);
    ceMPU6050->acceleration.x = -((fp32)(((int16)(tempBuf[1]<<8)|tempBuf[0])) / 16384);  //���ٶ�X��

    tempBuf[2] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_ACCEL_YOUT_L);
    tempBuf[3] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_ACCEL_YOUT_H);
    ceMPU6050->acceleration.y  = -((fp32)(((int16)(tempBuf[3]<<8)|tempBuf[2]))  / 16384); //���ٶ�Y��

    tempBuf[4] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_ACCEL_ZOUT_L);
    tempBuf[5] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_ACCEL_ZOUT_H);
    ceMPU6050->acceleration.z = -((fp32)(((int16)(tempBuf[5]<<8)|tempBuf[4]))  / 16384);  //���ٶ�Z��
    return &(ceMPU6050->acceleration);
}

/**
  * @brief  ��ȡ�����ǽ��ٶ�
  * @param  ceMPU6050:ceMPU6050���Զ���
  * @return ���ٶ�����
  */
CeMPU6050Gyr *ceMPU6050_getGyroscope(CeMPU6050 *ceMPU6050)
{
    uint8 tempBuf[6] = { 0 };

    tempBuf[0] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_XOUT_L);
    tempBuf[1] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_XOUT_H);
    ceMPU6050->gyroscope.x= ((fp32)(((int16)((tempBuf[1]& 0x00FF)<<8)|tempBuf[0]))) / 65.5;//������X��    

    tempBuf[2] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_YOUT_L);
    tempBuf[3] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_YOUT_H);
    ceMPU6050->gyroscope.y =  ((fp32)(((int16)((tempBuf[3]& 0x00FF)<<8)|tempBuf[2]))) / 65.5;//������Y��    

    tempBuf[4] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_ZOUT_L);
    tempBuf[5] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_ZOUT_H);
    ceMPU6050->gyroscope.z =  ((fp32)(((int16)((tempBuf[5]& 0x00FF)<<8)|tempBuf[4]))) / 65.5;//������Z��

    ceMPU6050->gyroscope.x -= ceMPU6050->gyroscopeZero.x;
    ceMPU6050->gyroscope.y -= ceMPU6050->gyroscopeZero.y;
    ceMPU6050->gyroscope.z -= ceMPU6050->gyroscopeZero.z;

    return &(ceMPU6050->gyroscope);
}

/**
  * @brief  CeMPU6050ģ���ʼ��
  * @param  ceMPU6050:ceMPU6050���Զ���
  */
CE_STATUS ceMPU6050_initial(CeMPU6050 *ceMPU6050, CE_RESOURCE ceI2cMaster)
{
    ceMPU6050->ceI2cMaster.ceResource = ceI2cMaster;
    ceMPU6050->ceI2cMaster.ceI2cMasterSpeed = CE_I2C_SPEED_3_4MBPS;
    ceI2cMasterOp.initial(&(ceMPU6050->ceI2cMaster));

    ceMPU6050_I2C_WriteOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS,CE_MPU6050_PWR_MGMT_1, 0x00);    //�������״̬
    ceMPU6050_I2C_WriteOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS,CE_MPU6050_SMPLRT_DIV, 0x07);
    ceMPU6050_I2C_WriteOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS,CE_MPU6050_CONFIG, 0x06);
    ceMPU6050_I2C_WriteOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS,CE_MPU6050_GYRO_CONFIG, 0x08);
    ceMPU6050_I2C_WriteOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS,CE_MPU6050_ACCEL_CONFIG, 0x01); 

    if(ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_WHO_AM_I) == 0x68)
    {
        int i;
        ceDebugOp.printf("MPU6050 initial success!\n");
        ceSystemOp.delayMs(10);
        ceMPU6050->gyroscopeZero.x = 0;
        ceMPU6050->gyroscopeZero.y = 0;
        ceMPU6050->gyroscopeZero.z = 0;

        for(i = 0; i < 32; i++)
        {
            uint8 tempBuf[6] = {0};
            tempBuf[0] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_XOUT_L);
            tempBuf[1] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_XOUT_H);
            ceMPU6050->gyroscope.x = (fp32)(((int16)(tempBuf[1]<<8)|tempBuf[0])) / 65.5;

            tempBuf[2] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_YOUT_L);
            tempBuf[3] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_YOUT_H);
            ceMPU6050->gyroscope.y = (fp32)(((int16)(tempBuf[3]<<8)|tempBuf[2])) / 65.5;

            tempBuf[4] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_ZOUT_L);
            tempBuf[5] = ceMPU6050_I2C_ReadOneByte(&(ceMPU6050->ceI2cMaster), CE_MPU6050_ADDRESS, CE_MPU6050_GYRO_ZOUT_H);
            ceMPU6050->gyroscope.z =  (fp32)(((int16)(tempBuf[5]<<8)|tempBuf[4])) / 65.5;

            ceMPU6050->gyroscopeZero.x += ceMPU6050->gyroscope.x;
            ceMPU6050->gyroscopeZero.y += ceMPU6050->gyroscope.y;
            ceMPU6050->gyroscopeZero.z += ceMPU6050->gyroscope.z;
            ceSystemOp.delayMs(5);
        }

        ceMPU6050->gyroscopeZero.x /= 32;
        ceMPU6050->gyroscopeZero.y /= 32;
        ceMPU6050->gyroscopeZero.z /= 32;

        return CE_STATUS_SUCCESS;
    }
    else
    {
        ceDebugOp.printf("MPU6050 initial faile!\n");
        return CE_STATUS_FAILE;
    }
}

const CeMPU6050Op ceMPU6050Op = {ceMPU6050_initial, ceMPU6050_getAcceleration, ceMPU6050_getGyroscope};

#ifdef __cplusplus
}
#endif //__cplusplus


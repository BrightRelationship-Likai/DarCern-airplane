/**
  ******************************************************************************
  * @file    ce10Dof.c
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于ce10Dof模块的驱动库文件
  ******************************************************************************
  * @attention
  *
  *1)MPU9255(三轴加速度,三轴陀螺仪,三轴罗盘) BMP180(气压计,内置温度传感器)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#include "Ce10Dof.h"
#include "math.h"
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#define Kp 4.50f   // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 1.0f    // integral gain governs rate of convergence of gyroscope biases

#define M_PI  (float)3.1415926535
/*MPU9250******************************************************/
#define    SMPLRT_DIV        0x19     //Sample Rate Divider. Typical values:0x07(125Hz) 1KHz internal sample rate
#define    CONFIG            0x1A     //Low Pass Filter.Typical values:0x06(5Hz)
#define    GYRO_CONFIG        0x1B    //Gyro Full Scale Select. Typical values:0x10(1000dps)
#define    ACCEL_CONFIG    0x1C       //Accel Full Scale Select. Typical values:0x01(2g)

#define    CE_ACCEL_DATA_BASE    0x3B //加速度数据的基地址，范围0x3B-0x40，8bit
#define    ACCEL_XOUT_H    0x3B
#define    ACCEL_XOUT_L    0x3C
#define    ACCEL_YOUT_H    0x3D
#define    ACCEL_YOUT_L    0x3E
#define    ACCEL_ZOUT_H    0x3F
#define    ACCEL_ZOUT_L    0x40

#define    TEMP_OUT_H        0x41
#define    TEMP_OUT_L        0x42

#define    CE_GYRO_DATA_BASE    0x43//陀螺仪速度数据的基地址，范围0x43-0x48，8bit
#define    GYRO_XOUT_H        0x43
#define    GYRO_XOUT_L        0x44
#define    GYRO_YOUT_H        0x45
#define    GYRO_YOUT_L        0x46
#define    GYRO_ZOUT_H        0x47
#define    GYRO_ZOUT_L        0x48

#define    CE_MAG_DATA_BASE    0x03  //电子罗盘数据的基地址，范围0x03-0x08，8bit
#define MAG_XOUT_L        0x03
#define MAG_XOUT_H        0x04
#define MAG_YOUT_L        0x05
#define MAG_YOUT_H        0x06
#define MAG_ZOUT_L        0x07
#define MAG_ZOUT_H        0x08

#define    PWR_MGMT_1        0x6B    //Power Management. Typical values:0x00(run mode)
#define    WHO_AM_I        0x75      //identity of the device

#define    GYRO_ADDRESS   0xD0       //Gyro and Accel device address
#define MAG_ADDRESS    0x18          //compass device address
#define ACCEL_ADDRESS  0xD0

#define ADDRESS_AD0_LOW     0xD0     //address pin low (GND), default for InvenSense evaluation board
#define ADDRESS_AD0_HIGH    0xD1     //address pin high (VCC)
#define DEFAULT_ADDRESS     GYRO_ADDRESS
#define WHO_AM_I_VAL                0x73 //identity of MPU9250 is 0x71. identity of MPU9255 is 0x73.

/**BMP180*****************************************************/
//看不懂查数据手册
#define BMP180_ADDR                 0xEE     // default I2C address
/* ---- Registers ---- */
#define CAL_AC1           0xAA  // R   Calibration data (16 bits)
#define CAL_AC2           0xAC  // R   Calibration data (16 bits)
#define CAL_AC3           0xAE  // R   Calibration data (16 bits)
#define CAL_AC4           0xB0  // R   Calibration data (16 bits)
#define CAL_AC5           0xB2  // R   Calibration data (16 bits)
#define CAL_AC6           0xB4  // R   Calibration data (16 bits)
#define CAL_B1            0xB6  // R   Calibration data (16 bits)
#define CAL_B2            0xB8  // R   Calibration data (16 bits)
#define CAL_MB            0xBA  // R   Calibration data (16 bits)
#define CAL_MC            0xBC  // R   Calibration data (16 bits)
#define CAL_MD            0xBE  // R   Calibration data (16 bits)
#define CONTROL           0xF4  // W   Control register
#define CONTROL_OUTPUT    0xF6  // R   Output registers 0xF6=MSB, 0xF7=LSB, 0xF8=XLSB

// BMP180 Modes
#define MODE_ULTRA_LOW_POWER    0 //oversampling=0, internalsamples=1, maxconvtimepressure=4.5ms, avgcurrent=3uA, RMSnoise_hPA=0.06, RMSnoise_m=0.5 超低功耗
#define MODE_STANDARD           1 //oversampling=1, internalsamples=2, maxconvtimepressure=7.5ms, avgcurrent=5uA, RMSnoise_hPA=0.05, RMSnoise_m=0.4 标准
#define MODE_HIGHRES            2 //oversampling=2, internalsamples=4, maxconvtimepressure=13.5ms, avgcurrent=7uA, RMSnoise_hPA=0.04, RMSnoise_m=0.3 高线性度
#define MODE_ULTRA_HIGHRES      3 //oversampling=3, internalsamples=8, maxconvtimepressure=25.5ms, avgcurrent=12uA, RMSnoise_hPA=0.03, RMSnoise_m=0.25 超高线性度

// Control register
#define READ_TEMPERATURE        0x2E
#define READ_PRESSURE           0x34
//Other
#define MSLP                    101325          // Mean Sea Level Pressure = 1013.25 hPA (1hPa = 100Pa = 1mbar)
#define LOCAL_ADS_ALTITUDE      5200            //mm     altitude of your position now
#define PRESSURE_OFFSET         0               //Pa    Offset
Ce10DofGyroscope* ce10Dof_getGyroscope(Ce10Dof* ce10Dof);
/**
  * @brief  Initializes I2C
  * @param  None
  * @retval None
  */

void ce10Dof_I2Cx_Init(Ce10Dof* ce10Dof, CE_RESOURCE ceI2cMaster)
{
    ce10Dof->ceI2cMaster.ceResource = ceI2cMaster;
    ce10Dof->ceI2cMaster.ceI2cMasterSpeed = CE_I2C_SPEED_3_4MBPS;
    ceI2cMasterOp.initial(&(ce10Dof->ceI2cMaster));
}

/**
  * @brief  Write an byte to the specified device address through I2C bus.
  *
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device
 * @param  Data: the data would be writen to the specified device address
  * @retval  None
**/

void ce10Dof_I2C_WriteOneByte(Ce10Dof* ce10Dof,uint8 DevAddr, uint8 RegAddr, uint8 Data)
{
     ceI2cMasterOp.start(&(ce10Dof->ceI2cMaster));
     ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),DevAddr);
     ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
     ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),RegAddr);
     ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
     ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),Data);
     ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
     ceI2cMasterOp.stop(&(ce10Dof->ceI2cMaster));
}

/**
  * @brief Write a buffer specified sizes  to the specified device address through I2C bus.
  *
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device
  * @param Num: the sizes of the specified buffer
  * @param pBuff: point to a the specified buffer that would be writen
  * @retval  false: paramter error
  *                true: Write a buffer succeed
**/

uint8 ce10Dof_I2C_WriteBuff(Ce10Dof* ce10Dof,uint8 DevAddr, uint8 RegAddr, uint8 Num, uint8 *pBuff)
{
    uint8 i;
    if(Num == 0 || pBuff == CE_NULL)
    {
        return 0x00;
    }
    ceI2cMasterOp.start(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),DevAddr);
    ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),RegAddr);
    ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));

    for(i = 0; i < Num; i ++)
    {
        ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),*(pBuff + i));
        ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
    }
    ceI2cMasterOp.stop(&(ce10Dof->ceI2cMaster));
    return 0x01;
}

/**
  * @brief Read an byte from the specified device address through I2C bus.
  *
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device
  *
  * @retval  the byte read from I2C bus
**/

uint8 ce10Dof_I2C_ReadOneByte(Ce10Dof* ce10Dof,uint8 DevAddr, uint8 RegAddr)
{
    uint8 TempVal = 0;
    ceI2cMasterOp.start(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),DevAddr);
    ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),RegAddr);
    ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.start(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),DevAddr | 0x01);
    ceI2cMasterOp.start(&(ce10Dof->ceI2cMaster));
    TempVal = ceI2cMasterOp.readByte(&(ce10Dof->ceI2cMaster),0x00);
    ceI2cMasterOp.stop(&(ce10Dof->ceI2cMaster));

    return TempVal;
}

/**
  * @brief Read couples of bytes  from the specified device address through I2C bus.
  *
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device
  * @param Num: the sizes of the specified buffer
  * @param pBuff: point to a the specified buffer that would read bytes from I2C bus
  * @retval  false: paramter error
  *                true: read a buffer succeed
**/

uint8 ce10Dof_I2C_ReadBuff(Ce10Dof* ce10Dof,uint8 DevAddr, uint8 RegAddr, uint8 Num, uint8 *pBuff)
{
    uint8 i;

    if(Num == 0 || pBuff == CE_NULL)
    {
        return 0x00;
    }
    ceI2cMasterOp.start(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),DevAddr);
    ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),RegAddr);
    ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.start(&(ce10Dof->ceI2cMaster));
    ceI2cMasterOp.writeByte(&(ce10Dof->ceI2cMaster),DevAddr|0x01);
    ceI2cMasterOp.waitAck(&(ce10Dof->ceI2cMaster));

    for(i = 0; i < Num; i ++)
    {
        if((Num - 1) == i)
        {
            *(pBuff + i) = ceI2cMasterOp.readByte(&(ce10Dof->ceI2cMaster),0x00);
        }
        else
        {
            *(pBuff + i) = ceI2cMasterOp.readByte(&(ce10Dof->ceI2cMaster),0x01);
        }
    }

    ceI2cMasterOp.stop(&(ce10Dof->ceI2cMaster));

    return 0x01;
}

/**
  * @brief  Read calibration data from the EEPROM of the BMP180//从BMP180的EEPROM中读取校准数据
  * @param  None
  * @retval None
  */
void ce10Dof_BMP180_ReadCalibrationData(Ce10Dof* ce10Dof)
{
    uint8 RegBuff[2];
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_AC1, 2, RegBuff);
    (ce10Dof->exBmp180.AC1) = ((int16)RegBuff[0] << 8 | ((int16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_AC2, 2, RegBuff);
    (ce10Dof->exBmp180.AC2) = ((int16)RegBuff[0] << 8 | ((int16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_AC3, 2, RegBuff);
    (ce10Dof->exBmp180.AC3) = ((int16)RegBuff[0] << 8 | ((int16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_AC4, 2, RegBuff);
    (ce10Dof->exBmp180.AC4) = ((uint16)RegBuff[0] << 8 | ((uint16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_AC5, 2, RegBuff);
    (ce10Dof->exBmp180.AC5) = ((uint16)RegBuff[0] << 8 | ((uint16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_AC6, 2, RegBuff);
    (ce10Dof->exBmp180.AC6) = ((uint16)RegBuff[0] << 8 | ((uint16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_B1, 2, RegBuff);
    (ce10Dof->exBmp180.B1) = ((int16)RegBuff[0] << 8 | ((int16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_B2, 2, RegBuff);
    (ce10Dof->exBmp180.B2) = ((int16)RegBuff[0] << 8 | ((int16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_MB, 2, RegBuff);
    (ce10Dof->exBmp180.MB) = ((int16)RegBuff[0] << 8 | ((int16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_MC, 2, RegBuff);
    (ce10Dof->exBmp180.MC) = ((int16)RegBuff[0] << 8 | ((int16)RegBuff[1]));
    ce10Dof_I2C_ReadBuff(ce10Dof,BMP180_ADDR, CAL_MD, 2, RegBuff);
    (ce10Dof->exBmp180.MD) = ((int16)RegBuff[0] << 8 | ((int16)RegBuff[1]));
}

/**
  * @brief  initializes BMP180//初始化
  * @param  None
  * @retval None
  */
CE_STATUS ce10Dof_BMP180_Init(Ce10Dof* ce10Dof)
{
    ce10Dof->exBmp180._oss = MODE_STANDARD;//运行模式
    ce10Dof_BMP180_ReadCalibrationData(ce10Dof);
    if(ce10Dof_I2C_ReadOneByte(ce10Dof,BMP180_ADDR, 0xd0 )== 0x55 )
    {//存在
        ce10Dof_BMP180_ReadCalibrationData(ce10Dof);
        ceDebugOp.printf("BMP180 initial success!\n");
              return CE_STATUS_SUCCESS;
    }
    else
    {//不存在
        ceDebugOp.printf("BMP180 initial faile!\n");
              return CE_STATUS_FAILE;
    }
}

/******************************************************
Function    :BMP180ReadUnsetTemperature
Input        :address
Output        :N/A
Return        :shour int byte-data
Description    :读取未校正的温度值
Note        :接收后面的一字节数据，主机不需要应答
******************************************************/
int32 ce10Dof_BMP180ReadUnsetTemperature(Ce10Dof* ce10Dof)
{
    uint8 msb , lsb ;
    ce10Dof_I2C_WriteOneByte(ce10Dof, BMP180_ADDR, 0xf4, 0x2e);
    msb = ce10Dof_I2C_ReadOneByte(ce10Dof,BMP180_ADDR, 0xf6 );
    lsb = ce10Dof_I2C_ReadOneByte(ce10Dof,BMP180_ADDR, 0xf6+1 );
    return ( ((int32)msb) << 8 | lsb) ;
}

/******************************************************
Function    :BMP180ReadUnsetPressure
Input        :N/A
Output        :N/A
Return        :未校正气压值
Description    :读取未校正的气压值
Note        :N/A
******************************************************/
int32 ce10Dof_BMP180ReadUnsetPressure(Ce10Dof* ce10Dof)
{
    int32 pressure = 0;
    uint8 msb, lsb;
    ce10Dof_I2C_WriteOneByte(ce10Dof, BMP180_ADDR, 0xf4, 0x34 + (ce10Dof->exBmp180._oss<<6));
    ceSystemOp.delayMs(10);
    msb = ce10Dof_I2C_ReadOneByte(ce10Dof,BMP180_ADDR, 0xf6 );
    lsb = ce10Dof_I2C_ReadOneByte(ce10Dof,BMP180_ADDR, 0xf6+1 );

    pressure = ( ((int32)msb) << 8 | lsb);
    pressure = (((int32)pressure <<8) + ce10Dof_I2C_ReadOneByte(ce10Dof,BMP180_ADDR, 0xf8 )) >> (8-ce10Dof->exBmp180._oss) ;
    return pressure;
}

/**
  * @brief  获取已经过校正的温度、气压、海拔高度
  * @param  ce10Dof:ce10Dof属性对象
  * @return 温度、气压、海拔高度
  */
Ce10DofEnvironment* ce10Dof_getEnvironment(Ce10Dof* ce10Dof)
{
    int32 x1, x2, B5, B6, x3, B3, p;
    unsigned long b4, b7;
    int32 UnsetTemperature,UnsetGasPress;
    //未校正的温度值
    UnsetTemperature = ce10Dof_BMP180ReadUnsetTemperature(ce10Dof);
    //温度校正
    x1 = ((UnsetTemperature) - ce10Dof->exBmp180.AC6) * (ce10Dof->exBmp180.AC5) >> 15;
    x2 = ((int32)(ce10Dof->exBmp180.MC) << 11) / (x1 + ce10Dof->exBmp180.MD);
    B5 = x1 + x2;
    ce10Dof->environment.temperature = ((fp32)((B5 + 8) >> 4))/10;



    //未校正的气压值
    UnsetGasPress = ce10Dof_BMP180ReadUnsetPressure(ce10Dof);
    //气压校正
    B6 = B5- 4000;
    x1 = ((int32)(ce10Dof->exBmp180.B2) * (B6 * B6 >> 12)) >> 11;
    x2 = ((int32)ce10Dof->exBmp180.AC2) * B6 >> 11;
    x3 = x1 + x2;
    B3 = ((((int32)(ce10Dof->exBmp180.AC1) * 4 + x3)<<ce10Dof->exBmp180._oss) + 2)/4;
    x1 = ((int32)ce10Dof->exBmp180.AC3) * B6 >> 13;
    x2 = ((int32)(ce10Dof->exBmp180.B1) * (B6 * B6 >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    b4 = ((int32)(ce10Dof->exBmp180.AC4) * (unsigned long) (x3 + 32768)) >> 15;
    b7 = ((unsigned long)(UnsetGasPress) - B3) * (50000 >> ce10Dof->exBmp180._oss);
    if( b7 < 0x80000000)
    {
         p = (b7 * 2) / b4 ;
    }
    else
    {
         p = (b7 / b4) * 2;
    }
    x1 = (p >> 8) * (p >> 8);
    x1 = ((int32)x1 * 3038) >> 16;
    x2 = (-7357 * p) >> 16;
    ce10Dof->environment.pressure = p + ((x1 + x2 + 3791) >> 4);

    //海拔计算
    ce10Dof->environment.altitude =(44330.0 * (1.0-pow((float)(ce10Dof->environment.pressure) / 101325.0, 1.0/5.255)) )/100;

    return &(ce10Dof->environment);
}

/**
  * @brief  MPU9250初始化
  * @param  ce10Dof:ce10Dof属性对象
  * @return None
  */
CE_STATUS ce10Dof_MPU9250_Init(Ce10Dof* ce10Dof)
{
    if(ce10Dof_I2C_ReadOneByte(ce10Dof,DEFAULT_ADDRESS, WHO_AM_I) == WHO_AM_I_VAL)
    {
        int i;
        ce10Dof_I2C_WriteOneByte(ce10Dof, GYRO_ADDRESS, PWR_MGMT_1, 0x00);
        ce10Dof_I2C_WriteOneByte(ce10Dof, GYRO_ADDRESS, SMPLRT_DIV, 0x07);
        ce10Dof_I2C_WriteOneByte(ce10Dof, GYRO_ADDRESS, CONFIG, 0x06);
        ce10Dof_I2C_WriteOneByte(ce10Dof, GYRO_ADDRESS, GYRO_CONFIG, 0x10);
        ce10Dof_I2C_WriteOneByte(ce10Dof, GYRO_ADDRESS, ACCEL_CONFIG, 0x01);
        ceDebugOp.printf("MPU9255 initial success!\n");
        ceSystemOp.delayMs(10);
        ce10Dof->gyroscopeZero.x = 0;
        ce10Dof->gyroscopeZero.y = 0;
        ce10Dof->gyroscopeZero.z = 0;
        
        for(i=0;i<32;i++)
        {
            uint8 BUF[6]={0};
            BUF[0]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_XOUT_L);
            BUF[1]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_XOUT_H);
            ce10Dof->gyroscope.x = (fp32)(((int16)(BUF[1]<<8)|BUF[0]) / 131);

            BUF[2]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_YOUT_L);
            BUF[3]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_YOUT_H);
            ce10Dof->gyroscope.y = (fp32)(((int16)(BUF[3]<<8)|BUF[2]) / 131);

            BUF[4]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_ZOUT_L);
            BUF[5]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_ZOUT_H);
            ce10Dof->gyroscope.z = (fp32)(((int16)(BUF[5]<<8)|BUF[4]) / 131);

            ce10Dof->gyroscopeZero.x += ce10Dof->gyroscope.x;
            ce10Dof->gyroscopeZero.y += ce10Dof->gyroscope.y;
            ce10Dof->gyroscopeZero.z += ce10Dof->gyroscope.z;
        }

        ce10Dof->gyroscopeZero.x /=32;
        ce10Dof->gyroscopeZero.y /=32;
        ce10Dof->gyroscopeZero.z /=32;

        return CE_STATUS_SUCCESS;
    }
    else
    {
       ceDebugOp.printf("MPU9255 initial faile!\n");
       return CE_STATUS_FAILE;
    }
}

/**
  * @brief  获取加速度
  * @param  ce10Dof:ce10Dof属性对象
  * @return 加速度数据
  */
Ce10DofAcceleration* ce10Dof_getAcceleration(Ce10Dof* ce10Dof)
{
    uint8 BUF[6]={0};

    BUF[0]=ce10Dof_I2C_ReadOneByte(ce10Dof,ACCEL_ADDRESS, ACCEL_XOUT_L);
    BUF[1]=ce10Dof_I2C_ReadOneByte(ce10Dof,ACCEL_ADDRESS, ACCEL_XOUT_H);
    ce10Dof->acceleration.x = ((fp32)(((int16)(BUF[1]<<8)|BUF[0])) / 16384);

    BUF[2]=ce10Dof_I2C_ReadOneByte(ce10Dof,ACCEL_ADDRESS, ACCEL_YOUT_L);
    BUF[3]=ce10Dof_I2C_ReadOneByte(ce10Dof,ACCEL_ADDRESS, ACCEL_YOUT_H);
    ce10Dof->acceleration.y = ((fp32)(((int16)(BUF[3]<<8)|BUF[2]))  / 16384);

    BUF[4]=ce10Dof_I2C_ReadOneByte(ce10Dof,ACCEL_ADDRESS, ACCEL_ZOUT_L);
    BUF[5]=ce10Dof_I2C_ReadOneByte(ce10Dof,ACCEL_ADDRESS, ACCEL_ZOUT_H);
    ce10Dof->acceleration.z = ((fp32)(((int16)(BUF[5]<<8)|BUF[4]))  / 16384);
    return &(ce10Dof->acceleration);
}

/**
  * @brief  获取陀螺仪角速度
  * @param  ce10Dof:ce10Dof属性对象
  * @return 角速度数据
  */
Ce10DofGyroscope* ce10Dof_getGyroscope(Ce10Dof* ce10Dof)
{
    uint8 BUF[6]={0};
    BUF[0]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_XOUT_L);
    BUF[1]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_XOUT_H);
    ce10Dof->gyroscope.x =    ((fp32)(((int16)(BUF[1]<<8)|BUF[0])) / 131);


    BUF[2]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_YOUT_L);
    BUF[3]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_YOUT_H);
    ce10Dof->gyroscope.y =    ((fp32)(((int16)(BUF[3]<<8)|BUF[2])) / 131);

    BUF[4]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_ZOUT_L);
    BUF[5]=ce10Dof_I2C_ReadOneByte(ce10Dof,GYRO_ADDRESS,GYRO_ZOUT_H);
    ce10Dof->gyroscope.z =    ((fp32)(((int16)(BUF[5]<<8)|BUF[4])) / 131);

    ce10Dof->gyroscope.x -=ce10Dof->gyroscopeZero.x;
    ce10Dof->gyroscope.y -=ce10Dof->gyroscopeZero.y;
    ce10Dof->gyroscope.z -=ce10Dof->gyroscopeZero.z;

    return &(ce10Dof->gyroscope);
}

/**
  * @brief  获取电子罗盘倾角
  * @param  ce10Dof:ce10Dof属性对象
  * @return 电子罗盘倾角数据
  */
Ce10DofMagnetic* ce10Dof_getMagnetic(Ce10Dof* ce10Dof)
{
    uint8 BUF[6]={0};
    ce10Dof_I2C_WriteOneByte(ce10Dof,GYRO_ADDRESS,0x37,0x02);
    ceSystemOp.delayMs(10);
    ce10Dof_I2C_WriteOneByte(ce10Dof,MAG_ADDRESS,0x0A,0x01);
    ceSystemOp.delayMs(10);

    BUF[0]=ce10Dof_I2C_ReadOneByte(ce10Dof,MAG_ADDRESS,MAG_XOUT_L);
    BUF[1]=ce10Dof_I2C_ReadOneByte(ce10Dof,MAG_ADDRESS,MAG_XOUT_H);
    ce10Dof->magnetic.x=(BUF[1]<<8)|BUF[0];

    BUF[2]=ce10Dof_I2C_ReadOneByte(ce10Dof,MAG_ADDRESS,MAG_YOUT_L);
    BUF[3]=ce10Dof_I2C_ReadOneByte(ce10Dof,MAG_ADDRESS,MAG_YOUT_H);
    ce10Dof->magnetic.y=    (BUF[3]<<8)|BUF[2];

    BUF[4]=ce10Dof_I2C_ReadOneByte(ce10Dof,MAG_ADDRESS,MAG_ZOUT_L);
    BUF[5]=ce10Dof_I2C_ReadOneByte(ce10Dof,MAG_ADDRESS,MAG_ZOUT_H);
    ce10Dof->magnetic.z=    (BUF[5]<<8)|BUF[4];

    return &(ce10Dof->magnetic);
}

/**
  * @brief  Ce10Dof模块初始化
  * @param  ce10Dof:ce10Dof属性对象
  */
CE_STATUS ce10Dof_initial(Ce10Dof* ce10Dof,CE_RESOURCE ceI2cMaster)
{
    CE_STATUS ceStatus;
    ce10Dof->exBmp180.Pressure0 = MSLP;
    ce10Dof_I2Cx_Init(ce10Dof,ceI2cMaster);
    ceStatus = ce10Dof_MPU9250_Init(ce10Dof);
    ceStatus = ce10Dof_BMP180_Init(ce10Dof);

    if(ceStatus == CE_STATUS_SUCCESS)
    {
        return CE_STATUS_SUCCESS;
    }else
    {
        return CE_STATUS_FAILE;
    }
}

const Ce10DofOp ce10DofOp = {ce10Dof_initial, ce10Dof_getAcceleration, ce10Dof_getGyroscope, ce10Dof_getMagnetic,ce10Dof_getEnvironment};

#ifdef __cplusplus
 }
#endif //__cplusplus

#include "MPU6050.h"

int16_t Accel_X_RAW;
int16_t Accel_Y_RAW;
int16_t Accel_Z_RAW;

int16_t Gyro_X_RAW;
int16_t Gyro_Y_RAW;
int16_t Gyro_Z_RAW;

float Gx;
float Gy;
float Gz;
float Ax;
float Ay;
float Az;

void MPU6050_Init(void);
void MPU6050_Read_Accel(void);
void MPU6050_Read_Gyro(void);
void pingled(void);
void MPU6050_Init(void)
{
	uint8_t check,data;
	
	// check device ID WHO AM I
	HAL_I2C_Mem_Read(&hi2c3,MPU6050_ADDR,WHO_AM_I_REG,1,&check,1,1000);
	
	if(check == 104) // if the device is present
	{
		// power management register 0x6B we should write all 0's to wake the sensor up
			data=0;
			HAL_I2C_Mem_Write(&hi2c3,MPU6050_ADDR,PWR_MGMT_1_REG,1,&data,1,1000);
		// set DATA RATE of 1KHZ by writing SMPLRT_DIV register
		
			data=0x07;
			HAL_I2C_Mem_Write(&hi2c3,MPU6050_ADDR,SMPLRT_DIV_REG,1,&data,1,1000);
	}
}

void MPU6050_Read_Accel(void)
{
	uint8_t Rec_Data[6];
	
	HAL_I2C_Mem_Read_IT(&hi2c3,MPU6050_ADDR<<1,ACCEL_XOUT_H_REG,I2C_MEMADD_SIZE_8BIT,Rec_Data,6);
	Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);
	/*** convert the RAW values into acceleration in 'g'
     we have to divide according to the Full scale value set in FS_SEL
     I have configured FS_SEL = 0. So I am dividing by 16384.0
     for more details check ACCEL_CONFIG Register              ****/

	Ax = Accel_X_RAW/16384.0;  // get the float g
	Ay = Accel_Y_RAW/16384.0;
	Az = Accel_Z_RAW/16384.0;
	
}

void MPU6050_Read_Gyro(void)
{
	uint8_t Rec_Data[6];
	
	HAL_I2C_Mem_Read_IT (&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, I2C_MEMADD_SIZE_8BIT, Rec_Data, 6);
	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);
	
	/*** convert the RAW values into dps (°/s)
     we have to divide according to the Full scale value set in FS_SEL
     I have configured FS_SEL = 0. So I am dividing by 131.0
     for more details check GYRO_CONFIG Register              ****/

	Gx = Gyro_X_RAW/131.0;
	Gy = Gyro_Y_RAW/131.0;
	Gz = Gyro_Z_RAW/131.0;
	
}

void pingled(void)
{
	HAL_GPIO_TogglePin(LD5_GPIO_Port,LD5_Pin|LD6_Pin|LD5_Pin|LD6_Pin);
		HAL_Delay(500);
		
		HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_RESET);
		HAL_Delay(400);
		HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_SET);
		HAL_Delay(400);
		HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_RESET);
		HAL_Delay(300);
		HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_SET);
		HAL_Delay(300);
		HAL_GPIO_WritePin(LD5_GPIO_Port,LD6_Pin,GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LD5_GPIO_Port,LD6_Pin,GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_SET);
		HAL_Delay(100);
		
		HAL_GPIO_TogglePin(LD5_GPIO_Port,LD6_Pin|LD6_Pin|LD5_Pin|LD6_Pin);
		HAL_Delay(500);
}


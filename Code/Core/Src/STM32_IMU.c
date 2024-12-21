/*
 * STM32_IMU.c
 *
 *  Created on: Dec 21, 2024
 *      Author: doudz
 */


#include "STM32_IMU.h"


#define IMU_addr_R  0xD0
#define IMU_addr_W  0xD1

#define IMU_REG_SMPLRT_DIV    0x19
#define IMU_REG_CONFIG   	  0x1A
#define IMU_REG_GYRO_CONFIG   0x1B
#define IMU_REG_ACCEL_CONFIG  0x1C
#define IMU_REG_PWR_MNGMT	  0x6B

#define IMU_TEMP_H    0x41
#define IMU_TEMP_L    0x42
#define IMU_GYRO_X_H  0x43
#define IMU_GYRO_X_L  0x44
#define IMU_GYRO_Y_H  0x45
#define IMU_GYRO_Y_L  0x46
#define IMU_GYRO_Z_H  0x47
#define IMU_GYRO_Z_L  0x48


extern I2C_HandleTypeDef hi2c2;
uint8_t tx_buffer,rx_buffer,temp_H,temp_L;
int16_t temperature;
uint16_t temp_degree;
uint8_t Rx_gyro_values[6];


int16_t Gyro_X_data = 0;
int16_t Gyro_Y_data = 0;
int16_t Gyro_Z_data = 0;


void read_IMU_temp()
{
	HAL_I2C_Mem_Read(&hi2c2, IMU_addr_R, IMU_TEMP_H, 1, temp_H, 1, 1000);

	HAL_I2C_Mem_Read(&hi2c2, IMU_addr_R, IMU_TEMP_H, 1, temp_L, 1, 1000);

	temperature = ((temp_H << 8) + temp_L);
	temp_degree = ((temperature/340) + 36.53);
}


void Read_IMU_Gyro()
{
	HAL_I2C_Mem_Read(&hi2c2, IMU_addr_R, IMU_GYRO_X_H ,1, Rx_gyro_values, 6, 1000);
    Gyro_X_data = (int16_t)(Rx_gyro_values[0] << 8 | Rx_gyro_values [1]);
    Gyro_Y_data = (int16_t)(Rx_gyro_values[2] << 8 | Rx_gyro_values [3]);
    Gyro_Z_data = (int16_t)(Rx_gyro_values[4] << 8 | Rx_gyro_values [5]);
}


void init_IMU_MPU6050()
{

	if	(HAL_I2C_IsDeviceReady(&hi2c2, IMU_addr_R, 1, 1000))

		{
			tx_buffer = 0x07;
			HAL_I2C_Mem_Write(&hi2c2, IMU_addr_W, IMU_REG_SMPLRT_DIV, 1, tx_buffer, 1, 1000);
			tx_buffer = 0xE0;
			HAL_I2C_Mem_Write(&hi2c2, IMU_addr_W, IMU_REG_GYRO_CONFIG, 1, tx_buffer, 1, 1000);
			tx_buffer = 0x00;
			HAL_I2C_Mem_Write(&hi2c2, IMU_addr_W, IMU_REG_PWR_MNGMT, 1, tx_buffer, 1, 1000);
			tx_buffer = 0x00;
			HAL_I2C_Mem_Write(&hi2c2, IMU_addr_W, IMU_REG_ACCEL_CONFIG, 1, tx_buffer, 1, 1000);
		}

}

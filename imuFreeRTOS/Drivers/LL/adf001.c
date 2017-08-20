/*
 * adf001.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Sumanth
 */



#include "adf001.h"
#include "i2c.h"

/*
 * @brief Local Static Variables
 */

/*
 * @brief Local Static Functions
 */
static uint16_t l3gd20_gyro_init(void)
{
	uint16_t err_num = 0;

	uint8_t data = 0;
	err_num = i2c_read(&data, GYRO_REGISTER_WHO_AM_I, GYRO_DEV_ADDR);
	if(err_num) { NRF_LOG_INFO("Failed to read GYRO_REGISTER_WHO_AM_I\r\n"); return ADF001_GYRO_ERR_INIT; }

	if(data != GYRO_WHOAMI_VAL)
	{
		NRF_LOG_INFO("GYRO Device value is incorrect [0x%02X, expected 0x%02X]\r\n", data, GYRO_WHOAMI_VAL);
		return ADF001_GYRO_ERR_INIT;
	}
	// Set Ctrl 1 register values
	// 11 - ODR - 760 Hz, 11 - BW -100 Hz 1 - Normal Mode 111 - XYZ Enable
	DEBUG_PRINT();
	data = 0x00;
	err_num = i2c_write(&data, GYRO_REGISTER_CTRL_REG1, GYRO_DEV_ADDR);
	if(err_num) { NRF_LOG_INFO("Failed to write GYRO_REGISTER_CTRL_REG1 [err_num 0x%02X]\r\n", err_num); return ADF001_GYRO_ERR_INIT; }
	nrf_delay_ms(100);
	data = 0x0F;
	err_num = i2c_write(&data, GYRO_REGISTER_CTRL_REG1, GYRO_DEV_ADDR);
	if(err_num) { NRF_LOG_INFO("Failed to write GYRO_REGISTER_CTRL_REG1 [err_num 0x%02X]\r\n", err_num); return ADF001_GYRO_ERR_INIT; }
	nrf_delay_ms(100);
	// Set Ctrl 3 register values
	// 1 - Enable Interrupt;
	data = 0x80;
	err_num = i2c_write(&data, GYRO_REGISTER_CTRL_REG3, GYRO_DEV_ADDR);
	if(err_num) { NRF_LOG_INFO("Failed to write GYRO_REGISTER_CTRL_REG3 [err_num 0x%02X]\r\n", err_num); return ADF001_GYRO_ERR_INIT; }
	nrf_delay_ms(100);
	err_num = i2c_read(&data, GYRO_REGISTER_OUT_TEMP, GYRO_DEV_ADDR);
	NRF_LOG_INFO("errnum = %d \r\n", err_num);
	if(err_num) { NRF_LOG_INFO("Failed to read GYRO_REGISTER_OUT_TEMP\r\n"); return ADF001_GYRO_ERR_INIT; }
	NRF_LOG_INFO("Temperature = %d %X\r\n", data, data);
	NRF_LOG_FLUSH();
	return err_num;
}


uint16_t adf001_init(void)
{
	uint16_t err_num = 0;
	err_num = l3gd20_gyro_init();
	return err_num;
}

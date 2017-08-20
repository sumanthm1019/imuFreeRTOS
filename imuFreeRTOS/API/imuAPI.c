/*
 * imuAPI.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Sumanth
 */
#include "main.h"

#include "imuAPI.h"
#include "imuHAL.c"
#include "adf001.h"

uint16_t imu_init(void)
{
	uint16_t err_num = 0;
	NRF_LOG_INFO("imu_init\r\n");
	err_num = adf001_init();
	return err_num;
}
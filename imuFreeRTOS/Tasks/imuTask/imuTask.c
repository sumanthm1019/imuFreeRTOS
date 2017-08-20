/*
 * imuTask.c
 *
 *  Created on: Aug 18, 2017
 *      Author: Sumanth
 */

#include "main.h"
#include "imuAPI.h"

void imuTask(void * pvParameter)
{
	uint16_t err_num = 0;

	err_num = imu_init();
	if(err_num) { NRF_LOG_ERROR("[imuTask] Failed to initialize imu [Err Num 0x%02X]\r\n", err_num); }
}

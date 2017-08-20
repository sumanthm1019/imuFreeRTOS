/*
 * i2c.h
 *
 *  Created on: Aug 19, 2017
 *      Author: Sumanth
 */
#include "main.h"
#include "nrf_drv_twi.h"

typedef struct
{
	uint8_t sda;
	uint8_t scl;
}i2c_cfg_t;

uint16_t i2c_init	(i2c_cfg_t *i2c);
uint16_t i2c_write	(uint8_t *data, uint8_t reg);
uint16_t i2c_read(uint8_t *data, uint8_t reg, uint8_t dev_addr);


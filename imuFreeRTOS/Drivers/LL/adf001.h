/*
 * adf001.h
 *
 *  Created on: Aug 19, 2017
 *      Author: Sumanth
 */

#include "main.h"

#ifndef DRIVERS_LL_ADF001_H_
#define DRIVERS_LL_ADF001_H_

// i2c Slave device addresses
#define ACCEL_DEV_ADDR 	0x19
#define MAG_DEV_ADDR	0x1E
#define GYRO_DEV_ADDR	0x6B

#define GYRO_WHOAMI_VAL		0xD7

/*=========================================================================
    REGISTERS
-----------------------------------------------------------------------*/
typedef enum
{                                             	// DEFAULT    TYPE
	GYRO_REGISTER_WHO_AM_I            = 0x0F,   // 11010100   r
	GYRO_REGISTER_CTRL_REG1           = 0x20,   // 00000111   rw
	GYRO_REGISTER_CTRL_REG2           = 0x21,   // 00000000   rw
	GYRO_REGISTER_CTRL_REG3           = 0x22,   // 00000000   rw
	GYRO_REGISTER_CTRL_REG4           = 0x23,   // 00000000   rw
	GYRO_REGISTER_CTRL_REG5           = 0x24,   // 00000000   rw
	GYRO_REGISTER_REFERENCE           = 0x25,   // 00000000   rw
	GYRO_REGISTER_OUT_TEMP            = 0x26,   //            r
	GYRO_REGISTER_STATUS_REG          = 0x27,   //            r
	GYRO_REGISTER_OUT_X_L             = 0x28,   //            r
	GYRO_REGISTER_OUT_X_H             = 0x29,   //            r
	GYRO_REGISTER_OUT_Y_L             = 0x2A,   //            r
	GYRO_REGISTER_OUT_Y_H             = 0x2B,   //            r
	GYRO_REGISTER_OUT_Z_L             = 0x2C,   //            r
	GYRO_REGISTER_OUT_Z_H             = 0x2D,   //            r
	GYRO_REGISTER_FIFO_CTRL_REG       = 0x2E,   // 00000000   rw
	GYRO_REGISTER_FIFO_SRC_REG        = 0x2F,   //            r
	GYRO_REGISTER_INT1_CFG            = 0x30,   // 00000000   rw
	GYRO_REGISTER_INT1_SRC            = 0x31,   //            r
	GYRO_REGISTER_TSH_XH              = 0x32,   // 00000000   rw
	GYRO_REGISTER_TSH_XL              = 0x33,   // 00000000   rw
	GYRO_REGISTER_TSH_YH              = 0x34,   // 00000000   rw
	GYRO_REGISTER_TSH_YL              = 0x35,   // 00000000   rw
	GYRO_REGISTER_TSH_ZH              = 0x36,   // 00000000   rw
	GYRO_REGISTER_TSH_ZL              = 0x37,   // 00000000   rw
	GYRO_REGISTER_INT1_DURATION       = 0x38    // 00000000   rw
} gyro_reg_t;
/*=========================================================================*/

typedef enum
{
	ADF001_SUCCESS = 0,
	ADF001_GYRO_ERR_INIT
}adf001_err_t;

uint16_t adf001_init(void);


#endif /* DRIVERS_LL_ADF001_H_ */

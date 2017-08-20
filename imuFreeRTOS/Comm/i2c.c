/*
 * i2c.c
 *
 *  Created on: Aug 19, 2017
 *      Author: Sumanth
 */

#include "i2c.h"


#define TWI_INSTANCE_ID 0

/*
 * @brief Static Variables
 */

static nrf_drv_twi_t m_i2c = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);;

static bool m_i2c_transfer_complete = false;
/**
 * @brief i2c event handler
 */
/**
 * @brief TWI events handler.
 */
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
	NRF_LOG_INFO("Twi Handler event type %d\r\n", p_event->type);
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                NRF_LOG_INFO("Data has been received\r\n");
                m_i2c_transfer_complete = true;
            }
            m_i2c_transfer_complete = true;
            NRF_LOG_INFO("Data transfer complete\r\n")
            break;
        default:
            break;
    }
}
/**
 * @brief Function initializes i2c drivers
 */
uint16_t i2c_init(i2c_cfg_t *i2c)
{
	uint16_t err_num = 0;
	const nrf_drv_twi_config_t nrf_twi_config = {
			.scl 				= i2c->scl,
			.sda 				= i2c->sda,
			.frequency			= NRF_TWI_FREQ_100K,
			.interrupt_priority = APP_IRQ_PRIORITY_HIGH,
			.clear_bus_init 	= false };

	err_num = nrf_drv_twi_init(&m_i2c, &nrf_twi_config, twi_handler, NULL);
	if(err_num) { NRF_LOG_ERROR("[i2c_init] Failed to initialize i2c [Error Num 0x%02x]\r\n", err_num); }

	nrf_drv_twi_enable(&m_i2c);
	return err_num;
}

/**
 * @brief Function to write data on i2c bus
 */
uint16_t i2c_write(uint8_t *data, uint8_t reg)
{
	uint16_t err_num = 0;

	err_num = nrf_drv_twi_tx(&m_i2c, reg, data, sizeof(data), false);
	if(err_num) { NRF_LOG_INFO("[i2c_write] Failed to write data on i2c bus! [Error Num: 0x%02X]\r\n", err_num); }

	// Wait for Tx Complete Semaphore
	return err_num;
}

/**
 * @brief Function to read data on i2c bus
 */
uint16_t i2c_read(uint8_t *data, uint8_t reg, uint8_t dev_addr)
{
	uint16_t err_num = 0;
	err_num = nrf_drv_twi_tx(&m_i2c, dev_addr, &reg, 1, false);
	if(err_num) { NRF_LOG_INFO("[i2c_write] Failed to write data on i2c bus! [Error Num: 0x%02X]\r\n", err_num); }

	while(m_i2c_transfer_complete == false);
	m_i2c_transfer_complete = false;

	NRF_LOG_INFO("Reading i2c values\r\n");
	err_num = nrf_drv_twi_rx(&m_i2c, dev_addr, data, sizeof(data));
	if(err_num) { NRF_LOG_INFO("[i2c_read] Failed to read data on i2c bus! [Error Num: 0x%02X]\r\n", err_num); }

	while(m_i2c_transfer_complete == false);
	m_i2c_transfer_complete = false;
	// Wait for Rx Complete Semaphore
	return err_num;
}



#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "my_ble.h"
#include "my_i2c.h"
#include "my_board.h"


#define TIMEOUT 	1000000
volatile uint32_t timeout = TIMEOUT;


static const nrf_drv_twi_t twiMaster = NRF_DRV_TWI_INSTANCE(0);

/* Indicates if operation on TWI has ended. */
static volatile bool m_xfer_write_done = false;
static volatile bool m_xfer_read_done = false;

/**
 * @brief TWI events handler.
 */
static void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{       
	switch(p_event->type)
	{
		case NRF_DRV_TWI_EVT_DONE:
			switch(p_event->xfer_desc.type)
			{
				case NRF_DRV_TWI_XFER_TX:
						m_xfer_write_done = true;
						break;
				case NRF_DRV_TWI_XFER_TXTX:
						m_xfer_write_done = true;
						break;
				case NRF_DRV_TWI_XFER_RX:
						m_xfer_read_done = true;
						break;
				case NRF_DRV_TWI_XFER_TXRX:
						m_xfer_read_done = true;
						break;
				default:
						break;
			}
			break;

		/*NACK received after sending the address.*/
		case NRF_DRV_TWI_EVT_ADDRESS_NACK:
			// evt_address_nack	= 1;
			break;
		
		/*Error event: NACK received after sending a data byte.*/
		case NRF_DRV_TWI_EVT_DATA_NACK:
			// evt_data_nack			= 1;
			break;
		
		default:
			break;        
	}   
}

void my_i2c_init(void)
{
    ret_code_t ret_code;
    
	const nrf_drv_twi_config_t config =
    {
       .scl                = I2C_SCL_PIN, 
       .sda                = I2C_SDA_PIN, 
       .frequency          = I2C_FREQUENCY,
       .interrupt_priority = I2C_INT_PRIORITY
		//.clear_bus_init     = false
    };

    ret_code = nrf_drv_twi_init(&twiMaster, &config, twi_handler, NULL);    
    APP_ERROR_CHECK(ret_code);

    nrf_drv_twi_enable(&twiMaster);
}


uint32_t my_i2c_readbyte(uint8_t slave_address, uint8_t read_address, uint8_t *data){
	
	uint8_t i2c_read_data;
	ret_code_t err_code;
	
	timeout = TIMEOUT;
	m_xfer_write_done = false;	//write read_address 
	err_code = nrf_drv_twi_tx(&twiMaster, slave_address, &read_address, 1, false);
	if(err_code != NRF_SUCCESS)
	{
		//loge("RB-1: %d \r\n", err_code);
		return err_code; 
	}
	while(!m_xfer_write_done)
	{	
		--timeout;
		if(!timeout)
		{
			err_code = NRF_ERROR_TIMEOUT;
			//loge("RB-2: %d \r\n", err_code);
			return NRF_ERROR_TIMEOUT;
		}
	}
	
	timeout = TIMEOUT;
	m_xfer_read_done = false; //read data on read_address
	err_code = nrf_drv_twi_rx(&twiMaster, slave_address, &i2c_read_data, sizeof(i2c_read_data));
	if(err_code != NRF_SUCCESS) { 
		
		//loge("RB-3: %d \r\n", err_code);
		return err_code;
	}
	while(!m_xfer_read_done)
	{	
		 --timeout;
		if(!timeout)
		{ 	
			err_code = NRF_ERROR_TIMEOUT;
			//loge("RB-4: %d \r\n", err_code);
			return NRF_ERROR_TIMEOUT;
		}
	}
	*data = i2c_read_data;
	
	return err_code;
}

uint32_t my_i2c_readbytes(uint8_t slave_address, uint8_t read_address, uint8_t *p_data, uint32_t length)
{
	ret_code_t err_code;
	
	timeout = TIMEOUT;
	m_xfer_write_done = false;
	err_code = nrf_drv_twi_tx(&twiMaster, slave_address, &read_address, 1, false);
	if(err_code != NRF_SUCCESS){ 
		//loge("RBS-1: %d \r\n", err_code);
		return err_code;
	}
	while(!m_xfer_write_done)
	{	
		--timeout;
		if(!timeout)
		{
			err_code = NRF_ERROR_TIMEOUT;
			//loge("RBS-2: %d \r\n", err_code);
			return NRF_ERROR_TIMEOUT;
		}
	}	
	
	timeout = TIMEOUT;
	m_xfer_read_done = false;
	err_code = nrf_drv_twi_rx(&twiMaster, slave_address, p_data, length);
	if(err_code != NRF_SUCCESS){ 
		
		//loge("RBS-3: %d \r\n", err_code);
		return err_code;
	}
	while(!m_xfer_read_done)
	{	
		--timeout;
		if(!timeout)
		{
			err_code = NRF_ERROR_TIMEOUT;
			//loge("RBS-4: %d \r\n", err_code);
			return NRF_ERROR_TIMEOUT;
		}
	}	
	
	return err_code;
}

uint32_t my_i2c_writebyte(uint8_t slave_address, uint8_t write_address, uint8_t data){
	
	ret_code_t err_code;
	uint8_t registers[2];

	registers[0] = write_address;
	registers[1] = data;
	
	timeout = TIMEOUT;
	m_xfer_write_done = false;
	err_code = nrf_drv_twi_tx(&twiMaster, slave_address, registers, sizeof(registers), false);
	if(err_code != NRF_SUCCESS)
	{
		//loge("WB-1: %d \r\n", err_code);
		return err_code;
	}
	while(!m_xfer_write_done)
	{
		--timeout;	
		if(!timeout)
		{
			err_code = NRF_ERROR_TIMEOUT;
			//loge("WB-2: %d \r\n", err_code);
			return NRF_ERROR_TIMEOUT;
		}
	}	
	return err_code;
}

uint32_t my_i2c_writebytes(uint8_t slave_address, uint8_t write_address, uint8_t *p_data, uint32_t length){
	
	ret_code_t err_code;
	uint8_t registers[length+1];

	registers[0] = write_address;
	memcpy(&registers[1], p_data, length);
	
	timeout = TIMEOUT;
	m_xfer_write_done = false;
	err_code = nrf_drv_twi_tx(&twiMaster, slave_address, registers, sizeof(registers), false);
	if(err_code != NRF_SUCCESS)
	{
		//loge("WB-1: %d \r\n", err_code);
		return err_code;
	}
	while(!m_xfer_write_done)
	{  
		--timeout;
		if(!timeout)
		{
			err_code = NRF_ERROR_TIMEOUT;
			//loge("WB-2: %d \r\n", err_code);
			return NRF_ERROR_TIMEOUT;
		}
	}	
	return err_code;
}

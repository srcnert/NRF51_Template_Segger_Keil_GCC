#ifndef MY_I2C_H__
#define MY_I2C_H__

#include "nrf_drv_twi.h"

#define I2C_FREQUENCY			NRF_TWI_FREQ_400K
#define I2C_INT_PRIORITY		APP_IRQ_PRIORITY_HIGHEST

void my_i2c_init(void);

uint32_t my_i2c_readbyte(uint8_t slave_address, uint8_t read_address, uint8_t *data);
uint32_t my_i2c_readbytes(uint8_t slave_address, uint8_t read_address, uint8_t *p_data, uint32_t length);

uint32_t my_i2c_writebyte(uint8_t slave_address, uint8_t write_address, uint8_t data);
uint32_t my_i2c_writebytes(uint8_t slave_address, uint8_t write_address, uint8_t *p_data, uint32_t length);

#endif /* __MY_I2C_H */


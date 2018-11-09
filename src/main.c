/*
Sercan ERAT
xx.xx.2018
v1.0.0
SDK 12.3.0 -- SD130v201
*/

/*
Bootloaderin public keyi asagidaki gibidir.
// Public key used to verify DFU images 
__ALIGN(4) const uint8_t pk[64] =
{
    0x9c, 0x8b, 0x7d, 0xb7, 0xd9, 0xeb, 0x34, 0xfa, 0xcf, 0x1e, 0xc0, 0x3f, 0x1b, 0xf2, 0xb9, 0xad, 0x30, 0xe8, 0xf3, 0x11, 0xe1, 0x7b, 0xa6, 0x2e, 0x12, 0x3c, 0x30, 0xad, 0x1c, 0x27, 0x37, 0x3c, 
    0x0d, 0xfb, 0xd1, 0x7d, 0x8e, 0xb0, 0x65, 0x5d, 0x7b, 0xf9, 0xae, 0x8e, 0xa2, 0x1b, 0xad, 0x73, 0x3b, 0x30, 0x68, 0xec, 0x48, 0x49, 0x5e, 0x42, 0xd7, 0x2d, 0x74, 0x68, 0xc6, 0x10, 0x38, 0x6e
};
*/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "sdk_config.h"

#include "nrf_gpio.h"
#include "nrf_delay.h"

#include "main.h"
#include "my_ble.h"
#include "my_timer.h"
#include "my_i2c.h"
#include "my_wdt.h"
#include "my_board.h"
#include "my_gpiote.h"
#include "my_fstorage.h"		

int main(void)
{
  my_board_init();
	// my_wdt_init();
	
	my_board_led_on(LED1);
	my_board_led_on(LED2);
	nrf_delay_ms(1000);
	
	my_fstorage_init();

	my_i2c_init();						// I2C INIT
	my_ble_init();					  // BLUETOOTH INIT

	my_ble_advertising_init();
	my_ble_advertising_start();
	
	my_timer_init(); 				// TIMERS INIT
		
	my_gpiote_init();				// GPIOTE INIT
	my_gpiote_pin_enabled();
	
	//DEBUG
	//logi("DEBUGGER START");
	// *(uint32_t *)~0 = 4; 	 // Hard Fault Example
	// APP_ERROR_CHECK(1);     // App Error Fault Handler Example
  my_board_leds_off(); 

	while(1){
		
		my_ble_power_manage();
	}
}


/**
 * @brief Assert callbacks.
*/
void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
		my_board_led_on(LED2);
		nrf_delay_ms(1000);
		NVIC_SystemReset();
		//while(1);
}

void HardFault_Handler(void)  
{
		my_board_led_on(LED2);
		nrf_delay_ms(1000);
		NVIC_SystemReset();
    //while(1);
}


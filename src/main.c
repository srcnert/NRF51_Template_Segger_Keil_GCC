/*
Sercan ERAT
xx.xx.2018
v1.0.0
SDK 12.3.0 -- SD130v201
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


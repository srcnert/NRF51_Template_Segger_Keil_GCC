#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrf_drv_gpiote.h"

#include "my_gpiote.h"
#include "my_timer.h"
#include "my_ble.h"

volatile bool intterupt_pin_flag = false;

static void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{ 
		intterupt_pin_flag = true;		
}


void my_gpiote_init(void){
	
		uint32_t err_code;
	
		err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(false);
    in_config.pull =  NRF_GPIO_PIN_NOPULL;
    err_code = nrf_drv_gpiote_in_init(INT_PIN, &in_config, in_pin_handler);
    APP_ERROR_CHECK(err_code);
}

void my_gpiote_pin_enabled(void){

	nrf_drv_gpiote_in_event_enable(INT_PIN, true);
}

void my_gpiote_pin_disabled(void){

	nrf_drv_gpiote_in_event_disable(INT_PIN);
}

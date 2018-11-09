#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "app_util_platform.h"

#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_adc.h"
#include "nrf_drv_adc.h"

#include "my_board.h"

void my_board_init(void)
{
	nrf_gpio_cfg_output(LED1);
	nrf_gpio_cfg_output(LED2);
	
	nrf_gpio_cfg_output(GPIO_2_PIN);
	nrf_gpio_pin_clear(LED1);
}

void my_board_led_on(uint8_t led_number)
{
		switch(led_number)
		{
			case LED1:
				nrf_gpio_pin_set(LED1);
				break;
			case LED2:
				nrf_gpio_pin_set(LED2);
				break;
		}		
}	

void my_board_led_off(uint8_t led_number)
{
		switch(led_number)
		{
			case LED1:
				nrf_gpio_pin_clear(LED1);
				break;
			case LED2:
				nrf_gpio_pin_clear(LED2);
				break;
		}		
}	

void my_board_led_toggle(uint8_t led_number)
{
		switch(led_number)
		{
			case LED1:
				nrf_gpio_pin_toggle(LED1);
				break;
			case LED2:
				nrf_gpio_pin_toggle(LED2);
				break;
		}		
}	

void my_board_leds_on(void)
{
	nrf_gpio_pin_set(LED1);
	nrf_gpio_pin_set(LED2);		
}	

void my_board_leds_off(void)
{
	nrf_gpio_pin_clear(LED1);
	nrf_gpio_pin_clear(LED2);		
}

void my_board_leds_toggle(void)
{
	nrf_gpio_pin_toggle(LED1);
	nrf_gpio_pin_toggle(LED2);		
}

uint8_t my_board_get_battery_pct(void)
{
	volatile uint32_t adc_sample;
	volatile uint8_t bat_pct;
	
	const nrf_adc_config_t nrf_adc_config = {	NRF_ADC_CONFIG_RES_10BIT,               \
												NRF_ADC_CONFIG_SCALING_SUPPLY_ONE_THIRD, \
												NRF_ADC_CONFIG_REF_VBG };

  // Initialize and configure ADC
	nrf_adc_configure( (nrf_adc_config_t *) &nrf_adc_config);
	NVIC_SetPriority(ADC_IRQn, APP_IRQ_PRIORITY_LOW);

	adc_sample= nrf_adc_convert_single	(	NRF_ADC_CONFIG_INPUT_DISABLED	)	;
	nrf_adc_stop();
	if (adc_sample >=880)
		adc_sample=880;
	else if (adc_sample <= 596)
		adc_sample=596;

	adc_sample=adc_sample-596;

	adc_sample=(adc_sample*100);
	adc_sample=adc_sample/284;
	bat_pct=adc_sample;
	return bat_pct;
}

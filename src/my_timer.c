#include <stdint.h>
#include "app_timer.h"
#include "nrf_gpio.h"

#include "main.h"
#include "my_ble.h"
#include "my_board.h"
#include "my_timer.h"
#include "my_gpiote.h"


APP_TIMER_DEF(IDLE_TIMER);
APP_TIMER_DEF(ADVERTISING_STOP_TIMER);

#define IDLE_TIME						1000*60*3
	
static void IDLE_TIMER_handler(void * p_context)
{
	//logi("IDLE TIMER");
} 

static void ADVERTISING_STOP_TIMER_handler(void * p_context){
	
	if(isAdvertising == true) 
	{
		my_ble_advertising_stop();
		//logi("ADV STOP");
	}	
}

void my_timer_init() {
	
	uint32_t err_code;
	
	//Create Timers
	err_code = app_timer_create(&IDLE_TIMER, APP_TIMER_MODE_REPEATED, IDLE_TIMER_handler);
  APP_ERROR_CHECK(err_code);	
	
	err_code = app_timer_create(&ADVERTISING_STOP_TIMER, APP_TIMER_MODE_SINGLE_SHOT, ADVERTISING_STOP_TIMER_handler);
  APP_ERROR_CHECK(err_code);
}

void my_timer_idle_start(void) 
{	
	app_timer_stop(IDLE_TIMER);
	app_timer_start(IDLE_TIMER, APP_TIMER_TICKS(IDLE_TIME, APP_TIMER_PRESCALER), NULL);
}

void my_timer_idle_stop(void) 
{	
	app_timer_stop(IDLE_TIMER);
}

void my_timer_adv_stop_start(uint32_t ADV_DURATION) {
	
	app_timer_stop(ADVERTISING_STOP_TIMER);
	app_timer_start(ADVERTISING_STOP_TIMER, APP_TIMER_TICKS(ADV_DURATION, APP_TIMER_PRESCALER), NULL);
}


void my_timer_adv_stop_stop() {
	
	app_timer_stop(ADVERTISING_STOP_TIMER);
}


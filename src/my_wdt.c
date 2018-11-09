#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nrf.h"
#include "nrf_drv_wdt.h"
#include "app_util_platform.h"

nrf_drv_wdt_channel_id m_channel_id;

void wdt_event_handler(void)
{
	//NOTE: The max amount of time we can spend in WDT interrupt is two cycles of 32768[Hz] clock - after that, reset occurs
}

void my_wdt_init(void)
{
	  //Configure WDT.
		uint32_t err_code;
	
    nrf_drv_wdt_config_t config = NRF_DRV_WDT_DEAFULT_CONFIG;
    err_code = nrf_drv_wdt_init(&config, wdt_event_handler);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_wdt_channel_alloc(&m_channel_id);
    APP_ERROR_CHECK(err_code);
    nrf_drv_wdt_enable();
}

void my_wdt_kick(void)
{
    nrf_drv_wdt_channel_feed(m_channel_id);
}	

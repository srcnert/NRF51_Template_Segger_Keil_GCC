#include <stdint.h>

#include "fstorage.h"
#include "nrf_gpio.h"

#include "my_fstorage.h"
#include "my_ble.h"

#define NUM_PAGES 4

static volatile uint8_t fs_callback_flag;

//fstorage
static void fs_evt_handler(fs_evt_t const * const evt, fs_ret_t result)
{
    if (result != FS_SUCCESS)
    {
        
    }
		else
		{
				// Fstorage command successfully completed
				fs_callback_flag = 0;
		}
}

FS_REGISTER_CFG(fs_config_t fs_config) =
		{
			  .callback  = fs_evt_handler, // Function for event callbacks.
				.num_pages = NUM_PAGES,      // Number of physical flash pages required.
				.priority  = 0xFE            // Priority for flash usage.
		};

void my_fstorage_init(void){
	
		fs_ret_t ret = fs_init();
		APP_ERROR_CHECK(ret);

}

// This function erase 1 page of the storage
void my_fstorage_erase(uint16_t num_pages)
{		
		fs_callback_flag = 1;
		fs_ret_t ret = fs_erase(&fs_config, (fs_config.p_start_addr + num_pages*256), 1, NULL);
		APP_ERROR_CHECK(ret);
		while(fs_callback_flag == 1)  { my_ble_power_manage(); }	
}

// This function erase all of the storage
void my_fstorage_erase_all(void)
{	
		fs_callback_flag = 1;
		fs_ret_t ret = fs_erase(&fs_config, (fs_config.p_start_addr), NUM_PAGES, NULL);
		APP_ERROR_CHECK(ret);
		while(fs_callback_flag == 1)  { my_ble_power_manage(); }	
}

void my_fstorage_read(uint32_t *data, uint16_t array_position)
{	
		*data = *(fs_config.p_start_addr + array_position);
}

void my_fstorage_write(uint32_t  data, uint16_t array_position){
													 
		fs_callback_flag = 1;
		fs_ret_t ret = fs_store(&fs_config, (fs_config.p_start_addr  + array_position), &data, 1, NULL);
	    APP_ERROR_CHECK(ret);
		while(fs_callback_flag == 1)  { my_ble_power_manage(); }
}

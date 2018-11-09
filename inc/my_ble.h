#ifndef __MY_BLE_H
#define	__MY_BLE_H

#include <stdint.h>
#include <string.h>

#include "nordic_common.h"
#include "nrf.h"
#include "ble_bas.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "softdevice_handler.h"
#include "app_timer.h"
#include "app_util_platform.h"

#include "my_ble.h"


#define APP_TIMER_PRESCALER             0                                           /**< Value of the RTC1 PRESCALER register. */

extern uint8_t adv_data[4];
extern volatile bool isAdvertising;

void my_ble_advertising_init(void);
void my_ble_advertising_start(void);
void my_ble_advertising_stop(void);

void my_ble_power_manage(void);
void my_ble_init(void);

int8_t my_ble_get_dB(uint8_t value);

#endif /* __MY_BLE_H */

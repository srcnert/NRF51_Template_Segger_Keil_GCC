#ifndef __MY_GPIOTE_H
#define	__MY_GPIOTE_H

#include "nrf_drv_gpiote.h"

#define INT_PIN 9

extern volatile bool interrupt_pin_flag;

void my_gpiote_init(void);
void my_gpiote_pin_enabled(void);
void my_gpiote_pin_disabled(void);

#endif /* __MY_GPIOTE_H */

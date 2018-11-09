#ifndef MY_BOARD_H__
#define MY_BOARD_H__

#define HEADER0									0x5A
#define HEADER1									0xDE
#define HEADER2									0x14

#define REED_SW_PIN								3
#define	BUTTON_PIN								22
#define GPIO_0_PIN								24
#define GPIO_1_PIN								25
#define	GPIO_2_PIN								0
#define GPIO_3_PIN								1
#define GPIO_4_PIN								2

#define INT_PIN										9
#define I2C_SDA_PIN								GPIO_0_PIN
#define I2C_SCL_PIN								GPIO_1_PIN
#define LED1											21
#define	LED2											22

uint8_t my_board_get_battery_pct(void);

void my_board_init(void);
void my_board_led_on(uint8_t led_number);
void my_board_led_off(uint8_t led_number);
void my_board_led_toggle(uint8_t led_number);

void my_board_leds_on(void);
void my_board_leds_off(void);
void my_board_leds_toggle(void);

												
#endif // MY_BOARD_H__



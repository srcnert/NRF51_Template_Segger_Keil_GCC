#ifndef __MY_TIMER_H
#define	__MY_TIMER_H

void my_timer_init(void);

void my_timer_idle_start(void);
void my_timer_idle_stop(void);

void my_timer_adv_stop_start(uint32_t ADV_DURATION);
void my_timer_adv_stop_stop(void);

#endif /* __MY_TIMER_H */

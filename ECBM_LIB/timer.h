#ifndef _ECBM_TIMER_H_
#define _ECBM_TIMER_H_


#define ECBM_TIMER0_EN (1)

#define ECBM_TIMER0_TMOD (0x00)

#define ECBM_TIMER0_AUXR (0x80)

#define ECBM_TIMER0_INTCLKO (0x00)

#define ECBM_TIMER0_COUNT (65500)

#define ECBM_TIMER0_IT_EN (1)


#define ECBM_TIMER1_EN (0)

#define ECBM_TIMER1_TMOD (0x00)

#define ECBM_TIMER1_AUXR (0x40)

#define ECBM_TIMER1_INTCLKO (0x00)

#define ECBM_TIMER1_COUNT (65535)

#define ECBM_TIMER1_IT_EN (0)


#define ECBM_TIMER2_EN (0)

#define ECBM_TIMER2_AUXR (0x04)

#define ECBM_TIMER2_INTCLKO (0x00)

#define ECBM_TIMER2_COUNT (500)

#define ECBM_TIMER2_IT_EN (0)


#define ECBM_TIMER3_EN (0)

#define ECBM_TIMER3_T4T3M (0x00)

#define ECBM_TIMER3_COUNT (65535)

#define ECBM_TIMER3_IT_EN (0)


#define ECBM_TIMER4_EN (0)

#define ECBM_TIMER4_T4T3M (0x00)

#define ECBM_TIMER4_COUNT (10000)

#define ECBM_TIMER4_IT_EN (0)



#include "ecbm_core.h"


extern void timer_start(u8 id);

extern void timer_stop(u8 id);

extern void timer_out(u8 id,u8 en);

extern void timer_init(void);

extern void timer_set_timer_mode(u8 id,u16 us);

extern void timer_set_value(u8 id,u16 value);

extern u16 timer_get_value(u8 id);

extern void timer0_it_callback(void);

extern void timer1_it_callback(void);

extern void timer2_it_callback(void);

extern void timer3_it_callback(void);

extern void timer4_it_callback(void);
#endif



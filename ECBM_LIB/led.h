#ifndef _ECBM_LED_H_
#define _ECBM_LED_H_












#define ECBM_LED_COM_EN (0x00)










#define ECBM_LED_SEGL_EN (0x00)








#define ECBM_LED_SEGH_EN (0x00)














#define ECBM_LED_CTRL (0x00)


#define ECBM_LED_CLK_DIV (1)



#include "ecbm_core.h"

#define LED_MODE_DC     (0x00)
#define LED_MODE_DA     (0x10)
#define LED_MODE_DCA    (0x20)

#define LED_DUTY_8_8    (0x00)
#define LED_DUTY_7_8    (0x01)
#define LED_DUTY_6_8    (0x02)
#define LED_DUTY_5_8    (0x03)
#define LED_DUTY_4_8    (0x04)
#define LED_DUTY_3_8    (0x05)
#define LED_DUTY_2_8    (0x06)
#define LED_DUTY_1_8    (0x07)


extern void led_init(void);

extern void led_start(void);

extern void led_stop(void);

extern void led_set_mode(u8 mode);

extern void led_set_duty(u8 duty);

extern void led_set_freq(u8 freq);
#endif



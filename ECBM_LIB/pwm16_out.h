#ifndef _ECBM_PWM16_OUT_H_
#define _ECBM_PWM16_OUT_H_























#define ECBM_PWM16_OUT_GROUPA_PIN_SEL (192)







#define ECBM_PWM16_OUT_GROUPA_EXT_PIN_SEL (0)












#define ECBM_PWM16_OUT_GROUPA_PIN_EN (3)






















#define ECBM_PWM16_OUT_GROUPA_PIN12_POL (13)
















#define ECBM_PWM16_OUT_GROUPA_PIN34_POL (0)











#define ECBM_PWM16_OUT_GROUPA_BKR   (80)










#define ECBM_PWM16_OUT_GROUPA_IOAUX   (3)















#define ECBM_PWM16_OUT_GROUPA_DTR (0)



























#define ECBM_PWM16_OUT_GROUPA_PIN_OIS (0)





#define ECBM_PWM16_OUT_GROUPA_FREQ (0)

#define ECBM_PWM16_OUT_GROUPA_ARR (11)

#define ECBM_PWM16_OUT_GROUPA_CH1_DUTY (5)

#define ECBM_PWM16_OUT_GROUPA_CH2_DUTY (0)

#define ECBM_PWM16_OUT_GROUPA_CH3_DUTY (0)

#define ECBM_PWM16_OUT_GROUPA_CH4_DUTY (0)












#define ECBM_PWM16_OUT_GROUPA_CR1     (0)
























#define ECBM_PWM16_OUT_GROUPB_PIN_SEL (0)






#define ECBM_PWM16_OUT_GROUPB_EXT_PIN_SEL (0)








#define ECBM_PWM16_OUT_GROUPB_PIN_EN (0)














#define ECBM_PWM16_OUT_GROUPB_PIN56_POL (15)








#define ECBM_PWM16_OUT_GROUPB_PIN78_POL (0)











#define ECBM_PWM16_OUT_GROUPB_BKR   (0)






#define ECBM_PWM16_OUT_GROUPB_IOAUX   (0)















#define ECBM_PWM16_OUT_GROUPB_DTR (0)















#define ECBM_PWM16_OUT_GROUPB_PIN_OIS (0)





#define ECBM_PWM16_OUT_GROUPB_FREQ (0)

#define ECBM_PWM16_OUT_GROUPB_ARR (0)

#define ECBM_PWM16_OUT_GROUPB_CH5_DUTY (0)

#define ECBM_PWM16_OUT_GROUPB_CH6_DUTY (0)

#define ECBM_PWM16_OUT_GROUPB_CH7_DUTY (0)

#define ECBM_PWM16_OUT_GROUPB_CH8_DUTY (0)












#define ECBM_PWM16_OUT_GROUPB_CR1     (0)




#include "ecbm_core.h"


extern void pwm16_out_init(void);

extern void pwm16_out_groupa_start(void);
extern void pwm16_out_groupb_start(void);

extern void pwm16_out_groupa_stop(void);
extern void pwm16_out_groupb_stop(void);

extern void pwm16_out_set_freq(u8 ch,u32 freq);

extern void pwm16_out_set_duty(u8 ch,u16 ch_duty);

extern void pwm16_out_pulse_start(u8 ch,u8 ch_count);

extern void pwm16_out_wave_start(u8 ch,u16 ch_duty);
#endif



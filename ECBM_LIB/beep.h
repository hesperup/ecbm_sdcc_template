#ifndef _ECBM_BEEP_H_
#define _ECBM_BEEP_H_







#define ECBM_BEEP_IO_WORK (0)









#define ECBM_BEEP_IO_PORT (0xB0)









#define ECBM_BEEP_IO_PIN  (0x03)



#define ECBM_BEEP_ON_TIME_MAX  (8)



#define ECBM_BEEP_OFF_TIME_MAX  (12)



#include "ecbm_core.h"


extern void beep_set_class(u8 on_time,u8 off_time);

extern void beep_start(u8 count);

extern void beep_idle(void);
#endif


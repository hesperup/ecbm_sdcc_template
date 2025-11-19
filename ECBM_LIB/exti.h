#ifndef _ECBM_EXTI_H_
#define _ECBM_EXTI_H_






#define ECBM_EXTI0_EN (0)





#define ECBM_EXTI0_MODE (1)


#define ECBM_EXTI0_INIT (1)




#define ECBM_EXTI1_EN (0)





#define ECBM_EXTI1_MODE (0)


#define ECBM_EXTI1_INIT (1)




#define ECBM_EXTI2_EN (0)


#define ECBM_EXTI2_INIT (1)




#define ECBM_EXTI3_EN (0)


#define ECBM_EXTI3_INIT (1)




#define ECBM_EXTI4_EN (0)


#define ECBM_EXTI4_INIT (1)




#include "ecbm_core.h"

#define EXTI_MODE_UP_DOWN   (0)
#define EXTI_MODE_DOWN      (1)


extern void exti_init(void);

extern void exti_start(u8 id);

extern void exti_stop(u8 id);

extern void exti_set_mode(u8 id,u8 mode);

extern void exti0_it_callback(void);

extern void exti1_it_callback(void);

extern void exti2_it_callback(void);

extern void exti3_it_callback(void);

extern void exti4_it_callback(void);
#endif



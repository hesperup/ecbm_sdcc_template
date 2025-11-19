#ifndef _ECBM_PCA_H_
#define _ECBM_PCA_H_

















#define ECBM_PCA_CMOD (0x08)

#define ECBM_PCA_CALLBACK_EN (0)





















#define ECBM_PCA_IO (0x00)



#define ECBM_PCA0_EN (0)









#define ECBM_PCA0_MODE (1)




#define ECBM_PCA0_UP_DOWN (0x00)



#define ECBM_PCA0_TIMER_AUTO_EN (0)

#define ECBM_PCA0_CALLBACK_EN (0)




#define ECBM_PCA1_EN (0)









#define ECBM_PCA1_MODE (5)




#define ECBM_PCA1_UP_DOWN (0x30)



#define ECBM_PCA1_TIMER_AUTO_EN (0)

#define ECBM_PCA1_CALLBACK_EN (1)




#define ECBM_PCA2_EN (0)









#define ECBM_PCA2_MODE (1)




#define ECBM_PCA2_UP_DOWN (0x00)



#define ECBM_PCA2_TIMER_AUTO_EN (0)

#define ECBM_PCA2_CALLBACK_EN (0)




#define ECBM_PCA3_EN (0)









#define ECBM_PCA3_MODE (3)




#define ECBM_PCA3_UP_DOWN (0x00)



#define ECBM_PCA3_TIMER_AUTO_EN (0)

#define ECBM_PCA3_CALLBACK_EN (0)




#include "ecbm_core.h"

#define PCA_ECOMn_1 (0x40)
#define PCA_ECOMn_0 (0xBF)

#define PCA_CAPPn_1 (0x20)
#define PCA_CAPPn_0 (0xDF)

#define PCA_CAPNn_1 (0x10)
#define PCA_CAPNn_0 (0xEF)

#define PCA_MATn_1  (0x08)
#define PCA_MATn_0  (0xF7)

#define PCA_TOGn_1  (0x04)
#define PCA_TOGn_0  (0xFB)

#define PCA_PWMn_1  (0x02)
#define PCA_PWMn_0  (0xFD)

#define PCA_ECCFn_1 (0x01)
#define PCA_ECCFn_0 (0xFE)

#define PCA_PIN_P12_P17_P16_P15_P14  (0x00)
#define PCA_PIN_P22_P23_P24_P25_P26  (0x10)
#define PCA_PIN_P74_P70_P71_P72_P73  (0x20)
#define PCA_PIN_P35_P33_P32_P31_P30  (0x30)

#define PCA_PIN_P12_P11_P10_P37  (0x00)
#define PCA_PIN_P34_P35_P36_P37  (0x10)
#define PCA_PIN_P24_P25_P26_P27  (0x20)

#define PCA_PIN_P55_P32_P33_P54  (0x00)
#define PCA_PIN_P55_P31_P33_P54  (0x10)
#define PCA_PIN_P31_P32_P33_P55  (0x20)

#define PCA_PIN_P13_P11_P10_P37  (0x00)
#define PCA_PIN_P34_P35_P36_P37  (0x10)
#define PCA_PIN_P54_P13_P14_P15  (0x20)

extern u8  pca_mode_0_gu8;
extern u8  pca_mode_1_gu8;
extern u8  pca_mode_2_gu8;
extern u8  pca_mode_3_gu8;

extern u16 pca_timer_count_0_gu16;
extern u16 pca_timer_count_1_gu16;
extern u16 pca_timer_count_2_gu16;
extern u16 pca_timer_count_3_gu16;

extern u16 pca_timer_add_0_gu16;
extern u16 pca_timer_add_1_gu16;
extern u16 pca_timer_add_2_gu16;
extern u16 pca_timer_add_3_gu16;


extern void pca_init(void);

extern void pca_set_io(u8 io);

extern void pca_set_mode(u8 id,u8 mode);

extern void pca_set_timer(u8 id,u16 count);

extern void pca_set_duty(u8 id,u16 duty);

extern void pca_timer_callback(void);

extern void pca0_callback(void);

extern void pca1_callback(void);

extern void pca2_callback(void);

extern void pca3_callback(void);
#endif



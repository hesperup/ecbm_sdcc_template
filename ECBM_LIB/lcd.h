#ifndef _ECBM_LCD_H_
#define _ECBM_LCD_H_















#define ECBM_LCD_CFG (0x00)


#define ECBM_LCD_DBLEN (2)



#define ECBM_LCD_FRAMERATE (60)



#define ECBM_LCD_BLANKRATE (1)





#define ECBM_LCD_CR (0)









#define ECBM_LCD_COMX_EN (0)



#define ECBM_LCD_SEG0_EN (0)



#define ECBM_LCD_CFG2_SEG0 (0)


#define ECBM_LCD_SEG1_EN (0)



#define ECBM_LCD_CFG2_SEG1 (0)


#define ECBM_LCD_SEG2_EN (0)



#define ECBM_LCD_CFG2_SEG2 (0)


#define ECBM_LCD_SEG3_EN (0)



#define ECBM_LCD_CFG2_SEG3 (0)









#define ECBM_LCD_SEGON1 (0)
















#define ECBM_LCD_SEGON2 (0)
















#define ECBM_LCD_SEGON3 (0)
















#define ECBM_LCD_SEGON4 (0)
















#define ECBM_LCD_SEGON5 (0)




#include "ecbm_core.h"


extern void lcd_init(void);

extern void lcd_write(u8 com,u8 group,u8 dat);

#endif



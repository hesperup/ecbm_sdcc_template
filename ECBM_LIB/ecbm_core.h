#ifndef _ECBM_CORE_H_
#define _ECBM_CORE_H_


#define ECBM_FVN (3)
#define ECBM_RVN (6)

#define ECBM_BVN (7)

#define SYSTEM_CLEAR_XDATA_LEN  (0)

#define ECBM_SYSCLK_SETTING (24000000UL)


#define ECBM_SYSCLK_OUT_EN (0)



#define ECBM_SYSLCK_OUT_PIN (1)










#define ECBM_SYSCLK_OUT_SETTING_FA (0x18)




#define ECBM_SYSCLK_OUT_SETTING_GH (0)




#define ECBM_MCU_CHECK_EN  (0)





#define ECBM_POWER_LIB_EN (1)


#define ECBM_UART_LIB_EN (0)



#define ECBM_AUTO_DOWNLOAD_EN  (0)



#define ECBM_EXTI_LIB_EN (1)


#define ECBM_TIMER_LIB_EN (1)


#define ECBM_EEPROM_LIB_EN (0)


#define ECBM_SPI_LIB_EN (0)


#define ECBM_IIC_LIB_EN (0)


#define ECBM_ADC_LIB_EN (0)


#define ECBM_CMP_LIB_EN (0)


#define ECBM_MDU16_LIB_EN (0)


#define ECBM_PCA_LIB_EN (0)


#define ECBM_PWM_LIB_EN (0)


#define ECBM_PWM16_OUT_LIB_EN (0)


#define ECBM_LCM_LIB_EN (0)


#define ECBM_LED_LIB_EN (0)


#define ECBM_LCD_LIB_EN (0)







#define ECBM_DELAY_EN (1)



#define ECBM_PRINTF_EN (0)



#define ECBM_STRING_EN (0)



#define ECBM_SOFTSPI_LIB_EN (0)



#define ECBM_SOFTIIC_LIB_EN (0)




#define ECBM_EDS_LIB_EN (0)


#define ECBM_10MS_EN (0)






#define ECBM_10MS_TIMER (0)



#define ECBM_STREAM_LIB_EN (0)


#define ECBM_BEEP_EN    (0)





#include "ecbm_reg.h"

#ifndef __SDCC
#include "intrins.h"
#endif
#include "STDARG.H"
#if (ECBM_PRINTF_EN)
#include "stdio.h"
#endif


#define LED_ON    LED=0;
#define LED_OFF   LED=1;
#define LED_BLINK LED=!LED;


#define REG_BGV   read_idata_u16(0xEF)
#define REG_ID(x) read_idata_u8 (0xF1+x)

#define io2port(n) ((n)>>4)
#define io2pin(n)  (0x01<<((n)&0x0f))

#include "gpio.h"
#include "power.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"
#include "eeprom.h"
#include "spi.h"
#include "soft_spi.h"
#include "iic.h"
#include "soft_iic.h"
#include "adc.h"
#include "cmp.h"
#include "mdu16.h"
#include "pca.h"
#include "lcm.h"
#include "pwm.h"
#include "pwm16_out.h"
#include "led.h"
#include "lcd.h"
#include "nvic.h"
#include "stream.h"
#include "stream_fur.h"
#include "stream_modbus.h"

#include "stream_ecp.h"
#include "eds.h"
#include "beep.h"

extern bit     auto_download_en_gb;
extern u8 data auto_download_old_char_gdu8;
extern u8 data auto_download_char_count_gdu8;


extern void delay_ms(u16 ms);

extern void delay_us(u16 us);

extern u16  delay_set_us(u16 us);

extern void system_uart_reset(void);

extern void system_check(void);


extern void system_init(void);

extern u16 str_find(s8 * dest,s8 * key);

extern u8 str_read_pin(s8 * str,u16 pos);

extern u16 str_read_u16(s8 * str,u16 pos);

extern u8 str_push_len(u8 * dest,u16 dlen,u8 * key,u16 klen);
#endif



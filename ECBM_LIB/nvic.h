#ifndef _ECBM_NVIC_H_
#define _ECBM_NVIC_H_





#define ECBM_NVIC_FUNCTION_EN (0)






#define ECBM_NVIC_EXTI0_PRIORITY (0)






#define ECBM_NVIC_TIMER0_PRIORITY (0)






#define ECBM_NVIC_EXTI1_PRIORITY (0)






#define ECBM_NVIC_TIMER1_PRIORITY (0)






#define ECBM_NVIC_UART1_PRIORITY (0)






#define ECBM_NVIC_ADC_PRIORITY (0)






#define ECBM_NVIC_LVD_PRIORITY (0)






#define ECBM_NVIC_PCA_PRIORITY (0)






#define ECBM_NVIC_UART2_PRIORITY (0)






#define ECBM_NVIC_SPI_PRIORITY (0)



#define ECBM_NVIC_EXTI2_PRIORITY (0)



#define ECBM_NVIC_EXTI3_PRIORITY (0)



#define ECBM_NVIC_TIMER2_PRIORITY (0)






#define ECBM_NVIC_EXTI4_PRIORITY (0)






#define ECBM_NVIC_UART3_PRIORITY (0)






#define ECBM_NVIC_UART4_PRIORITY (0)



#define ECBM_NVIC_TIMER3_PRIORITY (0)



#define ECBM_NVIC_TIMER4_PRIORITY (0)






#define ECBM_NVIC_CMP_PRIORITY (0)






#define ECBM_NVIC_PWM0_PRIORITY (0)






#define ECBM_NVIC_PWM0FD_PRIORITY (0)






#define ECBM_NVIC_IIC_PRIORITY (0)






#define ECBM_NVIC_USB_PRIORITY (0)






#define ECBM_NVIC_PWMA_PRIORITY (0)






#define ECBM_NVIC_PWMB_PRIORITY (0)






#define ECBM_NVIC_PWM1_PRIORITY (0)






#define ECBM_NVIC_PWM2_PRIORITY (0)






#define ECBM_NVIC_PWM3_PRIORITY (0)






#define ECBM_NVIC_PWM4_PRIORITY (0)






#define ECBM_NVIC_PWM5_PRIORITY (0)






#define ECBM_NVIC_PWM2FD_PRIORITY (0)






#define ECBM_NVIC_PWM4FD_PRIORITY (0)






#define ECBM_NVIC_TKSU_PRIORITY (0)






#define ECBM_NVIC_RTC_PRIORITY (0)






#define ECBM_NVIC_P0INT_PRIORITY (0)






#define ECBM_NVIC_P1INT_PRIORITY (0)






#define ECBM_NVIC_P2INT_PRIORITY (0)






#define ECBM_NVIC_P3INT_PRIORITY (0)






#define ECBM_NVIC_P4INT_PRIORITY (0)






#define ECBM_NVIC_P5INT_PRIORITY (0)






#define ECBM_NVIC_P6INT_PRIORITY (0)






#define ECBM_NVIC_P7INT_PRIORITY (0)






#define ECBM_NVIC_P8INT_PRIORITY (0)






#define ECBM_NVIC_P9INT_PRIORITY (0)






#define ECBM_NVIC_DMA_MEM_PRIORITY (0)






#define ECBM_NVIC_DMA_ADC_PRIORITY (0)






#define ECBM_NVIC_DMA_SPI_PRIORITY (0)






#define ECBM_NVIC_DMA_UART1_TX_PRIORITY (0)






#define ECBM_NVIC_DMA_UART1_RX_PRIORITY (0)






#define ECBM_NVIC_DMA_UART2_TX_PRIORITY (0)






#define ECBM_NVIC_DMA_UART2_RX_PRIORITY (0)






#define ECBM_NVIC_DMA_UART3_TX_PRIORITY (0)






#define ECBM_NVIC_DMA_UART3_RX_PRIORITY (0)






#define ECBM_NVIC_DMA_UART4_TX_PRIORITY (0)






#define ECBM_NVIC_DMA_UART4_RX_PRIORITY (0)






#define ECBM_NVIC_DMA_LCM_PRIORITY (0)






#define ECBM_NVIC_LCM_PRIORITY (0)



#include "ecbm_core.h"


extern void nvic_set_priority(void);

extern void p0_int_callback(void);

extern void p1_int_callback(void);

extern void p2_int_callback(void);

extern void p3_int_callback(void);

extern void p4_int_callback(void);

extern void p5_int_callback(void);

extern void p6_int_callback(void);

extern void p7_int_callback(void);

extern void p8_int_callback(void);

extern void p9_int_callback(void);

extern void bmm_mem_callback(void);

extern void bmm_adc_callback(void);

extern void bmm_spi_callback(void);

extern void bmm_u1tx_callback(void);

extern void bmm_u1rx_callback(void);

extern void bmm_u2tx_callback(void);

extern void bmm_u2rx_callback(void);

extern void bmm_u3tx_callback(void);

extern void bmm_u3rx_callback(void);

extern void bmm_u4tx_callback(void);

extern void bmm_u4rx_callback(void);

extern void bmm_lcm_callback(void);

extern void lcm_it_callback(void);
#endif



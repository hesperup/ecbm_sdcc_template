#ifndef _ECBM_ADC_H_
#define _ECBM_ADC_H_





















#define ECBM_ADC_CH0_EN (0)















#define ECBM_ADC_CH1_EN (0)















#define ECBM_ADC_CH2_EN (0)















#define ECBM_ADC_CH3_EN (0)















#define ECBM_ADC_CH4_EN (0)















#define ECBM_ADC_CH5_EN (0)















#define ECBM_ADC_CH6_EN (0)















#define ECBM_ADC_CH7_EN (0)















#define ECBM_ADC_CH8_EN (0)















#define ECBM_ADC_CH9_EN (0)















#define ECBM_ADC_CH10_EN (0)















#define ECBM_ADC_CH11_EN (0)















#define ECBM_ADC_CH12_EN (0)















#define ECBM_ADC_CH13_EN (0)















#define ECBM_ADC_CH14_EN (0)

















#define ECBM_ADC_CFG (47)


#define ECBM_ADC_8BIT (0)

#define ECBM_ADC_IT_EN (0)



#define ECBM_ADC_PWM_EN (0)











#define ECBM_ADC_EXCFG (0x00)





#include "ecbm_core.h"


#if     ((ECBM_MCU&0x0000F0)==0x0000C0)
#   define  ECBM_MCU_ADC_MAX  (4096.0f)
#elif   ((ECBM_MCU&0x0000F0)==0x0000A0)
#   define  ECBM_MCU_ADC_MAX  (1024.0f)
#else
#   define  ECBM_MCU_ADC_MAX  (1.0f)
#endif

#if (ECBM_MCU==0x2405C2)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#elif   (ECBM_MCU==0x2805C4)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#elif   (ECBM_MCU==0x2815C4)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#elif   (ECBM_MCU==0x3103A2)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x30)
#   define  A09 (0x31)
#   define  A10 (0x32)
#   define  A11 (0x33)
#   define  A12 (0x34)
#   define  A13 (0x35)
#   define  A14 (0x36)
#elif   (ECBM_MCU==0x3102A1)
#   define  A00 (0x30)
#   define  A01 (0x31)
#   define  A02 (0x32)
#   define  A03 (0x33)
#   define  A04 (0x54)
#   define  A05 (0x55)
#elif   (ECBM_MCU==0x3103A1)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x54)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x30)
#   define  A09 (0x31)
#   define  A10 (0x32)
#   define  A11 (0x33)
#   define  A12 (0x34)
#   define  A13 (0x35)
#   define  A14 (0x36)
#elif   (ECBM_MCU==0x3205A2)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#elif   (ECBM_MCU==0x3205A4)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#elif   (ECBM_MCU==0x4103A2)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A08 (0x30)
#   define  A09 (0x31)
#   define  A10 (0x32)
#   define  A11 (0x33)
#   define  A12 (0x34)
#   define  A13 (0x35)
#   define  A14 (0x36)
#elif   (ECBM_MCU==0x4105A2)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#elif   (ECBM_MCU==0x4205C4)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#elif   (ECBM_MCU==0x4305C2)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#elif   (ECBM_MCU==0x4305C4)
#   define  A00 (0x10)
#   define  A01 (0x11)
#   define  A02 (0x12)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#elif   (ECBM_MCU==0x4805C4)
#   define  A01 (0x11)
#   define  A02 (0x54)
#   define  A03 (0x13)
#   define  A04 (0x14)
#   define  A05 (0x15)
#   define  A06 (0x16)
#   define  A07 (0x17)
#   define  A08 (0x00)
#   define  A09 (0x01)
#   define  A10 (0x02)
#   define  A11 (0x03)
#   define  A12 (0x04)
#   define  A13 (0x05)
#   define  A14 (0x06)
#endif

extern float xdata adc_ch15_gxf;


extern void adc_init(void);

extern u16 adc_read(u8 ch);

extern void adc_read_start(u8 ch);

extern u16 adc_read_it(void);

extern float adc_voltage(u8 ch,float vref);

extern void adc_it_start(void);

extern void adc_it_stop(void);

extern float adc_read_vref(void);

extern void adc_it_callback(void);
#endif



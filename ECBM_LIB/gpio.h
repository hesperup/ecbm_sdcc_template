#ifndef _ECBM_GPIO_H_
#define _ECBM_GPIO_H_








#define ECBM_GPIO0_EN (1)

#define ECBM_GPIO1_EN (1)

#define ECBM_GPIO2_EN (1)

#define ECBM_GPIO3_EN (1)

#define ECBM_GPIO4_EN (1)

#define ECBM_GPIO5_EN (1)

#define ECBM_GPIO6_EN (1)

#define ECBM_GPIO7_EN (1)





#define ECBM_GPIO_WRITE_EN (0)

#define ECBM_GPIO_READ_EN (1)

#define ECBM_GPIO_UPPULL_EN (1)

#define ECBM_GPIO_UPPULL_EX_EN (0)

#define ECBM_GPIO_MODE_EN (1)

#define ECBM_GPIO_MODE_EX_EN (0)

#define ECBM_GPIO_SPEED_EN (0)

#define ECBM_GPIO_CURRENT_EN (0)

#define ECBM_GPIO_OUT_EN (1)

#define ECBM_GPIO_IN_EN (1)

#define ECBM_GPIO_TOGGLE_EN (1)

#define ECBM_GPIO_TOGGLE_FAST_EN (1)

#define ECBM_GPIO_OUT_FAST_EN (1)

#define ECBM_GPIO_IN_FAST_EN (1)




#include "ecbm_core.h"

#if 1

#define GPIO_PU  (0)
#define GPIO_HZ  (1)
#define GPIO_OD  (2)
#define GPIO_PP  (3)
#define GPIO_IN  GPIO_PU
#define GPIO_OUT GPIO_PP

#define GPIO_FAST   (0)
#define GPIO_SLOW   (1)

#define GPIO_STR    (0)
#define GPIO_GEN    (1)


#define GPIO_PIN_0   (0x01)
#define GPIO_PIN_1   (0x02)
#define GPIO_PIN_2   (0x04)
#define GPIO_PIN_3   (0x08)
#define GPIO_PIN_4   (0x10)
#define GPIO_PIN_5   (0x20)
#define GPIO_PIN_6   (0x40)
#define GPIO_PIN_7   (0x80)
#define GPIO_PIN_All (0xFF)

#define GPIO_P0  (0)
#define GPIO_P1  (1)
#define GPIO_P2  (2)
#define GPIO_P3  (3)
#define GPIO_P4  (4)
#define GPIO_P5  (5)
#define GPIO_P6  (6)
#define GPIO_P7  (7)

#define D00 (0x00)
#define D01 (0x01)
#define D02 (0x02)
#define D03 (0x03)
#define D04 (0x04)
#define D05 (0x05)
#define D06 (0x06)
#define D07 (0x07)

#define D10 (0x10)
#define D11 (0x11)
#define D12 (0x12)
#define D13 (0x13)
#define D14 (0x14)
#define D15 (0x15)
#define D16 (0x16)
#define D17 (0x17)

#define D20 (0x20)
#define D21 (0x21)
#define D22 (0x22)
#define D23 (0x23)
#define D24 (0x24)
#define D25 (0x25)
#define D26 (0x26)
#define D27 (0x27)

#define D30 (0x30)
#define D31 (0x31)
#define D32 (0x32)
#define D33 (0x33)
#define D34 (0x34)
#define D35 (0x35)
#define D36 (0x36)
#define D37 (0x37)

#define D40 (0x40)
#define D41 (0x41)
#define D42 (0x42)
#define D43 (0x43)
#define D44 (0x44)
#define D45 (0x45)
#define D46 (0x46)
#define D47 (0x47)

#define D50 (0x50)
#define D51 (0x51)
#define D52 (0x52)
#define D53 (0x53)
#define D54 (0x54)
#define D55 (0x55)
#define D56 (0x56)
#define D57 (0x57)

#define D60 (0x60)
#define D61 (0x61)
#define D62 (0x62)
#define D63 (0x63)
#define D64 (0x64)
#define D65 (0x65)
#define D66 (0x66)
#define D67 (0x67)

#define D70 (0x70)
#define D71 (0x71)
#define D72 (0x72)
#define D73 (0x73)
#define D74 (0x74)
#define D75 (0x75)
#define D76 (0x76)
#define D77 (0x77)

#define Dxx (0x88)
#define GPIO_Px (8)
#endif


extern void gpio_uppull(u8 pin,u8 en);

extern void gpio_uppull_ex(u8 port,u8 pin,u8 en);

extern void gpio_mode(u8 pin,u8 mode);

extern void gpio_mode_ex(u8 port,u8 pin,u8 mode);

extern void gpio_speed(u8 pin,u8 speed);

extern void gpio_current(u8 pin,u8 current);

extern void gpio_write(u8 port,u8 dat);

extern u8 gpio_read(u8 port);

extern void gpio_out(u8 pin,u8 value);

extern u8 gpio_in(u8 pin);

extern void gpio_toggle(u8 pin);

extern void gpio_toggle_fast(u8 port,u8 pin);

extern void gpio_out_fast(u8 port,u8 pin,u8 val);

extern u8 gpio_in_fast(u8 port,u8 pin);
#endif



#ifndef _ECBM_SPI_H_
#define _ECBM_SPI_H_
































#define ECBM_SPI_REG (0x50)









#define ECBM_SPI_IO (0)


#define ECBM_SPI_IT_EN (0)



#include "ecbm_core.h"

#define SPI_PIN_P12_P13_P14_P15 (0)
#define SPI_PIN_P22_P23_P24_P25 (4)
#define SPI_PIN_P74_P75_P76_P77 (8)
#define SPI_PIN_P35_P34_P33_P32 (12)

#define SPI_PIN_P54_P40_P41_P43 (8)

#define SPI_PIN_P55_P54_P33_P32 (0)

#define SPI_PIN_P54_P13_P14_P15 (0)


extern void spi_set_pin(u8 group);

extern void spi_init(void);

extern u8 spi_send(u8 dat);
#endif



#ifndef _ECBM_SOFT_SPI_H_
#define _ECBM_SOFT_SPI_H_
















#define ECBM_SOFT_SPI_MODE (0xD4)



#include "ecbm_core.h"



#define SOFT_SPI_MOSI_EN_MASK (0x80)
#define SOFT_SPI_MOSI_ENABLE  (0x80)
#define SOFT_SPI_MOSI_DISABLE (0x7F)

#define SOFT_SPI_MISO_EN_MASK (0x40)
#define SOFT_SPI_MISO_ENABLE  (0x40)
#define SOFT_SPI_MISO_DISABLE (0xBF)

#define SOFT_SPI_MSB_LSB_MASK (0x04)
#define SOFT_SPI_MSB          (0x04)
#define SOFT_SPI_LSB          (0xFB)

#define SOFT_SPI_CPOL_MASK    (0x02)
#define SOFT_SPI_CPOL_1       (0x02)
#define SOFT_SPI_CPOL_0       (0xFD)

#define SOFT_SPI_CPHA_MASK    (0x01)
#define SOFT_SPI_CPHA_1       (0x01)
#define SOFT_SPI_CPHA_0       (0xFE)

extern u8  data soft_spi_def_clk_port_gdu8;
extern u8  data soft_spi_def_clk_pin_gdu8;
extern u8  data soft_spi_def_mosi_port_gdu8;
extern u8  data soft_spi_def_mosi_pin_gdu8;
extern u8  data soft_spi_def_miso_port_gdu8;
extern u8  data soft_spi_def_miso_pin_gdu8;
extern u8  data soft_spi_mode_gdu8;
extern u8 xdata soft_spi_index_gxu8;
extern u8 xdata soft_spi_max_gxu8;
typedef struct{
    u8 clk_pin;
    u8 mosi_pin;
    u8 miso_pin;
    u8 mode;
    u8 dev_id;
}soft_spi_def;


extern void soft_spi_set_pin(soft_spi_def * dev);

extern void soft_spi_init(soft_spi_def * dev,u8 clk,u8 mosi,u8 miso,u8 mode);

extern u8 soft_spi_send(u8 dat);
#endif



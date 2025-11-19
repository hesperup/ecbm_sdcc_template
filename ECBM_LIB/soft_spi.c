#include "ecbm_core.h"
#if (ECBM_SOFTSPI_LIB_EN)

u8  data soft_spi_def_clk_port_gdu8;
u8  data soft_spi_def_clk_pin_gdu8;
u8  data soft_spi_def_mosi_port_gdu8;
u8  data soft_spi_def_mosi_pin_gdu8;
u8  data soft_spi_def_miso_port_gdu8;
u8  data soft_spi_def_miso_pin_gdu8;
u8  data soft_spi_mode_gdu8=0;
u8 xdata soft_spi_index_gxu8=0;
u8 xdata soft_spi_max_gxu8=0;


void soft_spi_set_pin(soft_spi_def * dev){
    if(soft_spi_index_gxu8!=dev->dev_id){
        soft_spi_def_clk_port_gdu8 =io2port(dev->clk_pin);
        soft_spi_def_clk_pin_gdu8  =io2pin (dev->clk_pin);
        soft_spi_def_mosi_port_gdu8=io2port(dev->mosi_pin);
        soft_spi_def_mosi_pin_gdu8 =io2pin (dev->mosi_pin);
        soft_spi_def_miso_port_gdu8=io2port(dev->miso_pin);
        soft_spi_def_miso_pin_gdu8 =io2pin (dev->miso_pin);
        soft_spi_mode_gdu8=dev->mode;
        soft_spi_index_gxu8=dev->dev_id;
    }
}

void soft_spi_init(soft_spi_def * dev,u8 clk,u8 mosi,u8 miso,u8 mode){
    dev->clk_pin =clk;
    dev->mosi_pin=mosi;
    dev->miso_pin=miso;
    dev->mode    =mode;
    gpio_mode(clk, GPIO_OUT);
    if(mode&SOFT_SPI_CPOL_MASK){
        gpio_out(clk,1);
    }else{
        gpio_out(clk,0);
    }
    if(mode&SOFT_SPI_MOSI_EN_MASK){
        gpio_mode(mosi,GPIO_OUT);
        gpio_out (mosi,1);
    }
    if(mode&SOFT_SPI_MISO_EN_MASK){
        gpio_mode  (miso,GPIO_IN);
        gpio_out   (miso,1);
    }
    dev->dev_id=++soft_spi_max_gxu8;
    soft_spi_set_pin(dev);
}

void soft_spi_set_pin_linkage(u8 id,u8 clk,u8 mosi,u8 miso,u8 mode){
    if(soft_spi_index_gxu8!=id){
        soft_spi_def_clk_port_gdu8 =io2port(clk);
        soft_spi_def_clk_pin_gdu8  =io2pin (clk);
        soft_spi_def_mosi_port_gdu8=io2port(mosi);
        soft_spi_def_mosi_pin_gdu8 =io2pin (mosi);
        soft_spi_def_miso_port_gdu8=io2port(miso);
        soft_spi_def_miso_pin_gdu8 =io2pin (miso);
        soft_spi_mode_gdu8=mode;
        soft_spi_index_gxu8=id;
    }
}

u8 soft_spi_init_linkage(u8 clk,u8 mosi,u8 miso,u8 mode){
    u8 id_u8;
    gpio_mode(clk, GPIO_OUT);
    if(mode&SOFT_SPI_CPOL_MASK){
        gpio_out(clk,1);
    }else{
        gpio_out(clk,0);
    }
    if(mode&SOFT_SPI_MOSI_EN_MASK){
        gpio_mode(mosi,GPIO_OUT);
        gpio_out (mosi,1);
    }
    if(mode&SOFT_SPI_MISO_EN_MASK){
        gpio_mode  (miso,GPIO_IN);
        gpio_out   (miso,1);
    }
    id_u8 =++soft_spi_max_gxu8;
    soft_spi_set_pin_linkage(id_u8,clk,mosi,miso,mode);
    return id_u8;
}

u8 soft_spi_send(u8 dat){
    u8 i_u8,j_u8,k_u8=0;
    if(soft_spi_mode_gdu8&SOFT_SPI_CPOL_MASK){
        gpio_out_fast(soft_spi_def_clk_port_gdu8,soft_spi_def_clk_pin_gdu8,1);
    }else{
        gpio_out_fast(soft_spi_def_clk_port_gdu8,soft_spi_def_clk_pin_gdu8,0);
    }
    if(soft_spi_mode_gdu8&SOFT_SPI_MSB_LSB_MASK){
        i_u8=0x80;
        for(j_u8=0;j_u8<8;j_u8++){
            if(dat&i_u8){
                gpio_out_fast(soft_spi_def_mosi_port_gdu8,soft_spi_def_mosi_pin_gdu8,1);
            }else{
                gpio_out_fast(soft_spi_def_mosi_port_gdu8,soft_spi_def_mosi_pin_gdu8,0);
            }
            gpio_toggle_fast(soft_spi_def_clk_port_gdu8,soft_spi_def_clk_pin_gdu8);
            if((soft_spi_mode_gdu8&SOFT_SPI_MISO_EN_MASK)&&((soft_spi_mode_gdu8&SOFT_SPI_CPHA_MASK)==0)){
                if(gpio_in_fast(soft_spi_def_miso_port_gdu8,soft_spi_def_miso_pin_gdu8)){
                    k_u8|=i_u8;
                }
            }
            gpio_toggle_fast(soft_spi_def_clk_port_gdu8,soft_spi_def_clk_pin_gdu8);
            if((soft_spi_mode_gdu8&SOFT_SPI_MISO_EN_MASK)&&((soft_spi_mode_gdu8&SOFT_SPI_CPHA_MASK)==1)){
                if(gpio_in_fast(soft_spi_def_miso_port_gdu8,soft_spi_def_miso_pin_gdu8)){
                    k_u8|=i_u8;
                }
            }
            i_u8>>=1;
        }
    }else{
        i_u8=0x01;
        for(j_u8=0;j_u8<8;j_u8++){
            if(dat&i_u8){
                gpio_out_fast(soft_spi_def_mosi_port_gdu8,soft_spi_def_mosi_pin_gdu8,1);
            }else{
                gpio_out_fast(soft_spi_def_mosi_port_gdu8,soft_spi_def_mosi_pin_gdu8,0);
            }
            gpio_toggle_fast(soft_spi_def_clk_port_gdu8,soft_spi_def_clk_pin_gdu8);
            if((soft_spi_mode_gdu8&SOFT_SPI_MISO_EN_MASK)&&((soft_spi_mode_gdu8&SOFT_SPI_CPHA_MASK)==0)){
                if(gpio_in_fast(soft_spi_def_miso_port_gdu8,soft_spi_def_miso_pin_gdu8)){
                    k_u8|=i_u8;
                }
            }
            gpio_toggle_fast(soft_spi_def_clk_port_gdu8,soft_spi_def_clk_pin_gdu8);
            if((soft_spi_mode_gdu8&SOFT_SPI_MISO_EN_MASK)&&((soft_spi_mode_gdu8&SOFT_SPI_CPHA_MASK)==1)){
                if(gpio_in_fast(soft_spi_def_miso_port_gdu8,soft_spi_def_miso_pin_gdu8)){
                    k_u8|=i_u8;
                }
            }
            i_u8<<=1;
        }
    }
    return k_u8;
}
#endif



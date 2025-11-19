#ifndef _ECBM_SOFT_IIC_H_
#define _ECBM_SOFT_IIC_H_





#define SOFT_IIC_FIND_EN (0)




#include "ecbm_core.h"

extern u8 data soft_iic_def_sda_port_gdu8;
extern u8 data soft_iic_def_sda_pin_gdu8;
extern u8 data soft_iic_def_scl_port_gdu8;
extern u8 data soft_iic_def_scl_pin_gdu8;
extern u8 data soft_iic_max_gdu8;
extern u8 data soft_iic_index_gdu8;
typedef struct{
    u8 scl_pin;
    u8 sda_pin;
    u8 dev_id;
}soft_iic_def;


extern void soft_iic_set_pin(soft_iic_def * dev);

extern void soft_iic_init(soft_iic_def * dev,u8 scl,u8 sda);

extern u8 soft_iic_start(void);

extern void soft_iic_stop(void);

extern void soft_iic_write_ack(void);

extern void soft_iic_write_nack(void);

extern u8 soft_iic_read_ack(void);

extern void soft_iic_write(u8 dat);

extern u8 soft_iic_read(void);

extern u8 soft_iic_find(u8 addr[]);

#endif



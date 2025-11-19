#ifndef _ECBM_IIC_H_
#define _ECBM_IIC_H_






#define ECBM_IIC_WAIT (400000L)










#define ECBM_IIC_IO (0)



#define ECBM_IIC_TIMEOUT (20000)



#define ECBM_IIC_SLAVE_ADDR_EN (0)




#define ECBM_IIC_SLAVE_ADDR (0x0F)



#define ECBM_IIC_BUF_MAX (20)


#define ECBM_EIICP_EN (0)




#include "ecbm_core.h"

#if ((ECBM_MCU==0x310201)||(ECBM_MCU==0x3102A1))
#define IIC_PIN_P32_P33 (0)
#define IIC_PIN_P54_P55 (16)
#else
#define IIC_PIN_P15_P14 (0)
#define IIC_PIN_P25_P24 (16)
#define IIC_PIN_P77_P76 (32)
#define IIC_PIN_P32_P33 (48)
#endif
#define EIICP_CMD_TRIG             (0)
#define EIICP_CMD_TRIG_REPLY       (1)
#define EIICP_CMD_READ             (2)
#define EIICP_CMD_READ_REPLY       (3)
#define EIICP_CMD_WRITE            (4)
#define EIICP_CMD_WRITE_REPLY      (5)

#define EIICP_CMD_AUTO_UPDATA      (200)
#define EIICP_CMD_ERROR_OPERATE    (254)

extern bit iic_master_busy_gb;
extern u8 xdata iic_index_gxu8;
extern bit eiicp_trig_gb;
extern u8  eiicp_data_count_gu8;
extern u8  eiicp_data_buf_gu8a[ECBM_IIC_BUF_MAX];


extern void iic_set_pin(u8 group);

extern void iic_reset_pin(u8 group);

extern void iic_master_init(void);

extern void iic_slave_init(void);

extern void iic_set_master_mode(void);

extern void iic_set_slave_mode(void);

extern void iic_start     (void);
extern void iic_stop      (void);
extern void iic_write     (u8 dat);
extern void iic_write_ack (void);
extern void iic_write_nack(void);
extern u8   iic_read      (void);
extern bit iic_read_ack   (void);

extern void eiicp_master_trig(u8 target_id,u16 addr);

extern void eiicp_master_write(u8 target_id,u16 addr,u8 * dat,u8 len);

extern void eiicp_master_read(u8 target_id,u16 addr,u8 len);

extern void eiicp_main(void);


extern u8 eiicp_get_id(void);

extern void eiicp_base_reg_trig(u16 addr);

extern u8 eiicp_base_reg_read(u16 addr);

extern void eiicp_base_reg_write(u16 addr,u8 dat);

extern void eiicp_master_trig_callback(u16 addr);

extern void eiicp_master_read_callback(u16 addr,u8 dat);

extern void eiicp_master_write_callback(u16 addr);
#endif



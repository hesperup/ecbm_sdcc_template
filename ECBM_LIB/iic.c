#include "ecbm_core.h"
#if (ECBM_IIC_LIB_EN)

bit iic_master_busy_gb;
u8 xdata iic_index_gxu8;
bit eiicp_trig_gb;
u8  eiicp_data_count_gu8;
u8  eiicp_data_buf_gu8a[ECBM_IIC_BUF_MAX];


void iic_set_pin(u8 group){
    #if ((ECBM_MCU==0x310201)||(ECBM_MCU==0x3102A1))
        switch(group){
            case IIC_PIN_P32_P33:{
                P3M1|=0x0C;
                P3M0|=0x0C;
                P3PU|=0x0C;
            }break;
            case IIC_PIN_P54_P55:{
                P5M1|=0x30;
                P5M0|=0x30;
                P5PU|=0x30;
            }break;
            default:break;
        }
    #else
        switch(group){
            case IIC_PIN_P15_P14:{
                P1M1|=0x30;
                P1M0|=0x30;
                P1PU|=0x30;
            }break;
            case IIC_PIN_P25_P24:{
                P2M1|=0x30;
                P2M0|=0x30;
                P2PU|=0x30;
            }break;
            case IIC_PIN_P77_P76:{
                P7M1|=0xC0;
                P7M0|=0xC0;
                P7PU|=0xC0;
            }break;
            case IIC_PIN_P32_P33:{
                P3M1|=0x0C;
                P3M0|=0x0C;
                P3PU|=0x0C;
            }break;
            default:break;
        }
    #endif
    IIC_SET_PIN(group);
}

void iic_set_pin_linkage(u8 group){
    if(iic_index_gxu8!=group){
        iic_index_gxu8=group;
        IIC_POWER_OFF;
        IIC_SET_PIN(group);
        IIC_POWER_ON;
    }
}

void iic_reset_pin(u8 group){
    #if ((ECBM_MCU==0x310201)||(ECBM_MCU==0x3102A1))
        switch(group){
            case IIC_PIN_P32_P33:{
                P3M1&=~0x0C;
                P3M0&=~0x0C;
                P3PU&=~0x0C;
            }break;
            case IIC_PIN_P54_P55:{
                P5M1&=~0x30;
                P5M0&=~0x30;
                P5PU&=~0x30;
            }break;
            default:break;
        }
    #else
        switch(group){
            case IIC_PIN_P15_P14:{
                P1M1&=~0x30;
                P1M0&=~0x30;
                P1PU&=~0x30;
            }break;
            case IIC_PIN_P25_P24:{
                P2M1&=~0x30;
                P2M0&=~0x30;
                P2PU&=~0x30;
            }break;
            case IIC_PIN_P77_P76:{
                P7M1&=~0xC0;
                P7M0&=~0xC0;
                P7PU&=~0xC0;
            }break;
            case IIC_PIN_P32_P33:{
                P3M1&=~0x0C;
                P3M0&=~0x0C;
                P3PU&=~0x0C;
            }break;
            default:break;
        }
    #endif
}

void iic_master_init(void){
    u8 res_u8=63;
    res_u8=(u8)(((ECBM_SYSCLK_SETTING/2/ECBM_IIC_WAIT)-4)/2);
    IIC_SET_SPEED(res_u8);
    iic_set_master_mode();
    iic_set_pin(ECBM_IIC_IO);
    iic_index_gxu8=ECBM_IIC_IO;
    IIC_POWER_ON;
}

void iic_slave_init(void){
    u8 res_u8=63;
    res_u8=(u8)(((ECBM_SYSCLK_SETTING/2/ECBM_IIC_WAIT)-4)/2);
    IIC_SET_SPEED(res_u8);
    #if (ECBM_EIICP_EN)
        IIC_SET_REG_SLADR(0xEC);
    #else
        #if (ECBM_IIC_SLAVE_ADDR_EN)
            IIC_SET_REG_SLADR(ECBM_IIC_SLAVE_ADDR<<1);
        #else
            IIC_SET_REG_SLADR(0x01);
        #endif
    #endif
    iic_set_slave_mode();
    iic_set_pin(ECBM_IIC_IO);
    iic_index_gxu8=ECBM_IIC_IO;
    IIC_POWER_ON;
}

void iic_set_master_mode(void){
    IIC_SET_REG_SLCR(1);
    IIC_SET_REG_MSST(0);
    IIC_SET_MODE_MASTER;

}

void iic_set_slave_mode(void){
    IIC_SET_REG_MSCR(0);
    IIC_SET_REG_SLST(0);
    IIC_SET_MODE_SLAVE;
    IIC_SET_REG_SLCR(0x78);
}

void iic_start(void){
    u16 timeout_u16=ECBM_IIC_TIMEOUT;
    iic_master_busy_gb=1;
    IIC_CMD_START;
    while(iic_master_busy_gb&&(timeout_u16--));
}
void iic_stop(void){
    u16 timeout_u16=ECBM_IIC_TIMEOUT;
    iic_master_busy_gb = 1;
    IIC_CMD_STOP;
    while(iic_master_busy_gb&&(timeout_u16--));
}
void iic_write(u8 dat){
    u16 timeout_u16=ECBM_IIC_TIMEOUT;
    IIC_SET_REG_DATA(dat);
    iic_master_busy_gb=1;
    IIC_CMD_TX_DATA;
    while(iic_master_busy_gb&&(timeout_u16--));
}
void iic_write_ack(void){
    u16 timeout_u16=ECBM_IIC_TIMEOUT;
    iic_master_busy_gb=1;
    IIC_CMD_TX_ACK;
    while(iic_master_busy_gb&&(timeout_u16--));
}
void iic_write_nack(void){
    u16 timeout_u16=ECBM_IIC_TIMEOUT;
    iic_master_busy_gb=1;
    IIC_CMD_TX_NACK;
    while(iic_master_busy_gb&&(timeout_u16--));
}
u8 iic_read(void){
    u16 timeout_u16=ECBM_IIC_TIMEOUT;
    iic_master_busy_gb=1;
    IIC_CMD_RX_DATA;
    while(iic_master_busy_gb&&(timeout_u16--));
    return IIC_GET_REG_DATA;
}
bit iic_read_ack(void){
    u16 timeout_u16=ECBM_IIC_TIMEOUT;
    iic_master_busy_gb=1;
    IIC_CMD_RX_ACK;
    while(iic_master_busy_gb&&(timeout_u16--));
    return IIC_GET_ACK>>1;
}

#if (ECBM_EIICP_EN)
void eiicp_master_base(u8 target_id,u8 operate,u16 addr,u8 * dat,u8 len){
    u16 timeout_u16=ECBM_IIC_TIMEOUT;
    u8 temp[8],i;
    iic_set_master_mode();


    temp[0]=target_id;

    temp[1]=eiicp_get_id();

    temp[2]=operate;

    temp[3]=0;

    temp[4]=0;

    temp[5]=(u8)(addr>>8);

    temp[6]=(u8)(addr);

    temp[7]=len;

    iic_master_busy_gb=1;
    IIC_SET_REG_DATA(0xEC);
    IIC_CMD_START_TXDATA_RXACK;
    while(iic_master_busy_gb&&(timeout_u16--));
    for(i=0;i<8;i++){
        iic_master_busy_gb=1;
        IIC_SET_REG_DATA(temp[i]);
        IIC_CMD_TXDATA_RXACK;
        while(iic_master_busy_gb&&(timeout_u16--));
    }

    if(operate==EIICP_CMD_WRITE){
        for(i=0;i<len;i++){
            iic_master_busy_gb=1;
            IIC_SET_REG_DATA(dat[i]);
            IIC_CMD_TXDATA_RXACK;
            while(iic_master_busy_gb&&(timeout_u16--));
        }
    }

    iic_master_busy_gb=1;
    IIC_CMD_STOP;
    while(iic_master_busy_gb&&(timeout_u16--));
    iic_set_slave_mode();
}

void eiicp_master_trig(u8 target_id,u16 addr){
    eiicp_master_base(target_id,EIICP_CMD_TRIG,addr,(u8 *)(0),0);
}

void eiicp_master_write(u8 target_id,u16 addr,u8 * dat,u8 len){
    eiicp_master_base(target_id,EIICP_CMD_WRITE,addr,dat,len);
}

void eiicp_master_read(u8 target_id,u16 addr,u8 len){
    eiicp_master_base(target_id,EIICP_CMD_READ,addr,(u8 *)(0),len);
}

void eiicp_main(void){
    u8  id_u8,len_u8,operate_u8;
    u16 i_u16,addr_u16;
    if(eiicp_trig_gb){
        eiicp_trig_gb=0;
        if(eiicp_data_buf_gu8a[0]==0xEC){
            if(eiicp_data_buf_gu8a[1]==eiicp_get_id()){

                id_u8     =eiicp_data_buf_gu8a[2];
                operate_u8=eiicp_data_buf_gu8a[3];
                addr_u16  =(u16)(eiicp_data_buf_gu8a[6])*256+(u16)(eiicp_data_buf_gu8a[7]);
                len_u8    =eiicp_data_buf_gu8a[8];
                switch(operate_u8){
                    case EIICP_CMD_TRIG:{
                        eiicp_base_reg_trig(addr_u16);
                        eiicp_master_base(id_u8,EIICP_CMD_TRIG_REPLY,addr_u16,(u8 *)(0),0);
                    }break;
                    case EIICP_CMD_TRIG_REPLY:{
                        eiicp_master_trig_callback(addr_u16);
                    }break;
                    case EIICP_CMD_READ:{
                        for(i_u16=0;i_u16<(u16)(len_u8);i_u16++){
                            eiicp_data_buf_gu8a[i_u16]=eiicp_base_reg_read(addr_u16+i_u16);
                        }
                        eiicp_master_base(id_u8,EIICP_CMD_READ_REPLY,addr_u16,eiicp_data_buf_gu8a,len_u8);
                    }break;
                    case EIICP_CMD_READ_REPLY:{
                        for(i_u16=0;i_u16<(u16)(len_u8);i_u16++){
                            eiicp_master_read_callback(addr_u16+i_u16,eiicp_data_buf_gu8a[9+i_u16]);
                        }
                    }break;
                    case EIICP_CMD_WRITE:{
                        for(i_u16=0;i_u16<(u16)(len_u8);i_u16++){
                            eiicp_base_reg_write(addr_u16+i_u16,eiicp_data_buf_gu8a[9+i_u16]);
                        }
                        eiicp_master_base(id_u8,EIICP_CMD_WRITE_REPLY,addr_u16,(u8 *)(0),0);
                    }break;
                    case EIICP_CMD_WRITE_REPLY:{
                        eiicp_master_write_callback(addr_u16);
                    }break;
                }
            }
        }
    }
}
#endif
#endif



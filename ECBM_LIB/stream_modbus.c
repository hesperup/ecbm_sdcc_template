#include "ecbm_core.h"
#if (ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_MODBUS_CH_COUNT)

u8  es_modbus_rtu_mode_gu8a        [ECBM_STREAM_MODBUS_CH_COUNT];
u8  es_modbus_rtu_send_id_gu8a     [ECBM_STREAM_MODBUS_CH_COUNT];
u8  es_modbus_rtu_reply_count_gu8a [ECBM_STREAM_MODBUS_CH_COUNT];
u8  es_modbus_rtu_status_gu8a      [ECBM_STREAM_MODBUS_CH_COUNT];
u8  es_modbus_rtu_broadcast_en_gu8a[ECBM_STREAM_MODBUS_CH_COUNT];
u8  es_modbus_rtu_fun_code_gu8a    [ECBM_STREAM_MODBUS_CH_COUNT];
u16 es_modbus_rtu_address_gu16a    [ECBM_STREAM_MODBUS_CH_COUNT];
u16 es_modbus_rtu_data_count_gu16a [ECBM_STREAM_MODBUS_CH_COUNT];
u16 es_modbus_rtu_uart_crc_gu16a   [ECBM_STREAM_MODBUS_CH_COUNT];
u16 es_modbus_rtu_crc_buf_gu16a    [ECBM_STREAM_MODBUS_CH_COUNT];
u8  es_modbus_rtu_cmd_count_gu8a   [ECBM_STREAM_MODBUS_CH_COUNT];
u8  es_modbus_rtu_count_gu8a       [ECBM_STREAM_MODBUS_CH_COUNT];
#if ((ES_MODBUS_RTU_CMD10_EN)||(ES_MODBUS_RTU_MASTER_EN))
    u16 es_modbus_rtu_cmd_buf_gu16a[ECBM_STREAM_MODBUS_CH_COUNT][ES_MODBUS_RTU_BUF_SIZE];
#endif

u8 ecbm_stream_modbus_chtoid(u8 ch){
    switch(ch){
        case 1:return (0);break;
        case 2:return ( ECBM_STREAM_CH1_EN*ECBM_STREAM_MODBUS_CH1_EN);break;
        case 3:return ((ECBM_STREAM_CH1_EN*ECBM_STREAM_MODBUS_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_MODBUS_CH2_EN));break;
        case 4:return ((ECBM_STREAM_CH1_EN*ECBM_STREAM_MODBUS_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_MODBUS_CH2_EN)+(ECBM_STREAM_CH3_EN*ECBM_STREAM_MODBUS_CH3_EN));break;
    }
    return (0);
}

void es_modbus_rtu_reset(u8 ch){
    u8 id_u8;
    id_u8=ecbm_stream_modbus_chtoid(ch);
    es_modbus_rtu_mode_gu8a        [id_u8]=ES_MODBUS_RTU_MODE_SLAVE;
    es_modbus_rtu_send_id_gu8a     [id_u8]=0;
    es_modbus_rtu_reply_count_gu8a [id_u8]=0;
    es_modbus_rtu_status_gu8a      [id_u8]=ES_MODBUS_RTU_READY;
    es_modbus_rtu_broadcast_en_gu8a[id_u8]=0;
    es_modbus_rtu_fun_code_gu8a    [id_u8]=0;
    es_modbus_rtu_address_gu16a    [id_u8]=0;
    es_modbus_rtu_data_count_gu16a [id_u8]=0;
    es_modbus_rtu_uart_crc_gu16a   [id_u8]=0;
    es_modbus_rtu_crc_buf_gu16a    [id_u8]=0;
    es_modbus_rtu_cmd_count_gu8a   [id_u8]=0;
    es_modbus_rtu_count_gu8a       [id_u8]=0;
}

void es_modbus_rtu_err_num(u8 ch,u8 fun_num,u8 err_num){
    u8  id_u8;
    u16 crc_u16;
    if(es_modbus_rtu_broadcast_en_gu8a[ecbm_stream_modbus_chtoid(ch)]){
        id_u8=es_modbus_rtu_get_id(ch);
        crc_u16=es_send_whit_crc(ch,0xFFFF,id_u8);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x80+fun_num);
        crc_u16=es_send_whit_crc(ch,crc_u16,err_num);
        uart_char(ch,(u8)(crc_u16));
        uart_char(ch,(u8)(crc_u16>>8));
    }
}

#if (ES_MODBUS_RTU_CMD01_EN)
    void es_modbus_rtu_cmd_0x01(u8 ch){
        u8 temp_u8,t1_u8,c1_u8,i_u8,j_u8,qw_u8,id_u8,index_u8;
        u16 crc_u16;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        id_u8=es_modbus_rtu_get_id(ch);
        if((es_modbus_rtu_data_count_gu16a[index_u8]>=1)&&(es_modbus_rtu_data_count_gu16a[index_u8]<=0x07D0)){
            if(((u32)(es_modbus_rtu_data_count_gu16a[index_u8])+(u32)(es_modbus_rtu_address_gu16a[index_u8]))<=65536UL){
                if(es_modbus_rtu_broadcast_en_gu8a[index_u8]){
                    t1_u8=(u8)(es_modbus_rtu_data_count_gu16a[index_u8]/8);
                    if(es_modbus_rtu_data_count_gu16a[index_u8]%8)t1_u8++;
                    crc_u16=es_send_whit_crc(ch,0xFFFF,id_u8);
                    crc_u16=es_send_whit_crc(ch,crc_u16,0x01);
                    crc_u16=es_send_whit_crc(ch,crc_u16,t1_u8);
                    for(i_u8=0;i_u8<t1_u8;i_u8++){
                        temp_u8=0;
                        if(es_modbus_rtu_data_count_gu16a[index_u8]>=8){
                            c1_u8=8;
                        }else{
                            c1_u8=(u8)(es_modbus_rtu_data_count_gu16a[index_u8]);
                        }
                        for(j_u8=0;j_u8<c1_u8;j_u8++){
                            es_modbus_cmd_read_bit(ch,es_modbus_rtu_address_gu16a[index_u8]++,&qw_u8);
                            if(qw_u8)temp_u8|=(1<<j_u8);
                        }
                        crc_u16=es_send_whit_crc(ch,crc_u16,temp_u8);
                        es_modbus_rtu_data_count_gu16a[index_u8]-=(u16)c1_u8;
                    }
                    uart_char(ch,(u8)(crc_u16));
                    uart_char(ch,(u8)(crc_u16>>8));
                }
            }else{
                es_modbus_rtu_err_num(ch,0x01,0x02);
            }
        }else{
            es_modbus_rtu_err_num(ch,0x01,0x03);
        }
    }
#endif

#if (ES_MODBUS_RTU_CMD02_EN)
    void es_modbus_rtu_cmd_0x02(u8 ch){
        u8 temp_u8,t1_u8,c1_u8,i_u8,j_u8,qw_u8,id_u8,index_u8;
        u16 crc_u16;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        id_u8=es_modbus_rtu_get_id(ch);
        if((es_modbus_rtu_data_count_gu16a[index_u8]>=1)&&(es_modbus_rtu_data_count_gu16a[index_u8]<=0x07D0)){
            if(((u32)(es_modbus_rtu_data_count_gu16a[index_u8])+(u32)(es_modbus_rtu_address_gu16a[index_u8]))<=65536UL){
                    if(es_modbus_rtu_broadcast_en_gu8a[index_u8]){
                        t1_u8=(u8)(es_modbus_rtu_data_count_gu16a[index_u8]/8);
                        if(es_modbus_rtu_data_count_gu16a[index_u8]%8)t1_u8++;
                        crc_u16=es_send_whit_crc(ch,0xFFFF,id_u8);
                        crc_u16=es_send_whit_crc(ch,crc_u16,0x02);
                        crc_u16=es_send_whit_crc(ch,crc_u16,t1_u8);
                        for(i_u8=0;i_u8<t1_u8;i_u8++){
                            temp_u8=0;
                            if(es_modbus_rtu_data_count_gu16a[index_u8]>=8){
                                c1_u8=8;
                            }else{
                                c1_u8=(u8)(es_modbus_rtu_data_count_gu16a[index_u8]);
                            }
                            for(j_u8=0;j_u8<c1_u8;j_u8++){
                                es_modbus_cmd_read_io_bit(ch,es_modbus_rtu_address_gu16a[index_u8]++,&qw_u8);
                                if(qw_u8)temp_u8|=(1<<j_u8);
                            }
                            crc_u16=es_send_whit_crc(ch,crc_u16,temp_u8);
                            es_modbus_rtu_data_count_gu16a[index_u8]-=(u16)c1_u8;
                        }
                        uart_char(ch,(u8)(crc_u16));
                        uart_char(ch,(u8)(crc_u16>>8));
                    }
            }else{
                es_modbus_rtu_err_num(ch,0x02,0x02);
            }
        }else{
            es_modbus_rtu_err_num(ch,0x02,0x03);
        }
    }
#endif

#if (ES_MODBUS_RTU_CMD03_EN)
    void es_modbus_rtu_cmd_0x03(u8 ch){
        u8 id_u8,index_u8;
        u16 temp_u16,i_u16,crc_u16;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        id_u8=es_modbus_rtu_get_id(ch);
        if((es_modbus_rtu_data_count_gu16a[index_u8]>=1)&&(es_modbus_rtu_data_count_gu16a[index_u8]<=0x007D)){
            if(((u32)(es_modbus_rtu_data_count_gu16a[index_u8])+(u32)(es_modbus_rtu_address_gu16a[index_u8]))<65536UL){
                if(es_modbus_rtu_broadcast_en_gu8a[index_u8]){
                    crc_u16=es_send_whit_crc(ch,0xFFFF,id_u8);
                    crc_u16=es_send_whit_crc(ch,crc_u16,0x03);
                    crc_u16=es_send_whit_crc(ch,crc_u16,es_modbus_rtu_data_count_gu16a[index_u8]*2);
                    for(i_u16=0;i_u16<es_modbus_rtu_data_count_gu16a[index_u8];i_u16++){
                        es_modbus_cmd_read_reg(ch,es_modbus_rtu_address_gu16a[index_u8]+i_u16,&temp_u16);
                        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(temp_u16>>8));
                        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(temp_u16));
                    }
                    uart_char(ch,(u8)(crc_u16));
                    uart_char(ch,(u8)(crc_u16>>8));
                }
            }else{
                es_modbus_rtu_err_num(ch,0x03,0x02);
            }
        }else{
            es_modbus_rtu_err_num(ch,0x03,0x03);
        }
    }
#endif

#if (ES_MODBUS_RTU_CMD04_EN)
    void es_modbus_rtu_cmd_0x04(u8 ch){
        u8 id_u8,index_u8;
        u16 temp_u16,i_u16,crc_u16;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        id_u8=es_modbus_rtu_get_id(ch);
        if((es_modbus_rtu_data_count_gu16a[index_u8]>=1)&&(es_modbus_rtu_data_count_gu16a[index_u8]<=0x007D)){
            if(((u32)(es_modbus_rtu_data_count_gu16a[index_u8])+(u32)(es_modbus_rtu_address_gu16a[index_u8]))<65536UL){
                if(es_modbus_rtu_broadcast_en_gu8a[index_u8]){
                    crc_u16=es_send_whit_crc(ch,0xFFFF,id_u8);
                    crc_u16=es_send_whit_crc(ch,crc_u16,0x04);
                    crc_u16=es_send_whit_crc(ch,crc_u16,es_modbus_rtu_data_count_gu16a[index_u8]*2);
                    for(i_u16=0;i_u16<es_modbus_rtu_data_count_gu16a[index_u8];i_u16++){
                        es_modbus_cmd_read_io_reg(ch,es_modbus_rtu_address_gu16a[index_u8]+i_u16,&temp_u16);
                        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(temp_u16>>8));
                        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(temp_u16));
                    }
                    uart_char(ch,(u8)(crc_u16));
                    uart_char(ch,(u8)(crc_u16>>8));
                }
            }else{
                es_modbus_rtu_err_num(ch,0x04,0x02);
            }
        }else{
            es_modbus_rtu_err_num(ch,0x04,0x03);
        }
    }
#endif

#if (ES_MODBUS_RTU_CMD05_EN)
    void es_modbus_rtu_cmd_0x05(u8 ch){
        u8 id_u8,index_u8;
        u16 crc_u16;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        id_u8=es_modbus_rtu_get_id(ch);
        if((es_modbus_rtu_data_count_gu16a[index_u8]==0x0000)||(es_modbus_rtu_data_count_gu16a[index_u8]==0xFF00)){
            es_modbus_cmd_write_bit(ch,es_modbus_rtu_address_gu16a[index_u8],(u8)(es_modbus_rtu_data_count_gu16a[index_u8]>>8));
            if(es_modbus_rtu_broadcast_en_gu8a[index_u8]){
                crc_u16=es_send_whit_crc(ch,0xFFFF,id_u8);
                crc_u16=es_send_whit_crc(ch,crc_u16,0x05);
                crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_address_gu16a[index_u8]>>8));
                crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_address_gu16a[index_u8]));
                crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_data_count_gu16a[index_u8]>>8));
                crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_data_count_gu16a[index_u8]));
                uart_char(ch,(u8)(crc_u16));
                uart_char(ch,(u8)(crc_u16>>8));
            }
        }else{
            es_modbus_rtu_err_num(ch,0x05,0x03);
        }
    }
#endif

#if (ES_MODBUS_RTU_CMD06_EN)
    void es_modbus_rtu_cmd_0x06(u8 ch){
        u8 id_u8,index_u8;
        u16 crc_u16;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        id_u8=es_modbus_rtu_get_id(ch);
        es_modbus_cmd_write_reg(ch,es_modbus_rtu_address_gu16a[index_u8],es_modbus_rtu_data_count_gu16a[index_u8]);
        if(es_modbus_rtu_broadcast_en_gu8a[index_u8]){
            crc_u16=es_send_whit_crc(ch,0xFFFF,id_u8);
            crc_u16=es_send_whit_crc(ch,crc_u16,0x06);
            crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_address_gu16a[index_u8]>>8));
            crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_address_gu16a[index_u8]));
            crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_data_count_gu16a[index_u8]>>8));
            crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_data_count_gu16a[index_u8]));
            uart_char(ch,(u8)(crc_u16));
            uart_char(ch,(u8)(crc_u16>>8));
        }
    }
#endif

#if (ES_MODBUS_RTU_CMD10_EN)
    void es_modbus_rtu_cmd_0x10(u8 ch){
        u8 i_u8,id_u8,index_u8;
        u16 crc_u16;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        id_u8=es_modbus_rtu_get_id(ch);
        if((es_modbus_rtu_cmd_count_gu8a[index_u8]==0)||(es_modbus_rtu_cmd_count_gu8a[index_u8]!=(u8)(es_modbus_rtu_data_count_gu16a[index_u8]*2))){
            es_modbus_rtu_err_num(ch,es_modbus_rtu_fun_code_gu8a[index_u8],0x03);
            return;
        }
        if((es_modbus_rtu_data_count_gu16a[index_u8]>=0x0001)&&(es_modbus_rtu_data_count_gu16a[index_u8]<=0x007B)){
            if(((u32)(es_modbus_rtu_address_gu16a[index_u8])+(u32)(es_modbus_rtu_data_count_gu16a[index_u8]))<65536UL){
                for(i_u8=0;i_u8<es_modbus_rtu_cmd_count_gu8a[index_u8];i_u8++){
                    es_modbus_cmd_write_reg(ch,es_modbus_rtu_address_gu16a[index_u8]+i_u8,es_modbus_rtu_cmd_buf_gu16a[index_u8][i_u8]);
                }
                if(es_modbus_rtu_broadcast_en_gu8a[index_u8]){
                    crc_u16=es_send_whit_crc(ch,0xFFFF,id_u8);
                    crc_u16=es_send_whit_crc(ch,crc_u16,0x10);
                    crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_address_gu16a[index_u8]>>8));
                    crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_address_gu16a[index_u8]));
                    crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_data_count_gu16a[index_u8]>>8));
                    crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_modbus_rtu_data_count_gu16a[index_u8]));
                    uart_char(ch,(u8)(crc_u16));
                    uart_char(ch,(u8)(crc_u16>>8));
                }
            }else{
                es_modbus_rtu_err_num(ch,0x10,0x02);
            }
        }else{
            es_modbus_rtu_err_num(ch,0x10,0x03);
        }
    }
#endif

void es_modbus_rtu_exe(u8 ch,u8 dat){
    u8 i_u8,temp_u8,mask_u8,index_u8;
    i_u8=i_u8;
    temp_u8=temp_u8;
    mask_u8=mask_u8;
    index_u8=ecbm_stream_modbus_chtoid(ch);

    if(es_modbus_rtu_mode_gu8a[index_u8]==ES_MODBUS_RTU_MODE_SLAVE){
        switch(es_modbus_rtu_status_gu8a[index_u8]){
            case ES_MODBUS_RTU_READY:{
                if((dat==es_modbus_rtu_get_id(ch))||(dat==0)){
                    es_modbus_rtu_status_gu8a      [index_u8]=ES_MODBUS_RTU_FUN_NUM;
                    es_modbus_rtu_broadcast_en_gu8a[index_u8]=dat;
                    es_modbus_rtu_fun_code_gu8a    [index_u8]=0;
                    es_modbus_rtu_uart_crc_gu16a   [index_u8]=es_crc16(0xFFFF,dat);
                }
            }break;
            case ES_MODBUS_RTU_FUN_NUM:{
                es_modbus_rtu_fun_code_gu8a [index_u8]=dat;
                es_modbus_rtu_status_gu8a   [index_u8]=ES_MODBUS_RTU_ADDRH;
                es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
            }break;
            case ES_MODBUS_RTU_ADDRH:{
                es_modbus_rtu_address_gu16a [index_u8]=(u16)(dat)<<8;
                es_modbus_rtu_status_gu8a   [index_u8]=ES_MODBUS_RTU_ADDRL;
                es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
            }break;
            case ES_MODBUS_RTU_ADDRL:{
                es_modbus_rtu_address_gu16a [index_u8]+=(u16)(dat);
                es_modbus_rtu_status_gu8a   [index_u8]=ES_MODBUS_RTU_DATA_COUNTH;
                es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
            }break;
            case ES_MODBUS_RTU_DATA_COUNTH:{
                es_modbus_rtu_data_count_gu16a[index_u8]=(u16)(dat)<<8;
                es_modbus_rtu_status_gu8a     [index_u8]=ES_MODBUS_RTU_DATA_COUNTL;
                es_modbus_rtu_uart_crc_gu16a  [index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
            }break;
            case ES_MODBUS_RTU_DATA_COUNTL:{
                es_modbus_rtu_data_count_gu16a  [index_u8]+=(u16)(dat);
                if(es_modbus_rtu_fun_code_gu8a  [index_u8]==0x10){
                    es_modbus_rtu_cmd_count_gu8a[index_u8]=0;
                    es_modbus_rtu_status_gu8a   [index_u8]=ES_MODBUS_RTU_BYTE_COUNT;
                }else{
                    es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_CRCL;
                }
                es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
            }break;
            case ES_MODBUS_RTU_CRCL:{
                es_modbus_rtu_crc_buf_gu16a[index_u8]=(u16)(dat);
                es_modbus_rtu_status_gu8a  [index_u8]=ES_MODBUS_RTU_CRCH;
            }break;
            case ES_MODBUS_RTU_CRCH:{
                es_modbus_rtu_crc_buf_gu16a[index_u8]+=(u16)dat<<8;
                if(es_modbus_rtu_crc_buf_gu16a[index_u8]==es_modbus_rtu_uart_crc_gu16a[index_u8]){
                    #if (ES_MODBUS_RTU_CMD_ALL_EN)
                        switch(es_modbus_rtu_fun_code_gu8a[index_u8]){
                            #if (ES_MODBUS_RTU_CMD01_EN)
                                case 0x01:es_modbus_rtu_cmd_0x01(ch);break;
                            #endif
                            #if (ES_MODBUS_RTU_CMD02_EN)
                                case 0x02:es_modbus_rtu_cmd_0x02(ch);break;
                            #endif
                            #if (ES_MODBUS_RTU_CMD03_EN)
                                case 0x03:es_modbus_rtu_cmd_0x03(ch);break;
                            #endif
                            #if (ES_MODBUS_RTU_CMD04_EN)
                                case 0x04:es_modbus_rtu_cmd_0x04(ch);break;
                            #endif
                            #if (ES_MODBUS_RTU_CMD05_EN)
                                case 0x05:es_modbus_rtu_cmd_0x05(ch);break;
                            #endif
                            #if (ES_MODBUS_RTU_CMD06_EN)
                                case 0x06:es_modbus_rtu_cmd_0x06(ch);break;
                            #endif
                            #if (ES_MODBUS_RTU_CMD10_EN)
                                case 0x10:es_modbus_rtu_cmd_0x10(ch);break;
                            #endif
                            default:{
                                es_modbus_rtu_err_num(ch,es_modbus_rtu_fun_code_gu8a[index_u8],0x01);
                            }break;
                        }
                    #endif
                }
                #if (ES_MODBUS_RTU_CRC_ERR_EN)
                    else{
                        es_modbus_rtu_crc_err_callback(ch);
                    }
                #endif
                es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_READY;
            }break;
            #if (ES_MODBUS_RTU_CMD10_EN)
                case ES_MODBUS_RTU_BYTE_COUNT:{
                    es_modbus_rtu_cmd_count_gu8a[index_u8]=dat;
                    es_modbus_rtu_count_gu8a[index_u8]=0;
                    es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_DATAH;
                    es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                }break;
                case ES_MODBUS_RTU_DATAH:{
                    es_modbus_rtu_cmd_buf_gu16a [index_u8][es_modbus_rtu_count_gu8a[index_u8]/2]=((u16)(dat))<<8;
                    es_modbus_rtu_count_gu8a[index_u8]++;
                    if(es_modbus_rtu_count_gu8a[index_u8]==(u8)(es_modbus_rtu_cmd_count_gu8a[index_u8])){
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_CRCL;
                    }else{
                        es_modbus_rtu_status_gu8a   [index_u8]=ES_MODBUS_RTU_DATAL;
                    }
                    es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                }break;
                case ES_MODBUS_RTU_DATAL:{
                    es_modbus_rtu_cmd_buf_gu16a[index_u8][es_modbus_rtu_count_gu8a[index_u8]/2]+=((u16)(dat));
                    es_modbus_rtu_count_gu8a[index_u8]++;
                    if(es_modbus_rtu_count_gu8a[index_u8]==(u8)(es_modbus_rtu_cmd_count_gu8a[index_u8])){
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_CRCL;
                    }else{
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_DATAH;
                    }
                    es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                }break;
            #endif
        }
    }else{
        #if (ES_MODBUS_RTU_MASTER_EN)
            switch(es_modbus_rtu_status_gu8a[index_u8]){
                case ES_MODBUS_RTU_READY:{
                    if(es_modbus_rtu_send_id_gu8a[index_u8]==dat){
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_FUN_NUM;
                        es_modbus_rtu_fun_code_gu8a[index_u8]=0;
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(0xFFFF,dat);
                    }
                }break;
                case ES_MODBUS_RTU_FUN_NUM:{
                    es_modbus_rtu_fun_code_gu8a[index_u8]=dat;
                    if(es_modbus_rtu_fun_code_gu8a[index_u8]<127){
                        switch(es_modbus_rtu_fun_code_gu8a[index_u8]){
                            #if (ES_MODBUS_RTU_MASTER_CMD01_EN)
                                case 0x01:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD02_EN)
                                case 0x02:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD03_EN)
                                case 0x03:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD04_EN)
                                case 0x04:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD_01020304_EN)
                                {
                                    es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_RETURN_COUNT;
                                    es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                                }break;
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD05_EN)
                                case 0x05:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD06_EN)
                                case 0x06:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD10_EN)
                                case 0x10:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD_050610_EN)
                                {
                                    es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_ADDRH;
                                    es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                                }break;
                            #endif
                            default:{
                                es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_READY;
                            }break;
                        }
                    }else{
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_ERROR_CODE;
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                    }
                }break;
                case ES_MODBUS_RTU_ERROR_CODE:{
                    es_modbus_rtu_reply_count_gu8a[index_u8]=dat;
                    es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_CRCL;
                    es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                }break;
                #if (ES_MODBUS_RTU_MASTER_CMD_01020304_EN)
                    case ES_MODBUS_RTU_RETURN_COUNT:{
                        es_modbus_rtu_reply_count_gu8a[index_u8]=dat;
                        es_modbus_rtu_cmd_count_gu8a  [index_u8]=0;
                        switch(es_modbus_rtu_fun_code_gu8a[index_u8]){
                            default:break;
                            #if (ES_MODBUS_RTU_MASTER_CMD01_EN)
                                case 0x01:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD02_EN)
                                case 0x02:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD_0102_EN)
                                {
                                    es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_0102_RETURN;
                                }break;
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD03_EN)
                                case 0x03:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD04_EN)
                                case 0x04:
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD_0304_EN)
                                {
                                    es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_0304_RETURN;
                                }break;
                            #endif
                        }
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                    }break;
                #endif
                #if (ES_MODBUS_RTU_MASTER_CMD_0102_EN)
                    case ES_MODBUS_RTU_0102_RETURN:{
                        es_modbus_rtu_cmd_buf_gu16a[index_u8][es_modbus_rtu_cmd_count_gu8a[index_u8]++]=dat;
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                        if(es_modbus_rtu_cmd_count_gu8a[index_u8]>=es_modbus_rtu_reply_count_gu8a[index_u8]){
                            es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_CRCL;
                        }
                    }break;
                #endif
                #if (ES_MODBUS_RTU_MASTER_CMD_0304_EN)
                    case ES_MODBUS_RTU_0304_RETURN:{
                        if(es_modbus_rtu_cmd_count_gu8a[index_u8]%2){
                            es_modbus_rtu_cmd_buf_gu16a[index_u8][es_modbus_rtu_cmd_count_gu8a[index_u8]>>1]<<=8;
                            es_modbus_rtu_cmd_buf_gu16a[index_u8][es_modbus_rtu_cmd_count_gu8a[index_u8]>>1]+=dat;
                        }else{
                            es_modbus_rtu_cmd_buf_gu16a[index_u8][es_modbus_rtu_cmd_count_gu8a[index_u8]>>1]=dat;
                        }
                        es_modbus_rtu_cmd_count_gu8a[index_u8]++;
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                        if(es_modbus_rtu_cmd_count_gu8a[index_u8]>=es_modbus_rtu_reply_count_gu8a[index_u8]){
                            es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_CRCL;
                        }
                    }break;
                #endif
                #if (ES_MODBUS_RTU_MASTER_CMD_050610_EN)
                    case ES_MODBUS_RTU_ADDRH:{
                        es_modbus_rtu_cmd_buf_gu16a[index_u8][0]=(u16)dat<<8;
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_ADDRL;
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                    }break;
                    case ES_MODBUS_RTU_ADDRL:{
                        es_modbus_rtu_cmd_buf_gu16a[index_u8][0]+=(u16)(dat);
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_DATA_COUNTH;
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                    }break;
                    case ES_MODBUS_RTU_DATA_COUNTH:{
                        es_modbus_rtu_cmd_buf_gu16a[index_u8][1]=(u16)(dat)<<8;
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_DATA_COUNTL;
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                    }break;
                    case ES_MODBUS_RTU_DATA_COUNTL:{
                        es_modbus_rtu_cmd_buf_gu16a[index_u8][1]+=(u16)(dat);
                        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_CRCL;
                        es_modbus_rtu_uart_crc_gu16a[index_u8]=es_crc16(es_modbus_rtu_uart_crc_gu16a[index_u8],dat);
                    }break;
                #endif
                case ES_MODBUS_RTU_CRCL:{
                    es_modbus_rtu_crc_buf_gu16a[index_u8]=(u16)(dat);
                    es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_CRCH;
                }break;
                case ES_MODBUS_RTU_CRCH:{
                    es_modbus_rtu_crc_buf_gu16a[index_u8]+=(u16)(dat)<<8;
                    if(es_modbus_rtu_crc_buf_gu16a[index_u8]==es_modbus_rtu_uart_crc_gu16a[index_u8]){
                        switch(es_modbus_rtu_fun_code_gu8a[index_u8]){
                            default:break;
                            #if (ES_MODBUS_RTU_MASTER_CMD01_EN)
                                case 0x01:{
                                    for(i_u8=0;i_u8<es_modbus_rtu_data_count_gu16a[index_u8];i_u8++){
                                        mask_u8=0x01<<(i_u8%8);
                                        temp_u8=(i_u8/8);
                                        if(es_modbus_rtu_cmd_buf_gu16a[index_u8][temp_u8]&mask_u8){
                                            mask_u8=1;
                                        }else{
                                            mask_u8=0;
                                        }
                                        es_modbus_rtu_master_0x01_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_address_gu16a[index_u8]+i_u8,mask_u8);
                                    }
                                }break;
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD02_EN)
                                case 0x02:{
                                    for(i_u8=0;i_u8<es_modbus_rtu_data_count_gu16a[index_u8];i_u8++){
                                        mask_u8=0x01<<(i_u8%8);
                                        temp_u8=(i_u8/8);
                                        if(es_modbus_rtu_cmd_buf_gu16a[index_u8][temp_u8]&mask_u8){
                                            mask_u8=1;
                                        }else{
                                            mask_u8=0;
                                        }
                                        es_modbus_rtu_master_0x02_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_address_gu16a[index_u8]+i_u8,mask_u8);
                                    }
                                }break;
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD03_EN)
                                case 0x03:{
                                    for(i_u8=0;i_u8<es_modbus_rtu_data_count_gu16a[index_u8];i_u8++){
                                        es_modbus_rtu_master_0x03_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_address_gu16a[index_u8]+i_u8,es_modbus_rtu_cmd_buf_gu16a[index_u8][i_u8]);
                                    }
                                }break;
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD04_EN)
                                case 0x04:{
                                    for(i_u8=0;i_u8<es_modbus_rtu_data_count_gu16a[index_u8];i_u8++){
                                        es_modbus_rtu_master_0x04_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_address_gu16a[index_u8]+i_u8,es_modbus_rtu_cmd_buf_gu16a[index_u8][i_u8]);
                                    }
                                }break;
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD05_EN)
                                case 0x05:{
                                    if(es_modbus_rtu_cmd_buf_gu16a[index_u8][1]){
                                        es_modbus_rtu_master_0x05_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_cmd_buf_gu16a[index_u8][0],1);
                                    }else{
                                        es_modbus_rtu_master_0x05_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_cmd_buf_gu16a[index_u8][0],0);
                                    }
                                }break;
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD06_EN)
                                case 0x06:{
                                    es_modbus_rtu_master_0x06_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_cmd_buf_gu16a[index_u8][0],es_modbus_rtu_cmd_buf_gu16a[index_u8][1]);
                                }break;
                            #endif
                            #if (ES_MODBUS_RTU_MASTER_CMD10_EN)
                                case 0x10:{
                                    es_modbus_rtu_master_0x10_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_cmd_buf_gu16a[index_u8][0],es_modbus_rtu_cmd_buf_gu16a[index_u8][1]);
                                }break;
                            #endif
                        }
                        if(es_modbus_rtu_fun_code_gu8a[index_u8]>127){
                            es_modbus_rtu_master_err_code_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8],es_modbus_rtu_fun_code_gu8a[index_u8]-0x80,es_modbus_rtu_reply_count_gu8a[index_u8]);
                        }
                    }else{
                        #if (ES_MODBUS_RTU_MASTER_CRC_ERR_EN)
                            es_modbus_rtu_master_crc_err_callback(ch,es_modbus_rtu_send_id_gu8a[index_u8]);
                        #endif
                    }
                }break;
            }
        #endif
    }
}

#if (ES_MODBUS_RTU_MASTER_EN)
    void es_modbus_rtu_set_slave_mode(u8 ch){
        u8 index_u8;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        es_modbus_rtu_mode_gu8a  [index_u8]=ES_MODBUS_RTU_MODE_SLAVE;
        es_modbus_rtu_status_gu8a[index_u8]=ES_MODBUS_RTU_READY;
    }
#endif

#if ((ES_MODBUS_RTU_MASTER_EN)&&(ES_MODBUS_RTU_MASTER_CMD01_EN))
    void es_modbus_rtu_master_0x01(u8 ch,u8 id,u16 addr,u16 len){
        u16 crc_u16;
        u8 index_u8;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        es_modbus_rtu_mode_gu8a[index_u8]=ES_MODBUS_RTU_MODE_MASTER;
        es_modbus_rtu_send_id_gu8a[index_u8]=id;
        crc_u16=es_send_whit_crc(ch,0xFFFF,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x01);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        if(len==0)len=1;
        if(len>2000)len=2000;
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len   ));
        uart_char(ch,(u8)(crc_u16   ));
        uart_char(ch,(u8)(crc_u16>>8));
    }
#endif

#if ((ES_MODBUS_RTU_MASTER_EN)&&(ES_MODBUS_RTU_MASTER_CMD02_EN))
    void es_modbus_rtu_master_0x02(u8 ch,u8 id,u16 addr,u16 len){
        u16 crc_u16;
        u8 index_u8;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        es_modbus_rtu_mode_gu8a[index_u8]=ES_MODBUS_RTU_MODE_MASTER;
        es_modbus_rtu_send_id_gu8a[index_u8]=id;
        crc_u16=es_send_whit_crc(ch,0xFFFF,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x02);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        if(len==0)len=1;
        if(len>2000)len=2000;
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len   ));
        uart_char(ch,(u8)(crc_u16   ));
        uart_char(ch,(u8)(crc_u16>>8));
    }
#endif

#if ((ES_MODBUS_RTU_MASTER_EN)&&(ES_MODBUS_RTU_MASTER_CMD03_EN))
    void es_modbus_rtu_master_0x03(u8 ch,u8 id,u16 addr,u16 len){
        u16 crc_u16;
        u8 index_u8;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        es_modbus_rtu_mode_gu8a[index_u8]=ES_MODBUS_RTU_MODE_MASTER;
        es_modbus_rtu_send_id_gu8a[index_u8]=id;
        crc_u16=es_send_whit_crc(ch,0xFFFF,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x03);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        if(len==0)len=1;
        if(len>125)len=125;
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len   ));
        uart_char(ch,(u8)(crc_u16   ));
        uart_char(ch,(u8)(crc_u16>>8));
    }
#endif

#if ((ES_MODBUS_RTU_MASTER_EN)&&(ES_MODBUS_RTU_MASTER_CMD04_EN))
    void es_modbus_rtu_master_0x04(u8 ch,u8 id,u16 addr,u16 len){
        u16 crc_u16;
        u8 index_u8;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        es_modbus_rtu_mode_gu8a[index_u8]=ES_MODBUS_RTU_MODE_MASTER;
        es_modbus_rtu_send_id_gu8a[index_u8]=id;
        crc_u16=es_send_whit_crc(ch,0xFFFF,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x04);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        if(len==0)len=1;
        if(len>125)len=125;
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len   ));
        uart_char(ch,(u8)(crc_u16   ));
        uart_char(ch,(u8)(crc_u16>>8));
    }
#endif

#if ((ES_MODBUS_RTU_MASTER_EN)&&(ES_MODBUS_RTU_MASTER_CMD05_EN))
    void es_modbus_rtu_master_0x05(u8 ch,u8 id,u16 addr,u8 dat){
        u16 crc_u16;
        u8 index_u8;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        es_modbus_rtu_mode_gu8a[index_u8]=ES_MODBUS_RTU_MODE_MASTER;
        es_modbus_rtu_send_id_gu8a[index_u8]=id;
        crc_u16=es_send_whit_crc(ch,0xFFFF,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x05);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        if(dat){
            crc_u16=es_send_whit_crc(ch,crc_u16,0xFF);
        }else{
            crc_u16=es_send_whit_crc(ch,crc_u16,0x00);
        }
        crc_u16=es_send_whit_crc(ch,crc_u16,0x00);
        uart_char(ch,(u8)(crc_u16   ));
        uart_char(ch,(u8)(crc_u16>>8));
    }
#endif

#if ((ES_MODBUS_RTU_MASTER_EN)&&(ES_MODBUS_RTU_MASTER_CMD06_EN))
    void es_modbus_rtu_master_0x06(u8 ch,u8 id,u16 addr,u16 dat){
        u16 crc_u16;
        u8 index_u8;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        es_modbus_rtu_mode_gu8a[index_u8]=ES_MODBUS_RTU_MODE_MASTER;
        es_modbus_rtu_send_id_gu8a[index_u8]=id;
        crc_u16=es_send_whit_crc(ch,0xFFFF,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x06);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(dat>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(dat   ));
        uart_char(ch,(u8)(crc_u16   ));
        uart_char(ch,(u8)(crc_u16>>8));
    }
#endif

#if ((ES_MODBUS_RTU_MASTER_EN)&&(ES_MODBUS_RTU_MASTER_CMD10_EN))
    void es_modbus_rtu_master_0x10(u8 ch,u8 id,u16 addr,u16 * dat,u16 len){
        u16 crc_u16,i_u16;
        u8 index_u8;
        index_u8=ecbm_stream_modbus_chtoid(ch);
        es_modbus_rtu_mode_gu8a[index_u8]=ES_MODBUS_RTU_MODE_MASTER;
        es_modbus_rtu_send_id_gu8a[index_u8]=id;
        crc_u16=es_send_whit_crc(ch,0xFFFF,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x10);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        if(len==0)len=1;
        if(len>120)len=120;
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len   ));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(len*2 ));
        for(i_u16=0;i_u16<len;i_u16++){
            crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(dat[i_u16]>>8));
            crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(dat[i_u16]   ));
        }
        uart_char(ch,(u8)(crc_u16   ));
        uart_char(ch,(u8)(crc_u16>>8));
    }
#endif
#endif



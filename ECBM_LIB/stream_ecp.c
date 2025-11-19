#include "ecbm_core.h"
#if (ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_ECP_CH_COUNT)

u8  es_ecp_status_gu8a   [ECBM_STREAM_ECP_CH_COUNT];
u8  es_ecp_data_len_gu8a [ECBM_STREAM_ECP_CH_COUNT];
u8  es_ecp_count_gu8a    [ECBM_STREAM_ECP_CH_COUNT];
u8  es_ecp_source_id_gu8a[ECBM_STREAM_ECP_CH_COUNT];
u8  es_ecp_target_id_gu8a[ECBM_STREAM_ECP_CH_COUNT];
u8  es_ecp_operation_gu8a[ECBM_STREAM_ECP_CH_COUNT];
u16 es_ecp_addr16_ex_gu16a[ECBM_STREAM_ECP_CH_COUNT];
u16 es_ecp_addr16_gu16a   [ECBM_STREAM_ECP_CH_COUNT];
u16 es_ecp_crc_gu16a      [ECBM_STREAM_ECP_CH_COUNT];
u16 es_ecp_crc_buf_gu16a  [ECBM_STREAM_ECP_CH_COUNT];
u8  es_ecp_data_buf_gu8a[ECBM_STREAM_ECP_CH_COUNT][ES_ECP_DATA_BUF_MAX];

u8 ecbm_stream_ecp_chtoid(u8 ch){
    switch(ch){
        case 1:return (0);break;
        case 2:return ( ECBM_STREAM_CH1_EN*ECBM_STREAM_ECP_CH1_EN);break;
        case 3:return ((ECBM_STREAM_CH1_EN*ECBM_STREAM_ECP_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_ECP_CH2_EN));break;
        case 4:return ((ECBM_STREAM_CH1_EN*ECBM_STREAM_ECP_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_ECP_CH2_EN)+(ECBM_STREAM_CH3_EN*ECBM_STREAM_ECP_CH3_EN));break;
    }
    return (0);
}

void es_ecp_reset(u8 ch){
    u8 id_u8;
    id_u8=ecbm_stream_ecp_chtoid(ch);
    es_ecp_status_gu8a    [id_u8]=ES_ECP_READY;
    es_ecp_data_len_gu8a  [id_u8]=0;
    es_ecp_count_gu8a     [id_u8]=0;
    es_ecp_source_id_gu8a [id_u8]=0;
    es_ecp_target_id_gu8a [id_u8]=0;
    es_ecp_operation_gu8a [id_u8]=0;
    es_ecp_addr16_ex_gu16a[id_u8]=0;
    es_ecp_addr16_gu16a   [id_u8]=0;
    es_ecp_crc_gu16a      [id_u8]=0;
    es_ecp_crc_buf_gu16a  [id_u8]=0;
}

void es_ecp_reply(u8 ch,u8 len,u8 cmd){
    u16 crc_u16,i_u16;
    u8 index_u8;
    index_u8=ecbm_stream_ecp_chtoid(ch);
    crc_u16=es_send_whit_crc(ch,0xffff,0xEC);
    crc_u16=es_send_whit_crc(ch,crc_u16, (len));
    crc_u16=es_send_whit_crc(ch,crc_u16,~(len));
    crc_u16=es_send_whit_crc(ch,crc_u16,es_ecp_source_id_gu8a[index_u8]);
    crc_u16=es_send_whit_crc(ch,crc_u16,es_ecp_get_id(ch));
    crc_u16=es_send_whit_crc(ch,crc_u16,cmd);
    crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_ecp_addr16_ex_gu16a[index_u8]>>8));
    crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_ecp_addr16_ex_gu16a[index_u8]   ));
    crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_ecp_addr16_gu16a[index_u8]>>8));
    crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(es_ecp_addr16_gu16a[index_u8]   ));
    for(i_u16=0;i_u16<(u16)(len);i_u16++){
        crc_u16=es_send_whit_crc(ch,crc_u16,es_ecp_data_buf_gu8a[index_u8][i_u16]);
    }
    uart_char(ch,(u8)(crc_u16>>8));
    uart_char(ch,(u8)(crc_u16));
    uart_char(ch,0xBE);
}

void es_ecp_cmd00(u8 ch){
    u8 res_u8,index_u8;
    index_u8=ecbm_stream_ecp_chtoid(ch);
    res_u8=es_ecp_trig(ch,es_ecp_addr16_gu16a[index_u8]);
    if((es_ecp_target_id_gu8a[index_u8])||(es_ecp_source_id_gu8a[index_u8]==255)){
        es_ecp_data_buf_gu8a[index_u8][0]=res_u8;
        if(res_u8){
            es_ecp_reply(ch,1,ES_ECP_CMD_ERROR_OPERATE);
        }else{
            es_ecp_reply(ch,1,ES_ECP_CMD_TRIG_REPLY);
        }
    }
}

void es_ecp_cmd02(u8 ch){
    u8 arg_len_u8,res_u8,index_u8;
    index_u8=ecbm_stream_ecp_chtoid(ch);
    arg_len_u8=es_ecp_data_buf_gu8a[index_u8][0];
    res_u8=es_ecp_read(ch,es_ecp_addr16_gu16a[index_u8],es_ecp_data_buf_gu8a[index_u8],arg_len_u8);
    if((es_ecp_target_id_gu8a[index_u8])||(es_ecp_source_id_gu8a[index_u8]==255)){
        if(res_u8){
            es_ecp_data_buf_gu8a[index_u8][0]=res_u8;
            es_ecp_reply(ch,1,ES_ECP_CMD_ERROR_OPERATE);
        }else{
            es_ecp_reply(ch,arg_len_u8,ES_ECP_CMD_READ_REPLY);
        }
    }
}

void es_ecp_cmd04(u8 ch){
    u8 res_u8,index_u8;
    index_u8=ecbm_stream_ecp_chtoid(ch);
    res_u8=es_ecp_write(ch,es_ecp_addr16_gu16a[index_u8],es_ecp_data_buf_gu8a[index_u8],es_ecp_data_len_gu8a[index_u8]);
    if((es_ecp_target_id_gu8a[index_u8])||(es_ecp_source_id_gu8a[index_u8]==255)){
        es_ecp_data_buf_gu8a[index_u8][0]=res_u8;
        if(res_u8){
            es_ecp_reply(ch,1,ES_ECP_CMD_ERROR_OPERATE);
        }else{
            es_ecp_reply(ch,1,ES_ECP_CMD_WRITE_REPLY);
        }
    }
}

void es_ecp_cmd0608(u8 ch,u8 cmd){
    u8 res1_u8,res2_u8,temp_u8;
    u16 i_u16;
    u8 index_u8;
    index_u8=ecbm_stream_ecp_chtoid(ch);
    for(i_u16=0;i_u16<(u16)(es_ecp_data_len_gu8a[index_u8]);i_u16++){
        res1_u8=es_ecp_read(ch,es_ecp_addr16_gu16a[index_u8]+i_u16,&temp_u8,1);
        if(cmd==ES_ECP_CMD_SET_BIT){
            temp_u8|=es_ecp_data_buf_gu8a[index_u8][i_u16];
        }
        if(cmd==ES_ECP_CMD_RESET_BIT){
            temp_u8&=es_ecp_data_buf_gu8a[index_u8][i_u16];
        }
        res2_u8=es_ecp_write(ch,es_ecp_addr16_gu16a[index_u8]+i_u16,&temp_u8,1);
        if((res1_u8+res2_u8)){
            break;
        }
    }
    if((es_ecp_target_id_gu8a[index_u8])||(es_ecp_source_id_gu8a[index_u8]==255)){
        if(res1_u8){
            es_ecp_data_buf_gu8a[index_u8][0]=res1_u8;
            es_ecp_reply(ch,1,ES_ECP_CMD_ERROR_OPERATE);
        }else{
            if(res2_u8){
                es_ecp_data_buf_gu8a[index_u8][0]=res2_u8;
                es_ecp_reply(ch,1,ES_ECP_CMD_ERROR_OPERATE);
            }else{
                es_ecp_reply(ch,1,ES_ECP_CMD_SET_BIT_REPLY);
            }
        }
    }
}

#if (ES_ECP_MASTER_EN)
    void es_ecp_master_write(u8 ch,u8 id,u16 addr,u8 * buf,u8 len){
        u8 count_u8;
        u16 crc_u16;
        crc_u16=es_send_whit_crc(ch,0xFFFF ,0xEC);
        crc_u16=es_send_whit_crc(ch,crc_u16, (len));
        crc_u16=es_send_whit_crc(ch,crc_u16,~(len));
        crc_u16=es_send_whit_crc(ch,crc_u16,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,es_ecp_get_id(ch));
        crc_u16=es_send_whit_crc(ch,crc_u16,ES_ECP_CMD_WRITE);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x00);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x00);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        for(count_u8=0;count_u8<len;count_u8++){
            crc_u16=es_send_whit_crc(ch,crc_u16,buf[count_u8]);
        }
        uart_char(ch,(u8)(crc_u16>>8));
        uart_char(ch,(u8)(crc_u16));
        uart_char(ch,0xBE);
    }
#endif

#if (ES_ECP_MASTER_EN)
    void es_ecp_master_read(u8 ch,u8 id,u16 addr,u8 len){
        u16 crc_u16;
        crc_u16=es_send_whit_crc(ch,crc_u16,0xEC);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x01);
        crc_u16=es_send_whit_crc(ch,crc_u16,0xFE);
        crc_u16=es_send_whit_crc(ch,crc_u16,id);
        crc_u16=es_send_whit_crc(ch,crc_u16,es_ecp_get_id(ch));
        crc_u16=es_send_whit_crc(ch,crc_u16,ES_ECP_CMD_READ);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x00);
        crc_u16=es_send_whit_crc(ch,crc_u16,0x00);
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr>>8));
        crc_u16=es_send_whit_crc(ch,crc_u16,(u8)(addr   ));
        crc_u16=es_send_whit_crc(ch,crc_u16,len);
        uart_char(ch,(u8)(crc_u16>>8));
        uart_char(ch,(u8)(crc_u16));
        uart_char(ch,0xBE);
    }
#endif

void es_ecp_exe(u8 ch,u8 dat){
    u8 index_u8;
    index_u8=ecbm_stream_ecp_chtoid(ch);
    switch(es_ecp_status_gu8a[index_u8]){
        case ES_ECP_READY:{
            if(dat==0xEC){
                es_ecp_status_gu8a[index_u8]=ES_ECP_GET_DATA_LEN;
                es_ecp_crc_gu16a[index_u8]=es_crc16(0xffff,0xEC);
            }
        }break;
        case ES_ECP_GET_DATA_LEN:{
            es_ecp_data_len_gu8a[index_u8]=dat;
            es_ecp_status_gu8a[index_u8]=ES_ECP_CHECK_DATA_LEN;
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
        }break;
        case ES_ECP_CHECK_DATA_LEN:{
            if(es_ecp_data_len_gu8a[index_u8]==(~dat)){
                es_ecp_status_gu8a[index_u8]=ES_ECP_GET_TARGET_ID;
                es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
            }else{
                if(es_ecp_data_len_gu8a==0xEC){
                    es_ecp_status_gu8a[index_u8]=ES_ECP_CHECK_DATA_LEN;
                    es_ecp_data_len_gu8a[index_u8]=dat;
                    es_ecp_crc_gu16a[index_u8]=es_crc16(0xffff,0xEC);
                    es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
                }else{
                    if(dat==0xEC){
                        es_ecp_status_gu8a[index_u8]=ES_ECP_GET_DATA_LEN;
                        es_ecp_crc_gu16a[index_u8]=es_crc16(0xffff,0xEC);
                    }else{
                        es_ecp_status_gu8a[index_u8]=ES_ECP_READY;
                    }
                }
            }
        }break;
        case ES_ECP_GET_TARGET_ID:{
            es_ecp_target_id_gu8a[index_u8]=dat;
            es_ecp_status_gu8a[index_u8]=ES_ECP_GET_SOURCE_ID;
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
        }break;
        case ES_ECP_GET_SOURCE_ID:{
            es_ecp_source_id_gu8a[index_u8]=dat;
            es_ecp_status_gu8a[index_u8]=ES_ECP_GET_OPERATION;
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
        }break;
        case ES_ECP_GET_OPERATION:{
            es_ecp_operation_gu8a[index_u8]=dat;
            es_ecp_status_gu8a[index_u8]=ES_ECP_GET_ADDR_31_24;
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
        }break;
        case ES_ECP_GET_ADDR_31_24:{
            es_ecp_addr16_ex_gu16a[index_u8]=(u16)(dat);
            es_ecp_status_gu8a[index_u8]=ES_ECP_GET_ADDR_23_16;
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],0x00);
        }break;
        case ES_ECP_GET_ADDR_23_16:{
            es_ecp_addr16_ex_gu16a[index_u8]<<=8;
            es_ecp_addr16_ex_gu16a[index_u8]+=(u16)(dat);
            es_ecp_status_gu8a[index_u8]=ES_ECP_GET_ADDR_15_8;
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],0x00);
        }break;
        case ES_ECP_GET_ADDR_15_8:{
            es_ecp_addr16_gu16a[index_u8]=(u16)(dat);
            es_ecp_status_gu8a[index_u8]=ES_ECP_GET_ADDR_7_0;
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
        }break;
        case ES_ECP_GET_ADDR_7_0:{
            es_ecp_addr16_gu16a[index_u8]<<=8;
            es_ecp_addr16_gu16a[index_u8]+=(u16)(dat);
            if(es_ecp_data_len_gu8a[index_u8]){
                es_ecp_status_gu8a[index_u8]=ES_ECP_GET_DATA;
                es_ecp_count_gu8a[index_u8]=0;
            }else{
                es_ecp_status_gu8a[index_u8]=ES_ECP_GET_CRC_H;
            }
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
        }break;
        case ES_ECP_GET_DATA:{
            es_ecp_data_buf_gu8a[index_u8][es_ecp_count_gu8a[index_u8]++]=dat;
            if(es_ecp_count_gu8a[index_u8]>=es_ecp_data_len_gu8a[index_u8]){
                es_ecp_status_gu8a[index_u8]=ES_ECP_GET_CRC_H;
            }
            es_ecp_crc_gu16a[index_u8]=es_crc16(es_ecp_crc_gu16a[index_u8],dat);
        }break;
        case ES_ECP_GET_CRC_H:{
            es_ecp_crc_buf_gu16a[index_u8]=(u16)(dat);
            es_ecp_status_gu8a[index_u8]=ES_ECP_GET_CRC_L;
        }break;
        case ES_ECP_GET_CRC_L:{
            es_ecp_crc_buf_gu16a[index_u8]<<=8;
            es_ecp_crc_buf_gu16a[index_u8]+=(u16)(dat);
            es_ecp_status_gu8a[index_u8]=ES_ECP_END;
        }break;
        case ES_ECP_END:{
            es_ecp_status_gu8a[index_u8]=ES_ECP_READY;
            if((dat==0xBE)&&(es_ecp_crc_buf_gu16a[index_u8]==es_ecp_crc_gu16a[index_u8])){
                if((es_ecp_target_id_gu8a[index_u8]==es_ecp_get_id(ch))||(es_ecp_target_id_gu8a[index_u8]==0)){
                    switch(es_ecp_operation_gu8a[index_u8]){
                        case ES_ECP_CMD_TRIG:
                            es_ecp_cmd00(ch);
                        break;
                        case ES_ECP_CMD_TRIG_REPLY:
                        break;

                        case ES_ECP_CMD_READ:
                            es_ecp_cmd02(ch);
                        break;
                        case ES_ECP_CMD_READ_REPLY:
                            #if (ES_ECP_MASTER_EN)
                            es_ecp_read_callback(ch,es_ecp_addr16_gu16a[index_u8],es_ecp_data_buf_gu8a[index_u8],es_ecp_data_len_gu8a[index_u8]);
                            #endif
                        break;


                        case ES_ECP_CMD_WRITE:
                            es_ecp_cmd04(ch);
                        break;
                        case ES_ECP_CMD_WRITE_REPLY:
                        break;

                        case ES_ECP_CMD_SET_BIT:
                        case ES_ECP_CMD_RESET_BIT:
                            es_ecp_cmd0608(ch,es_ecp_operation_gu8a[index_u8]);
                        break;
                    }
                }
            }
        }break;
    }
}
#endif



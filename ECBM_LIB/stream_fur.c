#include "ecbm_core.h"
#if (ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_FUR_CH_COUNT)

u8  es_fur_status_gu8a [ECBM_STREAM_FUR_CH_COUNT];
u16 es_fur_addr_gu16a  [ECBM_STREAM_FUR_CH_COUNT];
u16 es_fur_dat16_gu16a [ECBM_STREAM_FUR_CH_COUNT];
u8  es_fur_id_gu8a     [ECBM_STREAM_FUR_CH_COUNT];
u8  es_fur_dat8_gu8a   [ECBM_STREAM_FUR_CH_COUNT];
u8  es_fur_operate_gu8a[ECBM_STREAM_FUR_CH_COUNT];
u8  es_fur_temp8_gu8a  [ECBM_STREAM_FUR_CH_COUNT];

u8 ecbm_stream_fur_chtoid(u8 ch){
    switch(ch){
        case 1:return (0);break;
        case 2:return ( ECBM_STREAM_CH1_EN*ECBM_STREAM_FUR_CH1_EN);break;
        case 3:return ((ECBM_STREAM_CH1_EN*ECBM_STREAM_FUR_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_FUR_CH2_EN));break;
        case 4:return ((ECBM_STREAM_CH1_EN*ECBM_STREAM_FUR_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_FUR_CH2_EN)+(ECBM_STREAM_CH3_EN*ECBM_STREAM_FUR_CH3_EN));break;
    }
    return (0);
}

void es_fur_reset(u8 ch){
    u8 id_u8;
    id_u8=ecbm_stream_fur_chtoid(ch);
    es_fur_status_gu8a [id_u8]=FUR_GET_ADDR;
    es_fur_addr_gu16a  [id_u8]=0;
    es_fur_dat16_gu16a [id_u8]=0;
    es_fur_id_gu8a     [id_u8]=0;
    es_fur_dat8_gu8a   [id_u8]=0;
    es_fur_operate_gu8a[id_u8]=0;
    es_fur_temp8_gu8a  [id_u8]=0;
}

void es_fur_send_num_10(u8 ch,u16 num){
    u8 a_u8,b_u8,c_u8,d_u8,e_u8;
    a_u8=num       /10000;
    b_u8=num%10000/1000;
    c_u8=num%1000/100;
    d_u8=num%100/10;
    e_u8=num%10/1;
    if(a_u8)                uart_char(ch,a_u8+'0');
    if(a_u8|b_u8)           uart_char(ch,b_u8+'0');
    if(a_u8|b_u8|c_u8)      uart_char(ch,c_u8+'0');
    if(a_u8|b_u8|c_u8|d_u8) uart_char(ch,d_u8+'0');
                            uart_char(ch,e_u8+'0');
}

void es_fur_send_num_16(u8 ch,u16 num){
    u8 i_u8;
    u16 temp_u16;
    temp_u16=num;
    for(i_u8=0;i_u8<4;i_u8++){
        if((temp_u16&0xF000)<0xA000){
            uart_char(ch,'0'+(temp_u16&0xF000)>>12);
        }else{
            uart_char(ch,'A'+((temp_u16&0xF000)>>12)-10);
        }
        temp_u16<<=4;
    }
}

void es_fur_exe(u8 ch,u8 dat){
    u16 temp_u16,mask_u16;
    u8  operate_u8,id_u8;
    id_u8=ecbm_stream_fur_chtoid(ch);
    switch(es_fur_status_gu8a[id_u8]){
        case FUR_READY:{

        }break;
        case FUR_GET_ADDR:{
            if((dat>='0')&&(dat<='9')){
                es_fur_addr_gu16a[id_u8]*=10;
                es_fur_addr_gu16a[id_u8]+=(dat-'0');
            }else if(dat=='@'){
                es_fur_status_gu8a[id_u8]=FUR_GET_ID;
            }else if((dat==']')||(dat==')')){
                es_fur_status_gu8a[id_u8]=FUR_GET_OP;
            }else if((dat=='i')||(dat=='I')){
                es_fur_status_gu8a[id_u8]=FUR_CMD_ID;
            }else{
                es_fur_status_gu8a[id_u8]=FUR_READY;
            }
        }break;
        case FUR_CMD_ID:{
            if((dat=='d')||(dat=='D')){
                es_fur_operate_gu8a[id_u8]|=FUR_FBID;
            }else if(dat==']'){
                es_fur_status_gu8a[id_u8]=FUR_GET_OP;
            }else{
                es_fur_status_gu8a[id_u8]=FUR_READY;
            }
        }break;
        case FUR_GET_ID:{
            if((dat>='0')&&(dat<='9')){
                es_fur_id_gu8a[id_u8]*=10;
                es_fur_id_gu8a[id_u8]+=(dat-'0');
            }else if(dat==']'){
                es_fur_status_gu8a[id_u8]=FUR_GET_OP;
            }else{
                es_fur_status_gu8a[id_u8]=FUR_READY;
            }
        }break;
        case FUR_GET_OP:{
            if(dat=='+'){
                es_fur_operate_gu8a[id_u8]|=FUR_ADD;
                es_fur_status_gu8a [id_u8] =FUR_GET_OP_EX;
            }else if(dat=='-'){
                es_fur_operate_gu8a[id_u8]|=FUR_DEC;
                es_fur_status_gu8a [id_u8] =FUR_GET_OP_EX;
            }else if(dat=='*'){
                es_fur_operate_gu8a[id_u8]|=FUR_MUL;
                es_fur_status_gu8a [id_u8] =FUR_GET_OP_EX;
            }else if(dat=='/'){
                es_fur_operate_gu8a[id_u8]|=FUR_DIV;
                es_fur_status_gu8a [id_u8] =FUR_GET_OP_EX;
            }else if(dat=='&'){
                es_fur_operate_gu8a[id_u8]|=FUR_AND;
                es_fur_status_gu8a [id_u8] =FUR_GET_OP_EX;
            }else if(dat=='|'){
                es_fur_operate_gu8a[id_u8]|=FUR_OR;
                es_fur_status_gu8a [id_u8] =FUR_GET_OP_EX;
            }else if(dat=='^'){
                es_fur_operate_gu8a[id_u8]|=FUR_XOR;
                es_fur_status_gu8a [id_u8] =FUR_GET_OP_EX;
            }else if(dat=='.'){
                es_fur_operate_gu8a[id_u8]|=FUR_BIT;
                es_fur_status_gu8a [id_u8] =FUR_GET_OP_EX;
            }else if(dat=='='){
                es_fur_operate_gu8a[id_u8]|=FUR_EQU;
                es_fur_status_gu8a [id_u8] =FUR_GET_DATA;
            }else if(dat=='x'){
                es_fur_operate_gu8a[id_u8]|=FUR_HEX;
            }else if(dat=='?'){
                es_fur_operate_gu8a[id_u8]|=FUR_READ;
                es_fur_status_gu8a [id_u8] =FUR_WAIT_END;
            }else{
                es_fur_status_gu8a[id_u8]=FUR_READY;
            }
        }break;
        case FUR_GET_OP_EX:{
            if((dat>='0')&&(dat<='9')){
                es_fur_dat8_gu8a[id_u8]*=10;
                es_fur_dat8_gu8a[id_u8]+=(dat-'0');
            }else if(dat=='='){
                es_fur_dat8_gu8a[id_u8]&=0x0F;
                es_fur_status_gu8a[id_u8]=FUR_GET_DATA;
            }else{
                es_fur_status_gu8a[id_u8]=FUR_READY;
            }
        }break;
        case FUR_GET_DATA:{
            if((dat>='0')&&(dat<='9')){
                es_fur_dat16_gu16a[id_u8]*=10;
                es_fur_dat16_gu16a[id_u8]+=(dat-'0');
            }else if(dat==';'){
                es_fur_status_gu8a[id_u8]=FUR_END_DO;
            }else if((dat=='x')||(dat=='X')){
                es_fur_dat16_gu16a[id_u8]=0;
                es_fur_operate_gu8a[id_u8]|=FUR_HEX;
                es_fur_status_gu8a[id_u8]=FUR_GET_DATA16;
            }else{
                es_fur_status_gu8a[id_u8]=FUR_READY;
            }
        }break;
        case FUR_GET_DATA16:{
            if((dat>='0')&&(dat<='9')){
                es_fur_dat16_gu16a[id_u8]*=16;
                es_fur_dat16_gu16a[id_u8]+=(dat-'0');
            }else if((dat>='a')&&(dat<='f')){
                es_fur_dat16_gu16a[id_u8]*=16;
                es_fur_dat16_gu16a[id_u8]+=(dat-'a'+10);
            }else if((dat>='A')&&(dat<='F')){
                es_fur_dat16_gu16a[id_u8]*=16;
                es_fur_dat16_gu16a[id_u8]+=(dat-'A'+10);
            }else if(dat==';'){
                es_fur_status_gu8a[id_u8]=FUR_END_DO;
            }else{
                es_fur_status_gu8a[id_u8]=FUR_READY;
            }
        }break;
        case FUR_WAIT_END:{
            if(dat==';'){
                es_fur_status_gu8a[id_u8]=FUR_END_DO;
            }
        }break;
    }
    if(es_fur_status_gu8a[id_u8]==FUR_END_DO){
        operate_u8=es_fur_operate_gu8a[id_u8]&0x0F;
        if(operate_u8==FUR_FBID){
            #if (ECBM_STREAM_FUR_UART_SEND_EN)
                uart_char(ch,'i');
                uart_char(ch,'d');
                uart_char(ch,'=');
                es_fur_send_num_10(ch,(u16)es_fur_get_id(ch));
                uart_char(ch,';');
                uart_char(ch,'\r');
                uart_char(ch,'\n');
            #endif
        }else{
            if( (es_fur_id_gu8a[id_u8]==0)||
                (es_fur_id_gu8a[id_u8]==es_fur_get_id(ch))){
                temp_u16=es_fur_read_reg(ch,es_fur_addr_gu16a[id_u8]);
                if(es_fur_operate_gu8a[id_u8]&FUR_WRITE){
                    switch(operate_u8){
                        case FUR_READ:

                        break;
                        case FUR_ADD:
                            temp_u16+=es_fur_dat16_gu16a[id_u8];
                        break;
                        case FUR_DEC:
                            temp_u16-=es_fur_dat16_gu16a[id_u8];
                        break;
                        case FUR_MUL:
                            temp_u16*=es_fur_dat16_gu16a[id_u8];
                        break;
                        case FUR_DIV:
                            temp_u16/=es_fur_dat16_gu16a[id_u8];
                        break;
                        case FUR_AND:
                            temp_u16&=es_fur_dat16_gu16a[id_u8];
                        break;
                        case FUR_OR:
                            temp_u16|=es_fur_dat16_gu16a[id_u8];
                        break;
                        case FUR_XOR:
                            temp_u16^=es_fur_dat16_gu16a[id_u8];
                        break;
                        case FUR_BIT:
                            mask_u16=1<<es_fur_dat8_gu8a[id_u8];
                            if(es_fur_dat16_gu16a[id_u8]){
                                temp_u16|=mask_u16;
                            }else{
                                temp_u16&=~mask_u16;
                            }
                        break;
                        case FUR_EQU:
                            temp_u16=es_fur_dat16_gu16a[id_u8];
                        break;
                    }
                    es_fur_write_reg(ch,es_fur_addr_gu16a[id_u8],temp_u16);
                    #if (ECBM_STREAM_FUR_UART_SEND_EN)
                        uart_char(ch,'(');
                        es_fur_send_num_10(ch,es_fur_addr_gu16a[id_u8]);
                        uart_char(ch,')');
                        uart_char(ch,'=');
                        if(es_fur_operate_gu8a[id_u8]&FUR_HEX){
                            uart_char(ch,'0');
                            uart_char(ch,'x');
                            es_fur_send_num_16(ch,temp_u16);
                        }else{
                            es_fur_send_num_10(ch,temp_u16);
                        }
                        uart_char(ch,';');
                        uart_char(ch,'\r');
                        uart_char(ch,'\n');
                    #endif
                }else{
                    #if (ECBM_STREAM_FUR_MATER_EN)
                        es_fur_master_receive_callback(ch,es_fur_addr_gu16a,es_fur_dat16_gu16a);
                    #endif
                }
            }
        }
        es_fur_status_gu8a[id_u8]=FUR_READY;
    }
    if(dat=='['){
        es_fur_reset(ch);
        es_fur_operate_gu8a[id_u8]|=FUR_WRITE;
    }else if(dat=='('){
        es_fur_reset(ch);
    }
}

#if (ECBM_STREAM_FUR_MATER_EN)
    void es_fur_master_send(u8 ch,u16 addr,u8 id,u16 dat){
        uart_char(ch,'[');
        es_fur_send_num_10(ch,addr);
        if(id){
            uart_char(ch,'@');
            es_fur_send_num_10(ch,id);
        }
        uart_char(ch,']');
        uart_char(ch,'=');
        es_fur_send_num_10(ch,dat);
        uart_char(ch,';');
        uart_char(ch,'\r');
        uart_char(ch,'\n');
    }
#endif

#if (ECBM_STREAM_FUR_MATER_EN)
    void es_fur_master_read(u8 ch,u16 addr,u8 id){
        uart_char(ch,'[');
        es_fur_send_num_10(ch,addr);
        if(id){
            uart_char(ch,'@');
            es_fur_send_num_10(ch,id);
        }
        uart_char(ch,']');
        uart_char(ch,'?');
        uart_char(ch,';');
        uart_char(ch,'\r');
        uart_char(ch,'\n');
    }
#endif
#endif



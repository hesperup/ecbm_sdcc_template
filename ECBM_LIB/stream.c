#include "ecbm_core.h"
#if ((ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_CH_COUNT))

#if (ECBM_STREAM_CH1_EN)
u8 xdata ecbm_stream_ch1_buf_gxu8a[ECBM_STREAM_CH1_SZIE];
u8 ecbm_stream_ch1_point_gu8;
u8 ecbm_stream_ch1_read_point_gu8;
u8 ecbm_stream_ch1_count_gu8;
u8 ecbm_stream_ch1_time_gu8;
u8 ecbm_stream_ch1_status_gu8;
#endif

#if (ECBM_STREAM_CH2_EN)
u8 xdata ecbm_stream_ch2_buf_gxu8a[ECBM_STREAM_CH2_SZIE];
u8 ecbm_stream_ch2_point_gu8;
u8 ecbm_stream_ch2_read_point_gu8;
u8 ecbm_stream_ch2_count_gu8;
u8 ecbm_stream_ch2_time_gu8;
u8 ecbm_stream_ch2_status_gu8;
#endif

#if (ECBM_STREAM_CH3_EN)
u8 xdata ecbm_stream_ch3_buf_gxu8a[ECBM_STREAM_CH3_SZIE];
u8 ecbm_stream_ch3_point_gu8;
u8 ecbm_stream_ch3_read_point_gu8;
u8 ecbm_stream_ch3_count_gu8;
u8 ecbm_stream_ch3_time_gu8;
u8 ecbm_stream_ch3_status_gu8;
#endif

#if (ECBM_STREAM_CH4_EN)
u8 xdata ecbm_stream_ch4_buf_gxu8a[ECBM_STREAM_CH4_SZIE];
u8 ecbm_stream_ch4_point_gu8;
u8 ecbm_stream_ch4_read_point_gu8;
u8 ecbm_stream_ch4_count_gu8;
u8 ecbm_stream_ch4_time_gu8;
u8 ecbm_stream_ch4_status_gu8;
#endif


void ecbm_stream_init(void){
    u8 i_u8;
    #if (ECBM_STREAM_CH1_EN)
        for(i_u8=0;i_u8<ECBM_STREAM_CH1_SZIE;i_u8++){
            ecbm_stream_ch1_buf_gxu8a[i_u8]=0;
        }
        ecbm_stream_ch1_point_gu8=0;
        ecbm_stream_ch1_read_point_gu8=0;
        ecbm_stream_ch1_count_gu8=0;
        ecbm_stream_ch1_time_gu8=0;
        ecbm_stream_ch1_status_gu8=0;
    #endif
    #if (ECBM_STREAM_CH2_EN)
        for(i_u8=0;i_u8<ECBM_STREAM_CH2_SZIE;i_u8++){
            ecbm_stream_ch2_buf_gxu8a[i_u8]=0;
        }
        ecbm_stream_ch2_point_gu8=0;
        ecbm_stream_ch2_read_point_gu8=0;
        ecbm_stream_ch2_count_gu8=0;
        ecbm_stream_ch2_time_gu8=0;
        ecbm_stream_ch2_status_gu8=0;
    #endif
    #if (ECBM_STREAM_CH3_EN)
        for(i_u8=0;i_u8<ECBM_STREAM_CH3_SZIE;i_u8++){
            ecbm_stream_ch3_buf_gxu8a[i_u8]=0;
        }
        ecbm_stream_ch3_point_gu8=0;
        ecbm_stream_ch3_read_point_gu8=0;
        ecbm_stream_ch3_count_gu8=0;
        ecbm_stream_ch3_time_gu8=0;
        ecbm_stream_ch3_status_gu8=0;
    #endif
    #if (ECBM_STREAM_CH4_EN)
        for(i_u8=0;i_u8<ECBM_STREAM_CH4_SZIE;i_u8++){
            ecbm_stream_ch4_buf_gxu8a[i_u8]=0;
        }
        ecbm_stream_ch4_point_gu8=0;
        ecbm_stream_ch4_read_point_gu8=0;
        ecbm_stream_ch4_count_gu8=0;
        ecbm_stream_ch4_time_gu8=0;
        ecbm_stream_ch4_status_gu8=0;
    #endif
}

void ecbm_stream_timer_run(void){
    #if (ECBM_STREAM_CH1_EN)
        if(ecbm_stream_ch1_status_gu8&ECBM_STREAM_TIME_EN){
            ecbm_stream_ch1_time_gu8++;
            if(ecbm_stream_ch1_time_gu8>ECBM_STREAM_TIME_MAX){
                ecbm_stream_ch1_status_gu8|=ECBM_STREAM_TIME_OUT;
            }
            if(ecbm_stream_ch1_time_gu8>ECBM_STREAM_IDLE_MAX){
                ecbm_stream_ch1_status_gu8|=ECBM_STREAM_UART_IDLE;
                ecbm_stream_ch1_status_gu8&=~ECBM_STREAM_TIME_EN;
            }
        }
    #endif

    #if (ECBM_STREAM_CH2_EN)
        if(ecbm_stream_ch2_status_gu8&ECBM_STREAM_TIME_EN){
            ecbm_stream_ch2_time_gu8++;
            if(ecbm_stream_ch2_time_gu8>ECBM_STREAM_TIME_MAX){
                ecbm_stream_ch2_status_gu8|=ECBM_STREAM_TIME_OUT;
            }
            if(ecbm_stream_ch2_time_gu8>ECBM_STREAM_IDLE_MAX){
                ecbm_stream_ch2_status_gu8|=ECBM_STREAM_UART_IDLE;
                ecbm_stream_ch2_status_gu8&=~ECBM_STREAM_TIME_EN;
            }
        }
    #endif

    #if (ECBM_STREAM_CH3_EN)
        if(ecbm_stream_ch3_status_gu8&ECBM_STREAM_TIME_EN){
            ecbm_stream_ch3_time_gu8++;
            if(ecbm_stream_ch3_time_gu8>ECBM_STREAM_TIME_MAX){
                ecbm_stream_ch3_status_gu8|=ECBM_STREAM_TIME_OUT;
            }
            if(ecbm_stream_ch3_time_gu8>ECBM_STREAM_IDLE_MAX){
                ecbm_stream_ch3_status_gu8|=ECBM_STREAM_UART_IDLE;
                ecbm_stream_ch3_status_gu8&=~ECBM_STREAM_TIME_EN;
            }
        }
    #endif

    #if (ECBM_STREAM_CH4_EN)
        if(ecbm_stream_ch4_status_gu8&ECBM_STREAM_TIME_EN){
            ecbm_stream_ch4_time_gu8++;
            if(ecbm_stream_ch4_time_gu8>ECBM_STREAM_TIME_MAX){
                ecbm_stream_ch4_status_gu8|=ECBM_STREAM_TIME_OUT;
            }
            if(ecbm_stream_ch4_time_gu8>ECBM_STREAM_IDLE_MAX){
                ecbm_stream_ch4_status_gu8|=ECBM_STREAM_UART_IDLE;
                ecbm_stream_ch4_status_gu8&=~ECBM_STREAM_TIME_EN;
            }
        }
    #endif
}

void ecbm_stream_main(void){
    u8 dat_u8;

    #if (ECBM_STREAM_CH1_EN)
        if(ecbm_stream_ch1_status_gu8&ECBM_STREAM_TIME_OUT){
            if((ecbm_stream_ch1_count_gu8>0)&&(ecbm_stream_ch1_count_gu8<ECBM_STREAM_CH1_SZIE)){
                ecbm_stream_ch1_status_gu8&=~ECBM_STREAM_TIME_OUT;
                while(ecbm_stream_ch1_count_gu8){
                    dat_u8=ecbm_stream_ch1_buf_gxu8a[ecbm_stream_ch1_read_point_gu8];
                    ecbm_stream_ch1_count_gu8--;
                    #if (ECBM_STREAM_USER_CH1_EN)
                    ecbm_stream_user_exe(1,dat_u8);
                    #endif
                    #if (ECBM_STREAM_FUR_CH1_EN)
                    es_fur_exe(1,dat_u8);
                    #endif
                    #if (ECBM_STREAM_MODBUS_CH1_EN)
                    es_modbus_rtu_exe(1,dat_u8);
                    #endif
                    #if (ECBM_STREAM_ECP_CH1_EN)
                    es_ecp_exe(1,dat_u8);
                    #endif
                    ecbm_stream_ch1_read_point_gu8++;
                    if(ecbm_stream_ch1_read_point_gu8>=ECBM_STREAM_CH1_SZIE){
                        ecbm_stream_ch1_read_point_gu8=0;
                    }
                }
            }
        }
        if(ecbm_stream_ch1_status_gu8&ECBM_STREAM_UART_IDLE){
            ecbm_stream_ch1_status_gu8&=~ECBM_STREAM_UART_IDLE;
            #if (ECBM_STREAM_FUR_CH1_EN)
                es_fur_reset(1);
            #endif
            #if (ECBM_STREAM_MODBUS_CH1_EN)
                es_modbus_rtu_reset(1);
            #endif
            #if (ECBM_STREAM_ECP_CH1_EN)
                es_ecp_reset(1);
            #endif
        }
    #endif

    #if (ECBM_STREAM_CH2_EN)
        if(ecbm_stream_ch2_status_gu8&ECBM_STREAM_TIME_OUT){
            if((ecbm_stream_ch2_count_gu8>0)&&(ecbm_stream_ch2_count_gu8<ECBM_STREAM_CH2_SZIE)){
                ecbm_stream_ch2_status_gu8&=~ECBM_STREAM_TIME_OUT;
                while(ecbm_stream_ch2_count_gu8){
                    dat_u8=ecbm_stream_ch2_buf_gxu8a[ecbm_stream_ch2_read_point_gu8];
                    ecbm_stream_ch2_count_gu8--;
                    #if (ECBM_STREAM_USER_CH2_EN)
                    ecbm_stream_user_exe(2,dat_u8);
                    #endif
                    #if (ECBM_STREAM_FUR_CH2_EN)
                    es_fur_exe(2,dat_u8);
                    #endif
                    #if (ECBM_STREAM_MODBUS_CH2_EN)
                    es_modbus_rtu_exe(2,dat_u8);
                    #endif
                    #if (ECBM_STREAM_ECP_CH2_EN)
                    es_ecp_exe(2,dat_u8);
                    #endif
                    ecbm_stream_ch2_read_point_gu8++;
                    if(ecbm_stream_ch2_read_point_gu8>=ECBM_STREAM_CH2_SZIE){
                        ecbm_stream_ch2_read_point_gu8=0;
                    }
                }
            }
        }
        if(ecbm_stream_ch2_status_gu8&ECBM_STREAM_UART_IDLE){
            ecbm_stream_ch2_status_gu8&=~ECBM_STREAM_UART_IDLE;
            #if (ECBM_STREAM_FUR_CH2_EN)
                es_fur_reset(2);
            #endif
            #if (ECBM_STREAM_MODBUS_CH2_EN)
                es_modbus_rtu_reset(2);
            #endif
            #if (ECBM_STREAM_ECP_CH2_EN)
                es_ecp_reset(2);
            #endif
        }
    #endif

    #if (ECBM_STREAM_CH3_EN)
        if(ecbm_stream_ch3_status_gu8&ECBM_STREAM_TIME_OUT){
            if((ecbm_stream_ch3_count_gu8>0)&&(ecbm_stream_ch3_count_gu8<ECBM_STREAM_CH3_SZIE)){
                ecbm_stream_ch3_status_gu8&=~ECBM_STREAM_TIME_OUT;
                while(ecbm_stream_ch3_count_gu8){
                    dat_u8=ecbm_stream_ch3_buf_gxu8a[ecbm_stream_ch3_read_point_gu8];
                    ecbm_stream_ch3_count_gu8--;
                    #if (ECBM_STREAM_USER_CH3_EN)
                    ecbm_stream_user_exe(3,dat_u8);
                    #endif
                    #if (ECBM_STREAM_FUR_CH3_EN)
                    es_fur_exe(3,dat_u8);
                    #endif
                    #if (ECBM_STREAM_MODBUS_CH3_EN)
                    es_modbus_rtu_exe(3,dat_u8);
                    #endif
                    #if (ECBM_STREAM_ECP_CH3_EN)
                    es_ecp_exe(3,dat_u8);
                    #endif
                    ecbm_stream_ch3_read_point_gu8++;
                    if(ecbm_stream_ch3_read_point_gu8>=ECBM_STREAM_CH3_SZIE){
                        ecbm_stream_ch3_read_point_gu8=0;
                    }
                }
            }
        }
        if(ecbm_stream_ch3_status_gu8&ECBM_STREAM_UART_IDLE){
            ecbm_stream_ch3_status_gu8&=~ECBM_STREAM_UART_IDLE;
            #if (ECBM_STREAM_FUR_CH3_EN)
                es_fur_reset(3);
            #endif
            #if (ECBM_STREAM_MODBUS_CH3_EN)
                es_modbus_rtu_reset(3);
            #endif
            #if (ECBM_STREAM_ECP_CH3_EN)
                es_ecp_reset(3);
            #endif
        }
    #endif

    #if (ECBM_STREAM_CH4_EN)
        if(ecbm_stream_ch4_status_gu8&ECBM_STREAM_TIME_OUT){
            if((ecbm_stream_ch4_count_gu8>0)&&(ecbm_stream_ch4_count_gu8<ECBM_STREAM_CH4_SZIE)){
                ecbm_stream_ch4_status_gu8&=~ECBM_STREAM_TIME_OUT;
                while(ecbm_stream_ch4_count_gu8){
                    dat_u8=ecbm_stream_ch4_buf_gxu8a[ecbm_stream_ch4_read_point_gu8];
                    ecbm_stream_ch4_count_gu8--;
                    #if (ECBM_STREAM_USER_CH4_EN)
                    ecbm_stream_user_exe(4,dat_u8);
                    #endif
                    #if (ECBM_STREAM_FUR_CH4_EN)
                    es_fur_exe(4,dat_u8);
                    #endif
                    #if (ECBM_STREAM_MODBUS_CH4_EN)
                    es_modbus_rtu_exe(4,dat_u8);
                    #endif
                    #if (ECBM_STREAM_ECP_CH4_EN)
                    es_ecp_exe(4,dat_u8);
                    #endif
                    ecbm_stream_ch4_read_point_gu8++;
                    if(ecbm_stream_ch4_read_point_gu8>=ECBM_STREAM_CH4_SZIE){
                        ecbm_stream_ch4_read_point_gu8=0;
                    }
                }
            }
        }
        if(ecbm_stream_ch4_status_gu8&ECBM_STREAM_UART_IDLE){
            ecbm_stream_ch4_status_gu8&=~ECBM_STREAM_UART_IDLE;
            #if (ECBM_STREAM_FUR_CH4_EN)
                es_fur_reset(4);
            #endif
            #if (ECBM_STREAM_MODBUS_CH4_EN)
                es_modbus_rtu_reset(4);
            #endif
            #if (ECBM_STREAM_ECP_CH4_EN)
                es_ecp_reset(4);
            #endif
        }
    #endif
}

#if (ECBM_STREAM_CMP_EN)
void ecbm_stream_strcmp(u8 dat,u8 code * str,u8 * count){
    if(str[*count]==dat){
        (*count)++;
    }else{
        *count=0;
        if(str[*count]==dat){
            (*count)++;
        }
    }
}
#endif

#if (ECBM_STREAM_MODBUS_CH_COUNT+ECBM_STREAM_ECP_CH_COUNT)
    u16 es_crc16(u16 crc,u8 buf){
        u8 j;
        u16 crc_buf;
        crc_buf=crc^buf;
        for(j=0;j<8;j++){
            if(crc_buf&0x01){
                crc_buf=(crc_buf>>1)^0xA001;
            }else{
                crc_buf>>=1;
            }
        }
        return crc_buf;
    }
    u16 es_send_whit_crc(u8 ch,u16 crc,u8 dat){
        uart_char(ch,dat);
        return es_crc16(crc,dat);
    }
#endif
#endif



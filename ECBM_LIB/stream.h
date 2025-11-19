#ifndef _ECBM_STREAM_H_
#define _ECBM_STREAM_H_



#define ECBM_STREAM_VERSION "V2.0"






#define ECBM_STREAM_TIME_MS  (20)
#define ECBM_STREAM_TIME_MAX (ECBM_STREAM_TIME_MS/10)





#define ECBM_STREAM_IDLE_MS  (80)
#define ECBM_STREAM_IDLE_MAX (ECBM_STREAM_IDLE_MS/10)





#define ECBM_STREAM_CH1_EN (1)


#define ECBM_STREAM_CH1_SZIE    (10)

#define ECBM_STREAM_USER_CH1_EN  (0)



#define ECBM_STREAM_FUR_CH1_EN  (0)



#define ECBM_STREAM_MODBUS_CH1_EN (1)




#define ECBM_STREAM_ECP_CH1_EN (0)




#define ECBM_STREAM_CH2_EN (0)


#define ECBM_STREAM_CH2_SZIE    (10)

#define ECBM_STREAM_USER_CH2_EN  (0)



#define ECBM_STREAM_FUR_CH2_EN (0)



#define ECBM_STREAM_MODBUS_CH2_EN (0)




#define ECBM_STREAM_ECP_CH2_EN (0)




#define ECBM_STREAM_CH3_EN (0)


#define ECBM_STREAM_CH3_SZIE    (10)

#define ECBM_STREAM_USER_CH3_EN  (0)



#define ECBM_STREAM_FUR_CH3_EN (0)



#define ECBM_STREAM_MODBUS_CH3_EN (0)




#define ECBM_STREAM_ECP_CH3_EN (0)




#define ECBM_STREAM_CH4_EN (0)


#define ECBM_STREAM_CH4_SZIE    (10)

#define ECBM_STREAM_USER_CH4_EN  (0)



#define ECBM_STREAM_FUR_CH4_EN (0)



#define ECBM_STREAM_MODBUS_CH4_EN (0)




#define ECBM_STREAM_ECP_CH4_EN (0)

#define ECBM_STREAM_CH_COUNT (ECBM_STREAM_CH1_EN+ECBM_STREAM_CH2_EN+ECBM_STREAM_CH3_EN+ECBM_STREAM_CH4_EN)





#define ECBM_STREAM_CMP_EN (0)



#define ECBM_STREAM_FUR_CH_COUNT ((ECBM_STREAM_CH1_EN*ECBM_STREAM_FUR_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_FUR_CH2_EN)+(ECBM_STREAM_CH3_EN*ECBM_STREAM_FUR_CH3_EN)+(ECBM_STREAM_CH4_EN*ECBM_STREAM_FUR_CH4_EN))



#define ECBM_STREAM_FUR_UART_SEND_EN (1)



#define ECBM_STREAM_FUR_MATER_EN (1)




#define ECBM_STREAM_MODBUS_CH_COUNT ((ECBM_STREAM_CH1_EN*ECBM_STREAM_MODBUS_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_MODBUS_CH2_EN)+(ECBM_STREAM_CH3_EN*ECBM_STREAM_MODBUS_CH3_EN)+(ECBM_STREAM_CH4_EN*ECBM_STREAM_MODBUS_CH4_EN))



#define ES_MODBUS_RTU_CMD01_EN (1)


#define ES_MODBUS_RTU_CMD05_EN (1)


#define ES_MODBUS_RTU_CMD03_EN (1)


#define ES_MODBUS_RTU_CMD06_EN (1)


#define ES_MODBUS_RTU_CMD10_EN (1)


#define ES_MODBUS_RTU_CMD02_EN (1)


#define ES_MODBUS_RTU_CMD04_EN (1)


#define ES_MODBUS_RTU_CRC_ERR_EN (0)

#define ES_MODBUS_RTU_CMD_BIT_EN  (ES_MODBUS_RTU_CMD01_EN+ES_MODBUS_RTU_CMD05_EN)
#define ES_MODBUS_RTU_CMD_REG_EN  (ES_MODBUS_RTU_CMD03_EN+ES_MODBUS_RTU_CMD06_EN+ES_MODBUS_RTU_CMD10_EN)
#define ES_MODBUS_RTU_CMD_IO_EN   (ES_MODBUS_RTU_CMD02_EN+ES_MODBUS_RTU_CMD04_EN)
#define ES_MODBUS_RTU_CMD_ALL_EN  (ES_MODBUS_RTU_CMD_BIT_EN+ES_MODBUS_RTU_CMD_REG_EN+ES_MODBUS_RTU_CMD_IO_EN)



#define ES_MODBUS_RTU_MASTER_EN (0)


#define ES_MODBUS_RTU_MASTER_CMD01_EN (1)


#define ES_MODBUS_RTU_MASTER_CMD05_EN (1)


#define ES_MODBUS_RTU_MASTER_CMD03_EN (1)


#define ES_MODBUS_RTU_MASTER_CMD06_EN (1)


#define ES_MODBUS_RTU_MASTER_CMD10_EN (1)


#define ES_MODBUS_RTU_MASTER_CMD02_EN (1)


#define ES_MODBUS_RTU_MASTER_CMD04_EN (1)


#define ES_MODBUS_RTU_MASTER_CRC_ERR_EN (0)

#define ES_MODBUS_RTU_MASTER_CMD_0102_EN        (ES_MODBUS_RTU_MASTER_CMD01_EN+ES_MODBUS_RTU_MASTER_CMD02_EN)
#define ES_MODBUS_RTU_MASTER_CMD_0304_EN        (ES_MODBUS_RTU_MASTER_CMD03_EN+ES_MODBUS_RTU_MASTER_CMD04_EN)
#define ES_MODBUS_RTU_MASTER_CMD_01020304_EN    (ES_MODBUS_RTU_MASTER_CMD_0102_EN+ES_MODBUS_RTU_MASTER_CMD_0304_EN)
#define ES_MODBUS_RTU_MASTER_CMD_050610_EN      (ES_MODBUS_RTU_MASTER_CMD05_EN+ES_MODBUS_RTU_MASTER_CMD06_EN+ES_MODBUS_RTU_MASTER_CMD10_EN)





#define ES_MODBUS_RTU_BUF_SIZE  (10)





#define ECBM_STREAM_ECP_CH_COUNT ((ECBM_STREAM_CH1_EN*ECBM_STREAM_ECP_CH1_EN)+(ECBM_STREAM_CH2_EN*ECBM_STREAM_ECP_CH2_EN)+(ECBM_STREAM_CH3_EN*ECBM_STREAM_ECP_CH3_EN)+(ECBM_STREAM_CH4_EN*ECBM_STREAM_ECP_CH4_EN))



#define ES_ECP_DATA_BUF_MAX (32)


#define ES_ECP_MASTER_EN (1)





#include "ecbm_core.h"

#define ECBM_STREAM_TIME_EN   (0x01)
#define ECBM_STREAM_TIME_OUT  (0x02)
#define ECBM_STREAM_UART_IDLE (0x04)

#if ((ECBM_10MS_EN)&&(ECBM_STREAM_LIB_EN))
    #if (ECBM_STREAM_CH1_EN)
    extern u8 xdata ecbm_stream_ch1_buf_gxu8a[ECBM_STREAM_CH1_SZIE];
    extern u8 ecbm_stream_ch1_point_gu8;
    extern u8 ecbm_stream_ch1_read_point_gu8;
    extern u8 ecbm_stream_ch1_count_gu8;
    extern u8 ecbm_stream_ch1_time_gu8;
    extern u8 ecbm_stream_ch1_status_gu8;
    #endif
    #if (ECBM_STREAM_CH2_EN)
    extern u8 xdata ecbm_stream_ch2_buf_gxu8a[ECBM_STREAM_CH2_SZIE];
    extern u8 ecbm_stream_ch2_point_gu8;
    extern u8 ecbm_stream_ch2_read_point_gu8;
    extern u8 ecbm_stream_ch2_count_gu8;
    extern u8 ecbm_stream_ch2_time_gu8;
    extern u8 ecbm_stream_ch2_status_gu8;
    #endif
    #if (ECBM_STREAM_CH3_EN)
    extern u8 xdata ecbm_stream_ch3_buf_gxu8a[ECBM_STREAM_CH3_SZIE];
    extern u8 ecbm_stream_ch3_point_gu8;
    extern u8 ecbm_stream_ch3_read_point_gu8;
    extern u8 ecbm_stream_ch3_count_gu8;
    extern u8 ecbm_stream_ch3_time_gu8;
    extern u8 ecbm_stream_ch3_status_gu8;
    #endif
    #if (ECBM_STREAM_CH4_EN)
    extern u8 xdata ecbm_stream_ch4_buf_gxu8a[ECBM_STREAM_CH4_SZIE];
    extern u8 ecbm_stream_ch4_point_gu8;
    extern u8 ecbm_stream_ch4_read_point_gu8;
    extern u8 ecbm_stream_ch4_count_gu8;
    extern u8 ecbm_stream_ch4_time_gu8;
    extern u8 ecbm_stream_ch4_status_gu8;
    #endif
#endif



extern void ecbm_stream_user_exe(u8 ch,u8 dat);


extern void ecbm_stream_init(void);

extern void ecbm_stream_main(void);

extern void ecbm_stream_strcmp(u8 dat,u8 code * str,u8 * count);


extern void ecbm_stream_timer_run(void);

extern u16 es_crc16(u16 crc,u8 buf);
extern u16 es_send_whit_crc(u8 ch,u16 crc,u8 dat);
#endif



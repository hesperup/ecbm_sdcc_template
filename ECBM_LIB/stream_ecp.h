#ifndef _ECBM_STREAM_ECP_H_
#define _ECBM_STREAM_ECP_H_


#include "ecbm_core.h"

#define ES_ECP_READY             (0)
#define ES_ECP_GET_DATA_LEN      (1)
#define ES_ECP_CHECK_DATA_LEN    (2)
#define ES_ECP_GET_TARGET_ID     (3)
#define ES_ECP_GET_SOURCE_ID     (4)
#define ES_ECP_GET_OPERATION     (5)
#define ES_ECP_GET_ADDR_31_24    (6)
#define ES_ECP_GET_ADDR_23_16    (7)
#define ES_ECP_GET_ADDR_15_8     (8)
#define ES_ECP_GET_ADDR_7_0      (9)
#define ES_ECP_GET_DATA          (10)
#define ES_ECP_GET_CRC_H         (11)
#define ES_ECP_GET_CRC_L         (12)
#define ES_ECP_END               (13)

#define ES_ECP_CMD_TRIG             (0)
#define ES_ECP_CMD_TRIG_REPLY       (1)
#define ES_ECP_CMD_READ             (2)
#define ES_ECP_CMD_READ_REPLY       (3)
#define ES_ECP_CMD_WRITE            (4)
#define ES_ECP_CMD_WRITE_REPLY      (5)
#define ES_ECP_CMD_SET_BIT          (6)
#define ES_ECP_CMD_SET_BIT_REPLY    (7)
#define ES_ECP_CMD_RESET_BIT        (8)
#define ES_ECP_CMD_RESET_BIT_REPLY  (9)

#define ES_ECP_CMD_AUTO_UPDATA      (200)
#define ES_ECP_CMD_ERROR_OPERATE    (254)
#define ES_ECP_CMD_ERROR_CRC        (255)

#if (ECBM_STREAM_ECP_CH_COUNT)
    extern u8  es_ecp_status_gu8a   [ECBM_STREAM_ECP_CH_COUNT];
    extern u8  es_ecp_data_len_gu8a [ECBM_STREAM_ECP_CH_COUNT];
    extern u8  es_ecp_count_gu8a    [ECBM_STREAM_ECP_CH_COUNT];
    extern u8  es_ecp_source_id_gu8a[ECBM_STREAM_ECP_CH_COUNT];
    extern u8  es_ecp_target_id_gu8a[ECBM_STREAM_ECP_CH_COUNT];
    extern u8  es_ecp_operation_gu8a[ECBM_STREAM_ECP_CH_COUNT];
    extern u16 es_ecp_addr16_ex_gu16a[ECBM_STREAM_ECP_CH_COUNT];
    extern u16 es_ecp_addr16_gu16a [ECBM_STREAM_ECP_CH_COUNT];
    extern u16 es_ecp_crc_gu16a    [ECBM_STREAM_ECP_CH_COUNT];
    extern u16 es_ecp_crc_buf_gu16a[ECBM_STREAM_ECP_CH_COUNT];
    extern u8  es_ecp_data_buf_gu8a[ECBM_STREAM_ECP_CH_COUNT][ES_ECP_DATA_BUF_MAX];
#endif


void es_ecp_reset(u8 ch);


extern u8 es_ecp_get_id(u8 ch);

extern u8 es_ecp_trig(u8 ch,u16 addr);

extern u8 es_ecp_write(u8 ch,u16 addr,u8 * buf,u8 len);

extern u8 es_ecp_read(u8 ch,u16 addr,u8 * buf,u8 len);

extern void es_ecp_read_callback(u8 ch,u16 addr,u8 * buf,u8 len);


extern void es_ecp_reply(u8 ch,u8 len,u8 cmd);

extern void es_ecp_cmd00(u8 ch);

extern void es_ecp_cmd02(u8 ch);

extern void es_ecp_cmd04(u8 ch);

extern void es_ecp_cmd0608(u8 ch,u8 cmd);

extern void es_ecp_master_write(u8 ch,u8 id,u16 addr,u8 * buf,u8 len);

extern void es_ecp_master_read(u8 ch,u8 id,u16 addr,u8 len);

extern void es_ecp_exe(u8 ch,u8 dat);
#endif



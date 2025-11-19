#ifndef _ECBM_STREAM_MODBUS_H_
#define _ECBM_STREAM_MODBUS_H_


#include "ecbm_core.h"

#define ES_MODBUS_RTU_READY           (0)
#define ES_MODBUS_RTU_WAIT            (1)
#define ES_MODBUS_RTU_FUN_NUM         (2)
#define ES_MODBUS_RTU_ADDRH           (3)
#define ES_MODBUS_RTU_ADDRL           (4)
#define ES_MODBUS_RTU_DATA_COUNTH     (5)
#define ES_MODBUS_RTU_DATA_COUNTL     (6)
#define ES_MODBUS_RTU_COUNT_ERR       (7)
#define ES_MODBUS_RTU_CRCH            (8)
#define ES_MODBUS_RTU_CRCL            (9)
#define ES_MODBUS_RTU_DO              (10)
#define ES_MODBUS_RTU_DATAH           (11)
#define ES_MODBUS_RTU_DATAL           (12)
#define ES_MODBUS_RTU_BYTE_COUNT      (13)
#define ES_MODBUS_RTU_RETURN_COUNT    (14)
#define ES_MODBUS_RTU_0102_RETURN     (15)
#define ES_MODBUS_RTU_0304_RETURN     (16)
#define ES_MODBUS_RTU_ERROR_CODE      (17)

#define ES_MODBUS_RTU_MODE_SLAVE      (0)
#define ES_MODBUS_RTU_MODE_MASTER     (1)

#if (ECBM_STREAM_MODBUS_CH_COUNT)
    extern u8  es_modbus_rtu_mode        [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u8  es_modbus_rtu_send_id     [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u8  es_modbus_rtu_reply_count [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u8  es_modbus_rtu_status      [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u8  es_modbus_rtu_broadcast_en[ECBM_STREAM_MODBUS_CH_COUNT];
    extern u8  es_modbus_rtu_fun_code    [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u16 es_modbus_rtu_address     [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u16 es_modbus_rtu_data_count  [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u16 es_modbus_rtu_uart_crc    [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u16 es_modbus_rtu_crc_buf     [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u8  es_modbus_rtu_cmd_count   [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u8  es_modbus_rtu_count_gu8a  [ECBM_STREAM_MODBUS_CH_COUNT];
    extern u16 es_modbus_rtu_cmd_buf[ECBM_STREAM_MODBUS_CH_COUNT][ES_MODBUS_RTU_BUF_SIZE];
#endif



extern u8 es_modbus_rtu_get_id(u8 ch);

extern void es_modbus_cmd_read_io_bit(u8 ch,u16 addr,u8 * dat);

extern void es_modbus_cmd_read_io_reg(u8 ch,u16 addr,u16 * dat);

extern void es_modbus_cmd_write_bit(u8 ch,u16 addr,u8 dat);

extern void es_modbus_cmd_read_bit(u8 ch,u16 addr,u8 * dat);

extern void es_modbus_cmd_write_reg(u8 ch,u16 addr,u16 dat);

extern void es_modbus_cmd_read_reg(u8 ch,u16 addr,u16 * dat);

extern void es_modbus_rtu_crc_err_callback(u8 ch);


extern void es_modbus_rtu_master_crc_err_callback(u8 ch,u8 id);

extern void es_modbus_rtu_master_err_code_callback(u8 ch,u8 id,u8 cmd,u8 err_code);

extern void es_modbus_rtu_master_0x01_callback(u8 ch,u8 id,u16 addr,u8 dat);

extern void es_modbus_rtu_master_0x02_callback(u8 ch,u8 id,u16 addr,u8 dat);

extern void es_modbus_rtu_master_0x03_callback(u8 ch,u8 id,u16 addr,u16 dat);

extern void es_modbus_rtu_master_0x04_callback(u8 ch,u8 id,u16 addr,u16 dat);

extern void es_modbus_rtu_master_0x05_callback(u8 ch,u8 id,u16 addr,u8 dat);

extern void es_modbus_rtu_master_0x06_callback(u8 ch,u8 id,u16 addr,u16 dat);

extern void es_modbus_rtu_master_0x10_callback(u8 ch,u8 id,u16 addr,u16 len);


extern void es_modbus_rtu_set_slave_mode(u8 ch);

extern void es_modbus_rtu_master_0x01(u8 ch,u8 id,u16 addr,u16 len);

extern void es_modbus_rtu_master_0x02(u8 ch,u8 id,u16 addr,u16 len);

extern void es_modbus_rtu_master_0x03(u8 ch,u8 id,u16 addr,u16 len);

extern void es_modbus_rtu_master_0x04(u8 ch,u8 id,u16 addr,u16 len);

extern void es_modbus_rtu_master_0x05(u8 ch,u8 id,u16 addr,u8 dat);

extern void es_modbus_rtu_master_0x06(u8 ch,u8 id,u16 addr,u16 dat);

extern void es_modbus_rtu_master_0x10(u8 ch,u8 id,u16 addr,u16 * dat,u16 len);


extern void es_modbus_rtu_reset(u8 ch);

extern void es_modbus_rtu_err_num(u8 ch,u8 fun_num,u8 err_num);

extern void es_modbus_rtu_cmd_0x01(u8 ch);

extern void es_modbus_rtu_cmd_0x02(u8 ch);

extern void es_modbus_rtu_cmd_0x03(u8 ch);

extern void es_modbus_rtu_cmd_0x04(u8 ch);

extern void es_modbus_rtu_cmd_0x05(u8 ch);

extern void es_modbus_rtu_cmd_0x06(u8 ch);

extern void es_modbus_rtu_cmd_0x10(u8 ch);

extern void es_modbus_rtu_exe(u8 ch,u8 dat);
#endif



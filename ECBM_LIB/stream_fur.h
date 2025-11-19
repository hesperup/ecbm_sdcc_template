#ifndef _ECBM_STREAM_FUR_H_
#define _ECBM_STREAM_FUR_H_


#include "ecbm_core.h"


#define FUR_READ    (0x00)
#define FUR_ADD     (0x01)
#define FUR_DEC     (0x02)
#define FUR_MUL     (0x03)
#define FUR_DIV     (0x04)
#define FUR_AND     (0x05)
#define FUR_OR      (0x06)
#define FUR_XOR     (0x07)
#define FUR_BIT     (0x08)
#define FUR_EQU     (0x09)
#define FUR_FBID    (0x0A)

#define FUR_WRITE   (0x80)
#define FUR_HEX     (0x40)

#define FUR_READY       (0)
#define FUR_GET_ADDR    (1)
#define FUR_GET_ID      (2)
#define FUR_GET_OP      (3)
#define FUR_GET_OP_EX   (4)
#define FUR_GET_DATA    (5)
#define FUR_GET_DATA16  (6)
#define FUR_CMD_ID      (7)
#define FUR_WAIT_END    (8)
#define FUR_END_DO      (9)

#if (ECBM_STREAM_FUR_CH_COUNT)
extern u8  es_fur_status_gu8a [ECBM_STREAM_FUR_CH_COUNT];
extern u16 es_fur_addr_gu16a  [ECBM_STREAM_FUR_CH_COUNT];
extern u16 es_fur_dat16_gu16a [ECBM_STREAM_FUR_CH_COUNT];
extern u8  es_fur_id_gu8a     [ECBM_STREAM_FUR_CH_COUNT];
extern u8  es_fur_dat8_gu8a   [ECBM_STREAM_FUR_CH_COUNT];
extern u8  es_fur_operate_gu8a[ECBM_STREAM_FUR_CH_COUNT];
extern u8  es_fur_temp8_gu8a  [ECBM_STREAM_FUR_CH_COUNT];
#endif



extern u8 es_fur_get_id(u8 ch);

extern u16 es_fur_read_reg(u8 ch,u16 addr);

extern void es_fur_write_reg(u8 ch,u16 addr,u16 dat);

extern void es_fur_master_receive_callback(u8 ch,u16 addr,u16 dat);


extern void es_fur_master_send(u8 ch,u16 addr,u8 id,u16 dat);

extern void es_fur_master_read(u8 ch,u16 addr,u8 id);


extern void es_fur_reset(u8 ch);

extern void es_fur_send_num_10(u8 ch,u16 num);

extern void es_fur_send_num_16(u8 ch,u16 num);

extern void es_fur_exe(u8 ch,u8 dat);
#endif



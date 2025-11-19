#ifndef _ECBM_UART_H_
#define _ECBM_UART_H_










#define ECBM_UART_TX_MODE (1)

#define ECBM_UART_PRINTF_EN (1)


#define ECBM_UART_PRINTF_BUF_MAX (64)


#define ECBM_UART1_EN (1)








#define ECBM_UART1_TX_BUF_MASK (0x3F)














#define ECBM_UART1_BAUD_RATE (115200)















#define ECBM_UART1_SCON_CONFIG (0x50)







#define ECBM_UART1_SADDR_CONFIG (0xA1)








#define ECBM_UART1_SADEN_CONFIG (0xFF)






#define ECBM_UART1_PCON_CONFIG (0x00)








#define ECBM_UART1_AUXR_CONFIG (0x00)








#define ECBM_UART1_IO (0x00)







#define ECBM_UART1_PARITY (0)

#define ECBM_UART1_SEND_CALLBACK_EN (0)

#define ECBM_UART1_RECEIVE_CALLBACK_EN (0)

#define ECBM_UART1_485_EN (0)












#define ECBM_UART1_485_RE_PORT (0xC0)









#define ECBM_UART1_485_RE_PIN  (0x03)









#define ECBM_UART1_485_DE_PORT (0xC0)









#define ECBM_UART1_485_DE_PIN  (0x03)



#define ECBM_UART2_EN (0)








#define ECBM_UART2_TX_BUF_MASK (0x0F)














#define ECBM_UART2_BAUD_RATE (115200)









#define ECBM_UART2_S2CON_CONFIG (0x10)





#define ECBM_UART2_IO (0x00)







#define ECBM_UART2_PARITY (0)

#define ECBM_UART2_SEND_CALLBACK_EN (0)

#define ECBM_UART2_RECEIVE_CALLBACK_EN (0)

#define ECBM_UART2_485_EN (0)












#define ECBM_UART2_485_RE_PORT (0xC0)









#define ECBM_UART2_485_RE_PIN  (0x03)









#define ECBM_UART2_485_DE_PORT (0xC0)









#define ECBM_UART2_485_DE_PIN  (0x03)



#define ECBM_UART3_EN (0)








#define ECBM_UART3_TX_BUF_MASK (0x0F)














#define ECBM_UART3_BAUD_RATE (115200)












#define ECBM_UART3_S3CON_CONFIG (0x50)




#define ECBM_UART3_IO (0x00)







#define ECBM_UART3_PARITY (0)

#define ECBM_UART3_SEND_CALLBACK_EN (0)

#define ECBM_UART3_RECEIVE_CALLBACK_EN (0)

#define ECBM_UART3_485_EN (0)












#define ECBM_UART3_485_RE_PORT (0xC0)









#define ECBM_UART3_485_RE_PIN  (0x03)









#define ECBM_UART3_485_DE_PORT (0xC0)









#define ECBM_UART3_485_DE_PIN  (0x03)



#define ECBM_UART4_EN (0)








#define ECBM_UART4_TX_BUF_MASK (0x0F)














#define ECBM_UART4_BAUD_RATE (115200)












#define ECBM_UART4_S4CON_CONFIG (0x50)




#define ECBM_UART4_IO (0x04)







#define ECBM_UART4_PARITY (0)

#define ECBM_UART4_SEND_CALLBACK_EN (0)

#define ECBM_UART4_RECEIVE_CALLBACK_EN (0)

#define ECBM_UART4_485_EN (0)












#define ECBM_UART4_485_RE_PORT (0xC0)









#define ECBM_UART4_485_RE_PIN  (0x03)









#define ECBM_UART4_485_DE_PORT (0xC0)









#define ECBM_UART4_485_DE_PIN  (0x03)





#include "ecbm_core.h"

#define UART1_PIN_P30_P31 (0x00)
#define UART1_PIN_P36_P37 (0x40)
#define UART1_PIN_P16_P17 (0x80)
#define UART1_PIN_P43_P44 (0xC0)

#define UART1_PIN_P32_P33 (0x40)
#define UART1_PIN_P54_P55 (0x80)

#define UART2_PIN_P10_P11 (0x00)
#define UART2_PIN_P40_P42 (0x01)
#define UART2_PIN_P46_P47 (0x01)

#define UART3_PIN_P00_P01 (0x00)
#define UART3_PIN_P50_P51 (0x02)

#define UART4_PIN_P02_P03 (0x00)
#define UART4_PIN_P52_P53 (0x04)

extern bit uart1_busy_gb;
extern bit uart2_busy_gb;
extern bit uart3_busy_gb;
extern bit uart4_busy_gb;
extern u8 xdata uart1_tx_buf[ECBM_UART1_TX_BUF_MASK+1];
extern u8 data  uart1_tx_buf_write_point;
extern u8 data  uart1_tx_buf_read_point;
extern u8 xdata uart2_tx_buf[ECBM_UART2_TX_BUF_MASK+1];
extern u8 data  uart2_tx_buf_write_point;
extern u8 data  uart2_tx_buf_read_point;
extern u8 xdata uart3_tx_buf[ECBM_UART3_TX_BUF_MASK+1];
extern u8 data  uart3_tx_buf_write_point;
extern u8 data  uart3_tx_buf_read_point;
extern u8 xdata uart4_tx_buf[ECBM_UART4_TX_BUF_MASK+1];
extern u8 data  uart4_tx_buf_write_point;
extern u8 data  uart4_tx_buf_read_point;


extern void uart_init(void);

extern void uart_set_io(u8 id,u8 io);

extern void uart_set_baud(u8 id,u32 baud);

extern void uart_char(u8 id,u8 ch);

extern void uart_char_9(u8 id,u8 ch,u8 bit9);

extern void uart_string(u8 id,u8 * str);

extern void uart_printf(u8 id,const char * str,...);

extern void uart1_receive_callback(void);

extern void uart1_send_callback(void);

extern void uart2_receive_callback(void);

extern void uart2_send_callback(void);

extern void uart3_receive_callback(void);

extern void uart3_send_callback(void);

extern void uart4_receive_callback(void);

extern void uart4_send_callback(void);
#endif



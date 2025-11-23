#include "ecbm_core.h"
#if (ECBM_UART_LIB_EN)

#if (ECBM_UART1_EN)
    bit uart1_busy_gb;
    #if (ECBM_UART_TX_MODE)
        u8 xdata uart1_tx_buf[ECBM_UART1_TX_BUF_MASK+1];
        u8 data  uart1_tx_buf_write_point;
        u8 data  uart1_tx_buf_read_point;
    #endif
    #if ((ECBM_MCU==0x310201)||(ECBM_MCU==0x3102A1))
        u8 code uart1_io_map_gcu8[3][2]={
            {D30,D31},
            {D32,D33},
            {D54,D55},
        };
    #else
        u8 code uart1_io_map_gcu8[4][2]={
            {D30,D31},
            {D36,D37},
            {D16,D17},
            {D43,D44},
        };
    #endif
#endif
#if (ECBM_UART2_EN)
    bit uart2_busy_gb;
    #if (ECBM_UART_TX_MODE)
        u8 xdata uart2_tx_buf[ECBM_UART2_TX_BUF_MASK+1];
        u8 data  uart2_tx_buf_write_point;
        u8 data  uart2_tx_buf_read_point;
    #endif
    #if ((ECBM_MCU&0xF00000)<=0x200000)
        u8 code uart2_io_map_gcu8[2][2]={
            {D10,D11},
            {D40,D42},
        };
    #else
        u8 code uart2_io_map_gcu8[2][2]={
            {D10,D11},
            {D46,D47},
        };
    #endif
#endif
#if (ECBM_UART3_EN)
    bit uart3_busy_gb;
    #if (ECBM_UART_TX_MODE)
        u8 xdata uart3_tx_buf[ECBM_UART3_TX_BUF_MASK+1];
        u8 data  uart3_tx_buf_write_point;
        u8 data  uart3_tx_buf_read_point;
    #endif
    u8 code uart3_io_map_gcu8[2][2]={
        {D00,D01},
        {D50,D51},
    };
#endif
#if (ECBM_UART4_EN)
    bit uart4_busy_gb;
    #if (ECBM_UART_TX_MODE)
        u8 xdata uart4_tx_buf[ECBM_UART4_TX_BUF_MASK+1];
        u8 data  uart4_tx_buf_write_point;
        u8 data  uart4_tx_buf_read_point;
    #endif
    u8 code uart4_io_map_gcu8[2][2]={
        {D02,D03},
        {D52,D53},
    };
#endif


#if (ECBM_UART1_EN)
    #if (ECBM_UART1_PARITY!=0)
       #if ((ECBM_UART1_SCON_CONFIG&0x80)!=0x80)
           #error   若想开启串口1的校验功能，请把工作模式设置为9位！
       #endif
    #else
       #if ((ECBM_UART1_SCON_CONFIG&0x80)&&((ECBM_UART1_SCON_CONFIG&0x20)==0))
            #warning 串口1当前没有开启校验或者多机通信功能，请留意一下工作模式是否一定设置为9位。
       #endif
    #endif
#endif

#if (ECBM_UART2_EN)
#   if (ECBM_UART2_PARITY!=0)
#       if ((ECBM_UART2_S2CON_CONFIG&0x80)!=0x80)
#           error 若想开启串口2的校验功能，请把工作模式设置为9位！
#       endif
#   else
#       if ((ECBM_UART2_S2CON_CONFIG&0x80)&&((ECBM_UART2_S2CON_CONFIG&0x20)==0))
#           warning 串口2当前没有开启校验或者多机通信功能，请留意一下工作模式是否一定设置为9位。
#       endif
#   endif
#endif

#if (ECBM_UART3_EN)
#   if (ECBM_UART3_PARITY!=0)
#       if ((ECBM_UART3_S3CON_CONFIG&0x80)!=0x80)
#           error 若想开启串口3的校验功能，请把工作模式设置为9位！
#       endif
#   else
#       if (ECBM_UART3_S3CON_CONFIG&0x80)&&((ECBM_UART3_S3CON_CONFIG&0x20)==0)
#           warning 串口3当前没有开启校验或者多机通信功能，请留意一下工作模式是否一定设置为9位。
#       endif
#   endif
#endif

#if (ECBM_UART4_EN)
#   if (ECBM_UART4_PARITY!=0)
#       if ((ECBM_UART4_S4CON_CONFIG&0x80)!=0x80)
#           error 若想开启串口4的校验功能，请把工作模式设置为9位！
#       endif
#   else
#       if (ECBM_UART4_S4CON_CONFIG&0x80)&&((ECBM_UART4_S4CON_CONFIG&0x20)==0)
#           warning 串口4当前没有开启校验或者多机通信功能，请留意一下工作模式是否一定设置为9位。
#       endif
#   endif
#endif

#if (ECBM_UART1_SCON_CONFIG&0x20)&&((ECBM_UART1_SCON_CONFIG&0x80)==0)
#   error 若开启串口1的多机通信功能，请把工作模式设置为9位！
#endif
#if (ECBM_UART2_S2CON_CONFIG&0x20)&&((ECBM_UART2_S2CON_CONFIG&0x80)==0)
#   error 若开启串口2的多机通信功能，请把工作模式设置为9位！
#endif
#if (ECBM_UART3_S3CON_CONFIG&0x20)&&((ECBM_UART3_S3CON_CONFIG&0x80)==0)
#   error 若开启串口3的多机通信功能，请把工作模式设置为9位！
#endif
#if (ECBM_UART4_S4CON_CONFIG&0x20)&&((ECBM_UART4_S4CON_CONFIG&0x80)==0)
#   error 若开启串口4的多机通信功能，请把工作模式设置为9位！
#endif

#if (ECBM_UART2_EN)&&((ECBM_MCU&0x00000F)<0x000002)
#   error 当前单片机型号不支持串口2，请更换型号或者关闭串口2。
#endif
#if (ECBM_UART3_EN)&&((ECBM_MCU&0x00000F)<0x000003)
#   error 当前单片机型号不支持串口3，请更换型号或者关闭串口3。
#endif
#if (ECBM_UART4_EN)&&((ECBM_MCU&0x00000F)<0x000004)
#   error 当前单片机型号不支持串口4，请更换型号或者关闭串口4。
#endif

#if ((ECBM_UART1_EN)&&(ECBM_UART1_AUXR_CONFIG&0x01)&&(ECBM_UART2_EN))
#   if  (ECBM_UART1_BAUD_RATE != ECBM_UART2_BAUD_RATE)
#       error 串口1和串口2的波特率产生器（定时器2）冲突。请更换串口1的波特率产生器或者将串口1和串口2的波特率调成一致。
#   endif
#endif

#if (ECBM_UART1_EN)&&(ECBM_UART1_AUXR_CONFIG&0x01)&&(ECBM_UART3_EN)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)
#   if  (ECBM_UART1_BAUD_RATE != ECBM_UART3_BAUD_RATE)
#       error 串口1和串口3的波特率产生器（定时器2）冲突。请更换串口1或串口3的波特率产生器或者将串口1和串口3的波特率调成一致。
#   endif
#endif

#if (ECBM_UART1_EN)&&(ECBM_UART1_AUXR_CONFIG&0x01)&&(ECBM_UART4_EN)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#   if  (ECBM_UART1_BAUD_RATE != ECBM_UART4_BAUD_RATE)
#       error 串口1和串口4的波特率产生器（定时器2）冲突。请更换串口1或串口4的波特率产生器或者将串口1和串口4的波特率调成一致。
#   endif
#endif

#if (ECBM_UART2_EN)&&(ECBM_UART3_EN)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)
#   if  (ECBM_UART2_BAUD_RATE != ECBM_UART3_BAUD_RATE)
#       error 串口2和串口3的波特率产生器（定时器2）冲突。请更换串口3的波特率产生器或者将串口2和串口3的波特率调成一致。
#   endif
#endif

#if (ECBM_UART2_EN)&&(ECBM_UART4_EN)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#   if  (ECBM_UART2_BAUD_RATE != ECBM_UART4_BAUD_RATE)
#       error 串口2和串口4的波特率产生器（定时器2）冲突。请更换串口4的波特率产生器或者将串口2和串口4的波特率调成一致。
#   endif
#endif

#if (ECBM_UART3_EN)&&((ECBM_UART3_S3CON_CONFIG&0x40)==0x00)&&(ECBM_UART4_EN)&&((ECBM_UART4_S4CON_CONFIG&0x40)==0x00)
#   if  (ECBM_UART3_BAUD_RATE != ECBM_UART4_BAUD_RATE)
#       error 串口3和串口4的波特率产生器（定时器2）冲突。请更换串口3或串口4的波特率产生器或者将串口3和串口4的波特率调成一致。
#   endif
#endif

#if (ECBM_UART1_485_EN)


#endif

#if (ECBM_UART2_485_EN)


#endif

#if (ECBM_UART3_485_EN)


#endif

#if (ECBM_UART4_485_EN)


#endif


void uart_init(void){
    #if (ECBM_UART1_EN)
        UART1_SET_REG_SCON  (ECBM_UART1_SCON_CONFIG);//写入SCON配置，包含工作模式、接收使能、多机通信的选项。
        UART1_SET_REG_PCON  (ECBM_UART1_PCON_CONFIG); //写入PCON配置，包含波特率加倍。
        UART1_SET_REG_AUXR  (ECBM_UART1_AUXR_CONFIG);//写入AUXR配置，包含加倍控制、波特率发生器选择。
        uart_set_io         (1,ECBM_UART1_IO);          //写入IO选择控制位。
        uart_set_baud       (1,ECBM_UART1_BAUD_RATE);   //设置波特率。
        #if (ECBM_UART1_SCON_CONFIG&0x20)
            UART1_SET_REG_SADDR (ECBM_UART1_SADDR_CONFIG);
            UART1_SET_REG_SADEN (ECBM_UART1_SADEN_CONFIG);
        #endif
        #if ((ECBM_UART1_AUXR_CONFIG&0x01)==0)
            TIMER1_SET_MODE_1T;
            TIMER1_SET_REG_TMOD(0x20);
            TIMER1_IT_DISABLE;
            TIMER1_POWER_ON;
        #else
            TIMER2_SET_MODE_1T;
            TIMER2_IT_DISABLE;
            TIMER2_POWER_ON;
        #endif
        uart1_busy_gb=0;
        #if (ECBM_UART_TX_MODE)
            uart1_tx_buf_write_point=0;
            uart1_tx_buf_read_point=0;
        #endif
    
        UART1_IT_ENABLE;
        #if (ECBM_UART1_485_EN)
            UART1_485_RE_IO=0;
            UART1_485_DE_IO=0;
            #if   (ECBM_UART1_485_RE_PORT==0x80)
                gpio_mode(D00+ECBM_UART1_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_RE_PORT==0x90)
                gpio_mode(D10+ECBM_UART1_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_RE_PORT==0xA0)
                gpio_mode(D20+ECBM_UART1_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_RE_PORT==0xB0)
                gpio_mode(D30+ECBM_UART1_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_RE_PORT==0xC0)
                gpio_mode(D40+ECBM_UART1_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_RE_PORT==0xC8)
                gpio_mode(D50+ECBM_UART1_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_RE_PORT==0xE8)
                gpio_mode(D60+ECBM_UART1_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_RE_PORT==0xF8)
                gpio_mode(D70+ECBM_UART1_485_RE_PIN,GPIO_OUT);
            #endif
            #if   (ECBM_UART1_485_DE_PORT==0x80)
                gpio_mode(D00+ECBM_UART1_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_DE_PORT==0x90)
                gpio_mode(D10+ECBM_UART1_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_DE_PORT==0xA0)
                gpio_mode(D20+ECBM_UART1_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_DE_PORT==0xB0)
                gpio_mode(D30+ECBM_UART1_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_DE_PORT==0xC0)
                gpio_mode(D40+ECBM_UART1_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_DE_PORT==0xC8)
                gpio_mode(D50+ECBM_UART1_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_DE_PORT==0xE8)
                gpio_mode(D60+ECBM_UART1_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART1_485_DE_PORT==0xF8)
                gpio_mode(D70+ECBM_UART1_485_DE_PIN,GPIO_OUT);
            #endif
        #endif
    #endif

    #if (ECBM_UART2_EN)
        UART2_SET_REG_S2CON (ECBM_UART2_S2CON_CONFIG);
        uart_set_io         (2,ECBM_UART2_IO);
        uart_set_baud       (2,ECBM_UART2_BAUD_RATE);
        TIMER2_SET_MODE_1T;
        TIMER2_IT_DISABLE;
        TIMER2_POWER_ON;
        uart2_busy_gb=0;
        #if (ECBM_UART_TX_MODE)
            uart2_tx_buf_write_point=0;
            uart2_tx_buf_read_point=0;
        #endif
        UART2_IT_ENABLE;
        #if (ECBM_UART2_485_EN)
            UART2_485_RE_IO=0;
            UART2_485_DE_IO=0;
            #if   (ECBM_UART2_485_RE_PORT==0x80)
                gpio_mode(D00+ECBM_UART2_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_RE_PORT==0x90)
                gpio_mode(D10+ECBM_UART2_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_RE_PORT==0xA0)
                gpio_mode(D20+ECBM_UART2_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_RE_PORT==0xB0)
                gpio_mode(D30+ECBM_UART2_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_RE_PORT==0xC0)
                gpio_mode(D40+ECBM_UART2_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_RE_PORT==0xC8)
                gpio_mode(D50+ECBM_UART2_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_RE_PORT==0xE8)
                gpio_mode(D60+ECBM_UART2_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_RE_PORT==0xF8)
                gpio_mode(D70+ECBM_UART2_485_RE_PIN,GPIO_OUT);
            #endif
            #if   (ECBM_UART2_485_DE_PORT==0x80)
                gpio_mode(D00+ECBM_UART2_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_DE_PORT==0x90)
                gpio_mode(D10+ECBM_UART2_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_DE_PORT==0xA0)
                gpio_mode(D20+ECBM_UART2_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_DE_PORT==0xB0)
                gpio_mode(D30+ECBM_UART2_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_DE_PORT==0xC0)
                gpio_mode(D40+ECBM_UART2_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_DE_PORT==0xC8)
                gpio_mode(D50+ECBM_UART2_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_DE_PORT==0xE8)
                gpio_mode(D60+ECBM_UART2_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART2_485_DE_PORT==0xF8)
                gpio_mode(D70+ECBM_UART2_485_DE_PIN,GPIO_OUT);
            #endif
        #endif
    #endif

    #if (ECBM_UART3_EN)
        UART3_SET_REG_S3CON (ECBM_UART3_S3CON_CONFIG);
        uart_set_io         (3,ECBM_UART3_IO);
        uart_set_baud       (3,ECBM_UART3_BAUD_RATE);
        #if (ECBM_UART3_S3CON_CONFIG&0x40)==0
            TIMER2_SET_MODE_1T;
            TIMER2_IT_DISABLE;
            TIMER2_POWER_ON;
        #else
            TIMER3_SET_MODE_1T;
            TIMER3_IT_DISABLE;
            TIMER3_POWER_ON;
        #endif
        uart3_busy_gb=0;
        #if (ECBM_UART_TX_MODE)
            uart3_tx_buf_write_point=0;
            uart3_tx_buf_read_point=0;
        #endif
        UART3_IT_ENABLE;
        #if (ECBM_UART3_485_EN)
            UART3_485_RE_IO=0;
            UART3_485_DE_IO=0;
            #if   (ECBM_UART3_485_RE_PORT==0x80)
                gpio_mode(D00+ECBM_UART3_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_RE_PORT==0x90)
                gpio_mode(D10+ECBM_UART3_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_RE_PORT==0xA0)
                gpio_mode(D20+ECBM_UART3_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_RE_PORT==0xB0)
                gpio_mode(D30+ECBM_UART3_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_RE_PORT==0xC0)
                gpio_mode(D40+ECBM_UART3_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_RE_PORT==0xC8)
                gpio_mode(D50+ECBM_UART3_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_RE_PORT==0xE8)
                gpio_mode(D60+ECBM_UART3_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_RE_PORT==0xF8)
                gpio_mode(D70+ECBM_UART3_485_RE_PIN,GPIO_OUT);
            #endif
            #if   (ECBM_UART3_485_DE_PORT==0x80)
                gpio_mode(D00+ECBM_UART3_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_DE_PORT==0x90)
                gpio_mode(D10+ECBM_UART3_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_DE_PORT==0xA0)
                gpio_mode(D20+ECBM_UART3_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_DE_PORT==0xB0)
                gpio_mode(D30+ECBM_UART3_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_DE_PORT==0xC0)
                gpio_mode(D40+ECBM_UART3_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_DE_PORT==0xC8)
                gpio_mode(D50+ECBM_UART3_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_DE_PORT==0xE8)
                gpio_mode(D60+ECBM_UART3_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART3_485_DE_PORT==0xF8)
                gpio_mode(D70+ECBM_UART3_485_DE_PIN,GPIO_OUT);
            #endif
        #endif
    #endif

    #if (ECBM_UART4_EN)
        UART4_SET_REG_S4CON (ECBM_UART4_S4CON_CONFIG);
        uart_set_io         (4,ECBM_UART4_IO);
        uart_set_baud       (4,ECBM_UART4_BAUD_RATE);
        #if (ECBM_UART4_S4CON_CONFIG&0x40)==0
            TIMER2_SET_MODE_1T;
            TIMER2_IT_DISABLE;
            TIMER2_POWER_ON;
        #else
            TIMER4_SET_MODE_1T;
            TIMER4_IT_DISABLE;
            TIMER4_POWER_ON;
        #endif
        uart4_busy_gb=0;
        #if (ECBM_UART_TX_MODE)
            uart4_tx_buf_write_point=0;
            uart4_tx_buf_read_point=0;
        #endif
        UART4_IT_ENABLE;
        #if (ECBM_UART4_485_EN)
            UART4_485_RE_IO=0;
            UART4_485_DE_IO=0;
            #if   (ECBM_UART4_485_RE_PORT==0x80)
                gpio_mode(D00+ECBM_UART4_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_RE_PORT==0x90)
                gpio_mode(D10+ECBM_UART4_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_RE_PORT==0xA0)
                gpio_mode(D20+ECBM_UART4_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_RE_PORT==0xB0)
                gpio_mode(D30+ECBM_UART4_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_RE_PORT==0xC0)
                gpio_mode(D40+ECBM_UART4_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_RE_PORT==0xC8)
                gpio_mode(D50+ECBM_UART4_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_RE_PORT==0xE8)
                gpio_mode(D60+ECBM_UART4_485_RE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_RE_PORT==0xF8)
                gpio_mode(D70+ECBM_UART4_485_RE_PIN,GPIO_OUT);
            #endif
            #if   (ECBM_UART4_485_DE_PORT==0x80)
                gpio_mode(D00+ECBM_UART4_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_DE_PORT==0x90)
                gpio_mode(D10+ECBM_UART4_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_DE_PORT==0xA0)
                gpio_mode(D20+ECBM_UART4_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_DE_PORT==0xB0)
                gpio_mode(D30+ECBM_UART4_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_DE_PORT==0xC0)
                gpio_mode(D40+ECBM_UART4_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_DE_PORT==0xC8)
                gpio_mode(D50+ECBM_UART4_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_DE_PORT==0xE8)
                gpio_mode(D60+ECBM_UART4_485_DE_PIN,GPIO_OUT);
            #elif (ECBM_UART4_485_DE_PORT==0xF8)
                gpio_mode(D70+ECBM_UART4_485_DE_PIN,GPIO_OUT);
            #endif
        #endif
    #endif
}

void uart_set_io(u8 id,u8 io){
    switch(id){
        #if (ECBM_UART1_EN)
            case 1:{
                UART1_SET_PIN(io);
                gpio_mode(uart1_io_map_gcu8[io>>6][0],GPIO_IN);
                gpio_mode(uart1_io_map_gcu8[io>>6][1],GPIO_OUT);
            }break;
        #endif
        #if (ECBM_UART2_EN)
            case 2:{
                UART2_SET_PIN(io);
                gpio_mode(uart2_io_map_gcu8[io][0],GPIO_IN);
                gpio_mode(uart2_io_map_gcu8[io][1],GPIO_OUT);
            }break;
        #endif
        #if (ECBM_UART3_EN)
            case 3:{
                UART3_SET_PIN(io);
                gpio_mode(uart3_io_map_gcu8[io>>1][0],GPIO_IN);
                gpio_mode(uart3_io_map_gcu8[io>>1][1],GPIO_OUT);
            }break;
        #endif
        #if (ECBM_UART4_EN)
            case 4:{
                UART4_SET_PIN(io);
                gpio_mode(uart4_io_map_gcu8[io>>2][0],GPIO_IN);
                gpio_mode(uart4_io_map_gcu8[io>>2][1],GPIO_OUT);
            }break;
        #endif
    }
}

void uart_set_baud(u8 id,u32 baud){
    u16 res_u16;
    res_u16=(u16)(65536-(u16)(ECBM_SYSCLK_SETTING/4/baud));
    // TH1=0xfd;
	// TL1=0xfd;
    res_u16 = 0xfdfd;
    switch(id){
        #if (ECBM_UART1_EN)
            case 1:{
                #if ((ECBM_UART1_AUXR_CONFIG&0x01)==0)
                    TIMER1_SET_REG_HL(res_u16);
                #else
                    TIMER2_SET_REG_HL(res_u16);
                #endif
            }break;
        #endif
        #if (ECBM_UART2_EN)
            case 2:{
                TIMER2_SET_REG_HL(res_u16);
            }break;
        #endif
        #if (ECBM_UART3_EN)
            case 3:{
                #if ((ECBM_UART3_S3CON_CONFIG&0x40)==0)
                    TIMER2_SET_REG_HL(res_u16);
                #else
                    TIMER3_SET_REG_HL(res_u16);
                #endif
            }break;
        #endif
        #if (ECBM_UART4_EN)
            case 4:{
                #if ((ECBM_UART4_S4CON_CONFIG&0x40)==0)
                    TIMER2_SET_REG_HL(res_u16);
                #else
                    TIMER4_SET_REG_HL(res_u16);
                #endif
            }break;
        #endif
    }
}

#if (ECBM_UART_TX_MODE)
    #if (ECBM_UART1_EN)
    void uart1_tx_trig(void){
        u8 ch=uart1_tx_buf[uart1_tx_buf_read_point];
        #if (ECBM_UART1_485_EN)
            UART1_485_RE_IO=1;
            UART1_485_DE_IO=1;
        #endif
        #if (ECBM_UART1_PARITY==1)
            IF_ODD(ch){
                UART1_SET_TXD_BYTE9_0;
            }else{
                UART1_SET_TXD_BYTE9_1;
            }
        #elif (ECBM_UART1_PARITY==2)
            IF_ODD(ch){
                UART1_SET_TXD_BYTE9_1;
            }else{
                UART1_SET_TXD_BYTE9_0;
            }
        #elif (ECBM_UART1_PARITY==3)
            UART1_SET_TXD_BYTE9_1;
        #elif (ECBM_UART1_PARITY==4)
            UART1_SET_TXD_BYTE9_0;
        #endif
        UART1_SET_REG_SBUF(ch);
        uart1_tx_buf_read_point++;
        uart1_tx_buf_read_point&=ECBM_UART1_TX_BUF_MASK;
        uart1_busy_gb=1;
    }
    void uart1_tx_end(void){
        uart1_busy_gb=0;
        #if (ECBM_UART1_485_EN)
            UART1_485_RE_IO=0;
            UART1_485_DE_IO=0;
        #endif
    }
    #endif

    #if (ECBM_UART2_EN)
    void uart2_tx_trig(void){
        u8 ch=uart2_tx_buf[uart2_tx_buf_read_point];
        #if (ECBM_UART2_485_EN)
            UART2_485_RE_IO=1;
            UART2_485_DE_IO=1;
        #endif
        #if (ECBM_UART2_PARITY==1)
            IF_ODD(ch){
                UART2_SET_TXD_BYTE9_0;
            }else{
                UART2_SET_TXD_BYTE9_1;
            }
        #elif (ECBM_UART2_PARITY==2)
            IF_ODD(ch){
                UART2_SET_TXD_BYTE9_1;
            }else{
                UART2_SET_TXD_BYTE9_0;
            }
        #elif (ECBM_UART2_PARITY==3)
            UART2_SET_TXD_BYTE9_1;
        #elif (ECBM_UART2_PARITY==4)
            UART2_SET_TXD_BYTE9_0;
        #endif
        UART2_SET_REG_S2BUF(ch);
        uart2_tx_buf_read_point++;
        uart2_tx_buf_read_point&=ECBM_UART2_TX_BUF_MASK;
        uart2_busy_gb=1;
    }
    void uart2_tx_end(void){
        uart2_busy_gb=0;
        #if (ECBM_UART2_485_EN)
            UART2_485_RE_IO=0;
            UART2_485_DE_IO=0;
        #endif
    }
    #endif                                                          
    #if (ECBM_UART3_EN)
    void uart3_tx_trig(void){
        u8 ch=uart3_tx_buf[uart3_tx_buf_read_point];
        #if (ECBM_UART3_485_EN)
            UART3_485_RE_IO=1;
            UART3_485_DE_IO=1;
        #endif
        #if   (ECBM_UART3_PARITY==1)
            IF_ODD(ch){
                UART3_SET_TXD_BYTE9_0;
            }else{
                UART3_SET_TXD_BYTE9_1;
            }
        #elif (ECBM_UART3_PARITY==2)
            IF_ODD(ch){
                UART3_SET_TXD_BYTE9_1;
            }else{
                UART3_SET_TXD_BYTE9_0;
            }
        #elif (ECBM_UART3_PARITY==3)
            UART3_SET_TXD_BYTE9_1;
        #elif (ECBM_UART3_PARITY==4)
            UART3_SET_TXD_BYTE9_0;
        #endif
        UART3_SET_REG_S3BUF(ch);
        uart3_tx_buf_read_point++;
        uart3_tx_buf_read_point&=ECBM_UART3_TX_BUF_MASK;
        uart3_busy_gb=1;
    }
    void uart3_tx_end(void){
        uart3_busy_gb=0;
        #if (ECBM_UART3_485_EN)
            UART3_485_RE_IO=0;
            UART3_485_DE_IO=0;
        #endif
    }
    #endif
    #if (ECBM_UART4_EN)
    void uart4_tx_trig(void){
        u8 ch=uart4_tx_buf[uart4_tx_buf_read_point];
        #if (ECBM_UART4_485_EN)
            UART4_485_RE_IO=1;
            UART4_485_DE_IO=1;
        #endif
        #if   (ECBM_UART4_PARITY==1)
            IF_ODD(ch){
                UART4_SET_TXD_BYTE9_0;
            }else{
                UART4_SET_TXD_BYTE9_1;
            }
        #elif (ECBM_UART4_PARITY==2)
            IF_ODD(ch){
                UART4_SET_TXD_BYTE9_1;
            }else{
                UART4_SET_TXD_BYTE9_0;
            }
        #elif (ECBM_UART4_PARITY==3)
            UART4_SET_TXD_BYTE9_1;
        #elif (ECBM_UART4_PARITY==4)
            UART4_SET_TXD_BYTE9_0;
        #endif
        UART4_SET_REG_S4BUF(ch);
        uart4_tx_buf_read_point++;
        uart4_tx_buf_read_point&=ECBM_UART4_TX_BUF_MASK;
        uart4_busy_gb=1;
    }
    void uart4_tx_end(void){
        uart4_busy_gb=0;
        #if (ECBM_UART4_485_EN)
            UART4_485_RE_IO=0;
            UART4_485_DE_IO=0;
        #endif
    }
    #endif
#endif

void uart_char(u8 id,u8 ch){
    switch(id){
        #if (ECBM_UART1_EN)
            case 1:{
    
                #if (ECBM_UART_TX_MODE)
                    
                    uart1_tx_buf[uart1_tx_buf_write_point]=ch;
                    uart1_tx_buf_write_point++;
                    uart1_tx_buf_write_point&=ECBM_UART1_TX_BUF_MASK;
                    // P10 = 0x00; 
                    if(uart1_busy_gb==0){
                        uart1_tx_trig();
                    }
                    
                    
                #else
                    #if (ECBM_UART1_485_EN)
                        UART1_485_RE_IO=1;
                        UART1_485_DE_IO=1;
                    #endif
                    #if (ECBM_UART1_PARITY==1)
                        IF_ODD(ch){
                            UART1_SET_TXD_BYTE9_0;
                        }else{
                            UART1_SET_TXD_BYTE9_1;
                        }
                    #elif (ECBM_UART1_PARITY==2)
                        IF_ODD(ch){
                            UART1_SET_TXD_BYTE9_1;
                        }else{
                            UART1_SET_TXD_BYTE9_0;
                        }
                    #elif (ECBM_UART1_PARITY==3)
                        UART1_SET_TXD_BYTE9_1;
                    #elif (ECBM_UART1_PARITY==4)
                        UART1_SET_TXD_BYTE9_0;
                    #endif
                    UART1_SET_REG_SBUF(ch);
                    uart1_busy_gb=1;
                    while(uart1_busy_gb);
                    #if (ECBM_UART1_485_EN)
                        UART1_485_RE_IO=0;
                        UART1_485_DE_IO=0;
                    #endif
                #endif
            }break;
        #endif
        #if (ECBM_UART2_EN)
            case 2:{
                #if (ECBM_UART_TX_MODE)
                    uart2_tx_buf[uart2_tx_buf_write_point]=ch;
                    uart2_tx_buf_write_point++;
                    uart2_tx_buf_write_point&=ECBM_UART2_TX_BUF_MASK;
                    if(uart2_busy_gb==0){
                        uart2_tx_trig();
                    }
                #else
                    #if (ECBM_UART2_485_EN)
                        UART2_485_RE_IO=1;
                        UART2_485_DE_IO=1;
                    #endif
                    #if (ECBM_UART2_PARITY==1)
                        IF_ODD(ch){
                            UART2_SET_TXD_BYTE9_0;
                        }else{
                            UART2_SET_TXD_BYTE9_1;
                        }
                    #elif (ECBM_UART2_PARITY==2)
                        IF_ODD(ch){
                            UART2_SET_TXD_BYTE9_1;
                        }else{
                            UART2_SET_TXD_BYTE9_0;
                        }
                    #elif (ECBM_UART2_PARITY==3)
                        UART2_SET_TXD_BYTE9_1;
                    #elif (ECBM_UART2_PARITY==4)
                        UART2_SET_TXD_BYTE9_0;
                    #endif
                    UART2_SET_REG_S2BUF(ch);
                    uart2_busy_gb=1;
                    while(uart2_busy_gb);
                    #if (ECBM_UART2_485_EN)
                        UART2_485_RE_IO=0;
                        UART2_485_DE_IO=0;
                    #endif
                #endif
            }break;
        #endif
        #if (ECBM_UART3_EN)
            case 3:{
                #if (ECBM_UART_TX_MODE)
                    uart3_tx_buf[uart3_tx_buf_write_point]=ch;
                    uart3_tx_buf_write_point++;
                    uart3_tx_buf_write_point&=ECBM_UART3_TX_BUF_MASK;
                    if(uart3_busy_gb==0){
                        uart3_tx_trig();
                    }
                #else
                    #if (ECBM_UART3_485_EN)
                        UART3_485_RE_IO=1;
                        UART3_485_DE_IO=1;
                    #endif
                    #if   (ECBM_UART3_PARITY==1)
                        IF_ODD(ch){
                            UART3_SET_TXD_BYTE9_0;
                        }else{
                            UART3_SET_TXD_BYTE9_1;
                        }
                    #elif (ECBM_UART3_PARITY==2)
                        IF_ODD(ch){
                            UART3_SET_TXD_BYTE9_1;
                        }else{
                            UART3_SET_TXD_BYTE9_0;
                        }
                    #elif (ECBM_UART3_PARITY==3)
                        UART3_SET_TXD_BYTE9_1;
                    #elif (ECBM_UART3_PARITY==4)
                        UART3_SET_TXD_BYTE9_0;
                    #endif
                    UART3_SET_REG_S3BUF(ch);
                    uart3_busy_gb=1;
                    while(uart3_busy_gb);
                    #if (ECBM_UART3_485_EN)
                        UART3_485_RE_IO=0;
                        UART3_485_DE_IO=0;
                    #endif
                #endif
            }break;
        #endif
        #if (ECBM_UART4_EN)
            case 4:{
                #if (ECBM_UART_TX_MODE)
                    uart4_tx_buf[uart4_tx_buf_write_point]=ch;
                    uart4_tx_buf_write_point++;
                    uart4_tx_buf_write_point&=ECBM_UART4_TX_BUF_MASK;
                    if(uart4_busy_gb==0){
                        uart4_tx_trig();
                    }
                #else
                    #if (ECBM_UART4_485_EN)
                        UART4_485_RE_IO=1;
                        UART4_485_DE_IO=1;
                    #endif
                    #if   (ECBM_UART4_PARITY==1)
                        IF_ODD(ch){
                            UART4_SET_TXD_BYTE9_0;
                        }else{
                            UART4_SET_TXD_BYTE9_1;
                        }
                    #elif (ECBM_UART4_PARITY==2)
                        IF_ODD(ch){
                            UART4_SET_TXD_BYTE9_1;
                        }else{
                            UART4_SET_TXD_BYTE9_0;
                        }
                    #elif (ECBM_UART4_PARITY==3)
                        UART4_SET_TXD_BYTE9_1;
                    #elif (ECBM_UART4_PARITY==4)
                        UART4_SET_TXD_BYTE9_0;
                    #endif
                    UART4_SET_REG_S4BUF(ch);
                    uart4_busy_gb=1;
                    while(uart4_busy_gb);
                    #if (ECBM_UART4_485_EN)
                        UART4_485_RE_IO=0;
                        UART4_485_DE_IO=0;
                    #endif
                #endif
            }break;
        #endif
    }
}

void uart_char_9(u8 id,u8 ch,u8 bit9){
    switch(id){
        #if (ECBM_UART1_EN)
            case 1:{
                #if (ECBM_UART1_485_EN)
                    UART1_485_RE_IO=1;
                    UART1_485_DE_IO=1;
                #endif
                if(bit9){
                    UART1_SET_TXD_BYTE9_1;
                }else{
                    UART1_SET_TXD_BYTE9_0;
                }
                UART1_SET_REG_SBUF(ch);
                uart1_busy_gb=1;
                while(uart1_busy_gb);
                #if (ECBM_UART1_485_EN)
                    UART1_485_RE_IO=0;
                    UART1_485_DE_IO=0;
                #endif
            }break;
        #endif
        #if (ECBM_UART2_EN)
            case 2:{
                #if (ECBM_UART2_485_EN)
                    UART2_485_RE_IO=1;
                    UART2_485_DE_IO=1;
                #endif
                if(bit9){
                    UART2_SET_TXD_BYTE9_1;
                }else{
                    UART2_SET_TXD_BYTE9_0;
                }
                UART2_SET_REG_S2BUF(ch);
                uart2_busy_gb=1;
                while(uart2_busy_gb);
                #if (ECBM_UART2_485_EN)
                    UART2_485_RE_IO=0;
                    UART2_485_DE_IO=0;
                #endif
            }break;
        #endif
        #if (ECBM_UART3_EN)
            case 3:{
                #if (ECBM_UART3_485_EN)
                    UART3_485_RE_IO=1;
                    UART3_485_DE_IO=1;
                #endif
                if(bit9){
                    UART3_SET_TXD_BYTE9_1;
                }else{
                    UART3_SET_TXD_BYTE9_0;
                }
                UART3_SET_REG_S3BUF(ch);
                uart3_busy_gb=1;
                while(uart3_busy_gb);
                #if (ECBM_UART3_485_EN)
                    UART3_485_RE_IO=0;
                    UART3_485_DE_IO=0;
                #endif
            }break;
        #endif
        #if (ECBM_UART4_EN)
            case 4:{
                #if (ECBM_UART4_485_EN)
                    UART4_485_RE_IO=1;
                    UART4_485_DE_IO=1;
                #endif
                if(bit9){
                    UART4_SET_TXD_BYTE9_1;
                }else{
                    UART4_SET_TXD_BYTE9_0;
                }
                UART4_SET_REG_S4BUF(ch);
                uart4_busy_gb=1;
                while(uart4_busy_gb);
                #if (ECBM_UART4_485_EN)
                    UART4_485_RE_IO=0;
                    UART4_485_DE_IO=0;
                #endif
            }break;
        #endif
    }
}

void uart_string(u8 id,u8 * str){
    while(*str){
        uart_char(id,*str++);
    }
}

#if ((ECBM_UART_PRINTF_EN)&&(ECBM_PRINTF_EN))
    void uart_printf(u8 id,const char * str,...){
        static  char xdata buf[ECBM_UART_PRINTF_BUF_MAX];
        va_list vp;
        va_start(vp, str);

        vsprintf(buf,str,vp);
        va_end(vp);
        uart_string(id,buf);
    }
#endif

#endif



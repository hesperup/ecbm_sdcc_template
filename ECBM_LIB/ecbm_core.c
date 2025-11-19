#include "ecbm_core.h"

#if (ECBM_AUTO_DOWNLOAD_EN)
#   if (ECBM_UART_LIB_EN==0)
#       warning 因串口库未使能,自动下载功能失效!
#   endif
#   if (ECBM_UART1_EN==0)
#       error 自动下载功能因串口1未使能而开启失败,请前往uart.h使能串口1!
#   endif
#   if (ECBM_UART1_IO!=0)
#       error 自动下载功能需要串口1映射到P30和P31,请前往uart.h修改串口1的输出IO!
#   endif
#endif

#if         ((ECBM_MCU&0xF00000)==0x100000)
#   define	ECBM_MCU_NAME   "STC8F"
#elif       ((ECBM_MCU&0xF00000)==0x200000)
#   define	ECBM_MCU_NAME   "STC8A"
#elif       ((ECBM_MCU&0xF00000)==0x300000)
#   define	ECBM_MCU_NAME   "STC8G"
#elif       ((ECBM_MCU&0xF00000)==0x400000)
#   define	ECBM_MCU_NAME   "STC8H"
#elif       ((ECBM_MCU&0xF00000)==0x500000)
#   define	ECBM_MCU_NAME   "STC8C"
#endif

union{
    u32 num32;
    u16 num16[2];
    u8  num8[4];
}data fast_cout;
#if ((ECBM_UART_LIB_EN)&&(ECBM_AUTO_DOWNLOAD_EN))
    bit auto_download_en_gb;
    u8 data auto_download_old_char_gdu8;
    u8 data auto_download_char_count_gdu8;
#endif

#if (ECBM_DELAY_EN)

void delay_ms(u16 ms){
    u16 i_u16;
    if(ms){
        do{
            i_u16=ECBM_SYSCLK_SETTING/10000;
            while(--i_u16);
        }while(--ms);
    }
}

void delay_us(u16 us){
    u16 i_u16;
    i_u16=us;
	do{}while(--i_u16);
}

u16 delay_set_us(u16 us){

    fast_cout.num32=((u32)(ECBM_SYSCLK_SETTING/10000)*(u32)(us))*131;
    return fast_cout.num16[0]>>1;
}
#endif

#if ((ECBM_UART_LIB_EN)&&(ECBM_AUTO_DOWNLOAD_EN))
    void system_uart_reset(void){
        if(auto_download_old_char_gdu8!=UART1_GET_REG_SBUF){
            auto_download_old_char_gdu8=UART1_GET_REG_SBUF;
            auto_download_char_count_gdu8=0;
        }else{
            if(auto_download_en_gb)auto_download_char_count_gdu8++;
        }
        if(auto_download_char_count_gdu8>=233){
            EA_DISABLE;
            while(1)POWER_RESET;
        }
    }
#endif

#if ((ECBM_UART_LIB_EN)&&(ECBM_UART1_EN)&&(ECBM_UART_PRINTF_EN)&&(ECBM_PRINTF_EN)&&(ECBM_MCU_CHECK_EN))
    void system_check(void){
        u8 i,j;
        u16 aaa=0x1234;
        uart_printf(1,"ECBM V%bu.%bu.%bu on %s",ECBM_FVN,ECBM_RVN,ECBM_BVN,ECBM_MCU_NAME);
        uart_printf(1,"%uK",(u16)((ECBM_MCU&0x0F0000)>>16));
        uart_printf(1,"%02u",(u16)(ECBM_MCU_ROM_SIZE));
        #if     (ECBM_MCU==0x110301)
            uart_printf(1,"-8PIN");
        #elif   (ECBM_MCU==0x110302)
            uart_printf(1,"S2-16PIN/20PIN");
        #elif   (ECBM_MCU==0x120502)
            uart_printf(1,"S2");
        #elif   (ECBM_MCU==0x120504)
            uart_printf(1,"S4");
        #elif   (ECBM_MCU==0x2405C2)
            uart_printf(1,"S2A12");
        #elif   (ECBM_MCU==0x2815C4)
            uart_printf(1,"D4");
        #elif   (ECBM_MCU==0x2805C4)
            uart_printf(1,"S4A12");
        #elif   (ECBM_MCU==0x3103A2)
            uart_printf(1,"-16PIN/20PIN");
        #elif   (ECBM_MCU==0x310201)
            uart_printf(1,"-8PIN ");
        #elif   (ECBM_MCU==0x3102A1)
            uart_printf(1,"A-8PIN");
        #elif   (ECBM_MCU==0x3103A1)
            uart_printf(1,"T-20PIN");
        #elif   (ECBM_MCU==0x3205A2)
            uart_printf(1,"S2");
        #elif   (ECBM_MCU==0x3205A4)
            uart_printf(1,"S4");
        #elif   (ECBM_MCU==0x4103A2)
            uart_printf(1,"-20PIN");
        #elif   (ECBM_MCU==0x4105A2)
            uart_printf(1,"-32PIN");
        #elif   (ECBM_MCU==0x4305C2)
            uart_printf(1,"S2");
        #elif   (ECBM_MCU==0x4305C4)
            uart_printf(1,"S4");
        #elif   (ECBM_MCU==0x4805C4)
            uart_printf(1,"U");
        #elif   (ECBM_MCU==0x520502)
            uart_printf(1,"S2");
        #elif   (ECBM_MCU==0x520504)
            uart_printf(1,"S4");
        #endif
        j=0;
        uart_printf(1,"\r\nChecking MCU ID");
        for(i=0;i<7;i++){
            uart_printf(1,".");
            if((REG_ID(i))==(MCUID[i])){
                j++;
            }
        }
        if(j!=7){
            uart_printf(1,"Error\r\nPlease check the setting of the MCU model\r\n");
        }else{
            uart_printf(1,"OK\r\nID    :");for(i=0;i<7;i++){uart_printf(1,"%02X",(u16)(MCUID[i]));}uart_printf(1,"\r\n");
            uart_printf(1,"DATA  :128\tByte\r\n");
            uart_printf(1,"IDATA :128\tByte\r\n");
            uart_printf(1,"XDATA :%u\tByte\r\n",(u16)((ECBM_MCU&0x0F0000)>>16)*1024);
            uart_printf(1,"FLASH :%lu\tByte\r\n",(u32)ECBM_MCU_ROM_SIZE*1024);
            uart_printf(1,"SYSCLK:%lu\tHz\r\n",ECBM_SYSCLK_SETTING);
            uart_printf(1,"BGV   :%u\tmV\r\n",REG_BGV);
            uart_printf(1,"ENDIAN:");
            if(*((char*)(&aaa))==0x12)uart_printf(1,"big\tendian\r\n");
            if(*((char*)(&aaa))==0x34)uart_printf(1,"little\tendian\r\n");
        }
    }
#endif

extern void beep_init(void);
void system_init(void){
    #if (SYSTEM_CLEAR_XDATA_LEN)
    u16 i_u16;
    for(i_u16=0;i_u16<SYSTEM_CLEAR_XDATA_LEN;i_u16++){
        (*((u8  volatile xdata *)i_u16))=0;
    }
    #endif
    EX_SFR_ENABLE;

    #if ((ECBM_UART_LIB_EN)&&(ECBM_AUTO_DOWNLOAD_EN))
        auto_download_en_gb=1;
        auto_download_old_char_gdu8=0;
        auto_download_char_count_gdu8=0;
        uart_init();
    #endif

    #if (ECBM_10MS_EN)
        #if     (ECBM_10MS_TIMER==0)
            TIMER0_SET_MODE_12T;
            TIMER0_SET_REG_HL(65536UL-(u32)(ECBM_SYSCLK_SETTING/1200));
            TIMER0_SET_MODE_TIMER;
            TIMER0_IT_ENABLE;
            TIMER0_POWER_ON;
        #elif   (ECBM_10MS_TIMER==1)
            TIMER1_SET_MODE_12T;
            TIMER1_SET_REG_HL(65536UL-(u32)(ECBM_SYSCLK_SETTING/1200));
            TIMER1_SET_MODE_TIMER;
            TIMER1_IT_ENABLE;
            TIMER1_POWER_ON;
        #elif   (ECBM_10MS_TIMER==2)
            TIMER2_SET_MODE_12T;
            TIMER2_SET_REG_HL(65536UL-(u32)(ECBM_SYSCLK_SETTING/1200));
            TIMER2_SET_MODE_TIMER;
            TIMER2_IT_ENABLE;
            TIMER2_POWER_ON;
        #elif   (ECBM_10MS_TIMER==3)
            TIMER3_SET_MODE_12T;
            TIMER3_SET_REG_HL(65536UL-(u32)(ECBM_SYSCLK_SETTING/1200));
            TIMER3_SET_MODE_TIMER;
            TIMER3_IT_ENABLE;
            TIMER3_POWER_ON;
        #elif   (ECBM_10MS_TIMER==4)
            TIMER4_SET_MODE_12T;
            TIMER4_SET_REG_HL(65536UL-(u32)(ECBM_SYSCLK_SETTING/1200));
            TIMER4_SET_MODE_TIMER;
            TIMER4_IT_ENABLE;
            TIMER4_POWER_ON;
        #endif
        #if ((ECBM_STREAM_LIB_EN)&&(ECBM_STREAM_CH_COUNT))
            ecbm_stream_init();
        #endif
        #if (ECBM_BEEP_EN)
            beep_init();
        #endif
    #endif

    #if ((ECBM_POWER_LIB_EN)&&(ECBM_POWER_RST_CFG_EN))
        power_rstcfg_init();
    #endif

    #if (ECBM_SYSCLK_OUT_EN)
        #if ((ECBM_MCU&0xF00000)>0x200000)
            #if (ECBM_SYSLCK_OUT_PIN)
                CLK_SET_OUT_TO_P16_GH;
            #else
                CLK_SET_OUT_TO_P54_GH;
            #endif
            CLK_OUT_SET_DIV_GH(ECBM_SYSCLK_OUT_SETTING_GH);
        #else
            #if (ECBM_SYSLCK_OUT_PIN)
                CLK_SET_OUT_TO_P16_FA;
            #else
                CLK_SET_OUT_TO_P54_FA;
            #endif
            CLK_OUT_SET_DIV_FA(ECBM_SYSCLK_OUT_SETTING_FA);
        #endif
    #endif

    EA_ENABLE;
    #if ((ECBM_UART_LIB_EN)&&(ECBM_UART1_EN)&&(ECBM_UART_PRINTF_EN)&&(ECBM_PRINTF_EN)&&(ECBM_MCU_CHECK_EN))
        delay_ms(500);
        system_check();
    #endif
}

#if (ECBM_STRING_EN)

u16 str_find(s8 * dest,s8 * key){
    u16 key_count_u16,count_u16;
    key_count_u16=0;
    count_u16    =0;
    while(*dest){
        if(key[key_count_u16]==(*dest)){
            key_count_u16++;
        }else if(key[0]==(*dest)){
			key_count_u16=1;
        }else{
            key_count_u16=0;
        }
		count_u16++;
        dest++;
        if(key[key_count_u16]==0){
            return (count_u16-key_count_u16);
        }
    }
    return 0xffff;
}

u8 str_read_pin(s8 * str,u16 pos){
    u8  dat_u8,offset_u8,count_u8;
    dat_u8=0;
    count_u8=0;
    for(offset_u8=0;offset_u8<10;offset_u8++){
        if((str[pos+offset_u8]>='0')&&(str[pos+offset_u8]<='7')){
            count_u8++;
            if(count_u8==1){
                dat_u8=(str[pos+offset_u8]-'0')<<4;
            }
            if(count_u8==2){
                dat_u8=(str[pos+offset_u8]-'0')|dat_u8;
                return dat_u8;
            }
        }
        if((str[pos+offset_u8]>='8')&&(str[pos+offset_u8]<='9')){
            count_u8++;
        }
        if(str[pos+offset_u8]==',')break;
        if(str[pos+offset_u8]==0)break;
    }
    return dat_u8;
}

u16 str_read_u16(s8 * str,u16 pos){
    u16 dat_u16;
    u8  offset_u8;
    dat_u16=0;
    for(offset_u8=0;offset_u8<20;offset_u8++){
        if((str[pos+offset_u8]>='0')&&(str[pos+offset_u8]<='9')){
            dat_u16*=10;
            dat_u16+=str[pos+offset_u8]-'0';
        }
        if(str[pos+offset_u8]==',')break;
        if(str[pos+offset_u8]=='.')break;
        if(str[pos+offset_u8]==0)break;
    }
    return dat_u16;
}

u8 str_push_len(u8 * dest,u16 dlen,u8 * key,u16 klen){
    u16 i_u16,j_u16,start_u16,stop_u16;
    j_u16    =0;
    start_u16=0;
    stop_u16 =0;
    for(i_u16=0;i_u16<dlen;i_u16++){
        if(dest[i_u16]==key[j_u16]){
            j_u16++;
            if(j_u16==klen){
                stop_u16=i_u16;
                break;
            }
        }else{
            j_u16=0;
            start_u16=i_u16+1;
        }
    }
    if(start_u16<=stop_u16){
        for(i_u16=start_u16;i_u16<stop_u16;i_u16++){
            dest[i_u16]=0;
        }
        return 1;
    }else{
        return 0;
    }
}
#endif



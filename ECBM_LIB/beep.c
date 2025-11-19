#include "ecbm_core.h"
#if (ECBM_BEEP_EN)


#define ECBM_BEEP_OFF       (0)
#define ECBM_BEEP_IDLE      (1)
#define ECBM_BEEP_AUTO_ON   (2)
#define ECBM_BEEP_AUTO_OFF  (3)



u8 beep_on_time_gu8;
u8 beep_off_time_gu8;
u8 beep_count_gu8;
u8 beep_time_gu8;
u8 beep_state_gu8;


void beep_init(void){
    BEEP_IO=!ECBM_BEEP_IO_WORK;
    #if   (ECBM_BEEP_IO_PORT==0x80)
        gpio_mode(D00+ECBM_BEEP_IO_PIN,GPIO_OUT);
    #elif (ECBM_BEEP_IO_PORT==0x90)
        gpio_mode(D10+ECBM_BEEP_IO_PIN,GPIO_OUT);
    #elif (ECBM_BEEP_IO_PORT==0xA0)
        gpio_mode(D20+ECBM_BEEP_IO_PIN,GPIO_OUT);
    #elif (ECBM_BEEP_IO_PORT==0xB0)
        gpio_mode(D30+ECBM_BEEP_IO_PIN,GPIO_OUT);
    #elif (ECBM_BEEP_IO_PORT==0xC0)
        gpio_mode(D40+ECBM_BEEP_IO_PIN,GPIO_OUT);
    #elif (ECBM_BEEP_IO_PORT==0xC8)
        gpio_mode(D50+ECBM_BEEP_IO_PIN,GPIO_OUT);
    #elif (ECBM_BEEP_IO_PORT==0xE8)
        gpio_mode(D60+ECBM_BEEP_IO_PIN,GPIO_OUT);
    #elif (ECBM_BEEP_IO_PORT==0xF8)
        gpio_mode(D70+ECBM_BEEP_IO_PIN,GPIO_OUT);
    #endif
    beep_on_time_gu8=ECBM_BEEP_ON_TIME_MAX;
    beep_off_time_gu8=ECBM_BEEP_OFF_TIME_MAX;
    beep_count_gu8=0;
    beep_time_gu8=0;
    beep_state_gu8=ECBM_BEEP_OFF;
}

void beep_run(void){
    switch(beep_state_gu8){
        case ECBM_BEEP_OFF:{
            BEEP_IO=!ECBM_BEEP_IO_WORK;
            if(beep_count_gu8){
                beep_time_gu8=0;
                beep_state_gu8=ECBM_BEEP_AUTO_ON;
            }
        }break;
        case ECBM_BEEP_IDLE:{

        }break;
        case ECBM_BEEP_AUTO_ON:{
            BEEP_IO=ECBM_BEEP_IO_WORK;
            beep_time_gu8++;
            if(beep_time_gu8>=beep_on_time_gu8){
                beep_time_gu8=0;
                beep_count_gu8--;
                beep_state_gu8=ECBM_BEEP_AUTO_OFF;
            }
        }break;
        case ECBM_BEEP_AUTO_OFF:{
            BEEP_IO=!ECBM_BEEP_IO_WORK;
            beep_time_gu8++;
            if(beep_time_gu8>=beep_off_time_gu8){
                beep_time_gu8=0;
                if(beep_count_gu8){
                    beep_state_gu8=ECBM_BEEP_AUTO_ON;
                }else{
                    beep_state_gu8=ECBM_BEEP_OFF;
                }
            }
        }
    }
}

void beep_set_class(u8 on_time,u8 off_time){
    beep_on_time_gu8=on_time;
    beep_off_time_gu8=off_time;
}

void beep_start(u8 count){
    beep_count_gu8=count;
    if(beep_state_gu8==ECBM_BEEP_IDLE){
        beep_state_gu8=ECBM_BEEP_OFF;
    }
}

void beep_idle(void){
    beep_state_gu8=ECBM_BEEP_IDLE;
}
#endif


#include "ecbm_core.h"
#if (ECBM_LED_LIB_EN)


void led_init(void){
    LED_SET_REG_COMEN(ECBM_LED_COM_EN);
    LED_SET_REG_SEGENL(ECBM_LED_SEGL_EN);
    LED_SET_REG_SEGENH(ECBM_LED_SEGH_EN);
    LED_SET_REG_CTRL(ECBM_LED_CTRL);
    LED_SET_REG_CKS(ECBM_LED_CLK_DIV);
}

void led_start(void){
    LED_POWER_ON;
}

void led_stop(void){
    LED_POWER_OFF;
}

void led_set_mode(u8 mode){
    switch(mode){
        case LED_MODE_DC :{LED_SET_MODE_DC; }break;
        case LED_MODE_DA :{LED_SET_MODE_DA; }break;
        case LED_MODE_DCA:{LED_SET_MODE_DCA;}break;
    }
}

void led_set_duty(u8 duty){
    LED_SET_DUTY(duty);
}

void led_set_freq(u8 freq){

    freq=freq;
}
#endif



#include "ecbm_core.h"
#if (ECBM_PWM16_OUT_LIB_EN)

#if (ECBM_MCU!=0x4805C4)
#error "本库只适用于STC8H8K64U,其他型号的PWM原理和寄存器不同不能使用!"
#endif


void pwm16_out_init(void){
    PWMA_PS   =ECBM_PWM16_OUT_GROUPA_PIN_SEL;
    PWMA_ETRPS=ECBM_PWM16_OUT_GROUPA_EXT_PIN_SEL;
    PWMA_ENO  =ECBM_PWM16_OUT_GROUPA_PIN_EN;
    PWMA_IOAUX=ECBM_PWM16_OUT_GROUPA_IOAUX;
    PWMA_PSCR =ECBM_PWM16_OUT_GROUPA_FREQ;
    PWMA_ARR  =ECBM_PWM16_OUT_GROUPA_ARR;
    PWMA_CCR1 =ECBM_PWM16_OUT_GROUPA_CH1_DUTY;
    PWMA_CCR2 =ECBM_PWM16_OUT_GROUPA_CH2_DUTY;
    PWMA_CCR3 =ECBM_PWM16_OUT_GROUPA_CH3_DUTY;
    PWMA_CCR4 =ECBM_PWM16_OUT_GROUPA_CH4_DUTY;
    PWMA_DTR  =ECBM_PWM16_OUT_GROUPA_DTR;
    PWMA_OISR =ECBM_PWM16_OUT_GROUPA_PIN_OIS;
    PWMA_CCER1=ECBM_PWM16_OUT_GROUPA_PIN12_POL;
    PWMA_CCER2=ECBM_PWM16_OUT_GROUPA_PIN34_POL;
    PWMA_BKR  =ECBM_PWM16_OUT_GROUPA_BKR;
    PWMA_CR1  =ECBM_PWM16_OUT_GROUPA_CR1;

    PWMB_PS   =ECBM_PWM16_OUT_GROUPB_PIN_SEL;
    PWMB_ETRPS=ECBM_PWM16_OUT_GROUPB_EXT_PIN_SEL;
    PWMB_ENO  =ECBM_PWM16_OUT_GROUPB_PIN_EN;
    PWMB_IOAUX=ECBM_PWM16_OUT_GROUPB_IOAUX;
    PWMB_PSCR =ECBM_PWM16_OUT_GROUPB_FREQ;
    PWMB_ARR  =ECBM_PWM16_OUT_GROUPB_ARR;
    PWMB_CCR5 =ECBM_PWM16_OUT_GROUPB_CH5_DUTY;
    PWMB_CCR6 =ECBM_PWM16_OUT_GROUPB_CH6_DUTY;
    PWMB_CCR7 =ECBM_PWM16_OUT_GROUPB_CH7_DUTY;
    PWMB_CCR8 =ECBM_PWM16_OUT_GROUPB_CH8_DUTY;
    PWMB_DTR  =ECBM_PWM16_OUT_GROUPB_DTR;
    PWMB_OISR =ECBM_PWM16_OUT_GROUPB_PIN_OIS;
    PWMB_CCER1=ECBM_PWM16_OUT_GROUPB_PIN56_POL;
    PWMB_CCER2=ECBM_PWM16_OUT_GROUPB_PIN78_POL;
    PWMB_BKR  =ECBM_PWM16_OUT_GROUPB_BKR;
    PWMB_CR1  =ECBM_PWM16_OUT_GROUPB_CR1;
}

void pwm16_out_groupa_start(void){
    PWMA_BKR|=0x80;
    PWMA_CR1|=0x01;
}
void pwm16_out_groupb_start(void){
    PWMB_BKR|=0x80;
    PWMB_CR1|=0x01;
}

void pwm16_out_groupa_stop(void){
    PWMA_CR1&=~0x01;
    PWMA_BKR&=~0x80;
}
void pwm16_out_groupb_stop(void){
    PWMB_CR1&=~0x01;
    PWMB_BKR&=~0x80;
}

void pwm16_out_set_freq(u8 ch,u32 freq){
    u32 temp,temp2,temp3;
    if(freq){
        temp=(ECBM_SYSCLK_SETTING/freq);
        if(temp>=65535UL){
            temp2=temp/65535UL;
            temp3=temp/(temp2+1);
        }else{
            temp2=0;
            temp3=temp;
        }
        if(temp3){
            temp3--;
        }
        if(ch<=4){
            PWMA_PSCR=(u16)(temp2);
            PWMA_ARR =(u16)(temp3);
        }else if(ch<=8){
            PWMB_PSCR=(u16)(temp2);
            PWMB_ARR =(u16)(temp3);
        }
    }
}

void pwm16_out_set_duty(u8 ch,u16 ch_duty){
    u16 arr_temp,ccmr_temp;
    if(ch_duty==0){
        ccmr_temp=0x40;
        arr_temp=0;
    }else if(ch_duty>=10000){
        ccmr_temp=0x50;
        arr_temp=0;
    }else{
        ccmr_temp=0x60;
        if(ch<=4){
            arr_temp=(u16)((u32)(PWMA_ARR)*(u32)(ch_duty)/10000UL);
        }else if(ch<=8){
            arr_temp=(u16)((u32)(PWMB_ARR)*(u32)(ch_duty)/10000UL);
        }
    }
    switch(ch){
        case 1:{PWMA_CCMR1=ccmr_temp;PWMA_CCR1=arr_temp;}break;
        case 2:{PWMA_CCMR2=ccmr_temp;PWMA_CCR2=arr_temp;}break;
        case 3:{PWMA_CCMR3=ccmr_temp;PWMA_CCR3=arr_temp;}break;
        case 4:{PWMA_CCMR4=ccmr_temp;PWMA_CCR4=arr_temp;}break;
        case 5:{PWMB_CCMR1=ccmr_temp;PWMB_CCR5=arr_temp;}break;
        case 6:{PWMB_CCMR2=ccmr_temp;PWMB_CCR6=arr_temp;}break;
        case 7:{PWMB_CCMR3=ccmr_temp;PWMB_CCR7=arr_temp;}break;
        case 8:{PWMB_CCMR4=ccmr_temp;PWMB_CCR8=arr_temp;}break;
    }
}

void pwm16_out_pulse_start(u8 ch,u8 ch_count){
    if(ch_count){
        switch(ch){
            case 1:{PWMA_CCMR1=0x60;PWMA_CCR1=PWMA_ARR>>1;}break;
            case 2:{PWMA_CCMR2=0x60;PWMA_CCR2=PWMA_ARR>>1;}break;
            case 3:{PWMA_CCMR3=0x60;PWMA_CCR3=PWMA_ARR>>1;}break;
            case 4:{PWMA_CCMR4=0x60;PWMA_CCR4=PWMA_ARR>>1;}break;
            case 5:{PWMB_CCMR1=0x60;PWMB_CCR5=PWMB_ARR>>1;}break;
            case 6:{PWMB_CCMR2=0x60;PWMB_CCR6=PWMB_ARR>>1;}break;
            case 7:{PWMB_CCMR3=0x60;PWMB_CCR7=PWMB_ARR>>1;}break;
            case 8:{PWMB_CCMR4=0x60;PWMB_CCR8=PWMB_ARR>>1;}break;
        }
        if(ch<=4){
            PWMA_CR1|=0x08;
            PWMA_RCR=ch_count-1;
            pwm16_out_groupa_start();
        }else if(ch<=8){
            PWMB_CR1|=0x08;
            PWMB_RCR=ch_count-1;
            pwm16_out_groupb_start();
        }
    }
}

void pwm16_out_wave_start(u8 ch,u16 ch_duty){
    pwm16_out_set_duty(ch,ch_duty);
    if(ch<=4){
        PWMA_CR1&=~0x08;
        pwm16_out_groupa_start();
    }else if(ch<=8){
        PWMB_CR1&=~0x08;
        pwm16_out_groupb_start();
    }
}
#endif



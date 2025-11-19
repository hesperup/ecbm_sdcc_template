#include "ecbm_core.h"
#if (ECBM_EXTI_LIB_EN)


void exti_init(void){
    #if (ECBM_EXTI0_EN)
        gpio_mode(D32,GPIO_IN);
        EXTI0_SET_IO_HIGH;
        #if (ECBM_EXTI0_MODE==0)
            EXTI0_SET_MODE_UP_DOWN;
        #else
            EXTI0_SET_MODE_DOWN;
        #endif
        #if (ECBM_EXTI0_INIT)
            EXTI0_ENABLE;
        #endif
    #endif

    #if (ECBM_EXTI1_EN)
        gpio_mode(D33,GPIO_IN);
        EXTI1_SET_IO_HIGH;
        #if (ECBM_EXTI1_MODE==0)
            EXTI1_SET_MODE_UP_DOWN;
        #else
            EXTI1_SET_MODE_DOWN;
        #endif
        #if (ECBM_EXTI1_INIT)
            EXTI1_ENABLE;
        #endif
    #endif

    #if (ECBM_EXTI2_EN)
        gpio_mode(D36,GPIO_IN);
        EXTI2_SET_IO_HIGH;
        #if (ECBM_EXTI2_INIT)
            EXTI2_ENABLE;
        #endif
    #endif

    #if (ECBM_EXTI3_EN)
        gpio_mode(D37,GPIO_IN);
        EXTI3_SET_IO_HIGH;
        #if (ECBM_EXTI3_INIT)
            EXTI3_ENABLE;
        #endif
    #endif

    #if (ECBM_EXTI4_EN)
        gpio_mode(D30,GPIO_IN);
        EXTI4_SET_IO_HIGH;
        #if (ECBM_EXTI4_INIT)
            EXTI4_ENABLE;
        #endif
    #endif
}

void exti_start(u8 id){
    switch(id){
        #if (ECBM_EXTI0_EN)
            case 0:{EXTI0_ENABLE;}break;
        #endif
        #if (ECBM_EXTI1_EN)
            case 1:{EXTI1_ENABLE;}break;
        #endif
        #if (ECBM_EXTI2_EN)
            case 2:{EXTI2_ENABLE;}break;
        #endif
        #if (ECBM_EXTI3_EN)
            case 3:{EXTI3_ENABLE;}break;
        #endif
        #if (ECBM_EXTI4_EN)
            case 4:{EXTI4_ENABLE;}break;
        #endif
        default:break;
    }
}

void exti_stop(u8 id){
    switch(id){
        #if (ECBM_EXTI0_EN)
            case 0:{EXTI0_DISABLE;}break;
        #endif
        #if (ECBM_EXTI1_EN)
            case 1:{EXTI1_DISABLE;}break;
        #endif
        #if (ECBM_EXTI2_EN)
            case 2:{EXTI2_DISABLE;}break;
        #endif
        #if (ECBM_EXTI3_EN)
            case 3:{EXTI3_DISABLE;}break;
        #endif
        #if (ECBM_EXTI4_EN)
            case 4:{EXTI4_DISABLE;}break;
        #endif
        default:break;
    }
}

void exti_set_mode(u8 id,u8 mode){
    mode=mode;
    switch(id){
        default:break;
        #if (ECBM_EXTI0_EN)
            case 0:{
                if(mode){
                    EXTI0_SET_MODE_DOWN;
                }else{
                    EXTI0_SET_MODE_UP_DOWN;
                }
            }break;
        #endif
        #if (ECBM_EXTI1_EN)
            case 1:{
                if(mode){
                    EXTI1_SET_MODE_DOWN;
                }else{
                    EXTI1_SET_MODE_UP_DOWN;
                }
            }break;
        #endif
    }
}
#endif



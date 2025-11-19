#include "ecbm_core.h"
#if (ECBM_LCM_LIB_EN)

#if (ECBM_MCU!=0x2815C4)
#   error 请使用带LCM外设的单片机型号！
#endif


void lcm_init(void){
    LCMIFCFG =ECBM_LCM_CFG1;
    LCMIFCFG2=ECBM_LCM_CFG2;
    #if   ((ECBM_LCM_CFG1&0x0E)==0x00)
        P2M1=0x00;
        P2M0=0x00;
    #elif ((ECBM_LCM_CFG1&0x0E)==0x04)
        P6M1=0x00;
        P6M0=0x00;
    #elif ((ECBM_LCM_CFG1&0x0E)==0x02)
        P2M1=0x00;
        P2M0=0x00;
        P0M1=0x00;
        P0M0=0x00;
    #elif ((ECBM_LCM_CFG1&0x0E)==0x06)
        P2M1=0x00;
        P2M0=0x00;
        P6M1=0x00;
        P6M0=0x00;
    #elif ((ECBM_LCM_CFG1&0x0E)==0x0A)
        P2M1=0x00;
        P2M0=0x00;
        P7M1=0x00;
        P7M0=0x00;
    #elif ((ECBM_LCM_CFG1&0x0E)==0x0E)
        P6M1=0x00;
        P6M0=0x00;
        P7M1=0x00;
        P7M0=0x00;
    #endif
    #if   ((ECBM_LCM_CFG2&0x60)==0x00)
        gpio_mode(D41,GPIO_OUT);
        gpio_mode(D44,GPIO_OUT);
        gpio_mode(D43,GPIO_OUT);
    #elif ((ECBM_LCM_CFG2&0x60)==0x20)
        gpio_mode(D41,GPIO_OUT);
        gpio_mode(D37,GPIO_OUT);
        gpio_mode(D36,GPIO_OUT);
    #elif ((ECBM_LCM_CFG2&0x60)==0x40)
        gpio_mode(D41,GPIO_OUT);
        gpio_mode(D42,GPIO_OUT);
        gpio_mode(D40,GPIO_OUT);
    #elif ((ECBM_LCM_CFG2&0x60)==0x60)
        gpio_mode(D40,GPIO_OUT);
        gpio_mode(D37,GPIO_OUT);
        gpio_mode(D36,GPIO_OUT);
    #endif
}

void lcm_write_8cmd(u8 cmd){
    u16 timeout_u16=4800;
    LCMIFDATL=cmd;
    LCM_WRITE_CMD;
    while((LCM_GET_FLAG==0)&&(timeout_u16))timeout_u16--;
    LCM_CLS_FLAG;
}

void lcm_write_8data(u8 dat){
    u16 timeout_u16=4800;
    LCMIFDATL=dat;
    LCM_WRITE_DATA;
    while((LCM_GET_FLAG==0)&&(timeout_u16))timeout_u16--;
    LCM_CLS_FLAG;
}

void lcm_write_16cmd(u16 cmd){
    u16 timeout_u16=4800;
    LCMIFDATH=(u8)(cmd>>8);
    LCMIFDATL=(u8)(cmd);
    LCM_WRITE_CMD;
    while((LCM_GET_FLAG==0)&&(timeout_u16))timeout_u16--;
    LCM_CLS_FLAG;
}

void lcm_write_16data(u16 dat){
    u16 timeout_u16=4800;
    LCMIFDATH=(u8)(dat>>8);
    LCMIFDATL=(u8)(dat);
    LCM_WRITE_DATA;
    while((LCM_GET_FLAG==0)&&(timeout_u16))timeout_u16--;
    LCM_CLS_FLAG;
}
#endif



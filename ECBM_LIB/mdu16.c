#include "ecbm_core.h"
#if (ECBM_MDU16_LIB_EN)

#if (((ECBM_MCU&0xF00000)<=0x200000)&&(ECBM_MCU!=0x2815C4))
#   error 该单片机没有MDU16！
#endif


u8 div32(u32 * num1,u16 * num2){
    MDU16_RESET;
    MDU16_SET_32DIV;
    MD3MD2MD1MD0=*num1;
    MD5MD4      =*num2;
    MDU16_START;
    while(MDU16_GET_END_FLAG);
    *num1=MD3MD2MD1MD0;
    *num2=MD5MD4;
    return MDU16_GET_MDOV_FLAG;
}

u8 div16(u16 * num1,u16 * num2){
    MDU16_RESET;
    MDU16_SET_16DIV;
    MD1MD0 =*num1;
    MD5MD4 =*num2;
    MDU16_START;
    while(MDU16_GET_END_FLAG);
    *num1=MD1MD0;
    *num2=MD5MD4;
    return MDU16_GET_MDOV_FLAG;
}

u8 mul16(u16 num1,u16 num2,u32 * num3){
    MDU16_RESET;
    MDU16_SET_16MUL;
    MD1MD0 =num1;
    MD5MD4 =num2;
    MDU16_START;
    while(MDU16_GET_END_FLAG);
    *num3=MD3MD2MD1MD0;
    return MDU16_GET_MDOV_FLAG;
}
#endif



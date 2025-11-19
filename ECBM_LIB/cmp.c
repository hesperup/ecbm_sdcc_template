#include "ecbm_core.h"
#if (ECBM_CMP_LIB_EN)

#if (ECBM_MCU==0x110301)||(ECBM_MCU==0x310201)||(ECBM_MCU==0x3102A1)
#   error 该型号没有比较器！
#endif


void cmp_init(void){
    CMP_SET_REG_CMPCR2(ECBM_CMP_CMPCR2);
    CMP_SET_REG_CMPCR1(ECBM_CMP_CMPCR1);
    CMP_SET_REG_CMPEXCFG(ECBM_CMP_EXCFG);
    #if (ECBM_CMP_INIT_ON)
        CMP_POWER_ON;
    #endif
}

u8 cmp_read(void){
    if(CMP_GET_RESULT){
        return 1;
    }else{
        return 0;
    }
}

void cmp_start(void){
    CMP_POWER_ON;
}

void cmp_stop(void){
    CMP_POWER_OFF;
}
#endif



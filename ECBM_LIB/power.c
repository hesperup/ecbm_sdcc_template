#include "ecbm_core.h"
#if (ECBM_POWER_LIB_EN)


#if (ECBM_POWER_RESET_EN)
    void power_reset_code(void){
        _nop_();
        MCU_RESET;
        _nop_();
        _nop_();
    }
#endif

#if (ECBM_POWER_RESET_EN)
    void power_reset_isp(void){
        _nop_();
        POWER_RESET;
        _nop_();
        _nop_();
    }
#endif

#if (ECBM_POWER_CONTROL_EN)
    void power_powerdown(void){
        #if (ECBM_POWER_WKTC_CONFIG&0x8000)
            WKT_SET_REG_COUNT(ECBM_POWER_WKTC_CONFIG);
        #endif
        _nop_();
        POWER_DOWN;
        _nop_();
        _nop_();
    }
#endif

#if (ECBM_POWER_CONTROL_EN)
    void power_cpu_idle(void){
        _nop_();
        POWER_IDLE;
        _nop_();
        _nop_();
    }
#endif

#if (ECBM_POWER_WDOG_EN)
    void wdt_start(void){
        WDT_SET_REG_CONTR(ECBM_POWER_WDT_MODE|EN_WDT);
    }
#endif

#if (ECBM_POWER_WDOG_EN)
    void wdt_feed(void){
        WDT_CLR;
    }
#endif

#if (ECBM_POWER_RST_CFG_EN)
    void power_rstcfg_init(void){
        SYS_SET_REG_RSTCFG(ECBM_POWER_RST_CFG_MODE);
    }
#endif
#endif



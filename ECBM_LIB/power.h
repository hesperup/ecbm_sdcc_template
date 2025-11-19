#ifndef _ECBM_POWER_H_
#define _ECBM_POWER_H_








#define ECBM_POWER_WDOG_EN (0)













#define ECBM_POWER_WDT_MODE (0x05)



#define ECBM_POWER_RESET_EN (0)


#define ECBM_POWER_CONTROL_EN (0)





#define ECBM_POWER_WKTC_CONFIG (4095)





#define ECBM_POWER_RST_CFG_EN (0)











#define ECBM_POWER_RST_CFG_MODE (0x00)




#include "ecbm_core.h"


extern void power_reset_code(void);

extern void power_reset_isp(void);

extern void power_powerdown(void);

extern void power_cpu_idle(void);

extern void wdt_start(void);

extern void wdt_feed(void);

extern void power_rstcfg_init(void);
#endif



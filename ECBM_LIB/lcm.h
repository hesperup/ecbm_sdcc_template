#ifndef _ECBM_LCM_H_
#define _ECBM_LCM_H_
















#define ECBM_LCM_CFG1 (0x00)











#define ECBM_LCM_CFG2 (0x1F)



#include "ecbm_core.h"


extern void lcm_init(void);

extern void lcm_write_8cmd(u8 cmd);

extern void lcm_write_8data(u8 dat);

extern void lcm_write_16cmd(u16 cmd);

extern void lcm_write_16data(u16 dat);
#endif



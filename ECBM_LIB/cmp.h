#ifndef _ECBM_CMP_H_
#define _ECBM_CMP_H_
























#define ECBM_CMP_CMPCR1 (0x30)



#define ECBM_CMP_OUT_IO (0x00)










#define ECBM_CMP_CMPCR2 (193)


#define ECBM_CMP_INIT_ON (1)















#define ECBM_CMP_EXCFG (0x00)




#include "ecbm_core.h"


extern void cmp_init(void);

extern u8 cmp_read(void);

extern void cmp_start(void);

extern void cmp_stop(void);

extern void cmp_it_callback(void);
#endif



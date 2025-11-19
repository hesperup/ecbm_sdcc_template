#ifndef _ECBM_EDS_H_
#define _ECBM_EDS_H_









#define EDS_ERROR_SUM_HANDLING (5)



#include "ecbm_core.h"

#define EDS_OK          (0)
#define EDS_ERR_NULL    (1)
#define EDS_ERR_ID      (2)
#define EDS_ERR_SECTOR  (3)

#define EDS_ERR_SUM     (4)
#define EDS_ERR_DATA    (5)

#define EDS_WAR_DATA    (6)

#define EDS_DATA_VOID   (7)
#define EDS_DATA_EXISTS (8)


extern u8 eds_init(u8 sector_start,u8 sector_szie,u16 pack_len);

extern u8 eds_write(u8 sector_start,u8 * buf);

extern u8 eds_read(u8 sector_start,u8 * buf);
#endif


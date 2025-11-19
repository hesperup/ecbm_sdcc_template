#ifndef _ECBM_EEPROM_H_
#define _ECBM_EEPROM_H_






#define ECBM_EEPROM_EX_EN (0)



#include "ecbm_core.h"

extern u8 xdata eeprom_ex_buf_gxu8a[512];


extern void eeprom_init(void);

extern void eeprom_erase(u16 addr);

extern void eeprom_write(u16 addr,u8 dat);

extern u8 eeprom_read(u16 addr);

extern void eeprom_read_ex(u16 addr,u8 * dat,u16 num);

extern void eeprom_write_ex(u16 addr,u8 * dat,u16 num);
#endif



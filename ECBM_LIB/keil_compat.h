#ifndef _ECBM_KEIL_COMPAT_H_
#define _ECBM_KEIL_COMPAT_H_


#ifdef __SDCC

#ifndef xdata
#define xdata
#endif
#ifndef data
#define data
#endif
#ifndef idata
#define idata
#endif
#ifndef code
#define code
#endif


#ifndef bit
typedef unsigned char bit;
#endif

#endif

#endif


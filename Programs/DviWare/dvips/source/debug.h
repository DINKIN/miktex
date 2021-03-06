/* 
 * Here's some stuff for debugging dvips.  See dvips.h for copyright.
 */

#ifdef DEBUG

#define dd(darg)	((darg)&debug_flag)

#define D_SPECIAL		(1<<0)
#define D_PATHS			(1<<1)
#define D_FONTS			(1<<2)
#define D_PAGE			(1<<3)
#define D_HEADER                (1<<4)
#define D_COMPRESS              (1<<5)
#define D_FILES			(1<<6)
#define D_MEM                   (0) /* too verbose 1<<7 */
#define D_CONFIG                (1<<8)

#ifndef KPATHSEA
#define fopen my_real_fopen
extern FILE *my_real_fopen();
#endif
#endif /* DEBUG */

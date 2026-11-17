/* newlib's locale and multibyte conversion (libc/locale, libc/stdlib/mbtowc_r.c) as vfprintf uses them. */
#ifndef DW4_NEWLIB_LOCALE_H
#define DW4_NEWLIB_LOCALE_H

#include "dw4/newlib_reent.h"

/* only the field vfprintf reads; the full struct lives in the retail data */
struct lconv {
    char *decimal_point;
};

extern int __mb_cur_max;
struct lconv *localeconv(void);
int _mbtowc_r(struct _reent *, int *, const char *, unsigned int, int *);

#endif

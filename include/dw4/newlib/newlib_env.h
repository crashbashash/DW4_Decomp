/* newlib's environment lookup (libc/stdlib/getenv_r.c) and the lock around it (envlock.c). */
#ifndef DW4_NEWLIB_ENV_H
#define DW4_NEWLIB_ENV_H

#include "dw4/newlib/newlib_reent.h"

char *_findenv_r(struct _reent *, const char *, int *);
void __env_lock(struct _reent *);
void __env_unlock(struct _reent *);

#endif

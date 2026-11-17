/* newlib's reentrant system-call stubs (libc/reent) over the kernel's file calls, and the process exit. */
#ifndef DW4_NEWLIB_SYSCALLS_H
#define DW4_NEWLIB_SYSCALLS_H

#include "dw4/newlib_reent.h"

struct stat;

long _read_r(struct _reent *, int, void *, int);
long _write_r(struct _reent *, int, const void *, int);
int _close_r(struct _reent *, int);
int _fstat_r(struct _reent *, int, struct stat *);
int _kill_r(struct _reent *, int, int);
int _getpid_r(struct _reent *);
void _exit(int) __attribute__((noreturn));

#endif

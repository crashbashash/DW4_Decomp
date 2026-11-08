/* newlib's stdio internals: libc/stdio/local.h, fvwrite.h and the __S stream flags. */
#ifndef DW4_NEWLIB_STDIO_H
#define DW4_NEWLIB_STDIO_H

#include "dw4/newlib_reent.h"

typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

#define EOF (-1)
#define BUFSIZ 1024

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SRD 0x0004
#define __SWR 0x0008
#define __SRW 0x0010
#define __SEOF 0x0020
#define __SERR 0x0040
#define __SMBF 0x0080
#define __SAPP 0x0100
#define __SSTR 0x0200
#define __SOPT 0x0400
#define __SNPT 0x0800
#define __SOFF 0x1000
#define __SMOD 0x2000

#define CHECK_INIT(fp) \
  do					\
    {					\
      if ((fp)->_data == 0)		\
	(fp)->_data = _REENT;		\
      if (!(fp)->_data->__sdidinit)	\
	__sinit ((fp)->_data);		\
    }					\
  while (0)

#define cantwrite(fp) \
  ((((fp)->_flags & __SWR) == 0 || (fp)->_bf._base == 0) && __swsetup(fp))
#define HASUB(fp) ((fp)->_ub._base != 0)
#define FREEUB(fp) { \
	if ((fp)->_ub._base != (fp)->_ubuf) \
		_free_r((fp)->_data, (char *)(fp)->_ub._base); \
	(fp)->_ub._base = 0; \
}
#define __sferror(p) (((p)->_flags & __SERR) != 0)

struct __siov {
    const void *iov_base;
    size_t iov_len;
};

struct __suio {
    struct __siov *uio_iov;
    int uio_iovcnt;
    int uio_resid;
};

void __sinit(struct _reent *);
void _free_r(struct _reent *, void *);
int _fwalk(struct _reent *, int (*)(FILE *));
struct _glue *__sfmoreglue(struct _reent *, int);
int __sfvwrite(FILE *, struct __suio *);
int __swsetup(FILE *);
int __srefill(FILE *);
void __smakebuf(FILE *);
int fflush(FILE *);
int __svfscanf(FILE *, const char *, va_list);
int vfprintf(FILE *, const char *, va_list);
int vfiprintf(FILE *, const char *, va_list);
int _vfprintf_r(struct _reent *, FILE *, const char *, va_list);
int _vfiprintf_r(struct _reent *, FILE *, const char *, va_list);

#endif

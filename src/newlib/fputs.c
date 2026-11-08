#include "dw4/newlib_stdio.h"

unsigned int strlen(const char *s);

int fputs(const char *s, FILE *fp)
{
    struct __suio uio;
    struct __siov iov;

    iov.iov_base = s;
    iov.iov_len = uio.uio_resid = strlen(s);
    uio.uio_iov = &iov;
    uio.uio_iovcnt = 1;
    return __sfvwrite(fp, &uio);
}

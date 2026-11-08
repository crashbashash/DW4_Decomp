/* newlib fputs(s, fp). */
typedef unsigned int size_t;
struct __siov { const void *iov_base; size_t iov_len; };
struct __suio { struct __siov *uio_iov; int uio_iovcnt; int uio_resid; };
typedef struct __sFILE FILE;

size_t strlen(const char *);
int FUN_001258b0(FILE *, struct __suio *);

int FUN_00125278(const char *s, FILE *fp)
{
    struct __suio uio;
    struct __siov iov;

    iov.iov_base = s;
    iov.iov_len = uio.uio_resid = strlen(s);
    uio.uio_iov = &iov;
    uio.uio_iovcnt = 1;
    return FUN_001258b0(fp, &uio);
}

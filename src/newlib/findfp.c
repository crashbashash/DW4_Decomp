#include "dw4/newlib_stdio.h"

#define NDYNAMIC 4
#define ENOMEM 12

int __sread(void *, char *, int);
int __swrite(void *, const char *, int);
long __sseek(void *, long, int);
int __sclose(void *);
void *_malloc_r(struct _reent *, unsigned int);
void *memset(void *, int, unsigned int);
void _cleanup_r(struct _reent *);
void std(FILE *, int, int, struct _reent *);

void std(FILE *ptr, int flags, int file, struct _reent *data)
{
    ptr->_p = 0;
    ptr->_r = 0;
    ptr->_w = 0;
    ptr->_flags = flags;
    ptr->_file = file;
    ptr->_bf._base = 0;
    ptr->_bf._size = 0;
    ptr->_lbfsize = 0;
    ptr->_cookie = ptr;
    ptr->_read = __sread;
    ptr->_write = __swrite;
    ptr->_seek = __sseek;
    ptr->_close = __sclose;
    ptr->_data = data;
}

struct _glue *__sfmoreglue(struct _reent *d, int n)
{
    struct _glue *g;
    FILE *p;

    g = _malloc_r(d, sizeof(*g) + n * sizeof(FILE));
    if (g == 0) {
        return 0;
    }
    p = (FILE *)(g + 1);
    g->_next = 0;
    g->_niobs = n;
    g->_iobs = p;
    memset(p, 0, n * sizeof(FILE));
    return g;
}

FILE *__sfp(struct _reent *d)
{
    FILE *fp;
    int n;
    struct _glue *g;

    if (!d->__sdidinit)
        __sinit(d);
    for (g = &d->__sglue;; g = g->_next) {
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++)
            if (fp->_flags == 0)
                goto found;
        if (g->_next == NULL && (g->_next = __sfmoreglue(d, NDYNAMIC)) == NULL)
            break;
    }
    d->_errno = ENOMEM;
    return NULL;

found:
    fp->_flags = 1;
    fp->_p = NULL;
    fp->_w = 0;
    fp->_r = 0;
    fp->_bf._base = NULL;
    fp->_bf._size = 0;
    fp->_lbfsize = 0;
    fp->_file = -1;
    fp->_ub._base = NULL;
    fp->_ub._size = 0;
    fp->_lb._base = NULL;
    fp->_lb._size = 0;
    fp->_data = d;
    return fp;
}

void _cleanup_r(struct _reent *ptr)
{
    _fwalk(ptr, fflush);
}

void _cleanup(void)
{
    _cleanup_r(_REENT);
}

void __sinit(struct _reent *s)
{
    s->__cleanup = _cleanup_r;
    s->__sdidinit = 1;
    std(&s->__sf[0], __SRD, 0, s);
    std(&s->__sf[1], __SWR | __SLBF, 1, s);
    std(&s->__sf[2], __SWR | __SNBF, 2, s);
    s->__sglue._next = 0;
    s->__sglue._niobs = 3;
    s->__sglue._iobs = s->__sf;
}

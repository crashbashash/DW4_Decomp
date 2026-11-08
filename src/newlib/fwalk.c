#include "dw4/newlib_stdio.h"

int _fwalk(struct _reent *ptr, int (*function)(FILE *))
{
    FILE *fp;
    struct _glue *g;
    int n;
    int ret = 0;

    for (g = &ptr->__sglue; g != 0; g = g->_next) {
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++) {
            if (fp->_flags != 0) {
                ret |= (*function)(fp);
            }
        }
    }
    return ret;
}

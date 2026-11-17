#include "dw4/newlib_locale.h"

int _mbtowc_r(struct _reent *ptr, int *pwc, const char *s, unsigned int n, int *state)
{
    int dummy;
    const unsigned char *t = (const unsigned char *)s;

    if (pwc == 0) {
        pwc = &dummy;
    }
    if (s == 0) {
        return 0;
    }
    if (n == 0) {
        return -1;
    }
    *pwc = *t;
    return *t != '\0';
}

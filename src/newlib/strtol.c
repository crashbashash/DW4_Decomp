#include "dw4/newlib_reent.h"

long _strtol_r(struct _reent *, const char *, char **, int);
#define LONG_MAX_64 0x7fffffffffffffffL
#define LONG_MIN_64 (-0x7fffffffffffffffL - 1)
extern const unsigned char _ctype_[];
#define CT(c) (_ctype_ + 1)[c]
#define CT_UPPER 0x1
#define CT_ALPHA 0x3
#define CT_DIGIT 0x4
#define CT_SPACE 0x8

long _strtol_r(struct _reent *rptr, const char *nptr, char **endptr, int base)
{
    const char *s = nptr;
    unsigned long acc;
    int c;
    unsigned long cutoff;
    int neg = 0, any, cutlim;

    do {
        c = *s++;
    } while (CT(c) & CT_SPACE);
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = neg ? -(unsigned long)LONG_MIN_64 : LONG_MAX_64;
    cutlim = cutoff % (unsigned long)base;
    cutoff /= (unsigned long)base;
    acc = 0;
    any = 0;
    while (1) {
        if (CT(c) & CT_DIGIT)
            c -= '0';
        else if (CT(c) & CT_ALPHA)
            c -= (CT(c) & CT_UPPER) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
        c = *s++;
    }
    if (any < 0) {
        acc = neg ? LONG_MIN_64 : LONG_MAX_64;
        rptr->_errno = 34; /* ERANGE */
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *)(any ? s - 1 : nptr);
    return acc;
}

long strtol(const char *s, char **ptr, int base)
{
    return _strtol_r(_REENT, s, ptr, base);
}

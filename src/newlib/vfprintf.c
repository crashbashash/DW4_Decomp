#include "dw4/newlib_stdio.h"

struct lconv {
    char *decimal_point;
};
struct lconv *localeconv(void);
char *cvt(struct _reent *, double, int, int, char *, int *, int, int *);
int exponent(char *, int, int);
typedef unsigned int __uint32_t;
typedef int wchar_t;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
extern int __mb_cur_max;
int _mbtowc_r (struct _reent *, wchar_t *, const char *, size_t, int *);
char * _dtoa_r (struct _reent *, double, int, int, int *, int*, char**);
void * memchr (const void *, int, size_t);
size_t strlen (const char *);
int isnan (double);
int isinf (double);
union double_union
{
  double d;
  __uint32_t i[2];
};

int __sprint(FILE *fp, register struct __suio *uio)
{
        register int err;
        if (uio->uio_resid == 0) {
                uio->uio_iovcnt = 0;
                return (0);
        }
        err = __sfvwrite(fp, uio);
        uio->uio_resid = 0;
        uio->uio_iovcnt = 0;
        return (err);
}

int __sbprintf(register FILE *fp, const char *fmt, va_list ap)
{
        int ret;
        FILE fake;
        unsigned char buf[1024];
        fake._data = fp->_data;
        fake._flags = fp->_flags & ~__SNBF;
        fake._file = fp->_file;
        fake._cookie = fp->_cookie;
        fake._write = fp->_write;
        fake._bf._base = fake._p = buf;
        fake._bf._size = fake._w = sizeof(buf);
        fake._lbfsize = 0;
        ret = vfprintf(&fake, fmt, ap);
        if (ret >= 0 && fflush(&fake))
                ret = (-1);
        if (fake._flags & __SERR)
                fp->_flags |= __SERR;
        return (ret);
}

int
vfprintf(FILE * fp ,
        const char *fmt0 ,
        va_list ap)
{
  CHECK_INIT (fp);
  return _vfprintf_r (fp->_data, fp, fmt0, ap);
}

int
_vfprintf_r(struct _reent *data ,
        FILE * fp ,
        const char *fmt0 ,
        va_list ap)
{
        register char *fmt;
        register int ch;
        register int n, m;
        register char *cp;
        register struct __siov *iovp;
        register int flags;
        int ret;
        int width;
        int prec;
        char sign;
        wchar_t wc;
        char *decimal_point = localeconv()->decimal_point;
        char softsign;
        double _fpvalue;
        int expt;
        int expsize;
        int ndig;
        char expstr[7];
        u_long _uquad;
        enum { OCT, DEC, HEX } base;
        int dprec;
        int realsz;
        int size;
        char *xdigs;
        struct __suio uio;
        struct __siov iov[8];
        char buf[(308+39+1)];
        char ox[2];
        int state = 0;
        static const char blanks[16] =
         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
        static const char zeroes[16] =
         {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
        if (cantwrite (fp))
                return ((-1));
        if ((fp->_flags & (__SNBF|__SWR|__SRW)) == (__SNBF|__SWR) &&
            fp->_file >= 0)
                return (__sbprintf(fp, fmt0, ap));
        fmt = (char *)fmt0;
        uio.uio_iov = iovp = iov;
        uio.uio_resid = 0;
        uio.uio_iovcnt = 0;
        ret = 0;
        for (;;) {
                cp = fmt;
                while ((n = _mbtowc_r(_impure_ptr, &wc, fmt, __mb_cur_max, &state)) > 0) {
                        fmt += n;
                        if (wc == '%') {
                                fmt--;
                                break;
                        }
                }
                if ((m = fmt - cp) != 0) {
                        { iovp->iov_base = (cp); iovp->iov_len = (m); uio.uio_resid += (m); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                        ret += m;
                }
                if (n <= 0)
                        goto done;
                fmt++;
                flags = 0;
                dprec = 0;
                width = 0;
                prec = -1;
                sign = '\0';
rflag: ch = *fmt++;
reswitch: switch (ch) {
                case ' ':
                        if (!sign)
                                sign = ' ';
                        goto rflag;
                case '#':
                        flags |= 0x001;
                        goto rflag;
                case '*':
                        if ((width = __builtin_va_arg((ap), int)) >= 0)
                                goto rflag;
                        width = -width;
                case '-':
                        flags |= 0x004;
                        goto rflag;
                case '+':
                        sign = '+';
                        goto rflag;
                case '.':
                        if ((ch = *fmt++) == '*') {
                                n = __builtin_va_arg((ap), int);
                                prec = n < 0 ? -1 : n;
                                goto rflag;
                        }
                        n = 0;
                        while (((unsigned)((ch) - '0') <= 9)) {
                                n = 10 * n + ((ch) - '0');
                                ch = *fmt++;
                        }
                        prec = n < 0 ? -1 : n;
                        goto reswitch;
                case '0':
                        flags |= 0x080;
                        goto rflag;
                case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                        n = 0;
                        do {
                                n = 10 * n + ((ch) - '0');
                                ch = *fmt++;
                        } while (((unsigned)((ch) - '0') <= 9));
                        width = n;
                        goto reswitch;
                case 'L':
                        flags |= 0x008;
                        goto rflag;
                case 'h':
                        flags |= 0x040;
                        goto rflag;
                case 'l':
                        if (*fmt == 'l') {
                                fmt++;
                                flags |= 0x020;
                        } else {
                                flags |= 0x010;
                        }
                        goto rflag;
                case 'q':
                        flags |= 0x020;
                        goto rflag;
                case 'c':
                        *(cp = buf) = __builtin_va_arg((ap), int);
                        size = 1;
                        sign = '\0';
                        break;
                case 'D':
                        flags |= 0x010;
                case 'd':
                case 'i':
                        _uquad = (flags&0x010 ? __builtin_va_arg((ap), long) : flags&0x040 ? (long)(short)__builtin_va_arg((ap), int) : (long)__builtin_va_arg((ap), int));
                        if ((long) _uquad < 0)
                        {
                                _uquad = -_uquad;
                                sign = '-';
                        }
                        base = DEC;
                        goto number;
                case 'e':
                case 'E':
                case 'f':
                case 'g':
                case 'G':
                        if (prec == -1) {
                                prec = 6;
                        } else if ((ch == 'g' || ch == 'G') && prec == 0) {
                                prec = 1;
                        }
                        if (flags & 0x008) {
                                _fpvalue = (double) __builtin_va_arg((ap), long double);
                        } else {
                                _fpvalue = __builtin_va_arg((ap), double);
                        }
                        if (isinf(_fpvalue)) {
                                if (_fpvalue < 0)
                                        sign = '-';
                                cp = "Inf";
                                size = 3;
                                break;
                        }
                        if (isnan(_fpvalue)) {
                                cp = "NaN";
                                size = 3;
                                break;
                        }
                        flags |= 0x100;
                        cp = cvt(data, _fpvalue, prec, flags, &softsign,
                                &expt, ch, &ndig);
                        if (ch == 'g' || ch == 'G') {
                                if (expt <= -4 || expt > prec)
                                        ch = (ch == 'g') ? 'e' : 'E';
                                else
                                        ch = 'g';
                        }
                        if (ch <= 'e') {
                                --expt;
                                expsize = exponent(expstr, expt, ch);
                                size = expsize + ndig;
                                if (ndig > 1 || flags & 0x001)
                                        ++size;
                        } else if (ch == 'f') {
                                if (expt > 0) {
                                        size = expt;
                                        if (prec || flags & 0x001)
                                                size += prec + 1;
                                } else
                                        size = prec + 2;
                        } else if (expt >= ndig) {
                                size = expt;
                                if (flags & 0x001)
                                        ++size;
                        } else
                                size = ndig + (expt > 0 ?
                                        1 : 2 - expt);
                        if (softsign)
                                sign = '-';
                        break;
                case 'n':
                        if (flags & 0x010)
                                *__builtin_va_arg((ap), long *) = ret;
                        else if (flags & 0x040)
                                *__builtin_va_arg((ap), short *) = ret;
                        else
                                *__builtin_va_arg((ap), int *) = ret;
                        continue;
                case 'O':
                        flags |= 0x010;
                case 'o':
                        _uquad = (flags&0x010 ? __builtin_va_arg((ap), u_long) : flags&0x040 ? (u_long)(u_short)__builtin_va_arg((ap), int) : (u_long)__builtin_va_arg((ap), u_int));
                        base = OCT;
                        goto nosign;
                case 'p':
                        _uquad = (u_long)(unsigned long)__builtin_va_arg((ap), void *);
                        base = HEX;
                        xdigs = "0123456789abcdef";
                        flags |= 0x002;
                        ch = 'x';
                        goto nosign;
                case 's':
                        if ((cp = __builtin_va_arg((ap), char *)) == 0)
                                cp = "(null)";
                        if (prec >= 0) {
                                char *p = memchr(cp, 0, prec);
                                if (p != 0) {
                                        size = p - cp;
                                        if (size > prec)
                                                size = prec;
                                } else
                                        size = prec;
                        } else
                                size = strlen(cp);
                        sign = '\0';
                        break;
                case 'U':
                        flags |= 0x010;
                case 'u':
                        _uquad = (flags&0x010 ? __builtin_va_arg((ap), u_long) : flags&0x040 ? (u_long)(u_short)__builtin_va_arg((ap), int) : (u_long)__builtin_va_arg((ap), u_int));
                        base = DEC;
                        goto nosign;
                case 'X':
                        xdigs = "0123456789ABCDEF";
                        goto hex;
                case 'x':
                        xdigs = "0123456789abcdef";
hex: _uquad = (flags&0x010 ? __builtin_va_arg((ap), u_long) : flags&0x040 ? (u_long)(u_short)__builtin_va_arg((ap), int) : (u_long)__builtin_va_arg((ap), u_int));
                        base = HEX;
                        if (flags & 0x001 && _uquad != 0)
                                flags |= 0x002;
nosign: sign = '\0';
number: if ((dprec = prec) >= 0)
                                flags &= ~0x080;
                        cp = buf + (308+39+1);
                        if (_uquad != 0 || prec != 0) {
                                switch (base) {
                                case OCT:
                                        do {
                                                *--cp = ((_uquad & 7) + '0');
                                                _uquad >>= 3;
                                        } while (_uquad);
                                        if (flags & 0x001 && *cp != '0')
                                                *--cp = '0';
                                        break;
                                case DEC:
                                        while (_uquad >= 10) {
                                                *--cp = ((_uquad % 10) + '0');
                                                _uquad /= 10;
                                        }
                                        *--cp = ((_uquad) + '0');
                                        break;
                                case HEX:
                                        do {
                                                *--cp = xdigs[_uquad & 15];
                                                _uquad >>= 4;
                                        } while (_uquad);
                                        break;
                                default:
                                        cp = "bug in vfprintf: bad base";
                                        size = strlen(cp);
                                        goto skipsize;
                                }
                        }
                        size = buf + (308+39+1) - cp;
                skipsize:
                        break;
                default:
                        if (ch == '\0')
                                goto done;
                        cp = buf;
                        *cp = ch;
                        size = 1;
                        sign = '\0';
                        break;
                }
                realsz = dprec > size ? dprec : size;
                if (sign)
                        realsz++;
                else if (flags & 0x002)
                        realsz+= 2;
                if ((flags & (0x004|0x080)) == 0)
                        { if ((n = (width - realsz)) > 0) { while (n > 16) { { iovp->iov_base = (blanks); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (blanks); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
                if (sign) {
                        { iovp->iov_base = (&sign); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                } else if (flags & 0x002) {
                        ox[0] = '0';
                        ox[1] = ch;
                        { iovp->iov_base = (ox); iovp->iov_len = (2); uio.uio_resid += (2); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                }
                if ((flags & (0x004|0x080)) == 0x080)
                        { if ((n = (width - realsz)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
                { if ((n = (dprec - size)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
                if ((flags & 0x100) == 0) {
                        { iovp->iov_base = (cp); iovp->iov_len = (size); uio.uio_resid += (size); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                } else {
                        if (ch >= 'f') {
                                if (_fpvalue == 0) {
                                        { iovp->iov_base = ("0"); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                        if (expt < ndig || (flags & 0x001) != 0) {
                                                { iovp->iov_base = (decimal_point); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                                { if ((n = (ndig - 1)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
                                        }
                                } else if (expt <= 0) {
                                        { iovp->iov_base = ("0"); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                        if(expt || ndig) {
                                                { iovp->iov_base = (decimal_point); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                                { if ((n = (-expt)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
                                                { iovp->iov_base = (cp); iovp->iov_len = (ndig); uio.uio_resid += (ndig); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                        }
                                } else if (expt >= ndig) {
                                        { iovp->iov_base = (cp); iovp->iov_len = (ndig); uio.uio_resid += (ndig); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                        { if ((n = (expt - ndig)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
                                        if (flags & 0x001)
                                                { iovp->iov_base = ("."); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                } else {
                                        { iovp->iov_base = (cp); iovp->iov_len = (expt); uio.uio_resid += (expt); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                        cp += expt;
                                        { iovp->iov_base = ("."); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                        { iovp->iov_base = (cp); iovp->iov_len = (ndig-expt); uio.uio_resid += (ndig-expt); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                }
                        } else {
                                if (ndig > 1 || flags & 0x001) {
                                        ox[0] = *cp++;
                                        ox[1] = '.';
                                        { iovp->iov_base = (ox); iovp->iov_len = (2); uio.uio_resid += (2); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                       if (_fpvalue) {
                                                { iovp->iov_base = (cp); iovp->iov_len = (ndig-1); uio.uio_resid += (ndig-1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                        } else
                                                { if ((n = (ndig - 1)) > 0) { while (n > 16) { { iovp->iov_base = (zeroes); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (zeroes); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
                                } else
                                        { iovp->iov_base = (cp); iovp->iov_len = (1); uio.uio_resid += (1); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                                { iovp->iov_base = (expstr); iovp->iov_len = (expsize); uio.uio_resid += (expsize); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } };
                        }
                }
                if (flags & 0x004)
                        { if ((n = (width - realsz)) > 0) { while (n > 16) { { iovp->iov_base = (blanks); iovp->iov_len = (16); uio.uio_resid += (16); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; n -= 16; } { iovp->iov_base = (blanks); iovp->iov_len = (n); uio.uio_resid += (n); iovp++; if (++uio.uio_iovcnt >= 8) { if (__sprint(fp, &uio)) goto error; iovp = iov; } }; } };
                ret += width > realsz ? width : realsz;
                { if (uio.uio_resid && __sprint(fp, &uio)) goto error; uio.uio_iovcnt = 0; iovp = iov; };
        }
done:
        { if (uio.uio_resid && __sprint(fp, &uio)) goto error; uio.uio_iovcnt = 0; iovp = iov; };
error:
        return __sferror (fp) ? EOF : ret;
}

char * cvt(struct _reent *data, double value, int ndigits, int flags, char *sign, int *decpt, int ch, int *length)
{
        int mode, dsgn;
        char *digits, *bp, *rve;
        union double_union tmp;
        if (ch == 'f') {
                mode = 3;
        } else {
                if (ch == 'e' || ch == 'E') {
                        ndigits++;
                }
                mode = 2;
        }
        tmp.d = value;
        if ((tmp.i[1]) & ((__uint32_t)0x80000000L)) {
                value = -value;
                *sign = '-';
        } else
                *sign = '\000';
        digits = _dtoa_r(data, value, mode, ndigits, decpt, &dsgn, &rve);
        if ((ch != 'g' && ch != 'G') || flags & 0x001) {
                bp = digits + ndigits;
                if (ch == 'f') {
                        if (*digits == '0' && value)
                                *decpt = -ndigits + 1;
                        bp += *decpt;
                }
                if (value == 0)
                        rve = bp;
                while (rve < bp)
                        *rve++ = '0';
        }
        *length = rve - digits;
        return (digits);
}

int exponent(char *p0, int exp, int fmtch)
{
        register char *p, *t;
        char expbuf[308];
        p = p0;
        *p++ = fmtch;
        if (exp < 0) {
                exp = -exp;
                *p++ = '-';
        }
        else
                *p++ = '+';
        t = expbuf + 308;
        if (exp > 9) {
                do {
                        *--t = ((exp % 10) + '0');
                } while ((exp /= 10) > 9);
                *--t = ((exp) + '0');
                for (; t < expbuf + 308; *p++ = *t++);
        }
        else {
                *p++ = '0';
                *p++ = ((exp) + '0');
        }
        return (p - p0);
}

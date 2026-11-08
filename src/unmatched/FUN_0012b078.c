/* newlib _strtod_r(ptr, s00, se), preprocessed newlib 1.10.0 stdlib/strtod.c. */
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long _off_t;
typedef long _ssize_t;
typedef __uint32_t __ULong;
struct _glue
{
  struct _glue *_next;
  int _niobs;
  struct __sFILE *_iobs;
};
struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};
struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};
struct _atexit {
        struct _atexit *_next;
        int _ind;
        void (*_fns[32])(void);
};
struct __sbuf {
        unsigned char *_base;
        int _size;
};
typedef long _fpos_t;
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;
  void * _cookie;
  int (*_read) (void * _cookie, char *_buf, int _n);
  int (*_write) (void * _cookie, const char *_buf,
                                            int _n);
  _fpos_t (*_seek) (void * _cookie, _fpos_t _offset, int _whence);
  int (*_close) (void * _cookie);
  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;
  unsigned char _ubuf[3];
  unsigned char _nbuf[1];
  struct __sbuf _lb;
  int _blksize;
  int _offset;
  struct _reent *_data;
};
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;
};
struct _reent
{
  int _errno;
  struct __sFILE *_stdin, *_stdout, *_stderr;
  int _inc;
  char _emergency[25];
  int _current_category;
  const char *_current_locale;
  int __sdidinit;
  void (*__cleanup) (struct _reent *);
  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;
  int _cvtlen;
  char *_cvtbuf;
  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
        } _reent;
      struct
        {
          unsigned char * _nextf[30];
          unsigned int _nmalloc[30];
        } _unused;
    } _new;
  struct _atexit *_atexit;
  struct _atexit _atexit0;
  void (**(_sig_func))(int);
  struct _glue __sglue;
  struct __sFILE __sf[3];
};
extern struct _reent *D_004854a0;
void _reclaim_reent (struct _reent *);
typedef unsigned int size_t;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef unsigned int wint_t;
struct stat;
struct tms;
struct timeval;
struct timezone;
extern int _close_r (struct _reent *, int);
extern int _execve_r (struct _reent *, char *, char **, char **);
extern int _fcntl_r (struct _reent *, int, int, int);
extern int _fork_r (struct _reent *);
extern int _fstat_r (struct _reent *, int, struct stat *);
extern int _getpid_r (struct _reent *);
extern int _kill_r (struct _reent *, int, int);
extern int _link_r (struct _reent *, const char *, const char *);
extern _off_t _lseek_r (struct _reent *, int, _off_t, int);
extern int _open_r (struct _reent *, const char *, int, int);
extern _ssize_t _read_r (struct _reent *, int, void *, size_t);
extern void *_sbrk_r (struct _reent *, size_t);
extern int _stat_r (struct _reent *, const char *, struct stat *);
extern unsigned long _times_r (struct _reent *, struct tms *);
extern int _unlink_r (struct _reent *, const char *);
extern int _wait_r (struct _reent *, int *);
extern _ssize_t _write_r (struct _reent *, int, const void *, size_t);
extern int _gettimeofday_r (struct _reent *, struct timeval *tp, struct timezone *tzp);
void * memchr (const void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void * memcpy (void *, const void *, size_t);
void * memmove (void *, const void *, size_t);
void * memset (void *, int, size_t);
char *strcat (char *, const char *);
char *strchr (const char *, int);
int strcmp (const char *, const char *);
int strcoll (const char *, const char *);
char *strcpy (char *, const char *);
size_t strcspn (const char *, const char *);
char *strerror (int);
size_t strlen (const char *);
char *strncat (char *, const char *, size_t);
int strncmp (const char *, const char *, size_t);
char *strncpy (char *, const char *, size_t);
char *strpbrk (const char *, const char *);
char *strrchr (const char *, int);
size_t strspn (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *, const char *);
size_t strxfrm (char *, const char *, size_t);
char *strtok_r (char *, const char *, char **);
int bcmp (const char *, const char *, size_t);
void bcopy (const char *, char *, size_t);
void bzero (char *, size_t);
int ffs (int);
char *index (const char *, int);
void * memccpy (void *, const void *, int, size_t);
char *rindex (const char *, int);
int strcasecmp (const char *, const char *);
char *strdup (const char *);
char *_strdup_r (struct _reent *, const char *);
int strncasecmp (const char *, const char *, size_t);
char *strsep (char **, const char *);
char *strlwr (char *);
char *strupr (char *);
typedef union
{
  double value;
  struct
  {
    unsigned int fraction1:32;
    unsigned int fraction0:20;
    unsigned int exponent :11;
    unsigned int sign : 1;
  } number;
  struct
  {
    unsigned int function1:32;
    unsigned int function0:19;
    unsigned int quiet:1;
    unsigned int exponent: 11;
    unsigned int sign : 1;
  } nan;
  struct
  {
    unsigned long lsw;
    unsigned long msw;
  } parts;
  long aslong[2];
} __ieee_double_shape_type;
typedef union
{
  float value;
  struct
  {
    unsigned int fraction0: 7;
    unsigned int fraction1: 16;
    unsigned int exponent: 8;
    unsigned int sign : 1;
  } number;
  struct
  {
    unsigned int function1:16;
    unsigned int function0:6;
    unsigned int quiet:1;
    unsigned int exponent:8;
    unsigned int sign:1;
  } nan;
  long p1;
} __ieee_float_shape_type;
typedef int fp_rnd;
fp_rnd fpgetround (void);
fp_rnd fpsetround (fp_rnd);
typedef int fp_except;
fp_except fpgetmask (void);
fp_except fpsetmask (fp_except);
fp_except fpgetsticky (void);
fp_except fpsetsticky (fp_except);
typedef int fp_rdi;
fp_rdi fpgetroundtoi (void);
fp_rdi fpsetroundtoi (fp_rdi);
int isnan (double);
int isinf (double);
int finite (double);
int isnanf (float);
int isinff (float);
int finitef (float);
union __dmath
{
  __uint32_t i[2];
  double d;
};
extern const union __dmath D_004d3c80[];
extern double atan (double);
extern double cos (double);
extern double sin (double);
extern double tan (double);
extern double tanh (double);
extern double frexp (double, int *);
extern double modf (double, double *);
extern double ceil (double);
extern double fabs (double);
extern double floor (double);
extern double acos (double);
extern double asin (double);
extern double atan2 (double, double);
extern double cosh (double);
extern double sinh (double);
extern double exp (double);
extern double ldexp (double, int);
extern double log (double);
extern double log10 (double);
extern double pow (double, double);
extern double sqrt (double);
extern double fmod (double, double);
extern double infinity (void);
extern double nan (void);
extern int isnan (double);
extern int isinf (double);
extern int finite (double);
extern double copysign (double, double);
extern int ilogb (double);
extern double asinh (double);
extern double cbrt (double);
extern double nextafter (double, double);
extern double rint (double);
extern double scalbn (double, int);
extern double log1p (double);
extern double expm1 (double);
extern double acosh (double);
extern double atanh (double);
extern double remainder (double, double);
extern double gamma (double);
extern double gamma_r (double, int *);
extern double lgamma (double);
extern double lgamma_r (double, int *);
extern double erf (double);
extern double erfc (double);
extern double y0 (double);
extern double y1 (double);
extern double yn (int, double);
extern double j0 (double);
extern double j1 (double);
extern double jn (int, double);
extern double hypot (double, double);
extern double cabs();
extern double drem (double, double);
extern float atanf (float);
extern float cosf (float);
extern float sinf (float);
extern float tanf (float);
extern float tanhf (float);
extern float frexpf (float, int *);
extern float modff (float, float *);
extern float ceilf (float);
extern float fabsf (float);
extern float floorf (float);
extern float acosf (float);
extern float asinf (float);
extern float atan2f (float, float);
extern float coshf (float);
extern float sinhf (float);
extern float expf (float);
extern float ldexpf (float, int);
extern float logf (float);
extern float log10f (float);
extern float powf (float, float);
extern float sqrtf (float);
extern float fmodf (float, float);
extern float infinityf (void);
extern float nanf (void);
extern int isnanf (float);
extern int isinff (float);
extern int finitef (float);
extern float copysignf (float, float);
extern int ilogbf (float);
extern float asinhf (float);
extern float cbrtf (float);
extern float nextafterf (float, float);
extern float rintf (float);
extern float scalbnf (float, int);
extern float log1pf (float);
extern float expm1f (float);
extern float acoshf (float);
extern float atanhf (float);
extern float remainderf (float, float);
extern float gammaf (float);
extern float gammaf_r (float, int *);
extern float lgammaf (float);
extern float lgammaf_r (float, int *);
extern float erff (float);
extern float erfcf (float);
extern float y0f (float);
extern float y1f (float);
extern float ynf (int, float);
extern float j0f (float);
extern float j1f (float);
extern float jnf (int, float);
extern float hypotf (float, float);
extern float cabsf();
extern float dremf (float, float);
extern int *__signgam (void);
struct exception
{
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};
extern int matherr (struct exception *e);
enum __fdlibm_version
{
  __fdlibm_ieee = -1,
  __fdlibm_svid,
  __fdlibm_xopen,
  __fdlibm_posix
};
extern const enum __fdlibm_version __fdlib_version;
extern int *__errno (void);
extern const char * const _sys_errlist[];
extern int _sys_nerr;
union double_union
{
  double d;
  __uint32_t i[2];
};
typedef struct _Bigint _Bigint;
struct _reent ;
double FUN_00127ec8 (double x);
double FUN_00127f98 (_Bigint *a , int *e);
_Bigint * FUN_001273e0 (struct _reent *p, int k);
void FUN_00127488 (struct _reent *p, _Bigint *v);
_Bigint * FUN_001274b8 (struct _reent *p, _Bigint *, int, int);
_Bigint * FUN_001275c0 (struct _reent *, const char*, int, int, __ULong);
_Bigint * FUN_00127830 (struct _reent *,int);
_Bigint * FUN_00127868 (struct _reent *, _Bigint *, _Bigint *);
_Bigint * FUN_00127a78 (struct _reent *, _Bigint *, int k);
int FUN_001276f0 (__ULong);
int FUN_00127770 (__ULong *);
_Bigint * FUN_00128130 (struct _reent *p, double d, int *e, int *bits);
_Bigint * FUN_00127b78 (struct _reent *p, _Bigint *b, int k);
_Bigint * FUN_00127d38 (struct _reent *p, _Bigint *a, _Bigint *b);
int FUN_00127cd0 (_Bigint *a, _Bigint *b);
double FUN_001282b8 (_Bigint *a, _Bigint *b);
extern const double D_004d4028[];
extern const double D_004d4000[];
extern const double D_004d3f38[];
double FUN_00128388 (int);
double
FUN_0012b078(struct _reent *ptr ,
        const char *s00 ,
        char **se)
{
  int bb2, bb5, bbe, bd2, bd5, bbbits, bs2, c, dsign, e1, esign, i, j,
    k, nd, nd0, nf, nz, nz0, sign;
  long e;
  const char *s, *s0, *s1;
  double aadj, aadj1, adj;
  long L;
  unsigned long z;
  __ULong y;
  union double_union rv, rv0;
  _Bigint *bb, *bb1, *bd, *bd0, *bs, *delta;
  sign = nz0 = nz = 0;
  rv.d = 0.;
  for (s = s00;; s++)
    switch (*s)
      {
      case '-':
        sign = 1;
      case '+':
        if (*++s)
          goto break2;
      case 0:
        s = s00;
        goto ret;
      case '\t':
      case '\n':
      case '\v':
      case '\f':
      case '\r':
      case ' ':
        continue;
      default:
        goto break2;
      }
break2:
  if (*s == '0')
    {
      nz0 = 1;
      while (*++s == '0');
      if (!*s)
        goto ret;
    }
  s0 = s;
  y = z = 0;
  for (nd = nf = 0; (c = *s) >= '0' && c <= '9'; nd++, s++)
    if (nd < 9)
      y = 10 * y + c - '0';
    else if (nd < 16)
      z = 10 * z + c - '0';
  nd0 = nd;
  if (c == '.')
    {
      c = *++s;
      if (!nd)
        {
          for (; c == '0'; c = *++s)
            nz++;
          if (c > '0' && c <= '9')
            {
              s0 = s;
              nf += nz;
              nz = 0;
              goto have_dig;
            }
          goto dig_done;
        }
      for (; c >= '0' && c <= '9'; c = *++s)
        {
        have_dig:
          nz++;
          if (c -= '0')
            {
              nf += nz;
              for (i = 1; i < nz; i++)
                if (nd++ < 9)
                  y *= 10;
                else if (nd <= 15 + 1)
                  z *= 10;
              if (nd++ < 9)
                y = 10 * y + c;
              else if (nd <= 15 + 1)
                z = 10 * z + c;
              nz = 0;
            }
        }
    }
dig_done:
  e = 0;
  if (c == 'e' || c == 'E')
    {
      if (!nd && !nz && !nz0)
        {
          s = s00;
          goto ret;
        }
      s00 = s;
      esign = 0;
      switch (c = *++s)
        {
        case '-':
          esign = 1;
        case '+':
          c = *++s;
        }
      if (c >= '0' && c <= '9')
        {
          while (c == '0')
            c = *++s;
          if (c > '0' && c <= '9')
            {
              e = c - '0';
              s1 = s;
              while ((c = *++s) >= '0' && c <= '9')
                e = 10 * e + c - '0';
              if (s - s1 > 8)
                e = 9999999L;
              if (esign)
                e = -e;
            }
          else
            e = 0;
        }
      else
        s = s00;
    }
  if (!nd)
    {
      if (!nz && !nz0)
        s = s00;
      goto ret;
    }
  e1 = e -= nf;
  if (!nd0)
    nd0 = nd;
  k = nd < 15 + 1 ? nd : 15 + 1;
  rv.d = y;
  if (k > 9)
    rv.d = D_004d3f38[k - 9] * rv.d + z;
  bd0 = 0;
  if (nd <= 15
      && 0 == 1
    )
    {
      if (!e)
        goto ret;
      if (e > 0)
        {
          if (e <= 22)
            {
                           rv.d *= D_004d3f38[e];
              goto ret;
            }
          i = 15 - nd;
          if (e <= 22 + i)
            {
              e -= i;
              rv.d *= D_004d3f38[i];
                           rv.d *= D_004d3f38[e];
              goto ret;
            }
        }
      else if (e >= -22)
        {
                       rv.d /= D_004d3f38[-e];
          goto ret;
        }
    }
  e1 += nd - k;
  if (e1 > 0)
    {
      if ((i = e1 & 15) != 0)
        rv.d *= D_004d3f38[i];
      if (e1 &= ~15)
        {
          if (e1 > 308)
            {
            ovfl:
              ptr->_errno = 34;
              rv.d = (D_004d3c80[0].d);
              if (bd0)
                goto retfree;
              goto ret;
            }
          if (e1 >>= 4)
            {
              for (j = 0; e1 > 1; j++, e1 >>= 1)
                if (e1 & 1)
                  rv.d *= D_004d4000[j];
              (rv.i[1]) -= 53 * ((__uint32_t)0x100000L);
              rv.d *= D_004d4000[j];
              if ((z = (rv.i[1]) & ((__uint32_t)0x7ff00000L))
                  > ((__uint32_t)0x100000L) * (1024 + 1023 - 53))
                goto ovfl;
              if (z > ((__uint32_t)0x100000L) * (1024 + 1023 - 1 - 53))
                {
                  (rv.i[1]) = (((__uint32_t)0xfffffL) | ((__uint32_t)0x100000L)*(1024+1023-1));
                  (rv.i[0]) = ((__uint32_t)0xffffffffL);
                }
              else
                (rv.i[1]) += 53 * ((__uint32_t)0x100000L);
            }
        }
    }
  else if (e1 < 0)
    {
      e1 = -e1;
      if ((i = e1 & 15) != 0)
        rv.d /= D_004d3f38[i];
      if (e1 &= ~15)
        {
          e1 >>= 4;
          if (e1 >= 1 << 5)
            goto undfl;
          for (j = 0; e1 > 1; j++, e1 >>= 1)
            if (e1 & 1)
              rv.d *= D_004d4028[j];
          rv0.d = rv.d;
          rv.d *= D_004d4028[j];
          if (!rv.d)
            {
              rv.d = 2. * rv0.d;
              rv.d *= D_004d4028[j];
              if (!rv.d)
                {
                undfl:
                  rv.d = 0.;
                  ptr->_errno = 34;
                  if (bd0)
                    goto retfree;
                  goto ret;
                }
              (rv.i[1]) = 0;
              (rv.i[0]) = 1;
            }
        }
    }
  bd0 = FUN_001275c0 (ptr, s0, nd0, nd, y);
  for (;;)
    {
      bd = FUN_001273e0 (ptr, bd0->_k);
      memcpy((char *)&bd->_sign, (char *)&bd0->_sign, bd0->_wds*sizeof(__int32_t) + 2*sizeof(int));
      bb = FUN_00128130 (ptr, rv.d, &bbe, &bbbits);
      bs = FUN_00127830 (ptr, 1);
      if (e >= 0)
        {
          bb2 = bb5 = 0;
          bd2 = bd5 = e;
        }
      else
        {
          bb2 = bb5 = -e;
          bd2 = bd5 = 0;
        }
      if (bbe >= 0)
        bb2 += bbe;
      else
        bd2 -= bbe;
      bs2 = bb2;
      i = bbe + bbbits - 1;
      if (i < (-1022))
        j = bbe + (53 - (-1022));
      else
        j = 53 + 1 - bbbits;
      bb2 += j;
      bd2 += j;
      i = bb2 < bd2 ? bb2 : bd2;
      if (i > bs2)
        i = bs2;
      if (i > 0)
        {
          bb2 -= i;
          bd2 -= i;
          bs2 -= i;
        }
      if (bb5 > 0)
        {
          bs = FUN_00127a78 (ptr, bs, bb5);
          bb1 = FUN_00127868 (ptr, bs, bb);
          FUN_00127488 (ptr, bb);
          bb = bb1;
        }
      if (bb2 > 0)
        bb = FUN_00127b78 (ptr, bb, bb2);
      if (bd5 > 0)
        bd = FUN_00127a78 (ptr, bd, bd5);
      if (bd2 > 0)
        bd = FUN_00127b78 (ptr, bd, bd2);
      if (bs2 > 0)
        bs = FUN_00127b78 (ptr, bs, bs2);
      delta = FUN_00127d38 (ptr, bb, bd);
      dsign = delta->_sign;
      delta->_sign = 0;
      i = FUN_00127cd0 (delta, bs);
      if (i < 0)
        {
          if (dsign || (rv.i[0]) || (rv.i[1]) & ((__uint32_t)0xfffffL))
            break;
          delta = FUN_00127b78 (ptr, delta, 1);
          if (FUN_00127cd0 (delta, bs) > 0)
            goto drop_down;
          break;
        }
      if (i == 0)
        {
          if (dsign)
            {
              if (((rv.i[1]) & ((__uint32_t)0xfffffL)) == ((__uint32_t)0xfffffL)
                  && (rv.i[0]) == 0xffffffff)
                {
                  (rv.i[1]) = ((rv.i[1]) & ((__uint32_t)0x7ff00000L))
                    + ((__uint32_t)0x100000L)
                    ;
                  (rv.i[0]) = 0;
                  break;
                }
            }
          else if (!((rv.i[1]) & ((__uint32_t)0xfffffL)) && !(rv.i[0]))
            {
            drop_down:
              L = ((rv.i[1]) & ((__uint32_t)0x7ff00000L)) - ((__uint32_t)0x100000L);
              (rv.i[1]) = L | ((__uint32_t)0xfffffL);
              (rv.i[0]) = 0xffffffff;
              break;
            }
          if (!((rv.i[0]) & 1))
            break;
          if (dsign)
            rv.d += FUN_00127ec8 (rv.d);
          else
            {
              rv.d -= FUN_00127ec8 (rv.d);
              if (!rv.d)
                goto undfl;
            }
          break;
        }
      if ((aadj = FUN_001282b8 (delta, bs)) <= 2.)
        {
          if (dsign)
            aadj = aadj1 = 1.;
          else if ((rv.i[0]) || (rv.i[1]) & ((__uint32_t)0xfffffL))
            {
              if ((rv.i[0]) == 1 && !(rv.i[1]))
                goto undfl;
              aadj = 1.;
              aadj1 = -1.;
            }
          else
            {
              if (aadj < 2. / 2)
                aadj = 1. / 2;
              else
                aadj *= 0.5;
              aadj1 = -aadj;
            }
        }
      else
        {
          aadj *= 0.5;
          aadj1 = dsign ? aadj : -aadj;
          if (0 == 0)
            aadj1 += 0.5;
        }
      y = (rv.i[1]) & ((__uint32_t)0x7ff00000L);
      if (y == ((__uint32_t)0x100000L) * (1024 + 1023 - 1))
        {
          rv0.d = rv.d;
          (rv.i[1]) -= 53 * ((__uint32_t)0x100000L);
          adj = aadj1 * FUN_00127ec8 (rv.d);
          rv.d += adj;
          if (((rv.i[1]) & ((__uint32_t)0x7ff00000L)) >=
              ((__uint32_t)0x100000L) * (1024 + 1023 - 53))
            {
              if ((rv0.i[1]) == (((__uint32_t)0xfffffL) | ((__uint32_t)0x100000L)*(1024+1023-1)) && (rv0.i[0]) == ((__uint32_t)0xffffffffL))
                goto ovfl;
              (rv.i[1]) = (((__uint32_t)0xfffffL) | ((__uint32_t)0x100000L)*(1024+1023-1));
              (rv.i[0]) = ((__uint32_t)0xffffffffL);
              goto cont;
            }
          else
            (rv.i[1]) += 53 * ((__uint32_t)0x100000L);
        }
      else
        {
          if (y <= (53 - 1) * ((__uint32_t)0x100000L) && aadj >= 1.)
            {
              aadj1 = (double) (int) (aadj + 0.5);
              if (!dsign)
                aadj1 = -aadj1;
            }
          adj = aadj1 * FUN_00127ec8 (rv.d);
          rv.d += adj;
        }
      z = (rv.i[1]) & ((__uint32_t)0x7ff00000L);
      if (y == z)
        {
          L = aadj;
          aadj -= L;
          if (dsign || (rv.i[0]) || (rv.i[1]) & ((__uint32_t)0xfffffL))
            {
              if (aadj < .4999999 || aadj > .5000001)
                break;
            }
          else if (aadj < .4999999 / 2)
            break;
        }
    cont:
      FUN_00127488 (ptr, bb);
      FUN_00127488 (ptr, bd);
      FUN_00127488 (ptr, bs);
      FUN_00127488 (ptr, delta);
    }
retfree:
  FUN_00127488 (ptr, bb);
  FUN_00127488 (ptr, bd);
  FUN_00127488 (ptr, bs);
  FUN_00127488 (ptr, bd0);
  FUN_00127488 (ptr, delta);
ret:
  if (se)
    *se = (char *) s;
  return sign ? -rv.d : rv.d;
}

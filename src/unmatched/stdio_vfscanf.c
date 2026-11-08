/* newlib stdio/vfscanf.c (1.9.0, adjusted toward Sony's snapshot) */
extern const short D_004d4550[17];
extern const char D_004d4578[];
typedef int __int32_t;
typedef unsigned int __uint32_t;
int isalnum (int __c);
int isalpha (int __c);
int iscntrl (int __c);
int isdigit (int __c);
int isgraph (int __c);
int islower (int __c);
int isprint (int __c);
int ispunct (int __c);
int isspace (int __c);
int isupper (int __c);
int isxdigit (int __c);
int tolower (int __c);
int toupper (int __c);
int isascii (int __c);
int toascii (int __c);
int _tolower (int __c);
int _toupper (int __c);
extern const char D_004d3d10[];
typedef unsigned int size_t;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef unsigned int wint_t;
typedef unsigned int size_t;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef unsigned int wint_t;
typedef __builtin_va_list va_list;
typedef __builtin_va_list __gnuc_va_list;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long clock_t;
typedef long time_t;
struct timespec {
  time_t tv_sec;
  long tv_nsec;
};
struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
};
typedef long daddr_t;
typedef char * caddr_t;
typedef unsigned short ino_t;
typedef short dev_t;
typedef long off_t;
typedef unsigned short uid_t;
typedef unsigned short gid_t;
typedef int pid_t;
typedef long key_t;
typedef long ssize_t;
typedef unsigned int mode_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned short nlink_t;
typedef long fd_mask;
typedef struct _types_fd_set {
        fd_mask fds_bits[(((64)+(((sizeof (fd_mask) * 8))-1))/((sizeof (fd_mask) * 8)))];
} _types_fd_set;
struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};
clock_t clock (void);
double difftime (time_t _time2, time_t _time1);
time_t mktime (struct tm *_timeptr);
time_t time (time_t *_timer);
char *asctime (const struct tm *_tblock);
char *ctime (const time_t *_time);
struct tm *gmtime (const time_t *_timer);
struct tm *localtime (const time_t *_timer);
size_t strftime (char *_s, size_t _maxsize, const char *_fmt, const struct tm *_t);
char *asctime_r (const struct tm *, char *);
char *ctime_r (const time_t *, char *);
struct tm *gmtime_r (const time_t *, struct tm *);
struct tm *localtime_r (const time_t *, struct tm *);
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
  int (*_write) (void * _cookie, const char *_buf, int _n);
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
          struct tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
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
typedef _fpos_t fpos_t;
typedef struct __sFILE FILE;
int remove (const char *);
int rename (const char *, const char *);
char * tempnam (const char *, const char *);
FILE * tmpfile (void);
char * tmpnam (char *);
int fclose (FILE *);
int FUN_00124e10 (FILE *);
FILE * freopen (const char *, const char *, FILE *);
void setbuf (FILE *, char *);
int setvbuf (FILE *, char *, int, size_t);
int fprintf (FILE *, const char *, ...);
int fscanf (FILE *, const char *, ...);
int printf (const char *, ...);
int scanf (const char *, ...);
int sscanf (const char *, const char *, ...);
int vfprintf (FILE *, const char *, __gnuc_va_list);
int vprintf (const char *, __gnuc_va_list);
int vsprintf (char *, const char *, __gnuc_va_list);
int vsnprintf (char *, size_t, const char *, __gnuc_va_list);
int fgetc (FILE *);
char * fgets (char *, int, FILE *);
int fputc (int, FILE *);
int fputs (const char *, FILE *);
int getc (FILE *);
int getchar (void);
char * gets (char *);
int putc (int, FILE *);
int putchar (int);
int puts (const char *);
int FUN_0012c5d0 (int, FILE *);
size_t FUN_001252c8 (void *, size_t _size, size_t _n, FILE *);
size_t fwrite (const void * , size_t _size, size_t _n, FILE *);
int fgetpos (FILE *, fpos_t *);
int fseek (FILE *, long, int);
int fsetpos (FILE *, const fpos_t *);
long ftell ( FILE *);
void rewind (FILE *);
void clearerr (FILE *);
int feof (FILE *);
int ferror (FILE *);
void perror (const char *);
FILE * fopen (const char *_name, const char *_type);
int sprintf (char *, const char *, ...);
int snprintf (char *, size_t, const char *, ...);
int vfiprintf (FILE *, const char *, __gnuc_va_list);
int iprintf (const char *, ...);
int fiprintf (FILE *, const char *, ...);
int siprintf (char *, const char *, ...);
FILE * fdopen (int, const char *);
int fileno (FILE *);
int getw (FILE *);
int pclose (FILE *);
FILE * popen (const char *, const char *);
int putw (int, FILE *);
void setbuffer (FILE *, char *, int);
int setlinebuf (FILE *);
FILE * _fdopen_r (struct _reent *, int, const char *);
FILE * _fopen_r (struct _reent *, const char *, const char *);
int _getchar_r (struct _reent *);
char * _gets_r (struct _reent *, char *);
int _iprintf_r (struct _reent *, const char *, ...);
int _mkstemp_r (struct _reent *, char *);
char * _mktemp_r (struct _reent *, char *);
void _perror_r (struct _reent *, const char *);
int _printf_r (struct _reent *, const char *, ...);
int _putchar_r (struct _reent *, int);
int _puts_r (struct _reent *, const char *);
int _remove_r (struct _reent *, const char *);
int _rename_r (struct _reent *,
                           const char *_old, const char *_new);
int _scanf_r (struct _reent *, const char *, ...);
int _sprintf_r (struct _reent *, char *, const char *, ...);
int _snprintf_r (struct _reent *, char *, size_t, const char *, ...);
char * _tempnam_r (struct _reent *, const char *, const char *);
FILE * _tmpfile_r (struct _reent *);
char * _tmpnam_r (struct _reent *, char *);
int _vfprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list);
int _vprintf_r (struct _reent *, const char *, __gnuc_va_list);
int _vsprintf_r (struct _reent *, char *, const char *, __gnuc_va_list);
int _vsnprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list);
int __srget (FILE *);
int __swbuf (int, FILE *);
FILE *funopen (const void * _cookie,
                int (*readfn)(void * _cookie, char *_buf, int _n),
                int (*writefn)(void * _cookie, const char *_buf, int _n),
                fpos_t (*seekfn)(void * _cookie, fpos_t _off, int _whence),
                int (*closefn)(void * _cookie));
typedef struct
{
  int quot;
  int rem;
} div_t;
typedef struct
{
  long quot;
  long rem;
} ldiv_t;
extern int __mb_cur_max;
void abort (void) __attribute__ ((noreturn));
int abs (int);
int atexit (void (*__func)(void));
double FUN_001236d0 (const char *__nptr);
float atoff (const char *__nptr);
int atoi (const char *__nptr);
long FUN_00123710 (const char *__nptr);
void * bsearch (const void * __key,
                       const void * __base,
                       size_t __nmemb,
                       size_t __size,
                       int (* _compar) (const void *, const void *));
void * calloc (size_t __nmemb, size_t __size);
div_t div (int __numer, int __denom);
void exit (int __status) __attribute__ ((noreturn));
void free (void *);
char * getenv (const char *__string);
char * _getenv_r (struct _reent *, const char *__string);
char * _findenv (const char *, int *);
char * _findenv_r (struct _reent *, const char *, int *);
long labs (long);
ldiv_t ldiv (long __numer, long __denom);
void * malloc (size_t __size);
int mblen (const char *, size_t);
int _mblen_r (struct _reent *, const char *, size_t, int *);
int mbtowc (wchar_t *, const char *, size_t);
int _mbtowc_r (struct _reent *, wchar_t *, const char *, size_t, int *);
int wctomb (char *, wchar_t);
int _wctomb_r (struct _reent *, char *, wchar_t, int *);
size_t mbstowcs (wchar_t *, const char *, size_t);
size_t _mbstowcs_r (struct _reent *, wchar_t *, const char *, size_t, int *);
size_t wcstombs (char *, const wchar_t *, size_t);
size_t _wcstombs_r (struct _reent *, char *, const wchar_t *, size_t, int *);
int mkstemp (char *);
char * mktemp (char *);
void qsort (void * __base, size_t __nmemb, size_t __size, int(*_compar)(const void *, const void *));
int rand (void);
void * realloc (void * __r, size_t __size);
void srand (unsigned __seed);
double strtod (const char *__n, char **_end_PTR);
float strtodf (const char *__n, char **_end_PTR);
long FUN_0012c218 (const char *__n, char **_end_PTR, int __base);
unsigned long FUN_0012c478 (const char *_n_PTR, char **_end_PTR, int __base);
unsigned long _strtoul_r (struct _reent *,const char *_n_PTR, char **_end_PTR, int __base);
int system (const char *__string);
int putenv (const char *__string);
int _putenv_r (struct _reent *, const char *__string);
int setenv (const char *__string, const char *__value, int __overwrite);
int _setenv_r (struct _reent *, const char *__string, const char *__value, int __overwrite);
char * gcvt (double,int,char *);
char * gcvtf (float,int,char *);
char * fcvt (double,int,int *,int *);
char * fcvtf (float,int,int *,int *);
char * ecvt (double,int,int *,int *);
char * ecvtbuf (double, int, int*, int*, char *);
char * fcvtbuf (double, int, int*, int*, char *);
char * ecvtf (float,int,int *,int *);
char * dtoa (double, int, int, int *, int*, char**);
int rand_r (unsigned *__seed);
void cfree (void *);
char * _dtoa_r (struct _reent *, double, int, int, int *, int*, char**);
void * FUN_00126600 (struct _reent *, size_t);
void * _calloc_r (struct _reent *, size_t, size_t);
void FUN_001253e8 (struct _reent *, void *);
void * FUN_001290d0 (struct _reent *, void *, size_t);
void _mstats_r (struct _reent *, char *);
int _system_r (struct _reent *, const char *);
void __eprintf (const char *, const char *, unsigned int, const char *);
typedef __builtin_va_list va_list;
typedef __builtin_va_list __gnuc_va_list;
char * _gcvt (struct _reent *, double , int , char *, char, int);
           char *FUN_0012fbe0 ();
int
FUN_0012ef50 (fp, fmt0, ap)
     register FILE *fp;
     char const *fmt0;
     va_list ap;
{
  register char *fmt = (char *) fmt0;
  register int c;
  register size_t width;
  register char *p;
  register int n;
  register int flags;
  register char *p0;
  int nassigned;
  int nread;
  int base = 0;
  int nbytes = 1;
  wchar_t wc;
  unsigned long (*ccfn) () = 0;
  char ccltab[256];
  char buf[(308+39+3)];
  char *lptr;
  short *sp;
  int *ip;
  float *flp;
  long double *ldp;
  double *dp;
  long *lp;
  nassigned = 0;
  nread = 0;
  for (;;)
    {
      wc = *fmt;
      fmt += nbytes;
      if (wc == 0)
        return nassigned;
      if (nbytes == 1 && ((D_004d3d10+1)[(unsigned)(wc)]&010))
        {
          for (;;)
            {
              if ((fp->_r <= 0 && FUN_001296a8(fp)))
                return nassigned;
              if (!((D_004d3d10+1)[(unsigned)(*fp->_p)]&010))
                break;
              nread++, fp->_r--, fp->_p++;
            }
          continue;
        }
      if (wc != '%')
        goto literal;
      width = 0;
      flags = 0;
    again:
      c = *fmt++;
      switch (c)
        {
        case '%':
        literal:
          lptr = fmt - nbytes;
          for (n = 0; n < nbytes; ++n)
            {
              if ((fp->_r <= 0 && FUN_001296a8(fp)))
                goto input_failure;
              if (*fp->_p != *lptr)
                goto match_failure;
              fp->_r--, fp->_p++;
              nread++;
              ++lptr;
            }
          continue;
        case '*':
          flags |= 0x08;
          goto again;
        case 'l':
          flags |= 0x01;
          goto again;
        case 'L':
          flags |= 0x02;
          goto again;
        case 'h':
          flags |= 0x04;
          goto again;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          width = width * 10 + c - '0';
          goto again;
        case 'D':
          flags |= 0x01;
        case 'd':
          c = 3;
          ccfn = (unsigned long (*)())FUN_0012c218;
          base = 10;
          break;
        case 'i':
          c = 3;
          ccfn = (unsigned long (*)())FUN_0012c218;
          base = 0;
          break;
        case 'O':
          flags |= 0x01;
        case 'o':
          c = 3;
          ccfn = FUN_0012c478;
          base = 8;
          break;
        case 'u':
          c = 3;
          ccfn = FUN_0012c478;
          base = 10;
          break;
        case 'X':
        case 'x':
          flags |= 0x100;
          c = 3;
          ccfn = FUN_0012c478;
          base = 16;
          break;
        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
          c = 4;
          break;
        case 's':
          c = 2;
          break;
        case '[':
          fmt = FUN_0012fbe0 (ccltab, fmt);
          flags |= 0x20;
          c = 1;
          break;
        case 'c':
          flags |= 0x20;
          c = 0;
          break;
        case 'p':
          flags |= 0x10 | 0x100;
          c = 3;
          ccfn = FUN_0012c478;
          base = 16;
          break;
        case 'n':
          if (flags & 0x08)
            continue;
          if (flags & 0x04)
            {
              sp = __builtin_va_arg((ap), short *);
              *sp = nread;
            }
          else if (flags & 0x01)
            {
              lp = __builtin_va_arg((ap), long *);
              *lp = nread;
            }
          else
            {
              ip = __builtin_va_arg((ap), int *);
              *ip = nread;
            }
          continue;
        case '\0':
          return (-1);
        default:
          if (((D_004d3d10+1)[(unsigned)(c)]&01))
            flags |= 0x01;
          c = 3;
          ccfn = (unsigned long (*)())FUN_0012c218;
          base = 10;
          break;
        }
      if ((fp->_r <= 0 && FUN_001296a8(fp)))
        goto input_failure;
      if ((flags & 0x20) == 0)
        {
          while (((D_004d3d10+1)[(unsigned)(*fp->_p)]&010))
            {
              nread++;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (FUN_001296a8 (fp))
                goto input_failure;
            }
        }
      switch (c)
        {
        case 0:
          if (width == 0)
            width = 1;
          if (flags & 0x08)
            {
              size_t sum = 0;
              for (;;)
                {
                  if ((n = fp->_r) < width)
                    {
                      sum += n;
                      width -= n;
                      fp->_p += n;
                      if (FUN_001296a8 (fp))
                        {
                          if (sum == 0)
                            goto input_failure;
                          break;
                        }
                    }
                  else
                    {
                      sum += width;
                      fp->_r -= width;
                      fp->_p += width;
                      break;
                    }
                }
              nread += sum;
            }
          else
            {
              size_t r = FUN_001252c8 ((void *) __builtin_va_arg((ap), char *), 1, width, fp);
              if (r == 0)
                goto input_failure;
              nread += r;
              nassigned++;
            }
          break;
        case 1:
          if (width == 0)
            width = ~0;
          if (flags & 0x08)
            {
              n = 0;
              while (ccltab[*fp->_p])
                {
                  n++, fp->_r--, fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && FUN_001296a8(fp)))
                    {
                      if (n == 0)
                        goto input_failure;
                      break;
                    }
                }
              if (n == 0)
                goto match_failure;
            }
          else
            {
              p0 = p = __builtin_va_arg((ap), char *);
              while (ccltab[*fp->_p])
                {
                  fp->_r--;
                  *p++ = *fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && FUN_001296a8(fp)))
                    {
                      if (p == p0)
                        goto input_failure;
                      break;
                    }
                }
              n = p - p0;
              if (n == 0)
                goto match_failure;
              *p = 0;
              nassigned++;
            }
          nread += n;
          break;
        case 2:
          if (width == 0)
            width = ~0;
          if (flags & 0x08)
            {
              n = 0;
              while (!((D_004d3d10+1)[(unsigned)(*fp->_p)]&010))
                {
                  n++, fp->_r--, fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && FUN_001296a8(fp)))
                    break;
                }
              nread += n;
            }
          else
            {
              p0 = p = __builtin_va_arg((ap), char *);
              while (!((D_004d3d10+1)[(unsigned)(*fp->_p)]&010))
                {
                  fp->_r--;
                  *p++ = *fp->_p++;
                  if (--width == 0)
                    break;
                  if ((fp->_r <= 0 && FUN_001296a8(fp)))
                    break;
                }
              *p = 0;
              nread += p - p0;
              nassigned++;
            }
          continue;
        case 3:
          if (--width > sizeof (buf) - 2)
            width = sizeof (buf) - 2;
          width++;
          flags |= 0x40 | 0x80 | 0x200;
          for (p = buf; width; width--)
            {
              c = *fp->_p;
              switch (c)
                {
                case '0':
                  if (base == 0)
                    {
                      base = 8;
                      flags |= 0x100;
                    }
                  if (flags & 0x200)
                    flags &= ~(0x40 | 0x200 | 0x80);
                  else
                    flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                  base = D_004d4550[base];
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '8':
                case '9':
                  base = D_004d4550[base];
                  if (base <= 8)
                    break;
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                  if (base <= 10)
                    break;
                  flags &= ~(0x40 | 0x100 | 0x80);
                  goto ok;
                case '+':
                case '-':
                  if (flags & 0x40)
                    {
                      flags &= ~0x40;
                      goto ok;
                    }
                  break;
                case 'x':
                case 'X':
                  if (flags & 0x100 && p == buf + 1)
                    {
                      base = 16;
                      flags &= ~0x100;
                      goto ok;
                    }
                  break;
                }
              break;
            ok:
              *p++ = c;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (FUN_001296a8 (fp))
                break;
            }
          if (flags & 0x80)
            {
              if (p > buf)
                (void) FUN_0012c5d0 (*(char *)-- p, fp);
              goto match_failure;
            }
          c = ((char *) p)[-1];
          if (c == 'x' || c == 'X')
            {
              --p;
                         FUN_0012c5d0 (c, fp);
            }
          if ((flags & 0x08) == 0)
            {
              unsigned long res;
              *p = 0;
              res = (*ccfn) (buf, (char **) 0, base);
              if (flags & 0x10)
                *(__builtin_va_arg((ap), void * *)) = (void *) (unsigned long) res;
              else if (flags & 0x04)
                {
                  sp = __builtin_va_arg((ap), short *);
                  *sp = res;
                }
              else if (flags & 0x01)
                {
                  lp = __builtin_va_arg((ap), long *);
                  *lp = res;
                }
              else
                {
                  ip = __builtin_va_arg((ap), int *);
                  *ip = res;
                }
              nassigned++;
            }
          nread += p - buf;
          break;
        case 4:
        {
          long leading_zeroes;
          long zeroes, exp_adjust;
          char *exp_start;
          if (--width > sizeof (buf) - 2)
            width = sizeof (buf) - 2;
          width++;
          flags |= 0x40 | 0x80 | 0x100 | 0x200;
          zeroes = 0;
          exp_adjust = 0;
          for (p = buf; width; )
            {
              c = *fp->_p;
              switch (c)
                {
                case '0':
                  if (flags & 0x80)
                    {
                      flags &= ~0x40;
                      zeroes++;
                      goto fskip;
                    }
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                  flags &= ~(0x40 | 0x80);
                  goto fok;
                case '+':
                case '-':
                  if (flags & 0x40)
                    {
                      flags &= ~0x40;
                      goto fok;
                    }
                  break;
                case '.':
                  if (flags & 0x100)
                    {
                      flags &= ~(0x40 | 0x100);
                      leading_zeroes = zeroes;
                      goto fok;
                    }
                  break;
                case 'e':
                case 'E':
                  if ((flags & (0x80 | 0x200)) == 0x200
                      || ((flags & 0x200) && zeroes))
                    {
                      if (! (flags & 0x100))
                        {
                          exp_adjust = zeroes - leading_zeroes;
                          exp_start = p;
                        }
                      flags =
                        (flags & ~(0x200 | 0x100)) |
                        0x40 | 0x80;
                      zeroes = 0;
                      goto fok;
                    }
                  break;
                }
              break;
            fok:
              *p++ = c;
              width--;
            fskip:
              ++nread;
              if (--fp->_r > 0)
                fp->_p++;
              else
              if (FUN_001296a8 (fp))
                break;
            }
          if (zeroes)
            flags &= ~0x80;
          if (flags & 0x80)
            {
              if (flags & 0x200)
                {
                  while (p > buf)
                    {
                      FUN_0012c5d0 (*(char *)-- p, fp);
                    }
                  goto match_failure;
                }
              c = *(char *)-- p;
              --nread;
              if (c != 'e' && c != 'E')
                {
                  (void) FUN_0012c5d0 (c, fp);
                  c = *(char *)-- p;
                  --nread;
                }
              (void) FUN_0012c5d0 (c, fp);
            }
          if ((flags & 0x08) == 0)
            {
              double res;
              long new_exp;
              *p = 0;
              if ((flags & (0x100 | 0x200)) == 0x200)
                {
                  exp_adjust = zeroes - leading_zeroes;
                  new_exp = -exp_adjust;
                  exp_start = p;
                }
              else if (exp_adjust)
                new_exp = FUN_00123710 (exp_start + 1) - exp_adjust;
              if (exp_adjust)
                {
                  if (exp_start >= buf + sizeof (buf) - ((8 * sizeof (long) - 1) * 4 / 13 + 2))
                    exp_start = buf + sizeof (buf) - ((8 * sizeof (long) - 1) * 4 / 13 + 2) - 1;
                 sprintf (exp_start, D_004d4578, new_exp);
                }
              res = FUN_001236d0 (buf);
              if (flags & 0x01)
                {
                  dp = __builtin_va_arg((ap), double *);
                  *dp = res;
                }
              else if (flags & 0x02)
                {
                  ldp = __builtin_va_arg((ap), long double *);
                  *ldp = res;
                }
              else
                {
                  flp = __builtin_va_arg((ap), float *);
                  *flp = res;
                }
              nassigned++;
            }
          break;
        }
        }
    }
input_failure:
  return nassigned ? nassigned : -1;
match_failure:
  return nassigned;
}
char *
FUN_0012fbe0 (tab, fmt)
     register char *tab;
     register char *fmt;
{
  register int c, n, v;
  c = *fmt++;
  if (c == '^')
    {
      v = 1;
      c = *fmt++;
    }
  else
    v = 0;
  for (n = 0; n < 256; n++)
    tab[n] = v;
  if (c == 0)
    return fmt - 1;
  v = 1 - v;
  for (;;)
    {
      tab[c] = v;
    doswitch:
      n = *fmt++;
      switch (n)
        {
        case 0:
          return fmt - 1;
        case '-':
          n = *fmt;
          if (n == ']' || n < c)
            {
              c = '-';
              break;
            }
          fmt++;
          do
            {
              tab[++c] = v;
            }
          while (c < n);
          goto doswitch;
          break;
        case ']':
          return fmt;
        default:
          c = n;
          break;
        }
    }
}

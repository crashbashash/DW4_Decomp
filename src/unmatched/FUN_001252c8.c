typedef unsigned int size_t;
typedef long _fpos_t;
#define NULL 0
#define EOF (-1)
struct __sbuf {
    unsigned char *_base;
    int _size;
};
typedef struct __sFILE {
    unsigned char *_p;
    int _r;
    int _w;
    short _flags;
    short _file;
    struct __sbuf _bf;
    int _lbfsize;
    void *_cookie;
    int (*_read)(void *_cookie, char *_buf, int _n);
    int (*_write)(void *_cookie, const char *_buf, int _n);
    _fpos_t (*_seek)(void *_cookie, _fpos_t _offset, int _whence);
    int (*_close)(void *_cookie);
    struct __sbuf _ub;
    unsigned char *_up;
    int _ur;
    unsigned char _ubuf[3];
    unsigned char _nbuf[1];
    struct __sbuf _lb;
    int _blksize;
    int _offset;
    struct _reent *_data;
} FILE;
struct _glue {
    struct _glue *_next;
    int _niobs;
    struct __sFILE *_iobs;
};
struct _atexit {
    struct _atexit *_next;
    int _ind;
    void (*_fns[32])(void);
};
struct tm {
    int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst;
};
struct _reent {
    int _errno;
    struct __sFILE *_stdin, *_stdout, *_stderr;
    int _inc;
    char _emergency[25];
    int _current_category;
    const char *_current_locale;
    int __sdidinit;
    void (*__cleanup)(struct _reent *);
    struct _Bigint *_result;
    int _result_k;
    struct _Bigint *_p5s;
    struct _Bigint **_freelist;
    int _cvtlen;
    char *_cvtbuf;
    union {
        struct {
            unsigned int _rand_next;
            char *_strtok_last;
            char _asctime_buf[26];
            struct tm _localtime_buf;
            int _gamma_signgam;
        } _reent;
        struct {
            unsigned char *_nextf[30];
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
#define _REENT D_004854a0
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
#define _DEFUN(name, arglist, args) name(args)
#define name(void) name(void)
#define _AND ,
#define _CONST const
#define _PTR void *
#define _VOID void
#define CHECK_INIT(fp) \
  do					\
    {					\
      if ((fp)->_data == 0)		\
	(fp)->_data = _REENT;		\
      if (!(fp)->_data->__sdidinit)	\
	__sinit ((fp)->_data);		\
    }					\
  while (0)
void FUN_00125138(struct _reent *);
#define __sinit FUN_00125138
int FUN_00125c90(struct _reent *, int (*)(FILE *));
#define _fwalk FUN_00125c90
struct _glue *FUN_00124f88(struct _reent *, int);
#define __sfmoreglue FUN_00124f88
void *memcpy(void *, const void *, size_t);
int FUN_001296a8(FILE *);
#define __srefill FUN_001296a8
size_t
FUN_001252c8(_PTR buf, size_t size, size_t count, FILE * fp)
{
  register size_t resid;
  register char *p;
  register int r;
  size_t total;

  if ((resid = count * size) == 0)
    return 0;
  if (fp->_r < 0)
    fp->_r = 0;
  total = resid;
  p = buf;

  while (resid > (r = fp->_r))
    {
      (void) memcpy ((void *) p, (void *) fp->_p, (size_t) r);
      fp->_p += r;
      /* fp->_r = 0 ... done in __srefill */
      p += r;
      resid -= r;
      if (__srefill (fp))
	{
	  /* no more input: return partial result */
#ifdef __SCLE
        if (fp->_flags & __SCLE)
            return crlf(fp, buf, total-resid, 1) / size;
#endif
	  return (total - resid) / size;
	}
    }
  (void) memcpy ((void *) p, (void *) fp->_p, resid);
  fp->_r -= resid;
  fp->_p += resid;
#ifdef __SCLE
  if (fp->_flags & __SCLE)
    return crlf(fp, buf, total, 0) / size;
#endif
  return count;
}

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
void FUN_00124d40(struct _reent *);
void FUN_00124d48(struct _reent *);
#define ENV_LOCK FUN_00124d40(reent_ptr)
#define ENV_UNLOCK FUN_00124d48(reent_ptr)
int strncmp(const char *, const char *, size_t);
#define strncmp strncmp
extern char ***D_004851a8;
#define p_environ D_004851a8

char *
FUN_00125d78(struct _reent *reent_ptr, register _CONST char *name, int *offset)
{
  register int len;
  register char **p;
  _CONST char *c;

  ENV_LOCK;

  /* In some embedded systems, this does not get set.  This protects
     newlib from dereferencing a bad pointer.  */
  if (!*p_environ)
    return NULL;

  c = name;
  len = 0;
  while (*c && *c != '=')
    {
      c++;
      len++;
    }

  for (p = *p_environ; *p; ++p)
    if (!strncmp (*p, name, len))
      if (*(c = *p + len) == '=')
	{
	  *offset = p - *p_environ;
          ENV_UNLOCK;
	  return (char *) (++c);
	}
  ENV_UNLOCK;
  return NULL;
}

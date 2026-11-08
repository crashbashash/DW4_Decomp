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
#define _DEFUN_VOID(name) name(void)
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
#define BUFSIZ 1024
#define S_IFMT 0170000
#define S_IFCHR 0020000
#define S_IFREG 0100000
struct stat {
    short st_dev;
    unsigned short st_ino;
    unsigned int st_mode;
    unsigned short st_nlink;
    unsigned short st_uid;
    unsigned short st_gid;
    short st_rdev;
    long st_size;
    long st_atime;
    long st_spare1;
    long st_mtime;
    long st_spare2;
    long st_ctime;
    long st_spare3;
    long st_blksize;
    long st_blocks;
    long st_spare4[2];
};
int FUN_00125850(struct _reent *, int, struct stat *);
#define _fstat_r FUN_00125850
void *FUN_00126600(struct _reent *, size_t);
#define _malloc_r FUN_00126600
_fpos_t FUN_0012a088(void *, _fpos_t, int);
#define __sseek FUN_0012a088
void FUN_001250f8(struct _reent *);
#define _cleanup_r FUN_001250f8
int FUN_0010b690(int);
#define isatty FUN_0010b690

_VOID
FUN_00126028 (fp)
     register FILE *fp;
{
  register size_t size, couldbetty;
  register _PTR p;
  struct stat st;

  if (fp->_flags & __SNBF)
    {
      fp->_bf._base = fp->_p = fp->_nbuf;
      fp->_bf._size = 1;
      return;
    }
  if (fp->_file < 0 || _fstat_r (fp->_data, fp->_file, &st) < 0)
    {
      couldbetty = 0;
      size = BUFSIZ;
      /* do not try to optimise fseek() */
      fp->_flags |= __SNPT;
    }
  else
    {
      couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
#ifdef HAVE_BLKSIZE
      size = st.st_blksize <= 0 ? BUFSIZ : st.st_blksize;
#else
      size = BUFSIZ;
#endif
      /*
       * Optimize fseek() only if it is a regular file.
       * (The test for __sseek is mainly paranoia.)
       */
      if ((st.st_mode & S_IFMT) == S_IFREG && fp->_seek == __sseek)
	{
	  fp->_flags |= __SOPT;
#ifdef HAVE_BLKSIZE
	  fp->_blksize = st.st_blksize;
#else
	  fp->_blksize = 1024;
#endif
	}
      else
	fp->_flags |= __SNPT;
    }
  if ((p = _malloc_r (fp->_data, size)) == NULL)
    {
      fp->_flags |= __SNBF;
      fp->_bf._base = fp->_p = fp->_nbuf;
      fp->_bf._size = 1;
    }
  else
    {
      fp->_data->__cleanup = _cleanup_r;
      fp->_flags |= __SMBF;
      fp->_bf._base = fp->_p = (unsigned char *) p;
      fp->_bf._size = size;
      if (couldbetty && isatty (fp->_file))
	fp->_flags |= __SLBF;
    }
}

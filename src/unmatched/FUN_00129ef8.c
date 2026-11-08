/* newlib sscanf(str, fmt, ...). */
typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)
struct _reent;
struct __sbuf { unsigned char *_base; int _size; };
typedef struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;
  void *_cookie;
  int (*_read)(void *, char *, int);
  int (*_write)(void *, const char *, int);
  long (*_seek)(void *, long, int);
  int (*_close)(void *);
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
struct _reent {
  int _errno;
  FILE *_stdin, *_stdout, *_stderr;
  int _inc;
  char _emergency[25];
  int _current_category;
  const char *_current_locale;
  int __sdidinit;
};
extern struct _reent *D_004854a0;
unsigned int strlen(const char *);
int FUN_00129ef0(void *, char *, int);
int FUN_0012ef50(FILE *, const char *, va_list);
#define __SRD 0x0004

int FUN_00129ef8(const char *str, const char *fmt, ...)
{
  int ret;
  va_list ap;
  FILE f;

  f._flags = __SRD;
  f._bf._base = f._p = (unsigned char *) str;
  f._bf._size = f._r = strlen (str);
  f._read = FUN_00129ef0;
  f._ub._base = 0;
  f._lb._base = 0;
  f._data = D_004854a0;
  va_start (ap, fmt);
  ret = FUN_0012ef50 (&f, fmt, ap);
  va_end (ap);
  return ret;
}

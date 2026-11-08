/* newlib _snprintf_r(ptr, str, size, fmt, ...). */
typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)
typedef unsigned int size_t;
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
#define __SWR 0x0008
#define __SSTR 0x0200
int vfprintf(FILE *fp, const char *fmt, va_list ap);

int FUN_00129ca0(struct _reent *ptr, char *str, size_t size, const char *fmt, ...)
{
  int ret;
  va_list ap;
  FILE f;

  f._flags = __SWR | __SSTR;
  f._bf._base = f._p = (unsigned char *) str;
  f._bf._size = f._w = (size > 0 ? size - 1 : 0);
  f._data = ptr;
  va_start (ap, fmt);
  ret = vfprintf (&f, fmt, ap);
  va_end (ap);
  if (size > 0)
    *f._p = 0;
  return (ret);
}

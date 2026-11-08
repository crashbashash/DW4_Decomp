/* newlib __srefill(fp). */
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
void FUN_00125138(struct _reent *);
int FUN_00124e10(FILE *);
void FUN_001253e8(struct _reent *, void *);
void FUN_00126028(FILE *);
int FUN_00125c90(struct _reent *, int (*)(FILE *));
int FUN_00129670(FILE *);

#define EOF (-1)
#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SRD 0x0004
#define __SWR 0x0008
#define __SRW 0x0010
#define __SEOF 0x0020
#define __SERR 0x0040
#define __SMOD 0x2000
#define HASUB(fp) ((fp)->_ub._base != 0)
#define FREEUB(fp) { \
	if ((fp)->_ub._base != (fp)->_ubuf) \
		FUN_001253e8((fp)->_data, (char *)(fp)->_ub._base); \
	(fp)->_ub._base = 0; \
}
#define CHECK_INIT(fp) \
  do					\
    {					\
      if ((fp)->_data == 0)		\
	(fp)->_data = D_004854a0;		\
      if (!(fp)->_data->__sdidinit)	\
	FUN_00125138 ((fp)->_data);		\
    }					\
  while (0)

int
FUN_001296a8 (register FILE * fp)
{
  CHECK_INIT (fp);

  fp->_r = 0;

  if (fp->_flags & __SEOF)
    return EOF;

  if ((fp->_flags & __SRD) == 0)
    {
      if ((fp->_flags & __SRW) == 0)
	return EOF;
      if (fp->_flags & __SWR)
	{
	  if (FUN_00124e10 (fp))
	    return EOF;
	  fp->_flags &= ~__SWR;
	  fp->_w = 0;
	  fp->_lbfsize = 0;
	}
      fp->_flags |= __SRD;
    }
  else
    {
      if (HASUB (fp))
	{
	  FREEUB (fp);
	  if ((fp->_r = fp->_ur) != 0)
	    {
	      fp->_p = fp->_up;
	      return 0;
	    }
	}
    }

  if (fp->_bf._base == 0)
    FUN_00126028 (fp);

  if (fp->_flags & (__SLBF | __SNBF))
    (void) FUN_00125c90 (fp->_data, FUN_00129670);
  fp->_p = fp->_bf._base;
  fp->_r = (*fp->_read) (fp->_cookie, (char *) fp->_p, fp->_bf._size);
  fp->_flags &= ~__SMOD;
  if (fp->_r <= 0)
    {
      if (fp->_r == 0)
	fp->_flags |= __SEOF;
      else
	{
	  fp->_r = 0;
	  fp->_flags |= __SERR;
	}
      return EOF;
    }
  return 0;
}

typedef unsigned int size_t;
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
  int (*_read)();
  int (*_write)();
  long (*_seek)();
  int (*_close)();
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
struct __siov { void *iov_base; size_t iov_len; };
struct __suio { struct __siov *uio_iov; int uio_iovcnt; int uio_resid; };
int FUN_0012fef0();
int FUN_00124e10();
void *FUN_00127148();
void *memchr();
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define COPY(n)	  (void) FUN_00127148((void *) fp->_p, (void *) p, (size_t) (n))

int FUN_001258b0(fp, uio)
     register FILE *fp;
     register struct __suio *uio;
{
  register size_t len;
  register char *p;
  register struct __siov *iov;
  register int w, s;
  char *nl;
  int nlknown, nldist;

  if ((len = uio->uio_resid) == 0)
    return 0;

  if ((((fp)->_flags & 0x0008) == 0 || (fp)->_bf._base == 0) && FUN_0012fef0(fp))
    return -1;

  iov = uio->uio_iov;
  len = 0;

  if (fp->_flags & 0x0002)
    {
      do
	{
	  while (len == 0) { p = iov->iov_base; len = iov->iov_len; iov++; }
	  w = (*fp->_write) (fp->_cookie, p, MIN (len, 1024));
	  if (w <= 0)
	    goto err;
	  p += w;
	  len -= w;
	}
      while ((uio->uio_resid -= w) != 0);
    }
  else if ((fp->_flags & 0x0001) == 0)
    {
      do
	{
	  while (len == 0) { p = iov->iov_base; len = iov->iov_len; iov++; }
	  w = fp->_w;
	  if (fp->_flags & 0x0200)
	    {
	      if (len < w)
		w = len;
	      COPY (w);
	      fp->_w -= w;
	      fp->_p += w;
	      w = len;
	    }
	  else if (fp->_p > fp->_bf._base && len > w)
	    {
	      COPY (w);
	      fp->_p += w;
	      if (FUN_00124e10 (fp))
		goto err;
	    }
	  else if (len >= (w = fp->_bf._size))
	    {
	      w = (*fp->_write) (fp->_cookie, p, w);
	      if (w <= 0)
		goto err;
	    }
	  else
	    {
	      w = len;
	      COPY (w);
	      fp->_w -= w;
	      fp->_p += w;
	    }
	  p += w;
	  len -= w;
	}
      while ((uio->uio_resid -= w) != 0);
    }
  else
    {
      nlknown = 0;
      do
	{
	  while (len == 0) { nlknown = 0; p = iov->iov_base; len = iov->iov_len; iov++; }
	  if (!nlknown)
	    {
	      nl = memchr ((void *) p, '\n', len);
	      nldist = nl ? nl + 1 - p : len + 1;
	      nlknown = 1;
	    }
	  s = MIN (len, nldist);
	  w = fp->_w + fp->_bf._size;
	  if (fp->_p > fp->_bf._base && s > w)
	    {
	      COPY (w);
	      fp->_p += w;
	      if (FUN_00124e10 (fp))
		goto err;
	    }
	  else if (s >= (w = fp->_bf._size))
	    {
	      w = (*fp->_write) (fp->_cookie, p, w);
	      if (w <= 0)
		goto err;
	    }
	  else
	    {
	      w = s;
	      COPY (w);
	      fp->_w -= w;
	      fp->_p += w;
	    }
	  if ((nldist -= w) == 0)
	    {
	      if (FUN_00124e10 (fp))
		goto err;
	      nlknown = 0;
	    }
	  p += w;
	  len -= w;
	}
      while ((uio->uio_resid -= w) != 0);
    }
  return 0;

err:
  fp->_flags |= 0x0040;
  return -1;
}

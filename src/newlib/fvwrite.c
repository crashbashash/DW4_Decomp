#include "dw4/newlib_stdio.h"

void *memmove();
void *memchr();
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define COPY(n)	  (void) memmove((void *) fp->_p, (void *) p, (size_t) (n))

int __sfvwrite(register FILE *fp, register struct __suio *uio)
{
  register size_t len;
  register char *p;
  register struct __siov *iov;
  register int w, s;
  char *nl;
  int nlknown, nldist;

  if ((len = uio->uio_resid) == 0)
    return 0;

  if (cantwrite (fp))
    return -1;

  iov = uio->uio_iov;
  len = 0;

  if (fp->_flags & __SNBF)
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
  else if ((fp->_flags & __SLBF) == 0)
    {
      do
	{
	  while (len == 0) { p = iov->iov_base; len = iov->iov_len; iov++; }
	  w = fp->_w;
	  if (fp->_flags & __SSTR)
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
	      if (fflush (fp))
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
	      if (fflush (fp))
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
	      if (fflush (fp))
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
  fp->_flags |= __SERR;
  return -1;
}

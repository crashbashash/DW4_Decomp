#include "dw4/newlib_stdio.h"

int ungetc (int, FILE *);
void * _malloc_r (struct _reent *, size_t);
void * _realloc_r (struct _reent *, void *, size_t);
void * memcpy (void *, const void *, size_t);

int __submore(register FILE *fp)
{
  register int i;
  register unsigned char *p;
  if (fp->_ub._base == fp->_ubuf)
    {
      if ((p = (unsigned char *) _malloc_r (fp->_data, (size_t) 1024)) == 0)
        return (-1);
      fp->_ub._base = p;
      fp->_ub._size = 1024;
      p += 1024 - sizeof (fp->_ubuf);
      for (i = sizeof (fp->_ubuf); --i >= 0;)
        p[i] = fp->_ubuf[i];
      fp->_p = p;
      return 0;
    }
  i = fp->_ub._size;
  p = (unsigned char *) _realloc_r (fp->_data, (void *) (fp->_ub._base), i << 1);
  if (p == 0)
    return (-1);
  (void) memcpy ((void *) (p + i), (void *) p, (size_t) i);
  fp->_p = p + i;
  fp->_ub._base = p;
  fp->_ub._size = i << 1;
  return 0;
}

int ungetc(int c, register FILE *fp)
{
  if (c == EOF)
    return EOF;
  CHECK_INIT (fp);
  fp->_flags &= ~__SEOF;
  if ((fp->_flags & __SRD) == 0)
    {
      if ((fp->_flags & __SRW) == 0)
        return (-1);
      if (fp->_flags & __SWR)
        {
          if (fflush (fp))
            return (-1);
          fp->_flags &= ~__SWR;
          fp->_w = 0;
          fp->_lbfsize = 0;
        }
      fp->_flags |= __SRD;
    }
  c = (unsigned char) c;
  if (HASUB (fp))
    {
      if (fp->_r >= fp->_ub._size && __submore (fp))
        return (-1);
      *--fp->_p = c;
      fp->_r++;
      return c;
    }
  if (fp->_bf._base != 0 && fp->_p > fp->_bf._base && fp->_p[-1] == c)
    {
      fp->_p--;
      fp->_r++;
      return c;
    }
  fp->_ur = fp->_r;
  fp->_up = fp->_p;
  fp->_ub._base = fp->_ubuf;
  fp->_ub._size = sizeof (fp->_ubuf);
  fp->_ubuf[sizeof (fp->_ubuf) - 1] = c;
  fp->_p = &fp->_ubuf[sizeof (fp->_ubuf) - 1];
  fp->_r = 1;
  return c;
}

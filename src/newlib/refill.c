#include "dw4/newlib_stdio.h"

int lflush(FILE *);

int lflush(FILE *fp)
{
    if ((fp->_flags & (__SLBF | __SWR)) == (__SLBF | __SWR)) {
        return fflush(fp);
    }
    return 0;
}

int
__srefill (register FILE * fp)
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
	  if (fflush (fp))
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
    __smakebuf (fp);

  if (fp->_flags & (__SLBF | __SNBF))
    (void) _fwalk (fp->_data, lflush);
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

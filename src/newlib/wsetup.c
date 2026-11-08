#include "dw4/newlib_stdio.h"

int
__swsetup(register FILE * fp)
{
  CHECK_INIT (fp);
  if ((fp->_flags & __SWR) == 0)
    {
      if ((fp->_flags & __SRW) == 0)
        return (-1);
      if (fp->_flags & __SRD)
        {
          if (HASUB (fp))
            FREEUB (fp);
          fp->_flags &= ~(__SRD | __SEOF);
          fp->_r = 0;
          fp->_p = fp->_bf._base;
        }
      fp->_flags |= __SWR;
    }
  if (fp->_bf._base == 0)
    __smakebuf (fp);
  if (fp->_flags & __SLBF)
    {
      fp->_w = 0;
      fp->_lbfsize = -fp->_bf._size;
    }
  else
    fp->_w = fp->_flags & __SNBF ? 0 : fp->_bf._size;
  return 0;
}

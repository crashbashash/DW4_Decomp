typedef void (*_sig_func_ptr)(int);
#include "dw4/newlib_reent.h"
#define NSIG 32
#define SIG_DFL ((_sig_func_ptr)0)
#define SIG_IGN ((_sig_func_ptr)1)
#define SIG_ERR ((_sig_func_ptr)-1)
#define EINVAL 22
int FUN_00129940(struct _reent *ptr);
int FUN_00129c88(struct _reent *ptr);
int FUN_00129c28(struct _reent *ptr, int pid, int sig);

int
FUN_00129a30 (ptr, sig)
     struct _reent *ptr;
     int sig;
{
  _sig_func_ptr func;

  if (sig < 0 || sig >= NSIG)
    {
      ptr->_errno = EINVAL;
      return -1;
    }

  if (ptr->_sig_func == 0 && FUN_00129940 (ptr) != 0)
    return -1;
  
  func = ptr->_sig_func[sig];
  if (func == SIG_DFL)
    return FUN_00129c28 (ptr, FUN_00129c88 (ptr), sig);
  else if (func == SIG_IGN)
    return 0;
  else if (func == SIG_ERR)
    {
      ptr->_errno = EINVAL;
      return 1;
    }
  else
    {
      ptr->_sig_func[sig] = SIG_DFL;
      func (sig);
      return 0;
    }
}

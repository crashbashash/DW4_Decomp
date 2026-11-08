/* newlib 1.10.0 libc/signal/signal.c, built whole. */
typedef void (*_sig_func_ptr)(int);
#include "dw4/newlib_reent.h"
#define NULL ((void *)0)
#define NSIG 32
#define SIG_DFL ((_sig_func_ptr)0)
#define SIG_IGN ((_sig_func_ptr)1)
#define SIG_ERR ((_sig_func_ptr)-1)
#define EINVAL 22
#define _REENT DAT_004854a0
extern struct _reent *DAT_004854a0;
void *FUN_00126600(struct _reent *ptr, unsigned int size);
int FUN_00129c28(struct _reent *ptr, int pid, int sig);
int FUN_00129c88(struct _reent *ptr);

int
FUN_00129940 (ptr)
     struct _reent *ptr;
{
  int i;

  if (ptr->_sig_func == NULL)
    {
      ptr->_sig_func = (_sig_func_ptr *)FUN_00126600 (ptr, sizeof (_sig_func_ptr) * NSIG);
      if (ptr->_sig_func == NULL)
	return -1;

      for (i = 0; i < NSIG; i++)
	ptr->_sig_func[i] = SIG_DFL;
    }

  return 0;
}

_sig_func_ptr
FUN_001299b0 (ptr, sig, func)
     struct _reent *ptr;
     int sig;
     _sig_func_ptr func;
{
  _sig_func_ptr old_func;

  if (sig < 0 || sig >= NSIG)
    {
      ptr->_errno = EINVAL;
      return SIG_ERR;
    }

  if (ptr->_sig_func == NULL && FUN_00129940 (ptr) != 0)
    return SIG_ERR;

  old_func = ptr->_sig_func[sig];
  ptr->_sig_func[sig] = func;

  return old_func;
}

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

  if (ptr->_sig_func == NULL && FUN_00129940 (ptr) != 0)
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

int
FUN_00129b08 (ptr, sig)
     struct _reent *ptr;
     int sig;
{
  _sig_func_ptr func;

  if (sig < 0 || sig >= NSIG)
    {
      return -1;
    }

  if (ptr->_sig_func == NULL && FUN_00129940 (ptr) != 0)
    return -1;

  func = ptr->_sig_func[sig];
  if (func == SIG_DFL)
    return 1;
  else if (func == SIG_ERR)
    return 2;
  else if (func == SIG_IGN)
    return 3;
  else
    {
      ptr->_sig_func[sig] = SIG_DFL;
      func (sig);
      return 0;
    }
}

int
FUN_00129ba0 (sig)
     int sig;
{
  return FUN_00129a30 (_REENT, sig);
}

_sig_func_ptr
FUN_00129bc0 (int sig, _sig_func_ptr func)
{
  return FUN_001299b0 (_REENT, sig, func);
}

int
FUN_00129be8 ()
{
  return FUN_00129940 (_REENT);
}

int
FUN_00129c08 (int sig)
{
  return FUN_00129b08 (_REENT, sig);
}

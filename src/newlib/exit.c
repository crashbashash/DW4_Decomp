#include "dw4/newlib_reent.h"

void _exit(int code);

void exit(int code)
{
    struct _atexit *p;
    int n;

    for (p = _REENT->_atexit; p; p = p->_next) {
        for (n = p->_ind; --n >= 0;) {
            (*p->_fns[n])();
        }
    }
    if (_REENT->__cleanup) {
        (*_REENT->__cleanup)(_REENT);
    }
    _exit(code);
}

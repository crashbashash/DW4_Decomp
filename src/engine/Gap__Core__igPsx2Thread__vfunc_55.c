/* 0x0032f8c0
 * Store the id of the calling thread (GetThreadId syscall wrapper) in
 * `_threadID`, release the thread's stack block through FUN_00300f50
 * (igObject_FreeStorage's twin, finding #3225) and clear `_stack`.
 * Fields from include/dw4/reflected.h (+60 _threadID, +32 _stack). */
#include "dw4/reflected.h"
int FUN_00300f50();
int GetThreadId();

void Gap__Core__igPsx2Thread__vfunc_55(igPsx2Thread *self) {
    self->_threadID = GetThreadId();
    FUN_00300f50(self, self->_stack);
    self->_stack = 0;
}

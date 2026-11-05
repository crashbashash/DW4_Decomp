/* 0x0032fee0 — Gap::Core::igPsx2Thread::vfunc_47: runs the platform thread call on the
 * thread's id (_threadID) and reports through a status word: the "failed" word when the
 * call returns a negative value, the "succeeded" word otherwise.  Sibling vfunc_46 is
 * the same shape around SuspendThread.  The two status words at 0x004fb410 / 0x004fb418
 * are both zero in the pristine ELF (docs/engine/array-storage.md, allocator-registry.md). */
#include "dw4/reflected.h"
/* Status words reported to callers; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded_004fb410[4];
extern int g_statusFailed_004fb418[4];
int FUN_0010bea8(int);

void Gap__Core__igPsx2Thread__vfunc_47(int *status, igPsx2Thread *thread) {
    int *word;

    if (FUN_0010bea8(thread->_threadID) < 0) {
        word = g_statusFailed_004fb418;
    } else {
        word = g_statusSucceeded_004fb410;
    }
    *status = *word;
}

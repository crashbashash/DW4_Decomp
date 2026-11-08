/* Runs the platform thread call on the thread's id (_threadID) and reports through a status word:
 * the "failed" word when the call returns a negative value, the "succeeded" word otherwise.
 * Sibling vfunc_46 is the same shape around SuspendThread. The two status words are both zero in
 * the pristine ELF. */
#include "dw4/reflected.h"
/* Status words reported to callers; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
extern int g_allocatorFailureStatus[4];
int iSuspendThread(int);

void Gap__Core__igPsx2Thread__vfunc_47(int *status, igPsx2Thread *thread) {
    int *word;

    if (iSuspendThread(thread->_threadID) < 0) {
        word = g_allocatorFailureStatus;
    } else {
        word = g_statusSucceeded;
    }
    *status = *word;
}

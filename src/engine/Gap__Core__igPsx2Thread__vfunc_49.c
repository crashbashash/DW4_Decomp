/* 0x0032ff30 — igPsx2Thread vfunc 49: resume the thread from interrupt context.
 * Same as vfunc 48 but calls the SDK iResumeThread (the interrupt-handler
 * variant of ResumeThread) on the thread's kernel id (_threadID); a negative
 * result publishes the failure status word, anything else the success word
 * through the first (hidden return-slot) argument.  Both words are set once
 * at engine start-up (docs/engine/array-storage.md, findings #504:
 * 0x4fb410 = 0, 0x4fb418 = 1). */
#include "dw4/reflected.h"

extern int g_statusSuccess_004fb410[4];
extern int g_statusFailure_004fb418[4];
int iResumeThread(int);

void Gap__Core__igPsx2Thread__vfunc_49(int *status, igPsx2Thread *self) {
    int *word;

    if (iResumeThread(self->_threadID) < 0) {
        word = g_statusFailure_004fb418;
    } else {
        word = g_statusSuccess_004fb410;
    }
    *status = *word;
}

/* 0x0032fc40 — igPsx2Thread vfunc 48: resume the thread.
 * Calls the SDK ResumeThread on the thread's kernel id (_threadID) and
 * reports the outcome through the first (hidden return-slot) argument: a
 * negative SDK result publishes the engine's failure status word, anything
 * else the success word.  Both words are set once at engine start-up
 * (docs/engine/array-storage.md, findings #504: 0x4fb410 = 0, 0x4fb418 = 1).
 * Vfunc 49 is the same body calling iResumeThread (interrupt-handler variant). */
#include "dw4/reflected.h"

extern int g_statusSucceeded[4];
extern int g_allocatorFailureStatus[4];
int ResumeThread(int);

void Gap__Core__igPsx2Thread__vfunc_48(int *status, igPsx2Thread *self) {
    int *word;

    if (ResumeThread(self->_threadID) < 0) {
        word = g_allocatorFailureStatus;
    } else {
        word = g_statusSucceeded;
    }
    *status = *word;
}

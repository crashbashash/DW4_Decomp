/* 0x0032fbf0 — igPsx2Thread vfunc 46: suspend the thread.
 * Calls the SDK SuspendThread on the thread's kernel id (_threadID) and
 * reports the outcome through the first (hidden return-slot) argument: a
 * negative SDK result publishes the engine's failure status word, anything
 * else the success word.  Both words are set once at engine start-up
 * (docs/engine/array-storage.md, findings #504: 0x4fb410 = 0, 0x4fb418 = 1). */
#include "dw4/reflected.h"

extern int g_statusSucceeded_004fb410[4];
extern int g_statusFailed_004fb418[4];
int SuspendThread(int);

void Gap__Core__igPsx2Thread__vfunc_46(int *status, igPsx2Thread *self) {
    int *word;

    if (SuspendThread(self->_threadID) < 0) {
        word = g_statusFailed_004fb418;
    } else {
        word = g_statusSucceeded_004fb410;
    }
    *status = *word;
}

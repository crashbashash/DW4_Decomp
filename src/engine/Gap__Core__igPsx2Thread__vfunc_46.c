/* Suspends the thread. Calls the SDK SuspendThread on the thread's kernel id (_threadID) and
 * reports the outcome through the first (hidden return-slot) argument: a negative SDK result
 * publishes the engine's failure status word, anything else the success word. Both words are set
 * once at engine start-up (0 and 1). */
#include "dw4/reflected.h"

extern int g_statusSucceeded[4];
extern int g_allocatorFailureStatus[4];
int SuspendThread(int);

void Gap__Core__igPsx2Thread__vfunc_46(int *status, igPsx2Thread *self) {
    int *word;

    if (SuspendThread(self->_threadID) < 0) {
        word = g_allocatorFailureStatus;
    } else {
        word = g_statusSucceeded;
    }
    *status = *word;
}

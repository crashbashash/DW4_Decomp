/* IgPsx2Thread vfunc 48: resume the thread. Calls the SDK ResumeThread on the thread's kernel id
 * (_threadID) and reports the outcome through the first (hidden return-slot) argument: a negative
 * SDK result publishes the engine's failure status word (1), anything else the success word (0).
 * Both words are set once at engine start-up. Vfunc 49 is the same body calling iResumeThread
 * (interrupt-handler variant). */
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

/* The pool's event tracker (reflected `_eventTracker`), stored as a raw handle. */
#include "dw4/reflected.h"
int igAliasMemoryPool_GetEventTracker(igAliasMemoryPool *self) {
    return self->_eventTracker;
}

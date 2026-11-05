/* 0x002d1030 — igAliasMemoryPool::SetEventTracker: reference-counted
 * assignment of the _eventTracker field (+0x98).  Retain the new tracker,
 * release the previous one (destroying it when its count reaches zero), then
 * store.  The refcount is the low 23 bits of igObject::_refCount (see
 * src/engine/ref-field-lifecycle.cpp). */
#include "dw4/reflected.h"
void igObject_Destroy(void *);

void igAliasMemoryPool_SetEventTracker(igAliasMemoryPool *self, igObject *tracker) {
    igObject *previous;
    if (tracker != 0) {
        tracker->_refCount = tracker->_refCount + 1;
    }
    previous = (igObject *)(self->_eventTracker);
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_eventTracker = (int)(tracker);
}

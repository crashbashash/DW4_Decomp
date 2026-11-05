#include "dw4/reflected.h"
int igObject_Destroy();

/* 0x003016f0 — slot 23 of igObjectDirEntry: set the _ref reference (+24; reflected as a raw ref,
 * but the code treats it as a counted igObject).
 * Reference-counted assignment: retain the new object, release the old one
 * (destroying it when its 23-bit count reaches zero, see
 * docs/engine/near-miss-shapes-player-vfunc44.md), then store the new one. */
void Gap__Core__igObjectDirEntry__vfunc_23(igObjectDirEntry *self, igObject *object) {
    igObject *previousObject;
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    previousObject = (igObject *)(self->_ref);
    if (previousObject != 0) {
        previousObject->_refCount = previousObject->_refCount - 1;
        if ((previousObject->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousObject);
        }
    }
    self->_ref = (int)object;
}

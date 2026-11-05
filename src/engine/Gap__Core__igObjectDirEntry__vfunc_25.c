/* 0x00301c30
 * Release one reference to `object`: drop its reference count and destroy it
 * when the 23-bit count (the `<< 0x29 >> 0x29` mask) reaches zero.  `self` is
 * not used.  Same inline release as in src/game/beSystemUpdate.c. */
#include "dw4/reflected.h"
int igObject_Destroy();

void Gap__Core__igObjectDirEntry__vfunc_25(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = (int)object->_refCount - 1;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(object);
        }
    }
}

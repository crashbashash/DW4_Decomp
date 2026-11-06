/* Clear the LOD's cached range lookup: release the reference held in _lastRange (destroying it
 * when its 23-bit count in the low bits of the _refCount word reaches zero, the same inline
 * release as igParticleAttr::vfunc_32) and reset _lastIndex to -1 and the cached
 * _lastLower/_lastUpper bounds to 0. _lastRange/_lastIndex are the pair read back by
 * igLod::vfunc_37. */
#include "dw4/reflected.h"
int igObject_Destroy();

void Gap__Sg__igLod__vfunc_31(igLod *self) {
    igObject *lastRange;
    lastRange = (igObject *)(self->_lastRange);
    if (lastRange != 0) {
        lastRange->_refCount = lastRange->_refCount - 1;
        if (((unsigned long long) ((long long)(int) lastRange->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(lastRange);
        }
    }
    self->_lastRange = 0;
    self->_lastIndex = -1;
    self->_lastLower = 0;
    self->_lastUpper = 0;
}

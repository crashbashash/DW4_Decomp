/* Address of key {index} in this sequence's translation track, or 0 when the sequence does not
 * drive that channel. _drivenChannels is a bitmask (1 = translation, 2 and 4 = the two rotation
 * slots, 8 = scale); the key array starts 16 bytes into the list object and each key is 0xC bytes. */
#include "dw4/reflected.h"
int Gap__Sg__igTransformSequence1_5__vfunc_42(igTransformSequence1_5 *self, int index) {
    if (self->_drivenChannels & 1) {
        return *(int *)((char *)(self->_xlateList) + 16) + (index * 0xC);
    }
    return 0;
}

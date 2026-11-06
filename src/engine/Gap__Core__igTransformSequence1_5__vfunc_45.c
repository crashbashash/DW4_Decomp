/* Address of key {index} in this sequence's quaternion track, or 0 when the sequence does not
 * drive that channel. _drivenChannels is a bitmask (1 = translation, 2 and 4 = the two rotation
 * slots, 8 = scale); the key array starts 16 bytes into the list object and each key is 0x10
 * bytes. */
#include "dw4/reflected.h"
int Gap__Core__igTransformSequence1_5__vfunc_45(igTransformSequence1_5 *self, int index) {
    if (self->_drivenChannels & 2) {
        return *(int *)((char *)(self->_quatList) + 16) + (index * 0x10);
    }
    return 0;
}

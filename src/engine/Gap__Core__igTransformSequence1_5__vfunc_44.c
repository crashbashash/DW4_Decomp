/* 0x001e2b30 — Gap__Core__igTransformSequence1_5__vfunc_44.
 * Overwrites rotation key `index` (a 16-byte quaternion of _quatList) with the
 * four floats at `quaternion`.  Ignored unless channel bit 2 of _drivenChannels
 * is set and the index is inside the list (retail instructions; the sibling
 * accessors vfunc_42/vfunc_48 gate their lists on _drivenChannels the same way). */
#include "dw4/reflected.h"
void Gap__Core__igTransformSequence1_5__vfunc_44(igTransformSequence1_5 *self, int index, void *quaternion) {
    int count;
    igQuaternionfList *quatList;
    void *key;

    if (self->_drivenChannels & 2) {
        quatList = (igQuaternionfList *)(self->_quatList);
        count = quatList->_count;
        if ((count != 0) && (index >= 0) && (index < count)) {
            key = (void *)(quatList->_data + (index * 0x10));
            *(float *)((char *)(key) + 0) = (float) *(float *)((char *)(quaternion) + 0);
            *(float *)((char *)(key) + 4) = (float) *(float *)((char *)(quaternion) + 4);
            *(float *)((char *)(key) + 8) = (float) *(float *)((char *)(quaternion) + 8);
            *(float *)((char *)(key) + 12) = (float) *(float *)((char *)(quaternion) + 12);
        }
    }
}

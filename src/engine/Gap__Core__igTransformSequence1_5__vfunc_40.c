/* IgTransformSequence1_5 vfunc_40: overwrite one keyframe of the translation list (_xlateList,
 * 12-byte x/y/z entries) with the vector at `translation`. Does nothing unless bit 0 of
 * _drivenChannels is set and `index` is inside the list. Sibling accessors with the same shape:
 * vfunc_44 (quaternion list, bit 1) and vfunc_49 (scale list, bit 3). */
#include "dw4/reflected.h"
void Gap__Core__igTransformSequence1_5__vfunc_40(igTransformSequence1_5 *self, int index, float *translation) {
    int count;
    igVec3fList *xlateList;
    float *entry;

    if (self->_drivenChannels & 1) {
        xlateList = (igVec3fList *)(self->_xlateList);
        count = xlateList->_count;
        if ((count != 0) && (index >= 0) && (index < count)) {
            entry = (float *)(xlateList->_data + (index * 0xC));
            entry[0] = translation[0];
            entry[1] = translation[1];
            entry[2] = translation[2];
        }
    }
}

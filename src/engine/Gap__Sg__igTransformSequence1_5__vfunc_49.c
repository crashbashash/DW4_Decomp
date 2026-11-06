/* IgTransformSequence1_5 vfunc_49: store one scale key. When the sequence drives the scale channel
 * it copies the three floats at `scale` into key `index` of _scaleList (12 bytes per key); a
 * missing channel or an out-of-range index is ignored. Counterpart of vfunc_50, which returns the
 * address of the same key (it tests the same channel bit and uses the same 12-byte stride). */
#include "dw4/reflected.h"
/* _drivenChannels bit for the scale channel (vfunc_50 tests it before reading _scaleList) */
#define TRANSFORM_CHANNEL_SCALE 8
void Gap__Sg__igTransformSequence1_5__vfunc_49(igTransformSequence1_5 *self, int index, void *scale) {
    int count;
    igVec3fList *scaleList;
    float *key;
    float *src;

    if (self->_drivenChannels & TRANSFORM_CHANNEL_SCALE) {
        scaleList = (igVec3fList *)(self->_scaleList);
        count = scaleList->_count;
        if ((count != 0) && (index >= 0) && (index < count)) {
            key = (float *)(scaleList->_data + (index * 0xC));
            src = (float *)scale;
            key[0] = (float) src[0];
            key[1] = (float) src[1];
            key[2] = (float) src[2];
        }
    }
}

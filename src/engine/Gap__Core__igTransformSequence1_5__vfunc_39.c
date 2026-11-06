/* Number of keyframe times: the element count of the long-time list (`_timeListLong` is an
 * igLongList; `_count` is at +8). */
#include "dw4/reflected.h"
int Gap__Core__igTransformSequence1_5__vfunc_39(igTransformSequence1_5 *self) {
    return ((igLongList *)self->_timeListLong)->_count;
}

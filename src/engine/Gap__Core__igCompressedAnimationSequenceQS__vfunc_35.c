/* IgCompressedAnimationSequenceQS virtual getter 35. Returns the element count of the
 * `_compressedTimeList` (reflected object ref, +16): the word at +8 of an igDataList-style list is
 * `_count`. The list is read through the generic igDataList layout. */
#include "dw4/reflected.h"
int Gap__Core__igCompressedAnimationSequenceQS__vfunc_35(igCompressedAnimationSequenceQS *self) {
    return ((igDataList *)self->_compressedTimeList)->_count;
}

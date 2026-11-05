#include "dw4/reflected.h"

/* 0x001e33c0
 * Setter: stores the sequence length (`_animationDuration`, an
 * igUnsignedLongMetaField of the reflected igCompressedAnimationSequenceQS). */
void Gap__Core__igCompressedAnimationSequenceQS__vfunc_45(igCompressedAnimationSequenceQS *self, long long animationDuration) {
    self->_animationDuration = animationDuration;
}

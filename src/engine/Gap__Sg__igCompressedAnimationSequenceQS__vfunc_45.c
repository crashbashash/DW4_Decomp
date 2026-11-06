#include "dw4/reflected.h"

/* Setter: stores the sequence length (`_animationDuration`, an igUnsignedLongMetaField of the
 * reflected igCompressedAnimationSequenceQS). */
void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_45(igCompressedAnimationSequenceQS *self, long long animationDuration) {
    self->_animationDuration = animationDuration;
}

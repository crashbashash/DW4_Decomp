/* Returns the length of primitive strip `stripIndex` from the per-strip length table (_lengthData
 * is an int array, _numStrips entries); the getter paired with the setter in vfunc_26. */
#include "dw4/reflected.h"
int Gap__Gfx__igPrimLengthArray1_1__vfunc_27(igPrimLengthArray1_1 *self, int stripIndex) {
    return *(int *)(self->_lengthData + (stripIndex * 4));
}

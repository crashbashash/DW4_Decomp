/* Stores the length `length` of primitive strip `stripIndex` in the per-strip length table
 * (_lengthData is an int array, _numStrips entries). */
#include "dw4/reflected.h"
void Gap__Core__igPrimLengthArray1_1__vfunc_26(igPrimLengthArray1_1 *self, int stripIndex, int length) {
    *(int *)(self->_lengthData + (stripIndex * 4)) = length;
}

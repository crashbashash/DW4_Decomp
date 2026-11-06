#include "dw4/reflected.h"

/* Stores a float at +0x1c of the receiver. That offset lies past the 20 bytes the reflected
 * igPrimLengthArray1_1 describes, so the store stays an offset write. */
void Gap__Core__igPrimLengthArray1_1__vfunc_61(igPrimLengthArray1_1 *self, float value) {
    *(float *)((char *)self + 28) = value;
}

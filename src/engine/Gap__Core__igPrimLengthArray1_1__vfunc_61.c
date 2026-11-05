#include "dw4/reflected.h"

/* 0x0013fb00
 * Stores a float at +0x1c of the receiver. That offset lies past the 20 bytes
 * the reflected igPrimLengthArray1_1 describes, and no reflected field or
 * finding names it, so the store stays an offset write. */
void Gap__Core__igPrimLengthArray1_1__vfunc_61(igPrimLengthArray1_1 *self, float value) {
    *(float *)((char *)self + 28) = value;
}

/* 0x001d0890 — igLod vfunc 27: apply a transform to the node.
 * First runs the shared group step (FUN_001c6340 walks _childList, calling
 * each child's own slot 27 with the same argument), then transforms the LOD
 * centre point (_center, +0x34) in place by the 4x4 matrix.  The point/matrix
 * step (FUN_00192fc0) reads three floats from its second argument, applies
 * a row-vector multiply with the matrix's translation row, and stores three
 * floats to its first (asm/FUN_00192fc0.s). */
#include "dw4/reflected.h"

int FUN_00192fc0(float *, float *, float *);
int FUN_001c6340(igLod *, float *);

void Gap__Sg__igLod__vfunc_27(igLod *self, float *matrix) {
    FUN_001c6340(self, matrix);
    FUN_00192fc0(self->_center, self->_center, matrix);
}

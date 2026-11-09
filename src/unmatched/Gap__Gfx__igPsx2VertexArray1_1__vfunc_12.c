#include "dw4/reflected.h"

void FUN_001f05a0(int kind, long long sequence);
void FUN_0015e7b0(igPsx2VertexArray1_1 *self);
void FUN_00300f50(igPsx2VertexArray1_1 *self, int data);
void FUN_0017d2b0(igPsx2VertexArray1_1 *self);
void Gap__Core__igObject__vfunc_10(igPsx2VertexArray1_1 *self);

void Gap__Gfx__igPsx2VertexArray1_1__vfunc_12(igPsx2VertexArray1_1 *self) {
    if (self->_usageFlags & 4) {
        FUN_001f05a0(1, self->_lSequence);
    }
    if (self->_vdata != 0) {
        FUN_0015e7b0(self);
        FUN_00300f50(self, self->_vdata);
        self->_vdata = 0;
        self->_numVerts = 0;
    }
    FUN_0017d2b0(self);
    Gap__Core__igObject__vfunc_10(self);
}

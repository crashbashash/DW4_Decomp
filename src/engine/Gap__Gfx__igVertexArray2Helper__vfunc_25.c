/* Same as slot 24 for the stream with component type 6, index 0: looks it up with
 * igVertexArray2__FindVertexData and passes it to FUN_00162ca0 (same shape as FUN_00162b50 with
 * fewer data-list classes), whose component count is left in v0. The declared return type is void. */
#include "dw4/reflected.h"
int igVertexArray2__FindVertexData(int vertexArray, int componentType, int componentIndex);
int FUN_00162ca0(int vertexData);

void Gap__Gfx__igVertexArray2Helper__vfunc_25(igVertexArray2Helper *self) {
    FUN_00162ca0(igVertexArray2__FindVertexData(self->_vertexArray, 6, 0));
}

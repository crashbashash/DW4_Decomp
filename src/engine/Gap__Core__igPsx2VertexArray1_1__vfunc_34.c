/* Address of vertex `vertexIndex` in the array's vertex data: `_vdata` points at a block whose
 * second word (+4) is the base of the 12-byte (three-float) entries. */
#include "dw4/reflected.h"
#define VERTEX_ENTRY_SIZE 0xC  /* 3 floats per entry */
int Gap__Core__igPsx2VertexArray1_1__vfunc_34(igPsx2VertexArray1_1 *self, int vertexIndex) {
    return *(int *)((char *)(self->_vdata) + 4) + (vertexIndex * VERTEX_ENTRY_SIZE);
}

/* Looks up the bound vertex array's stream with component type 5, index 0
 * (igVertexArray2__FindVertexData) and passes it to FUN_00162b50, which switches on the class of
 * the stream's data list and leaves its component count in v0. The declared return type is void. */
#include "dw4/reflected.h"
int igVertexArray2__FindVertexData(int vertexArray, int componentType, int componentIndex);
int FUN_00162b50(int vertexData);

void Gap__Core__igVertexArray2Helper__vfunc_24(igVertexArray2Helper *self) {
    FUN_00162b50(igVertexArray2__FindVertexData(self->_vertexArray, 5, 0));
}

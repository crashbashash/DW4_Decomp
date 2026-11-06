/* Release the bound vertex array: drop one reference on it (destroying it when the 23-bit count in
 * the low bits of the _refCount word reaches zero, the same inline release as
 * igParticleAttr::vfunc_32) and clear _vertexArray. */
#include "dw4/reflected.h"
int igObject_Destroy();

void Gap__Gfx__igVertexArray2Helper__vfunc_55(igVertexArray2Helper *self) {
    igObject *vertexArray;
    vertexArray = (igObject *)(self->_vertexArray);
    if (vertexArray != 0) {
        vertexArray->_refCount = vertexArray->_refCount - 1;
        if (((unsigned long long) ((long long)(int) vertexArray->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(vertexArray);
        }
    }
    self->_vertexArray = 0;
}

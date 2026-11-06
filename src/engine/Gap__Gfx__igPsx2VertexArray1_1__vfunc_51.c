/* Read the {u, v} float pair of vertex `vertexIndex` from texture-coordinate stream `texCoordSet`
 * into *uv. The streams are _vdata[11 + set]; each entry is an 8-byte pair. vfunc_50 is the
 * setter, vfunc_52 returns the entry's address. */
#include "dw4/reflected.h"
void Gap__Gfx__igPsx2VertexArray1_1__vfunc_51(igPsx2VertexArray1_1 *self, int texCoordSet, int vertexIndex, void *uv) {
    void *entry;

    entry = (void *)(*(int *)(self->_vdata + ((texCoordSet + 0xB) * 4)) + (vertexIndex * 8));
    *(float *)((char *)(uv) + 0) = (float) *(float *)((char *)(entry) + 0);
    *(float *)((char *)(uv) + 4) = (float) *(float *)((char *)(entry) + 4);
}

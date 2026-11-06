/* Write the {u, v} float pair *uv to vertex `vertexIndex` of texture-coordinate stream
 * `texCoordSet` (_vdata[11 + set], 8 bytes per entry). vfunc_51 is the getter. */
#include "dw4/reflected.h"
void Gap__Core__igPsx2VertexArray1_1__vfunc_50(igPsx2VertexArray1_1 *self, int texCoordSet, int vertexIndex, void *uv) {
    void *entry;

    entry = (void *)(*(int *)(self->_vdata + ((texCoordSet + 0xB) * 4)) + (vertexIndex * 8));
    *(float *)((char *)(entry) + 0) = (float) *(float *)((char *)(uv) + 0);
    *(float *)((char *)(entry) + 4) = (float) *(float *)((char *)(uv) + 4);
}

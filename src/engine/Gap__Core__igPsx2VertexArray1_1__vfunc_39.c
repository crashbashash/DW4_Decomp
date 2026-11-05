/* 0x0015f0f0
 * Read the normal of vertex `index` into `out` (3 floats).  Counterpart of
 * vfunc_38: does nothing unless the vertex format has the normal bit set.
 * The normal stream is at _vdata + 72, 12 bytes per vertex (finding 680,
 * docs/engine/model-format.md). */
#include "dw4/reflected.h"
#define VERTEX_FORMAT_NORMALS 0x800000     /* bit 23 of _vertexFormat (finding 680) */
#define VDATA_NORMAL_STREAM 72             /* _vdata + 72: pointer to the normal stream */
#define NORMAL_STRIDE 0xC                  /* 3 floats per vertex */
void Gap__Core__igPsx2VertexArray1_1__vfunc_39(igPsx2VertexArray1_1 *self, int index, float *out) {
    float *normal;

    if (self->_vertexFormat & VERTEX_FORMAT_NORMALS) {
        normal = (float *)(*(int *)((char *)(self->_vdata) + VDATA_NORMAL_STREAM) + (index * NORMAL_STRIDE));
        out[0] = normal[0];
        out[1] = normal[1];
        out[2] = normal[2];
    }
}

/* 0x0015f0a0
 * Write the normal of vertex `index` from `in` (3 floats).  Does nothing
 * unless the vertex format has the normal bit set; stores into the normal
 * stream at _vdata + 72, 12 bytes per vertex (finding 680,
 * docs/engine/model-format.md). */
#include "dw4/reflected.h"
#define VERTEX_FORMAT_NORMALS 0x800000     /* bit 23 of _vertexFormat (finding 680) */
#define VDATA_NORMAL_STREAM 72             /* _vdata + 72: pointer to the normal stream */
#define NORMAL_STRIDE 0xC                  /* 3 floats per vertex */
void Gap__Core__igPsx2VertexArray1_1__vfunc_38(igPsx2VertexArray1_1 *self, int index, float *in) {
    float *normal;

    if (self->_vertexFormat & VERTEX_FORMAT_NORMALS) {
        normal = (float *)(*(int *)((char *)(self->_vdata) + VDATA_NORMAL_STREAM) + (index * NORMAL_STRIDE));
        normal[0] = in[0];
        normal[1] = in[1];
        normal[2] = in[2];
    }
}

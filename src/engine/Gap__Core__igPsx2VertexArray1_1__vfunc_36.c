/* Read the position of vertex `index` into `out` (3 floats). Does nothing unless the vertex format
 * has the position bit set. _vdata is the runtime table of stream pointers; the position stream is
 * at +68, 12 bytes per vertex. */
#include "dw4/reflected.h"
#define VERTEX_FORMAT_POSITIONS 0x400000   /* bit 22 of _vertexFormat */
#define VDATA_POSITION_STREAM 68           /* _vdata + 68: pointer to the position stream */
#define POSITION_STRIDE 0xC                /* 3 floats per vertex */
void Gap__Core__igPsx2VertexArray1_1__vfunc_36(igPsx2VertexArray1_1 *self, int index, float *out) {
    float *position;

    if (self->_vertexFormat & VERTEX_FORMAT_POSITIONS) {
        position = (float *)(*(int *)((char *)(self->_vdata) + VDATA_POSITION_STREAM) + (index * POSITION_STRIDE));
        out[0] = position[0];
        out[1] = position[1];
        out[2] = position[2];
    }
}

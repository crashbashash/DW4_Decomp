/* Write the position of vertex `index` from `in` (3 floats). Counterpart of vfunc_36: does nothing
 * unless the vertex format has the position bit set, and stores into the position stream at _vdata
 * + 68, 12 bytes per vertex. */
#include "dw4/reflected.h"
#define VERTEX_FORMAT_POSITIONS 0x400000   /* bit 22 of _vertexFormat */
#define VDATA_POSITION_STREAM 68           /* _vdata + 68: pointer to the position stream */
#define POSITION_STRIDE 0xC                /* 3 floats per vertex */
void Gap__Core__igPsx2VertexArray1_1__vfunc_35(igPsx2VertexArray1_1 *self, int index, float *in) {
    float *position;

    if (self->_vertexFormat & VERTEX_FORMAT_POSITIONS) {
        position = (float *)(*(int *)((char *)(self->_vdata) + VDATA_POSITION_STREAM) + (index * POSITION_STRIDE));
        position[0] = in[0];
        position[1] = in[1];
        position[2] = in[2];
    }
}

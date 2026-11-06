#include "dw4/reflected.h"
#include "dw4/typecast.h"
void *igVertexArray2__FindVertexData();
extern int DAT_005610b8[4];
void Gap__Gfx__igVertexArray2Helper__vfunc_29(igVertexArray2Helper *arg0, int arg1, float *arg2) {
    igVec3fList *var_s0;
    float *temp_v1;

    var_s0 = (igVec3fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData(arg0->_vertexArray, 1, 0))->_data), DAT_005610b8);
    temp_v1 = (float *)(var_s0->_data + (arg1 * 0xC));
    arg2[0] = temp_v1[0];
    arg2[1] = temp_v1[1];
    arg2[2] = temp_v1[2];
}

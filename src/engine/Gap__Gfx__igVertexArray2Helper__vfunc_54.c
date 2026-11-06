#include "dw4/reflected.h"
#include "dw4/typecast.h"
void *igVertexArray2__FindVertexData();
extern int DAT_005610c8[4];
void Gap__Gfx__igVertexArray2Helper__vfunc_54(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    igVec2fList *var_s0;
    char *temp_v1;

    var_s0 = (igVec2fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData(arg0->_vertexArray, 9, 0))->_data), DAT_005610c8);
    temp_v1 = (char *)(var_s0->_data + (arg1 * 8));
    *(float *)((char *)(arg2) + 0) = *(float *)(temp_v1 + 0);
    *(float *)((char *)(arg2) + 4) = *(float *)(temp_v1 + 4);
}

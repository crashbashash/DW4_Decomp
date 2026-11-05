#include "dw4/reflected.h"
igVertexData *igVertexArray2__FindVertexData();
int igObject_IsKindOf();
extern int DAT_005610b8[4];
void Gap__Core__igVertexArray2Helper__vfunc_35(igVertexArray2Helper *arg0, int arg1, float *arg2) {
    void *temp_v1;
    igVec3fList *var_s0;

    var_s0 = (igVec3fList *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 7, 0)->_data);
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610b8[0]) != 0)) {
        var_s0 = (igVec3fList *)var_s0;

    } else {
        var_s0 = (igVec3fList *)(0);
    }
    temp_v1 = (void *)(var_s0->_data + (arg1 * 0xC));
    arg2[0] = ((float *)temp_v1)[0];
    arg2[1] = ((float *)temp_v1)[1];
    arg2[2] = ((float *)temp_v1)[2];
}

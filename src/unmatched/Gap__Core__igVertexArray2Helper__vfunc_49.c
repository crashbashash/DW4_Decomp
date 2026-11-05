#include "dw4/reflected.h"
igVertexData *igVertexArray2__FindVertexData();
int igObject_IsKindOf();
extern int DAT_005610c8[4];
void Gap__Core__igVertexArray2Helper__vfunc_49(igVertexArray2Helper *arg0, int arg1, int arg2, float *arg3) {
    float *temp_v1;
    igVec2fList *var_s0;
    igVec2fList *r;

    var_s0 = (igVec2fList *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 4, arg1)->_data);
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610c8[0]) != 0)) {

        r = var_s0;
    } else {
        r = (igVec2fList *)(0);
    }
    temp_v1 = (float *)(r->_data + (arg2 * 8));
    arg3[0] = temp_v1[0];
    arg3[1] = temp_v1[1];
}

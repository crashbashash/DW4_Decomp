#include "dw4/reflected.h"
extern "C" {
void *igVertexArray2__FindVertexData(...);
int igObject_IsKindOf(...);
extern int DAT_005610c8[4];
void Gap__Core__igVertexArray2Helper__vfunc_48(igVertexArray2Helper *arg0, int arg1, int arg2, void *arg3) {
    int temp_v1;
    void *temp_v1_2;
    void *var_s0;
    igVec2fList *p;

    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 4, arg1)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610c8[0]) != 0)) {
        p = (igVec2fList *)var_s0;
    } else {
        p = (igVec2fList *)(0);
    }
    temp_v1 = p->_count;
    if ((temp_v1 != 0) && (arg2 >= 0) && (arg2 < temp_v1)) {
        temp_v1_2 = (void *)(p->_data + (arg2 * 8));
        *(float *)((char *)(temp_v1_2) + 0) = (float) *(float *)((char *)(arg3) + 0);
        *(float *)((char *)(temp_v1_2) + 4) = (float) *(float *)((char *)(arg3) + 4);
    }
}
}

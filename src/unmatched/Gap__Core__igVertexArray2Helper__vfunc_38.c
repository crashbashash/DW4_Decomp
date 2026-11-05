/* 0x00161460 - 156 bytes. Cast-or-null result kept in a separate variable (t = s0 / t = 0): the then arm survives as a jump and the join load is copied into its delay slot. */
#include "dw4/reflected.h"
void *igVertexArray2__FindVertexData();
int igObject_IsKindOf();
extern int DAT_005610b8[4];
void Gap__Core__igVertexArray2Helper__vfunc_38(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    void *temp_v1;
    void *var_s0;
    igVec3fList *t;

    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 8, 0)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610b8[0]) != 0)) {
        t = (igVec3fList *)var_s0;
    } else {
        t = (igVec3fList *)(0);
    }
    temp_v1 = (void *)(t->_data + (arg1 * 0xC));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 8);
}

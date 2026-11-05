#include "dw4/reflected.h"
#include "dw4/typecast.h"
void *igVertexArray2__FindVertexData();
extern int DAT_005610b8[4];
void Gap__Core__igVertexArray2Helper__vfunc_37(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    int temp_v1;
    void *temp_v1_2;
    igVec3fList *var_s1;

    var_s1 = (igVec3fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData(arg0->_vertexArray, 8, 0))->_data), DAT_005610b8);
    temp_v1 = var_s1->_count;
    if ((temp_v1 != 0) && (arg1 >= 0) && (arg1 < temp_v1)) {
        temp_v1_2 = (void *)(var_s1->_data + (arg1 * 0xC));
        *(float *)((char *)(temp_v1_2) + 0) = (float) *(float *)((char *)(arg2) + 0);
        *(float *)((char *)(temp_v1_2) + 4) = (float) *(float *)((char *)(arg2) + 4);
        *(float *)((char *)(temp_v1_2) + 8) = (float) *(float *)((char *)(arg2) + 8);
    }
}

#include "dw4/reflected.h"
extern "C" {
void *igVertexArray2__FindVertexData(...);
int igObject_IsKindOf(...);
extern int DAT_005610c8[4];
int Gap__Core__igVertexArray2Helper__vfunc_50(igVertexArray2Helper *arg0, int arg1, int arg2) {
    char *var_s0; char *p;
    var_s0 = (char *)(*(int *)((char *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 4, arg1)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610c8[0]) != 0)) {
        p = var_s0;
    } else {
        p = 0;
    }
    return *(int *)(p + 16) + (arg2 * 8);
}
}

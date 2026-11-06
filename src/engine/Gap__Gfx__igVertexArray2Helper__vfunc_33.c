#include "dw4/reflected.h"
void *igVertexArray2__FindVertexData();
int igObject_IsKindOf();
extern int DAT_005610b8[4];
int Gap__Gfx__igVertexArray2Helper__vfunc_33(igVertexArray2Helper *arg0, int arg1) {
    void *var_s0;
    void *r;
    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 3, 0)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, DAT_005610b8[0]) != 0)) {
        r = var_s0;
    } else {
        r = (void *)(0);
    }
    return *(int *)((char *)(r) + 16) + (arg1 * 0xC);
}

#include "dw4/reflected.h"

float Gap__Gfx__igPsx2VertexArray1_1__vfunc_58(igPsx2VertexArray1_1 *arg0, int arg1) {
    float var_f0;

    var_f0 = *(float *)(*(int *)((char *)(arg0->_vdata) + 76) + (arg1 * 4));
    if (!(var_f0 <= 1.5707964f) && (var_f0 <= 4.712389f)) {
        return 4.712389f - (var_f0 - 1.5707964f);
    }
    if (var_f0 < 0.0f) {
        var_f0 += 6.2831855f;
    }
    return var_f0;
}

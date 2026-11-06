#include "dw4/reflected.h"
extern float GPR_005548cc;
extern float GPR_005548d0;
extern float GPR_005548d4;

float Gap__Gfx__igPsx2VertexArray1_1__vfunc_58(igPsx2VertexArray1_1 *arg0, int arg1) {
    float var_f0;

    var_f0 = *(float *)(*(int *)((char *)(arg0->_vdata) + 76) + (arg1 * 4));
    if (!(var_f0 <= GPR_005548cc) && (var_f0 <= GPR_005548d0)) {
        return GPR_005548d0 - (var_f0 - GPR_005548cc);
    }
    if (var_f0 < 0.0f) {
        var_f0 += GPR_005548d4;
    }
    return var_f0;
}

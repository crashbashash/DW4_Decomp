/* Comparison written with the local on the left so the slt result stays in at; verified by tools/verify.py. */
#include "dw4/reflected.h"
extern "C" {
float FUN_003a7810();
int FUN_003a79a0(beCriVolume *arg0);
}

int FUN_003a79a0(beCriVolume *arg0) {
    float temp_f20;
    int var_v0;

    temp_f20 = arg0->_end;
    var_v0 = (int)((int) (127.0f * FUN_003a7810()));
    if (var_v0 <= (int) (127.0f * temp_f20)) {
        arg0->_isExec = 0;
        if (temp_f20 == 0.0f) {
            var_v0 = 0;
        }
    }
    return var_v0;
}

/* 0x001715a0 — FUN_001715a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_001715a0(igPsx2VisualContext *arg0, int arg1, float *arg2) {
    float *temp_v1;

    temp_v1 = (float *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    arg2[0] = temp_v1[0];
    arg2[1] = temp_v1[1];
    arg2[2] = temp_v1[2];
}

/* 0x001714e0 — FUN_001714e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_001714e0(igPsx2VisualContext *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 32);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 36);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 40);
    *(float *)((char *)(arg2) + 12) = (float) *(float *)((char *)(temp_v1) + 44);
}

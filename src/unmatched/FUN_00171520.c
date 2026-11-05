/* 0x00171520 — FUN_00171520. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_00171520(igPsx2VisualContext *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0->_pLightList) + 16) + (arg1 * 0xA0));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 16);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 20);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 24);
    *(float *)((char *)(arg2) + 12) = (float) *(float *)((char *)(temp_v1) + 28);
}

/* 0x001719e0 — FUN_001719e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_001719e0(igPsx2VisualContext *arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = (void *)arg0->_currentMaterial;
    *(float *)((char *)(arg1) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg1) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
    *(float *)((char *)(arg1) + 8) = (float) *(float *)((char *)(temp_v1) + 8);
    *(float *)((char *)(arg1) + 12) = (float) *(float *)((char *)(temp_v1) + 12);
}

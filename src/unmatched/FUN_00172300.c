/* 0x00172300 — FUN_00172300. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_00172300(igPsx2VisualContext *arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = (void *)(arg0->_currentMaterial);
    *(float *)((char *)(arg1) + 0) = (float) *(float *)((char *)(temp_v1) + 88);
    *(float *)((char *)(arg1) + 4) = (float) *(float *)((char *)(temp_v1) + 92);
    *(float *)((char *)(arg1) + 8) = (float) *(float *)((char *)(temp_v1) + 96);
    *(float *)((char *)(arg1) + 12) = (float) *(float *)((char *)(temp_v1) + 100);
}

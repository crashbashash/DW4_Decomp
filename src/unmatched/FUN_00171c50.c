/* 0x00171c50 — FUN_00171c50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_00171c50(igPsx2VisualContext *arg0, void *arg1) {
    igMaterialAttr *temp_v1;

    temp_v1 = (igMaterialAttr *)arg0->_currentMaterial;
    *(float *)((char *)(arg1) + 0) = (float) *(float *)&temp_v1->_ambient[0];
    *(float *)((char *)(arg1) + 4) = (float) *(float *)&temp_v1->_ambient[1];
    *(float *)((char *)(arg1) + 8) = (float) *(float *)&temp_v1->_ambient[2];
    *(float *)((char *)(arg1) + 12) = (float) *(float *)&temp_v1->_ambient[3];
}

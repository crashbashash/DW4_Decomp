/* 0x00171870 — FUN_00171870. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
void FUN_00171870(igPsx2VisualContext *arg0, void *arg1) {
    igMaterialAttr *temp_v1;

    temp_v1 = (igMaterialAttr *)arg0->_currentMaterial;
    *(float *)((char *)(arg1) + 0) = (float) *(float *)&temp_v1->_diffuse[0];
    *(float *)((char *)(arg1) + 4) = (float) *(float *)&temp_v1->_diffuse[1];
    *(float *)((char *)(arg1) + 8) = (float) *(float *)&temp_v1->_diffuse[2];
    *(float *)((char *)(arg1) + 12) = (float) *(float *)&temp_v1->_diffuse[3];
}

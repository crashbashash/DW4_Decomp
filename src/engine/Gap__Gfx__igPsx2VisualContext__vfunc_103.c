#include "dw4/reflected.h"
void Gap__Gfx__igPsx2VisualContext__vfunc_103(igPsx2VisualContext *arg0, void *arg1) {
    igMaterialAttr *temp_v1;

    temp_v1 = (igMaterialAttr *)arg0->_currentMaterial;
    *(float *)((char *)(arg1) + 0) = (float) *(float *)&temp_v1->_diffuse[0];
    *(float *)((char *)(arg1) + 4) = (float) *(float *)&temp_v1->_diffuse[1];
    *(float *)((char *)(arg1) + 8) = (float) *(float *)&temp_v1->_diffuse[2];
    *(float *)((char *)(arg1) + 12) = (float) *(float *)&temp_v1->_diffuse[3];
}

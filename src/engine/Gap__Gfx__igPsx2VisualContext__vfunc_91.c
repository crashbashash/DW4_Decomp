#include "dw4/reflected.h"
void Gap__Gfx__igPsx2VisualContext__vfunc_91(igPsx2VisualContext *arg0, int arg1, float *arg2) {
    igLightAttr *temp_v1;

    temp_v1 = (igLightAttr *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    arg2[0] = (float) *(float *)&temp_v1->_specular[0];
    arg2[1] = (float) *(float *)&temp_v1->_specular[1];
    arg2[2] = (float) *(float *)&temp_v1->_specular[2];
}

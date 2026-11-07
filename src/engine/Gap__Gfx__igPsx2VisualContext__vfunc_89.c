#include "dw4/reflected.h"
void Gap__Gfx__igPsx2VisualContext__vfunc_89(igPsx2VisualContext *arg0, int arg1, float *arg2) {
    float *temp_v1;

    temp_v1 = (float *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    arg2[0] = temp_v1[0];
    arg2[1] = temp_v1[1];
    arg2[2] = temp_v1[2];
}

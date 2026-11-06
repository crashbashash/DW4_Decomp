#include "dw4/reflected.h"
/* The reflected metadata types _diffuse as int[4], but the code reads floats. */
void FUN_00171560(igPsx2VisualContext *arg0, int arg1, float *arg2) {
    igLightAttr *temp_v1;

    temp_v1 = (igLightAttr *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    arg2[0] = *(float *)&temp_v1->_diffuse[0];
    arg2[1] = *(float *)&temp_v1->_diffuse[1];
    arg2[2] = *(float *)&temp_v1->_diffuse[2];
    arg2[3] = *(float *)&temp_v1->_diffuse[3];
}

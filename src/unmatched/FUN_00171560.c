#include "dw4/reflected.h"
/* Receiver igPsx2VisualContext (only class with a 4-byte ref at +1336, _pLightList -> igLightList,
 * _data +16, 0xA0-byte igLightAttr entries, _diffuse +48). The metadata types _diffuse as int[4];
 * the code reads floats. */
void FUN_00171560(igPsx2VisualContext *arg0, int arg1, float *arg2) {
    igLightAttr *temp_v1;

    temp_v1 = (igLightAttr *)(((igLightList *)arg0->_pLightList)->_data + (arg1 * 0xA0));
    arg2[0] = *(float *)&temp_v1->_diffuse[0];
    arg2[1] = *(float *)&temp_v1->_diffuse[1];
    arg2[2] = *(float *)&temp_v1->_diffuse[2];
    arg2[3] = *(float *)&temp_v1->_diffuse[3];
}

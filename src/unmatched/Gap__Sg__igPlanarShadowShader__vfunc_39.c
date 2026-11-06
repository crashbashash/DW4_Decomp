#include "dw4/reflected.h"
int ObjectList_AppendRetained();

void Gap__Sg__igPlanarShadowShader__vfunc_39(igPlanarShadowShader *arg0, int dummy1, int arg2, int arg3) {
    ObjectList_AppendRetained(arg0->_geoms);
    ObjectList_AppendRetained(arg0->_mats, arg2);
    ObjectList_AppendRetained(arg0->_blendmats, arg3);
}

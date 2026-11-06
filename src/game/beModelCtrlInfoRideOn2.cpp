/* C++ with exceptions on; the C-ABI names stay unmangled through this block. */
#include "dw4/reflected.h"
extern "C" {
extern int g_beModelCtrlInfoRideOn2_metaObject[4];
void Matrix44_SetTranslation(float *matrix, void *vec3);
/* Block of zero floats in the data segment (0.0f; other code reads its first word as a scalar 0.0f). */
extern int g_vec3Zero[4];
void Gap__Bec__beModelCtrlInfoRideOn2__vfunc_21(beModelCtrlInfoRideOn2 *self);
int Gap__Bec__beModelCtrlInfoRideOn2__vfunc_20(void);
}

/* Resets the ride-on pose: clears the translation of `_oldMatrix` to (0,0,0) and writes `_vector`
 * into the translation of the model node's matrix (+0x20 of a node, the igTransform `_m` offset).
 * Matrix44_SetTranslation copies vec3 into matrix words 12..14. */
void Gap__Bec__beModelCtrlInfoRideOn2__vfunc_21(beModelCtrlInfoRideOn2 *self) {
    Matrix44_SetTranslation(self->_oldMatrix, &g_vec3Zero[0]);
    Matrix44_SetTranslation((float *)(self->_modelNode + 0x20), &self->_vector);
}

int Gap__Bec__beModelCtrlInfoRideOn2__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn2_metaObject[0];
}

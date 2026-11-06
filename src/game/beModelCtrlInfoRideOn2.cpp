/* src/game/beModelCtrlInfoRideOn2.cpp — the beModelCtrlInfoRideOn2 methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time.  C++ with exceptions on (retail keeps an
 * exception index record for slot 21); the C-ABI names stay unmangled
 * through the extern "C" block. */
#include "dw4/reflected.h"
extern "C" {
extern int g_beModelCtrlInfoRideOn2_metaObject[4];
/* Matrix44_SetTranslation(matrix, vec3): copies the three floats of vec3 into the matrix translation row. */
void Matrix44_SetTranslation(float *matrix, void *vec3);
/* Block of zero floats in the data segment (0.0f; other code reads its first word as a scalar 0.0f). */
extern int g_vec3Zero[4];
void Gap__Bec__beModelCtrlInfoRideOn2__vfunc_21(beModelCtrlInfoRideOn2 *self);
int Gap__Bec__beModelCtrlInfoRideOn2__vfunc_20(void);
}

/* Reset the ride-on pose: clear the translation of `_oldMatrix` to (0,0,0) and write `_vector`
 * into the translation of the model node's matrix (+0x20 of a node, the igTransform `_m` offset).
 * Matrix44_SetTranslation(matrix, vec3) copies vec3 into matrix words 12..14
 * (asm/Matrix44_SetTranslation.s: stores at +48/+52/+56). */
void Gap__Bec__beModelCtrlInfoRideOn2__vfunc_21(beModelCtrlInfoRideOn2 *self) {
    Matrix44_SetTranslation(self->_oldMatrix, &g_vec3Zero[0]);
    Matrix44_SetTranslation((float *)(self->_modelNode + 0x20), &self->_vector);
}

/* 0x00398e30 */
int Gap__Bec__beModelCtrlInfoRideOn2__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn2_metaObject[0];
}

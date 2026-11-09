#include "dw4/reflected.h"

extern float DAT_004e1170[4];
extern float DAT_004e1180[4];
static inline void clampColor(float *c, const float *lo, const float *hi) {
    if (c[0] < lo[0]) c[0] = lo[0];
    if (c[1] < lo[1]) c[1] = lo[1];
    if (c[2] < lo[2]) c[2] = lo[2];
    if (c[3] < lo[3]) c[3] = lo[3];
    if (!(c[0] <= hi[0])) c[0] = hi[0];
    if (!(c[1] <= hi[1])) c[1] = hi[1];
    if (!(c[2] <= hi[2])) c[2] = hi[2];
    if (!(c[3] <= hi[3])) c[3] = hi[3];
}
void Gap__Attrs__igMaterialAttr__vfunc_35(igMaterialAttr *material, const float *color) {
    material->_ambient[0] = color[0];
    material->_ambient[1] = color[1];
    material->_ambient[2] = color[2];
    material->_ambient[3] = color[3];
    clampColor(material->_ambient, DAT_004e1170, DAT_004e1180);
}

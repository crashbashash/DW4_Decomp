#include "dw4/reflected.h"
int FUN_0018cf20(igPlane *plane, igSphere *sphere) {
    float radius = sphere->_radius; float d; int r; if (radius < 0.0f) return 0; d = plane->_norm[0] * sphere->_center[0] + plane->_norm[1] * sphere->_center[1] + plane->_norm[2] * sphere->_center[2] - plane->_offset; if (d <= -radius) r = 2; else if (d <= radius) r = 1; else r = 0; return r;
}

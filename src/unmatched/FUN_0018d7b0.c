#include "dw4/reflected.h"
int FUN_0018d7b0(igSphere *sphere, igPlane *plane) {
    float radius = sphere->_radius; if (radius < 0.0f) return 0; if (0.0f <= radius + plane->_offset - (sphere->_center[0] * plane->_norm[0] + sphere->_center[1] * plane->_norm[1] + sphere->_center[2] * plane->_norm[2])) return 1; return 0;
}

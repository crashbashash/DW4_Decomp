#include "dw4/reflected.h"
/* matching construct: declaration-order sweep — dy, dx, dz order */
int FUN_0018dcb0(igSphere *sphere, float *point) {
    float radius = sphere->_radius;
    if (radius < 0.0f) {
        return 0;
    }
    {
        float dy = sphere->_center[1] - point[1]; float dx = sphere->_center[0] - point[0]; float dz = sphere->_center[2] - point[2];
        if (dx * dx + dy * dy + dz * dz <= radius * radius) {
            return 2;
        }
        return 0;
    }
}

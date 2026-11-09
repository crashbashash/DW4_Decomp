#include "dw4/reflected.h"

/* matching construct: declaration-order sweep — dy, dx, dz order */
int FUN_0018d820(igSphere *a, igSphere *b) {
    if (a->_radius < 0.0f || b->_radius < 0.0f) {
        return 0;
    }
    {
        float r = a->_radius + b->_radius;
        float dy = a->_center[1] - b->_center[1];
        float dx = a->_center[0] - b->_center[0];
        float dz = a->_center[2] - b->_center[2];
        if (dx * dx + dy * dy + dz * dz <= r * r) {
            return 1;
        }
        return 0;
    }
}

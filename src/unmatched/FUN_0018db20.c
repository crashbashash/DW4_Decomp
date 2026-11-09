#include "dw4/reflected.h"

/* matching construct: declaration-order sweep — dy, dx, dz, distSq order */
int FUN_0018db20(igSphere *a, igSphere *b) {
    if (a->_radius < 0.0f) {
        return 0;
    }
    {
        float dy = a->_center[1] - b->_center[1]; float dx = a->_center[0] - b->_center[0]; float dz = a->_center[2] - b->_center[2]; float distSq;
        distSq = dx * dx + dy * dy + dz * dz;
        if (b->_radius <= a->_radius && distSq <= (a->_radius - b->_radius) * (a->_radius - b->_radius)) {
            return 2;
        }
        if (distSq <= (a->_radius + b->_radius) * (a->_radius + b->_radius)) {
            return 1;
        }
        return 0;
    }
}

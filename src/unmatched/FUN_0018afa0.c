#include "dw4/reflected.h"

int FUN_0018afa0(igAABox *box, igSphere *sphere) {
    float dist;
    int i;
    if (!(box->_min[0] <= box->_max[0]) || sphere->_radius < 0.0f) {
        return 0;
    }
    dist = 0.0f;
    for (i = 0; i < 3; i++) {
        float lo = box->_min[i];
        float c = sphere->_center[i];
        if (c < lo) {
            float s = c - lo;
            dist += s * s;
        } else if (box->_max[i] < c) {
            float s = c - box->_max[i];
            dist += s * s;
        }
    }
    if (dist <= sphere->_radius * sphere->_radius) {
        return 1;
    }
    return 0;
}

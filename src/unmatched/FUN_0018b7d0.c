#include "dw4/reflected.h"

void FUN_0018b7d0(igAABox *box, igSphere *sphere) {
    float radius;
    float low[3];
    float high[3];

    radius = sphere->_radius;
    if (radius < 0.0f) {
        return;
    }
    low[0] = sphere->_center[0] - radius;
    low[1] = sphere->_center[1] - radius;
    low[2] = sphere->_center[2] - radius;
    high[0] = sphere->_center[0] + radius;
    high[1] = sphere->_center[1] + radius;
    high[2] = sphere->_center[2] + radius;
    if (!(box->_min[0] <= low[0])) box->_min[0] = low[0];
    if (!(box->_min[1] <= low[1])) box->_min[1] = low[1];
    if (!(box->_min[2] <= low[2])) box->_min[2] = low[2];
    if (box->_max[0] < high[0]) box->_max[0] = high[0];
    if (box->_max[1] < high[1]) box->_max[1] = high[1];
    if (box->_max[2] < high[2]) box->_max[2] = high[2];
}

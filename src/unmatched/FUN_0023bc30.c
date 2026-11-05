/* 0x0023bc30 — FUN_0023bc30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver is igCollisionGroup (_bound -> igSphere; position/lastPosition/
 * collisionPosition/radius are initialised from the bound sphere). */
#include "dw4/reflected.h"
void FUN_0023bc30(igCollisionGroup *arg0) {
    igSphere *temp_v1;

    *(int *)&arg0->_time = 0xBF800000;
    temp_v1 = (igSphere *)arg0->_bound;
    *(float *)&arg0->_position[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_position[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_position[2] = (float) *(float *)&temp_v1->_center[2];
    *(float *)&arg0->_lastPosition[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_lastPosition[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_lastPosition[2] = (float) *(float *)&temp_v1->_center[2];
    *(float *)&arg0->_collisionPosition[0] = (float) *(float *)&temp_v1->_center[0];
    *(float *)&arg0->_collisionPosition[1] = (float) *(float *)&temp_v1->_center[1];
    *(float *)&arg0->_collisionPosition[2] = (float) *(float *)&temp_v1->_center[2];
    arg0->_radius = (float) temp_v1->_radius;
}

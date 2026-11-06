/* Float store, then a second store of -inf on the other path. */
#include "dw4/reflected.h"
void Gap__Gfx__igPsx2ParticleArray__vfunc_34(igPsx2ParticleArray *arg0, float fp) {
    arg0->_particleLifeStart = fp;
    if (arg0->_timeControlState & 2) {
        *(float *)(arg0->_ps2ParticleFormat + 24) = fp;
        return;
    }
    *(int *)(arg0->_ps2ParticleFormat + 24) = 0xFF800000;
}

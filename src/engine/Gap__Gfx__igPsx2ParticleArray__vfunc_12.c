/* IgPsx2ParticleArray vfunc 12: release the PS2 particle buffer. Frees the raw PS2-format particle
 * block (_ps2ParticleFormat) if one was built. A synchronised array (_bSynchronize) first calls
 * FUN_001f05a0 with its _lSequence number (a wait loop on a semaphore until the 64-bit counter at
 * index 1 of a global table reaches that number). The shared ParticleArray teardown (vfunc 10:
 * frees _particleArray, drops the point-sprite vertex array) then runs unconditionally. */
#include "dw4/reflected.h"

int FUN_001f05a0();
int Memory_FreeBuffer();
int Gap__Bec__ParticleArray__vfunc_10();

void Gap__Gfx__igPsx2ParticleArray__vfunc_12(igPsx2ParticleArray *self) {
    long long sequence;

    if (self->_ps2ParticleFormat != 0) {
        if (self->_bSynchronize != 0) {
            sequence = self->_lSequence;
            if (sequence != 0) {
                FUN_001f05a0(1, sequence);
            }
        }
        Memory_FreeBuffer(self->_ps2ParticleFormat);
    }
    Gap__Bec__ParticleArray__vfunc_10(self);
}

#include "dw4/reflected.h"
class ParticleArrayCalls {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual void configure(float lifeStart, int format, float lifeEnd, unsigned int maxNum, void *context);
};
extern "C" {
int Gap__Gfx__igParticleArray__vfunc_28(igPsx2ParticleArray *self, float time, unsigned int num, unsigned int offset, int *status);
void *FUN_00166d40(igPsx2ParticleArray *self);
extern unsigned long long DAT_00560668;
extern unsigned char DAT_00554b68;
int Gap__Gfx__igPsx2ParticleArray__vfunc_28(igPsx2ParticleArray *self, float time, unsigned int num, unsigned int offset, int *status);
}
int Gap__Gfx__igPsx2ParticleArray__vfunc_28(igPsx2ParticleArray *self, float time, unsigned int num, unsigned int offset, int *status) {
    void *context;

    if (!self->_hardwareSupport) {
        return Gap__Gfx__igParticleArray__vfunc_28(self, time, num, offset, status);
    }
    self->_currentTime = time;
    if (!(time <= self->_particleLifeEnd + self->_particleLifetimeEndOffset)) {
        *status = 1;
        return 1;
    }
    if (time < self->_particleLifeStart) {
        *status = 2;
        return 1;
    }
    DAT_00560668++;
    self->_particleNum = num;
    self->_particleOffset = offset;
    if (self->_context == 0) {
        context = FUN_00166d40(self);
        if (context != 0) {
            ((ParticleArrayCalls *)self)->configure(self->_particleLifeStart, self->_particleFormat, self->_particleLifeEnd, self->_maxNum, context);
            *status = 0;
        } else {
            *status = 1;
            return 0;
        }
    } else {
        *status = 0;
    }
    if (DAT_00554b68) {
        *status = 1;
        self->_currentTime = 1.0f + self->_particleLifeEnd;
    }
    return 1;
}

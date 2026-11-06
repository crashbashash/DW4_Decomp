#include "dw4/reflected.h"
extern int g_ParticleArray_metaObject[4];

int Gap__Bec__ParticleArray__vfunc_30(ParticleArray *p)
{
    return p->_particleFormat;
}

int Gap__Bec__ParticleArray__vfunc_29(ParticleArray *p)
{
    return p->_maxNum;
}

void Gap__Bec__ParticleArray__vfunc_37(ParticleArray *a0, int a1)
{
    a0->_timeControlState = a1;
}

int Gap__Bec__ParticleArray__vfunc_20(void)
{
    return g_ParticleArray_metaObject[0];
}

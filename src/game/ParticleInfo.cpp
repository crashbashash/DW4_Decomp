/* ParticleInfo methods: the metaobject accessor and the control-data reset. */
#include "dw4/reflected.h"
extern "C" {
extern int g_ParticleInfo_metaObject[4];
int memset(int, int, int);  /* memset(dst, byte, size); returns dst */
int Gap__Core__igObject__vfunc_11();
int Gap__Bec__ParticleInfo__vfunc_20(void);
void Gap__Bec__ParticleInfo__vfunc_11(ParticleInfo *self, int clearControls);
}

int Gap__Bec__ParticleInfo__vfunc_20(void)
{
    return g_ParticleInfo_metaObject[0];
}

/* Runs the igObject base step, then (when `clearControls` is set) zeroes the particle control
 * data: `_points` (192 words) and `_numControls` (32 words). */
void Gap__Bec__ParticleInfo__vfunc_11(ParticleInfo *self, int clearControls) {
    Gap__Core__igObject__vfunc_11();
    if (clearControls != 0) {
        memset((int)self->_points, 0, sizeof(self->_points));
        memset((int)self->_numControls, 0, sizeof(self->_numControls));
    }
}

/* ParticleInfo methods (Gap::Bec::ParticleInfo): name lookup, the metaobject
 * accessor and the control-data reset.  Field layout comes from the reflected
 * ParticleInfo in include/dw4/reflected.h.  Functions are in retail address order. */
#include "dw4/reflected.h"
extern "C" {
extern int g_ParticleInfo_metaObject_0058a0e0[4];
int igStrCmp(int, int);
int igObject_GetFieldValueByName(void *, int);  /* reflected-field lookup by name (see vfunc_22) */
int memset(int, int, int);  /* memset(dst, byte, size); returns dst */
int Gap__Core__igObject__vfunc_11();
int Gap__Bec__ParticleInfo__vfunc_22(ParticleInfo *self, int name);
int Gap__Bec__ParticleInfo__vfunc_20(void);
void Gap__Bec__ParticleInfo__vfunc_11(ParticleInfo *self, int clearControls);
}

/* 0x001d63c0
 * Name lookup: the info's own name resolves to its scene graph; any other
 * name falls through to igObject_GetFieldValueByName, which finds the reflected field of that
 * name (igMetaObject_FindFieldByName) and returns its value in this object. */
int Gap__Bec__ParticleInfo__vfunc_22(ParticleInfo *self, int name) {
    if (igStrCmp(name, self->_name) == 0) {
        return self->_sceneGraph;
    }
    return igObject_GetFieldValueByName(self, name);
}

/* 0x0036edd0 */
int Gap__Bec__ParticleInfo__vfunc_20(void)
{
    return g_ParticleInfo_metaObject_0058a0e0[0];
}

/* 0x0036ede0
 * Run the igObject base step, then (when `clearControls` is set) zero the
 * particle control data: `_points` (192 words) and `_numControls` (32 words). */
void Gap__Bec__ParticleInfo__vfunc_11(ParticleInfo *self, int clearControls) {
    Gap__Core__igObject__vfunc_11();
    if (clearControls != 0) {
        memset((int)self->_points, 0, sizeof(self->_points));
        memset((int)self->_numControls, 0, sizeof(self->_numControls));
    }
}

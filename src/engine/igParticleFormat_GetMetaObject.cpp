#include "dw4/reflected.h"
extern igMetaObject *g_igParticleFormat_metaObject[4];
extern "C" {
void FUN_0014d190(void);
igMetaObject *igParticleFormat_GetMetaObject(void);
}
igMetaObject *igParticleFormat_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleFormat_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014d190();
    return g_igParticleFormat_metaObject[0];
}

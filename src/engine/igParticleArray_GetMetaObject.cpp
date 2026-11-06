#include "dw4/reflected.h"
extern igMetaObject *g_igParticleArray_metaObject[4];
extern "C" {
void FUN_0014cd90(void);
igMetaObject *igParticleArray_GetMetaObject(void);
}
igMetaObject *igParticleArray_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleArray_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014cd90();
    return g_igParticleArray_metaObject[0];
}

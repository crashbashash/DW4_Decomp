#include "dw4/reflected.h"
extern igMetaObject *g_igParticleArray_metaObject[4];
extern "C" {
void FUN_0014cd90(void);
igMetaObject *igParticleArray_GetMetaObject(void);
}
igMetaObject *igParticleArray_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014cd90();
    return g_igParticleArray_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2ParticleArray_metaObject[4];
extern "C" {
void FUN_00153460(void);
igMetaObject *igPsx2ParticleArray_GetMetaObject(void);
}
igMetaObject *igPsx2ParticleArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ParticleArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153460();
    return g_igPsx2ParticleArray_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2ParticleArray_metaObject[4];
extern "C" {
void FUN_00153460(void);
igMetaObject *igPsx2ParticleArray_GetMetaObject(void);
}
igMetaObject *igPsx2ParticleArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ParticleArray_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00153460();
    return g_igPsx2ParticleArray_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igParticleAttr_metaObject[4];
extern "C" {
void FUN_00134e50(void);
igMetaObject *igParticleAttr_GetMetaObject(void);
}
igMetaObject *igParticleAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00134e50();
    return g_igParticleAttr_metaObject[0];
}

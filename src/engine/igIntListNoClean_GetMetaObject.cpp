#include "dw4/reflected.h"
extern igMetaObject *g_igIntListNoClean_metaObject[4];
extern "C" {
void FUN_002ca9d0(void);
igMetaObject *igIntListNoClean_GetMetaObject(void);
}
igMetaObject *igIntListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igIntListNoClean_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002ca9d0();
    return g_igIntListNoClean_metaObject[0];
}

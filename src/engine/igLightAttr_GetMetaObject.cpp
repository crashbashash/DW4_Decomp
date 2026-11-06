#include "dw4/reflected.h"
extern igMetaObject *g_igLightAttr_metaObject[4];
extern "C" {
void FUN_00136880(void);
igMetaObject *igLightAttr_GetMetaObject(void);
}
igMetaObject *igLightAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00136880();
    return g_igLightAttr_metaObject[0];
}

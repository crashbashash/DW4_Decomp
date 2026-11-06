#include "dw4/reflected.h"
extern igMetaObject *g_igLightSet_metaObject[4];
extern "C" {
void FUN_0019dcd0(void);
igMetaObject *igLightSet_GetMetaObject(void);
}
igMetaObject *igLightSet_GetMetaObject(void)
{
    igMetaObject *g = g_igLightSet_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019dcd0();
    return g_igLightSet_metaObject[0];
}

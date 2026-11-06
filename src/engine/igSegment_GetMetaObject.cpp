#include "dw4/reflected.h"
extern igMetaObject *g_igSegment_metaObject[4];
extern "C" {
void FUN_0019ae10(void);
igMetaObject *igSegment_GetMetaObject(void);
}
igMetaObject *igSegment_GetMetaObject(void)
{
    igMetaObject *g = g_igSegment_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019ae10();
    return g_igSegment_metaObject[0];
}

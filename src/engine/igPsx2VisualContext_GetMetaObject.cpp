#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2VisualContext_metaObject[4];
extern "C" {
void FUN_001511a0(void);
igMetaObject *igPsx2VisualContext_GetMetaObject(void);
}
igMetaObject *igPsx2VisualContext_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2VisualContext_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001511a0();
    return g_igPsx2VisualContext_metaObject[0];
}

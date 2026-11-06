#include "dw4/reflected.h"
extern igMetaObject *g_igVisualAttribute_metaObject[4];
extern "C" {
void FUN_001303b0(void);
igMetaObject *igVisualAttribute_GetMetaObject(void);
}
igMetaObject *igVisualAttribute_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualAttribute_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001303b0();
    return g_igVisualAttribute_metaObject[0];
}

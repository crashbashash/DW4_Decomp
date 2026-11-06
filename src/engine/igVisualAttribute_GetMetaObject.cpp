#include "dw4/reflected.h"
extern igMetaObject *g_igVisualAttribute_metaObject[4];
extern "C" {
void FUN_001303b0(void);
igMetaObject *igVisualAttribute_GetMetaObject(void);
}
igMetaObject *igVisualAttribute_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualAttribute_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001303b0();
    return g_igVisualAttribute_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igVisualContextAttrDefaultManager_metaObject[4];
extern "C" {
void FUN_001301c0(void);
igMetaObject *igVisualContextAttrDefaultManager_GetMetaObject(void);
}
igMetaObject *igVisualContextAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextAttrDefaultManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001301c0();
    return g_igVisualContextAttrDefaultManager_metaObject[0];
}

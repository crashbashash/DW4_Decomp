#include "dw4/reflected.h"
extern igMetaObject *g_igFloatList_metaObject[4];
extern "C" {
void FUN_002c9860(void);
igMetaObject *igFloatList_GetMetaObject(void);
}
igMetaObject *igFloatList_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c9860();
    return g_igFloatList_metaObject[0];
}

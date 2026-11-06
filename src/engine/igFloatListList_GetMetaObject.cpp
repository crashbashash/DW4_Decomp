#include "dw4/reflected.h"
extern igMetaObject *g_igFloatListList_metaObject[4];
extern "C" {
void FUN_002c96b0(void);
igMetaObject *igFloatListList_GetMetaObject(void);
}
igMetaObject *igFloatListList_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatListList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c96b0();
    return g_igFloatListList_metaObject[0];
}

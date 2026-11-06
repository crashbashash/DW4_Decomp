#include "dw4/reflected.h"
extern igMetaObject *g_igRayList_metaObject[4];
extern "C" {
void FUN_00188190(void);
igMetaObject *igRayList_GetMetaObject(void);
}
igMetaObject *igRayList_GetMetaObject(void)
{
    igMetaObject *g = g_igRayList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00188190();
    return g_igRayList_metaObject[0];
}

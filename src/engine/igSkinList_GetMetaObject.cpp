#include "dw4/reflected.h"
extern igMetaObject *g_igSkinList_metaObject[4];
extern "C" {
void FUN_00197f40(void);
igMetaObject *igSkinList_GetMetaObject(void);
}
igMetaObject *igSkinList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkinList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00197f40();
    return g_igSkinList_metaObject[0];
}

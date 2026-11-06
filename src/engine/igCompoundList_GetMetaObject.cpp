#include "dw4/reflected.h"
extern igMetaObject *g_igCompoundList_metaObject[4];
extern "C" {
void FUN_00225900(void);
igMetaObject *igCompoundList_GetMetaObject(void);
}
igMetaObject *igCompoundList_GetMetaObject(void)
{
    igMetaObject *g = g_igCompoundList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00225900();
    return g_igCompoundList_metaObject[0];
}

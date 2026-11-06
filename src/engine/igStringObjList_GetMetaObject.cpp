#include "dw4/reflected.h"
extern igMetaObject *g_igStringObjList_metaObject[4];
extern "C" {
void FUN_002b9470(void);
igMetaObject *igStringObjList_GetMetaObject(void);
}
igMetaObject *igStringObjList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringObjList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b9470();
    return g_igStringObjList_metaObject[0];
}

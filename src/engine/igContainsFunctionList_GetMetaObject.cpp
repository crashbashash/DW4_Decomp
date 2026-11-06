#include "dw4/reflected.h"
extern igMetaObject *g_igContainsFunctionList_metaObject[4];
extern "C" {
void FUN_00189650(void);
igMetaObject *igContainsFunctionList_GetMetaObject(void);
}
igMetaObject *igContainsFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189650();
    return g_igContainsFunctionList_metaObject[0];
}

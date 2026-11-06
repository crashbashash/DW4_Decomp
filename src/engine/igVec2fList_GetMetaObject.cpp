#include "dw4/reflected.h"
extern igMetaObject *g_igVec2fList_metaObject[4];
extern "C" {
void FUN_0018a3a0(void);
igMetaObject *igVec2fList_GetMetaObject(void);
}
igMetaObject *igVec2fList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec2fList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0018a3a0();
    return g_igVec2fList_metaObject[0];
}

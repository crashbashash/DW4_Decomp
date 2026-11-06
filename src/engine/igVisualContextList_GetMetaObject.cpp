#include "dw4/reflected.h"
extern igMetaObject *g_igVisualContextList_metaObject[4];
extern "C" {
void FUN_00149f70(void);
igMetaObject *igVisualContextList_GetMetaObject(void);
}
igMetaObject *igVisualContextList_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00149f70();
    return g_igVisualContextList_metaObject[0];
}

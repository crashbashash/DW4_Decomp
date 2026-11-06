#include "dw4/reflected.h"
extern igMetaObject *g_igTransformList_metaObject[4];
extern "C" {
void FUN_00195f50(void);
igMetaObject *igTransformList_GetMetaObject(void);
}
igMetaObject *igTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195f50();
    return g_igTransformList_metaObject[0];
}

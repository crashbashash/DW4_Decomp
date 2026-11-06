#include "dw4/reflected.h"
extern igMetaObject *g_igSearchSceneGraph_metaObject[4];
extern "C" {
void FUN_00238ed0(void);
igMetaObject *igSearchSceneGraph_GetMetaObject(void);
}
igMetaObject *igSearchSceneGraph_GetMetaObject(void)
{
    igMetaObject *g = g_igSearchSceneGraph_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00238ed0();
    return g_igSearchSceneGraph_metaObject[0];
}

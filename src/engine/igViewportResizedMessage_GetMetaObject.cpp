#include "dw4/reflected.h"
extern igMetaObject *g_igViewportResizedMessage_metaObject[4];
extern "C" {
void FUN_00233380(void);
igMetaObject *igViewportResizedMessage_GetMetaObject(void);
}
igMetaObject *igViewportResizedMessage_GetMetaObject(void)
{
    igMetaObject *g = g_igViewportResizedMessage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233380();
    return g_igViewportResizedMessage_metaObject[0];
}

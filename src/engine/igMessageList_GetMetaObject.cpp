#include "dw4/reflected.h"
extern igMetaObject *g_igMessageList_metaObject[4];
extern "C" {
void FUN_00226420(void);
igMetaObject *igMessageList_GetMetaObject(void);
}
igMetaObject *igMessageList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00226420();
    return g_igMessageList_metaObject[0];
}

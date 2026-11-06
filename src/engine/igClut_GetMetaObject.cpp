#include "dw4/reflected.h"
extern igMetaObject *g_igClut_metaObject[4];
extern "C" {
void FUN_0014fb70(void);
igMetaObject *igClut_GetMetaObject(void);
}
igMetaObject *igClut_GetMetaObject(void)
{
    igMetaObject *g = g_igClut_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014fb70();
    return g_igClut_metaObject[0];
}

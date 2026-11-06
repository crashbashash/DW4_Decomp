#include "dw4/reflected.h"
extern igMetaObject *g_igFile_metaObject[4];
extern "C" {
void FUN_002c4d80(void);
igMetaObject *igFile_GetMetaObject(void);
}
igMetaObject *igFile_GetMetaObject(void)
{
    igMetaObject *g = g_igFile_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c4d80();
    return g_igFile_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igElfFile_metaObject[4];
extern "C" {
void FUN_002ced70(void);
igMetaObject *igElfFile_GetMetaObject(void);
}
igMetaObject *igElfFile_GetMetaObject(void)
{
    igMetaObject *g = g_igElfFile_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002ced70();
    return g_igElfFile_metaObject[0];
}

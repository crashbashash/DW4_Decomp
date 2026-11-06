#include "dw4/reflected.h"
extern igMetaObject *g_igShaderProcessor_metaObject[4];
extern "C" {
void FUN_00198c30(void);
igMetaObject *igShaderProcessor_GetMetaObject(void);
}
igMetaObject *igShaderProcessor_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderProcessor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00198c30();
    return g_igShaderProcessor_metaObject[0];
}

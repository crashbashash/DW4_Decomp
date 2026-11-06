#include "dw4/reflected.h"
extern igMetaObject *g_igShaderInfo_metaObject[4];
extern "C" {
void FUN_00198e30(void);
igMetaObject *igShaderInfo_GetMetaObject(void);
}
igMetaObject *igShaderInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderInfo_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00198e30();
    return g_igShaderInfo_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igShaderData_metaObject[4];
extern "C" {
void FUN_00199760(void);
igMetaObject *igShaderData_GetMetaObject(void);
}
igMetaObject *igShaderData_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderData_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00199760();
    return g_igShaderData_metaObject[0];
}

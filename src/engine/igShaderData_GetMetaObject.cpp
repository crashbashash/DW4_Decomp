#include "dw4/reflected.h"
extern igMetaObject *g_igShaderData_metaObject[4];
extern "C" {
void FUN_00199760(void);
igMetaObject *igShaderData_GetMetaObject(void);
}
igMetaObject *igShaderData_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199760();
    return g_igShaderData_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igInterpretedShaderData_metaObject[4];
extern "C" {
void FUN_0019ebc0(void);
igMetaObject *igInterpretedShaderData_GetMetaObject(void);
}
igMetaObject *igInterpretedShaderData_GetMetaObject(void)
{
    igMetaObject *g = g_igInterpretedShaderData_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019ebc0();
    return g_igInterpretedShaderData_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igInterpretedShaderData_metaObject[4];
extern "C" {
void FUN_0019ebc0(void);
igMetaObject *igInterpretedShaderData_GetMetaObject(void);
}
igMetaObject *igInterpretedShaderData_GetMetaObject(void)
{
    igMetaObject *g = g_igInterpretedShaderData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019ebc0();
    return g_igInterpretedShaderData_metaObject[0];
}

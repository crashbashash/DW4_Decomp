#include "dw4/reflected.h"
extern igMetaObject *g_igEnvironmentMapShader2_metaObject[4];
extern "C" {
void FUN_001a15a0(void);
igMetaObject *igEnvironmentMapShader2_GetMetaObject(void);
}
igMetaObject *igEnvironmentMapShader2_GetMetaObject(void)
{
    igMetaObject *g = g_igEnvironmentMapShader2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a15a0();
    return g_igEnvironmentMapShader2_metaObject[0];
}

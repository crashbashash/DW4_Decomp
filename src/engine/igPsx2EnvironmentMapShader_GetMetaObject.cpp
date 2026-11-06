#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2EnvironmentMapShader_metaObject[4];
extern "C" {
void FUN_001ab540(void);
igMetaObject *igPsx2EnvironmentMapShader_GetMetaObject(void);
}
igMetaObject *igPsx2EnvironmentMapShader_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2EnvironmentMapShader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001ab540();
    return g_igPsx2EnvironmentMapShader_metaObject[0];
}

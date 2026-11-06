#include "dw4/reflected.h"
extern igMetaObject *g_igPlanarShadowShader_metaObject[4];
extern "C" {
void FUN_0019c3f0(void);
igMetaObject *igPlanarShadowShader_GetMetaObject(void);
}
igMetaObject *igPlanarShadowShader_GetMetaObject(void)
{
    igMetaObject *g = g_igPlanarShadowShader_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019c3f0();
    return g_igPlanarShadowShader_metaObject[0];
}

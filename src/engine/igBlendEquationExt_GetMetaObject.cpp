#include "dw4/reflected.h"
extern igMetaObject *g_igBlendEquationExt_metaObject[4];
extern "C" {
void FUN_0014ff00(void);
igMetaObject *igBlendEquationExt_GetMetaObject(void);
}
igMetaObject *igBlendEquationExt_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendEquationExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014ff00();
    return g_igBlendEquationExt_metaObject[0];
}

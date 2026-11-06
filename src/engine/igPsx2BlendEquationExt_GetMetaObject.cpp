#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2BlendEquationExt_metaObject[4];
extern "C" {
void FUN_00154710(void);
igMetaObject *igPsx2BlendEquationExt_GetMetaObject(void);
}
igMetaObject *igPsx2BlendEquationExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2BlendEquationExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00154710();
    return g_igPsx2BlendEquationExt_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2BlendEquationExt_metaObject[4];
extern "C" {
void FUN_00154710(void);
igMetaObject *igPsx2BlendEquationExt_GetMetaObject(void);
}
igMetaObject *igPsx2BlendEquationExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2BlendEquationExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00154710();
    return g_igPsx2BlendEquationExt_metaObject[0];
}

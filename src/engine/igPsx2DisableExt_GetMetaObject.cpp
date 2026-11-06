#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2DisableExt_metaObject[4];
extern "C" {
void FUN_00154040(void);
igMetaObject *igPsx2DisableExt_GetMetaObject(void);
}
igMetaObject *igPsx2DisableExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2DisableExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00154040();
    return g_igPsx2DisableExt_metaObject[0];
}

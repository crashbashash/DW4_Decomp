#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2DisableExt_metaObject[4];
extern "C" {
void FUN_00154040(void);
igMetaObject *igPsx2DisableExt_GetMetaObject(void);
}
igMetaObject *igPsx2DisableExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2DisableExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00154040();
    return g_igPsx2DisableExt_metaObject[0];
}

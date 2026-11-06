#include "dw4/reflected.h"
extern igMetaObject *g_igCharListNoClean_metaObject[4];
extern "C" {
void FUN_002cadc0(void);
igMetaObject *igCharListNoClean_GetMetaObject(void);
}
igMetaObject *igCharListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igCharListNoClean_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cadc0();
    return g_igCharListNoClean_metaObject[0];
}

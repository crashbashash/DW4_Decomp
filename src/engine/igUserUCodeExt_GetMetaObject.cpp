#include "dw4/reflected.h"
extern igMetaObject *g_igUserUCodeExt_metaObject[4];
extern "C" {
void FUN_0014bbb0(void);
igMetaObject *igUserUCodeExt_GetMetaObject(void);
}
igMetaObject *igUserUCodeExt_GetMetaObject(void)
{
    igMetaObject *g = g_igUserUCodeExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014bbb0();
    return g_igUserUCodeExt_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igImageConvert_metaObject[4];
extern "C" {
void FUN_0014dbb0(void);
igMetaObject *igImageConvert_GetMetaObject(void);
}
igMetaObject *igImageConvert_GetMetaObject(void)
{
    igMetaObject *g = g_igImageConvert_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014dbb0();
    return g_igImageConvert_metaObject[0];
}

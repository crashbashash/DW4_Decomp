#include "dw4/reflected.h"
extern igMetaObject *g_igGraphPath_metaObject[4];
extern "C" {
void FUN_0019f7a0(void);
igMetaObject *igGraphPath_GetMetaObject(void);
}
igMetaObject *igGraphPath_GetMetaObject(void)
{
    igMetaObject *g = g_igGraphPath_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019f7a0();
    return g_igGraphPath_metaObject[0];
}

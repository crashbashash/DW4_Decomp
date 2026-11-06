#include "dw4/reflected.h"
extern igMetaObject *g_igTimer_metaObject[4];
extern "C" {
void FUN_002b7ab0(void);
igMetaObject *igTimer_GetMetaObject(void);
}
igMetaObject *igTimer_GetMetaObject(void)
{
    igMetaObject *g = g_igTimer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b7ab0();
    return g_igTimer_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igDirectory_metaObject[4];
extern "C" {
void FUN_002c74b0(void);
igMetaObject *igDirectory_GetMetaObject(void);
}
igMetaObject *igDirectory_GetMetaObject(void)
{
    igMetaObject *g = g_igDirectory_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c74b0();
    return g_igDirectory_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igObjectStringMap_metaObject[4];
extern "C" {
void FUN_002bcd30(void);
igMetaObject *igObjectStringMap_GetMetaObject(void);
}
igMetaObject *igObjectStringMap_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectStringMap_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bcd30();
    return g_igObjectStringMap_metaObject[0];
}

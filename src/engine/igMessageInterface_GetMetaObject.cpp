#include "dw4/reflected.h"
extern igMetaObject *g_igMessageInterface_metaObject[4];
extern "C" {
void FUN_00226200(void);
igMetaObject *igMessageInterface_GetMetaObject(void);
}
igMetaObject *igMessageInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226200();
    return g_igMessageInterface_metaObject[0];
}

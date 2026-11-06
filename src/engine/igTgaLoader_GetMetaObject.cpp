#include "dw4/reflected.h"
extern igMetaObject *g_igTgaLoader_metaObject[4];
extern "C" {
void FUN_00150200(void);
igMetaObject *igTgaLoader_GetMetaObject(void);
}
igMetaObject *igTgaLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igTgaLoader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00150200();
    return g_igTgaLoader_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igTgaLoader_metaObject[4];
extern "C" {
void FUN_00150200(void);
igMetaObject *igTgaLoader_GetMetaObject(void);
}
igMetaObject *igTgaLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igTgaLoader_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00150200();
    return g_igTgaLoader_metaObject[0];
}

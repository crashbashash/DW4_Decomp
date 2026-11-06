#include "dw4/reflected.h"
extern igMetaObject *g_igImage_metaObject[4];
extern "C" {
void FUN_0014e050(void);
igMetaObject *igImage_GetMetaObject(void);
}
igMetaObject *igImage_GetMetaObject(void)
{
    igMetaObject *g = g_igImage_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014e050();
    return g_igImage_metaObject[0];
}

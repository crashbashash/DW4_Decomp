#include "dw4/reflected.h"
extern igMetaObject *g_igLod_metaObject[4];
extern "C" {
void FUN_0019d710(void);
igMetaObject *igLod_GetMetaObject(void);
}
igMetaObject *igLod_GetMetaObject(void)
{
    igMetaObject *g = g_igLod_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019d710();
    return g_igLod_metaObject[0];
}

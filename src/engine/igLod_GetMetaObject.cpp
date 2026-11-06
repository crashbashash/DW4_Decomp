#include "dw4/reflected.h"
extern igMetaObject *g_igLod_metaObject[4];
extern "C" {
void FUN_0019d710(void);
igMetaObject *igLod_GetMetaObject(void);
}
igMetaObject *igLod_GetMetaObject(void)
{
    igMetaObject *g = g_igLod_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019d710();
    return g_igLod_metaObject[0];
}

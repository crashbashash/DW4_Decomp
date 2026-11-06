#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionGridHelper_metaObject[4];
extern "C" {
void FUN_00239ee0(void);
igMetaObject *igCollisionGridHelper_GetMetaObject(void);
}
igMetaObject *igCollisionGridHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGridHelper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239ee0();
    return g_igCollisionGridHelper_metaObject[0];
}

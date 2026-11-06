#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionGridHelper_metaObject[4];
extern "C" {
void FUN_00239ee0(void);
igMetaObject *igCollisionGridHelper_GetMetaObject(void);
}
igMetaObject *igCollisionGridHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGridHelper_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00239ee0();
    return g_igCollisionGridHelper_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igActorInfo_metaObject[4];
extern "C" {
void FUN_001aa410(void);
igMetaObject *igActorInfo_GetMetaObject(void);
}
igMetaObject *igActorInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igActorInfo_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001aa410();
    return g_igActorInfo_metaObject[0];
}

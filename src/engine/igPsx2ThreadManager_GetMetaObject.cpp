#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2ThreadManager_metaObject[4];
extern "C" {
void FUN_002cf360(void);
igMetaObject *igPsx2ThreadManager_GetMetaObject(void);
}
igMetaObject *igPsx2ThreadManager_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ThreadManager_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cf360();
    return g_igPsx2ThreadManager_metaObject[0];
}

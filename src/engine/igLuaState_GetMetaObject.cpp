#include "dw4/reflected.h"
extern igMetaObject *g_igLuaState_metaObject[4];
extern "C" {
void FUN_0023c590(void);
igMetaObject *igLuaState_GetMetaObject(void);
}
igMetaObject *igLuaState_GetMetaObject(void)
{
    igMetaObject *g = g_igLuaState_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0023c590();
    return g_igLuaState_metaObject[0];
}

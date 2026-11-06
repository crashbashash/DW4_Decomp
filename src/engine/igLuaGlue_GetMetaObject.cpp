#include "dw4/reflected.h"
extern igMetaObject *g_igLuaGlue_metaObject[4];
extern "C" {
void FUN_0023c7a0(void);
igMetaObject *igLuaGlue_GetMetaObject(void);
}
igMetaObject *igLuaGlue_GetMetaObject(void)
{
    igMetaObject *g = g_igLuaGlue_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0023c7a0();
    return g_igLuaGlue_metaObject[0];
}

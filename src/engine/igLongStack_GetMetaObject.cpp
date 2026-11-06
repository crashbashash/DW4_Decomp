#include "dw4/reflected.h"
extern igMetaObject *g_igLongStack_metaObject[4];
extern "C" {
void FUN_001e40f0(void);
igMetaObject *igLongStack_GetMetaObject(void);
}
igMetaObject *igLongStack_GetMetaObject(void)
{
    igMetaObject *g = g_igLongStack_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001e40f0();
    return g_igLongStack_metaObject[0];
}

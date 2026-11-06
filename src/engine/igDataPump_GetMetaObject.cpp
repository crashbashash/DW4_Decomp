#include "dw4/reflected.h"
extern igMetaObject *g_igDataPump_metaObject[4];
extern "C" {
void FUN_001e5ab0(void);
igMetaObject *igDataPump_GetMetaObject(void);
}
igMetaObject *igDataPump_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPump_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001e5ab0();
    return g_igDataPump_metaObject[0];
}

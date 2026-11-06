#include "dw4/reflected.h"
extern igMetaObject *g_igSerialScheduler_metaObject[4];
extern "C" {
void FUN_00231290(void);
igMetaObject *igSerialScheduler_GetMetaObject(void);
}
igMetaObject *igSerialScheduler_GetMetaObject(void)
{
    igMetaObject *g = g_igSerialScheduler_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00231290();
    return g_igSerialScheduler_metaObject[0];
}

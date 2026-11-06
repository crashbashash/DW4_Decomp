#include "dw4/reflected.h"
extern igMetaObject *g_igMessage_metaObject[4];
extern "C" {
void FUN_00231700(void);
igMetaObject *igMessage_GetMetaObject(void);
}
igMetaObject *igMessage_GetMetaObject(void)
{
    igMetaObject *g = g_igMessage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231700();
    return g_igMessage_metaObject[0];
}

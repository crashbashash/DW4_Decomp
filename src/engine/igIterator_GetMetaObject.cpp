#include "dw4/reflected.h"
extern igMetaObject *g_igIterator_metaObject[4];
extern "C" {
void FUN_002273d0(void);
igMetaObject *igIterator_GetMetaObject(void);
}
igMetaObject *igIterator_GetMetaObject(void)
{
    igMetaObject *g = g_igIterator_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002273d0();
    return g_igIterator_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2Thread_metaObject[4];
extern "C" {
void FUN_002cf540(void);
igMetaObject *igPsx2Thread_GetMetaObject(void);
}
igMetaObject *igPsx2Thread_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Thread_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cf540();
    return g_igPsx2Thread_metaObject[0];
}

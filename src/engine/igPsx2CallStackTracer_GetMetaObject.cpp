#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2CallStackTracer_metaObject[4];
extern "C" {
void FUN_002d04a0(void);
igMetaObject *igPsx2CallStackTracer_GetMetaObject(void);
}
igMetaObject *igPsx2CallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2CallStackTracer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002d04a0();
    return g_igPsx2CallStackTracer_metaObject[0];
}

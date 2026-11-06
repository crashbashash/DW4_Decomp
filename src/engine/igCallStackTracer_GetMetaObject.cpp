#include "dw4/reflected.h"
extern igMetaObject *g_igCallStackTracer_metaObject[4];
extern "C" {
void FUN_002cc710(void);
igMetaObject *igCallStackTracer_GetMetaObject(void);
}
igMetaObject *igCallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTracer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cc710();
    return g_igCallStackTracer_metaObject[0];
}

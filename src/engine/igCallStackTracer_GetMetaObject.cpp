#include "dw4/reflected.h"
extern igMetaObject *g_igCallStackTracer_metaObject[4];
extern "C" {
void FUN_002cc710(void);
igMetaObject *igCallStackTracer_GetMetaObject(void);
}
igMetaObject *igCallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTracer_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cc710();
    return g_igCallStackTracer_metaObject[0];
}

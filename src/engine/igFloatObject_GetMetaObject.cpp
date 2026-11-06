#include "dw4/reflected.h"
extern igMetaObject *g_igFloatObject_metaObject[4];
extern "C" {
void FUN_001e5050(void);
igMetaObject *igFloatObject_GetMetaObject(void);
}
igMetaObject *igFloatObject_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatObject_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001e5050();
    return g_igFloatObject_metaObject[0];
}

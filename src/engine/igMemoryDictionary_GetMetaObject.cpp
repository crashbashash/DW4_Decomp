#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryDictionary_metaObject[4];
extern "C" {
void FUN_002c1190(void);
igMetaObject *igMemoryDictionary_GetMetaObject(void);
}
igMetaObject *igMemoryDictionary_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDictionary_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c1190();
    return g_igMemoryDictionary_metaObject[0];
}

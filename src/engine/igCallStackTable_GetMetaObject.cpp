#include "dw4/reflected.h"
extern igMetaObject *g_igCallStackTable_metaObject[4];
extern "C" {
void FUN_002cc960(void);
igMetaObject *igCallStackTable_GetMetaObject(void);
}
igMetaObject *igCallStackTable_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTable_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cc960();
    return g_igCallStackTable_metaObject[0];
}

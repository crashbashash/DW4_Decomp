#include "dw4/reflected.h"
extern igMetaObject *g_igSymbolTable_metaObject[4];
extern "C" {
void FUN_002b87c0(void);
igMetaObject *igSymbolTable_GetMetaObject(void);
}
igMetaObject *igSymbolTable_GetMetaObject(void)
{
    igMetaObject *g = g_igSymbolTable_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b87c0();
    return g_igSymbolTable_metaObject[0];
}

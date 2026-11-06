#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryFileEntryList_metaObject[4];
extern "C" {
void FUN_002c0ad0(void);
igMetaObject *igMemoryFileEntryList_GetMetaObject(void);
}
igMetaObject *igMemoryFileEntryList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFileEntryList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c0ad0();
    return g_igMemoryFileEntryList_metaObject[0];
}

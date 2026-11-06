#include "dw4/reflected.h"
extern igMetaObject *g_igLibraryList_metaObject[4];
extern "C" {
void FUN_002c2490(void);
igMetaObject *igLibraryList_GetMetaObject(void);
}
igMetaObject *igLibraryList_GetMetaObject(void)
{
    igMetaObject *g = g_igLibraryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c2490();
    return g_igLibraryList_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igItemDataBaseList_metaObject[4];
extern "C" {
void FUN_00228190(void);
igMetaObject *igItemDataBaseList_GetMetaObject(void);
}
igMetaObject *igItemDataBaseList_GetMetaObject(void)
{
    igMetaObject *g = g_igItemDataBaseList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00228190();
    return g_igItemDataBaseList_metaObject[0];
}

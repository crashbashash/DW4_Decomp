#include "dw4/reflected.h"
extern igMetaObject *g_igRefMetaField_metaObject[4];
extern "C" {
void FUN_002bb830(void);
igMetaObject *igRefMetaField_GetMetaObject(void);
}
igMetaObject *igRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRefMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002bb830();
    return g_igRefMetaField_metaObject[0];
}

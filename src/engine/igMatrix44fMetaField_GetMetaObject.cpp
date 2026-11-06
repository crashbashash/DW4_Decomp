#include "dw4/reflected.h"
extern igMetaObject *g_igMatrix44fMetaField_metaObject[4];
extern "C" {
void FUN_00188780(void);
igMetaObject *igMatrix44fMetaField_GetMetaObject(void);
}
igMetaObject *igMatrix44fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrix44fMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00188780();
    return g_igMatrix44fMetaField_metaObject[0];
}

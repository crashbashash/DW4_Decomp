#include "dw4/reflected.h"
extern igMetaObject *g_igDependencyMetaField_metaObject[4];
extern "C" {
void FUN_002c8090(void);
igMetaObject *igDependencyMetaField_GetMetaObject(void);
}
igMetaObject *igDependencyMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c8090();
    return g_igDependencyMetaField_metaObject[0];
}

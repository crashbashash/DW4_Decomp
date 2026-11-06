#include "dw4/reflected.h"
extern igMetaObject *g_igCreateCollisionDatabase_metaObject[4];
extern "C" {
void FUN_002395b0(void);
igMetaObject *igCreateCollisionDatabase_GetMetaObject(void);
}
igMetaObject *igCreateCollisionDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igCreateCollisionDatabase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002395b0();
    return g_igCreateCollisionDatabase_metaObject[0];
}

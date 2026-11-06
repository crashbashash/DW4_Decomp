#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationDatabase_metaObject[4];
extern "C" {
void FUN_001a7b00(void);
igMetaObject *igAnimationDatabase_GetMetaObject(void);
}
igMetaObject *igAnimationDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationDatabase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7b00();
    return g_igAnimationDatabase_metaObject[0];
}

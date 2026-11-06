#include "dw4/reflected.h"
extern igMetaObject *g_igItemInterface_metaObject[4];
extern "C" {
void FUN_00227ef0(void);
igMetaObject *igItemInterface_GetMetaObject(void);
}
igMetaObject *igItemInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igItemInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227ef0();
    return g_igItemInterface_metaObject[0];
}

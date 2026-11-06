#include "dw4/reflected.h"
extern igMetaObject *g_igItemBase_metaObject[4];
extern "C" {
void FUN_00228950(void);
igMetaObject *igItemBase_GetMetaObject(void);
}
igMetaObject *igItemBase_GetMetaObject(void)
{
    igMetaObject *g = g_igItemBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228950();
    return g_igItemBase_metaObject[0];
}

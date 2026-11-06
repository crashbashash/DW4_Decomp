#include "dw4/reflected.h"
extern igMetaObject *g_igOverrideAttrSet_metaObject[4];
extern "C" {
void FUN_0019c7b0(void);
igMetaObject *igOverrideAttrSet_GetMetaObject(void);
}
igMetaObject *igOverrideAttrSet_GetMetaObject(void)
{
    igMetaObject *g = g_igOverrideAttrSet_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019c7b0();
    return g_igOverrideAttrSet_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igAttrStack_metaObject[4];
extern "C" {
void FUN_001a5b90(void);
igMetaObject *igAttrStack_GetMetaObject(void);
}
igMetaObject *igAttrStack_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a5b90();
    return g_igAttrStack_metaObject[0];
}

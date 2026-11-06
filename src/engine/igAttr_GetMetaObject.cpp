#include "dw4/reflected.h"
extern igMetaObject *g_igAttr_metaObject[4];
extern "C" {
void FUN_0013b110(void);
igMetaObject *igAttr_GetMetaObject(void);
}
igMetaObject *igAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013b110();
    return g_igAttr_metaObject[0];
}

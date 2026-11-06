#include "dw4/reflected.h"
extern igMetaObject *g_igAttr_metaObject[4];
extern "C" {
void FUN_0013b110(void);
igMetaObject *igAttr_GetMetaObject(void);
}
igMetaObject *igAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0013b110();
    return g_igAttr_metaObject[0];
}

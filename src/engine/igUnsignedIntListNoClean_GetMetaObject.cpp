#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedIntListNoClean_metaObject[4];
extern "C" {
void FUN_002ca380(void);
igMetaObject *igUnsignedIntListNoClean_GetMetaObject(void);
}
igMetaObject *igUnsignedIntListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntListNoClean_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ca380();
    return g_igUnsignedIntListNoClean_metaObject[0];
}

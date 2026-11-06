#include "dw4/reflected.h"
extern igMetaObject *g_igCustomStateCollection_metaObject[4];
extern "C" {
void FUN_0014f0c0(void);
igMetaObject *igCustomStateCollection_GetMetaObject(void);
}
igMetaObject *igCustomStateCollection_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateCollection_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014f0c0();
    return g_igCustomStateCollection_metaObject[0];
}

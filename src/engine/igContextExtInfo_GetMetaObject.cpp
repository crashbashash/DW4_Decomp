#include "dw4/reflected.h"
extern igMetaObject *g_igContextExtInfo_metaObject[4];
extern "C" {
void FUN_002cb7c0(void);
igMetaObject *igContextExtInfo_GetMetaObject(void);
}
igMetaObject *igContextExtInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtInfo_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cb7c0();
    return g_igContextExtInfo_metaObject[0];
}

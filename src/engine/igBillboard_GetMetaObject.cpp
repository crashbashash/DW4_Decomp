#include "dw4/reflected.h"
extern igMetaObject *g_igBillboard_metaObject[4];
extern "C" {
void FUN_001a5050(void);
igMetaObject *igBillboard_GetMetaObject(void);
}
igMetaObject *igBillboard_GetMetaObject(void)
{
    igMetaObject *g = g_igBillboard_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a5050();
    return g_igBillboard_metaObject[0];
}

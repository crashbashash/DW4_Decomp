#include "dw4/reflected.h"
extern igMetaObject *g_igMessageBase_metaObject[4];
extern "C" {
void FUN_00226540(void);
igMetaObject *igMessageBase_GetMetaObject(void);
}
igMetaObject *igMessageBase_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageBase_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00226540();
    return g_igMessageBase_metaObject[0];
}

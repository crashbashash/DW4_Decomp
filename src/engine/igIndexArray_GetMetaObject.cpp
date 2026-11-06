#include "dw4/reflected.h"
extern igMetaObject *g_igIndexArray_metaObject[4];
extern "C" {
void FUN_0014d890(void);
igMetaObject *igIndexArray_GetMetaObject(void);
}
igMetaObject *igIndexArray_GetMetaObject(void)
{
    igMetaObject *g = g_igIndexArray_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014d890();
    return g_igIndexArray_metaObject[0];
}

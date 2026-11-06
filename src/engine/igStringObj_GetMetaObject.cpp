#include "dw4/reflected.h"
extern igMetaObject *g_igStringObj_metaObject[4];
extern "C" {
void FUN_002b9620(void);
igMetaObject *igStringObj_GetMetaObject(void);
}
igMetaObject *igStringObj_GetMetaObject(void)
{
    igMetaObject *g = g_igStringObj_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b9620();
    return g_igStringObj_metaObject[0];
}

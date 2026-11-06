#include "dw4/reflected.h"
extern igMetaObject *g_igController_metaObject[4];
extern "C" {
void FUN_00146900(void);
igMetaObject *igController_GetMetaObject(void);
}
igMetaObject *igController_GetMetaObject(void)
{
    igMetaObject *g = g_igController_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146900();
    return g_igController_metaObject[0];
}

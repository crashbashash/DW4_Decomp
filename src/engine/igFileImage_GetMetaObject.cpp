#include "dw4/reflected.h"
extern igMetaObject *g_igFileImage_metaObject[4];
extern "C" {
void FUN_0014def0(void);
igMetaObject *igFileImage_GetMetaObject(void);
}
igMetaObject *igFileImage_GetMetaObject(void)
{
    igMetaObject *g = g_igFileImage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014def0();
    return g_igFileImage_metaObject[0];
}

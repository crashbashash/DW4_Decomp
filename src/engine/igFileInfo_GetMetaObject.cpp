#include "dw4/reflected.h"
extern igMetaObject *g_igFileInfo_metaObject[4];
extern "C" {
void FUN_002290c0(void);
igMetaObject *igFileInfo_GetMetaObject(void);
}
igMetaObject *igFileInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igFileInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002290c0();
    return g_igFileInfo_metaObject[0];
}

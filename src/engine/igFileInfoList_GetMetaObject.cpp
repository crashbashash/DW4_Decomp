#include "dw4/reflected.h"
extern igMetaObject *g_igFileInfoList_metaObject[4];
extern "C" {
void FUN_00228dd0(void);
igMetaObject *igFileInfoList_GetMetaObject(void);
}
igMetaObject *igFileInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igFileInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228dd0();
    return g_igFileInfoList_metaObject[0];
}

#include "dw4/reflected.h"
extern igMetaObject *g_igBoolList_metaObject[4];
extern "C" {
void FUN_002cb1f0(void);
igMetaObject *igBoolList_GetMetaObject(void);
}
igMetaObject *igBoolList_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cb1f0();
    return g_igBoolList_metaObject[0];
}

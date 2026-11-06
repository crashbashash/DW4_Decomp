#include "dw4/reflected.h"
extern igMetaObject *g_igIntList_metaObject[4];
extern "C" {
void igIntList_EnsureRegistered(void);
igMetaObject *igIntList_GetMetaObject(void);
}
igMetaObject *igIntList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntList_EnsureRegistered();
    return g_igIntList_metaObject[0];
}

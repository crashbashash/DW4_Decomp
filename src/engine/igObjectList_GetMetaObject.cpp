#include "dw4/reflected.h"
extern igMetaObject *g_igObjectList_metaObject[4];
extern "C" {
void igObjectList_EnsureRegistered(void);
igMetaObject *igObjectList_GetMetaObject(void);
}
igMetaObject *igObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectList_EnsureRegistered();
    return g_igObjectList_metaObject[0];
}

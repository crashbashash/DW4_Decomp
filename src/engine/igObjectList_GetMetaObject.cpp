#include "dw4/reflected.h"
extern igMetaObject *g_igObjectList_metaObject[4];
extern "C" {
void igObjectList_EnsureRegistered(void);
igMetaObject *igObjectList_GetMetaObject(void);
}
igMetaObject *igObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igObjectList_EnsureRegistered();
    return g_igObjectList_metaObject[0];
}

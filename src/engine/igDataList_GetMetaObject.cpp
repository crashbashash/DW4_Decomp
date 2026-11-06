#include "dw4/reflected.h"
extern igMetaObject *g_igDataList_metaObject[4];
extern "C" {
void igDataList_EnsureRegistered(void);
igMetaObject *igDataList_GetMetaObject(void);
}
igMetaObject *igDataList_GetMetaObject(void)
{
    igMetaObject *g = g_igDataList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igDataList_EnsureRegistered();
    return g_igDataList_metaObject[0];
}

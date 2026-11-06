#include "dw4/reflected.h"
extern igMetaObject *g_igViewList_metaObject[4];
extern "C" {
void igViewList_EnsureRegistered(void);
igMetaObject *igViewList_GetMetaObject(void);
}
igMetaObject *igViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igViewList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igViewList_EnsureRegistered();
    return g_igViewList_metaObject[0];
}

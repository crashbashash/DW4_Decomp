#include "dw4/reflected.h"
extern igMetaObject *g_igFieldChangeViewList_metaObject[4];
extern "C" {
void igFieldChangeViewList_EnsureRegistered(void);
igMetaObject *igFieldChangeViewList_GetMetaObject(void);
}
igMetaObject *igFieldChangeViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeViewList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igFieldChangeViewList_EnsureRegistered();
    return g_igFieldChangeViewList_metaObject[0];
}
